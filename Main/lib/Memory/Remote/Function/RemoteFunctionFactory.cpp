#include "RemoteFunctionFactory.h"
#include "RemoteFunctionResolver.h"

namespace Memory
{
    RemoteFunctionFactory::RemoteFunctionFactory( SharedRemoteProcessService remoteProcessService )
        : _remoteProcessService( remoteProcessService )
    {
    }

    bool RemoteFunctionFactory::Create( LPTHREAD_START_ROUTINE functionRoutine, std::unique_ptr<RemoteFunction>* function ) const
    {
        std::vector<byte> functionBytes;
        if( !RemoteFunctionResolver().Resolve( functionRoutine, functionBytes ) )
            return false;

        LPVOID remoteFunctionBytes;
        if( !_remoteProcessService->CreateAllocatedRemoteData( &functionBytes.at( 0 ), functionBytes.size(), &remoteFunctionBytes ) )
            return false;

        *function = std::make_unique<RemoteFunction>( _remoteProcessService, remoteFunctionBytes );
        return true;
    }

    bool RemoteFunctionFactory::Create( LPTHREAD_START_ROUTINE functionRoutine, LPVOID data, size_t size, std::unique_ptr<RemoteFunction>* function ) const
    {
        if( !Create( functionRoutine, function ) )
            return false;

        LPVOID remoteFunctionData;
        if( !_remoteProcessService->CreateAllocatedRemoteData( static_cast< byte* >( data ), size, &remoteFunctionData ) )
            return false;

        ( *function )->SetDataPtr( remoteFunctionData );
        return true;
    }
}
