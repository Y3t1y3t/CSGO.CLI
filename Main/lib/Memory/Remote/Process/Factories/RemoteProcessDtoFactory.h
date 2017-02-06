#ifndef _MEMORY_REMOTEPROCESSDTOFACTORY_H_
#define _MEMORY_REMOTEPROCESSDTOFACTORY_H_

#pragma once

#include "../Dtos/RemoteProcessDto.h"

#include <string>
#include <windows.h>
#include <memory>

namespace Memory
{
    class RemoteProcessDtoFactory
    {
    public:
        bool Create( const std::string& processName,
                     const std::string& windowName,
                     const std::string& windowClassName,
                     DWORD accessRigths,
                     std::unique_ptr<RemoteProcessDto>* processPtr ) const;

    private:

        bool GetProcessIdByProcessName( const std::string& processName, DWORD* processIdPtr ) const;
        bool GetProcessIdByWindow( const std::string& windowName, const std::string& windowClassName, DWORD* processIdPtr ) const;
        bool GetProcessHandleByProcessIdWithAccessRights( DWORD processId, DWORD accessRights, HANDLE* processHandlePtr ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSDTOFACTORY_H_ */
