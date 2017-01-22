#ifndef _CSGO_INTERFACES_H_
#define _CSGO_INTERFACES_H_

#pragma once

#include "Engine/EngineClient.h"

#include "../../../lib/Memory/Remote/Function/RemoteFunctionParams.h"

#include <memory>

namespace CSGO
{
    namespace Remote
    {
        class GetInterfacesParams : public Memory::RemoteFunctionParams
        {
        public:
            typedef uintptr_t( __cdecl* CreateInterfaceFn )( const char*, uintptr_t* );
            const char CreateInterface[ 16 ] = "CreateInterface";

            struct Engine
            {
                const char Name[ 11 ] = "engine.dll";
                uintptr_t Base = 0x0;
                CreateInterfaceFn CreateInterface;

                struct EngineClient
                {
                    const char Version[ 17 ] = "VEngineClient014";
                    DWORD Instance = 0x0;
                } EngineClient;
            } Engine;
        };

        inline __declspec( naked ) void GetInterfaces( GetInterfacesParams* params )
        {
            if( params != nullptr ) {
                for( ;; params->Imports.Kernel32.Sleep( 50 ) ) {
                    params->Engine.Base = DWORD( params->Imports.Kernel32.GetModuleHandleA( params->Engine.Name ) );
                    if( params->Engine.Base != 0x0 )
                        break;
                }

                params->Engine.CreateInterface = GetInterfacesParams::CreateInterfaceFn( params->Imports.Kernel32.GetProcAddress( HMODULE( params->Engine.Base ), params->CreateInterface ) );
                if( params->Engine.CreateInterface ) {
                    params->Engine.EngineClient.Instance = params->Engine.CreateInterface( params->Engine.EngineClient.Version, nullptr );
                }
            }
            _asm retn 1;
        }
    }

    class Interfaces
    {
    public:
        bool OnLoad( Memory::SharedRemoteFunctionService remoteFunctionService ) const;
    };

    extern std::unique_ptr<Interfaces> gInterfaces;
}

#endif /* _CSGO_INTERFACES_H_ */
