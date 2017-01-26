#include "EngineClient.h"

namespace CSGO
{
    EngineClient::EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) : 
        InterfaceBase( remoteFunctionService, instance)
    {
    }

    bool EngineClient::IsConnected( void )
    {
        auto params = Remote::IsConnectedParams( _instance );
        if( _isConnected == nullptr && !_remoteFunctionService->Create( LPTHREAD_START_ROUTINE( Remote::IsConnected ), &params, sizeof( Remote::IsConnectedParams ), &_isConnected ) )
            return false;

        if( !_remoteFunctionService->Execute( _isConnected ) )
            return false;

        if( !_isConnected->GetDataPtrValue( &params ) )
            return false;
        return params.Result;
    }

    void EngineClient::ClientCmdUnrestricted( const char* command, bool wait )
    {
        auto params = Remote::ClientCmdUnrestrictedParams( _instance, command, wait );
        if( _clientCmdUnrestricted == nullptr
            && !_remoteFunctionService->Create( LPTHREAD_START_ROUTINE( Remote::ClientCmdUnrestricted ), &params, sizeof( Remote::ClientCmdUnrestrictedParams ), &_clientCmdUnrestricted )
            || !_clientCmdUnrestricted->SetDataPtrValue( params ) )
            return;

        _remoteFunctionService->Execute( _clientCmdUnrestricted );
    }

    std::unique_ptr<EngineClient> gEngineClient;
}
