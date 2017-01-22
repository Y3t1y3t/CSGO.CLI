#include "../CSGO/Interfaces/Interfaces.h"

#include "../../lib/Memory/Remote/RemoteProcessService.h"
#include "../../lib/Memory/Remote/Function/RemoteFunctionService.h"

#include <cstdlib>
#include <memory>
#include <iostream>
#include <thread>

int main()
{
    auto remoteProcessService = std::make_shared<Memory::RemoteProcessService>();
    if( !remoteProcessService->Attach( Memory::RemoteProcessParamsDto( "csgo.exe" ) ) ) {
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

    while( remoteProcessService->IsValid() ) {
        std::cout << "IsConnected: " << ( CSGO::gEngineClient->IsConnected() ? "true" : "false" ) << std::endl;
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    std::cout << "process closed." << std::endl;
    system( "pause" );

    return 0;
}
