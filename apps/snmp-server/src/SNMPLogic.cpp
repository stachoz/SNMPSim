#include "SNMPLogic.h"

#include <iostream>

#include "data/Device.h"

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
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        forwardDataToHost(datagram);
        // processTheDatagram(datagram);
    }
}

void SNMPLogic::processTheDatagram(const QNetworkDatagram& datagram) const {
    QByteArray bytesToDecode = datagram.data();
    QHostAddress senderAddress = datagram.senderAddress();
    SNMPMessage decodedMessage = SNMPMessageDecoder::decodeSNMPMessageBytes(bytesToDecode);
    decodedMessage.ip = senderAddress.toString().toStdString();

    std::cout << "Message decoded: " << decodedMessage.getString() << std::endl;
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

void SNMPLogic::forwardDataToHost(const QNetworkDatagram& datagram) {
    auto result = udpSocket->writeDatagram(datagram.data(), QHostAddress("172.17.0.1"), 55555);

    if(result == -1) {
        std::cout << "Unable to send datagram." << std::endl;
        std::cout <<  udpSocket->errorString().toStdString() << std::endl;
    }
}