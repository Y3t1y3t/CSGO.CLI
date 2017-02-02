#ifndef _CSGO_CLIENTCLASS_H_
#define _CSGO_CLIENTCLASS_H_

#pragma once

#include "../../../lib/Memory/Remote/Dto/Base/RemoteDtoBase.h"
#include "../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimpleMember.h"
#include "../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimplePtrMember.h"
#include "../../../lib/Memory/Remote/Dto/Member/RemoteDtoPtrMember.h"

namespace CSGO
{
    class ClientClass;

    typedef Memory::RemoteDtoPtrMember<ClientClass> RemoteClientClass;

    class ClientClass : public Memory::RemoteDtoBase
    {

    public:

        explicit                ClientClass( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base );
                                ~ClientClass( void ) = default;

        Memory::RemoteString    Name    = Memory::RemoteString( 0x8, 32 );
        RemoteClientClass       Next    = RemoteClientClass( 0x10 );
        Memory::RemoteSize      Id      = Memory::RemoteSize( 0x14 );
    };
}

#endif /* _CSGO_CLIENTCLASS_H_ */
