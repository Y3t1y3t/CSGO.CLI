#ifndef _MEMORY_REMOTEPROCESSTHREADSPROVIDER_H_
#define _MEMORY_REMOTEPROCESSTHREADSPROVIDER_H_

#pragma once

#include <vector>
#include <windows.h>

namespace Memory
{
    class RemoteProcessThreadsProvider
    {
    public:
        bool Provide( DWORD processId, std::vector<DWORD>* threadIdsPtr ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSTHREADSPROVIDER_H_ */
