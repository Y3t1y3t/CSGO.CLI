#include "RemoteHandleService.h"

namespace Memory
{
    bool RemoteHandleService::GetSystemHandlesForProcessId( ULONG processId, std::vector<SystemHandle> *handles ) const
    {
        std::vector<byte> querySystemInformationData;

        auto handleInfo = Util::CallNtFunction<SystemHandleInformation>( [] ( byte* ntData, ULONG* ntDataSize ) -> NTSTATUS {
            return NtQuerySystemInformation( SYSTEM_INFORMATION_CLASS( SystemInfoClass::SystemHandleInformation ), ntData, *ntDataSize, ntDataSize );
        }, &querySystemInformationData );

        for( auto count = 0UL; count < handleInfo->HandleCount; ++count ) {
            if( handleInfo->Handles[ count ].UniqueProcessId != processId )
                continue;
            handles->emplace_back( handleInfo->Handles[ count ] );
        }
        return !handles->empty();
    }
}