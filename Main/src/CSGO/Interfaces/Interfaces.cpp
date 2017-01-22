#include "Interfaces.h"

namespace CSGO
{
    bool Interfaces::OnLoad( Memory::SharedRemoteFunctionService remoteFunctionService ) const
    {
        std::unique_ptr<Memory::RemoteFunction> function;
        Remote::GetInterfacesParams params;

        if( !remoteFunctionService->Create( LPTHREAD_START_ROUTINE( Remote::GetInterfaces ), &params, sizeof( Remote::GetInterfacesParams ), &function ) )
            return false;

        if( !remoteFunctionService->Execute( function ) )
            return false;

        if( !function->GetDataPtrValue( &params ) )
            return false;
        
        gEngineClient = std::make_unique<EngineClient>( remoteFunctionService, params.Engine.EngineClient.Instance );
        return true;
    }

    std::unique_ptr<Interfaces> gInterfaces = std::make_unique<Interfaces>();
}
