#ifndef _CLI_CLIENTHOOK_H_
#define _CLI_CLIENTHOOK_H_

#pragma once

#include "../../../../lib/Memory/Remote/Hook/RemoteHookService.h"

#include "../Base/HookBase.h"

#include "VirtualMethods/CreateMoveVirtualMethodHook.h"

namespace CLI
{
    class ClientHook : public HookBase
    {
        std::unique_ptr<Memory::RemoteVirtualMethodsTableHook>  _tabelHook;
        std::unique_ptr<CreateMoveVirtualMethodHook>            _createMove;

    public:

        ClientHook( Memory::SharedRemoteProcessService remoteProcessService,
                    Memory::SharedRemoteFunctionService remoteFunctionService,
                    Memory::SharedRemoteHookService remoteHookService );
        ~ClientHook() = default;

        bool Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle ) override;
    };
}

#endif /* _CLI_CLIENTHOOK_H_ */
