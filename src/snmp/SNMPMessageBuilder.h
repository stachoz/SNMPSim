//
// Created by stachoz on 11/16/24.
//

#pragma once
#include <qbytearray.h>

#include "data/SNMPMessage.h"

class SNMPMessageBuilder {
public:
    QByteArray buildMessage(const SNMPMessage& requestData) const;

private:
    void buildVersion(QByteArray &messageBytes) const;
    void buildCommunityString(QByteArray &messageBytes, const std::string &communityString) const;
    void buildPDU(QByteArray &messageBytes) const;
    void buildRequestID(QByteArray &messageBytes, const uint16_t& requestId) const;
    void buildError(QByteArray &messageBytes) const;
    void buildErrorIndex(QByteArray &messageBytes) const;
    void buildVarbindList(QByteArray &messageBytes) const;
    void buildVarbind(QByteArray &messageBytes) const;
    void buildOID(QByteArray &messageBytes, const std::vector<unsigned int> &oid) const;
    void buildValue(QByteArray &messageBytes, const std::optional<int8_t> &value = std::nullopt) const;
    QByteArray encodeOidSegmentToBytes(unsigned int num) const ;
};
