#ifndef _MEMORY_REMOTEDTOMEMBERRESOLVER_H_
#define _MEMORY_REMOTEDTOMEMBERRESOLVER_H_

#pragma once

#include "Member/Base/RemoteDtoMemberBase.h"
#include "Base/RemoteDtoBase.h"

#include <list>

namespace Memory
{
    class RemoteDtoMemberResolver
    {
        const uintptr_t RemoteDtoBaseSize = sizeof( RemoteDtoBase );
        const size_t    RemoteDtoMemberIdentifier = typeid( RemoteDtoMemberBase ).hash_code();

    public:

        bool Resolve( const uintptr_t& baseClassPtr, size_t inheritedClassSize, size_t *maxDataSize, std::list<RemoteDtoMemberBase*> *members ) const;
    };
}

#endif /* _MEMORY_REMOTEDTOMEMBERRESOLVER_H_ */
