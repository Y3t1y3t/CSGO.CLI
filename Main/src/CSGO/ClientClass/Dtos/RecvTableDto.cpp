#include "RecvTableDto.h"

namespace CSGO
{
    RecvTableDto::RecvPropDto::RecvPropDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base ) :
        RemoteDtoBase( remoteProcessService, base )
    {
        Initialize( sizeof( RecvPropDto ) );
    }

    RecvTableDto::RecvTableDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base ) :
        RemoteDtoBase( remoteProcessService, base )
    {
        Initialize( sizeof( RecvTableDto ) );
    }
}
