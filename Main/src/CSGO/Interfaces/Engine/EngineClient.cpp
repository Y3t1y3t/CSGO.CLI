#include "EngineClient.h"

namespace CSGO
{
    EngineClient::EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        _remoteFunctionService( remoteFunctionService ),
        _instance( instance )
    {
    }

    bool EngineClient::IsConnected( void )
    {
        auto result = Remote::IsConnectedParams( _instance );
        if( _isConnected == nullptr && !_remoteFunctionService->Create( LPTHREAD_START_ROUTINE( Remote::IsConnected ), &result, sizeof( Remote::IsConnectedParams ), &_isConnected ) )
            return false;

        if( !_remoteFunctionService->Execute( _isConnected ) )
            return false;

        if( !_isConnected->GetDataPtrValue( &result ) )
            return false;
        return result.Result;
    }

    std::unique_ptr<EngineClient> gEngineClient;
}
