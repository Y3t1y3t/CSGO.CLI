#ifndef _MEMORY_REMOTEFUNCTION_H_
#define _MEMORY_REMOTEFUNCTION_H_

#pragma once

#include "../RemoteProcessService.h"

namespace Memory
{
    class RemoteFunction
    {
        SharedRemoteProcessService  _remoteProcessService;
        LPVOID                      _functionPtr;
        LPVOID                      _dataPtr;

    public:

        explicit RemoteFunction( SharedRemoteProcessService remoteProcessService = nullptr, LPVOID function = nullptr, LPVOID data = nullptr );
        ~RemoteFunction( void );

        bool    IsValidFunctionPtr( void ) const;
        bool    IsValidDataPtr( void ) const;

        LPVOID  GetFunctionPtr( void ) const;
        void    SetFunctionPtr( LPVOID functionPtr );

        LPVOID  GetDataPtr( void ) const;
        void    SetDataPtr( LPVOID dataPtr );

        template<class T>
        bool    GetDataPtrValue( T* out );

        template<class T>
        bool    SetDataPtrValue( const T& in );
    };

    template <class T>
    bool RemoteFunction::GetDataPtrValue( T* out )
    {
        if( !IsValidDataPtr() )
            return false;
        return _remoteProcessService->Read( GetDataPtr(), out );
    }

    template <class T>
    bool RemoteFunction::SetDataPtrValue( const T& in )
    {
        if( !IsValidDataPtr() )
            return false;
        return _remoteProcessService->Write( GetDataPtr(), in );
    }
}

#endif /* _MEMORY_REMOTEFUNCTION_H_ */