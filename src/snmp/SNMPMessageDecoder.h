//
// Created by stachoz on 11/30/24.
//

#pragma once

#include <qbytearray.h>
#include <qdatastream.h>
#include <vector>

#include "data/SNMPMessage.h"


class SNMPMessageDecoder {
public:
    SNMPMessage decodeSNMPMessageBytes(QByteArray& messageBytes);

    void decodeMessageType(QByteArray &messageBytes);

    void decodeVersion(QByteArray& messageBytes);

    std::string decodeCommunityString(QByteArray& messageBytes);

    void decodePdu(QByteArray& messageBytes);

    uint16_t decodeRequestId(QByteArray &messageBytes);

    int decodeError(QByteArray& messageBytes);

    void decodeErrorIndex(QByteArray& messageBytes);

    void decodeVarbindList(QByteArray& messageBytes);

    void decodeVarbind(QByteArray& messageBytes);

    std::vector<unsigned int> decodeOid(QByteArray& messageBytes);

    void applyOidSpecialRule(QByteArray &messageBytes, std::vector<unsigned int> &oid);

    std::optional<int32_t> decodeValue(QByteArray& messageBytes);

    int decodeLength(QByteArray& messageBytes);

    int decodeNumber(QByteArray& messageBytes, int length);
};
