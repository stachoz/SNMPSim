//
// Created by stachoz on 3/21/25.
//

#pragma once
#include <map>
#include <QNetworkDatagram>
#include <qobject.h>
#include <QTimer>
#include <QUdpSocket>
#include <SnmpFrame.pb.h>
#include <string>

#include "DeviceParam.h"
#include "DockerContainerLauncher.h"
#include "SnmpDataManager.h"

class DataReceiverLogic : public QObject{
    Q_OBJECT
public:
    explicit DataReceiverLogic(QObject *parent = nullptr);

signals:
    void snmpFrameReceived(SnmpFrame param);
    void newDeviceDataReceived(std::string_view ip, std::string_view deviceName);
    void noDataReceivedFromContainers();
    void dataReceiving();
    void deviceStatusChange(std::string_view ip, DeviceStatus status);
private slots:
    void processDatagram();

private:
    std::unique_ptr<QUdpSocket> updSocket = std::make_unique<QUdpSocket>(this);
    std::unique_ptr<SnmpDataManager> dataManager = std::make_unique<SnmpDataManager>();
    QTimer noDataReceivedTimer;
    int dataNoReceivedTimeout = 5000;
    bool noContainersRunning {true};

    void initSocket();

    void updateSnmpData(const SnmpFrame &frame);
};
