#ifndef _MEMORY_REMOTEDTOSIMPLEMEMBER_H_
#define _MEMORY_REMOTEDTOSIMPLEMEMBER_H_

#pragma once

#include "Base/RemoteDtoMemberBase.h"

namespace Memory
{
    template <class T>
    class RemoteDtoSimpleMember : public RemoteDtoMemberBase
    {
    public:
        explicit    RemoteDtoSimpleMember( const size_t& offset );
                    ~RemoteDtoSimpleMember( void ) = default;

        T           Get( void );
        void        Get( T* out );
    };

    template <class T>
    RemoteDtoSimpleMember<T>::RemoteDtoSimpleMember( const size_t& offset ) :
        RemoteDtoMemberBase( offset, sizeof( T ) )
    {
    }

    template <class T>
    T RemoteDtoSimpleMember<T>::Get()
    {
        return *reinterpret_cast< T* >( &_data->at( _offset ) );
    }

    template <class T>
    void RemoteDtoSimpleMember<T>::Get( T* out )
    {
        *out = *reinterpret_cast< T* >( &_data->at( _offset ) );
    }

    typedef RemoteDtoSimpleMember<float>    RemoteFloat;
    typedef RemoteDtoSimpleMember<int>      RemoteInt;
    typedef RemoteDtoSimpleMember<double>   RemoteDouble;
    typedef RemoteDtoSimpleMember<size_t>   RemoteSize;
}

#endif /* _MEMORY_REMOTEDTOSIMPLEMEMBER_H_ */
