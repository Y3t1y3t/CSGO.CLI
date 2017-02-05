#include "RemoteProcessService.h"

#include <TlHelp32.h>
#include <thread>

namespace Memory
{
    RemoteProcessService::RemoteProcessService() :
        _remoteProcessIdProvider( std::make_unique<RemoteProcessIdProvider>() ),
        _remoteProcessHandleProvider( std::make_unique<RemoteProcessHandleProvider>() ),
        _process( nullptr )
    {
    }

    RemoteProcessService::~RemoteProcessService()
    {
        Detach();
    }

    bool RemoteProcessService::Attach( const RemoteProcessParamsDto& process )
    {
        Detach();

        _process = std::make_unique<RemoteProcessDto>( process );

        auto startTick = GetTickCount64();
        auto maxRetryTicks = 1000 * 60 * 5;

        do {
            if( !GetProcessId( &_process->Id ) )
                continue;
            if( !GetProcessHandle( &_process->Handle ) )
                continue;
            return true;
        } while( ![ & ] ( ULONGLONG currentTick ) -> bool {
            auto result = !( maxRetryTicks != 0 ? currentTick - startTick <= maxRetryTicks : true );
            if( !result )
                std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
            return result;
        }( GetTickCount64() ) );
        return false;
    }

    void RemoteProcessService::Detach() const
    {
        if( _process != nullptr )
            _process->Invalidate();
    }

    LPVOID RemoteProcessService::AllocRemoteData( const byte* data, size_t size ) const
    {
        if( !_process->IsValid() )
            return nullptr;

        auto remoteData = VirtualAllocEx( _process->Handle, nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
        if( remoteData == nullptr )
            return nullptr;

        if( WriteProcessMemory( _process->Handle, remoteData, data, size, nullptr ) == FALSE )
            return nullptr;

        return remoteData;
    }

    bool RemoteProcessService::DeallocRemoteData( LPVOID entryPoint ) const
    {
        if( !_process->IsValid() )
            return false;
        return VirtualFreeEx( _process->Handle, entryPoint, 0, MEM_RELEASE ) != FALSE;
    }

    HANDLE RemoteProcessService::StartRemoteThread( LPVOID entryPoint, LPVOID data ) const
    {
        if( !_process->IsValid() )
            return nullptr;
        return CreateRemoteThread( _process->Handle, nullptr, NULL, static_cast< LPTHREAD_START_ROUTINE >( entryPoint ), data, NULL, nullptr );
    }

    bool RemoteProcessService::GetSharedHandle( HANDLE handle, DWORD accessRights, HANDLE *duplicatedHandle ) const
    {
        if( !_process->IsValid() )
            return false;
        return DuplicateHandle( handle, handle, _process->Handle, duplicatedHandle, accessRights, FALSE, NULL ) != FALSE;
    }

    bool RemoteProcessService::Read( const uintptr_t& ptr, LPVOID out, const size_t& size ) const
    {
        if( !_process->IsValid() )
            return false;
        return ReadProcessMemory( _process->Handle, LPCVOID( ptr ), out, size, nullptr ) != FALSE;
    }

    bool RemoteProcessService::Write( const uintptr_t& ptr, LPCVOID in, const size_t& size ) const
    {
        if( !_process->IsValid() )
            return false;
        return WriteProcessMemory( _process->Handle, LPVOID( ptr ), in, size, nullptr ) != FALSE;
    }

    bool RemoteProcessService::IsValid() const
    {
        DWORD processId;
        return GetProcessId( &processId );
    }

    bool RemoteProcessService::GetProcessId( DWORD *processId ) const
    {
        if( _process->WindowName.empty() && _process->WindowClassName.empty() )
            return _remoteProcessIdProvider->ProvideProcessIdByProcessName( _process->ProcessName, processId );
        return _remoteProcessIdProvider->ProvideProcessIdByWindow( _process->WindowName, _process->WindowClassName, processId );
    }

    bool RemoteProcessService::GetProcessHandle( HANDLE *processHandle ) const
    {
        return _remoteProcessHandleProvider->ProvideProcessHandleByProcessIdWithAccessRights( _process->Id, _process->AccessRights, processHandle );
    }
}
