#include "RemoteProcessIdProvider.h"

#include <TlHelp32.h>

namespace Memory
{
    bool RemoteProcessIdProvider::ProvideProcessIdByProcessName( std::string& processName, DWORD* processId ) const
    {
        auto snapshotHandle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
        if( !snapshotHandle )
            return false;

        PROCESSENTRY32  processEntry = { sizeof( PROCESSENTRY32 ) };
        if( Process32First( snapshotHandle, &processEntry ) == TRUE ) {
            do {
                if( processEntry.szExeFile != processName )
                    continue;
                *processId = processEntry.th32ProcessID;
            } while( *processId == 0 && Process32Next( snapshotHandle, &processEntry ) == TRUE );
        }

        CloseHandle( snapshotHandle );
        return *processId != 0;
    }

    bool RemoteProcessIdProvider::ProvideProcessIdByWindow( std::string& windowName, std::string& windowClassName, DWORD* processId ) const
    {
        auto hWin = FindWindowA(
            windowClassName.empty() ? NULL : windowClassName.c_str(),
            windowName.empty() ? NULL : windowName.c_str() );

        if( hWin == nullptr )
            return false;

        GetWindowThreadProcessId( hWin, processId );
        return *processId != 0;
    }
}
