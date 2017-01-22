#ifndef _MEMORY_REMOTEFUNCTIONSERVICE_H_
#define _MEMORY_REMOTEFUNCTIONSERVICE_H_

#pragma once

#include "RemoteFunction.h"
#include "RemoteFunctionExecuter.h"
#include "RemoteFunctionFactory.h"

#include <memory>

namespace Memory
{
    class RemoteFunctionService;

    typedef std::shared_ptr<RemoteFunctionService> SharedRemoteFunctionService;

    class RemoteFunctionService
    {
        std::unique_ptr<RemoteFunctionExecuter> _functionExecuter;
        std::unique_ptr<RemoteFunctionFactory>  _functionFactory;

    public:

        explicit RemoteFunctionService( SharedRemoteProcessService remoteProcessSerivce );

        bool Create( LPTHREAD_START_ROUTINE functionRoutine, std::unique_ptr<RemoteFunction>* function ) const;
        bool Create( LPTHREAD_START_ROUTINE functionRoutine, LPVOID data, size_t size, std::unique_ptr<RemoteFunction>* function ) const;
        
        bool Execute( const std::unique_ptr<RemoteFunction>& function ) const;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONSERVICE_H_ */
