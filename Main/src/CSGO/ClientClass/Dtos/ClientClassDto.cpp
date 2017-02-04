#include "ClientClassDto.h"

namespace CSGO
{
    ClientClassDto::ClientClassDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base ) :
        RemoteDtoBase( remoteProcessService, base )
    {
        Initialize( sizeof( ClientClassDto ) );
    }
}
