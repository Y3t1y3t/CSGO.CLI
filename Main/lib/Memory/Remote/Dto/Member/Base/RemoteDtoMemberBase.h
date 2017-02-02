#ifndef _MEMORY_REMOTEDTOMEMBERBASE_H_
#define _MEMORY_REMOTEDTOMEMBERBASE_H_

#pragma once

#include "../../../Process/RemoteProcessService.h"

#include <windows.h>
#include <vector>
#include <typeinfo>

namespace Memory
{
    class RemoteDtoMemberBase
    {
        const size_t    Identifier = typeid( RemoteDtoMemberBase ).hash_code();

        size_t          _offset;

    public:

        explicit        RemoteDtoMemberBase( const size_t& offset );
        virtual         ~RemoteDtoMemberBase( void ) = default;

        virtual bool    OnUpdate( SharedRemoteProcessService remoteProcessService, std::vector<byte>* data ) = 0;
        virtual size_t  GetSize( void ) const = 0;

        size_t          GetOffset( void ) const;
        size_t          GetDataSize( void ) const;
    };
}

#endif /* _MEMORY_REMOTEDTOMEMBERBASE_H_ */
