#ifndef _CSGO_CLIENTCLASSDTO_H_
#define _CSGO_CLIENTCLASSDTO_H_

#pragma once

#include "../../../../lib/Memory/Remote/Dto/Base/RemoteDtoBase.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimpleMember.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimplePtrMember.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoPtrMember.h"

#include "RecvTableDto.h"

namespace CSGO
{
    class ClientClassDto;

    using RemoteClientClass = Memory::RemoteDtoPtrMember<ClientClassDto>;

    class ClientClassDto : public Memory::RemoteDtoBase
    {
    public:
        explicit                ClientClassDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base );
                                ~ClientClassDto() = default;

        Memory::RemoteString    Name    = Memory::RemoteString( 0x8, 0x20 );
        RemoteRecvTableDto      Table   = RemoteRecvTableDto( 0xC );
        RemoteClientClass       Next    = RemoteClientClass( 0x10 );
        Memory::RemoteSize      Id      = Memory::RemoteSize( 0x14 );
    };
}

#endif /* _CSGO_CLIENTCLASSDTO_H_ */
