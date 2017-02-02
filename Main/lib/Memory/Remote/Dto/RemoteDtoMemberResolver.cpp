#include "RemoteDtoMemberResolver.h"

namespace Memory
{
    bool RemoteDtoMemberResolver::Parse( const uintptr_t& baseClassPtr, size_t inheritedClassSize, std::vector<RemoteDtoMemberBase*> *members ) const
    {
        auto sizeCount = size_t( floor( inheritedClassSize / sizeof( size_t ) ) );

        auto inheritedObjStart = baseClassPtr + RemoteDtoBaseSize;
        auto inheritedObjPtr = reinterpret_cast< size_t* >( inheritedObjStart );

        for( auto count = 0U; count < sizeCount; ++count ) {
            if( inheritedObjPtr[ count ] == RemoteDtoMemberIdentifier ) {
                auto member = reinterpret_cast< RemoteDtoMemberBase* >( &inheritedObjPtr[ count - 1U ] );
                members->emplace_back( member );
            }
        }

        return !members->empty();
    }
}
