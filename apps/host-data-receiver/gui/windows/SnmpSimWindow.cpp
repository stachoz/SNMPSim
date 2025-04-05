//
// Created by stachoz on 3/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SnmpSimWindow.h" resolved

#include "SnmpSimWindow.h"

#include <iostream>

#include "ui_SnmpSimWindow.h"
#include "gui/widgets/DeviceWidget.h"
#include "src/DockerContainerLauncher.h"


SnmpSimWindow::SnmpSimWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::SnmpSimWindow) {
    ui->setupUi(this);
    // connect(ui->startButton, &QPushButton::clicked, dockerLauncher.get(), &DockerContainerLauncher::startDockerContainer);

    auto devicesLayout = new QGridLayout();
    devicesLayout->setContentsMargins(0, 0, 0, 0);
    devicesLayout->setHorizontalSpacing(5);
    devicesLayout->setVerticalSpacing(5);
    auto testDeviceWidget = new DeviceWidget("test", "1.1.1.1", this);
    auto testDeviceWidget1 = new DeviceWidget("test1", "1.1.1.1", this);
    auto testDeviceWidget2 = new DeviceWidget("test2", "1.1.1.1", this);
    auto testDeviceWidget3 = new DeviceWidget("test3", "1.1.1.1", this);
    auto testDeviceWidget4 = new DeviceWidget("test4", "1.1.1.1", this);
    auto testDeviceWidget5 = new DeviceWidget("test5", "1.1.1.1", this);
    devicesLayout->addWidget(testDeviceWidget, 0, 1);
    devicesLayout->addWidget(testDeviceWidget1, 0, 2);
    devicesLayout->addWidget(testDeviceWidget2, 0, 3);
    devicesLayout->addWidget(testDeviceWidget3, 1, 1);
    devicesLayout->addWidget(testDeviceWidget4, 1, 2);
    devicesLayout->addWidget(testDeviceWidget5, 1, 3);
    testDeviceWidget->show();

    devicesLayout->setRowStretch(0, 0);
    devicesLayout->setRowStretch(1, 0);

    ui->groupBox_devies->setLayout(devicesLayout);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}