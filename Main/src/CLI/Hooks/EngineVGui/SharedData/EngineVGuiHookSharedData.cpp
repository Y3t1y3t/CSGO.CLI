#include "EngineVGuiHookSharedData.h"

namespace CLI
{
    EngineVGuiHookSharedData::EngineVGuiHookSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle ) :
        RemoteVirtualMethodsTableHookSharedData( virtualMethodsTablePtr, sharedOriginProcessHandle )
    {
    }
}
