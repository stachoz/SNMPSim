//
// Created by stachoz on 3/24/25.
//

#include "DeviceWidget.h"



DeviceWidget::DeviceWidget(const QString &deviceName, const QString &ipAddress,
                           QWidget *parent) : name(deviceName), ip(ipAddress), QWidget(parent) {

    connect(viewDetailsButton, &QPushButton::clicked, this, [this]() {
        emit sigShowDeviceDetails(ip);
    });

    frame->setFixedSize(200, 150);
    frame->setStyleSheet(
      "QGroupBox {"
        "   border-radius: 10px; "
        "   border: 2px solid #4C4C4C;"
        "   padding: 5px;"
        "}"
    );

    QLabel *nameLabel = new QLabel("<b>Device name:</b> " + deviceName);
    QLabel *ipLabel = new QLabel("<b>IP Address:</b> " + ipAddress);

    nameLabel->setStyleSheet("margin-bottom: 5px;");
    ipLabel->setStyleSheet("margin-bottom: 5px;");
    statusLabel->setStyleSheet("margin-bottom: 5px;");
    viewDetailsButton->setStyleSheet("margin-bottom: 5px; font-weight: bold; padding: 5px;");

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

void DeviceWidget::setDeviceStatus(DeviceStatus deviceStatus) {
    std::string color;
    std::string text = "<b>Status: " ;
    switch (deviceStatus) {
        case DeviceStatus::GOOD:
            color = "#50c878;";
            text += "GOOD</b>";
            break;
        case DeviceStatus::NON_ACTIVE:
            color = "#4C4C4C;";
            break;
        case DeviceStatus::WARNING:
            color = "orange;";
            break;
        case DeviceStatus::DANGER:
            color = "red;";
            text += "ERROR</b>";
            break;
    }

    std::stringstream frameStyleSheet;
    frameStyleSheet <<
        "QGroupBox {"
        "   border-radius: 10px;"
        "   border: 2px solid " << color << ";"
        "   padding: 5px;"
        "}";

    std::stringstream statusLabelStyleSheet;
    statusLabelStyleSheet <<
        "margin-bottom: 5px;"
        "color:" << color << ";";

    statusLabel->setText(text.c_str());
    statusLabel->setStyleSheet(statusLabelStyleSheet.str().c_str());
    frame->setStyleSheet(frameStyleSheet.str().c_str());
    update();
}

std::string DeviceWidget::getIp() const {
    return ip.toStdString();
}
