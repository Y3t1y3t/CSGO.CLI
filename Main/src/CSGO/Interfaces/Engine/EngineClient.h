#ifndef _CSGO_ENGINECLIENT_H_
#define _CSGO_ENGINECLIENT_H_

#pragma once

#include "../../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

namespace CSGO
{
    namespace Remote
    {
        class IsConnectedParams
        {
        public:
            explicit IsConnectedParams( uintptr_t instance ) : Instance( instance ) {}

            uintptr_t   Instance = 0x0;
            bool        Result = false;
        };

        inline __declspec( naked ) void IsConnected( IsConnectedParams* params )
        {
            if( params != nullptr ) {
                params->Result = reinterpret_cast< bool( __thiscall* )( uintptr_t ) >( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 27 ] )( params->Instance );
            }
            _asm retn 1;
        }
    }

    class EngineClient
    {
        Memory::SharedRemoteFunctionService     _remoteFunctionService;
        uintptr_t                               _instance;

        /* FUNCTION */
        std::unique_ptr<Memory::RemoteFunction> _isConnected;

    public:

        EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance );

        bool IsConnected( void );
    };

    extern std::unique_ptr<EngineClient> gEngineClient;
}

#endif /* _CSGO_ENGINECLIENT_H_ */