#include "RemoteVirtualMethodsTableHookSharedData.h"

namespace Memory
{
    RemoteVirtualMethodsTableHookSharedData::RemoteVirtualMethodsTableHookSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle )
    {
        VirtualMethodsTablePtr = virtualMethodsTablePtr;
        SharedOriginProcessHandle = sharedOriginProcessHandle;
    }
}
