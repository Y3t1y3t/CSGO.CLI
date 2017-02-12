#include "RemoteProcessPatternResolver.h"

namespace Memory
{
    RemoteProcessPatternResolver::RemoteProcessPatternResolver( RemoteProcessReadFn read ) :
        _patternResolver( std::make_unique<PatternResolver>() ),
        _read( read )
    {
    }

    bool RemoteProcessPatternResolver::Resolve( const std::unique_ptr<RemoteProcessModuleDto>& module,
                                                const std::string& pattern,
                                                RemotePatternType patternType,
                                                uintptr_t patternOffset,
                                                uintptr_t resultOffset,
                                                uintptr_t* resultPtr ) const
    {
        auto moduleBytes = std::vector<byte>( module->Size );
        if( !_read( module->Base, &moduleBytes.at( 0 ), module->Size ) )
            return false;

        if( !_patternResolver->Resolve( moduleBytes, pattern, resultPtr ) )
            return false;

        return ResolveByPatternType( module->Base, patternType, patternOffset, resultOffset, resultPtr );
    }

    bool RemoteProcessPatternResolver::ResolveByPatternType( uintptr_t moduleBase,
                                                             RemotePatternType patternType,
                                                             uintptr_t patternOffset,
                                                             uintptr_t resultOffset,
                                                             uintptr_t* resultPtr ) const
    {
        *resultPtr += moduleBase + patternOffset;

        if( ( patternType & RemotePatternType::JmpDestination ) == RemotePatternType::JmpDestination ) {

            uintptr_t jmpValue = 0x0;
            if( !_read( *resultPtr, &jmpValue, sizeof( uintptr_t ) ) )
                return false;

            *resultPtr += jmpValue;
        }

        if( ( patternType & RemotePatternType::Value ) == RemotePatternType::Value && !_read( *resultPtr, resultPtr, sizeof( uintptr_t ) ) )
            return false;

        if( ( patternType & RemotePatternType::Relative ) == RemotePatternType::Relative )
            *resultPtr -= moduleBase;

        *resultPtr += resultOffset;
        return true;
    }
}
