//
// Created by stachoz on 11/16/24.
//

#pragma once

#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include <QTimer>

#include "SNMPMessageBuilder.h"
#include "SNMPMessageDecoder.h"


class SNMPLogic : public QObject {
    Q_OBJECT
public:
    explicit SNMPLogic(QObject* parent = nullptr);
private:
    std::unique_ptr<QUdpSocket> udpSocket = std::make_unique<QUdpSocket>();
    std::unique_ptr<SNMPMessageBuilder> snmpMessageBuilder = std::make_unique<SNMPMessageBuilder>();
    std::unique_ptr<SNMPMessageDecoder> snmpMessageDecoder = std::make_unique<SNMPMessageDecoder>();
    QTimer* sendMessageTimer = new QTimer(this);

    void initSocket();

    void sendData();

    void readPendingDatagrams();

    void processTheDatagram(QNetworkDatagram &datagram) const;
};
