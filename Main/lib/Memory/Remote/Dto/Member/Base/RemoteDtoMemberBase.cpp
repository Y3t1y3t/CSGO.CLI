#include "RemoteDtoMemberBase.h"

namespace Memory
{
    RemoteDtoMemberBase::RemoteDtoMemberBase( const size_t& offset, const size_t& size, std::vector<byte>* data ) :
        _offset( offset ),
        _size( size ),
        _data( data )
    {
    }

    size_t RemoteDtoMemberBase::GetOffset( void ) const
    {
        return _offset;
    }

    size_t RemoteDtoMemberBase::GetSize( void ) const
    {
        return _size;
    }

    void RemoteDtoMemberBase::SetData( std::vector<byte>* data )
    {
        _data = data;
    }
}
