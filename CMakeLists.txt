cmake_minimum_required(VERSION 3.10)
project(InertialPointer)

# Standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(WIN32)

    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)

    target_sources(${PROJECT_NAME} PRIVATE src/windows/WinSocket.cpp src/windows/WinNetworkContext.cpp src/windows/WinSocketFactory.cpp
        src/windows/SocketFactoryProvider.cpp)

    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
    
    
else()
    message(FATAL_ERROR "NOT YET SUPPORTED")

    target_sources(${PROJECT_NAME} PRIVATE)
endif()

if(MSVC)
    # Microslop flags
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # GCC & Clang flags
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()