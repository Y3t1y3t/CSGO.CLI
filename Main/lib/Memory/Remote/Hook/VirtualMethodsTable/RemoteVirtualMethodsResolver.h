#ifndef _MEMORY_REMOTEVIRTUALMETHODSRESOLVER_H_
#define _MEMORY_REMOTEVIRTUALMETHODSRESOLVER_H_

#pragma once

#include "../../Process/RemoteProcessService.h"

#include <vector>

namespace Memory
{
    class RemoteVirtualMethodsResolver
    {
        SharedRemoteProcessService _remoteProcessService;

    public:

        explicit RemoteVirtualMethodsResolver( SharedRemoteProcessService remoteProcessService );
        ~RemoteVirtualMethodsResolver( void ) = default;

        bool Resolve( const uintptr_t& virtualMethodsTablePtr, std::vector<uintptr_t>* virtualMethods ) const;
    };
}

#endif /* _MEMORY_REMOTEVIRTUALMETHODSRESOLVER_H_ */
