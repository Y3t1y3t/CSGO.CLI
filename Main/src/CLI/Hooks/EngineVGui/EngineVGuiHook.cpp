#include "EngineVGuiHook.h"

#include "SharedData/EngineVGuiHookSharedData.h"

namespace CLI
{
    EngineVGuiHook::EngineVGuiHook( const Memory::SharedRemoteProcessService& remoteProcessService,
                                    const Memory::SharedRemoteFunctionService& remoteFunctionService,
                                    const Memory::SharedRemoteHookService& remoteHookService ) :
        HookBase( remoteProcessService, remoteFunctionService, remoteHookService )
    {
    }

    bool EngineVGuiHook::Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle )
    {
        if( !_remoteHookService->Create<EngineVGuiHookSharedData>( instance, sharedOriginProcessHandle, &_tableHook ) )
            return false;

        _paintHook = std::make_unique<PaintVirtualMethodHook>( _remoteProcessService, _remoteFunctionService );
        if( !_tableHook->SetVirtualMethodHook<EngineVGuiHookSharedData>( _paintHook.get() ) )
            return false;

        _tableHook->SetTableHook();
        return true;
    }
}
