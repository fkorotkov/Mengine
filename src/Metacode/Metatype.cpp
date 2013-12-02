#   include "Metatype.h"

#   include "Interface/UnicodeInterface.h"
#   include "Interface/StringizeInterface.h"

#   include "LoaderEngine.h"

namespace Metabuf
{
	//////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::String & _value, void * _userData )
	{
        (void)_userData;

		size_t size;
		ar.readSize( size );

        if( size == 0 )
        {
            _value.clear();

            return;
        }

		_value.resize( size );

        ar.readCount( &_value[0], size );
	}
	//////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::ConstString & _value, void * _userData )
	{
        Menge::LoaderEngine * loader = static_cast<Menge::LoaderEngine *>(_userData);

		size_t index;
		ar.readSize( index );

        _value = loader->getCacheConstString( index );
	}
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::WChar & _value, void * _userData )
    {   
        size_t size;
        ar.readSize( size );

        char utf8[32];
        ar.readBuffer( (unsigned char *)utf8, size );

        Menge::LoaderEngine * loader = static_cast<Menge::LoaderEngine *>(_userData);
        Menge::ServiceProviderInterface * serviceProvider = loader->getServiceProvider();

        size_t unicodeSize;

        Menge::WChar unicode[2];
        if( UNICODE_SERVICE(serviceProvider)
            ->utf8ToUnicode( utf8, size, unicode, 2, &unicodeSize ) == false )
        {
            throw Metabuf::ArchiveException();

            return;
        }

        if( unicodeSize == 0 )
        {
            throw Metabuf::ArchiveException();

            return;
        }

        _value = unicode[0];
    }
	//////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::WString & _value, void * _userData )
	{
        static Menge::String utf8;
        ar.read( utf8 );

        Menge::LoaderEngine * loader = static_cast<Menge::LoaderEngine *>(_userData);
        Menge::ServiceProviderInterface * serviceProvider = loader->getServiceProvider();

        Menge::Helper::utf8ToUnicode( serviceProvider, utf8, _value );
	}
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::ColourValue & _value, void * _userData )
    {
        (void)_userData;

        float r;
		float g;
		float b;
		float a;
        ar.readPOD( r );
        ar.readPOD( g );
        ar.readPOD( b );
        ar.readPOD( a );

        float coef = 1.f / 255.f;

        r *= coef;
        g *= coef;
        b *= coef;
        a *= coef;

        _value.setARGB( a, r, g, b );
    }
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::GlyphChar & _value, void * _userData )
    {
        (void)_userData;

        size_t code;
        ar.readPOD( code );

        _value.setCode( code );
    }
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::Polygon & _value, void * _userData )
    {
        (void)_userData;

        size_t count;
        ar.readSize(count);

        if( count % 2 != 0 )
        {
            throw Metabuf::ArchiveException();

            return;
        }

        for( size_t i = 0; i != count; i += 2 )
        {
            mt::vec2f v;
            ar.read( v );

            boost::geometry::append( _value, v );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, Menge::Floats & _value, void * _userData )
    {
        (void)_userData;

        size_t count;
        ar.readSize(count);

        _value.resize( count );

        ar.readCount( &_value[0], count );
    }
	//////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, mt::vec2f & _value, void * _userData )
	{
        (void)_userData;

		ar.readPOD( _value.x );
		ar.readPOD( _value.y );
	}
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, mt::vec3f & _value, void * _userData )
    {
        (void)_userData;

        ar.readPOD( _value.x );
        ar.readPOD( _value.y );
        ar.readPOD( _value.z );
    }
    //////////////////////////////////////////////////////////////////////////
    void archive_read( ArchiveReader & ar, mt::vec4f & _value, void * _userData )
    {
        (void)_userData;

        ar.readPOD( _value.x );
        ar.readPOD( _value.y );
        ar.readPOD( _value.z );
        ar.readPOD( _value.w );
    }
}