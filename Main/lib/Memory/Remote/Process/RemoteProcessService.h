#ifndef _MEMORY_REMOTEPROCESS_H_
#define _MEMORY_REMOTEPROCESS_H_

#pragma once

#include <windows.h>
#include <string>
#include <memory>

#define PROCESS_REMOTE (PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_DUP_HANDLE )

namespace Memory
{
    class RemoteProcessService;

    using SharedRemoteProcessService = std::shared_ptr<RemoteProcessService>;

    class RemoteProcessParamsDto
    {
    public:
        RemoteProcessParamsDto( const std::string& processName, const std::string& windowName = std::string(), const std::string& windowClassName = std::string(), DWORD accessRights = PROCESS_REMOTE );
        ~RemoteProcessParamsDto() = default;

        DWORD       AccessRights;
        std::string ProcessName;
        std::string WindowName;
        std::string WindowClassName;
    };

    class RemoteProcessDto : public RemoteProcessParamsDto
    {
    public:
        explicit RemoteProcessDto( RemoteProcessParamsDto dto );
        ~RemoteProcessDto() = default;

        DWORD       Id;
        HANDLE      Handle;
    };

    class RemoteProcessService
    {
        RemoteProcessDto    _process = RemoteProcessDto( { std::string() } );

    public:

        RemoteProcessService() = default;
        ~RemoteProcessService();

        bool                        Attach( const RemoteProcessParamsDto& process );
        void                        Detach();

        LPVOID                      AllocRemoteData( const byte* data, size_t size ) const;
        bool                        DeallocRemoteData( LPVOID entryPoint ) const;

        HANDLE                      StartRemoteThread( LPVOID entryPoint, LPVOID data ) const;
        HANDLE                      GetSharedHandle( HANDLE handle, DWORD accessRights = PROCESS_REMOTE ) const;

        bool                        Read( const uintptr_t& ptr, LPVOID out, const size_t& size ) const;
        template<class T> bool      Read( LPCVOID ptr, T* out ) const;
        template<class T> bool      Read( const uintptr_t& ptr, T* out ) const;

        template<class T> bool      Write( LPVOID ptr, const T& in ) const;
        template<class T> bool      Write( const uintptr_t& ptr, const T& in ) const;

        bool                        IsValid();

        RemoteProcessDto&           Get();

    private:

        bool                        GetProcessId();
        bool                        GetProcessHandle();
    };

    template <class T>
    bool RemoteProcessService::Read( LPCVOID ptr, T* out ) const
    {
        return ReadProcessMemory( _process.Handle, ptr, out, sizeof( T ), nullptr ) != FALSE;
    }

    template <class T>
    bool RemoteProcessService::Read( const uintptr_t& ptr, T* out ) const
    {
        return ReadProcessMemory( _process.Handle, LPCVOID( ptr ), out, sizeof( T ), nullptr ) != FALSE;
    }

    template <class T>
    bool RemoteProcessService::Write( LPVOID ptr, const T& in ) const
    {
        return WriteProcessMemory( _process.Handle, ptr, LPCVOID( &in ), sizeof( T ), nullptr ) != FALSE;
    }

    template <class T>
    bool RemoteProcessService::Write( const uintptr_t& ptr, const T& in ) const
    {
        return WriteProcessMemory( _process.Handle, LPVOID( ptr ), LPCVOID( &in ), sizeof( T ), nullptr ) != FALSE;
    }
}

#endif /* _MEMORY_REMOTEPROCESS_H_ */
