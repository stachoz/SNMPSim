//
// Created by stachoz on 3/24/25.
//

#include "DeviceWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>

DeviceWidget::DeviceWidget(const QString &deviceName, const QString &ipAddress,
                            QWidget *parent) : name(deviceName), ip(ipAddress), QWidget(parent) {

    connect(viewDetailsButton, &QPushButton::clicked, this, [this]() {
        emit sigShowDeviceDetails(ip);
    });


    auto* frame = new QGroupBox(this);
    frame->setFixedSize(220, 150);
    frame->setStyleSheet(
      "QGroupBox {"
        "   border-radius: 10px; "
        "   border: 2px solid #4C4C4C;"
        "   padding: 5px;"
        "}"
    );

    QLabel *nameLabel = new QLabel("<b>Device name:</b> " + deviceName);
    QLabel *ipLabel = new QLabel("<b>IP Address:</b> " + ipAddress);
    QLabel *statusLabel = new QLabel("<b>Status:</b> good");

    nameLabel->setStyleSheet("margin-bottom: 5px;");
    ipLabel->setStyleSheet("margin-bottom: 5px;");
    statusLabel->setStyleSheet("margin-bottom: 5px;");
    viewDetailsButton->setStyleSheet("margin-bottom: 5px; font-weight: bold; padding: 5px;");


    switch (deviceStatus) {
        case DeviceStatus::GOOD:
            statusLabel->setStyleSheet("color: #50c878;");
            break;
        case DeviceStatus::NON_ACTIVE:
            statusLabel->setStyleSheet("color: gray;");
            break;
        case DeviceStatus::WARNING:
            statusLabel->setStyleSheet("color: orange;");
            break;
        case DeviceStatus::DANGER:
            statusLabel->setStyleSheet("color: red;");
            break;
    }

    auto layout = new QVBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(ipLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(viewDetailsButton, 0, Qt::AlignCenter);
    layout->addStretch();

    frame->setLayout(layout);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(frame, 0, Qt::AlignCenter);
    setLayout(mainLayout);
}
