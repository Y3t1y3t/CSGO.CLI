#ifndef _MEMORY_REMOTEHOOKSERVICE_H_
#define _MEMORY_REMOTEHOOKSERVICE_H_

#pragma once

#include "VirtualMethodsTable/RemoteVirtualMethodsTableHookFactory.h"

namespace Memory
{
    class RemoteHookService;

    typedef std::shared_ptr<RemoteHookService> SharedRemoteHookService;

    class RemoteHookService
    {
        std::unique_ptr<RemoteVirtualMethodsTableHookFactory> _remoteVirtualMethodsTableHookFactory;

    public:

        explicit RemoteHookService( SharedRemoteProcessService remoteProcessService );
        ~RemoteHookService( void ) = default;

        template<typename T>
        bool Create( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::unique_ptr<RemoteVirtualMethodsTableHook>* hook );
    };

    template <typename T>
    bool RemoteHookService::Create(const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::unique_ptr<RemoteVirtualMethodsTableHook>* hook)
    {
        return _remoteVirtualMethodsTableHookFactory->Create<T>( virtualMethodsTablePtr, sharedOriginProcessHandle, hook );
    }
}

#endif /* _MEMORY_REMOTEHOOKSERVICE_H_ */
