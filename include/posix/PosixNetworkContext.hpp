#pragma once

#include "interface/INetworkContext.hpp"

class PosixNetworkContext : public INetworkContext {
    PosixNetworkContext();
    ~PosixNetworkContext();
};