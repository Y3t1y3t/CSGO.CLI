#ifndef _MEMORY_REMOTEPROCESSCONSTS_H_
#define _MEMORY_REMOTEPROCESSCONSTS_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteProcessConsts
    {
    public:
        static const DWORD AccessRights = ( PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_DUP_HANDLE );
    };
}

#endif /* _MEMORY_REMOTEPROCESSCONSTS_H_ */
