#ifndef _CLI_PAINTVIRTUALMETHODHOOK_H_
#define _CLI_PAINTVIRTUALMETHODHOOK_H_

#pragma once

#include "../../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/RemoteVirtualMethodHookBase.h"
#include "../../../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

namespace CLI
{
    class PaintVirtualMethodHook : public Memory::RemoteVirtualMethodHookBase
    {
        static PaintVirtualMethodHook*      _self;
        Memory::SharedRemoteProcessService  _remoteProcessService;

    public:

        explicit                    PaintVirtualMethodHook( Memory::SharedRemoteProcessService remoteProcessService, Memory::SharedRemoteFunctionService remoteFunctionService );
                                    ~PaintVirtualMethodHook();

        static inline DWORD WINAPI  FunctionCallback( LPVOID paramsPtr );
        static void __fastcall      VirtualMethodCallback( void* _ecx, void*, size_t paintMode );
    };
}

#endif /* _CLI_PAINTVIRTUALMETHODHOOK_H_ */
