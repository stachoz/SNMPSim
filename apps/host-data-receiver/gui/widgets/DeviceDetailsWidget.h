//
// Created by stachoz on 4/13/25.
//

// DeviceDetailsWidget.h
#pragma once

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTimer>
#include <vector>
#include "src/DeviceParam.h"

class DeviceDetailsWidget : public QWidget {
    Q_OBJECT
public:
    explicit DeviceDetailsWidget(const QString& deviceName, const QString& ipAddress, QWidget* parent = nullptr);
    void updateParameters(const std::vector<DeviceParam>& params);
    void updateParameter(const DeviceParam& param);
signals:
    void backToDevicesRequested();

private:
    QLabel* deviceNameLabel;
    QLabel* ipAddressLabel;
    QTableWidget* paramsTable;
    QPushButton* backButton;
    QTimer updateTimer;
    int updateInterval = 2'000;

    void setupUI();
};