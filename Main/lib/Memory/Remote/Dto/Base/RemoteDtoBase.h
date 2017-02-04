#ifndef _MEMORY_REMOTEDTOBASE_H_
#define _MEMORY_REMOTEDTOBASE_H_

#pragma once

#include "../Member/Base/RemoteDtoMemberBase.h"

#include "../../Process/RemoteProcessService.h"

#include <vector>
#include <windows.h>
#include <list>

namespace Memory
{
    class RemoteDtoBase
    {
        SharedRemoteProcessService          _remoteProcessService;
        std::list<RemoteDtoMemberBase*>     _members;
        std::vector<byte>                   _data;
        uintptr_t                           _base;

    public:

        explicit    RemoteDtoBase( SharedRemoteProcessService remoteProcessService, const uintptr_t& base );
                    ~RemoteDtoBase() = default;

        bool        Initialize( const size_t& inheritedClassSize );
        bool        Update( size_t level = 0 );
        bool        ForceUpdate( const uintptr_t& base, size_t level = 0 );

    private:

        void        SetBase( const uintptr_t& base );

        bool        UpdateData();
        bool        UpdateMembers( size_t level );
    };
}

#endif /* _MEMORY_REMOTEDTOBASE_H_ */
