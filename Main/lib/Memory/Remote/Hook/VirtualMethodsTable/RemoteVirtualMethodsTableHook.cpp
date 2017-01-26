#include "RemoteVirtualMethodsTableHook.h"

namespace Memory
{
    RemoteVirtualMethodsTableHook::RemoteVirtualMethodsTableHook(
        SharedRemoteProcessService remoteProcessService,
        const uintptr_t& virtualMethodsTablePtr,
        std::vector<uintptr_t>& virtualMethods,
        const uintptr_t& sharedDataPtr,
        const size_t& sharedDataSize
    ) : _remoteProcessService( remoteProcessService )
    {
        _sharedData.Ptr = sharedDataPtr;
        _sharedData.Size = sharedDataSize;
        _virtualMethodsTable.Ptr = virtualMethodsTablePtr;
        _virtualMethodsTable.VirtualMethods = virtualMethods;
        _remoteProcessService->Read<uintptr_t>( _virtualMethodsTable.Ptr, &_virtualMethodsTable.PtrValue );
    }

    RemoteVirtualMethodsTableHook::~RemoteVirtualMethodsTableHook( void )
    {
        RemoveHook();

        if( IsValidSharedDataPtr() ) {
            _remoteProcessService->DeallocRemoteData( reinterpret_cast< LPVOID >( GetSharedDataPtr() ) );
            SetSharedDataPtr( 0x0 );
        }
    }

    bool RemoteVirtualMethodsTableHook::IsValidSharedDataPtr( void ) const
    {
        return _sharedData.Ptr != 0x0;
    }

    void RemoteVirtualMethodsTableHook::SetHook( void ) const
    {
        _remoteProcessService->Write<uintptr_t>( _virtualMethodsTable.Ptr, GetVirtualMethodsPtr() );
    }

    void RemoteVirtualMethodsTableHook::RemoveHook( void ) const
    {
        _remoteProcessService->Write<uintptr_t>( _virtualMethodsTable.Ptr, _virtualMethodsTable.PtrValue );
    }

    uintptr_t RemoteVirtualMethodsTableHook::GetVirtualMethodsPtr( void ) const
    {
        return GetSharedDataPtr() + GetSharedDataSize();
    }

    uintptr_t RemoteVirtualMethodsTableHook::GetVirtualMethodPtr( const size_t& index ) const
    {
        if( index < 0 || index >= _virtualMethodsTable.VirtualMethods.size() )
            return 0;
        return _virtualMethodsTable.VirtualMethods.at( index );
    }

    void RemoteVirtualMethodsTableHook::SetVirtualMethodPtr( const size_t& index, const uintptr_t& virtualMethodPtr ) const
    {
        if( index < 0 || index >= _virtualMethodsTable.VirtualMethods.size() )
            return;

        _remoteProcessService->Write<uintptr_t>( GetVirtualMethodsPtr() + index * sizeof( uintptr_t ), virtualMethodPtr );
    }

    uintptr_t RemoteVirtualMethodsTableHook::GetSharedDataPtr( void ) const
    {
        return _sharedData.Ptr;
    }

    void RemoteVirtualMethodsTableHook::SetSharedDataPtr( const uintptr_t& sharedDataPtr )
    {
        _sharedData.Ptr = sharedDataPtr;
    }

    size_t RemoteVirtualMethodsTableHook::GetSharedDataSize( void ) const
    {
        return _sharedData.Size;
    }
}
