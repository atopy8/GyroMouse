#pragma once

#include "interface/ISocketFactory.hpp"

/**
 * @class SocketFactoryProvider
 * @brief Class allowing the user to create a socket factory without knowing which implementation will be used.
 */
class SocketFactoryProvider {
    public:
        /**
         * @brief function used by user to create a socket factory without knowing which platform its using.
         * @return unique ptr of the socket factory
         * @details this function will have two real implementations, only one will be compiled at compilation, depending on the platform its compiling on.
         */
        static std::unique_ptr<ISocketFactory> createSocketFactory();
};