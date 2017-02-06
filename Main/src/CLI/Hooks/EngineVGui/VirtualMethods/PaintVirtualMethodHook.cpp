#include "PaintVirtualMethodHook.h"

#include "../SharedData/EngineVGuiHookSharedData.h"

#include <iostream> //TODO: Remove

namespace CLI
{
    PaintVirtualMethodHook* PaintVirtualMethodHook::_self = nullptr;

    PaintVirtualMethodHook::PaintVirtualMethodHook( Memory::SharedRemoteProcessService remoteProcessService, Memory::SharedRemoteFunctionService remoteFunctionService )
    {
        if( _self != nullptr )
            throw std::exception( "only one instance can be created at the same time." );

        _self = this;
        _remoteProcessService = remoteProcessService;

        Index = 14;
        Callback = FunctionCallback;
        GetVirtualMethodData = ( [] ( void* sharedData ) -> Memory::RemoteVirtualMethodsTableHookSharedData::VirtualMethodData* {
            return &static_cast< EngineVGuiHookSharedData * >( sharedData )->PaintData;
        } );

        remoteFunctionService->Create( LPTHREAD_START_ROUTINE( VirtualMethodCallback ), &RemoteCallback );
    }

    PaintVirtualMethodHook::~PaintVirtualMethodHook()
    {
        _self = nullptr;
    }

    DWORD PaintVirtualMethodHook::FunctionCallback( LPVOID paramsPtr )
    {
        if( paramsPtr == nullptr )
            return 1;

        EngineVGuiHookSharedData::PaintVirtualMethod::Parameters params;
        if( !_self->_remoteProcessService->Read( paramsPtr, &params ) )
            return 2;

        std::cout << params.PaintMode << std::endl;
        return 0;
    }

#pragma optimize( "", off )
    void PaintVirtualMethodHook::VirtualMethodCallback( void* _ecx, void*, size_t paintMode )
    {
        if( _ecx != nullptr ) {
            auto sharedData = reinterpret_cast< EngineVGuiHookSharedData* >( *reinterpret_cast< uintptr_t* >( _ecx ) - sizeof( EngineVGuiHookSharedData ) );

            using PaintFn = void( __thiscall* )( uintptr_t, size_t );
            PaintFn( sharedData->PaintData.Function )( sharedData->VirtualMethodsTablePtr, paintMode );

            sharedData->PaintData.Params.PaintMode = paintMode;

            auto remoteThreadHandle = sharedData->Imports.Kernel32.CreateRemoteThread( sharedData->SharedOriginProcessHandle, nullptr, NULL, sharedData->PaintData.Callback, &sharedData->PaintData.Params, NULL, nullptr );
            if( remoteThreadHandle != nullptr ) {
                if( sharedData->Imports.Kernel32.WaitForSingleObject( remoteThreadHandle, INFINITE ) == WAIT_OBJECT_0 && remoteThreadHandle != INVALID_HANDLE_VALUE ) {
                    sharedData->Imports.Kernel32.CloseHandle( remoteThreadHandle );
                }
            }
        }
    }
#pragma optimize( "", on )
}
