#include "RemoteDtoMemberBase.h"

namespace Memory
{
    RemoteDtoMemberBase::RemoteDtoMemberBase( const size_t& offset ) :
        _offset( offset )
    {
    }

    size_t RemoteDtoMemberBase::GetOffset( void ) const
    {
        return _offset;
    }

    size_t RemoteDtoMemberBase::GetDataSize( void ) const
    {
        return GetOffset() + GetSize();
    }
}