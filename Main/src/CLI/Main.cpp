#include "Hooks/Client/ClientHook.h"

#include "Hooks/HooksService.h"

#include "../CSGO/Interfaces/InterfacesService.h"
#include "../CSGO/ClientClass/ClientClassService.h"

#include <cstdlib>
#include <iostream>
#include <thread>

int main()
{
    auto remoteProcessService = std::make_shared<Memory::RemoteProcessService>();
    auto remoteFuntionService = std::make_shared<Memory::RemoteFunctionService>( remoteProcessService );

    if( !remoteProcessService->Attach("csgo.exe", "Counter-Strike: Global Offensive" ) ) {
        std::cout << "failed to attach." << std::endl;
        system( "pause" );
        return -1;
    }

    auto interfacesService = std::make_unique<CSGO::InterfacesService>( remoteFuntionService );
    if( !interfacesService->Register( &CSGO::gClient )
        || !interfacesService->Register( &CSGO::gEngineClient ) ) {
        std::cout << "failed to register interfaces." << std::endl;
        system( "pause" );
        return -2;
    }

    /*
        auto clientClassService = std::make_unique<CSGO::ClientClassService>( remoteProcessService, CSGO::gClient->GetAllClasses() );
        std::cout << std::hex << clientClassService->GetRecvPropOffset( "DT_BaseEntity", "m_vecOrigin" ) << std::endl;
    */

    auto hooksService = std::make_unique<CLI::HooksService>( remoteProcessService, remoteFuntionService );
    if( !hooksService->Register<CLI::ClientHook>( CSGO::gClient->GetInstance() ) ) {
        std::cout << "failed to register clienthook." << std::endl;
        system( "pause" );
        return -3;
    }

    while( remoteProcessService->IsAlive() ) {
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    std::cout << "process closed." << std::endl;
    system( "pause" );

    return 0;
}
