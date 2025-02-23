enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(SNMPSimTests
        SNMPMessageBuilderTest.cpp
        SNMPMessageDecoderTest.cpp
)

target_include_directories(SNMPSimTests PRIVATE ${CMAKE_SOURCE_DIR}/snmp-server)

target_link_libraries(SNMPSimTests PRIVATE
        gtest
        gtest_main
        SnmpSimLib
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

gtest_discover_tests(SNMPSimTests)

