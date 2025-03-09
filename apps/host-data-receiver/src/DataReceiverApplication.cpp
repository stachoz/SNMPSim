#include "DataReceiverApplication.h"

DataReceiverApplication::DataReceiverApplication(int &argc, char **argv): QApplication(argc, argv) {
    initSocket();
}

void DataReceiverApplication::processDatagram() const {
    while (updSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = updSocket->receiveDatagram();
        QByteArray data = datagram.data();
        SnmpFrame snmpFrame;
        if(snmpFrame.ParseFromArray(data.data(), data.size())) {
            std::cout << "Odebrano ramke: "
                    << "IP: " << snmpFrame.ip() << " ,"
                    << "RequestId: " << snmpFrame.requestid() << " ,"
                    << "Oid: " << snmpFrame.oid() << " ,"
                    << "Value: " << snmpFrame.value() << std::endl;
        }
        else {
            std::cout << "Błąd deserializacji ramki Protobuf";
        }
    }
}

void DataReceiverApplication::initSocket() {
    updSocket->bind(QHostAddress::AnyIPv4, 55555);
    connect(updSocket.get(), &QUdpSocket::readyRead, this, &DataReceiverApplication::processDatagram);
}
