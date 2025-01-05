//
// Created by stachoz on 11/16/24.
//

#include "SNMPLogic.h"

SNMPLogic::SNMPLogic(QObject *parent) : QObject(parent), udpSocket(std::make_unique<QUdpSocket>()) {}

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

void SNMPLogic::processTheDatagram(const QNetworkDatagram &datagram) {
}
