#include "SNMPLogic.h"

uint16_t SNMPLogic::requestIdCounter = 0;

SNMPLogic::SNMPLogic(QObject *parent) : QObject(parent){
    initSocket();
    sendMessageTimer.setInterval(1000);
    connect(&sendMessageTimer, &QTimer::timeout, this, &SNMPLogic::sendData);
    sendMessageTimer.start();
}

void SNMPLogic::initSocket() {
    udpSocket->bind(QHostAddress::AnyIPv4, 161);

    connect(udpSocket.get(), &QUdpSocket::readyRead, this, &SNMPLogic::readPendingDatagrams);
}

void SNMPLogic::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram receivedDatagram = udpSocket->receiveDatagram();
        QByteArray receivedData = receivedDatagram.data();
        SNMPMessage decodedSnmpMessage = SNMPMessageDecoder::decodeSNMPMessageBytes(receivedData);
        decodedSnmpMessage.ip = receivedDatagram.senderAddress().toString().toStdString();
        forwardDataToHost(decodedSnmpMessage);
    }
}

void SNMPLogic::sendData() {
    std::vector messages = createSNMPMessages(deviceManager->getDevices());

    for(const auto& message : messages) {
        QByteArray encodedMessage = SNMPMessageBuilder::buildMessage(message);
        auto result = udpSocket->writeDatagram(encodedMessage, QHostAddress(QString::fromStdString(message.ip)), 161);

        if(result == -1) {
            std::cout << "Unable to send datagram. " << message.getString() << std::endl;
            std::cout <<  udpSocket->errorString().toStdString() << std::endl;
        }
        else {
            std::cout << "snmp-get sent. " << message.getString() << std::endl;
        }
    }
}

std::vector<SNMPMessage> SNMPLogic::createSNMPMessages(const std::vector<Device> &devices) const {
    std::vector<SNMPMessage> snmpMessages;

    for(const auto& device : devices) {
        SNMPMessage message;
        message.communityString = "public";
        message.ip = device.ip;
        for(auto& [oidName, oidValue] : device.snmpOids) {
            message.requestId = requestIdCounter++;
            message.oid = oidValue;
            snmpMessages.push_back(message);
        }
    }

    return snmpMessages;
}

void SNMPLogic::forwardDataToHost(SNMPMessage& message) {
    if(message.value.has_value()) {
        SnmpFrame protoSnmpFrame;
        protoSnmpFrame.set_requestid(message.requestId);
        protoSnmpFrame.set_ip(message.ip);
        protoSnmpFrame.set_oid(message.getOidAsString());
        protoSnmpFrame.set_value(std::get<int32_t>(*message.value));
        protoSnmpFrame.set_timestamp(QDateTime::currentMSecsSinceEpoch());

        QByteArray data(protoSnmpFrame.ByteSizeLong(), 0);
        protoSnmpFrame.SerializeToArray(data.data(), data.size());

        // #TODO automatyczne wczytywanie adresu host.docker.internal (192.168.65.2)
        auto result = udpSocket->writeDatagram(data, QHostAddress("192.168.65.2"), 55555);

        if(result == -1) {
            std::cout << "Unable to send proto frame" << std::endl;
            std::cout <<  udpSocket->errorString().toStdString() << std::endl;
        }
        else {
            std::cout << "Message forwarded" << std::endl;
        }
    }
}