#ifndef _CSGO_CLIENT_H_
#define _CSGO_CLIENT_H_

#pragma once

#include "../Base/InterfaceBase.h"

namespace CSGO
{
    class Client : public InterfaceBase
    {
        std::unique_ptr<Memory::RemoteFunction> _getAllClasses;

    public:

        explicit    Client( Memory::SharedRemoteFunctionService remoteFunctionService, uintptr_t instance = 0x0 );
                    ~Client() = default;

        std::string GetModuleName() override          { return "client.dll"; }
        std::string GetInterfaceVersion() override    { return "VClient018"; }

    private:

        struct Remote
        {
        #pragma region GetAllClasses
            class GetAllClassesParams
            {
            public:
                explicit GetAllClassesParams( const uintptr_t& instance = 0x0 ) :
                    Instance( instance ),
                    Result( 0x0 )
                {
                }

                uintptr_t   Instance;
                uintptr_t   Result;
            };

            static DWORD WINAPI GetAllClasses( LPVOID paramsPtr );
        #pragma endregion;
        };

    public:

        uintptr_t GetAllClasses();
    };

    extern std::unique_ptr<Client> gClient;
}

#endif /* _CSGO_CLIENT_H_ */
