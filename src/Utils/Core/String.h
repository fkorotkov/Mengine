#	pragma once

#	include "Config/Typedef.h"
#	include "Config/String.h"

#	include "Core/ConstString.h"

namespace Menge
{	
	namespace Utils
	{
		const ConstString& emptyConstString();
		
		void split( TVectorString & _outStrings, const String& _str, bool _trimDelims, const String& _delim );
		void wsplit( TVectorWString & _outStrings, const WString& _str, bool _trimDelims, const WString& _delim );

		void split2( TVectorString & _outStrings, const String& _str, bool _trimDelims, const TVectorString & _delims );
		void u32split2( TVectorU32String & _outStrings, const U32String& _str, bool _trimDelims, const TVectorU32String & _delims );

		void join( const String& _delim, const TVectorString& _stringArray, String & _outString );
		void trim( String& str, bool left = true, bool right = true );

		bool intToString( int _value, String & _str );
		bool unsignedToString( uint32_t _value, String & _str );
        bool floatToString( float _value, String & _str );

		bool intToWString( int _value, WString & _str );
		bool unsignedToWString( uint32_t _value, WString & _str );
        bool floatToWString( float _value, WString & _str );

        bool stringToInt( const String & _str, int32_t & _value );
        bool stringToUnsigned( const String & _str, uint32_t & _value );
        bool wstringToFloat( const String & _str, float & _value );

        bool wstringToInt( const WString & _str, int32_t & _value );
        bool wstringToInt2( const WString & _str, int32_t & _value1, int32_t & _value2, bool _separator );
        bool wstringToInt4( const WString & _str, int32_t & _value1, int32_t & _value2, int32_t & _value3, int32_t & _value4, bool _separator );
        bool wstringToUnsigned( const WString & _str, uint32_t & _value );
        bool wstringToFloat( const WString & _str, float & _value );
    }
};
