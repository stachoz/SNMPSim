//
// Created by stachoz on 3/11/25.
//
#pragma once

#include <qgridlayout.h>
#include <QLabel>
#include <QWidget>
#include <SnmpFrame.pb.h>

#include "gui/widgets/DeviceWidget.h"
#include "src/DeviceParam.h"
#include "src/DockerContainerLauncher.h"

namespace Ui { class SnmpSimWindow; }

class SnmpSimWindow : public QWidget {
    Q_OBJECT

public:
    explicit SnmpSimWindow(QWidget *parent = nullptr);
    ~SnmpSimWindow() override;
    void receiveNewSnmpFrame(const SnmpFrame& frame);
    void addNewDeviceWidget(DeviceWidget *newWidget);
private:
    Ui::SnmpSimWindow *ui;
    std::unique_ptr<DockerContainerLauncher> dockerLauncher = std::make_unique<DockerContainerLauncher>();
    std::unordered_map<std::string, std::vector<DeviceParam>> deviceParams {};
    std::vector<DeviceWidget*> deviceWidgets {};
    bool areContainersRunning {false};

    QGridLayout* devicesLayout = new QGridLayout();
    QLabel* noDevicesLabel = new QLabel("No running devices...");
    int rows = 0;
    int columns = 0;
};
