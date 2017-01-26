#ifndef _CSGO_INTERFACES_H_
#define _CSGO_INTERFACES_H_

#pragma once

#include "Client/Client.h"
#include "Engine/EngineClient.h"

#include "../../../lib/Memory/Remote/Function/RemoteFunctionParams.h"
#include "../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

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

            struct ClientModule
            {
                const char Name[ 11 ] = "client.dll";
                uintptr_t Base = 0x0;
                CreateInterfaceFn CreateInterface;

                struct Client
                {
                    const char Version[ 11 ] = "VClient018";
                    DWORD Instance = 0x0;
                } Client;
            } ClientModule;

            struct EngineModule
            {
                const char Name[ 11 ] = "engine.dll";
                uintptr_t Base = 0x0;
                CreateInterfaceFn CreateInterface;

                struct EngineClient
                {
                    const char Version[ 17 ] = "VEngineClient014";
                    DWORD Instance = 0x0;
                } EngineClient;
            } EngineModule;
        };

        inline __declspec( naked ) void GetInterfaces( GetInterfacesParams* params )
        {
            if( params != nullptr ) {

                /* CLIENT */

                for( ;; params->Imports.Kernel32.Sleep( 50 ) ) {
                    params->ClientModule.Base = DWORD( params->Imports.Kernel32.GetModuleHandleA( params->ClientModule.Name ) );
                    if( params->ClientModule.Base != 0x0 )
                        break;
                }

                params->ClientModule.CreateInterface = GetInterfacesParams::CreateInterfaceFn( params->Imports.Kernel32.GetProcAddress( HMODULE( params->ClientModule.Base ), params->CreateInterface ) );
                if( params->ClientModule.CreateInterface ) {
                    params->ClientModule.Client.Instance = params->ClientModule.CreateInterface( params->ClientModule.Client.Version, nullptr );
                }

                /* ENGINE */

                for( ;; params->Imports.Kernel32.Sleep( 50 ) ) {
                    params->EngineModule.Base = DWORD( params->Imports.Kernel32.GetModuleHandleA( params->EngineModule.Name ) );
                    if( params->EngineModule.Base != 0x0 )
                        break;
                }

                params->EngineModule.CreateInterface = GetInterfacesParams::CreateInterfaceFn( params->Imports.Kernel32.GetProcAddress( HMODULE( params->EngineModule.Base ), params->CreateInterface ) );
                if( params->EngineModule.CreateInterface ) {
                    params->EngineModule.EngineClient.Instance = params->EngineModule.CreateInterface( params->EngineModule.EngineClient.Version, nullptr );
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
