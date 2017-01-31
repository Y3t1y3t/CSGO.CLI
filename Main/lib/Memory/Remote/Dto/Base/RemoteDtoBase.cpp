#include "RemoteDtoBase.h"

#include <algorithm>

namespace Memory
{
    RemoteDtoBase::RemoteDtoBase( SharedRemoteProcessService remoteProcessService )
        : _remoteProcessService( remoteProcessService )
    {
    }

    bool RemoteDtoBase::Initialize( const size_t& inheritedClassSize )
    {
        auto baseSize = sizeof( RemoteDtoBase );
        if( baseSize >= inheritedClassSize )
            throw std::exception( "" ); //TODO

        auto sizeCount = size_t( floor( inheritedClassSize / sizeof( size_t ) ) );
        if( sizeCount <= 0 )
            throw std::exception( "" ); //TODO

        auto inheritedObjStart = uintptr_t( this ) + baseSize;
        auto inheritedObjPtr = reinterpret_cast< size_t* >( inheritedObjStart );

        size_t maxDataSize = 0x0;
        for( auto count = 0U; count < sizeCount; ++count ) {
            auto inheritedObjMember = &inheritedObjPtr[ count ];
            if( *inheritedObjMember != typeid( RemoteDtoMemberBase ).hash_code() )
                continue;

            _members.emplace_back( reinterpret_cast< RemoteDtoMemberBase* >( inheritedObjMember ) );

            auto member = _members.at( _members.size() - 1 );
            member->SetData( &_data );

            maxDataSize = std::max<size_t>( member->GetSize() + member->GetOffset(), maxDataSize );
        }

        _data = std::vector<byte>( maxDataSize );
        return maxDataSize != 0;
    }

    bool RemoteDtoBase::Update( const uintptr_t& base )
    {
        return _remoteProcessService->Read( base, &_data.at( 0 ), _data.size() );
    }
}
