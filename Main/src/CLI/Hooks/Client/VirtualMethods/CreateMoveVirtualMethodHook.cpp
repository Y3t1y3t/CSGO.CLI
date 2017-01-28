#include "CreateMoveVirtualMethodHook.h"

#include <iostream>

namespace CLI
{
    CreateMoveVirtualMethodHook* CreateMoveVirtualMethodHook::_self = nullptr;

    CreateMoveVirtualMethodHook::CreateMoveVirtualMethodHook( Memory::SharedRemoteProcessService remoteProcessService, Memory::SharedRemoteFunctionService remoteFunctionService )
    {
        if( _self != nullptr )
            throw std::exception( "only on instance can be created at the same time." );

        _self = this;
        _remoteProcessService = remoteProcessService;

        Index = 21;
        Callback = FunctionCallback;
        GetVirtualMethodData = ( [] ( void* sharedData ) -> Memory::RemoteVirtualMethodsTableHookSharedData::VirtualMethodData* {
            return &static_cast< ClientHookSharedData * >( sharedData )->CreateMoveData;
        } );

        remoteFunctionService->Create( LPTHREAD_START_ROUTINE( VirtualMethodCallback ), &RemoteCallback );
    }

    CreateMoveVirtualMethodHook::~CreateMoveVirtualMethodHook()
    {
        _self = nullptr;
    }

    DWORD CreateMoveVirtualMethodHook::FunctionCallback( LPVOID paramsPtr )
    {
        if( paramsPtr == nullptr )
            return -1;

        ClientHookSharedData::CreateMoveVirtualMethod::Parameters params;
        if( !_self->_remoteProcessService->Read( paramsPtr, &params ) )
            return -2;

        std::cout << "hkCreateMove called. seq: " << params.Number << std::endl;
        return 0;
    }

    void CreateMoveVirtualMethodHook::VirtualMethodCallback( void* ecx, void*, size_t number, float input, bool active )
    {
        if( ecx != nullptr ) {
            auto sharedData = reinterpret_cast< ClientHookSharedData* >( *reinterpret_cast< uintptr_t* >( ecx ) - sizeof( ClientHookSharedData ) );

            typedef void( __thiscall* CreateMoveFn )( uintptr_t, size_t, float, bool );
            CreateMoveFn( sharedData->CreateMoveData.Function )( sharedData->VirtualMethodsTablePtr, number, input, active );

            sharedData->CreateMoveData.Params.Number = number;
            sharedData->CreateMoveData.Params.Input = input;
            sharedData->CreateMoveData.Params.Active = active;

            auto remoteThreadHandle = sharedData->Imports.Kernel32.CreateRemoteThread( sharedData->SharedOriginProcessHandle, nullptr, NULL, sharedData->CreateMoveData.Callback, &sharedData->CreateMoveData.Params, NULL, nullptr );
            if( remoteThreadHandle != nullptr ) {
                if( sharedData->Imports.Kernel32.WaitForSingleObject( remoteThreadHandle, INFINITE ) == WAIT_OBJECT_0 && remoteThreadHandle != INVALID_HANDLE_VALUE ) {
                    sharedData->Imports.Kernel32.CloseHandle( remoteThreadHandle );
                }
            }
        }
    }
}
