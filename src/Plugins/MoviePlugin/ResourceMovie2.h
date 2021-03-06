#pragma once

#include "Interface/DataInterface.h"

#include "Movie2Interface.h"
#include "Movie2DataInterface.h"

#include "Kernel/Resource.h"
#include "Kernel/Content.h"
#include "Kernel/Viewport.h"
#include "Kernel/Color.h"

#include "Config/Map.h"

#include "math/mat4.h"

#include "movie/movie.hpp"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    struct ResourceMovie2CompositionLayer
    {
        uint32_t index;
        ConstString name;
        ConstString type;
        mt::mat4f matrix;
        Color color;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef Vector<ResourceMovie2CompositionLayer> ResourceMovie2CompositionLayers;
    //////////////////////////////////////////////////////////////////////////
    struct ResourceMovie2CompositionSubComposition
    {
        uint32_t index;
        ConstString name;

        float duration;
        float frameDuration;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef Vector<ResourceMovie2CompositionSubComposition> ResourceMovie2CompositionSubCompositions;
    //////////////////////////////////////////////////////////////////////////
    struct ResourceMovie2CompositionDesc
    {
        float duration;
        float frameDuration;

        bool has_bounds;
        mt::box2f bounds;

        bool master;

        ResourceMovie2CompositionLayers layers;
        ResourceMovie2CompositionSubCompositions subcompositions;
    };
    //////////////////////////////////////////////////////////////////////////
    class ResourceMovie2
        : public Resource
        , public Content
    {
        DECLARE_VISITABLE( Resource );
        DECLARE_CONTENTABLE();
        DECLARE_MAGICABLE( MAGIC_AEZ );

    public:
        ResourceMovie2();
        ~ResourceMovie2() override;

    public:
        bool hasComposition( const ConstString & _name ) const;
        float getCompositionDuration( const ConstString & _name ) const;
        float getCompositionFrameDuration( const ConstString & _name ) const;

    public:
        const Movie2DataInterfacePtr & getMovieData() const;
        const aeMovieCompositionData * getCompositionData( const ConstString & _name ) const;

    public:
        void setCompositionDesc( const ConstString & _name, const ResourceMovie2CompositionDesc & _composition );
        const ResourceMovie2CompositionDesc * getCompositionDesc( const ConstString & _name ) const;

    public:
        typedef Lambda<void( const ConstString &, const ResourceMovie2CompositionDesc & )> LambdaCompositionDescs;
        void foreachCompositionDesc( const LambdaCompositionDescs & _lambda );

    protected:
        bool _compile() override;
        void _release() override;

    protected:
        Movie2DataInterfacePtr m_movieData;

        typedef Map<ConstString, ResourceMovie2CompositionDesc> MapCompositions;
        MapCompositions m_compositions;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<ResourceMovie2, Resource> ResourceMovie2Ptr;
    //////////////////////////////////////////////////////////////////////////
}