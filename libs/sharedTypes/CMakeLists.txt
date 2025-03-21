add_library(SharedTypesLib STATIC
    src/Device.h
        src/Device.cpp
)

target_include_directories(SNMPBytesOperationLib PUBLIC src)