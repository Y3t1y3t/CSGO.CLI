#ifndef _CLI_CLIENTHOOKSHAREDDATA_H_
#define _CLI_CLIENTHOOKSHAREDDATA_H_

#pragma once

#include "../../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/SharedData/RemoteVirtualMethodsTableHookSharedData.h"

namespace CLI
{
    class ClientHookSharedData : public Memory::RemoteVirtualMethodsTableHookSharedData
    {
    public:
        explicit    ClientHookSharedData( const uintptr_t& virtualMethodsTablePtr = 0x0, HANDLE sharedOriginProcessHandle = nullptr );
                    ~ClientHookSharedData() = default;

        class CreateMoveVirtualMethod : public VirtualMethodData
        {
        public:
            struct Parameters
            {
                size_t  Number;
                float   Input;
                bool    Active;
            } Params;
        } CreateMoveData;
    };
}

#endif /* _CLI_CLIENTHOOKSHAREDDATA_H_ */