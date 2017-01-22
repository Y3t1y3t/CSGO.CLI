#include "RemoteProcessService.h"

#include <TlHelp32.h>

namespace Memory
{
    RemoteProcessParamsDto::RemoteProcessParamsDto( const std::string& processName, const std::string& windowName, const std::string& windowClassName, DWORD accessRights )
    {
        ProcessName = processName;
        WindowName = windowName;
        WindowClassName = windowClassName;
        AccessRights = accessRights;
    }

    RemoteProcessDto::RemoteProcessDto( RemoteProcessParamsDto dto )
        : RemoteProcessParamsDto( dto )
    {
        Id = 0;
        Handle = INVALID_HANDLE_VALUE;
    }

    bool RemoteProcessService::Attach( const RemoteProcessParamsDto& process )
    {
        Detach();

        _process = RemoteProcessDto( process );

        auto curtime = GetTickCount64();
        do {
            if( !GetProcessId() )
                continue;
            if( !GetProcessHandle() )
                continue;
            return true;
        } while( ( 1000 * 60 * 5 != 0 ? ( GetTickCount64() - curtime ) <= 1000 * 60 * 5 : true ) );

        return false;
    }

    void RemoteProcessService::Detach( void )
    {
        if( _process.Handle != INVALID_HANDLE_VALUE )
            CloseHandle( _process.Handle );

        _process = RemoteProcessDto( {std::string()} );
    }

    LPVOID RemoteProcessService::AllocRemoteData( const byte* data, size_t size ) const
    {
        auto remoteData = VirtualAllocEx( _process.Handle, nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
        if( remoteData == nullptr )
            return nullptr;

        if( WriteProcessMemory( _process.Handle, remoteData, data, size, nullptr ) == FALSE )
            return nullptr;
        return remoteData;
    }

    bool RemoteProcessService::DeallocRemoteData(LPVOID entryPoint) const
    {
        return VirtualFreeEx( _process.Handle, entryPoint, 0, MEM_RELEASE ) != FALSE;
    }

    HANDLE RemoteProcessService::StartRemoteThread(LPVOID entryPoint, LPVOID data) const
    {
        return CreateRemoteThread( _process.Handle, nullptr, NULL, static_cast< LPTHREAD_START_ROUTINE >( entryPoint ), data, NULL, nullptr );
    }

    bool RemoteProcessService::IsValid( void )
    {
        _process.Id = 0;
        return GetProcessId();
    }

    RemoteProcessDto& RemoteProcessService::Get( void )
    {
        return _process;
    }

    bool RemoteProcessService::GetProcessId( void )
    {
        if( _process.WindowName.empty() && _process.WindowClassName.empty() ) {
            auto hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
            if( !hSnapshot )
                return false;

            PROCESSENTRY32 pe32 = { sizeof( PROCESSENTRY32 ) };
            if( Process32First( hSnapshot, &pe32 ) == TRUE ) {
                do {
                    if( pe32.szExeFile == _process.ProcessName )
                        _process.Id = pe32.th32ProcessID;
                } while( Process32Next( hSnapshot, &pe32 ) == TRUE && _process.Id == 0 );
            }

            CloseHandle( hSnapshot );
        }
        else {
            auto hWin = FindWindowA(
                _process.WindowClassName.empty() ? NULL : _process.WindowClassName.c_str(),
                _process.WindowName.empty() ? NULL : _process.WindowName.c_str() );
            if( hWin )
                GetWindowThreadProcessId( hWin, &_process.Id );
        }
        return bool( _process.Id != 0 );
    }

    bool RemoteProcessService::GetProcessHandle( void )
    {
        if( _process.Id == 0 )
            return false;
        return bool( ( _process.Handle = OpenProcess( _process.AccessRights, FALSE, _process.Id ) ) != INVALID_HANDLE_VALUE );
    }
}
