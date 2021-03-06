#pragma once

#include "Config/Typedef.h"

#include "Interface/AnimationInterface.h"

#include "Kernel/Mixin.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    class Animatable
        : public Mixin
    {
    public:
        virtual AnimationInterface * getAnimation()
        {
            return nullptr;
        };
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<Animatable> AnimatablePtr;
    //////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////
#define DECLARE_ANIMATABLE()\
public:\
    Mengine::AnimationInterface * getAnimation() override{ return this; }\
protected:
