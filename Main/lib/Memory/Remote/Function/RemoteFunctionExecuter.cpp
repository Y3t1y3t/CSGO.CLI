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

        auto remoteThreadHandle = HANDLE( nullptr );
        if( !_remoteProcessService->CreateRemoteThread( function->GetFunctionPtr(), function->GetDataPtr(), &remoteThreadHandle ) )
            return false;

        if( WaitForSingleObject( remoteThreadHandle, INFINITE ) != WAIT_OBJECT_0 )
            return false;

        return CloseHandle( remoteThreadHandle ) != FALSE;
    }
}
