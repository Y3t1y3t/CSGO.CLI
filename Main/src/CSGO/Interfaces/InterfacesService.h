#ifndef _CSGO_INTERFACESSERVICE_H_
#define _CSGO_INTERFACESSERVICE_H_

#pragma once

#include "../../../lib/Memory/Remote/Function/RemoteFunctionParams.h"
#include "../../../lib/Memory/Remote/Function/RemoteFunctionService.h"

// ReSharper disable CppUnusedIncludeDirective
#include "Client/Client.h"
#include "Engine/EngineClient.h"
// ReSharper restore CppUnusedIncludeDirective

#include <memory>

namespace CSGO
{
    class InterfacesService
    {
        Memory::SharedRemoteFunctionService     _remoteFunctionService;
        std::unique_ptr<Memory::RemoteFunction> _getInterfaces;

    public:

        explicit InterfacesService( Memory::SharedRemoteFunctionService remoteFunctionService );
        ~InterfacesService() = default;

    private:

        struct Remote
        {
        #pragma region GetInterface
            class GetInterfaceParams : public Memory::RemoteFunctionParams
            {
            public:
                GetInterfaceParams( const std::string& moduleName, const std::string& interfaceVersion );
                ~GetInterfaceParams() = default;

                using CreateInterfaceFn = uintptr_t( __cdecl* )( const char*, uintptr_t* );
                const char CreateInterface[ 16 ] = "CreateInterface";

                struct Module
                {
                    char Name[ 200 ];
                } Module;

                struct Interface
                {
                    char        Version[ 200 ];
                    uintptr_t   Instance;
                } Interface;
            };

            static DWORD WINAPI GetInterface( LPVOID paramsPtr );
        #pragma endregion
        };

    public:

        template<class T>
        bool Register( std::unique_ptr<T>* interfacePtr );
    };

    template <class T>
    bool InterfacesService::Register( std::unique_ptr<T>* interfacePtr )
    {
        *interfacePtr = std::make_unique<T>( _remoteFunctionService );

        auto params = Remote::GetInterfaceParams( ( *interfacePtr )->GetModuleName(), ( *interfacePtr )->GetInterfaceVersion() );
        if( _getInterfaces == nullptr
            && !_remoteFunctionService->Create( Remote::GetInterface, &params, sizeof( Remote::GetInterfaceParams ), &_getInterfaces )
            || !_getInterfaces->SetDataPtrValue( params ) )
            return false;

        if( !_remoteFunctionService->Execute( _getInterfaces ) )
            return false;

        if( !_getInterfaces->GetDataPtrValue( &params )
            || params.Interface.Instance == 0x0 )
            return false;

        ( *interfacePtr )->SetInstance( params.Interface.Instance );
        return true;
    }
}

#endif /* _CSGO_INTERFACESSERVICE_H_ */
