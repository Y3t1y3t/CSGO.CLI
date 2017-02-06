#include "RemoteProcessDto.h"

namespace Memory
{
    RemoteProcessDto::RemoteProcessDto( DWORD processId, HANDLE processHandle ) :
        Id( processId ),
        Handle( processHandle )
    {
    }
}
