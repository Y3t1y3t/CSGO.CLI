#ifndef _MEMORY_REMOTEFUNCTIONPARAMS_H_
#define _MEMORY_REMOTEFUNCTIONPARAMS_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteFunctionParams
    {
    public:
        struct Imports
        {
            class Kernel32
            {
            public:
                Kernel32( void );
                ~Kernel32( void ) = default;

                typedef FARPROC( __stdcall *GetProcAddressFn )( HMODULE module, LPCSTR lpProcName );
                GetProcAddressFn GetProcAddress;

                typedef HMODULE( __stdcall *GetModuleHandleAFn )( LPCSTR moduleName );
                GetModuleHandleAFn GetModuleHandleA;

                typedef void( __stdcall *SleepFn )( DWORD dwMilliseconds );
                SleepFn Sleep;
            } Kernel32;
        } Imports;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONPARAMS_H_ */
