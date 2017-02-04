#include "EngineClient.h"

namespace CSGO
{
    EngineClient::EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }

    DWORD EngineClient::Remote::IsConnected( LPVOID paramsPtr )
    {
        if( paramsPtr != nullptr ) {
            auto params = static_cast< IsConnectedParams* >( paramsPtr );

            using IsConnectedFn = bool( __thiscall* )( uintptr_t );
            params->Result = IsConnectedFn( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 27 ] )( params->Instance );
        }
        return 0;
    }

    DWORD EngineClient::Remote::ClientCmdUnrestricted( LPVOID paramsPtr )
    {
        if( paramsPtr != nullptr ) {
            auto params = static_cast< ClientCmdUnrestrictedParams* >( paramsPtr );

            using ClientCmdUnrestrictedFn = void( __thiscall* )( uintptr_t, const char*, bool );
            ClientCmdUnrestrictedFn( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 114 ] )( params->Instance, params->Command, params->Wait );
        }
        return 0;
    }

    bool EngineClient::IsConnected()
    {
        auto params = Remote::IsConnectedParams( _instance );
        if( _isConnected == nullptr && !_remoteFunctionService->Create( Remote::IsConnected, &params, sizeof( Remote::IsConnectedParams ), &_isConnected ) )
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
            && !_remoteFunctionService->Create( Remote::ClientCmdUnrestricted, &params, sizeof( Remote::ClientCmdUnrestrictedParams ), &_clientCmdUnrestricted )
            || !_clientCmdUnrestricted->SetDataPtrValue( params ) )
            return;

        _remoteFunctionService->Execute( _clientCmdUnrestricted );
    }

    std::unique_ptr<EngineClient> gEngineClient;
}
