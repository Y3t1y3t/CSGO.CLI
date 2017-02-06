#ifndef _CSGO_ENGINEVGUI_H_
#define _CSGO_ENGINEVGUI_H_

#pragma once
#include "../Base/InterfaceBase.h"

namespace CSGO
{
    class EngineVGui : public InterfaceBase
    {
    public:
        explicit    EngineVGui(const Memory::SharedRemoteFunctionService& remoteFunctionService, const uintptr_t& instance = 0x0);
                    ~EngineVGui() = default;

        std::string GetModuleName() override        { return "engine.dll"; }
        std::string GetInterfaceVersion() override  { return "VEngineVGui001"; }

    private:

        struct Remote
        {
            
        };

    public:


    };

    extern std::unique_ptr<EngineVGui> gEngineVGui;
}

#endif /* _CSGO_ENGINEVGUI_H_ */
