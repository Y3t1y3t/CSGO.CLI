#ifndef _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOK_H_
#define _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOK_H_

#pragma once

#include "../../Process/RemoteProcessService.h"

#include <vector>

namespace Memory
{
    class RemoteVirtualMethodsTableHook
    {
        SharedRemoteProcessService  _remoteProcessService;

        struct VirtualMethodsTable
        {
            uintptr_t               Ptr;
            uintptr_t               PtrValue;
            std::vector<uintptr_t>  VirtualMethods;
        }_virtualMethodsTable;

        struct SharedData
        {
            uintptr_t   Ptr;
            size_t      Size;
        }_sharedData;

    public:

        explicit RemoteVirtualMethodsTableHook( SharedRemoteProcessService remoteProcessService, const uintptr_t& virtualMethodsTablePtr, std::vector<uintptr_t>& virtualMethods, const uintptr_t& sharedDataPtr, const size_t& sharedDataSize );
        ~RemoteVirtualMethodsTableHook( void );

        bool        IsValidSharedDataPtr( void ) const;

        void        SetHook( void ) const;
        void        RemoveHook( void ) const;

        uintptr_t   GetVirtualMethodsPtr( void ) const;

        uintptr_t   GetVirtualMethodPtr( const size_t& index ) const;
        void        SetVirtualMethodPtr( const size_t& index, const uintptr_t& virtualMethodPtr ) const;

        uintptr_t   GetSharedDataPtr( void ) const;
        void        SetSharedDataPtr( const uintptr_t& sharedDataPtr );

        size_t      GetSharedDataSize( void ) const;

        template<class T>
        bool        GetSharedDataPtrValue( T* out );

        template<class T>
        bool        SetSharedDataPtrValue( const T& in );
    };

    template <class T>
    bool RemoteVirtualMethodsTableHook::GetSharedDataPtrValue( T* out )
    {
        if( !IsValidSharedDataPtr() )
            return false;
        return _remoteProcessService->Read<T>( GetSharedDataPtr(), out );
    }

    template <class T>
    bool RemoteVirtualMethodsTableHook::SetSharedDataPtrValue( const T& in )
    {
        if( !IsValidSharedDataPtr() )
            return false;
        return _remoteProcessService->Write<T>( GetSharedDataPtr(), in );
    }
}

#endif /* _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOK_H_ */