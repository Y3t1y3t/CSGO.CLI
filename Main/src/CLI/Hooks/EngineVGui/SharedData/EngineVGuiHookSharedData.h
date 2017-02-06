#ifndef _CLI_ENGINEVGUIHOOKSHAREDDATA_H_
#define _CLI_ENGINEVGUIHOOKSHAREDDATA_H_

#pragma once

#include "../../../../../lib/Memory/Remote/Hook/VirtualMethodsTable/SharedData/RemoteVirtualMethodsTableHookSharedData.h"

namespace CLI
{
    class EngineVGuiHookSharedData : public Memory::RemoteVirtualMethodsTableHookSharedData
    {
    public:
        explicit    EngineVGuiHookSharedData(const uintptr_t& virtualMethodsTablePtr = 0x0, HANDLE sharedOriginProcessHandle = nullptr);
                    ~EngineVGuiHookSharedData() = default;

        class PaintVirtualMethod : public VirtualMethodData
        {
        public:
            struct Parameters
            {
                size_t      PaintMode;
            } Params;
        } PaintData;
    };
}

#endif /* _CLI_ENGINEVGUIHOOKSHAREDDATA_H_ */
