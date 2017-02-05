#ifndef _MEMORY_REMOTEPROCESSIDPROVIDER_H_
#define _MEMORY_REMOTEPROCESSIDPROVIDER_H_

#pragma once

#include <string>
#include <windows.h>

namespace Memory
{
    class RemoteProcessIdProvider
    {
    public:
        bool ProvideProcessIdByProcessName( std::string& processName, DWORD *processId ) const;
        bool ProvideProcessIdByWindow( std::string& windowName, std::string& windowClassName, DWORD *processId ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSIDPROVIDER_H_ */
