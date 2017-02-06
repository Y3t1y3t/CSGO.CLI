#include "RemoteProcessDtoFactory.h"

#include <TlHelp32.h>

namespace Memory
{
    bool RemoteProcessDtoFactory::Create( const std::string& processName,
                                          const std::string& windowName,
                                          const std::string& windowClassName,
                                          DWORD accessRigths,
                                          std::unique_ptr<RemoteProcessDto>* processPtr ) const
    {
        DWORD processId = 0;
        if( !GetProcessIdByProcessName( processName, &processId ) &&
            !GetProcessIdByWindow( windowName, windowClassName, &processId ) )
            return false;

        HANDLE processHandle = nullptr;
        if( !GetProcessHandleByProcessIdWithAccessRights( processId, accessRigths, &processHandle ) )
            return false;

        *processPtr = std::make_unique<RemoteProcessDto>( processId, processHandle );
        return true;
    }

    bool RemoteProcessDtoFactory::GetProcessIdByProcessName( const std::string& processName, DWORD* processIdPtr ) const
    {
        if( processName.empty() )
            return false;

        auto snapshotHandle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
        if( snapshotHandle == INVALID_HANDLE_VALUE)
            return false;

        PROCESSENTRY32  processEntry = { sizeof( PROCESSENTRY32 ) };
        if( Process32First( snapshotHandle, &processEntry ) == TRUE ) {
            do {
                if( processEntry.szExeFile == processName ) {
                    *processIdPtr = processEntry.th32ProcessID;
                    break;
                }
            } while( Process32Next( snapshotHandle, &processEntry ) == TRUE );
        }

        CloseHandle( snapshotHandle );
        return *processIdPtr != 0;
    }

    bool RemoteProcessDtoFactory::GetProcessIdByWindow( const std::string& windowName, const std::string& windowClassName, DWORD* processIdPtr ) const
    {
        if( windowClassName.empty() && windowClassName.empty() )
            return false;

        auto hWin = FindWindowA(
            windowClassName.empty() ? NULL : windowClassName.c_str(),
            windowName.empty() ? NULL : windowName.c_str() );

        if( hWin == nullptr )
            return false;

        GetWindowThreadProcessId( hWin, processIdPtr );
        return *processIdPtr != 0;
    }

    bool RemoteProcessDtoFactory::GetProcessHandleByProcessIdWithAccessRights( DWORD processId, DWORD accessRights, HANDLE* processHandlePtr ) const
    {
        if( processId == 0 )
            return false;
        return ( *processHandlePtr = OpenProcess( accessRights, FALSE, processId ) ) != nullptr;
    }
}
