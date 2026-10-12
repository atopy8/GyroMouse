#include "SocketFactoryProvider.hpp"
#include "windows/WinSocketFactory.hpp"


std::unique_ptr<ISocketFactory> SocketFactoryProvider::createSocketFactory(){
    // point in the code where it knows which implementation will be used. allows main function or users of the factory to use it unknowingly of the platform.
    return std::make_unique<WinSocketFactory>();
}