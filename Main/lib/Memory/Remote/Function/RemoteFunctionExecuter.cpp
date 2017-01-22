#include "RemoteFunctionExecuter.h"

namespace Memory
{
    RemoteFunctionExecuter::RemoteFunctionExecuter( SharedRemoteProcessService remoteProcessService ) :
        _remoteProcessService( remoteProcessService )
    {
    }

    bool RemoteFunctionExecuter::Execute( const std::unique_ptr<RemoteFunction>& function ) const
    {
        if( !function->IsValidFunctionPtr() )
            return false;

        auto remoteThreadHandle = _remoteProcessService->StartRemoteThread( function->GetFunctionPtr(), function->GetDataPtr() );
        if( remoteThreadHandle == nullptr )
            return false;

        return WaitForSingleObject( remoteThreadHandle, INFINITE ) == WAIT_OBJECT_0;
    }
}
