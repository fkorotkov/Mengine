#include "ResourceImage.h"

#include "Interface/RenderTextureInterface.h"

#include "Kernel/Logger.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    ResourceImage::ResourceImage()
        : m_maxSize( 0.f, 0.f )
        , m_size( 0.f, 0.f )
        , m_offset( 0.f, 0.f )
        , m_uvImageRotate( false )
        , m_uvAlphaRotate( false )
        , m_hasAlpha( false )
        , m_isPremultiply( false )
        , m_isPow2( false )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    ResourceImage::~ResourceImage()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    void ResourceImage::setTexture( const RenderTextureInterfacePtr & _texture )
    {
        m_texture = _texture;
    }
    //////////////////////////////////////////////////////////////////////////
    void ResourceImage::setTextureAlpha( const RenderTextureInterfacePtr & _textureAlpha )
    {
        m_textureAlpha = _textureAlpha;
    }
    //////////////////////////////////////////////////////////////////////////
    void ResourceImage::_release()
    {
        if( m_texture != nullptr )
        {
            const FilePath & filePath = m_texture->getFileName();

            LOGGER_INFO( "ResourceImage::_release %s release texture %s"
                , this->getName().c_str()
                , filePath.c_str()
            );

            m_texture = nullptr;
        }

        if( m_textureAlpha != nullptr )
        {
            const FilePath & filePath = m_textureAlpha->getFileName();

            LOGGER_INFO( "ResourceImage::_release %s release texture alpha %s"
                , this->getName().c_str()
                , filePath.c_str()
            );

            m_textureAlpha = nullptr;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void ResourceImage::correctUVImage( mt::vec2f & _out, const mt::vec2f & _in )
    {
        if( m_uvImageRotate == false )
        {
            mt::uv4_quad_point( _out, m_uvTextureImage, _in );
        }
        else
        {
            mt::multiply_tetragon_uv4_v2( _out, m_uvTextureImage, _in );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void ResourceImage::correctUVAlpha( mt::vec2f & _out, const mt::vec2f & _in )
    {
        if( m_uvAlphaRotate == false )
        {
            mt::uv4_quad_point( _out, m_uvTextureAlpha, _in );
        }
        else
        {
            mt::multiply_tetragon_uv4_v2( _out, m_uvTextureAlpha, _in );
        }
    }
}
