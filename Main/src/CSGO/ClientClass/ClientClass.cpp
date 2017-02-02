#include "ClientClass.h"

namespace CSGO
{
    ClientClass::ClientClass( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base ) :
        RemoteDtoBase( remoteProcessService, base )
    {
        Initialize( sizeof( ClientClass ) );
    }
}
