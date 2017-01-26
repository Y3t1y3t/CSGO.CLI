#include "../CSGO/Interfaces/Interfaces.h"

#include "../../lib/Memory/Remote/Process/RemoteProcessService.h"
#include "../../lib/Memory/Remote/Function/RemoteFunctionService.h"


#include <cstdlib>
#include <memory>
#include <iostream>
#include <thread>

#include "../../lib/Memory/Remote/Hook/VirtualMethodsTable/RemoteVirtualMethodsTableHookFactory.h"

auto remoteProcessService = std::make_shared<Memory::RemoteProcessService>(); //TODO Hook Wrapper and stuff

inline void hkCreateMove( LPVOID paramsPtr)
{
    if( paramsPtr == nullptr )
        return;

    CSGO::Remote::ClientSharedData::CreateMoveHook::Parameters params;
    if( !remoteProcessService->Read( paramsPtr, &params ) )
        return;

    std::cout << "hkCreateMove called. seq: " << params.Number << std::endl;
}

int main()
{
    if( !remoteProcessService->Attach( Memory::RemoteProcessParamsDto( "csgo.exe", "Counter-Strike: Global Offensive" ) ) ) {
        std::cout << "failed to attach." << std::endl;
        system( "pause" );
        return -1;
    }

    auto remoteFuntionService = std::make_shared<Memory::RemoteFunctionService>( remoteProcessService );
    if( !CSGO::gInterfaces->OnLoad( remoteFuntionService ) ) {
        std::cout << "failed to load interfaces." << std::endl;
        system( "pause" );
        return -2;
    }

    std::unique_ptr<Memory::RemoteVirtualMethodsTableHook> clientHook;
    std::unique_ptr<Memory::RemoteFunction> createMove;

    if( !remoteFuntionService->Create( LPTHREAD_START_ROUTINE(CSGO::Remote::hkCreateMove ), &createMove ) )
        return -3;

    auto originProcessHandle = OpenProcess( PROCESS_REMOTE, FALSE, GetCurrentProcessId() );
    auto sharedProcessHandle = remoteProcessService->ShareHandle( originProcessHandle );

    auto remoteVMTHookFactory = std::make_shared<Memory::RemoteVirtualMethodsTableHookFactory>( remoteProcessService );
    if( remoteVMTHookFactory->Create<CSGO::Remote::ClientSharedData>( CSGO::gClient->GetInstance(), sharedProcessHandle, &clientHook ) ) {

        CSGO::Remote::ClientSharedData sharedData;
        if( clientHook->GetSharedDataPtrValue( &sharedData ) ) {

            sharedData.CreateMove.Callback = LPTHREAD_START_ROUTINE( hkCreateMove );
            sharedData.CreateMove.Function = clientHook->GetVirtualMethodPtr( 21 );

            clientHook->SetVirtualMethodPtr( 21, uintptr_t( createMove->GetFunctionPtr() ) );
            clientHook->SetSharedDataPtrValue( sharedData );

            clientHook->SetHook();
        }
    }

    while( remoteProcessService->IsValid() ) {
        /*auto isConnected = CSGO::gEngineClient->IsConnected();
        if( isConnected )
            CSGO::gEngineClient->ClientCmdUnrestricted( "say CSGO.Extern doing it." );

        std::cout << "IsConnected: " << ( isConnected ? "true" : "false" ) << std::endl;*/
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    std::cout << "process closed." << std::endl;
    system( "pause" );

    return 0;
}
