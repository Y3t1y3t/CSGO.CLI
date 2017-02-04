#include "InterfaceBase.h"

namespace CSGO
{
    InterfaceBase::InterfaceBase( Memory::SharedRemoteFunctionService remoteFunctionService, const uintptr_t& instance ) :
        _remoteFunctionService( remoteFunctionService ),
        _instance( instance )
    {
    }

    InterfaceBase::~InterfaceBase()
    {
    }

    uintptr_t InterfaceBase::GetInstance() const
    {
        return _instance;
    }

    void InterfaceBase::SetInstance( const uintptr_t& instance )
    {
        _instance = instance;
    }
}
