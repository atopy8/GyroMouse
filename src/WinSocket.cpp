#include "../include/WinSocket.hpp"

#include <stdexcept>
#include <iostream>
#include <format>

WinSocket::WinSocket() {
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err != 0) {
        throw std::runtime_error(std::format("Failed to execute WSAStartup with error {}", err));
    }
    
    allocatedSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (allocatedSocket == INVALID_SOCKET){
        throw std::runtime_error(std::format("Socket function failed with error {}", WSAGetLastError()));
    }

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
}


// to steal
WinSocket::WinSocket(WinSocket &&other) noexcept {
    allocatedSocket = other.allocatedSocket;
    other.allocatedSocket = INVALID_SOCKET;
}

WinSocket &WinSocket::operator=(WinSocket &&other) noexcept {
    if (this == &other)
        return *this;
        
    if (allocatedSocket != INVALID_SOCKET){
        int result = closesocket(allocatedSocket);
        if (result == SOCKET_ERROR) {
            std::cerr << "closesocket function failed with error " << WSAGetLastError();
        }
    }
    allocatedSocket = other.allocatedSocket;
    other.allocatedSocket = INVALID_SOCKET;
    return *this;
}; 

void WinSocket::bindPort(const std::uint16_t port){
    service.sin_port = htons(port);
    int result = bind(allocatedSocket, (SOCKADDR *)&service, sizeof(service));
    if (result != 0) {
        throw std::runtime_error(std::format("bind function failed with error {}", WSAGetLastError()));
    }
};

std::size_t WinSocket::receive(std::span<std::uint8_t> buffer){
    int serviceSize = (int)sizeof(service);
    int result = recvfrom(allocatedSocket, reinterpret_cast<char *>(buffer.data()), static_cast<int>(buffer.size()), 0, (SOCKADDR *)&service, &serviceSize);
    if (result == SOCKET_ERROR) {
        throw std::runtime_error(std::format("recvfrom function failed with error {}", WSAGetLastError()));
    }
    return result;
}        

WinSocket::~WinSocket(){
    if (allocatedSocket != INVALID_SOCKET){
        int result = closesocket(allocatedSocket);
        if (result == SOCKET_ERROR) {
            std::cerr << "closesocket function failed with error " << WSAGetLastError();
        }
        WSACleanup();
    }
};