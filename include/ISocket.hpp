#pragma once

#include <span>
#include <cstdint>

class ISocket {
    public:
        /**
         * @brief Receiving function of the socket. When called, returns next span of the receiving buffer.
         * @param buffer writing the new elements received in a buffer.
         * @return Returns size of the added elements.
         * @throw std::runtime_error if Connection not set or connexion error
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