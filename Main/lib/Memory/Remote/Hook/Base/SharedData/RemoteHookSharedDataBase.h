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
                Kernel32( void );
                ~Kernel32( void ) = default;

                typedef HANDLE( __stdcall *CreateRemoteThreadFn )( HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId );
                CreateRemoteThreadFn CreateRemoteThread;

                typedef DWORD( __stdcall *WaitForSingleObjectFn )( HANDLE hHandle, DWORD dwMilliseconds );
                WaitForSingleObjectFn WaitForSingleObject;

                typedef BOOL( __stdcall *CloseHandleFn )( HANDLE hObject );
                CloseHandleFn CloseHandle;
            } Kernel32;
        };
    };
}

#endif /* _MEMORY_REMOTEHOOKSHAREDDATABASE_H_ */
