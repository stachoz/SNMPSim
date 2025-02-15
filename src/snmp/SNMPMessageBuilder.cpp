//
// Created by stachoz on 11/16/24.
//

// https://www.ranecommercial.com/legacy/note161.html


#include "SNMPMessageBuilder.h"

#include <iostream>
#include <qdatastream.h>
#include <qiodevice.h>
#include <vector>

#include "data/SNMPConstants.h"
#include "data/SNMPMessage.h"

QByteArray SNMPMessageBuilder::buildMessage(const SNMPMessage& requestData) const {
    QByteArray messageBytes;

    buildValue(messageBytes, requestData.value);
    buildOID(messageBytes, requestData.oid);
    buildVarbind(messageBytes);
    buildVarbindList(messageBytes);
    buildErrorIndex(messageBytes);
    buildError(messageBytes);
    buildRequestID(messageBytes, requestData.requestId);
    buildPDU(messageBytes);
    buildCommunityString(messageBytes, requestData.communityString);
    buildVersion(messageBytes);

    messageBytes.push_back(static_cast<char>(messageBytes.size()));
    messageBytes.push_back(SNMP::SEQUENCE_TYPE);

    std::reverse(std::begin(messageBytes), std::end(messageBytes));

    return messageBytes;
}

void SNMPMessageBuilder::buildVersion(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(SNMP::SNMP_V2));
    messageBytes.push_back(0x01);
    messageBytes.push_back(SNMP::INTEGER_TYPE);
}

void SNMPMessageBuilder::buildCommunityString(QByteArray& messageBytes, const std::string& communityString) const {
    messageBytes.push_back(encodeStringToBytes(communityString));
    messageBytes.push_back(static_cast<char>(communityString.size()));
    messageBytes.push_back(SNMP::OCTET_STRING_TYPE);
}

void SNMPMessageBuilder::buildPDU(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(messageBytes.size()));
    messageBytes.push_back(SNMP::GET_REQUEST_TYPE);
}

void SNMPMessageBuilder::buildRequestID(QByteArray& messageBytes, const uint16_t& requestId) const {
    QByteArray encodedRequestId;

    QDataStream stream(&encodedRequestId, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << requestId;

    auto lastIndex = encodedRequestId.size() - 1;

    if(encodedRequestId.at(lastIndex) == 0x00) {
        encodedRequestId.remove(lastIndex, 1);
    }

    messageBytes.push_back(encodedRequestId);

    messageBytes.push_back(static_cast<char>(encodedRequestId.size()));
    messageBytes.push_back(SNMP::INTEGER_TYPE);
}

void SNMPMessageBuilder::buildError(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(0x00));
    messageBytes.push_back(0x01);
    messageBytes.push_back(SNMP::INTEGER_TYPE);
}

void SNMPMessageBuilder::buildErrorIndex(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(0x00));
    messageBytes.push_back(0x01);
    messageBytes.push_back(SNMP::INTEGER_TYPE);
}

void SNMPMessageBuilder::buildVarbindList(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(messageBytes.size()));
    messageBytes.push_back(SNMP::SEQUENCE_TYPE);
}

void SNMPMessageBuilder::buildVarbind(QByteArray& messageBytes) const {
    messageBytes.push_back(static_cast<char>(messageBytes.size()));
    messageBytes.push_back(SNMP::SEQUENCE_TYPE);
}

void SNMPMessageBuilder::buildOID(QByteArray &messageBytes, const std::vector<unsigned int>& oid) const {
    if(oid.size() <= 2) throw std::runtime_error("Invalid size of OID: " + oid.size());

    QByteArray encodedOid;

    std::for_each(oid.rbegin(), oid.rend() - 2, [&encodedOid, this](const unsigned int& oidNum) {
        encodedOid.push_back(encodeOidSegmentToBytes(oidNum));
    });

    encodedOid.push_back(SNMP::OID_BEGINNING);

    messageBytes.push_back(encodedOid);
    messageBytes.push_back(static_cast<char>(encodedOid.size()));
    messageBytes.push_back(SNMP::OID_TYPE);
}

void SNMPMessageBuilder::buildValue(QByteArray &messageBytes,
    const std::optional<std::variant<int32_t, std::string>> &value) const {
         messageBytes.push_back(static_cast<char>(0x00));
         messageBytes.push_back(SNMP::NULL_TYPE);
}

QByteArray SNMPMessageBuilder::encodeOidSegmentToBytes(unsigned int num) const {
    QByteArray result;
    uint8_t segment = 0;

    do {
        segment = num & SNMP::VALUE_BITS_MASK;
        if(!result.isEmpty()) segment |= SNMP::FIRST_BIT_SET_MASK;
        result.push_back(static_cast<char>(segment));
        num >>= SNMP::VALUE_BITS_NUM;
    } while(num > 0);

    return result;
}

QByteArray SNMPMessageBuilder::encodeStringToBytes(const std::string& value) const {
    QByteArray stringBytes;

    std::for_each(std::rbegin(value), std::rend(value), [&stringBytes](auto& c) {
        stringBytes.push_back(c);
    });

    return stringBytes;
}