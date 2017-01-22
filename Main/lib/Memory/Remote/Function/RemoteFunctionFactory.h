#ifndef _MEMORY_REMOTEFUNCTIONFACTORY_H_
#define _MEMORY_REMOTEFUNCTIONFACTORY_H_

#pragma once

#include "../RemoteProcessService.h"

#include "RemoteFunction.h"

namespace Memory
{
    class RemoteFunctionFactory
    {
        SharedRemoteProcessService  _remoteProcessService;

    public:

        explicit RemoteFunctionFactory( SharedRemoteProcessService remoteProcessService );

        bool Create( LPTHREAD_START_ROUTINE functionRoutine, std::unique_ptr<RemoteFunction>* function ) const;
        bool Create( LPTHREAD_START_ROUTINE functionRoutine, LPVOID data, size_t size, std::unique_ptr<RemoteFunction>* function ) const;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONFACTORY_H_ */