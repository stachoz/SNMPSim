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
    DataReceiverApplication(int &argc, char **argv);

private slots:
    void processDatagram() const;

private:
    std::unique_ptr<QUdpSocket> updSocket = std::make_unique<QUdpSocket>(this);

    void initSocket();
};
