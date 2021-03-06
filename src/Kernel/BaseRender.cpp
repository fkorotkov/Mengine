#include "Kernel/BaseRender.h"

#include "Interface/RenderServiceInterface.h"

#include "Kernel/Assertion.h"

#include <algorithm>

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    BaseRender::BaseRender()
        : m_relationRender( nullptr )
        , m_externalRender( false )
        , m_renderEnable( false )
        , m_hide( false )
        , m_localHide( false )
        , m_rendering( false )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    BaseRender::~BaseRender()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRelationRender( RenderInterface * _relationRender )
    {
        MENGINE_ASSERTION( _relationRender != nullptr, ("set nullptr relation render") );
        MENGINE_ASSERTION( _relationRender != this, ("set this relation render") );

        if( m_relationRender != nullptr )
        {
            m_relationRender->removeRelationRenderChildren_( this );
        }

        m_relationRender = static_cast<BaseRender *>(_relationRender);

        m_relationRender->addRelationRenderChildrenBack_( this );

        this->invalidateColor();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRelationRenderFront( RenderInterface * _relationRender )
    {
        MENGINE_ASSERTION( _relationRender != nullptr, ("set nullptr relation render") );
        MENGINE_ASSERTION( _relationRender != this, ("set this relation render") );

        if( m_relationRender != nullptr )
        {
            m_relationRender->removeRelationRenderChildren_( this );
        }

        m_relationRender = static_cast<BaseRender *>(_relationRender);

        m_relationRender->addRelationRenderChildrenFront_( this );

        this->invalidateColor();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::removeRelationRender()
    {
        if( m_relationRender == nullptr )
        {
            return;
        }

        m_relationRender->removeRelationRenderChildren_( this );
        m_relationRender = nullptr;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::moveRelationRenderFront( RenderInterface * _childRender )
    {
        MENGINE_ASSERTION( m_relationRenderChildren.empty() == false, ("move child is empty") );

        BaseRender * childRender = static_cast<BaseRender *>(_childRender);

        BaseRender * frontRender = m_relationRenderChildren.front();

        if( frontRender == childRender )
        {
            return;
        }

        this->removeRelationRenderChildren_( childRender );
        this->addRelationRenderChildrenFront_( childRender );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::moveRelationRenderBack( RenderInterface * _childRender )
    {
        MENGINE_ASSERTION( m_relationRenderChildren.empty() == false, ("move child is empty") );

        BaseRender * childRender = static_cast<BaseRender *>(_childRender);

        BaseRender * backRender = m_relationRenderChildren.back();

        if( backRender == childRender )
        {
            return;
        }

        this->removeRelationRenderChildren_( childRender );
        this->addRelationRenderChildrenBack_( childRender );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::foreachChildren( const LambdaRender & _lambda )
    {
        for( RenderInterface * child : m_relationRenderChildren )
        {
            _lambda( child );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRenderEnable( bool _renderEnable )
    {
        m_renderEnable = _renderEnable;

        this->updateRendering_();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setHide( bool _hide )
    {
        if( m_hide == _hide )
        {
            return;
        }

        m_hide = _hide;

        this->_setHide( _hide );

        this->updateRendering_();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::_setHide( bool _hide )
    {
        MENGINE_UNUSED( _hide );

        //Empty
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setLocalHide( bool _localHide )
    {
        if( m_localHide == _localHide )
        {
            return;
        }

        m_localHide = _localHide;

        this->_setLocalHide( _localHide );

        this->updateRendering_();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::_setLocalHide( bool _localHide )
    {
        MENGINE_UNUSED( _localHide );

        //Empty
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRelationRenderChildrenBack_( BaseRender * _childRender )
    {
        m_relationRenderChildren.push_back( _childRender );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRelationRenderChildrenFront_( BaseRender * _childRender )
    {
        m_relationRenderChildren.insert( m_relationRenderChildren.begin(), _childRender );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::removeRelationRenderChildren_( BaseRender * _childRender )
    {
        VectorBaseRender::iterator it_erase = std::find( m_relationRenderChildren.begin(), m_relationRenderChildren.end(), _childRender );

        MENGINE_ASSERTION( it_erase != m_relationRenderChildren.end(), ("remove relation child is not found") );

        m_relationRenderChildren.erase( it_erase );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRenderViewport( const RenderViewportInterfacePtr & _viewport )
    {
        m_renderViewport = _viewport;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderViewportInterfacePtr & BaseRender::getRenderViewport() const
    {
        return m_renderViewport;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRenderCamera( const RenderCameraInterfacePtr & _camera )
    {
        m_renderCamera = _camera;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderCameraInterfacePtr & BaseRender::getRenderCamera() const
    {
        return m_renderCamera;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRenderScissor( const RenderScissorInterfacePtr & _scissor )
    {
        m_renderScissor = _scissor;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderScissorInterfacePtr & BaseRender::getRenderScissor() const
    {
        return m_renderScissor;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setRenderTarget( const RenderTargetInterfacePtr & _target )
    {
        m_renderTarget = _target;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderTargetInterfacePtr & BaseRender::getRenderTarget() const
    {
        return m_renderTarget;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::renderWithChildren( const RenderContext * _context, bool _external ) const
    {
        if( m_rendering == false )
        {
            return;
        }

        if( m_externalRender == true && _external == false )
        {
            return;
        }

        RenderContext context;

        context.viewport = m_renderViewport != nullptr ? m_renderViewport : _context->viewport;
        context.camera = m_renderCamera != nullptr ? m_renderCamera : _context->camera;
        context.scissor = m_renderScissor != nullptr ? m_renderScissor : _context->scissor;
        context.target = m_renderTarget != nullptr ? m_renderTarget : _context->target;

        if( m_localHide == false && this->isPersonalTransparent() == false )
        {
            this->render( &context );
        }

        for( const BaseRender * child : m_relationRenderChildren )
        {
            child->renderWithChildren( &context, false );
        }

        if( context.target != nullptr )
        {
            const RenderInterfacePtr & targetRender = this->makeTargetRender( &context );

            if( targetRender != nullptr )
            {
                targetRender->render( _context );
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderInterfacePtr & BaseRender::makeTargetRender( const RenderContext * _context ) const
    {
        MENGINE_UNUSED( _context );

        return RenderInterfacePtr::none();
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::setExternalRender( bool _externalRender )
    {
        if( m_externalRender == _externalRender )
        {
            return;
        }

        m_externalRender = _externalRender;

        this->_setExternalRender( _externalRender );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::_setExternalRender( bool _externalRender )
    {
        MENGINE_UNUSED( _externalRender );

        //Empty
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRenderMesh( const RenderContext * _context, const RenderMaterialInterfacePtr & _material
        , const RenderVertexBufferInterfacePtr & _vertexBuffer
        , const RenderIndexBufferInterfacePtr & _indexBuffer
        , uint32_t _indexCount ) const
    {
        RENDER_SERVICE()
            ->addRenderMesh( _context, _material, _vertexBuffer, _indexBuffer, _indexCount );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRenderObject( const RenderContext * _context, const RenderMaterialInterfacePtr & _material
        , const RenderProgramVariableInterfacePtr & _variable
        , const RenderVertex2D * _vertices, uint32_t _vertexCount
        , const RenderIndex * _indices, uint32_t _indexCount
        , const mt::box2f * _bb, bool _debug ) const
    {
        RENDER_SERVICE()
            ->addRenderObject( _context, _material, _variable, _vertices, _vertexCount, _indices, _indexCount, _bb, _debug );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRenderQuad( const RenderContext * _context, const RenderMaterialInterfacePtr & _material
        , const RenderVertex2D * _vertices, uint32_t _vertexCount
        , const mt::box2f * _bb, bool _debug ) const
    {
        RENDER_SERVICE()
            ->addRenderQuad( _context, _material, _vertices, _vertexCount, _bb, _debug );
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::addRenderLine( const RenderContext * _context, const RenderMaterialInterfacePtr & _material
        , const RenderVertex2D * _vertices, uint32_t _vertexCount
        , const mt::box2f * _bb, bool _debug ) const
    {
        RENDER_SERVICE()
            ->addRenderLine( _context, _material, _vertices, _vertexCount, _bb, _debug );
    }
    //////////////////////////////////////////////////////////////////////////
    RenderVertex2D * BaseRender::getDebugRenderVertex2D( uint32_t _count ) const
    {
        RenderVertex2D * vertices = RENDER_SERVICE()
            ->getDebugRenderVertex2D( _count );

        return vertices;
    }
    //////////////////////////////////////////////////////////////////////////
    const RenderMaterialInterfacePtr & BaseRender::getDebugMaterial() const
    {
        const RenderMaterialInterfacePtr & debugMaterial = RENDERMATERIAL_SERVICE()
            ->getDebugLineMaterial();

        return debugMaterial;
    }
    //////////////////////////////////////////////////////////////////////////
    const Color & BaseRender::getWorldColor() const
    {
        if( m_relationRender == nullptr )
        {
            const Color & localColor = Colorable::getLocalColor();

            return localColor;
        }

        if( Colorable::isInvalidateColor() == false )
        {
            const Color & relationColor = Colorable::getRelationColor();

            return relationColor;
        }

        const Color & parentColor = m_relationRender->getWorldColor();

        const Color & relationColor = Colorable::updateRelationColor( parentColor );

        return relationColor;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::calcTotalColor( Color & _color ) const
    {
        const Color & worldColor = this->getWorldColor();
        _color = worldColor;

        const Color & personalColor = this->getPersonalColor();
        _color *= personalColor;
    }
    //////////////////////////////////////////////////////////////////////////
    bool BaseRender::isSolidColor() const
    {
        const Color & worldColour = this->getWorldColor();

        float worldAlpha = worldColour.getA();
        float personalAlpha = this->getPersonalAlpha();

        bool solid = mt::equal_f_f( worldAlpha * personalAlpha, 1.f );

        return solid;
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::invalidateColor()
    {
        Colorable::invalidateColor();

        for( BaseRender * child : m_relationRenderChildren )
        {
            child->invalidateColor();
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void BaseRender::updateRendering_()
    {
        m_rendering = false;

        if( this->isRenderEnable() == false )
        {
            return;
        }

        if( this->isHide() == true )
        {
            return;
        }

        if( this->isLocalTransparent() == true )
        {
            return;
        }

        m_rendering = true;
    }
}
