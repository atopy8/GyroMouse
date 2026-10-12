#pragma once

#include "interface/INetworkContext.hpp"
#include <WinSock2.h>

/**
 * @class WinNetworkContext
 * @brief RAII(Resource Acquisition Is Initialzation) for the WSAStartup / WSACleanup resource.
 */
class WinNetworkContext : public INetworkContext {
    public:
        /**
         * @brief Constructor of the WinNetworkContext Object. Calls WSAStartup
         * @throw std::runtime_error if WSAStartup fails
         */
        WinNetworkContext();
        /**
         * @brief destructor of WinNetworkContext
         * Calls WSACleanup
         */
        ~WinNetworkContext();
};