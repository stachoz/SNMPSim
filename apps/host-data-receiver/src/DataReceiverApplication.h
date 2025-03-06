//
// Created by stachoz on 2/25/25.
//

#pragma once
#include <iostream>
#include <QApplication>
#include <QNetworkDatagram>
#include <QUdpSocket>
#include <SnmpFrame.pb.h>

#include "SNMPMessageDecoder.h"


class DataReceiverApplication : public QApplication {
    Q_OBJECT
public:
    DataReceiverApplication(int &argc, char **argv) : QApplication(argc, argv) {
        initSocket();
    }

private slots:
    void processDatagram() {
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
            }
            else {
                std::cout << "Błąd deserializacji ramki Protobuf";
            }
        }
    }

private:
    std::unique_ptr<QUdpSocket> updSocket = std::make_unique<QUdpSocket>(this);

    void initSocket() {
        updSocket->bind(QHostAddress::AnyIPv4, 55555);
        connect(updSocket.get(), &QUdpSocket::readyRead, this, &DataReceiverApplication::processDatagram);
    }

};
