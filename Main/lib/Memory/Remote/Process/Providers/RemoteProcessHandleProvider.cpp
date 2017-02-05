#include "RemoteProcessHandleProvider.h"

namespace Memory
{
    bool RemoteProcessHandleProvider::ProvideProcessHandleByProcessIdWithAccessRights( DWORD& processId, DWORD& accessRights, HANDLE* processHandle ) const
    {
        if( processId == 0 )
            return false;
        return (*processHandle = OpenProcess(accessRights, FALSE, processId)) != nullptr;
    }
}
