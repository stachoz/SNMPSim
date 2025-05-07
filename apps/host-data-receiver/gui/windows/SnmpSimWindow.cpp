//
// Created by stachoz on 3/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SnmpSimWindow.h" resolved

#include "SnmpSimWindow.h"

#include <QLabel>

#include "ui_SnmpSimWindow.h"
#include "gui/widgets/DeviceWidget.h"
#include "src/DockerContainerLauncher.h"


SnmpSimWindow::SnmpSimWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::SnmpSimWindow) {
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, dockerLauncher.get(),[this]() {
        dockerLauncher->startDockerContainer();
        ui->startButton->setDisabled(true);
    });

    auto mainLayout = new QVBoxLayout();

    devicesGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    devicesGroupBox->setLayout(devicesLayout);
    devicesGroupBox->setStyleSheet(
        "QGroupBox {"
        "       border: none;"
        "   };"
        );

    mainLayout->addWidget(devicesGroupBox, 1, Qt::AlignHCenter | Qt::AlignVCenter);
    devicesGroupBox->setMinimumSize(620, 550);
    devicesGroupBox->hide();

    noDevicesLabel->setStyleSheet("font-size: 15px;");
    mainLayout->addWidget(noDevicesLabel, 1, Qt::AlignHCenter| Qt::AlignVCenter);
    ui->groupBox_main->setLayout(mainLayout);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}

void SnmpSimWindow::createNewDeviceWidget(std::string_view ip, std::string_view deviceName) {
    auto* deviceWidget = new DeviceWidget(deviceName.data(), ip.data(), this);
    connect(deviceWidget, &DeviceWidget::sigShowDeviceDetails, this, &SnmpSimWindow::showDeviceDetails);
    deviceWidgets.push_back(deviceWidget);
    devicesLayout->addWidget(deviceWidget, rows, columns);

    auto deviceDetails = new DeviceDetailsWidget(deviceName.data(), ip.data(), this);
    connect(deviceDetails, &DeviceDetailsWidget::backToDevicesRequested, this, &SnmpSimWindow::hideDeviceDetails);
    deviceDetails->hide();
    devicesLayout->addWidget(deviceDetails, 0, 0);
    deviceDetails->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deviceDetailsWidgets[ip.data()] = deviceDetails;

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
        // clickedDevieDetails->updateParameters(deviceParams[ipAddress.toStdString()]);
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

void SnmpSimWindow::updateDeviceDetails(const SnmpFrame& frame) {
    auto toUpdate = deviceDetailsWidgets[frame.ip().c_str()];
    DeviceParam param {
        frame.paramname(),
        frame.oid(),
        frame.value(),
        frame.isvalid()
    };
    if(shownDeviceDetailsIp == frame.ip()) {
        toUpdate->updateParameter(param);
    }
}

void SnmpSimWindow::showNoContainersRunningLabel() {
    devicesGroupBox->hide();
    noDevicesLabel->show();
}

void SnmpSimWindow::hideNoContainersRunningLabel() {
    noDevicesLabel->hide();
    devicesGroupBox->show();
}
