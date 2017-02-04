#include "ClientClassService.h"

namespace CSGO
{
    ClientClassService::ClientClassService( Memory::SharedRemoteProcessService remoteProcessService, const uintptr_t& allClassesPtr ) :
        _clientClassPtr( std::make_unique<ClientClassDto>( remoteProcessService, allClassesPtr ) )
    {
    }

    size_t ClientClassService::GetRecvPropOffset( const std::string& tableName, const std::string& propName ) const
    {
        auto tablePtr = FindRecvTablePtr( tableName.c_str() );
        if( tablePtr == nullptr )
            return 0;
        return FindRecvPropOffset( tablePtr, propName.c_str(), 0 );
    }

    size_t ClientClassService::FindRecvPropOffset( RecvTableDto* tablePtr, const char* name, size_t offset ) const
    {
        if( !tablePtr->Update( 2 ) )
            return 0;

        for( auto& prop : tablePtr->Props.Get() ) {
            if( !strcmp( prop->Name.GetPtr(), name ) )
                return prop->Offset.Get() + offset;

            auto propTablePtr = prop->Table.GetPtr();
            if( propTablePtr == nullptr )
                continue;

            auto result = FindRecvPropOffset( propTablePtr, name, prop->Offset.Get() + offset );
            if( result != 0x0 )
                return result;
        }
        return 0x0;
    }

    RecvTableDto* ClientClassService::FindRecvTablePtr( const char *name ) const
    {
        for( auto clientClassPtr = _clientClassPtr.get(); clientClassPtr != nullptr; clientClassPtr = clientClassPtr->Next.GetPtr() ) {

            clientClassPtr->Update( 2 );// TODO: Mark Props as lazy.

            auto tablePtr = clientClassPtr->Table.GetPtr();
            if( tablePtr == nullptr || strcmp( tablePtr->Name.GetPtr(), name ) )
                continue;

            return tablePtr;
        }
        return nullptr;
    }
}
