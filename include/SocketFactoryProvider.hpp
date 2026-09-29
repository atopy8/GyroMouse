#pragma once

#include "interface/ISocketFactory.hpp"

class SocketFactoryProvider {
    public:
        static std::unique_ptr<ISocketFactory> createSocketFactory();
};