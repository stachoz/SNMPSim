#include "SNMPLogic.h"

#include <iostream>

SNMPLogic::SNMPLogic(QObject *parent) : QObject(parent){
    initSocket();
    sendMessageTimer->setInterval(1000);
    connect(sendMessageTimer, &QTimer::timeout, this, &SNMPLogic::sendData);
    sendMessageTimer->start();
}

void SNMPLogic::initSocket() {
    udpSocket = std::make_unique<QUdpSocket>(this);
    udpSocket->bind(QHostAddress::LocalHost, 160);

    connect(udpSocket.get(), &QUdpSocket::readyRead, this, &SNMPLogic::readPendingDatagrams);
}

void SNMPLogic::readPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processTheDatagram(datagram);
    }
}

void SNMPLogic::processTheDatagram(QNetworkDatagram &datagram) const {
    QByteArray bytesToDecode = datagram.data();
    SNMPMessage decodedMessage = snmpMessageDecoder->decodeSNMPMessageBytes(bytesToDecode);

    std::cout << "Message decoded: " << decodedMessage.getString() << std::endl;
}

void SNMPLogic::sendData() {
    SNMPMessage message;
    message.oid = {1, 3, 6, 1, 2137, 1};
    message.communityString = "public";
    message.requestId = 1;

    QByteArray decodedMessage = snmpMessageBuilder->buildMessage(message);

    QHostAddress destinationAddress("127.0.0.1");

    auto result = udpSocket->writeDatagram(decodedMessage, QHostAddress("127.0.0.1"), 161);

    if(result == -1) {
        std::cout << "Unable to send datagram" << std::endl;
    }
    else {
        std::cout << "snmp-get sent. " << message.getString() << " to: " << destinationAddress.toString().toStdString() << std::endl;
    }
}