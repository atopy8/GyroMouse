#pragma once

/**
 * @class INetworkContext
 * @brief Abstraction representing the availibility of the network
 * @details "useless" for linux but mandatory for WSACleanup and WSAStartup on windows. Interfacing it so both implementation have same calls.
 * No methods.
 */
class INetworkContext {
    protected:
        INetworkContext() = default;

    public:
        virtual ~INetworkContext() = default;

        //no copy because if two object have the same context, one could close it for the other resulting in a crash
        // no copy
        INetworkContext(const INetworkContext &) = delete;
        INetworkContext &operator=(const INetworkContext &) = delete;

        //no steal, oculd be made but it would recquire an information on the object that the context has been stolen, adding complexity for nothing.
        INetworkContext(INetworkContext &&) = delete;
        INetworkContext &operator=(INetworkContext &&) = delete;
};