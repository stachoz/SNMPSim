//
// Created by stachoz on 3/21/25.
//

#include "DataReceiverLogic.h"

DataReceiverLogic::DataReceiverLogic(QObject *parent) : QObject(parent) {
    initSocket();
}

void DataReceiverLogic::processDatagram() {
    while (updSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = updSocket->receiveDatagram();
        QByteArray data = datagram.data();
        SnmpFrame snmpFrame;
        if(snmpFrame.ParseFromArray(data.data(), data.size())) {
            std::cout << "Odebrano ramke: "
                    << "IP: " << snmpFrame.ip() << " ,"
                    << "RequestId: " << snmpFrame.requestid() << " ,"
                    << "Oid: " << snmpFrame.oid() << " ,"
                    << "Value: " << snmpFrame.value() << std::endl;

            emit snmpFrameReceived(snmpFrame);
        }
        else {
            std::cout << "Błąd deserializacji ramki Protobuf";
        }
    }
}

void DataReceiverLogic::initSocket() {
    updSocket->bind(QHostAddress::AnyIPv4, 55555);
    connect(updSocket.get(), &QUdpSocket::readyRead, this, &DataReceiverLogic::processDatagram);
}