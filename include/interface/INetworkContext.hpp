#pragma once

class INetworkContext {
    protected:
        INetworkContext() = default;

    public:
        virtual ~INetworkContext() = default;

        INetworkContext(const INetworkContext &) = delete;
        INetworkContext &operator=(const INetworkContext &) = delete;

        INetworkContext(INetworkContext &&) = delete;
        INetworkContext &operator=(INetworkContext &&) = delete;
};