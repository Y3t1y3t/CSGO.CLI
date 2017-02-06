#include "RemoteFunction.h"

namespace Memory
{
    RemoteFunction::RemoteFunction( SharedRemoteProcessService remoteProcessService, LPVOID function, LPVOID data ) :
        _remoteProcessService( remoteProcessService ),
        _functionPtr( function ),
        _dataPtr( data )
    {
    }

    RemoteFunction::~RemoteFunction()
    {
        if( _functionPtr != nullptr ) {
            _remoteProcessService->FreeAllocatedRemoteData( _functionPtr );
            _functionPtr = nullptr;
        }
        if( _dataPtr != nullptr ) {
            _remoteProcessService->FreeAllocatedRemoteData( _dataPtr );
            _dataPtr = nullptr;
        }
    }

    bool RemoteFunction::IsValidFunctionPtr() const
    {
        return _functionPtr != nullptr;
    }

    bool RemoteFunction::IsValidDataPtr() const
    {
        return _dataPtr != nullptr;
    }

    LPVOID RemoteFunction::GetFunctionPtr() const
    {
        return _functionPtr;
    }

    void RemoteFunction::SetFunctionPtr( LPVOID functionPtr )
    {
        _functionPtr = functionPtr;
    }

    LPVOID RemoteFunction::GetDataPtr() const
    {
        return _dataPtr;
    }

    void RemoteFunction::SetDataPtr( LPVOID dataPtr )
    {
        _dataPtr = dataPtr;
    }
}
