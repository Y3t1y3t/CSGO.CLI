#ifndef _CSGO_ENGINECLIENT_H_
#define _CSGO_ENGINECLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

namespace CSGO
{
    class EngineClient : public InterfaceBase
    {
        std::unique_ptr<Memory::RemoteFunction> _isConnected;
        std::unique_ptr<Memory::RemoteFunction> _clientCmdUnrestricted;

    public:

        explicit    EngineClient( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance = 0x0 );
                    ~EngineClient() = default;

        std::string GetModuleName() override          { return "engine.dll"; }
        std::string GetInterfaceVersion() override    { return "VEngineClient014"; }

    private:

        struct Remote
        {
        #pragma region IsConnected
            class IsConnectedParams
            {
            public:
                explicit IsConnectedParams( const uintptr_t& instance = 0x0 ) :
                    Instance( instance ),
                    Result( false )
                {
                }

                uintptr_t   Instance;
                bool        Result;
            };

            static DWORD WINAPI IsConnected( LPVOID paramsPtr );
        #pragma endregion
        #pragma region ClientCmdUnrestricted
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

            static DWORD WINAPI ClientCmdUnrestricted( LPVOID paramsPtr );
        #pragma endregion
        };

    public:

        bool IsConnected();
        void ClientCmdUnrestricted( const char* command, bool wait = false );
    };

    extern std::unique_ptr<EngineClient> gEngineClient;
}

#endif /* _CSGO_ENGINECLIENT_H_ */