//
// Created by stachoz on 3/24/25.
//

#pragma once
#include <QPushButton>
#include <QWidget>

#include "DeviceStatus.h"

class DeviceWidget : public QWidget{
   Q_OBJECT
public:
   DeviceWidget(const QString& deviceName, const QString& ipAddress,QWidget *parent = 0);
signals:
   void sigShowDeviceDetails(const QString& ipAddress);

private:
   QString name;
   QString ip;
   DeviceStatus deviceStatus = DeviceStatus::GOOD;
   QPushButton* viewDetailsButton = new QPushButton("View details");
};
