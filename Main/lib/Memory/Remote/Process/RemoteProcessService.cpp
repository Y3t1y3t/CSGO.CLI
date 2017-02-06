#include "RemoteProcessService.h"

#include <TlHelp32.h>
#include <thread>
#include <algorithm>

namespace Memory
{
    RemoteProcessService::RemoteProcessService() :
        _remoteProcessDtoFactory( std::make_unique<RemoteProcessDtoFactory>() ),
        _remoteProcessModuleDtoFactory( std::make_unique<RemoteProcessModuleDtoFactory>() ),
        _remoteProcessThreadsProvider( std::make_unique<RemoteProcessThreadsProvider>() ),
        _process( nullptr )
    {
    }

    RemoteProcessService::~RemoteProcessService()
    {
        Detach();
    }

    bool RemoteProcessService::Attach( const std::string& processName, const std::string& windowName, const std::string& windowClassName, DWORD accessRigths )
    {
        Detach();

        while( !_remoteProcessDtoFactory->Create( processName, windowName, windowClassName, accessRigths, &_process ) )
            std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

        return true;
    }

    void RemoteProcessService::Detach()
    {
        if( !IsAlive() )
            return;

        CloseHandle( _process->Handle );
        _process.reset();
    }

    void RemoteProcessService::Suspend() const
    {
        if( !_process )
            return;

        std::vector<DWORD> threadIds;
        if( !_remoteProcessThreadsProvider->Provide( _process->Id, &threadIds ) )
            return;

        std::for_each( threadIds.begin(), threadIds.end(), [ & ] ( DWORD threadId ) -> void {

            auto threadHandle = OpenThread( THREAD_SUSPEND_RESUME, FALSE, threadId );
            if( threadHandle == nullptr )
                return;

            SuspendThread( threadHandle );
            CloseHandle( threadHandle );
        } );
    }

    void RemoteProcessService::Resume() const
    {
        if( !_process )
            return;

        std::vector<DWORD> threadIds;
        if( !_remoteProcessThreadsProvider->Provide( _process->Id, &threadIds ) )
            return;

        std::for_each( threadIds.begin(), threadIds.end(), [ & ] ( DWORD threadId ) -> void {

            auto threadHandle = OpenThread( THREAD_SUSPEND_RESUME, FALSE, threadId );
            if( threadHandle == nullptr )
                return;

            ResumeThread( threadHandle );
            CloseHandle( threadHandle );
        } );
    }

    bool RemoteProcessService::CreateRemoteModule( const std::string& moduleName, std::unique_ptr<RemoteProcessModuleDto>* modulePtr ) const
    {
        if( !_process )
            return false;

        return _remoteProcessModuleDtoFactory->Create( _process->Id, moduleName, modulePtr );
    }

    bool RemoteProcessService::CreateAllocatedRemoteData( const byte* dataPtr, size_t size, LPVOID* allocatedDataPtr ) const
    {
        if( !_process )
            return false;

        auto remoteData = VirtualAllocEx( _process->Handle, nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
        if( remoteData == nullptr )
            return false;

        if( WriteProcessMemory( _process->Handle, remoteData, dataPtr, size, nullptr ) == FALSE )
            return false;

        *allocatedDataPtr = remoteData;
        return true;
    }

    bool RemoteProcessService::FreeAllocatedRemoteData( LPVOID addressPtr ) const
    {
        if( !_process )
            return false;

        return VirtualFreeEx( _process->Handle, addressPtr, 0, MEM_RELEASE ) != FALSE;
    }

    bool RemoteProcessService::CreateRemoteThread( LPVOID entryPoint, LPVOID dataPtr, HANDLE* threadHandlePtr ) const
    {
        if( !_process )
            return false;

        auto remoteThreadHandle = ::CreateRemoteThread( _process->Handle, nullptr, NULL, static_cast< LPTHREAD_START_ROUTINE >( entryPoint ), dataPtr, NULL, nullptr );
        if( remoteThreadHandle == nullptr )
            return false;

        *threadHandlePtr = remoteThreadHandle;
        return true;
    }

    bool RemoteProcessService::CreateSharedHandle( HANDLE handle, DWORD accessRights, HANDLE* duplicatedHandlePtr ) const
    {
        if( !_process )
            return false;

        return DuplicateHandle( handle, handle, _process->Handle, duplicatedHandlePtr, accessRights, FALSE, NULL ) != FALSE;
    }

    bool RemoteProcessService::Read( const uintptr_t& address, LPVOID outPtr, const size_t& size ) const
    {
        if( !_process )
            return false;

        return ReadProcessMemory( _process->Handle, LPCVOID( address ), outPtr, size, nullptr ) != FALSE;
    }

    bool RemoteProcessService::Write( const uintptr_t& address, LPCVOID inPtr, const size_t& size ) const
    {
        if( !_process )
            return false;

        return WriteProcessMemory( _process->Handle, LPVOID( address ), inPtr, size, nullptr ) != FALSE;
    }

    bool RemoteProcessService::IsAlive() const
    {
        if( !_process )
            return false;

        DWORD exitCode;
        if( GetExitCodeProcess( _process->Handle, &exitCode ) == FALSE )
            return false;

        return exitCode == STILL_ACTIVE;
    }
}
