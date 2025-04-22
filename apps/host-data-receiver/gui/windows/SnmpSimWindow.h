//
// Created by stachoz on 3/11/25.
//
#pragma once

#include <qgridlayout.h>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <SnmpFrame.pb.h>

#include "gui/widgets/DeviceDetailsWidget.h"
#include "gui/widgets/DeviceWidget.h"
#include "src/DeviceParam.h"
#include "src/DockerContainerLauncher.h"

namespace Ui { class SnmpSimWindow; }

class SnmpSimWindow : public QWidget {
    Q_OBJECT

public:
    explicit SnmpSimWindow(QWidget *parent = nullptr);
    ~SnmpSimWindow() override;

    void createNewDeviceWidget(std::string_view ip, std::string_view deviceName);
public slots:
    void showNoContainersRunningLabel();
    void hideNoContainersRunningLabel();
    void updateDeviceDetails(const SnmpFrame &frame);

private slots:
    void showDeviceDetails(const QString& deviceName);
    void hideDeviceDetails();


private:
    Ui::SnmpSimWindow *ui;
    std::unique_ptr<DockerContainerLauncher> dockerLauncher = std::make_unique<DockerContainerLauncher>();
    std::vector<DeviceWidget*> deviceWidgets {};
    QMap<QString, DeviceDetailsWidget*> deviceDetailsWidgets {};
    std::string shownDeviceDetailsIp;

    QLabel* noDevicesLabel = new QLabel("No running devices...");
    QGridLayout* devicesLayout = new QGridLayout();
    QGroupBox* devicesGroupBox = new QGroupBox();

    int rows = 0;
    int columns = 0;
};