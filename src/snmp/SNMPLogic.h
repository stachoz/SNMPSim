//
// Created by stachoz on 11/16/24.
//

#pragma once

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>


class SNMPLogic : public QObject {
    Q_OBJECT
public:
    explicit SNMPLogic(QObject* parent = nullptr);
private:
    std::unique_ptr<QUdpSocket> udpSocket;

    void initSocket();

    void processTheDatagram(const QNetworkDatagram & datagram);

    void readPendingDatagrams();
    void sendData();
};
