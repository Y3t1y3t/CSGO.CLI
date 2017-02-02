#include "../RemoteDtoMemberResolver.h"

#include "RemoteDtoBase.h"

#include <algorithm>

namespace Memory
{
    RemoteDtoBase::RemoteDtoBase( SharedRemoteProcessService remoteProcessService, const uintptr_t& base ) :
        _remoteProcessService( remoteProcessService ),
        _base( base ),
        _members( std::vector<RemoteDtoMemberBase*>() ),
        _data( std::vector<byte>() )
    {
    }

    bool RemoteDtoBase::Initialize( const size_t& inheritedClassSize )
    {
        if( !RemoteDtoMemberResolver().Parse( uintptr_t( this ), inheritedClassSize, &_members ) )
            return false;
        return !( _data = std::vector<byte>( GetMaxDataSize() ) ).empty();
    }


    bool RemoteDtoBase::Update( bool loadLazy /* = false */ )
    {
        if( !UpdateData() )
            return false;
        return loadLazy || UpdateMembers();
    }

    bool RemoteDtoBase::ForceUpdate( const uintptr_t& base, bool loadLazy /* = false */ )
    {
        SetBase( base );
        return Update( loadLazy );
    }

    void RemoteDtoBase::SetBase( const uintptr_t& base )
    {
        _base = base;
    }

    bool RemoteDtoBase::UpdateData( void )
    {
        return _remoteProcessService->Read( _base, &_data.at( 0 ), _data.size() );
    }

    bool RemoteDtoBase::UpdateMembers( void )
    {
        auto result = true;
        std::for_each( _members.begin(), _members.end(), [ & ] ( auto member ) {
            if( !member->OnUpdate( _remoteProcessService, &_data ) )
                result = false;
        } );
        return result;
    }

    size_t RemoteDtoBase::GetMaxDataSize( void )
    {
        return ( *std::max_element( _members.begin(), _members.end(), [] ( RemoteDtoMemberBase* a, RemoteDtoMemberBase* b ) {
            return a->GetDataSize() < b->GetDataSize();
        } ) )->GetDataSize();
    }
}
