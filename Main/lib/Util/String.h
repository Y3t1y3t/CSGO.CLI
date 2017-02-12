#ifndef _UTIL_STRING_H_
#define _UTIL_STRING_H_

#pragma once

#include <algorithm>
#include <functional>
#include <memory>

namespace Util
{
    inline void StringSplit( const std::string& str, const char delimiter, std::function<void( const std::string::const_iterator&, const std::string::const_iterator& )> callback, int startOffset = 0, int endOffset = 0 )
    {
        if( str.find( delimiter ) == std::string::npos )
            return;

        auto start = next(str.begin(), startOffset);
        auto end = prev( str.end(), endOffset );

        auto pos = find( start, end, delimiter );
        while( pos != end ) {
            callback( start, pos );

            start = next( pos );
            pos = find( start, end, delimiter );
        }
        callback( start, pos );
    }

    inline bool StringSplit( const std::string& str, const char delimiter, std::vector<std::string>& splittedStrs, int startOffset = 0, int endOffset = 0 )
    {
        StringSplit( str, delimiter, [ & ] ( const std::string::const_iterator& start, const std::string::const_iterator& next ) -> void {
            splittedStrs.emplace_back( std::string( start, next ) );
        }, startOffset, endOffset );
        return !splittedStrs.empty();
    }

    template<typename ... Args>
    std::string StringFormat( const std::string& format, Args ... args )
    {
        size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
        std::unique_ptr<char[]> buf( new char[ size ] );
        snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 );
    }

    inline void StringErase( std::string& str, const char delimiter )
    {
        str.erase( remove( str.begin(), str.end(), delimiter ), str.end() );
    }

    inline bool StringStartsWith( const std::string& str, const std::string& prefix )
    {
        return equal( prefix.begin(), prefix.end(), str.begin() );
    }
}

#endif /* _UTIL_STRING_H_ */
