#include "HooksService.h"

namespace CLI
{
    HooksService::HooksService(
        Memory::SharedRemoteProcessService remoteProcessService,
        Memory::SharedRemoteFunctionService remoteFunctionService ) :
        _remoteProcessService( remoteProcessService ),
        _remoteFunctionService( remoteFunctionService ),
        _remoteHookService( std::make_shared<Memory::RemoteHookService>( remoteProcessService ) )
    {
        auto originProcessHandle = OpenProcess( Memory::RemoteProcessConsts::AccessRights, FALSE, GetCurrentProcessId() );
        if( !remoteProcessService->GetSharedHandle( originProcessHandle, Memory::RemoteProcessConsts::AccessRights, &_sharedOriginProcessHandle ) )
            throw std::exception( "couldn't share handle with target process." );
        CloseHandle( originProcessHandle );
    }

    HooksService::~HooksService()
    {
        if( _sharedOriginProcessHandle != INVALID_HANDLE_VALUE )
            CloseHandle( _sharedOriginProcessHandle );
    }
}
