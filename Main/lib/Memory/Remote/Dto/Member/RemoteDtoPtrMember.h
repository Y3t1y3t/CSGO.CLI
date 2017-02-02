#ifndef _MEMORY_REMOTEDTOPTRMEMBER_H_
#define _MEMORY_REMOTEDTOPTRMEMBER_H_

#pragma once

#include "Base/RemoteDtoMemberBase.h"

namespace Memory
{
    template<class T>
    class RemoteDtoPtrMember : public RemoteDtoMemberBase
    {
        std::unique_ptr<T>  _dtoPtr;
        uintptr_t           _ptrValue;

    public:

        explicit    RemoteDtoPtrMember( const size_t& offset );

    #pragma region InlinedFunctions
        bool OnUpdate( SharedRemoteProcessService remoteProcessService, std::vector<byte>* data ) override
        {
            _ptrValue = *reinterpret_cast< uintptr_t* >( &data->at( GetOffset() ) );
            if( _ptrValue == 0x0 )
                return false;

            if( _dtoPtr == nullptr )
                _dtoPtr = std::make_unique<T>( remoteProcessService, _ptrValue );
            return _dtoPtr->ForceUpdate( _ptrValue, true ); // TODO: Handle Infinite-Loop
        }

        size_t GetSize( void ) const override { return sizeof( T* ); }
    #pragma endregion

        T* GetPtr( void );
    };

    template <class T>
    RemoteDtoPtrMember<T>::RemoteDtoPtrMember( const size_t& offset ) :
        RemoteDtoMemberBase( offset ),
        _ptrValue( 0x0 )
    {
    }

    template <class T>
    T* RemoteDtoPtrMember<T>::GetPtr( void )
    {
        if( _ptrValue == 0x0 )
            return nullptr;
        return _dtoPtr.get();
    }
}

#endif /* _MEMORY_REMOTEDTOPTRMEMBER_H_ */
