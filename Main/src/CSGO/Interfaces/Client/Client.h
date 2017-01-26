#ifndef _CSGO_CLIENT_H_
#define _CSGO_CLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

#include "../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/SharedData/RemoteVirtualMethodsTableHookSharedData.h"

namespace CSGO
{
    namespace Remote
    {
        class ClientSharedData : public Memory::RemoteVirtualMethodsTableHookSharedData
        {
        public:
            explicit ClientSharedData( const uintptr_t& virtualMethodsTablePtr = 0x0, HANDLE sharedOriginProcessHandle = nullptr );

            class CreateMoveHook : public HookBase
            {
            public:
                struct Parameters
                {
                    size_t      Number;
                    float       Input;
                    bool        Active;
                } Params;
            } CreateMove;
        };

        inline void __fastcall hkCreateMove( void *ecx, void *, size_t number, float input, bool active )
        {
            if( ecx != nullptr ) {
                auto sharedData = reinterpret_cast< ClientSharedData* >( *reinterpret_cast< uintptr_t* >( ecx ) - sizeof( ClientSharedData ) );

                typedef void( __thiscall* CreateMoveFn )( uintptr_t, size_t, float, bool );
                CreateMoveFn( sharedData->CreateMove.Function )( sharedData->VirtualMethodsTablePtr, number, input, active );

                sharedData->CreateMove.Params.Number = number;
                sharedData->CreateMove.Params.Input = input;
                sharedData->CreateMove.Params.Active = active;

                auto remoteThreadHandle = sharedData->Imports.Kernel32.CreateRemoteThread( sharedData->SharedOriginProcessHandle, nullptr, NULL, sharedData->CreateMove.Callback, &sharedData->CreateMove.Params, NULL, nullptr );
                if( remoteThreadHandle != nullptr ) {
                    if( sharedData->Imports.Kernel32.WaitForSingleObject( remoteThreadHandle, INFINITE ) == WAIT_OBJECT_0 && remoteThreadHandle != INVALID_HANDLE_VALUE ) {
                        sharedData->Imports.Kernel32.CloseHandle( remoteThreadHandle );
                    }
                }
            }
        }
    }

    class Client : public InterfaceBase
    {
    public:
        Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance );
        ~Client( void ) = default;
    };

    extern std::unique_ptr<Client> gClient;
}

#endif /* _CSGO_CLIENT_H_ */
