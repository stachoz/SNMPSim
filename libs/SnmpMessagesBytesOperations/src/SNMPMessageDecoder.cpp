//
// Created by stachoz on 11/30/24.
//

#include "SNMPMessageDecoder.h"


SNMPMessage SNMPMessageDecoder::decodeSNMPMessageBytes(QByteArray &messageBytes) {
    SNMPMessage message;

    decodeMessageType(messageBytes);
    decodeVersion(messageBytes);
    message.communityString = decodeCommunityString(messageBytes);
    decodePdu(messageBytes);
    message.requestId = decodeRequestId(messageBytes);

    // #TODO log error code
    int error = decodeError(messageBytes);

    decodeErrorIndex(messageBytes);
    decodeVarbindList(messageBytes);
    decodeVarbind(messageBytes);
    message.oid = decodeOid(messageBytes);
    message.value = decodeValue(messageBytes);

    return message;
}

void SNMPMessageDecoder::decodeMessageType(QByteArray& messageBytes) {
    messageBytes.remove(0, 1);
    decodeLength(messageBytes);
}

void SNMPMessageDecoder::decodeVersion(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    int length = decodeLength(messageBytes);
    decodeNumber(messageBytes, length);
}

std::string SNMPMessageDecoder::decodeCommunityString(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);

    int lengthValue = decodeLength(messageBytes);

    return decodeString(messageBytes, lengthValue);
}

void SNMPMessageDecoder::decodePdu(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    decodeLength(messageBytes);
}

uint16_t SNMPMessageDecoder::decodeRequestId(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    int length = decodeLength(messageBytes);
    return static_cast<uint16_t>(decodeNumber(messageBytes, length));
}

int SNMPMessageDecoder::decodeError(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    int length = decodeLength(messageBytes);
    return decodeNumber(messageBytes, length);
}

void SNMPMessageDecoder::decodeErrorIndex(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    int length = decodeLength(messageBytes);
    decodeNumber(messageBytes, length);
}

void SNMPMessageDecoder::decodeVarbindList(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    decodeLength(messageBytes);
}

void SNMPMessageDecoder::decodeVarbind(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    decodeLength(messageBytes);
}

std::vector<unsigned int> SNMPMessageDecoder::decodeOid(QByteArray &messageBytes) {
    messageBytes.remove(0, 1);
    int length = decodeLength(messageBytes);
    std::vector<unsigned int> oid {};

    bool isStoredOnMultipleBytes = false;
    int shiftNum = 1;

    for(int i = length - 1; i > 0; i--) {
        uint8_t byte = messageBytes.at(i);
        messageBytes.remove(i, 1);

        isStoredOnMultipleBytes = byte > SNMP::VALUE_BITS_MASK;

        if(isStoredOnMultipleBytes) {
            oid.back() += (byte & SNMP::VALUE_BITS_MASK) << (shiftNum++ * SNMP::VALUE_BITS_NUM);
        }
        else {
            oid.push_back(byte);
            shiftNum = 1;
        }
    }

    applyOidSpecialRule(messageBytes, oid);

    std::ranges::reverse(oid);

    return oid;
}

void SNMPMessageDecoder::applyOidSpecialRule(QByteArray& messageBytes, std::vector<unsigned int>& oid) {
    messageBytes.remove(0, 1);
    oid.push_back(3);
    oid.push_back(1);
}

std::optional<std::variant<int32_t, std::string>> SNMPMessageDecoder::decodeValue(QByteArray &messageBytes) {
    uint8_t type = messageBytes.at(0);
    messageBytes.remove(0, 1);

    if(type == SNMP::NULL_TYPE) {
        messageBytes.remove(0, 1);
        return std::nullopt;
    }

    int length = decodeLength(messageBytes);

    if(type == SNMP::OCTET_STRING_TYPE) {
        return decodeString(messageBytes, length);
    }

    return decodeNumber(messageBytes, length);
}

int SNMPMessageDecoder::decodeLength(QByteArray &messageBytes) {
    auto lengthSize = messageBytes.at(0);
    messageBytes.remove(0, 1);

    int lengthValue = 0;

    if(lengthSize > SNMP::VALUE_BITS_MASK) {
        lengthValue = lengthSize & SNMP::VALUE_BITS_MASK;
    }
    else {
        lengthValue = lengthSize;
    }

    return lengthValue;
}

int SNMPMessageDecoder::decodeNumber(QByteArray &messageBytes, int length) {
    int value = 0;

    for (int i = 0; i < length; ++i) {
        value = (value << 8) | static_cast<unsigned char>(messageBytes.at(i));
    }

    messageBytes.remove(0, length);

    return value;
}

std::string SNMPMessageDecoder::decodeString(QByteArray &messageBytes, int length) {
    std::string communityString;

    for(int i = 0; i < length; i++) {
        communityString.push_back(messageBytes.at(0));
        messageBytes.remove(0, 1);
    }

    return communityString;
}
