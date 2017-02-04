#include "../RemoteDtoMemberResolver.h"

#include "RemoteDtoBase.h"

#include <algorithm>

namespace Memory
{
    RemoteDtoBase::RemoteDtoBase( SharedRemoteProcessService remoteProcessService, const uintptr_t& base ) :
        _remoteProcessService( remoteProcessService ),
        _members( std::list<RemoteDtoMemberBase*>() ),
        _data( std::vector<byte>() ),
        _base( base )
    {
    }

    bool RemoteDtoBase::Initialize( const size_t& inheritedClassSize )
    {
        size_t maxDataSize = 0;
        if( !RemoteDtoMemberResolver().Resolve( uintptr_t( this ), inheritedClassSize, &maxDataSize, &_members ) )
            return false;
        return !( _data = std::vector<byte>( maxDataSize ) ).empty();
    }

    bool RemoteDtoBase::Update( size_t level /* = 1 */ )
    {
        if( !UpdateData() )
            return false;
        return UpdateMembers( level );
    }

    bool RemoteDtoBase::ForceUpdate( const uintptr_t& base, size_t level /* = 1 */ )
    {
        SetBase( base );
        return Update( level );
    }

    void RemoteDtoBase::SetBase( const uintptr_t& base )
    {
        _base = base;
    }

    bool RemoteDtoBase::UpdateData()
    {
        return _remoteProcessService->Read( _base, &_data.at( 0 ), _data.size() );
    }

    bool RemoteDtoBase::UpdateMembers( size_t level )
    {
        if( level-- == 0U )
            return true;

        auto result = true;
        std::for_each( _members.begin(), _members.end(), [ & ] ( auto member ) {
            if( !member->OnUpdate( _remoteProcessService, level, &_data ) )
                result = false;
        });
        return result;
    }
}
