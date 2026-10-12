#pragma once

 
#include <WinSock2.h>
#include <memory>

#include "interface/ISocket.hpp"
#include "interface/INetworkContext.hpp"

/**
 * @class WinSocket
 * @brief Implementation of the ISocket interface for windows
 * @details Encapsulate a handle socket (winsock) and a shared ownership of the context (INetworkContext)
 */
class WinSocket : public ISocket {
    private:
        SOCKET allocatedSocket = INVALID_SOCKET;
        sockaddr_in localService = {};
        std::shared_ptr<INetworkContext> networkContext;

    public:
        /**
         * @brief Constructor of the object. The shared ptr of the network is to make sure the network context isn't deleted before the sockets
         * @param context a shared ownership of the network context.
         */
        WinSocket(std::shared_ptr<INetworkContext> context);

        // no copy because of unique ressource SOCKET
        WinSocket(const WinSocket &) = delete;
        WinSocket &operator=(const WinSocket &) = delete;

        // to steal
        // can steal but the original won't be usable after this to ensure we don't have a socket closing the SOCKET ressource and making the other socket crash
        WinSocket(WinSocket &&other) noexcept;
        WinSocket &operator=(WinSocket &&other) noexcept;

        void bindPort(const std::uint16_t port) override;

        std::size_t receive(std::span<std::uint8_t> buffer) override;

        ~WinSocket() override;
};