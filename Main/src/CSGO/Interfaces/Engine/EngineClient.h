#ifndef _CSGO_ENGINECLIENT_H_
#define _CSGO_ENGINECLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

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
                typedef bool( __thiscall* IsConnectedFn )( uintptr_t );
                params->Result = IsConnectedFn( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 27 ] )( params->Instance );
            }
            _asm retn 1;
        }

        class ClientCmdUnrestrictedParams
        {
        public:
            explicit ClientCmdUnrestrictedParams( uintptr_t instance, const char* command, bool wait ) :
                Instance( instance ),
                Wait( wait )
            {
                auto size = min( strlen( command ) + 1, 200 );
                memcpy( Command, command, size );
            }

            uintptr_t   Instance = 0x0;
            bool        Wait = false;
            char        Command[ 200 ];
        };

        inline __declspec( naked ) void ClientCmdUnrestricted( ClientCmdUnrestrictedParams* params )
        {
            if( params != nullptr ) {
                typedef void( __thiscall* ClientCmdUnrestrictedFn )( uintptr_t, const char*, bool );
                ClientCmdUnrestrictedFn( ( *reinterpret_cast< DWORD** >( params->Instance ) )[ 114 ] )( params->Instance, params->Command, params->Wait );
            }
            _asm retn 1;
        }
    }

    class EngineClient : public InterfaceBase
    {
        std::unique_ptr<Memory::RemoteFunction> _isConnected;
        std::unique_ptr<Memory::RemoteFunction> _clientCmdUnrestricted;

    public:

        EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance );
        ~EngineClient( void ) = default;

        bool IsConnected( void );
        void ClientCmdUnrestricted( const char* command, bool wait = false );
    };

    extern std::unique_ptr<EngineClient> gEngineClient;
}

#endif /* _CSGO_ENGINECLIENT_H_ */