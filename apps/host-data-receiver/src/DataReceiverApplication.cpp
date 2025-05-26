#include "DataReceiverApplication.h"

DataReceiverApplication::DataReceiverApplication(int &argc, char **argv) : QApplication(argc, argv) {

    bool isTestMode = false;
    QString containersConfigPath;

    if (argc == 3 && QString(argv[1]).compare("TEST", Qt::CaseInsensitive) == 0) {
        isTestMode = true;
        containersConfigPath = QString(argv[2]);
        std::cout << "Tryb testowy włączony. Ścieżka do pliku: " << containersConfigPath.toStdString() << std::endl;
    }

    window = std::make_unique<SnmpSimWindow>(isTestMode, containersConfigPath.toStdString());

    connect(logic.get(), &DataReceiverLogic::newDeviceDataReceived, window.get(), &SnmpSimWindow::createNewDeviceWidget);
    connect(logic.get(), &DataReceiverLogic::noDataReceivedFromContainers, window.get(), &SnmpSimWindow::showNoContainersRunningLabel);
    connect(logic.get(), &DataReceiverLogic::dataReceiving, window.get(), &SnmpSimWindow::hideNoContainersRunningLabel);
    connect(logic.get(), &DataReceiverLogic::snmpFrameReceived, window.get(), &SnmpSimWindow::updateDeviceDetails);
    connect(logic.get(), &DataReceiverLogic::deviceStatusChange, window.get(), &SnmpSimWindow::updateDeviceStatus);
    window->show();
}
