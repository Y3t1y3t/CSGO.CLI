#include "RemoteVirtualMethodsResolver.h"

namespace Memory
{
    RemoteVirtualMethodsResolver::RemoteVirtualMethodsResolver( SharedRemoteProcessService remoteProcessService ) :
        _remoteProcessService( remoteProcessService )
    {
    }

    bool RemoteVirtualMethodsResolver::Resolve( const uintptr_t& virtualMethodsTablePtr, std::vector<uintptr_t>* virtualMethods ) const
    {
        uintptr_t virtualMethodsPtr;
        if( !_remoteProcessService->Read<uintptr_t>( reinterpret_cast< LPVOID >( virtualMethodsTablePtr ), &virtualMethodsPtr ) )
            return false;

        uintptr_t virtualMethodPtr;
        while( _remoteProcessService->Read<uintptr_t>( reinterpret_cast< LPVOID >( virtualMethodsPtr + virtualMethods->size() * sizeof( uintptr_t ) ), &virtualMethodPtr )
               && virtualMethodPtr != 0x0 ) {
            virtualMethods->emplace_back( virtualMethodPtr );
        }

        return !virtualMethods->empty();
    }
}
