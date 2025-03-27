//
// Created by stachoz on 3/24/25.
//

#include "DeviceWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>

DeviceWidget::DeviceWidget(const QString &deviceName, const QString &ipAddress
                           , QWidget *parent) : QWidget(parent) {
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
    QPushButton* viewDetailsButton = new QPushButton("View details");

    nameLabel->setStyleSheet("margin-bottom: 5px;");
    ipLabel->setStyleSheet("margin-bottom: 5px;");
    statusLabel->setStyleSheet("margin-bottom: 5px;");
    viewDetailsButton->setStyleSheet("margin-bottom: 5px; font-weight: bold; padding: 5px;");


    switch (deviceStatus) {
        case DeviceStatus::GOOD:
            statusLabel->setStyleSheet("color: green;");
        case DeviceStatus::NON_ACTIVE:
            statusLabel->setStyleSheet("color: gray;");
        case DeviceStatus::WARNING:
            statusLabel->setStyleSheet("color: orange;");
        case DeviceStatus::DANGER:
            statusLabel->setStyleSheet("color: red;");

    }

    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->addWidget(nameLabel);
    layout->addWidget(ipLabel);
    layout->addWidget(statusLabel);
    layout->addWidget(viewDetailsButton, 0, Qt::AlignCenter);
    layout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(frame, 0, Qt::AlignCenter);
    setLayout(layout);
}
