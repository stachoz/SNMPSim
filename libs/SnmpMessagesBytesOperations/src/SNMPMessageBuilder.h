//
// Created by stachoz on 11/16/24.
//

#pragma once

#include "SNMPMessage.h"
#include "SNMPConstants.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <variant>
#include <qt6/QtCore/qbytearray.h>
#include <qt6/QtCore/qdatastream.h>
#include <qt6/QtCore/qiodevice.h>


class SNMPMessageBuilder {
public:
    static QByteArray buildMessage(const SNMPMessage& requestData);

private:
    static void buildVersion(QByteArray &messageBytes);
    static void buildCommunityString(QByteArray &messageBytes, const std::string &communityString);
    static void buildPDU(QByteArray &messageBytes);
    static void buildRequestID(QByteArray &messageBytes, const uint16_t& requestId);
    static void buildError(QByteArray &messageBytes);
    static void buildErrorIndex(QByteArray &messageBytes);
    static void buildVarbindList(QByteArray &messageBytes);
    static void buildVarbind(QByteArray &messageBytes);
    static void buildOID(QByteArray &messageBytes, const std::vector<unsigned int> &oid);
    static void buildValue(QByteArray &messageBytes, const std::optional<std::variant<int32_t, std::string>> &value = std::nullopt);

    static QByteArray encodeOidSegmentToBytes(unsigned int num);
    static QByteArray encodeStringToBytes(const std::string &value);
};
