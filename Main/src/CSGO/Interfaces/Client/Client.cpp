#include "Client.h"

namespace CSGO
{
    Client::Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }

    DWORD Client::Remote::GetAllClasses( LPVOID paramsPtr )
    {
        if( paramsPtr != nullptr ) {
            auto params = static_cast< GetAllClassesParams* >( paramsPtr );

            using GetAllClassesFn = uintptr_t( __thiscall* )( uintptr_t );
            params->Result = GetAllClassesFn( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 8 ] )( params->Instance );
        }
        return 0;
    }

    uintptr_t Client::GetAllClasses()
    {
        auto params = Remote::GetAllClassesParams( _instance );
        if( _getAllClasses == nullptr && !_remoteFunctionService->Create( Remote::GetAllClasses, &params, sizeof( Remote::GetAllClassesParams ), &_getAllClasses ) )
            return 0x0;

        if( !_remoteFunctionService->Execute( _getAllClasses ) )
            return 0x0;

        if( !_getAllClasses->GetDataPtrValue( &params ) )
            return 0x0;
        return params.Result;
    }

    std::unique_ptr<Client> gClient;
}
