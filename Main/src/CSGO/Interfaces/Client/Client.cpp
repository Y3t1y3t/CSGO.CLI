#include "Client.h"

namespace CSGO
{
    namespace Remote
    {
        ClientSharedData::ClientSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle ) :
            RemoteVirtualMethodsTableHookSharedData( virtualMethodsTablePtr, sharedOriginProcessHandle )
        {
        }
    }

    Client::Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance ) :
        InterfaceBase( remoteFunctionService, instance )
    {
    }

    std::unique_ptr<Client> gClient;
}
