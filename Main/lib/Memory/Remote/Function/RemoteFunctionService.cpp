#include "RemoteFunctionService.h"

namespace Memory
{
    RemoteFunctionService::RemoteFunctionService( SharedRemoteProcessService remoteProcessSerivce ) :
        _functionExecuter( std::make_unique<RemoteFunctionExecuter>( remoteProcessSerivce ) ),
        _functionFactory( std::make_unique<RemoteFunctionFactory>( remoteProcessSerivce ) )
    {
    }

    bool RemoteFunctionService::Create( LPTHREAD_START_ROUTINE functionRoutine, std::unique_ptr<RemoteFunction>* function ) const
    {
        return _functionFactory->Create( functionRoutine, function );
    }

    bool RemoteFunctionService::Create( LPTHREAD_START_ROUTINE functionRoutine, LPVOID data, size_t size, std::unique_ptr<RemoteFunction>* function ) const
    {
        return _functionFactory->Create( functionRoutine, data, size, function );
    }

    bool RemoteFunctionService::Execute( const std::unique_ptr<RemoteFunction>& function ) const
    {
        return _functionExecuter->Execute( function );
    }
}
