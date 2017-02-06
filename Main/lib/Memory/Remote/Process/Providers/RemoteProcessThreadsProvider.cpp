#include "RemoteProcessThreadsProvider.h"

#include <TlHelp32.h>

namespace Memory
{
    bool RemoteProcessThreadsProvider::Provide( DWORD processId, std::vector<DWORD>* threadIdsPtr ) const
    {
        auto snapshotHandle = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 );
        if( snapshotHandle == INVALID_HANDLE_VALUE )
            return false;

        THREADENTRY32 threadEntry = { sizeof( THREADENTRY32 ) };
        if( Thread32First( snapshotHandle, &threadEntry ) == TRUE ) {
            do {
                if( threadEntry.th32OwnerProcessID == processId )
                    threadIdsPtr->emplace_back( threadEntry.th32ThreadID );
            } while( Thread32Next( snapshotHandle, &threadEntry ) == TRUE );
        }

        CloseHandle( snapshotHandle );
        return !threadIdsPtr->empty();
    }
}
