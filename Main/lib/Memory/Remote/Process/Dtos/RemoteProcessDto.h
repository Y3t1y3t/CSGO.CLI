#ifndef _MEMORY_REMOTEPROCESSDTO_H_
#define _MEMORY_REMOTEPROCESSDTO_H_

#pragma once

#include "RemoteProcessParamsDto.h"

namespace Memory
{
    class RemoteProcessDto : public RemoteProcessParamsDto
    {
    public:
        DWORD       Id;
        HANDLE      Handle;

        explicit    RemoteProcessDto( RemoteProcessParamsDto dto );
                    ~RemoteProcessDto();

        bool        IsValid() const;
        void        Invalidate();
    };
}

#endif /* _MEMORY_REMOTEPROCESSDTO_H_ */
