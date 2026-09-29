#include "SocketFactoryProvider.hpp"
#include "windows/WinSocketFactory.hpp"

std::unique_ptr<ISocketFactory> SocketFactoryProvider::createSocketFactory(){
    return std::make_unique<WinSocketFactory>();
}