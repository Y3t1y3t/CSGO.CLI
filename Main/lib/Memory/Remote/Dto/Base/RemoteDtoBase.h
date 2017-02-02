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
        std::vector<RemoteDtoMemberBase*>   _members;
        std::vector<byte>                   _data;
        uintptr_t                           _base;

    public:

        explicit    RemoteDtoBase( SharedRemoteProcessService remoteProcessService, const uintptr_t& base );
                    ~RemoteDtoBase( void ) = default;

        bool        Initialize( const size_t& inheritedClassSize );
        bool        Update( bool loadLazy = false );
        bool        ForceUpdate( const uintptr_t& base, bool loadLazy = false );

    private:

        void        SetBase( const uintptr_t& base );

        bool        UpdateData( void );
        bool        UpdateMembers( void );

        size_t      GetMaxDataSize( void );
    };
}

#endif /* _MEMORY_REMOTEDTOBASE_H_ */
