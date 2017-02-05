#ifndef _MEMORY_REMOTEPROCESS_H_
#define _MEMORY_REMOTEPROCESS_H_

#pragma once

#include "Dtos/RemoteProcessDto.h"

#include "Providers/RemoteProcessIdProvider.h"
#include "Providers/RemoteProcessHandleProvider.h"

#include <windows.h>
#include <memory>

namespace Memory
{
    class RemoteProcessService
    {
        std::unique_ptr<RemoteProcessIdProvider>        _remoteProcessIdProvider;
        std::unique_ptr<RemoteProcessHandleProvider>    _remoteProcessHandleProvider;
        std::unique_ptr<RemoteProcessDto>               _process;

    public:

        RemoteProcessService();
        ~RemoteProcessService();

        bool                        Attach( const RemoteProcessParamsDto& process );
        void                        Detach() const;

        LPVOID                      AllocRemoteData( const byte* data, size_t size ) const;
        bool                        DeallocRemoteData( LPVOID entryPoint ) const;

        HANDLE                      StartRemoteThread( LPVOID entryPoint, LPVOID data ) const;
        bool                        GetSharedHandle( HANDLE handle, DWORD accessRights, HANDLE *duplicatedHandle ) const;

        bool                        Read( const uintptr_t& ptr, LPVOID out, const size_t& size ) const;
        template<class T> bool      Read( LPCVOID ptr, T* out ) const                                       { return Read( uintptr_t( ptr ), out, sizeof( T ) ); }
        template<class T> bool      Read( const uintptr_t& ptr, T* out ) const                              { return Read( ptr, out, sizeof( T ) ); }

        bool                        Write( const uintptr_t& ptr, LPCVOID in, const size_t& size ) const;
        template<class T> bool      Write( LPVOID ptr, const T& in ) const                                  { return Write( uintptr_t( ptr ), LPCVOID( &in ), sizeof( T ) ); }
        template<class T> bool      Write( const uintptr_t& ptr, const T& in ) const                        { return Write( ptr, LPCVOID( &in ), sizeof( T ) ); }

        bool                        IsValid() const;

    private:

        bool                        GetProcessId( DWORD *processId ) const;
        bool                        GetProcessHandle( HANDLE *processHandle ) const;
    };

    using SharedRemoteProcessService = std::shared_ptr<RemoteProcessService>;
}

#endif /* _MEMORY_REMOTEPROCESS_H_ */
