#ifndef _MEMORY_REMOTEPROCESSMODULEPROVIDER_H_
#define _MEMORY_REMOTEPROCESSMODULEPROVIDER_H_

#pragma once

#include "../Dtos/RemoteProcessModuleDto.h"

#include <windows.h>
#include <string>
#include <memory>

namespace Memory
{
    class RemoteProcessModuleDtoFactory
    {
    public:
        bool Create( DWORD processId, const std::string& moduleName, std::unique_ptr<RemoteProcessModuleDto>* modulePtr ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSMODULEPROVIDER_H_ */
