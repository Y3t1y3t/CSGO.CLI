#include "RemoteHookSharedDataBase.h"

namespace Memory
{
    RemoteHookSharedDataBase::Imports::Kernel32::Kernel32( void )
    {
        auto module = GetModuleHandleA( "kernel32.dll" );

        CreateRemoteThread = CreateRemoteThreadFn( GetProcAddress( module, "CreateRemoteThread" ) );
        WaitForSingleObject = WaitForSingleObjectFn( GetProcAddress( module, "WaitForSingleObject" ) );
        CloseHandle = CloseHandleFn( GetProcAddress( module, "CloseHandle" ) );
    }
}
