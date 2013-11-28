#   pragma once

#   include "Kernel/Visitor.h"

#   include "Layer2D.h"

namespace Menge
{
    class Arrow;
    class HotSpot;
    class RenderCameraInterface;

    class HotspotMousePickerVisitor
        : public Visitor
        , public ConcreteVisitor<Layer2D>
    {
    public:
        HotspotMousePickerVisitor( HotSpot * _layerspaceHotspot, const RenderCameraInterface * _camera, const mt::vec2f & _point, Arrow * _arrow );

    public:
        bool test( Layer * _layer );

    protected:
        void accept( Layer2D * _visited ) override;

    protected:
        HotSpot * m_hotspot;
        const RenderCameraInterface * m_camera;
        mt::vec2f m_point;
        Arrow * m_arrow;

        bool m_result;
    };
}