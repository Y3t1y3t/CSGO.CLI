#include "ClientHookSharedData.h"

namespace CLI
{
    ClientHookSharedData::ClientHookSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle ) :
        RemoteVirtualMethodsTableHookSharedData( virtualMethodsTablePtr, sharedOriginProcessHandle )
    {
    }
}