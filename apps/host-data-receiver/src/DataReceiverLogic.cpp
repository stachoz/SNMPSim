//
// Created by stachoz on 3/21/25.
//

#include "DataReceiverLogic.h"

DataReceiverLogic::DataReceiverLogic(QObject *parent) : QObject(parent) {
    initSocket();
    noDataReceivedTimer.setInterval(dataNoReceivedTimeout);
    connect(&noDataReceivedTimer, &QTimer::timeout, this, [this] {
        noContainersRunning = true;
        emit noDataReceivedFromContainers();
    });
    noDataReceivedTimer.start();
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
                    << "Value: " << snmpFrame.value() << " ,"
                    << "isValid: " << snmpFrame.isvalid() << " ,"
                    << "unit: " << snmpFrame.unit() << std::endl;

            updateSnmpData(snmpFrame);
            noDataReceivedTimer.start();
            if(noContainersRunning) {
                emit dataReceiving();
                noContainersRunning = false;
            }
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

void DataReceiverLogic::updateSnmpData(const SnmpFrame& frame) {
    if(dataManager->isNewDevice(frame.ip())) {
       emit newDeviceDataReceived(frame.ip(), frame.devicename());
    }
    dataManager->updateData(frame);
    emit deviceStatusChange(frame.ip(), dataManager->checkGeneralDeviceStatus(frame.ip()));
    emit snmpFrameReceived(frame);
}