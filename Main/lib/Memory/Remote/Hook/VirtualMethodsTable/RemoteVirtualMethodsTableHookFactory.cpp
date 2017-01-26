#include "RemoteVirtualMethodsTableHookFactory.h"

namespace Memory
{
    RemoteVirtualMethodsTableHookFactory::RemoteVirtualMethodsTableHookFactory( SharedRemoteProcessService remoteProcessService ) :
        _remoteProcessService( remoteProcessService ),
        _remoteVirtualMethodsResolver( std::make_unique<RemoteVirtualMethodsResolver>( remoteProcessService ) )
    {
    }
}
