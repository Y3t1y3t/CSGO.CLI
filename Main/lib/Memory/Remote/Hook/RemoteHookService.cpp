#include "RemoteHookService.h"

namespace Memory
{
    RemoteHookService::RemoteHookService( SharedRemoteProcessService remoteProcessService ) :
        _remoteVirtualMethodsTableHookFactory( std::make_unique<RemoteVirtualMethodsTableHookFactory>( remoteProcessService ) )
    {
    }
}
