add_library(SNMPBytesOperationLib STATIC
        src/SNMPMessageDecoder.cpp
        src/SNMPMessageDecoder.h
        src/SNMPMessageBuilder.cpp
        src/SNMPMessageBuilder.h
        src/SNMPConstants.h
        src/SNMPMessage.h
)

target_include_directories(SNMPBytesOperationLib PUBLIC src)
target_link_libraries(SNMPBytesOperationLib PRIVATE Qt6::Core Qt6::Widgets Qt6::Network)
