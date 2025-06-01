//
// Created by stachoz on 11/16/24.
//

#pragma once

#include <iostream>
#include <QDateTime>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include <QTimer>

#include "data/DeviceManager.h"

#include "SNMPMessageBuilder.h"
#include "SNMPMessageDecoder.h"
#include "SnmpFrame.pb.h"


class SNMPLogic : public QObject {
    Q_OBJECT
public:
    SNMPLogic(QObject *parent, std::string ip, int port);
private:
    std::unique_ptr<QUdpSocket> udpSocket = std::make_unique<QUdpSocket>(this);
    std::unique_ptr<SNMPMessageBuilder> snmpMessageBuilder = std::make_unique<SNMPMessageBuilder>();
    std::unique_ptr<SNMPMessageDecoder> snmpMessageDecoder = std::make_unique<SNMPMessageDecoder>();
    std::unique_ptr<DeviceManager> deviceManager = std::make_unique<DeviceManager>();
    QTimer sendMessageTimer {this};
    static uint16_t requestIdCounter;
    std::string receiverIp;
    int receiverPort;


    void initSocket();

    void sendData();

    void readPendingDatagrams();

    std::vector<SNMPMessage> createSNMPMessages(const std::vector<Device> &devices) const;

    void forwardDataToHost(SNMPMessage &message) const;

    bool validateMessage(const SNMPMessage &message) const;

    void sendDevicesNames() const;
};
