#include "ClientHook.h"
#include "SharedData/ClientHookSharedData.h"

namespace CLI
{
    ClientHook::ClientHook(
        Memory::SharedRemoteProcessService remoteProcessService,
        Memory::SharedRemoteFunctionService remoteFunctionService,
        Memory::SharedRemoteHookService remoteHookService ) :
        HookBase( remoteProcessService, remoteFunctionService, remoteHookService )
    {
    }

    bool ClientHook::Register( const uintptr_t& instance, const HANDLE& sharedOriginProcessHandle )
    {
        if( !_remoteHookService->Create<ClientHookSharedData>( instance, sharedOriginProcessHandle, &_hook ) )
            return false;

        _createMove = std::make_unique<CreateMoveVirtualMethodHook>( _remoteProcessService, _remoteFunctionService );
        if( !_hook->SetVirtualMethodHook<ClientHookSharedData>( _createMove.get() ) )
            return false;

        _hook->SetTableHook();
        return true;
    }
}
