#ifndef _MEMORY_REMOTEDTOPTRARRAYMEMBER_H_
#define _MEMORY_REMOTEDTOPTRARRAYMEMBER_H_

#pragma once

#include "Base/RemoteDtoMemberBase.h"
#include "RemoteDtoSimpleMember.h"

namespace Memory
{
    template<class T>
    class RemoteDtoPtrArrayMember : public RemoteDtoMemberBase
    {
        std::vector<std::unique_ptr<T>> _dtoPtrArrays;
        size_t                          _arrayTypeSize;
        std::unique_ptr<RemoteSize>     _arrayCountMember;
        uintptr_t                       _ptrValue;

    public:

        explicit RemoteDtoPtrArrayMember( const size_t& offset, const size_t& arrayTypeSize, std::unique_ptr<RemoteSize> arrayCountMember );

    #pragma region InlinedFunctions
        bool OnUpdate( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data ) override
        {
            _arrayCountMember->OnUpdate( remoteProcessService, level, data );
            return UpdateArray( remoteProcessService, level, data );
        }

        size_t GetSize() const override { return sizeof( T* ); }
    #pragma endregion

        std::vector<std::unique_ptr<T>>& Get();

    private:

        bool UpdateArray( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data );
    };

    template <class T>
    RemoteDtoPtrArrayMember<T>::RemoteDtoPtrArrayMember( const size_t& offset, const size_t& arrayTypeSize, std::unique_ptr<RemoteSize> arrayCountMember ) :
        RemoteDtoMemberBase( offset ),
        _dtoPtrArrays( std::vector<std::unique_ptr<T>>() ),
        _arrayTypeSize( arrayTypeSize ),
        _ptrValue( 0x0 )
    {
        _arrayCountMember.swap( arrayCountMember );
    }

    template <class T>
    std::vector<std::unique_ptr<T>>& RemoteDtoPtrArrayMember<T>::Get()
    {
        return _dtoPtrArrays;
    }

    template <class T>
    bool RemoteDtoPtrArrayMember<T>::UpdateArray( SharedRemoteProcessService remoteProcessService, size_t level, std::vector<byte>* data )
    {
        auto arrayCountPtr = _arrayCountMember->GetPtr();
        auto arrayCount = arrayCountPtr == nullptr ? 0 : *arrayCountPtr;

        _dtoPtrArrays = std::vector<std::unique_ptr<T>>( arrayCount );
        if( _dtoPtrArrays.empty() )
            return false;

        _ptrValue = *reinterpret_cast< uintptr_t* >( &data->at( GetOffset() ) );
        if( _ptrValue == 0x0 )
            return false;

        size_t count = 0;
        for( std::unique_ptr<T>& dtoPtr : _dtoPtrArrays ) {
            dtoPtr = std::make_unique<T>( remoteProcessService, _ptrValue + count++ * _arrayTypeSize );
            dtoPtr->Update( level );
        }
        return true;
    }
}

#endif /* _MEMORY_REMOTEDTOPTRARRAYMEMBER_H_ */
