cmake_minimum_required(VERSION 3.10)
project(InertialPointer)

# Standard C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp
    src/WinSocket.cpp)

if(MSVC)
    # Microslop flags
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # GCC & Clang flags
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

target_link_libraries(${PROJECT_NAME} ws2_32)