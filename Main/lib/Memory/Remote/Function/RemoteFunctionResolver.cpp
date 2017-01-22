#include "RemoteFunctionResolver.h"

namespace Memory
{
    bool RemoteFunctionResolver::Resolve( void* functionPtr, std::vector<byte>& functionBytes ) const
    {
        auto bytes = static_cast< byte* >( functionPtr );
        if( bytes[ 0 ] == byte( IntelInstructions::JMP ) )
            bytes += *reinterpret_cast< intptr_t* >( &bytes[ 1 ] ) + byte( IntelInstructionsLength::JMP );

        for( ; !IsAtTheEnd( bytes - 3 ); ++bytes )
            functionBytes.emplace_back( *bytes );

        return !functionBytes.empty();
    }

    bool RemoteFunctionResolver::IsAtTheEnd( byte* bytes ) const
    {
        // _asm retn 1
        return bytes[ 0 ] == 0xC2
            && bytes[ 1 ] == 0x01
            && bytes[ 2 ] == 0x00;
    }
}
