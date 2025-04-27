cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("client-server")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(client 
    src/client_main.cpp 
    src/Client.cpp 
    src/SocketManager.cpp
)

add_executable(data_processor 
    src/data_processor_main.cpp
    src/DataProcessor.cpp
    src/DataProcessorUtils.cpp
    src/SocketManager.cpp
)

add_executable(display_server 
    src/display_server_main.cpp 
    src/DisplayServer.cpp 
    src/SocketManager.cpp
)

add_executable(DataProcessorTests
    tests/DataProcessorTests.cpp
    src/DataProcessorUtils.cpp
    src/SocketManager.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(client ws2_32)
target_link_libraries(data_processor ws2_32)
target_link_libraries(display_server ws2_32)

target_link_libraries(DataProcessorTests 
    PRIVATE 
    ws2_32
    GTest::GTest 
)

enable_testing()
add_test(NAME DataProcessorTests COMMAND DataProcessorTests)