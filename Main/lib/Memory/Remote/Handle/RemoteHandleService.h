#ifndef _MEMORY_REMOTEHANDLESERVICE_H_
#define _MEMORY_REMOTEHANDLESERVICE_H_

#pragma once

#include "../../../Util/NT.h"

#include <vector>
#include <functional>

namespace Memory
{
    class RemoteHandleService
    {
        enum class SystemInfoClass
        {
            SystemHandleInformation = 16
        };

    public:

        struct SystemHandle
        {
            USHORT  UniqueProcessId;
            USHORT  CreatorBackTraceIndex;
            UCHAR   ObjectTypeIndex;
            UCHAR   HandleAttributes;
            USHORT  HandleValue;
            PVOID   Object;
            ULONG   GrantedAccess;
        };

        struct SystemHandleInformation
        {
            ULONG           HandleCount;
            SystemHandle    Handles[1];
        };

        bool GetSystemHandlesForProcessId( ULONG processId, std::vector<SystemHandle> *handles ) const;
    };
}

#endif /* _MEMORY_REMOTEHANDLESERVICE_H_ */
