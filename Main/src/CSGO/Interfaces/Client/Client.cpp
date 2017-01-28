#include "Client.h"

namespace CSGO
{
    namespace Remote
    {

    }

    Client::Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }

    std::unique_ptr<Client> gClient;
}
