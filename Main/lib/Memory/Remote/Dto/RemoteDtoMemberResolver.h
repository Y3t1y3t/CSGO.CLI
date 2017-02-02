#ifndef _MEMORY_REMOTEDTOMEMBERRESOLVER_H_
#define _MEMORY_REMOTEDTOMEMBERRESOLVER_H_

#pragma once

#include "Member/Base/RemoteDtoMemberBase.h"
#include "Base/RemoteDtoBase.h"

namespace Memory
{
    class RemoteDtoMemberResolver
    {
        const uintptr_t RemoteDtoBaseSize = sizeof( RemoteDtoBase );
        const size_t    RemoteDtoMemberIdentifier = typeid( RemoteDtoMemberBase ).hash_code();

    public:

        bool Parse( const uintptr_t& baseClassPtr, size_t inheritedClassSize, std::vector<RemoteDtoMemberBase*> *members ) const;
    };
}

#endif /* _MEMORY_REMOTEDTOMEMBERRESOLVER_H_ */
