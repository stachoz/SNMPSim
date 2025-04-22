#include "DataReceiverApplication.h"


DataReceiverApplication::DataReceiverApplication(int &argc, char **argv) : QApplication(argc, argv) {
    connect(logic.get(), &DataReceiverLogic::newDeviceDataReceived, window.get(), &SnmpSimWindow::createNewDeviceWidget);
    connect(logic.get(), &DataReceiverLogic::noDataReceivedFromContainers, window.get(), &SnmpSimWindow::showNoContainersRunningLabel);
    connect(logic.get(), &DataReceiverLogic::dataReceiving, window.get(), &SnmpSimWindow::hideNoContainersRunningLabel);
    connect(logic.get(), &DataReceiverLogic::snmpFrameReceived, window.get(), &SnmpSimWindow::updateDeviceDetails);
    window->show();
}
