//
// Created by stachoz on 12/1/24.
//


#include <gtest/gtest.h>

#include "snmp/SNMPMessageDecoder.h"

class SNMPMessageDecoderTest : public ::testing::Test {
protected:
    SNMPMessageDecoder decoder;

    void SetUp() override {
        decoder = SNMPMessageDecoder();
    }
};

TEST_F(SNMPMessageDecoderTest, decodeWithNullValue) {
    QByteArray bytesToDecode = QByteArrayLiteral("\x30\x2C"
                                             "\x02\x01\x00"
                                             "\x04\x07\x70\x72\x69\x76\x61\x74\x65"
                                             "\xA0\x1e"
                                             "\x02\x01\x01"
                                             "\x02\x01\x00"
                                             "\x02\x01\x00"
                                             "\x30\x13"
                                             "\x30\x11"
                                             "\x06\x0d\x2b\x06\x01\x04\x01\x94\x78\x01\x02\x07\x03\x02\x00"
                                             "\x05\x00");

    SNMPMessage message;
    message.communityString = "private";
    message.requestId = 1;
    message.oid = {1, 3, 6, 1, 4, 1, 2680, 1, 2, 7, 3, 2, 0};
    message.value = std::nullopt;


    auto result = decoder.decodeSNMPMessageBytes(bytesToDecode);

    ASSERT_EQ(message.communityString, result.communityString);
    ASSERT_EQ(message.requestId, result.requestId);
    ASSERT_EQ(message.oid, result.oid);
    ASSERT_EQ(message.value, result.value);
    ASSERT_EQ(bytesToDecode.isEmpty(), true);
}
