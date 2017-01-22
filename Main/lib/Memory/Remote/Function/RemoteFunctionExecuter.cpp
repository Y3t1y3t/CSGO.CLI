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

        if( WaitForSingleObject( remoteThreadHandle, INFINITE ) != WAIT_OBJECT_0 )
            return false;

        return CloseHandle( remoteThreadHandle ) != FALSE;
    }
}
