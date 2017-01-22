#ifndef _MEMORY_REMOTEPROCESS_H_
#define _MEMORY_REMOTEPROCESS_H_

#pragma once

#include <windows.h>
#include <string>
#include <memory>

namespace Memory
{
    class RemoteProcessService;

    typedef std::shared_ptr<RemoteProcessService> SharedRemoteProcessService;

    class RemoteProcessParamsDto
    {
    public:
        RemoteProcessParamsDto( const std::string& processName, const std::string& windowName = std::string(), const std::string& windowClassName = std::string(), DWORD accessRights = PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION );
        ~RemoteProcessParamsDto( void ) = default;

        DWORD       AccessRights;
        std::string ProcessName;
        std::string WindowName;
        std::string WindowClassName;
    };

    class RemoteProcessDto : public RemoteProcessParamsDto
    {
    public:
        explicit RemoteProcessDto( RemoteProcessParamsDto dto );
        ~RemoteProcessDto( void ) = default;

        DWORD       Id;
        HANDLE      Handle;
    };

    class RemoteProcessService
    {
        RemoteProcessDto    _process = RemoteProcessDto( { std::string() } );

    public:

        bool Attach( const RemoteProcessParamsDto& process );
        void Detach( void );

        LPVOID  AllocRemoteData( const byte* data, size_t size ) const;
        bool    DeallocRemoteData( LPVOID entryPoint ) const;

        HANDLE  StartRemoteThread( LPVOID entryPoint, LPVOID data ) const;

        template<class T>
        bool    Read( LPVOID ptr, T* out );

        template<class T>
        bool    Write( LPVOID ptr, const T& in );

        bool    IsValid( void );

        RemoteProcessDto& Get( void );

    private:

        bool GetProcessId( void );
        bool GetProcessHandle( void );
    };

    template <class T>
    bool RemoteProcessService::Read( LPVOID ptr, T* out )
    {
        return ReadProcessMemory( _process.Handle, ptr, out, sizeof( T ), nullptr ) != FALSE;
    }

    template <class T>
    bool RemoteProcessService::Write( LPVOID ptr, const T& in )
    {
        return WriteProcessMemory( _process.Handle, ptr, LPCVOID( &in ), sizeof( T ), nullptr ) != FALSE;
    }
}

#endif /* _MEMORY_REMOTEPROCESS_H_ */
