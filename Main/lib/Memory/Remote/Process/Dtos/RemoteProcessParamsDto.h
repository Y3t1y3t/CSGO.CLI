#ifndef _MEMORY_REMOTEPROCESSPARAMSDTO_H_
#define _MEMORY_REMOTEPROCESSPARAMSDTO_H_

#pragma once

#include "../Consts/RemoteProcessConsts.h"

#include <string>

namespace Memory
{
    class RemoteProcessParamsDto
    {
    public:
        DWORD       AccessRights;
        std::string ProcessName;
        std::string WindowName;
        std::string WindowClassName;

        explicit    RemoteProcessParamsDto( const std::string& processName = std::string(),
                                            const std::string& windowName = std::string(),
                                            const std::string& windowClassName = std::string(),
                                            DWORD accessRights = RemoteProcessConsts::AccessRights );
                    ~RemoteProcessParamsDto() = default;

        void        Invalidate();
    };
}

#endif /* _MEMORY_REMOTEPROCESSPARAMSDTO_H_ */
