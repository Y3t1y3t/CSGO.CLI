#ifndef _MEMORY_REMOTEPROCESSHANDLEPROVIDER_H_
#define _MEMORY_REMOTEPROCESSHANDLEPROVIDER_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteProcessHandleProvider
    {
    public:
        bool ProvideProcessHandleByProcessIdWithAccessRights( DWORD& processId, DWORD& accessRights, HANDLE *processHandle ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSHANDLEPROVIDER_H_ */
