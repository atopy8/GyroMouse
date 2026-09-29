#include "windows/WinSocketFactory.hpp"
#include "windows/WinSocket.hpp"

#include <memory>

WinSocketFactory::WinSocketFactory() {
    networkContext = std::make_shared<WinNetworkContext>();
}

std::unique_ptr<ISocket> WinSocketFactory::createSocket(){
    return std::make_unique<WinSocket>(networkContext);
}

WinSocketFactory::~WinSocketFactory() {
}