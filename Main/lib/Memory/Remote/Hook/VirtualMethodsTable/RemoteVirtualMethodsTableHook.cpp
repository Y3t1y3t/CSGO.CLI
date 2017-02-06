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

    RemoteVirtualMethodsTableHook::~RemoteVirtualMethodsTableHook()
    {
        RemoveTableHook();

        if( !IsValidSharedDataPtr() )
            return;

        _remoteProcessService->FreeAllocatedRemoteData( reinterpret_cast< LPVOID >( GetSharedDataPtr() ) );
    }

    void RemoteVirtualMethodsTableHook::SetTableHook() const
    {
        _remoteProcessService->Suspend();
        _remoteProcessService->Write<uintptr_t>( _virtualMethodsTable.Ptr, GetVirtualMethodsPtr() );
        _remoteProcessService->Resume();
    }

    void RemoteVirtualMethodsTableHook::RemoveTableHook() const
    {
        _remoteProcessService->Suspend();
        _remoteProcessService->Write<uintptr_t>( _virtualMethodsTable.Ptr, _virtualMethodsTable.PtrValue );
        _remoteProcessService->Resume();
    }

    bool RemoteVirtualMethodsTableHook::IsValidSharedDataPtr() const
    {
        return _sharedData.Ptr != 0x0;
    }

    uintptr_t RemoteVirtualMethodsTableHook::GetVirtualMethodsPtr() const
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
        
        _remoteProcessService->Suspend();
        _remoteProcessService->Write<uintptr_t>( GetVirtualMethodsPtr() + index * sizeof( uintptr_t ), virtualMethodPtr );
        _remoteProcessService->Resume();
    }

    uintptr_t RemoteVirtualMethodsTableHook::GetSharedDataPtr() const
    {
        return _sharedData.Ptr;
    }

    void RemoteVirtualMethodsTableHook::SetSharedDataPtr( const uintptr_t& sharedDataPtr )
    {
        _sharedData.Ptr = sharedDataPtr;
    }

    size_t RemoteVirtualMethodsTableHook::GetSharedDataSize() const
    {
        return _sharedData.Size;
    }
}
