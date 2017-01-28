#include "ClientHook.h"

namespace CLI
{
    bool ClientHook::OnLoad(
        Memory::SharedRemoteProcessService remoteProcessService,
        Memory::SharedRemoteFunctionService remoteFunctionService,
        Memory::SharedRemoteHookService remoteHookService,
        const uintptr_t& instance,
        const HANDLE& sharedProcessHandle )
    {
        if( !remoteHookService->Create<ClientHookSharedData>( instance, sharedProcessHandle, &_hook ) )
            return false;

        _createMove = std::make_unique<CreateMoveVirtualMethodHook>( remoteProcessService, remoteFunctionService );
        if( !_hook->SetVirtualMethodHook<ClientHookSharedData>( _createMove.get() ) )
            return false;

        _hook->SetTableHook();
        return true;
    }

    std::unique_ptr<ClientHook> gClientHook = std::make_unique<ClientHook>();
}
