#ifndef _CLI_ENGINEVGUIHOOK_H_
#define _CLI_ENGINEVGUIHOOK_H_

#pragma once

#include "../Base/HookBase.h"

#include "VirtualMethods/PaintVirtualMethodHook.h"

namespace CLI
{
    class EngineVGuiHook : public HookBase
    {
        std::unique_ptr<Memory::RemoteVirtualMethodsTableHook>  _tableHook;
        std::unique_ptr<PaintVirtualMethodHook>                 _paintHook;

    public:

        EngineVGuiHook( const Memory::SharedRemoteProcessService& remoteProcessService,
                        const Memory::SharedRemoteFunctionService& remoteFunctionService,
                        const Memory::SharedRemoteHookService& remoteHookService );
        ~EngineVGuiHook() = default;

        bool Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle ) override;
    };
}

#endif /* _CLI_ENGINEVGUIHOOK_H_ */
