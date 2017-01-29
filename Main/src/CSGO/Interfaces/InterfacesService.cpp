#include "InterfacesService.h"

namespace CSGO
{
    InterfacesService::InterfacesService( Memory::SharedRemoteFunctionService remoteFunctionService ) :
        _remoteFunctionService( remoteFunctionService )
    {
    }

    InterfacesService::Remote::GetInterfaceParams::GetInterfaceParams( const std::string& moduleName, const std::string& interfaceVersion )
    {
        Interface.Instance = 0x0;

        auto interfaceVersionSize = min( interfaceVersion.size() + 1, 200 );
        memcpy( Interface.Version, interfaceVersion.c_str(), interfaceVersionSize );

        auto moduleNameSize = min( moduleName.size() + 1, 200 );
        memcpy( Module.Name, moduleName.c_str(), moduleNameSize );
    }

    DWORD InterfacesService::Remote::GetInterface( LPVOID paramsPtr )
    {
        if( paramsPtr != nullptr ) {
            auto params = static_cast< GetInterfaceParams* >( paramsPtr );

            HMODULE module;
            for( ;; params->Imports.Kernel32.Sleep( 50 ) ) {
                module = params->Imports.Kernel32.GetModuleHandleA( params->Module.Name );
                if( module != nullptr )
                    break;
            }

            auto createInterface = GetInterfaceParams::CreateInterfaceFn( params->Imports.Kernel32.GetProcAddress( module, params->CreateInterface ) );
            if( createInterface ) {
                params->Interface.Instance = createInterface( params->Interface.Version, nullptr );
            }
        }
        return 0;
    }
}
