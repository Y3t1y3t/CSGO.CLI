#include "RemoteFunctionResolver.h"

namespace Memory
{
    bool RemoteFunctionResolver::Resolve( void* functionPtr, std::vector<byte>& functionBytes ) const
    {
        auto bytes = static_cast< byte* >( functionPtr );
        if( bytes[ 0 ] == byte( IntelInstructions::JMP ) )
            bytes += *reinterpret_cast< intptr_t* >( &bytes[ 1 ] ) + byte( IntelInstructionsLength::JMP );

        for( ; !IsFunctionRet( bytes - 3 ); ++bytes )
            functionBytes.emplace_back( *bytes );

        return !functionBytes.empty();
    }

    bool RemoteFunctionResolver::IsFunctionRet( byte* bytes ) const
    {
        // _asm retn 01 C2 01 XX
        // _asm INT3    CC
        // _asm INT3    CC
        return bytes[ 0 ] == byte( IntelInstructions::RET )
            && bytes[ 3 ] == byte( IntelInstructions::INT3 )
            && bytes[ 4 ] == byte( IntelInstructions::INT3 );
    }
}
