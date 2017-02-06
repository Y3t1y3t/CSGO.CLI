#include "EngineVGui.h"

namespace CSGO
{
    EngineVGui::EngineVGui( const Memory::SharedRemoteFunctionService& remoteFunctionService, const uintptr_t& instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }
    
    std::unique_ptr<EngineVGui> gEngineVGui;
}
