#pragma once

#include "interface/INetworkContext.hpp"
#include <WinSock2.h>


class WinNetworkContext : public INetworkContext {
    public:
        WinNetworkContext();
        ~WinNetworkContext();

        // no copy
        WinNetworkContext(const WinNetworkContext &) = delete;
        WinNetworkContext &operator=(const WinNetworkContext &) = delete;

        // no steal
        WinNetworkContext(WinNetworkContext &&other) = delete;
        WinNetworkContext &operator=(WinNetworkContext &&other) = delete;
};