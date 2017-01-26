#ifndef _CSGO_INTERFACEBASE_H_
#define _CSGO_INTERFACEBASE_H_

#pragma once

#include "../../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

#include <windows.h>

namespace CSGO
{
    class InterfaceBase
    {
    protected:
        Memory::SharedRemoteFunctionService     _remoteFunctionService;
        uintptr_t                               _instance;

    public:

        explicit    InterfaceBase( Memory::SharedRemoteFunctionService remoteFunctionService, const uintptr_t& instance );
                    ~InterfaceBase( void ) = default;

        uintptr_t   GetInstance( void ) const;
        void        SetInstance( uintptr_t instance );
    };
}

#endif /* _CSGO_INTERFACEBASE_H_ */
