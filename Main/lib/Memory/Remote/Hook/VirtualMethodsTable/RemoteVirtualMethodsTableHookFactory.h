#ifndef _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKFACTORY_H_
#define _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKFACTORY_H_

#pragma once

#include "RemoteVirtualMethodsTableHook.h"
#include "RemoteVirtualMethodsResolver.h"

#include "../../Process/RemoteProcessService.h"

#include <vector>
#include <iostream>

namespace Memory
{
    class RemoteVirtualMethodsTableHookFactory
    {
        SharedRemoteProcessService                      _remoteProcessService;
        std::unique_ptr<RemoteVirtualMethodsResolver>   _remoteVirtualMethodsResolver;

    public:

        explicit RemoteVirtualMethodsTableHookFactory( SharedRemoteProcessService remoteProcessService );


        template<typename T>
        bool Create( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::unique_ptr<RemoteVirtualMethodsTableHook>* hook );

    private:

        template <class T>
        LPVOID CreateSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::vector<uintptr_t>& virtualMethods ) const;
    };

    template <typename T>
    bool RemoteVirtualMethodsTableHookFactory::Create( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::unique_ptr<RemoteVirtualMethodsTableHook>* hook )
    {
        std::vector<uintptr_t> virtualMethods;
        if( !_remoteVirtualMethodsResolver->Resolve( virtualMethodsTablePtr, &virtualMethods ) )
            return false;

        auto sharedDataPtr = CreateSharedData<T>( virtualMethodsTablePtr, sharedOriginProcessHandle, virtualMethods );
        if( sharedDataPtr == nullptr )
            return false;

        *hook = std::make_unique<RemoteVirtualMethodsTableHook>( _remoteProcessService, virtualMethodsTablePtr, virtualMethods, reinterpret_cast< uintptr_t >( sharedDataPtr ), sizeof( T ) );
        return true;
    }

    template <typename T>
    LPVOID RemoteVirtualMethodsTableHookFactory::CreateSharedData( const uintptr_t& virtualMethodsTablePtr, HANDLE sharedOriginProcessHandle, std::vector<uintptr_t>& virtualMethods ) const
    {
        auto virtualMethodsSize = virtualMethods.size() * sizeof( uintptr_t );
        auto sharedDataObjSize = sizeof( T );
        auto remoteSharedDataSize = sharedDataObjSize + virtualMethodsSize;

        std::unique_ptr<byte[]> remoteSharedData( new byte[ remoteSharedDataSize ] );

        auto remoteSharedDataPtr = reinterpret_cast< byte* >( remoteSharedData.get() );
        auto sharedDataObj = T( virtualMethodsTablePtr, sharedOriginProcessHandle );
        std::memcpy( remoteSharedDataPtr, &sharedDataObj, sharedDataObjSize );

        auto virtualMethodsPtr = reinterpret_cast< uintptr_t >( remoteSharedDataPtr ) + sharedDataObjSize;
        std::memcpy( reinterpret_cast< void* >( virtualMethodsPtr ), &virtualMethods.at( 0 ), virtualMethodsSize );

        return _remoteProcessService->AllocRemoteData( remoteSharedDataPtr, remoteSharedDataSize );
    }
}

#endif /* _MEMORY_REMOTEVIRTUALMETHODSTABLEHOOKFACTORY_H_ */
