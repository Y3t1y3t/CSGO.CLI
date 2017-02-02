#include "Hooks/Client/ClientHook.h"
#include "Hooks/HooksService.h"

#include "../CSGO/ClientClass/ClientClass.h"
#include "../CSGO/Interfaces/InterfacesService.h"

#include <cstdlib>
#include <iostream>
#include <thread>

int main()
{
    auto remoteProcessService = std::make_shared<Memory::RemoteProcessService>();
    auto remoteFuntionService = std::make_shared<Memory::RemoteFunctionService>( remoteProcessService );

    if( !remoteProcessService->Attach( Memory::RemoteProcessParamsDto( "csgo.exe", "Counter-Strike: Global Offensive" ) ) ) {
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

    auto hooksService = std::make_unique<CLI::HooksService>( remoteProcessService, remoteFuntionService );
    if( !hooksService->Register<CLI::ClientHook>( *CSGO::gClient->GetInstance() ) ) {
        std::cout << "failed to register clienthook." << std::endl;
        system( "pause" );
        return -3;
    }

    std::unique_ptr<CSGO::ClientClass> clientClassPtr;
    while( remoteProcessService->IsValid() ) {

        auto isConnected = CSGO::gEngineClient->IsConnected();
        if( isConnected && clientClassPtr == nullptr ) {

            clientClassPtr = std::make_unique<CSGO::ClientClass>( remoteProcessService, CSGO::gClient->GetAllClasses() );
            if( clientClassPtr->Update() ) {
                for( auto clientClass = clientClassPtr.get(); clientClass != nullptr; clientClass = clientClass->Next.GetPtr() ) {
                    clientClass->Update();
                    std::cout << "Name: " << clientClass->Name.GetPtr() << ", Id: " << clientClass->Id.Get() << std::endl;
                }
            }
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    std::cout << "process closed." << std::endl;
    system( "pause" );

    return 0;
}