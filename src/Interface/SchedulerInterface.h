#pragma once

#include "Interface/Interface.h"
#include "Interface/ServiceInterface.h"
#include "Interface/UpdationInterface.h"

#include "Kernel/Factorable.h"
#include "Kernel/ConstString.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    class ScheduleEventInterface
        : public Interface
    {
    public:
        virtual void onScheduleComplete( uint32_t _id ) = 0;
        virtual void onScheduleStop( uint32_t _id ) = 0;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<ScheduleEventInterface> ScheduleEventInterfacePtr;
    //////////////////////////////////////////////////////////////////////////
    class ScheduleTimingInterface
        : public Interface
    {
    public:
        virtual void onScheduleTiming( uint32_t _id, uint32_t _iterate, float _time ) = 0;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<ScheduleTimingInterface> ScheduleTimingInterfacePtr;
    //////////////////////////////////////////////////////////////////////////
    class SchedulePipeInterface
        : public Interface
    {
    public:
        virtual float onSchedulePipe( uint32_t _id, uint32_t _index ) = 0;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<SchedulePipeInterface> SchedulePipeInterfacePtr;
    //////////////////////////////////////////////////////////////////////////
    class SchedulerInterface
        : public Interface
    {
    public:
        virtual bool initialize( const ConstString & _name ) = 0;
        virtual void finalize() = 0;

    public:
        virtual const ConstString & getName() const = 0;

    public:
        virtual uint32_t event( float _delay, const ScheduleEventInterfacePtr & _event ) = 0;

    public:
        virtual uint32_t timing( const SchedulePipeInterfacePtr & _pipe, const ScheduleTimingInterfacePtr & _timing, const ScheduleEventInterfacePtr & _event ) = 0;

    public:
        virtual bool refresh( uint32_t _id ) = 0;

    public:
        virtual bool exist( uint32_t _id ) const = 0;

    public:
        virtual bool remove( uint32_t _id ) = 0;
        virtual void removeAll() = 0;

        virtual bool freeze( uint32_t _id, bool _freeze ) = 0;
        virtual void freezeAll( bool _freeze ) = 0;
        virtual bool isFreezeAll() const = 0;
        virtual bool isFreeze( uint32_t _id ) const = 0;

        virtual float getTimePassed( uint32_t _id ) const = 0;
        virtual float getTimeLeft( uint32_t _id ) const = 0;

    public:
        virtual void setSpeedFactor( float _factor ) = 0;
        virtual float getSpeedFactor() const = 0;

    public:
        virtual float getTime() const = 0;
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<SchedulerInterface> SchedulerInterfacePtr;
    //////////////////////////////////////////////////////////////////////////
}