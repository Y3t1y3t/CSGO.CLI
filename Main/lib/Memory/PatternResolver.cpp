#include "PatternResolver.h"

#include "../Util/String.h"

namespace Memory
{
    bool PatternResolver::Resolve( const std::vector<byte>& dataBytes, const std::string& pattern, uintptr_t* resultPtr ) const
    {
        std::vector<std::string> patternBytes;
        if( !Util::StringSplit( pattern, ' ', patternBytes ) )
            return false;

        auto maxOffset = dataBytes.size() - patternBytes.size();
        if( maxOffset <= 0 )
            return false;

        for( auto offset = 0UL; offset < maxOffset; ++offset ) {

            if( !IsPatternMatched( next( dataBytes.begin(), offset ), patternBytes ) )
                continue;

            *resultPtr = offset;
            return true;
        }
        return false;
    }

    bool PatternResolver::IsPatternMatched( std::vector<byte>::const_iterator dataBytes, const std::vector<std::string>& patternBytes ) const
    {
        for( auto& patternByte : patternBytes ) {
            if( patternByte != "?" && GetByte( patternByte ) != *dataBytes )
                return false;
            dataBytes = next( dataBytes );
        }
        return true;
    }

    size_t PatternResolver::GetByte( const std::string& byte ) const
    {
        return ( byte[ 0 ] >= '0' && byte[ 0 ] <= '9'
                 ? byte[ 0 ] - '0'
                 : ( byte[ 0 ] & ~0x20 ) - 'A' + 0xA ) << 4 | ( byte[ 1 ] >= '0' && byte[ 1 ] <= '9'
                                                                ? byte[ 1 ] - '0'
                                                                : ( byte[ 1 ] & ~0x20 ) - 'A' + 0xa );
    }
}
