#include "DX9RenderVertexAttribute.h"

#include "Interface/StringizeServiceInterface.h"

#include "DX9RenderEnum.h"
#include "DX9ErrorHelper.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    DX9RenderVertexAttribute::DX9RenderVertexAttribute()
        : m_elementSize( 0 )
        , m_pD3DDevice( nullptr )
        , m_vertexDeclaration( nullptr )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    DX9RenderVertexAttribute::~DX9RenderVertexAttribute()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    bool DX9RenderVertexAttribute::initialize( const ConstString & _name, uint32_t _elementSize )
    {
        m_name = _name;
        m_elementSize = _elementSize;

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool DX9RenderVertexAttribute::compile( IDirect3DDevice9 * _pD3DDevice )
    {
        m_pD3DDevice = _pD3DDevice;

        D3DVERTEXELEMENT9 declaration[64];

        DWORD declaration_iterator = 0;

        for( const Attribute & attribute : m_attributes )
        {
            if( attribute.uniform == STRINGIZE_STRING_LOCAL( "inVert" ) )
            {
                declaration[declaration_iterator++] = { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 };
            }

            if( attribute.uniform == STRINGIZE_STRING_LOCAL( "inCol" ) )
            {
                declaration[declaration_iterator++] = { 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 };
            }

            if( attribute.uniform == STRINGIZE_STRING_LOCAL( "inUV0" ) )
            {
                declaration[declaration_iterator++] = { 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 };
            }

            if( attribute.uniform == STRINGIZE_STRING_LOCAL( "inUV1" ) )
            {
                declaration[declaration_iterator++] = { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 };
            }
        }

        declaration[declaration_iterator] = D3DDECL_END();

        IF_DXCALL( m_pD3DDevice, CreateVertexDeclaration, (declaration, &m_vertexDeclaration) )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    const ConstString & DX9RenderVertexAttribute::getName() const
    {
        return m_name;
    }
    //////////////////////////////////////////////////////////////////////////
    uint32_t DX9RenderVertexAttribute::getElementSize() const
    {
        return m_elementSize;
    }
    //////////////////////////////////////////////////////////////////////////
    bool DX9RenderVertexAttribute::enable()
    {
        DXCALL( m_pD3DDevice, SetVertexDeclaration, (m_vertexDeclaration) );

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void DX9RenderVertexAttribute::disable()
    {
        //DXCALL( m_pD3DDevice, SetVertexDeclaration, (nullptr) );
    }
    //////////////////////////////////////////////////////////////////////////
    void DX9RenderVertexAttribute::addAttribute( const ConstString & _uniform, uint32_t _size, EVertexAttributeType _type, bool _normalized, uint32_t _stride, uint32_t _offset )
    {
        Attribute attr;
        attr.uniform = _uniform;
        attr.size = _size;
        attr.type = _type;
        attr.normalized = _normalized;
        attr.stride = _stride;
        attr.offset = _offset;

        m_attributes.emplace_back( attr );
    }
}