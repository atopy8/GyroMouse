#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "SocketFactoryProvider.hpp"
#include "Utils.hpp"
#include "ReceiveSocket.hpp"

#define MAX_CONSECUTIVE_ERRORS 50

int main(const int argc,const char* argv[]) {
    const std::uint16_t port = parse_port(argc, argv);
    if (port == 0){
        std::cerr << "Error parsing the port, usage : " << argv[0] << " <port(optionnal)>\n";
        return 1;
    }

    std::unique_ptr<ISocketFactory> factory;
    std::unique_ptr<ISocket> socket;

    try{
        factory = SocketFactoryProvider::createSocketFactory();
        socket = factory->createSocket();
        socket->bindPort(port);        
    }catch(const std::runtime_error& error){
        std::cerr << error.what();
        return 1;
    }

    std::function<void(std::span <const std::uint8_t>)> callbackFunction = [](std::span<const std::uint8_t> buffer){
        for (std::uint8_t byte : buffer)
        {
            std::cout << byte;
        }
    };
    return receiveSocket(*socket, MAX_CONSECUTIVE_ERRORS, callbackFunction);
}