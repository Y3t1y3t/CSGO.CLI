#ifndef _MEMORY_REMOTEDTOMEMBERBASE_H_
#define _MEMORY_REMOTEDTOMEMBERBASE_H_

#pragma once

#include <windows.h>
#include <vector>
#include <typeinfo>

namespace Memory
{
    class RemoteDtoMemberBase
    {
        const size_t        Identifier = typeid( RemoteDtoMemberBase ).hash_code();

    protected:

        size_t              _offset;
        size_t              _size;
        std::vector<byte>*  _data;

    public:

        explicit    RemoteDtoMemberBase( const size_t& offset, const size_t& size, std::vector<byte>* data = nullptr );
                    ~RemoteDtoMemberBase( void ) = default;

        size_t      GetOffset( void ) const;
        size_t      GetSize( void ) const;

        void        SetData( std::vector<byte>* data );
    };
}

#endif /* _MEMORY_REMOTEDTOMEMBERBASE_H_ */
