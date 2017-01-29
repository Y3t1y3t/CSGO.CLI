#ifndef _MEMORY_REMOTEVIRTUALMETHODHOOKBASE_H_
#define _MEMORY_REMOTEVIRTUALMETHODHOOKBASE_H_

#pragma once

#include "SharedData/RemoteVirtualMethodsTableHookSharedData.h"

#include "../../Function/RemoteFunction.h"

#include <functional>

namespace Memory
{
    class RemoteVirtualMethodHookBase
    {
    public:
        size_t                          Index;
        LPTHREAD_START_ROUTINE          Callback;
        std::unique_ptr<RemoteFunction> RemoteCallback;
        std::function<RemoteVirtualMethodsTableHookSharedData::VirtualMethodData *( void *sharedData )> GetVirtualMethodData;
    };
}

#endif /* _MEMORY_REMOTEVIRTUALMETHODHOOKBASE_H_ */
