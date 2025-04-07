//
// Created by stachoz on 3/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SnmpSimWindow.h" resolved

#include "SnmpSimWindow.h"

#include <iostream>
#include <QLabel>

#include "ui_SnmpSimWindow.h"
#include "gui/widgets/DeviceWidget.h"
#include "src/DockerContainerLauncher.h"


SnmpSimWindow::SnmpSimWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::SnmpSimWindow) {
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, dockerLauncher.get(),[this]() {
        dockerLauncher->startDockerContainer();
        areContainersRunning = true;
        ui->startButton->setDisabled(true);
    });

    if(!areContainersRunning) {
        noDevicesLabel->setStyleSheet("font-size: 15px;");
        devicesLayout->addWidget(noDevicesLabel, 0,0,  Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else {
        noDevicesLabel->hide();
    }
    ui->groupBox_devies->setLayout(devicesLayout);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}

void SnmpSimWindow::receiveNewSnmpFrame(const SnmpFrame& frame) {
    areContainersRunning = true;
    noDevicesLabel->hide();
    const auto& ip = frame.ip();
    auto deviceParamIt = deviceParams.find(ip);

    DeviceParam newDeviceParam;
    newDeviceParam.paramName = frame.devicename();
    newDeviceParam.oid = frame.oid();
    newDeviceParam.value = frame.value();

    if(deviceParamIt == deviceParams.end()) {
        auto deviceWidget = new DeviceWidget(
            frame.devicename().c_str(),
            frame.ip().c_str(),
            this
        );
        addNewDeviceWidget(deviceWidget);
        std::vector<DeviceParam> params;
        params.push_back(newDeviceParam);
        deviceParams[ip] = params;
    }
    else {
        auto [ip, deviceParams] = *deviceParamIt;
        auto paramByOid = std::find_if(std::begin(deviceParams), std::end(deviceParams), [this, &frame](const DeviceParam& deviceParam){
            return deviceParam.oid == frame.oid();
        });

        if(paramByOid == std::end(deviceParams)) {
            deviceParams.push_back(newDeviceParam);
        }
        else {
            paramByOid->value = frame.value();
        }
    }
}

void SnmpSimWindow::addNewDeviceWidget(DeviceWidget* newWidget) {
    deviceWidgets.push_back(newWidget);
    devicesLayout->addWidget(newWidget, rows, columns);
    ++columns;
    if(columns % 3 == 0) {
        ++rows;
        columns = 0;
    }
}