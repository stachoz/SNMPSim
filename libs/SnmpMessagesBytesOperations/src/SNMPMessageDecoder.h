//
// Created by stachoz on 11/30/24.
//

#pragma once

#include "SNMPConstants.h"
#include "SNMPMessage.h"
#include <variant>
#include <vector>
#include <qt6/QtCore/qbytearray.h>
#include <bits/ranges_algo.h>


class SNMPMessageDecoder {
public:
    static SNMPMessage decodeSNMPMessageBytes(QByteArray& messageBytes);
private:
    static void decodeMessageType(QByteArray &messageBytes);
    static void decodeVersion(QByteArray& messageBytes);
    static std::string decodeCommunityString(QByteArray& messageBytes);
    static void decodePdu(QByteArray& messageBytes);
    static uint16_t decodeRequestId(QByteArray &messageBytes);
    static int decodeError(QByteArray& messageBytes);
    static void decodeErrorIndex(QByteArray& messageBytes);
    static void decodeVarbindList(QByteArray& messageBytes);
    static void decodeVarbind(QByteArray& messageBytes);
    static std::vector<unsigned int> decodeOid(QByteArray& messageBytes);
    static void applyOidSpecialRule(QByteArray &messageBytes, std::vector<unsigned int> &oid);
    static std::optional<std::variant<int32_t, std::string>> decodeValue(QByteArray& messageBytes);
    static int decodeLength(QByteArray& messageBytes);
    static int decodeNumber(QByteArray& messageBytes, int length);
    static std::string decodeString(QByteArray& messageBytes, int length);
};
