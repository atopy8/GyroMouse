#pragma once

#include "interface/INetworkContext.hpp"
#include <WinSock2.h>


class WinNetworkContext : public INetworkContext {
    public:
        WinNetworkContext();
        ~WinNetworkContext();
};