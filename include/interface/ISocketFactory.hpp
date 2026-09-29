#pragma once

#include "interface/ISocket.hpp"
#include <memory>

class ISocketFactory {
    protected:
        ISocketFactory() = default;
    public:
        virtual ~ISocketFactory() = default;
        virtual std::unique_ptr<ISocket> createSocket() = 0;

        // no copy
        ISocketFactory(const ISocketFactory &) = delete;
        ISocketFactory &operator=(const ISocketFactory &) = delete;

        // no steal
        ISocketFactory(ISocketFactory &&other) = delete;
        ISocketFactory &operator=(ISocketFactory &&other) = delete;
};