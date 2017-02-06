#ifndef _MEMORY_REMOTEPROCESSDTO_H_
#define _MEMORY_REMOTEPROCESSDTO_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteProcessDto
    {
    public:
        RemoteProcessDto( DWORD processId, HANDLE processHandle );
        ~RemoteProcessDto() = default;

        DWORD       Id;
        HANDLE      Handle;
    };
}

#endif /* _MEMORY_REMOTEPROCESSDTO_H_ */
