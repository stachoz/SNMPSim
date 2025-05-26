//
// Created by stachoz on 3/11/25.
//
#pragma once

#include <qgridlayout.h>
#include <QGroupBox>
#include <QLabel>
#include <qstackedlayout.h>
#include <QTimer>
#include <QWidget>
#include <SnmpFrame.pb.h>
#include "gui/widgets/DeviceDetailsWidget.h"
#include "gui/widgets/DeviceWidget.h"
#include "gui/widgets/FlowLayout.h"
#include "src/DeviceParam.h"
#include "src/DockerContainerLauncher.h"
#include <QLabel>
#include "ui_SnmpSimWindow.h"
#include "gui/widgets/DeviceWidget.h"
#include "src/DockerContainerLauncher.h"

namespace Ui { class SnmpSimWindow; }

class SnmpSimWindow : public QWidget {
    Q_OBJECT

public:
    explicit SnmpSimWindow(bool isTest, std::string containersConfigPath, QWidget *parent = nullptr);
    ~SnmpSimWindow() override;

    void createNewDeviceWidget(std::string_view ip, std::string_view deviceName);
public slots:
    void showNoContainersRunningLabel();
    void hideNoContainersRunningLabel();

    void updateDeviceStatus(std::string_view ip, DeviceStatus status);

    void updateDeviceDetails(const SnmpFrame &frame);

private slots:
    void showDeviceDetails(const QString& deviceName);
    void hideDeviceDetails();


private:
    Ui::SnmpSimWindow *ui;
    std::unique_ptr<DockerContainerLauncher> dockerLauncher;
    std::vector<DeviceWidget*> deviceWidgets {};
    QMap<QString, DeviceDetailsWidget*> deviceDetailsWidgets {};
    std::string shownDeviceDetailsIp;

    QLabel* noDevicesLabel = new QLabel("No running devices...");
    QVBoxLayout* detailsLayout = new QVBoxLayout();
    FlowLayout* devicesLayout = new FlowLayout();
    QStackedLayout* mainStackedLayout = new QStackedLayout();
    QWidget* devicesPage = new QWidget();
    QWidget* detailsPage = new QWidget();
    QWidget* noDevicesPage = new QWidget();
};