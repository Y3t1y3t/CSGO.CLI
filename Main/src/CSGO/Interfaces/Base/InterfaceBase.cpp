#include "InterfaceBase.h"

namespace CSGO
{
    InterfaceBase::InterfaceBase( Memory::SharedRemoteFunctionService remoteFunctionService, const uintptr_t& instance ) :
        _remoteFunctionService( remoteFunctionService ),
        _instance( instance )
    {

    }

    uintptr_t InterfaceBase::GetInstance( void ) const
    {
        return _instance;
    }

    void InterfaceBase::SetInstance( uintptr_t instance )
    {
        _instance = instance;
    }
}
