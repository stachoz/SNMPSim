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

    noDevicesLabel->setStyleSheet("font-size: 15px;");
    mainGroupBoxLayout->addWidget(noDevicesLabel, 0,0,  Qt::AlignHCenter | Qt::AlignVCenter);
    ui->groupBox_main->setLayout(mainGroupBoxLayout);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}

void SnmpSimWindow::receiveNewSnmpFrame(const SnmpFrame& frame) {
    areContainersRunning = true;
    noDevicesLabel->hide();
    const auto& ip = frame.ip();
    auto deviceParamIt = deviceParams.find(ip);

    DeviceParam newDeviceParam {frame.devicename(), frame.oid(), frame.value()};
    newDeviceParam.value = frame.value();

    if(deviceParamIt == deviceParams.end()) {
        auto deviceWidget = new DeviceWidget(
            frame.devicename().c_str(),
            frame.ip().c_str(),
            this
        );
        connect(deviceWidget, &DeviceWidget::sigShowDeviceDetails, this, &SnmpSimWindow::showDeviceDetails);
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

    if(!deviceDetailsWidgets.contains(frame.ip().c_str())) {
        auto* deviceDetailWidget = new DeviceDetailsWidget(frame.devicename().c_str(), frame.ip().c_str());
        connect(deviceDetailWidget, &DeviceDetailsWidget::backToDevicesRequested, this, &SnmpSimWindow::hideDeviceDetails);
        deviceDetailWidget->hide();
        mainGroupBoxLayout->addWidget(deviceDetailWidget);
        deviceDetailsWidgets[frame.ip().c_str()] = deviceDetailWidget;
        std::cout << deviceDetailsWidgets.size() << std::endl;
    }

    if(shownDeviceDetailsIp == frame.ip()) {
        auto* detailsToUpadate = deviceDetailsWidgets[frame.ip().c_str()];
        detailsToUpadate->updateParameters(deviceParams[frame.ip()]);
    }
}

void SnmpSimWindow::addNewDeviceWidget(DeviceWidget* newWidget) {
    deviceWidgets.push_back(newWidget);
    mainGroupBoxLayout->addWidget(newWidget, rows, columns);
    ++columns;
    if(columns % 3 == 0) {
        ++rows;
        columns = 0;
    }
}

void SnmpSimWindow::showDeviceDetails(const QString& ipAddress) {
    shownDeviceDetailsIp = ipAddress.toStdString();
    for(auto* device : deviceWidgets) {
        device->hide();
    }

    if(deviceDetailsWidgets.contains(ipAddress)) {
        auto* clickedDevieDetails = deviceDetailsWidgets[ipAddress];
        clickedDevieDetails->updateParameters(deviceParams[ipAddress.toStdString()]);
        clickedDevieDetails->show();
    }
}

void SnmpSimWindow::hideDeviceDetails() {
    shownDeviceDetailsIp = "";

    for(auto* details : deviceDetailsWidgets) {
        details->hide();
    }

    for(auto* device : deviceWidgets) {
        device->show();
    }
}