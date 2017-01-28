#ifndef _CSGO_CLIENT_H_
#define _CSGO_CLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

#include "../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/SharedData/RemoteVirtualMethodsTableHookSharedData.h"

namespace CSGO
{
    namespace Remote
    {

    }

    class Client : public InterfaceBase
    {
    public:
        Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance );
        ~Client( void ) = default;
    };

    extern std::unique_ptr<Client> gClient;
}

#endif /* _CSGO_CLIENT_H_ */
