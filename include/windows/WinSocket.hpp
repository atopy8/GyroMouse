#pragma once

 
#include <WinSock2.h>
#include <memory>

#include "interface/ISocket.hpp"
#include "interface/INetworkContext.hpp"

class WinSocket : public ISocket {
    private:
        SOCKET allocatedSocket = INVALID_SOCKET;
        sockaddr_in localService = {};
        std::shared_ptr<INetworkContext> networkContext;

    public:
        WinSocket(std::shared_ptr<INetworkContext> context);

        // no copy
        WinSocket(const WinSocket &) = delete;
        WinSocket &operator=(const WinSocket &) = delete;

        // to steal
        WinSocket(WinSocket &&other) noexcept;
        WinSocket &operator=(WinSocket &&other) noexcept;

        void bindPort(const std::uint16_t port) override;

        std::size_t receive(std::span<std::uint8_t> buffer) override;

        ~WinSocket() override;
};