//
// Created by stachoz on 3/21/25.
//

#pragma once
#include <map>
#include <QNetworkDatagram>
#include <qobject.h>
#include <QUdpSocket>
#include <SnmpFrame.pb.h>
#include <string>

#include "DeviceParam.h"
#include "DockerContainerLauncher.h"

class DataReceiverLogic : public QObject{
    Q_OBJECT
public:
    explicit DataReceiverLogic(QObject *parent = nullptr);

signals:
    void  snmpFrameReceived(SnmpFrame param);
private slots:
    void processDatagram();

private:
    std::unique_ptr<QUdpSocket> updSocket = std::make_unique<QUdpSocket>(this);
    std::unique_ptr<DockerContainerLauncher> dockerLauncher = std::make_unique<DockerContainerLauncher>(this);
    std::map<std::string, std::vector<DeviceParam>> deviceParamsByIp;

    void initSocket();
};
