#ifndef _CLI_CREATEMOVEVIRTUALMETHODHOOK_H_
#define _CLI_CREATEMOVEVIRTUALMETHODHOOK_H_

#pragma once

#include "../../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/RemoteVirtualMethodHookBase.h"
#include "../../../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

#include "../SharedData/ClientHookSharedData.h"

namespace CLI
{
    class CreateMoveVirtualMethodHook : public Memory::RemoteVirtualMethodHookBase
    {
        static CreateMoveVirtualMethodHook* _self;
        Memory::SharedRemoteProcessService  _remoteProcessService;

    public:

        explicit CreateMoveVirtualMethodHook( Memory::SharedRemoteProcessService remoteProcessService, Memory::SharedRemoteFunctionService remoteFunctionService );
        ~CreateMoveVirtualMethodHook( void );

        static DWORD WINAPI     FunctionCallback( LPVOID paramsPtr );
        static void __fastcall  VirtualMethodCallback( void* ecx, void*, size_t number, float input, bool active );
    };
}

#endif /* _CLI_CREATEMOVEVIRTUALMETHODHOOK_H_ */
