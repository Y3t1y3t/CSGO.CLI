#ifndef _MEMORY_REMOTEPROCESSMODULEDTO_H_
#define _MEMORY_REMOTEPROCESSMODULEDTO_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteProcessModuleDto
    {
    public:
        RemoteProcessModuleDto( uintptr_t moduleBase, size_t moduleSize );
        ~RemoteProcessModuleDto() = default;

        uintptr_t   Base;
        size_t      Size;
    };
}

#endif /* _MEMORY_REMOTEPROCESSMODULEDTO_H_ */
