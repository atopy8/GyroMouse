#pragma once

#include "interface/ISocket.hpp"
#include <memory>

/**
 * @class ISocketFactory
 * @brief Interface defining the base contract for creating sockets without exposing real type. 
 * @details This abstract class serves as a abstraction layer independant of the platform. 
 * It allows the rest of the application to create the sockets without worrying of the underlying implementation linked to the OS (Winsock on win32 and posix on linux).
 */
class ISocketFactory {
    protected:
        // protected constructor to have a default but shouldn't be used.
        ISocketFactory() = default;
    public:
        virtual ~ISocketFactory() = default;

        /**
         * @brief Function used to create the socket without revealing its real type.
         * @return Returns unique_ptr of the socket created.
         */
        virtual std::unique_ptr<ISocket> createSocket() = 0;


        // no copy or steal since the factory is handled with unique ptr
        // no copy
        ISocketFactory(const ISocketFactory &) = delete;
        ISocketFactory &operator=(const ISocketFactory &) = delete;

        // no steal
        ISocketFactory(ISocketFactory &&other) = delete;
        ISocketFactory &operator=(ISocketFactory &&other) = delete;
};