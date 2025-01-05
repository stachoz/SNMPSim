#include <gtest/gtest.h>

#include "snmp/SNMPMessageBuilder.h"

class SNMPMessageBuilderTest : public ::testing::Test {
protected:
    SNMPMessageBuilder  builder;

    void SetUp() override {
        builder = SNMPMessageBuilder();
    }
};

TEST_F(SNMPMessageBuilderTest, buildMessageWithOidSegmentOnMultpileBytes) {
    QByteArray expectedBytes = QByteArrayLiteral("\x30\x2c"
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

    SNMPMessage request;
    request.requestId = 1;
    request.communityString = "private";
    request.oid = {1, 3, 6, 1, 4, 1, 2680, 1, 2, 7, 3, 2, 0};

    auto result = builder.buildMessage(request);

    ASSERT_EQ(result, expectedBytes);
}

TEST_F(SNMPMessageBuilderTest, buildMessageWithOidSegementsOnSingleByte) {
    QByteArray expectedBytes = QByteArrayLiteral("\x30\x2B"
                                             "\x02\x01\x00"
                                             "\x04\x07\x70\x72\x69\x76\x61\x74\x65"
                                             "\xA0\x1d"
                                             "\x02\x01\x01"
                                             "\x02\x01\x00"
                                             "\x02\x01\x00"
                                             "\x30\x12"
                                             "\x30\x10"
                                             "\x06\x0c\x2b\x06\x01\x04\x01\x50\x01\x02\x07\x03\x02\x00"
                                             "\x05\x00");

    SNMPMessage request;
    request.requestId = 1;
    request.communityString = "private";
    request.oid = {1, 3, 6, 1, 4, 1, 80, 1, 2, 7, 3, 2, 0};

    auto result = builder.buildMessage(request);

    ASSERT_EQ(result, expectedBytes);
}

TEST_F(SNMPMessageBuilderTest, buildMessageWithMaxRequestId) {
    QByteArray expectedBytes = QByteArrayLiteral("\x30\x2C"
                                             "\x02\x01\x00"
                                             "\x04\x07\x70\x72\x69\x76\x61\x74\x65"
                                             "\xA0\x1e"
                                             "\x02\x02\xff\xff"
                                             "\x02\x01\x00"
                                             "\x02\x01\x00"
                                             "\x30\x12"
                                             "\x30\x10"
                                             "\x06\x0c\x2b\x06\x01\x04\x01\x50\x01\x02\x07\x03\x02\x00"
                                             "\x05\x00");
    SNMPMessage request;
    request.requestId = 0xffff;
    request.communityString = "private";
    request.oid = {1, 3, 6, 1, 4, 1, 80, 1, 2, 7, 3, 2, 0};

    auto result = builder.buildMessage(request);

    ASSERT_EQ(result, expectedBytes);
}