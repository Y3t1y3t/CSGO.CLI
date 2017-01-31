#ifndef _CSGO_CLIENTCLASS_H_
#define _CSGO_CLIENTCLASS_H_

#pragma once

#include "../../../lib/Memory/Remote/Dto/Base/RemoteDtoBase.h"
#include "../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimpleMember.h"

namespace CSGO
{
    class ClientClass : public Memory::RemoteDtoBase
    {
    public:
        explicit ClientClass( const Memory::SharedRemoteProcessService& remoteProcessService );
        ~ClientClass( void ) = default;

        Memory::RemoteSize Id = Memory::RemoteSize( 0x18 );
    };
}

#endif /* _CSGO_CLIENTCLASS_H_ */
