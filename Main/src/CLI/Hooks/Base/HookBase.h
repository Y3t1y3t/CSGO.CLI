#ifndef _CLI_HOOKBASE_H_
#define _CLI_HOOKBASE_H_

#pragma once

#include "../../../../lib/Memory/Remote/Function/RemoteFunctionService.h"
#include "../../../../lib/Memory/Remote/Hook/RemoteHookService.h"

namespace CLI
{
    class HookBase
    {
    protected:
        Memory::SharedRemoteProcessService _remoteProcessService;
        Memory::SharedRemoteFunctionService _remoteFunctionService;
        Memory::SharedRemoteHookService _remoteHookService;

    public:

        HookBase( Memory::SharedRemoteProcessService remoteProcessService,
                    Memory::SharedRemoteFunctionService remoteFunctionService,
                    Memory::SharedRemoteHookService remoteHookService );
        virtual ~HookBase( void ) = default;

        virtual bool Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle ) = 0;
    };
}

#endif /* _CLI_HOOKBASE_H_ */
