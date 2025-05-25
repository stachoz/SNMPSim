//
// Created by stachoz on 3/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SnmpSimWindow.h" resolved

#include "SnmpSimWindow.h"


SnmpSimWindow::SnmpSimWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::SnmpSimWindow) {
    ui->setupUi(this);
    ui->groupBox_menu->hide();

    connect(ui->startButton, &QPushButton::clicked, dockerLauncher.get(),[this]() {
        dockerLauncher->startDockerContainer();
        ui->startButton->setDisabled(true);
    });

    auto* noDevicesPageLayout = new QVBoxLayout();
    noDevicesLabel->setStyleSheet("font-size: 15px;");
    noDevicesPageLayout->addWidget(noDevicesLabel, 1,  Qt::AlignHCenter | Qt::AlignVCenter);

    devicesPage->setLayout(devicesLayout);
    detailsPage->setLayout(detailsLayout);
    noDevicesPage->setLayout(noDevicesPageLayout);

    mainStackedLayout->addWidget(devicesPage);
    mainStackedLayout->addWidget(detailsPage);
    mainStackedLayout->addWidget(noDevicesPage);

    ui->groupBox_main->setLayout(mainStackedLayout);
    mainStackedLayout->setCurrentWidget(noDevicesPage);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}

void SnmpSimWindow::createNewDeviceWidget(std::string_view ip, std::string_view deviceName) {
    auto* deviceWidget = new DeviceWidget(deviceName.data(), ip.data(), this);
    connect(deviceWidget, &DeviceWidget::sigShowDeviceDetails, this, &SnmpSimWindow::showDeviceDetails);
    deviceWidgets.push_back(deviceWidget);
    devicesLayout->addWidget(deviceWidget);

    auto deviceDetails = new DeviceDetailsWidget(deviceName.data(), ip.data(), this);
    connect(deviceDetails, &DeviceDetailsWidget::backToDevicesRequested, this, &SnmpSimWindow::hideDeviceDetails);
    deviceDetails->hide();
    deviceDetails->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    detailsLayout->addWidget(deviceDetails, 1);
    deviceDetailsWidgets[ip.data()] = deviceDetails;
}

void SnmpSimWindow::showDeviceDetails(const QString& ipAddress) {
    mainStackedLayout->setCurrentWidget(detailsPage);

    shownDeviceDetailsIp = ipAddress.toStdString();

    if(deviceDetailsWidgets.contains(ipAddress)) {
        auto* clickedDevieDetails = deviceDetailsWidgets[ipAddress];
        clickedDevieDetails->show();
    }
}

void SnmpSimWindow::hideDeviceDetails() {
    mainStackedLayout->setCurrentWidget(devicesPage);
    shownDeviceDetailsIp = "";

    for(auto* details : deviceDetailsWidgets) {
        details->hide();
    }
}

void SnmpSimWindow::updateDeviceDetails(const SnmpFrame& frame) {
    auto toUpdate = deviceDetailsWidgets[frame.ip().c_str()];
    DeviceParam param {
        frame.paramname(),
        frame.oid(),
        frame.value(),
        frame.isvalid()
    };
    toUpdate->updateParameter(param);
}

void SnmpSimWindow::showNoContainersRunningLabel() {
    noDevicesLabel->show();
    mainStackedLayout->setCurrentWidget(noDevicesPage);
}

void SnmpSimWindow::hideNoContainersRunningLabel() {
    mainStackedLayout->setCurrentWidget(devicesPage);
}

void SnmpSimWindow::updateDeviceStatus(std::string_view ip, DeviceStatus status) {
    auto deviceToUpdate = std::find_if(std::begin(deviceWidgets), std::end(deviceWidgets), [this, ip](DeviceWidget* device) {
        return device->getIp() == ip;
    });
    if(deviceToUpdate != std::end(deviceWidgets)) {
        (*deviceToUpdate)->setDeviceStatus(status);
    }
}
