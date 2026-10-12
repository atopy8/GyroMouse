#pragma once

#include <span>
#include <cstdint>

/**
 * @class ISocket
 * @brief Interface defining the base contract for network connections. 
 * @details This abstract class serves as a abstraction layer independant of the platform. 
 * It allows the rest of the application to use sockets without worrying of the underlying implementation linked to the OS (Winsock on win32 and posix on linux).
 */
class ISocket {
    public:
        /**
         * @brief Receiving function of the socket. Fill the buffer and returns number of elements written. Waiting for a packet, can be blocking 
         * @param buffer writing the new elements received in a buffer.
         * @return Returns size of the added elements.
         * @throw std::runtime_error if Connection not set or connexion error. a return 0 is acceptable and shouldn't be taken as an error.
         */
        virtual std::size_t receive(std::span<std::uint8_t> buffer) = 0;
        
        /**
         * @brief Bind function of the socket. When called, tries to bind a connection to a port.
         * @param port port number
         * @throw std::runtime_error if Connection not set or connexion error
         */
        virtual void bindPort(const std::uint16_t port) = 0;

        /**
         * @brief Destroy function of the socket.
         */
        virtual ~ISocket() = default;
};