cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("kaspersky-task")
include_directories(include)

add_executable(client 
    src/client_main.cpp 
    src/Client.cpp 
    src/NetworkBase.cpp
)

add_executable(data_processor 
    src/data_processor_main.cpp 
    src/DataProcessor.cpp 
    src/NetworkBase.cpp
)

add_executable(display_server 
    src/display_server_main.cpp 
    src/DisplayServer.cpp 
    src/NetworkBase.cpp
)


target_link_libraries(client ws2_32)
target_link_libraries(data_processor ws2_32)
target_link_libraries(display_server ws2_32)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET client PROPERTY CXX_STANDARD 20)
  set_property(TARGET data_processor PROPERTY CXX_STANDARD 20)
  set_property(TARGET display_server PROPERTY CXX_STANDARD 20)
endif()

