#ifndef _MEMORY_REMOTEFUNCTIONEXECUTER_H_
#define _MEMORY_REMOTEFUNCTIONEXECUTER_H_

#pragma once

#include "RemoteFunction.h"

namespace Memory
{
    class RemoteFunctionExecuter
    {
        SharedRemoteProcessService _remoteProcessService;

    public:

        explicit RemoteFunctionExecuter( SharedRemoteProcessService remoteProcessService );
        ~RemoteFunctionExecuter( void ) = default;

        bool Execute( const std::unique_ptr<RemoteFunction>& data ) const;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONEXECUTER_H_ */
