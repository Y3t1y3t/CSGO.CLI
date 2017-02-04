#ifndef _UTIL_REMOTEHANDLESERVICE_H_
#define _UTIL_REMOTEHANDLESERVICE_H_

#pragma once

#pragma comment (lib, "ntdll.lib")

#include <windows.h>
#include <winternl.h>
#include <vector>
#include <functional>

#define STATUS_BAD_DATA                  ((NTSTATUS)0xC000090BL)
#define STATUS_INFO_LENGTH_MISMATCH      ((NTSTATUS)0xC0000004L)

namespace Util
{
    template <class T>
    T* CallNtFunction( std::function<NTSTATUS( PBYTE, PULONG )> ntFunction, std::vector<BYTE>* ntData )
    {
        auto ntDataSize = 0UL;
        NTSTATUS ntStatus;

        do {
            ntStatus = ntFunction( ntDataSize != 0UL ? &ntData->at( 0 ) : nullptr, &ntDataSize );
            if( ntDataSize == 0x0 && ntStatus == STATUS_BAD_DATA )
                return nullptr;
            if( ntStatus == STATUS_INFO_LENGTH_MISMATCH )
                *ntData = std::vector<BYTE>( ntDataSize );
        } while( !NT_SUCCESS( ntStatus ) );

        return reinterpret_cast< T* >( &ntData->at( 0 ) );
    }
}

#endif /* _UTIL_REMOTEHANDLESERVICE_H_ */
