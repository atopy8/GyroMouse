#pragma once

#include "interface/ISocketFactory.hpp"
#include "windows/WinNetworkContext.hpp"

/**
 * @class WinSocketFactory
 * @brief Is used to create WinSockets
 * @details Should be created by the SocketFactoryProvider. Should be created before sockets and survives to all sockets created, but if order is not respected, there is the shared ownership so it doesn't crash
 * Shared ownership of the network context. The network context should be created with it. This network context will be shared with the socket created by the factory.
 */
class WinSocketFactory : public ISocketFactory {
    private:
        std::shared_ptr<WinNetworkContext> networkContext;

    public:
        WinSocketFactory();
        ~WinSocketFactory() override;

        /**
         * @brief creates a socket.
         * @return the unique pointer of the socket created.
         */
        std::unique_ptr<ISocket> createSocket() override;
        

       
};