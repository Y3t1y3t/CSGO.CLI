#ifndef _CSGO_CLIENT_H_
#define _CSGO_CLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

namespace CSGO
{
    class Client : public InterfaceBase
    {
    public:
        explicit    Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance = 0x0 );
                    ~Client( void ) = default;

        std::string GetModuleName( void ) override          { return "client.dll"; }
        std::string GetInterfaceVersion( void ) override    { return "VClient018"; }
    };

    extern std::unique_ptr<Client> gClient;
}

#endif /* _CSGO_CLIENT_H_ */
