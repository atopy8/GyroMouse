#include "windows/WinNetworkContext.hpp"


#include <stdexcept>
#include <iostream>
#include <format>

WinNetworkContext::WinNetworkContext() {
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
        throw std::runtime_error(std::format("Failed to execute WSAStartup with error {}", err));
    }
}


WinNetworkContext::~WinNetworkContext(){
    WSACleanup();
}

