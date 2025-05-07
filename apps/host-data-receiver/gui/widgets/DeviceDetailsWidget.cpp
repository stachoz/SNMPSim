//
// Created by stachoz on 4/13/25.
//

#include "DeviceDetailsWidget.h"

DeviceDetailsWidget::DeviceDetailsWidget(const QString& deviceName, const QString& ipAddress, QWidget* parent)
    :  QWidget(parent) {
    deviceNameLabel = new QLabel("<b>Device:</b> " + deviceName);
    ipAddressLabel = new QLabel("<b>IP:</b> " + ipAddress);
    setupUI();
}

void DeviceDetailsWidget::setupUI() {
    paramsTable = new QTableWidget(this);
    paramsTable->setColumnCount(3);
    paramsTable->setHorizontalHeaderLabels({"Parameter", "OID", "Value"});
    paramsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    paramsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    paramsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    backButton = new QPushButton("Back to Devices", this);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit backToDevicesRequested();
    });

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(deviceNameLabel);
    layout->addWidget(ipAddressLabel);
    layout->addWidget(paramsTable);
    layout->addWidget(backButton, 0, Qt::AlignRight);

    setBaseSize(600, 500);
    setLayout(layout);
    setWindowTitle("Device Details");
}

void DeviceDetailsWidget::updateParameters(const std::vector<DeviceParam>& params) {
    paramsTable->setRowCount(params.size());

    for (int i = 0; i < params.size(); ++i) {
        const auto& param = params[i];
        paramsTable->setItem(i, 0, new QTableWidgetItem(param.paramName.c_str()));
        paramsTable->setItem(i, 1, new QTableWidgetItem(param.oid.c_str()));
        paramsTable->setItem(i, 2, new QTableWidgetItem(std::to_string(param.value).c_str()));
    }
}

void DeviceDetailsWidget::updateParameter(const DeviceParam& param) {
    QColor color = param.isValid ? QColor("#228B22") : QColor("#560319");
    for (int i = 0; i < paramsTable->rowCount(); ++i) {
        if (paramsTable->item(i, 1)->text() == param.oid.c_str()) {
            paramsTable->item(i, 2)->setText(std::to_string(param.value).c_str());
            paramsTable->item(i, 2)->setBackground(color);
            return;
        }
    }

    int newRow = paramsTable->rowCount();
    paramsTable->insertRow(newRow);
    paramsTable->setItem(newRow, 0, new QTableWidgetItem(param.paramName.c_str()));
    paramsTable->setItem(newRow, 1, new QTableWidgetItem(param.oid.c_str()));
    paramsTable->setItem(newRow, 2, new QTableWidgetItem(std::to_string(param.value).c_str()));
}
