#include <iostream>
#include <vector>
#include <memory>

#include "SocketFactoryProvider.hpp"

int main() {
    try{
        std::unique_ptr<ISocketFactory> factory = SocketFactoryProvider::createSocketFactory();
        std::unique_ptr<ISocket> socket = factory->createSocket();
        socket->bindPort(5000);

        std::vector<std::uint8_t> buffer(2048);
        while (true){
            std::size_t size = socket->receive(buffer);
            for (std::size_t i = 0; i < size; i++){
                std::cout << buffer[i];
            }
        }
    }catch(const std::runtime_error& error){
        std::cerr << error.what();
        return 1;
    }
    
    
}