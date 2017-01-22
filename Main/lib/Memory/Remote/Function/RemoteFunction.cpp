#include "RemoteFunction.h"

namespace Memory
{
    RemoteFunction::RemoteFunction( SharedRemoteProcessService remoteProcessService, LPVOID function, LPVOID data ) :
        _remoteProcessService( remoteProcessService ),
        _functionPtr( function ),
        _dataPtr( data )
    {
    }

    RemoteFunction::~RemoteFunction( void )
    {
        if( _functionPtr != nullptr ) {
            _remoteProcessService->DeallocRemoteData( _functionPtr );
            _functionPtr = nullptr;
        }
        if( _dataPtr != nullptr ) {
            _remoteProcessService->DeallocRemoteData( _dataPtr );
            _dataPtr = nullptr;
        }
    }

    bool RemoteFunction::IsValidFunctionPtr( void ) const
    {
        return _functionPtr != nullptr;
    }

    bool RemoteFunction::IsValidDataPtr( void ) const
    {
        return _dataPtr != nullptr;
    }

    LPVOID RemoteFunction::GetFunctionPtr( void ) const
    {
        return _functionPtr;
    }

    void RemoteFunction::SetFunctionPtr( LPVOID functionPtr )
    {
        _functionPtr = functionPtr;
    }

    LPVOID RemoteFunction::GetDataPtr( void ) const
    {
        return _dataPtr;
    }

    void RemoteFunction::SetDataPtr( LPVOID dataPtr )
    {
        _dataPtr = dataPtr;
    }
}
