#ifndef _CSGO_RECVTABLEDTO_H_
#define _CSGO_RECVTABLEDTO_H_

#pragma once

#include "../../../../lib/Memory/Remote/Dto/Base/RemoteDtoBase.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimpleMember.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoSimplePtrMember.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoPtrArrayMember.h"
#include "../../../../lib/Memory/Remote/Dto/Member/RemoteDtoPtrMember.h"

namespace CSGO
{
    class RecvTableDto : public Memory::RemoteDtoBase
    {
    public:
        class RecvPropDto : public RemoteDtoBase
        {
            using RemoteRecvTableDto = Memory::RemoteDtoPtrMember<RecvTableDto>;

        public:

            RecvPropDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base );
            ~RecvPropDto() = default;

            Memory::RemoteString    Name = Memory::RemoteString( 0x0, 0x20 );
            RemoteRecvTableDto      Table = RemoteRecvTableDto( 0x28 );
            Memory::RemoteSize      Offset = Memory::RemoteSize( 0x2C );
        };

    private:

        using RemoteRecvPropsDto = Memory::RemoteDtoPtrArrayMember<RecvPropDto>;

    public:

        RecvTableDto( const Memory::SharedRemoteProcessService& remoteProcessService, const uintptr_t& base );
        ~RecvTableDto() = default;
        
        RemoteRecvPropsDto      Props = RemoteRecvPropsDto( 0x0, 0x3C, std::make_unique<Memory::RemoteSize>( 0x4 ) );
        Memory::RemoteString    Name = Memory::RemoteString( 0xC, 0x20 );
    };

    using RemoteRecvTableDto = Memory::RemoteDtoPtrMember<RecvTableDto>;
}

#endif /* _CSGO_RECVTABLEDTO_H_ */
