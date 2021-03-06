#pragma once

#include "Interface/ServiceInterface.h"
#include "Interface/TextFontInterface.h"
#include "Interface/TextEntryInterface.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    class TextServiceInterface
        : public ServiceInterface
    {
        SERVICE_DECLARE( "TextService" )

    public:
        virtual bool loadTextEntry( const FileGroupInterfacePtr & _pakName, const FilePath & _path ) = 0;
        virtual bool unloadTextEntry( const FileGroupInterfacePtr & _pakName, const FilePath & _path ) = 0;

    public:
        virtual bool loadFonts( const FileGroupInterfacePtr & _pakName, const FilePath & _path ) = 0;
        virtual bool unloadFonts( const FileGroupInterfacePtr & _pakName, const FilePath & _path ) = 0;

    public:
        virtual bool addTextEntry( const ConstString & _key
            , const String & _text
            , const ConstString & _font
            , const Color & _colorFont
            , float _lineOffset
            , float _charOffset
            , float _maxLength
            , ETextHorizontAlign _horizontAlign
            , ETextVerticalAlign _verticalAlign
            , float _scale
            , uint32_t _params
            , bool _isOverride ) = 0;

    public:
        virtual bool existText( const ConstString& _key, TextEntryInterfacePtr* _entry ) const = 0;
        virtual const TextEntryInterfacePtr & getTextEntry( const ConstString& _key ) const = 0;

    public:
        virtual bool existFont( const ConstString & _name, TextFontInterfacePtr & _font ) const = 0;
        virtual TextFontInterfacePtr getFont( const ConstString & _name ) const = 0;

    public:
        virtual void setTextAlias( const ConstString & _environment, const ConstString& _alias, const ConstString& _key ) = 0;
        virtual void removeTextAlias( const ConstString & _environment, const ConstString& _alias ) = 0;
        virtual bool hasTextAlias( const ConstString & _environment, const ConstString& _alias ) const = 0;
        virtual const ConstString & getTextAlias( const ConstString & _environment, const ConstString& _alias ) const = 0;

    public:
        virtual void setTextAliasArguments( const ConstString & _environment, const ConstString & _alias, const VectorString & _arguments ) = 0;
        virtual void removeTextAliasArguments( const ConstString & _environment, const ConstString & _alias ) = 0;
        virtual bool getTextAliasArguments( const ConstString & _environment, const ConstString & _alias, VectorString & _arguments ) const = 0;

    public:
        typedef Lambda<void( const TextFontInterfacePtr & )> LambdaTextFont;
        virtual void foreachFonts( const LambdaTextFont & _lambda ) = 0;

    public:
        virtual const ConstString & getDefaultFontName() const = 0;

    public:
        virtual bool directFontCompile( const ConstString & _name ) = 0;
        virtual bool directFontRelease( const ConstString & _name ) = 0;

    public:
        virtual bool validate() const = 0;
    };
}
//////////////////////////////////////////////////////////////////////////
#define TEXT_SERVICE()\
	((Mengine::TextServiceInterface*)SERVICE_GET(Mengine::TextServiceInterface))
//////////////////////////////////////////////////////////////////////////
