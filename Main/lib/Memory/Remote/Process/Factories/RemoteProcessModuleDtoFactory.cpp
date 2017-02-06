#include "RemoteProcessModuleDtoFactory.h"

#include <TlHelp32.h>

namespace Memory
{
    bool RemoteProcessModuleDtoFactory::Create( DWORD processId, const std::string& moduleName, std::unique_ptr<RemoteProcessModuleDto>* modulePtr ) const
    {
        auto snapshotHandle = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, processId );
        if( snapshotHandle == INVALID_HANDLE_VALUE )
            return false;

        MODULEENTRY32 moduleEntry = { sizeof( MODULEENTRY32 ) };
        if( Module32First( snapshotHandle, &moduleEntry ) == TRUE ) {
            do {
                if( moduleEntry.szModule == moduleName ) {
                    *modulePtr = std::make_unique<RemoteProcessModuleDto>( uintptr_t( moduleEntry.modBaseAddr ), moduleEntry.modBaseSize );
                    break;
                }
            } while( Module32Next( snapshotHandle, &moduleEntry ) == TRUE );
        }

        CloseHandle( snapshotHandle );
        return *modulePtr != nullptr;
    }
}
