#include "RemoteProcessParamsDto.h"

namespace Memory
{
    RemoteProcessParamsDto::RemoteProcessParamsDto( const std::string& processName, const std::string& windowName, const std::string& windowClassName, DWORD accessRights )
    {
        ProcessName = processName;
        WindowName = windowName;
        WindowClassName = windowClassName;
        AccessRights = accessRights;
    }

    void RemoteProcessParamsDto::Invalidate()
    {
        ProcessName.clear();
        WindowName.clear();
        WindowClassName.clear();
        AccessRights = 0;
    }
}
