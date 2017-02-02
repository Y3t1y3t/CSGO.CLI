#ifndef _MEMORY_REMOTEDTOSIMPLEMEMBER_H_
#define _MEMORY_REMOTEDTOSIMPLEMEMBER_H_

#pragma once

#include "Base/RemoteDtoMemberBase.h"

namespace Memory
{
    template <class T>
    class RemoteDtoSimpleMember : public RemoteDtoMemberBase
    {
        T*          _dataValue;

    public:

        explicit    RemoteDtoSimpleMember( const size_t& offset );
                    ~RemoteDtoSimpleMember( void ) {}

        bool        OnUpdate( SharedRemoteProcessService remoteProcessService, std::vector<byte>* data ) override;
        size_t      GetSize( void ) const override;

        T*          GetPtr( void );
        T           Get( void );
    };

    template <class T>
    RemoteDtoSimpleMember<T>::RemoteDtoSimpleMember( const size_t& offset ) :
        RemoteDtoMemberBase( offset ),
        _dataValue( nullptr )
    {
    }

    template <class T>
    bool RemoteDtoSimpleMember<T>::OnUpdate( SharedRemoteProcessService /*remoteProcessService*/, std::vector<byte>* data )
    {
        _dataValue = reinterpret_cast< T* >( &data->at( GetOffset() ) );
        return true;
    }

    template <class T>
    size_t RemoteDtoSimpleMember<T>::GetSize( void ) const
    {
        return sizeof( T );
    }

    template <class T>
    T* RemoteDtoSimpleMember<T>::GetPtr( void )
    {
        return _dataValue;
    }

    template <class T>
    T RemoteDtoSimpleMember<T>::Get( void )
    {
        return *_dataValue;
    }

    typedef RemoteDtoSimpleMember<float>    RemoteFloat;
    typedef RemoteDtoSimpleMember<int>      RemoteInt;
    typedef RemoteDtoSimpleMember<double>   RemoteDouble;
    typedef RemoteDtoSimpleMember<size_t>   RemoteSize;
}

#endif /* _MEMORY_REMOTEDTOSIMPLEMEMBER_H_ */