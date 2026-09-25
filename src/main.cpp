#include <iostream>
#include <vector>
#include "../include/WinSocket.hpp"

int main() {
    WinSocket winSocket;
    winSocket.bindPort(5000);

    std::vector<uint8_t> buffer(2048);
    while (true){
        std::size_t size = winSocket.receive(buffer);
        for (std::size_t i = 0; i < size; i++){
            std::cout << buffer[i];
        }
    }
}