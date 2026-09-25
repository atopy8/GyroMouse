#pragma once

#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>

#include "ISocket.hpp"

class WinSocket : public ISocket {

    private:
        SOCKET allocatedSocket = INVALID_SOCKET;
        WSADATA wsaData;
        sockaddr_in service = {};

    public:
        WinSocket();

        // no copy
        WinSocket(const WinSocket &) = delete;
        WinSocket &operator=(const WinSocket &) = delete;

        // to steal
        WinSocket(WinSocket &&other) noexcept;
        WinSocket &operator=(WinSocket &&other) noexcept;

        void bindPort(const std::uint16_t port) override;

        std::size_t receive(std::span<std::uint8_t> buffer) override;

        ~WinSocket();
};