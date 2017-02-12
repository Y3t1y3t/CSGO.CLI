#ifndef _MEMORY_REMOTEPROCESSPATTERNRESOLVER_H_
#define _MEMORY_REMOTEPROCESSPATTERNRESOLVER_H_

#pragma once

#include "../../../PatternResolver.h"

#include "../Dtos/RemoteProcessModuleDto.h"
#include "../Enums/RemotePatternType.h"

#include <windows.h>
#include <memory>
#include <functional>

namespace Memory
{
    using RemoteProcessReadFn = std::function<bool( const uintptr_t&, LPVOID, const size_t& )>;

    class RemoteProcessPatternResolver
    {
        std::unique_ptr<PatternResolver>    _patternResolver;
        RemoteProcessReadFn                 _read;

    public:

        explicit    RemoteProcessPatternResolver( RemoteProcessReadFn read );
                    ~RemoteProcessPatternResolver() = default;

        bool        Resolve( const std::unique_ptr<RemoteProcessModuleDto>& module,
                             const std::string& pattern,
                             RemotePatternType patternType,
                             uintptr_t patternOffset,
                             uintptr_t resultOffset,
                             uintptr_t* resultPtr ) const;

    private:

        bool        ResolveByPatternType( uintptr_t moduleBase,
                                          RemotePatternType patternType,
                                          uintptr_t patternOffset,
                                          uintptr_t resultOffset,
                                          uintptr_t* resultPtr ) const;
    };
}

#endif /* _MEMORY_REMOTEPROCESSPATTERNRESOLVER_H_ */
