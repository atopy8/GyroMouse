#pragma once

#include "interface/INetworkContext.hpp"

class PosixNetworkContext : public INetworkContext {
    public:
        PosixNetworkContext();
        ~PosixNetworkContext();
};