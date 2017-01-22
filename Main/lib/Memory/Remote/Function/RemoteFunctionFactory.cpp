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

        *function = std::make_unique<RemoteFunction>( _remoteProcessService, _remoteProcessService->AllocRemoteData( &functionBytes.at( 0 ), functionBytes.size() ) );
        return (*function)->IsValidFunctionPtr();
    }

    bool RemoteFunctionFactory::Create( LPTHREAD_START_ROUTINE functionRoutine, LPVOID data, size_t size, std::unique_ptr<RemoteFunction>* function ) const
    {
        if( !Create( functionRoutine, function ) )
            return false;

        (*function)->SetDataPtr( _remoteProcessService->AllocRemoteData( static_cast< byte* >( data ), size ) );
        return (*function)->IsValidDataPtr();
    }
}
