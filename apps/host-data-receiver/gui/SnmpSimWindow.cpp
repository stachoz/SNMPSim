//
// Created by stachoz on 3/11/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SnmpSimWindow.h" resolved

#include "SnmpSimWindow.h"

#include <iostream>

#include "ui_SnmpSimWindow.h"
#include "src/DockerContainerLauncher.h"


SnmpSimWindow::SnmpSimWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::SnmpSimWindow) {
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, dockerLauncher.get(), &DockerContainerLauncher::startDockerContainer);
}

SnmpSimWindow::~SnmpSimWindow() {
    delete ui;
}