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

target_link_libraries(SNMPSimTests
        gtest
        gtest_main
        snmp
)

target_include_directories(SNMPSimTests PRIVATE ${PROJECT_SOURCE_DIR}/src)

gtest_discover_tests(SNMPSimTests)

