//
// Created by stachoz on 3/24/25.
//

#pragma once
#include <QWidget>

#include "DeviceStatus.h"

class DeviceWidget : public QWidget{
   Q_OBJECT
public:
   DeviceWidget(const QString& deviceName, const QString& ipAddress,QWidget *parent = 0);

private:
   DeviceStatus deviceStatus = DeviceStatus::GOOD;
};
