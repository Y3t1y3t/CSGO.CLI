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
        ~RemoteDtoSimpleMember() {}

        bool        OnUpdate( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data ) override;
        size_t      GetSize() const override;

        T*          GetPtr();
        T           Get();
    };

    template <class T>
    RemoteDtoSimpleMember<T>::RemoteDtoSimpleMember( const size_t& offset ) :
        RemoteDtoMemberBase( offset ),
        _dataValue( nullptr )
    {
    }

    template <class T>
    bool RemoteDtoSimpleMember<T>::OnUpdate( SharedRemoteProcessService /*remoteProcessService*/, size_t /*level*/, std::vector<byte>* data )
    {
        _dataValue = reinterpret_cast< T* >( &data->at( GetOffset() ) );
        return _dataValue != nullptr;
    }

    template <class T>
    size_t RemoteDtoSimpleMember<T>::GetSize() const
    {
        return sizeof( T );
    }

    template <class T>
    T* RemoteDtoSimpleMember<T>::GetPtr()
    {
        return _dataValue;
    }

    template <class T>
    T RemoteDtoSimpleMember<T>::Get()
    {
        return *_dataValue;
    }

    using RemoteFloat = RemoteDtoSimpleMember<float>;
    using RemoteInt = RemoteDtoSimpleMember<int>;
    using RemoteDouble = RemoteDtoSimpleMember<double>;
    using RemoteSize = RemoteDtoSimpleMember<size_t>;
    using RemoteUIntPtr = RemoteDtoSimpleMember<uintptr_t>;
}

#endif /* _MEMORY_REMOTEDTOSIMPLEMEMBER_H_ */