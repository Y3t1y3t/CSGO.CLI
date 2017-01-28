#ifndef _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKSHAREDDATA_H_
#define _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKSHAREDDATA_H_

#pragma once

#include "../../Base/SharedData/RemoteHookSharedDataBase.h"

#include <windows.h>

namespace Memory
{
    class RemoteVirtualMethodsTableHookSharedData : public RemoteHookSharedDataBase
    {
    public:
        class VirtualMethodData
        {
        public:
            uintptr_t               Function;
            LPTHREAD_START_ROUTINE  Callback;
        };

        explicit RemoteVirtualMethodsTableHookSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle );
        ~RemoteVirtualMethodsTableHookSharedData( void ) = default;

        Imports     Imports;

        uintptr_t   VirtualMethodsTablePtr;
        HANDLE      SharedOriginProcessHandle;
    };
}

#endif /* _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKSHAREDDATA_H_ */
