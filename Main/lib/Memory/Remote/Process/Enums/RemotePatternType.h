#ifndef _MEMORY_REMOTEPATTERNTYPE_H_
#define _MEMORY_REMOTEPATTERNTYPE_H_

#pragma once
#include "../../../../Macros/FlagEnum.h"

namespace Memory
{
    FLAG_ENUM( RemotePatternType )
    {
        Absolute = 0x0,
        Value = 0x1,
        Relative = 0x2,
        JmpDestination = 0x4
    };
}

#endif /* _MEMORY_REMOTEPATTERNTYPE_H_ */
