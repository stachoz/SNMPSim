//
// Created by stachoz on 3/24/25.
//

#pragma once
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "DeviceStatus.h"

class DeviceWidget : public QWidget{
   Q_OBJECT
public:
   DeviceWidget(const QString& deviceName, const QString& ipAddress,QWidget *parent = 0);
   void setDeviceStatus(DeviceStatus deviceStatus);
   std::string getIp() const;

signals:
   void sigShowDeviceDetails(const QString& ipAddress);

private:
   QString name;
   QString ip;
   DeviceStatus deviceStatus = DeviceStatus::GOOD;
   QPushButton* viewDetailsButton = new QPushButton("View details");
   QLabel *statusLabel = new QLabel("<b>Status:</b> good");
   QGroupBox* frame = new QGroupBox(this);
};
