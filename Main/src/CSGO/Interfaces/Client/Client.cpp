#include "Client.h"

namespace CSGO
{
    Client::Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }

    std::unique_ptr<Client> gClient;
}
