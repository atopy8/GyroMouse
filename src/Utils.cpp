#include <string>

#include "Utils.hpp"

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
