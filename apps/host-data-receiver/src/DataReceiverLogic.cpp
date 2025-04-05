//
// Created by stachoz on 3/21/25.
//

#include "DataReceiverLogic.h"

DataReceiverLogic::DataReceiverLogic(QObject *parent) : QObject(parent) {
    initSocket();
    dockerLauncher->startDockerContainer();
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

            saveSnmpFrame(snmpFrame);
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

void DataReceiverLogic::saveSnmpFrame(const SnmpFrame &snmpFrame) {
    const auto& ip = snmpFrame.ip();
    auto deviceParamIt = deviceParamsByIp.find(ip);

    DeviceParam newDeviceParam;
    newDeviceParam.paramName = snmpFrame.devicename();
    newDeviceParam.oid = snmpFrame.oid();
    newDeviceParam.value = snmpFrame.value();

    if(deviceParamIt == deviceParamsByIp.end()) {
        std::vector<DeviceParam> deviceParams;
        deviceParams.push_back(newDeviceParam);
        deviceParamsByIp[ip] = deviceParams;
    }
    else {
        auto [ip, deviceParams] = *deviceParamIt;
        auto paramByOid = std::find_if(std::begin(deviceParams), std::end(deviceParams), [this, snmpFrame](const DeviceParam& deviceParam){
            return deviceParam.oid == snmpFrame.oid();
        });

        if(paramByOid == std::end(deviceParams)) {
            deviceParams.push_back(newDeviceParam);
        }
        else {
            paramByOid->value = snmpFrame.value();
        }
    }
}
