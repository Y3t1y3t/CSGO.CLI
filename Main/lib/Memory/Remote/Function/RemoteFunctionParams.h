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
                Kernel32();
                ~Kernel32() = default;

                using GetProcAddressFn = FARPROC( __stdcall * )( HMODULE module, LPCSTR lpProcName );
                GetProcAddressFn GetProcAddress;

                using GetModuleHandleAFn = HMODULE( __stdcall * )( LPCSTR moduleName );
                GetModuleHandleAFn GetModuleHandleA;

                using SleepFn = void( __stdcall * )( DWORD dwMilliseconds );
                SleepFn Sleep;
            } Kernel32;
        } Imports;
    };
}

#endif /* _MEMORY_REMOTEFUNCTIONPARAMS_H_ */
