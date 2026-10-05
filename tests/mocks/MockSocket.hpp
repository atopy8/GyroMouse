#pragma once

#include <gmock/gmock.h>

#include "interface/ISocket.hpp"

class MockSocket : public ISocket {

    public:
        MOCK_METHOD(std::size_t, receive, (std::span<std::uint8_t> buffer), (override));

        MOCK_METHOD(void, bindPort, (const std::uint16_t port), (override));
};