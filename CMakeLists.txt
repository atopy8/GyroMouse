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
        src/windows/SocketFactoryProvider.cpp src/Utils.cpp src/ReceiveSocket.cpp)

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


option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    include(CTest)
    include(GoogleTest)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        063de7e9578f82b369302001269680b4b1553359 # release-1.18.0
    )
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(googletest)


    add_executable(testSocketInterface tests/interface/testSocketInterface.cpp src/ReceiveSocket.cpp)
    target_include_directories(testSocketInterface PRIVATE include tests/mocks)
    target_link_libraries(testSocketInterface PRIVATE GTest::gtest_main GTest::gmock)

    add_executable(testUtils tests/utils/testUtils.cpp src/Utils.cpp)
    target_include_directories(testUtils PRIVATE include)
    target_link_libraries(testUtils PRIVATE GTest::gtest_main)



    gtest_discover_tests(testSocketInterface)
    gtest_discover_tests(testUtils)

endif()
