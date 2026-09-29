#include "windows/WinSocket.hpp"

#include <stdexcept>
#include <iostream>
#include <format>

WinSocket::WinSocket(std::shared_ptr<INetworkContext> context) : networkContext(context) {    
    allocatedSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (allocatedSocket == INVALID_SOCKET){
        throw std::runtime_error(std::format("Socket function failed with error {}", WSAGetLastError()));
    }

    localService.sin_family = AF_INET;
    localService.sin_addr.s_addr = INADDR_ANY;
}


// to steal
WinSocket::WinSocket(WinSocket &&other) noexcept {
    allocatedSocket = other.allocatedSocket;
    localService = other.localService;
    other.allocatedSocket = INVALID_SOCKET;
    networkContext = std::move(other.networkContext);
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
    localService = other.localService;
    other.allocatedSocket = INVALID_SOCKET;
    networkContext = std::move(other.networkContext);
    return *this;
}

void WinSocket::bindPort(const std::uint16_t port){
    localService.sin_port = htons(port);
    
    int result = bind(allocatedSocket, reinterpret_cast<SOCKADDR *>(&localService), sizeof(localService));
    if (result != 0) {
        throw std::runtime_error(std::format("bind function failed with error {}", WSAGetLastError()));
    }
}

std::size_t WinSocket::receive(std::span<std::uint8_t> buffer){
    sockaddr_in clientService = {};
    int clientServiceSize = static_cast<int>(sizeof(clientService));
    
    int result = recvfrom(allocatedSocket, reinterpret_cast<char *>(buffer.data()), static_cast<int>(buffer.size()), 0, reinterpret_cast<SOCKADDR *>(&clientService), &clientServiceSize);
    if (result == SOCKET_ERROR) {
        throw std::runtime_error(std::format("recvfrom function failed with error {}", WSAGetLastError()));
    }
    return static_cast<std::size_t>(result);
}        

WinSocket::~WinSocket(){
    if (allocatedSocket != INVALID_SOCKET){
        int result = closesocket(allocatedSocket);
        if (result == SOCKET_ERROR) {
            std::cerr << "closesocket function failed with error " << WSAGetLastError();
        }
    }
}