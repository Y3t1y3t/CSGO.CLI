#ifndef _MEMORY_REMOTEDTOBASE_H_
#define _MEMORY_REMOTEDTOBASE_H_

#pragma once

#include "../Member/Base/RemoteDtoMemberBase.h"

#include "../../Process/RemoteProcessService.h"

#include <vector>
#include <windows.h>

namespace Memory
{
    class RemoteDtoBase
    {
        SharedRemoteProcessService          _remoteProcessService;
        std::vector<RemoteDtoMemberBase*>   _members = std::vector<RemoteDtoMemberBase*>();
        std::vector<byte>                   _data = std::vector<byte>();

    public:

        explicit RemoteDtoBase( SharedRemoteProcessService remoteProcessService );
        ~RemoteDtoBase( void ) = default;

        bool    Initialize( const size_t& inheritedClassSize );
        bool    Update( const uintptr_t& base );
    };
}

#endif /* _MEMORY_REMOTEDTOBASE_H_ */
