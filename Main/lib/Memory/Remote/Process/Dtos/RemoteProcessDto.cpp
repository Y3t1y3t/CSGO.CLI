#include "RemoteProcessDto.h"

namespace Memory
{
    RemoteProcessDto::RemoteProcessDto( RemoteProcessParamsDto dto ) :
        RemoteProcessParamsDto( dto ),
        Id( 0 ),
        Handle( INVALID_HANDLE_VALUE )
    {
    }

    RemoteProcessDto::~RemoteProcessDto()
    {
        Invalidate();
    }

    bool RemoteProcessDto::IsValid() const
    {
        return Handle != INVALID_HANDLE_VALUE;
    }

    void RemoteProcessDto::Invalidate()
    {
        if( Handle != INVALID_HANDLE_VALUE )
            CloseHandle( Handle );

        Id = 0;
        Handle = INVALID_HANDLE_VALUE;

        RemoteProcessParamsDto::Invalidate();
    }
}
