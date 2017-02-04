#ifndef _CLI_HOOKSSERVICE_H_
#define _CLI_HOOKSSERVICE_H_

#pragma

#include "Base/HookBase.h"

#include "../../../lib/Memory/Remote/Function/RemoteFunctionService.h"
#include "../../../lib/Memory/Remote/Hook/RemoteHookService.h"
#include "../../../lib/Memory/Remote/Process/RemoteProcessService.h"

#include <memory>
#include <winnt.h>

namespace CLI
{
    class HooksService
    {
        Memory::SharedRemoteProcessService      _remoteProcessService;
        Memory::SharedRemoteFunctionService     _remoteFunctionService;
        Memory::SharedRemoteHookService         _remoteHookService;
        HANDLE                                  _sharedOriginProcessHandle;
        std::vector<std::unique_ptr<HookBase>>  _hooks;

    public:

        HooksService( Memory::SharedRemoteProcessService remoteProcessService,
               Memory::SharedRemoteFunctionService remoteFunctionService );
        ~HooksService() = default;

        template<class T>
        bool Register( const uintptr_t& instance );
    };

    template <class T>
    bool HooksService::Register( const uintptr_t& instance )
    {
        _hooks.emplace_back( std::make_unique<T>( _remoteProcessService, _remoteFunctionService, _remoteHookService ) );
        return _hooks.at( _hooks.size() - 1 )->Register( instance, _sharedOriginProcessHandle );
    }
};

#endif /* _CLI_HOOKSSERVICE_H_ */
