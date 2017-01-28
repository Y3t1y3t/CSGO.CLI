#ifndef _CLI_CLIENTHOOK_H_
#define _CLI_CLIENTHOOK_H_

#pragma once

#include "../../../../lib/Memory/Remote/Hook/RemoteHookService.h"

#include "VirtualMethods/CreateMoveVirtualMethodHook.h"

namespace CLI
{
    class ClientHook
    {
        std::unique_ptr<Memory::RemoteVirtualMethodsTableHook> _hook;
        std::unique_ptr<CreateMoveVirtualMethodHook> _createMove;

    public:

        bool OnLoad( Memory::SharedRemoteProcessService remoteProcessService,
                     Memory::SharedRemoteFunctionService remoteFunctionService,
                     Memory::SharedRemoteHookService remoteHookService,
                     const uintptr_t& instance,
                     const HANDLE& sharedProcessHandle );
    };

    extern std::unique_ptr<ClientHook> gClientHook;
}

#endif /* _CLI_CLIENTHOOK_H_ */
