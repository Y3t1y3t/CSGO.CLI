#include "RemoteFunctionResolver.h"

namespace Memory
{
    bool RemoteFunctionResolver::Resolve( void* functionPtr, std::vector<byte>& functionBytes ) const
    {
        auto bytes = static_cast< byte* >( functionPtr );
        if( bytes[ 0 ] == byte( IntelInstructions::JMP ) )
            bytes += *reinterpret_cast< intptr_t* >( &bytes[ 1 ] ) + byte( IntelInstructionsLength::JMP );

        for( ; *bytes != byte( IntelInstructions::INT3 ); ++bytes )
            functionBytes.emplace_back( *bytes );

        return !functionBytes.empty();
    }
}
