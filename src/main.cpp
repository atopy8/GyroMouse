#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "SocketFactoryProvider.hpp"

#define MAX_CONSECUTIVE_ERRORS 50


std::uint16_t parse_port(const int argc,const char* argv[]){
    //parse port, by default returns 5000, if error return 0, port should be in [1:65535]
    if (argc == 1)
        return 5000;

    if (argc != 2)
        return 0;

    try {
        std::size_t pos = 0;
        const int port = std::stoi(argv[1], &pos);

        if (pos != std::string(argv[1]).size())
            return 0;

        if (port < 1 || port > 65535)
            return 0;

        return static_cast<std::uint16_t>(port);
    }
    catch (const std::exception&) {
        return 0;
    }
}

int main(const int argc,const char* argv[]) {
    const std::uint16_t port = parse_port(argc, argv);
    if (port == 0){
        std::cerr << "Error parsing the port, usage : " << argv[0] << " <port(optionnal)>\n";
        return 1;
    }

    std::unique_ptr<ISocketFactory> factory;
    std::unique_ptr<ISocket> socket;
    std::vector<std::uint8_t> buffer(2048);

    try{
        factory = SocketFactoryProvider::createSocketFactory();
        socket = factory->createSocket();
        socket->bindPort(port);        
    }catch(const std::runtime_error& error){
        std::cerr << error.what();
        return 1;
    }
    
    int consecutiveError = 0; // if network problem, no busy loop
    while (true){
        try{

            std::size_t size = socket->receive(buffer);
            for (std::size_t i = 0; i < size; i++){
                std::cout << buffer[i];
            }
            consecutiveError = 0;
            
        }catch(const std::runtime_error& error){
            std::cerr << error.what();
            consecutiveError++;
            if (consecutiveError > MAX_CONSECUTIVE_ERRORS){
                std::cerr << "MAX_CONSECUTIVE_ERRORS reached, terminating program.\n";
                return 1;
            }
        }
    }
}