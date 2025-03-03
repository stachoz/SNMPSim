//
// Created by stachoz on 11/16/24.
//

#pragma once


#include "data/Device.h"
#include "data/DeviceManager.h"
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
    std::unique_ptr<QUdpSocket> udpSocket = std::make_unique<QUdpSocket>(this);
    std::unique_ptr<SNMPMessageBuilder> snmpMessageBuilder = std::make_unique<SNMPMessageBuilder>();
    std::unique_ptr<SNMPMessageDecoder> snmpMessageDecoder = std::make_unique<SNMPMessageDecoder>();
    std::unique_ptr<DeviceManager> deviceManager = std::make_unique<DeviceManager>();
    QTimer sendMessageTimer {this};
    static uint16_t requestIdCounter;

    void initSocket();

    void sendData();

    void readPendingDatagrams();

    void processTheDatagram(const QNetworkDatagram &datagram) const;

    std::vector<SNMPMessage> createSNMPMessages(const std::vector<Device> &devices) const;

    void forwardDataToHost(const QNetworkDatagram &datagram);
};
