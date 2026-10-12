#pragma once

#include "interface/INetworkContext.hpp"

/**
 * @class PosixNetworkContext
 * @brief Posix implementation of the network context. Not implemented yet.
 */
class PosixNetworkContext : public INetworkContext {
    public:
        PosixNetworkContext();
        ~PosixNetworkContext();
};