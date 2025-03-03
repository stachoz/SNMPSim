//
// Created by stachoz on 2/25/25.
//

#pragma once
#include <QApplication>
#include <QNetworkDatagram>
#include <QUdpSocket>


class DataReceiverApplication : public QApplication {
    Q_OBJECT
public:
    DataReceiverApplication(int &argc, char **argv) : QApplication(argc, argv) {
        initSocket();
    }

private slots:
    void processDatagram() {
        while (updSocket->hasPendingDatagrams()) {
            // QNetworkDatagram datagram = updSocket->receiveDatagram();
            auto datagram = updSocket->receiveDatagram();
            qDebug() << datagram.data();
        }
    }

private:
    std::unique_ptr<QUdpSocket> updSocket = std::make_unique<QUdpSocket>(this);

    void initSocket() {
        updSocket->bind(QHostAddress::AnyIPv4, 55555);
        connect(updSocket.get(), &QUdpSocket::readyRead, this, &DataReceiverApplication::processDatagram);
    }

};
