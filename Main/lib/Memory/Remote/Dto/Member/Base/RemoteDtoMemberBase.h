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
        virtual         ~RemoteDtoMemberBase() = default;

        virtual bool    OnUpdate( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data ) = 0;
        virtual size_t  GetSize() const = 0;

        size_t          GetOffset() const;
        size_t          GetDataSize() const;
    };
}

#endif /* _MEMORY_REMOTEDTOMEMBERBASE_H_ */
