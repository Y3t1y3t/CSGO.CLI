#include "RemoteDtoMemberBase.h"

namespace Memory
{
    RemoteDtoMemberBase::RemoteDtoMemberBase( const size_t& offset ) :
        _offset( offset )
    {
    }

    size_t RemoteDtoMemberBase::GetOffset() const
    {
        return _offset;
    }

    size_t RemoteDtoMemberBase::GetDataSize() const
    {
        return GetOffset() + GetSize();
    }
}