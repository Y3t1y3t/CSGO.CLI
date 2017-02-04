#ifndef _MEMORY_REMOTEHOOKSHAREDDATABASE_H_
#define _MEMORY_REMOTEHOOKSHAREDDATABASE_H_

#pragma once

#include <windows.h>

namespace Memory
{
    class RemoteHookSharedDataBase
    {
    protected:
        struct Imports
        {
            class Kernel32
            {
            public:
                Kernel32();
                ~Kernel32() = default;

                using CreateRemoteThreadFn = HANDLE( __stdcall * )( HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId );
                CreateRemoteThreadFn CreateRemoteThread;

                using WaitForSingleObjectFn = DWORD( __stdcall * )( HANDLE hHandle, DWORD dwMilliseconds );
                WaitForSingleObjectFn WaitForSingleObject;

                using CloseHandleFn = BOOL( __stdcall * )( HANDLE hObject );
                CloseHandleFn CloseHandle;
            } Kernel32;
        };
    };
}

#endif /* _MEMORY_REMOTEHOOKSHAREDDATABASE_H_ */
