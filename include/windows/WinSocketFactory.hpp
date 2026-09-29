#pragma once

#include "interface/ISocketFactory.hpp"
#include "windows/WinNetworkContext.hpp"

class WinSocketFactory : public ISocketFactory {
    private:
        std::shared_ptr<WinNetworkContext> networkContext;

    public:
        WinSocketFactory();
        ~WinSocketFactory() override;

        std::unique_ptr<ISocket> createSocket() override;
        

       
};