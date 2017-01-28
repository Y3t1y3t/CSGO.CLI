#include "Hooks/Client/ClientHook.h"

#include "../CSGO/Interfaces/Interfaces.h"

#include "../../lib/Memory/Remote/Process/RemoteProcessService.h"
#include "../../lib/Memory/Remote/Function/RemoteFunctionService.h"
#include "../../lib/Memory/Remote/Hook/RemoteHookService.h"

#include <cstdlib>
#include <memory>
#include <iostream>
#include <thread>

int main()
{
    auto remoteProcessService = std::make_shared<Memory::RemoteProcessService>();
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

    auto originProcessHandle = OpenProcess( PROCESS_REMOTE, FALSE, GetCurrentProcessId() );
    auto sharedProcessHandle = remoteProcessService->GetSharedHandle( originProcessHandle );

    auto remoteHookService = std::make_shared<Memory::RemoteHookService>( remoteProcessService );

    if( !CLI::gClientHook->OnLoad( remoteProcessService, remoteFuntionService, remoteHookService, CSGO::gClient->GetInstance(), sharedProcessHandle ) ) {
        std::cout << "failed to load clienthook." << std::endl;
        system( "pause" );
        return -3;
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
