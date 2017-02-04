#include "RemoteDtoMemberResolver.h"

#include <algorithm>

namespace Memory
{
    bool RemoteDtoMemberResolver::Resolve( const uintptr_t& baseClassPtr, size_t inheritedClassSize, size_t *maxDataSize, std::list<RemoteDtoMemberBase*> *members ) const
    {
        auto sizeCount = size_t( floor( inheritedClassSize / sizeof( size_t ) ) );

        auto inheritedObjStart = baseClassPtr + RemoteDtoBaseSize;
        auto inheritedObjPtr = reinterpret_cast< size_t* >( inheritedObjStart );

        for( auto count = 0U; count < sizeCount; ++count ) {

            if( inheritedObjPtr[ count ] != RemoteDtoMemberIdentifier )
                continue;

            auto member = reinterpret_cast< RemoteDtoMemberBase* >( &inheritedObjPtr[ count - 1U ] );
            *maxDataSize = std::max<size_t>( member->GetDataSize(), *maxDataSize );

            members->emplace_back( member );
        }

        return !members->empty();
    }
}
