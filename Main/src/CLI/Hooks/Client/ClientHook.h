#ifndef _CLI_CLIENTHOOK_H_
#define _CLI_CLIENTHOOK_H_

#pragma once

#include "VirtualMethods/CreateMoveVirtualMethodHook.h"

#include "../Base/HookBase.h"

#include "../../../../lib/Memory/Remote/Hook/RemoteHookService.h"

namespace CLI
{
    class ClientHook : public HookBase
    {
        std::unique_ptr<Memory::RemoteVirtualMethodsTableHook>  _hook;
        std::unique_ptr<CreateMoveVirtualMethodHook>            _createMove;

    public:

        ClientHook( Memory::SharedRemoteProcessService remoteProcessService,
                    Memory::SharedRemoteFunctionService remoteFunctionService,
                    Memory::SharedRemoteHookService remoteHookService );
        ~ClientHook( void ) = default;

        bool Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle ) override;
    };
}

#endif /* _CLI_CLIENTHOOK_H_ */
