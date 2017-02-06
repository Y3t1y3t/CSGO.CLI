#include "RemoteProcessModuleDto.h"

namespace Memory
{
    RemoteProcessModuleDto::RemoteProcessModuleDto( uintptr_t moduleBase, size_t moduleSize ) :
        Base( moduleBase ),
        Size( moduleSize )
    {
    }
}
