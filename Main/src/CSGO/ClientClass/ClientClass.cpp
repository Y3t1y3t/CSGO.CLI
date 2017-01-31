#include "ClientClass.h"

namespace CSGO
{
    ClientClass::ClientClass( const Memory::SharedRemoteProcessService& remoteProcessService ) : RemoteDtoBase{ remoteProcessService }
    {
    }
}
