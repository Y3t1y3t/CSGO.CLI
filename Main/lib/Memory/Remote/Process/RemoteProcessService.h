#ifndef _MEMORY_REMOTEPROCESS_H_
#define _MEMORY_REMOTEPROCESS_H_

#pragma once

#include "Consts/RemoteProcessConsts.h"

#include "Dtos/RemoteProcessDto.h"
#include "Dtos/RemoteProcessModuleDto.h"

#include "Factories/RemoteProcessDtoFactory.h"
#include "Factories/RemoteProcessModuleDtoFactory.h"

#include "Providers/RemoteProcessThreadsProvider.h"

#include <windows.h>
#include <memory>

namespace Memory
{
    class RemoteProcessService
    {
        std::unique_ptr<RemoteProcessDtoFactory>        _remoteProcessDtoFactory;
        std::unique_ptr<RemoteProcessModuleDtoFactory>  _remoteProcessModuleDtoFactory;
        std::unique_ptr<RemoteProcessThreadsProvider>   _remoteProcessThreadsProvider;
        std::unique_ptr<RemoteProcessDto>               _process;

    public:

                                    RemoteProcessService();
                                    ~RemoteProcessService();

        bool                        Attach( const std::string& processName,
                                            const std::string& windowName = std::string(),
                                            const std::string& windowClassName = std::string(),
                                            DWORD accessRigths = RemoteProcessConsts::AccessRights );
        void                        Detach();
        
        void                        Suspend() const;
        void                        Resume() const;

        bool                        CreateRemoteModule( const std::string& moduleName, std::unique_ptr<RemoteProcessModuleDto>* modulePtr ) const;

        bool                        CreateAllocatedRemoteData( const byte* dataPtr, size_t size, LPVOID* allocatedDataPtr ) const;
        bool                        FreeAllocatedRemoteData( LPVOID addressPtr ) const;

        bool                        CreateRemoteThread( LPVOID entryPoint, LPVOID dataPtr, HANDLE* threadHandlePtr ) const;
        bool                        CreateSharedHandle( HANDLE handle, DWORD accessRights, HANDLE* duplicatedHandlePtr ) const;

        bool                        Read( const uintptr_t& address, LPVOID out, const size_t& size ) const;
        template<class T> bool      Read( LPCVOID address, T* outPtr ) const;
        template<class T> bool      Read( const uintptr_t& address, T* outPtr ) const;

        bool                        Write( const uintptr_t& address, LPCVOID in, const size_t& size ) const;
        template<class T> bool      Write( LPVOID address, const T& in ) const;
        template<class T> bool      Write( const uintptr_t& address, const T& in ) const;

        bool                        IsAlive() const;
    };

    template <class T>
    bool RemoteProcessService::Read( LPCVOID address, T* outPtr ) const
    {
        return Read( uintptr_t( address ), outPtr, sizeof( T ) );
    }

    template <class T>
    bool RemoteProcessService::Read( const uintptr_t& address, T* outPtr ) const
    {
        return Read( address, outPtr, sizeof( T ) );
    }

    template <class T>
    bool RemoteProcessService::Write( LPVOID address, const T& in ) const
    {
        return Write( uintptr_t( address ), LPCVOID( &in ), sizeof( T ) );
    }

    template <class T>
    bool RemoteProcessService::Write( const uintptr_t& address, const T& in ) const
    {
        return Write( address, LPCVOID( &in ), sizeof( T ) );
    }

    using SharedRemoteProcessService = std::shared_ptr<RemoteProcessService>;
}

#endif /* _MEMORY_REMOTEPROCESS_H_ */
