#include "SurfaceTrackMatte.h"

#include "Interface/RenderSystemInterface.h"
#include "Interface/StringizeServiceInterface.h"

#include "Kernel/ResourceImage.h"

#include "Kernel/Logger.h"
#include "Kernel/Document.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    SurfaceTrackMatte::SurfaceTrackMatte()
        : m_trackMatteMode( ESTM_MODE_NONE )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    SurfaceTrackMatte::~SurfaceTrackMatte()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    bool SurfaceTrackMatte::_initialize()
    {
        m_programVariable = RENDER_SYSTEM()
            ->createProgramVariable( 0, 1, MENGINE_DOCUMENT_FUNCTION );

        if( m_programVariable == nullptr )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void SurfaceTrackMatte::setResourceImage( const ResourceImagePtr & _resourceImage )
    {
        if( m_resourceImage == _resourceImage )
        {
            return;
        }

        this->recompile( [this, _resourceImage]() { m_resourceImage = _resourceImage; } );
    }
    //////////////////////////////////////////////////////////////////////////
    const ResourceImagePtr & SurfaceTrackMatte::getResourceImage() const
    {
        return m_resourceImage;
    }
    //////////////////////////////////////////////////////////////////////////
    void SurfaceTrackMatte::setResourceTrackMatteImage( const ResourceImagePtr & _resourceTrackMatteImage )
    {
        if( m_resourceTrackMatteImage == _resourceTrackMatteImage )
        {
            return;
        }

        this->recompile( [this, _resourceTrackMatteImage]() {m_resourceTrackMatteImage = _resourceTrackMatteImage; } );
    }
    //////////////////////////////////////////////////////////////////////////
    const ResourceImagePtr & SurfaceTrackMatte::getResourceTrackMatteImage() const
    {
        return m_resourceTrackMatteImage;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderProgramVariableInterfacePtr & SurfaceTrackMatte::getProgramVariable() const
    {
        return m_programVariable;
    }
    //////////////////////////////////////////////////////////////////////////
    void SurfaceTrackMatte::setTrackMatteMode( ESurfaceTrackMatteMode _trackMatteMode )
    {
        m_trackMatteMode = _trackMatteMode;
    }
    //////////////////////////////////////////////////////////////////////////
    ESurfaceTrackMatteMode SurfaceTrackMatte::getTrackMatteMode() const
    {
        return m_trackMatteMode;
    }
    //////////////////////////////////////////////////////////////////////////
    const mt::vec2f & SurfaceTrackMatte::getMaxSize() const
    {
        const mt::vec2f & maxSize = m_resourceImage->getMaxSize();

        return maxSize;
    }
    //////////////////////////////////////////////////////////////////////////
    const mt::vec2f & SurfaceTrackMatte::getSize() const
    {
        const mt::vec2f & size = m_resourceImage->getSize();

        return size;
    }
    //////////////////////////////////////////////////////////////////////////
    const mt::vec2f & SurfaceTrackMatte::getOffset() const
    {
        const mt::vec2f & offset = m_resourceImage->getOffset();

        return offset;
    }
    //////////////////////////////////////////////////////////////////////////
    uint32_t SurfaceTrackMatte::getUVCount() const
    {
        return 2;
    }
    //////////////////////////////////////////////////////////////////////////
    const mt::uv4f & SurfaceTrackMatte::getUV( uint32_t _index ) const
    {
        if( _index == 0 )
        {
            return m_resourceImage->getUVTextureImage();
        }
        if( _index == 1 )
        {
            return m_resourceTrackMatteImage->getUVTextureImage();
        }

        return mt::uv4f::identity();
    }
    //////////////////////////////////////////////////////////////////////////
    const Color & SurfaceTrackMatte::getColor() const
    {
        const Color & color = m_resourceImage->getColor();

        return color;
    }
    //////////////////////////////////////////////////////////////////////////
    void SurfaceTrackMatte::correctUV( uint32_t _index, mt::vec2f & _out, const mt::vec2f & _in )
    {
        (void)_index;

        _out = _in;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SurfaceTrackMatte::_compile()
    {
        if( m_resourceImage == nullptr )
        {
            LOGGER_ERROR( "SurfaceTrackMatte::_compile: '%s' resource is null"
                , m_name.c_str()
            );

            return false;
        }

        if( m_resourceImage.compile() == false )
        {
            LOGGER_ERROR( "SurfaceTrackMatte::_compile: '%s' resource '%s' is not compile"
                , m_name.c_str()
                , m_resourceImage->getName().c_str()
            );

            return false;
        }

        if( m_resourceTrackMatteImage == nullptr )
        {
            LOGGER_ERROR( "SurfaceTrackMatte::_compile: '%s' resource is null"
                , m_name.c_str()
            );

            return false;
        }

        if( m_resourceTrackMatteImage.compile() == false )
        {
            LOGGER_ERROR( "SurfaceTrackMatte::_compile: '%s' resource '%s' is not compile"
                , m_name.c_str()
                , m_resourceTrackMatteImage->getName().c_str()
            );

            return false;
        }

        this->invalidateMaterial();

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void SurfaceTrackMatte::_release()
    {
        m_resourceImage.release();
        m_resourceTrackMatteImage.release();
    }
    //////////////////////////////////////////////////////////////////////////
    RenderMaterialInterfacePtr SurfaceTrackMatte::_updateMaterial() const
    {
        RenderTextureInterfacePtr textures[2];

        textures[0] = m_resourceImage->getTexture();
        textures[1] = m_resourceTrackMatteImage->getTexture();

        EMaterialBlendMode blendMode = this->getBlendMode();
        bool premultiply = m_resourceImage->isPremultiply();

        RenderMaterialInterfacePtr material = nullptr;

        switch( m_trackMatteMode )
        {
        case ESTM_MODE_ALPHA:
            {
                switch( blendMode )
                {
                case EMB_NORMAL:
                    {
                        if( premultiply == false )
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_BLEND, PT_TRIANGLELIST, 2, textures );
                        }
                        else
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_BLEND_PREMULTIPLY, PT_TRIANGLELIST, 2, textures );
                        }
                    }break;
                case EMB_ADD:
                    {
                        if( premultiply == false )
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INTENSIVE, PT_TRIANGLELIST, 2, textures );
                        }
                        else
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INTENSIVE_PREMULTIPLY, PT_TRIANGLELIST, 2, textures );
                        }
                    }break;
                default:
                    {
                        LOGGER_ERROR( "SurfaceTrackMatte::_updateMaterial '%s' track matte mode '%d' invalid support blend mode '%d'"
                            , this->getName().c_str()
                            , m_trackMatteMode
                            , blendMode
                        );

                        return nullptr;
                    }break;
                }
            }break;
        case ESTM_MODE_ALPHA_INVERTED:
            {
                switch( blendMode )
                {
                case EMB_NORMAL:
                    {
                        if( premultiply == false )
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INVERTED_BLEND, PT_TRIANGLELIST, 2, textures );
                        }
                        else
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INVERTED_BLEND_PREMULTIPLY, PT_TRIANGLELIST, 2, textures );
                        }
                    }break;
                case EMB_ADD:
                    {
                        if( premultiply == false )
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INVERTED_INTENSIVE, PT_TRIANGLELIST, 2, textures );
                        }
                        else
                        {
                            material = this->getMaterial3( EM_TEXTURE_TRACKMATTE_INVERTED_INTENSIVE_PREMULTIPLY, PT_TRIANGLELIST, 2, textures );
                        }
                    }break;
                default:
                    {
                        LOGGER_ERROR( "SurfaceTrackMatte::_updateMaterial '%s' track matte mode '%d' invalid support blend mode '%d'"
                            , this->getName().c_str()
                            , m_trackMatteMode
                            , blendMode
                        );

                        return nullptr;
                    }break;
                }
            }break;
        default:
            {
                LOGGER_ERROR( "SurfaceTrackMatte::_updateMaterial '%s' invalid support track matte mode '%d'"
                    , this->getName().c_str()
                    , m_trackMatteMode
                );

                return nullptr;
            }break;
        }

        return material;
    }
    //////////////////////////////////////////////////////////////////////////
}
