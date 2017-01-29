#include "HookBase.h"

namespace CLI
{
    HookBase::HookBase(
        Memory::SharedRemoteProcessService remoteProcessService,
        Memory::SharedRemoteFunctionService remoteFunctionService,
        Memory::SharedRemoteHookService remoteHookService ) :
        _remoteProcessService( remoteProcessService ),
        _remoteFunctionService( remoteFunctionService ),
        _remoteHookService( remoteHookService )
    {
    }
}
