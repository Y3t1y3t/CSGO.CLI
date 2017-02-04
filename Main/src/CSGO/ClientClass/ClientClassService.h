#ifndef _CSGO_CLIENTCLASSSERVICE_H_
#define _CSGO_CLIENTCLASSSERVICE_H_

#pragma once

#include "Dtos/ClientClassDto.h"

#include <memory>

namespace CSGO
{
    class ClientClassService
    {
        std::unique_ptr<ClientClassDto> _clientClassPtr;

    public:

        ClientClassService( Memory::SharedRemoteProcessService remoteProcessService, const uintptr_t& allClassesPtr );
        ~ClientClassService() = default;

        size_t          GetRecvPropOffset( const std::string& tableName, const std::string& propName ) const;

    private:

        size_t          FindRecvPropOffset( RecvTableDto* table, const char* name, size_t offset ) const;
        RecvTableDto*   FindRecvTablePtr( const char* name ) const;
    };
}

#endif /* _CSGO_CLIENTCLASSSERVICE_H_ */
