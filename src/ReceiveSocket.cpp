#include "ReceiveSocket.hpp"
#include "CallbackError.hpp"
#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>

int receiveSocket(ISocket& socket, int maxConsecutiveErrors, std::function<void(std::span<const std::uint8_t>)> callbackFunction){
    
    std::vector<std::uint8_t> buffer(2048);
    int consecutiveError = 0;
    while (true){
        try{
            std::size_t size = socket.receive(buffer);
            callbackFunction(std::span<const std::uint8_t>(buffer).first(size));
            consecutiveError = 0;
                
            }
            catch(const CallbackError& error){
                std::cerr << error.what();
                return 2;
            }
            catch(const std::runtime_error& error){
                std::cerr << error.what();
                consecutiveError++;
                if (consecutiveError > maxConsecutiveErrors){
                    std::cerr << "MAX_CONSECUTIVE_ERRORS reached, terminating program.\n";
                    return 1;
                }
            }
    }
    
}