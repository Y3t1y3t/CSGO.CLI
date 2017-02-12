#ifndef _MEMORY_PATTERNRESOLVER_H_
#define _MEMORY_PATTERNRESOLVER_H_

#pragma once

#include <windows.h>
#include <vector>

namespace Memory
{
    class PatternResolver
    {
    public:
        bool    Resolve( const std::vector<byte>& dataBytes, const std::string& pattern, uintptr_t* resultPtr ) const;

    private:

        bool    IsPatternMatched( std::vector<byte>::const_iterator dataBytes, const std::vector<std::string>& patternBytes ) const;
        size_t  GetByte( const std::string& byte ) const;
    };
}

#endif /* _MEMORY_PATTERNRESOLVER_H_ */
