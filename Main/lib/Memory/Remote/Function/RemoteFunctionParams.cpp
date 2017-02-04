#include "RemoteFunctionParams.h"

namespace Memory
{
    RemoteFunctionParams::Imports::Kernel32::Kernel32()
    {
        auto module = ::GetModuleHandleA( "kernel32.dll" );

        GetProcAddress = GetProcAddressFn( ::GetProcAddress( module, "GetProcAddress" ) );
        GetModuleHandleA = GetModuleHandleAFn( ::GetProcAddress( module, "GetModuleHandleA" ) );
        Sleep = SleepFn( ::GetProcAddress( module, "Sleep" ) );
    }
}
