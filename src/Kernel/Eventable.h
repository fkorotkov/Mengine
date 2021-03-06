#pragma once

#include "Interface/EventationInterface.h"

#include "Kernel/Factorable.h"
#include "Kernel/ConstString.h"
#include "Kernel/Mixin.h"

#include "Config/Vector.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    class Eventable
        : public Mixin
    {
    public:
        virtual EventationInterface * getEventation()
        {
            return nullptr;
        };
    };
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<Eventable> EventablePtr;
    //////////////////////////////////////////////////////////////////////////
    namespace Helper
    {
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline static bool hasEventableReceiver( T * _self, uint32_t _event )
        {
            EventationInterface * eventation = _self->getEventation();

            if( eventation == nullptr )
            {
                return false;
            }

            bool exist = eventation->hasEventReceiver( _event );

            return exist;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        inline static bool hasEventableReceiver( const IntrusivePtr<T> & _self, uint32_t _event )
        {
            EventationInterface * eventation = _self->getEventation();

            if( eventation == nullptr )
            {
                return false;
            }

            bool exist = eventation->hasEventReceiver( _event );

            return exist;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        static typename T::EventReceiverType * getThisEventRecieverT( T * _self, uint32_t _event )
        {
            typedef typename T::EventReceiverType * T_EventReceiverTypePtr;

            EventationInterface * eventation = _self->getEventation();

            T_EventReceiverTypePtr reciever = eventation->getEventRecieverT<T_EventReceiverTypePtr>( _event );

            return reciever;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        static typename T::EventReceiverType * getThisEventRecieverT( const IntrusivePtr<T> & _self, uint32_t _event )
        {
            typedef typename T::EventReceiverType * T_EventReceiverTypePtr;

            EventationInterface * eventation = _self->getEventation();

            T_EventReceiverTypePtr reciever = eventation->getEventRecieverT<T_EventReceiverTypePtr>( _event );

            return reciever;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        static T * getThisEventReciever( Eventable * _self, uint32_t _event )
        {
            EventationInterface * eventation = _self->getEventation();

            T * reciever = eventation->getEventRecieverT<T *>( _event );

            return reciever;
        }
        //////////////////////////////////////////////////////////////////////////
        template<class T>
        static T * getThisEventReciever( const EventablePtr & _self, uint32_t _event )
        {
            EventationInterface * eventation = _self->getEventation();

            T * reciever = eventation->getEventRecieverT<T *>( _event );

            return reciever;
        }
    }
}
//////////////////////////////////////////////////////////////////////////
#define DECLARE_EVENTABLE_TYPE( Type )\
public:\
    typedef Type EventReceiverType;
//////////////////////////////////////////////////////////////////////////
#define DECLARE_EVENTABLE( Type )\
public:\
    DECLARE_EVENTABLE_TYPE( Type );\
    Mengine::EventationInterface * getEventation() override{ return this; }\
protected:
//////////////////////////////////////////////////////////////////////////
#define EVENTABLE_METHODR(Event, R)\
    Helper::hasEventableReceiver( this, Event ) == false ? R : Helper::getThisEventRecieverT( this, Event )

#define EVENTABLE_METHOD(Event)\
    EVENTABLE_METHODR(Event, ((void)0))

#define EVENTABLE_OTHER_METHODR(Self, Event, R)\
    Self == nullptr ? R : Helper::hasEventableReceiver( Self, Event ) == false ? R : Helper::getThisEventRecieverT( Self, Event )

#define EVENTABLE_OTHER_METHOD(Self, Event)\
    EVENTABLE_OTHER_METHODR(Self, Event, ((void)0))

#define EVENTABLE_METHODRS(Self, Event, R)\
    Helper::hasEventableReceiver( Self, Event ) == false ? R : Helper::getThisEventRecieverT( Self, Event )

#define EVENTABLE_OTHER_METHODRT(Self, Event, R, Type)\
    Self == nullptr ? R : Helper::hasEventableReceiver( Self, Event ) == false ? R : Helper::getThisEventReciever<Type>( Self, Event )

#define EVENTABLE_OTHER_METHODT(Self, Event, Type)\
    EVENTABLE_OTHER_METHODRT(Self, Event, ((void)0), Type)
