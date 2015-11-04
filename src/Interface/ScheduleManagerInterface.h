#   pragma once

#   include "Interface/ServiceInterface.h"

#   include "Factory/FactorablePtr.h"

namespace Menge
{
    class ScheduleListenerInterface
		: public FactorablePtr
    {
    public:
		virtual bool onScheduleUpdate( uint32_t _id, float _timing ) = 0;
        virtual void onScheduleComplete( uint32_t _id ) = 0;
        virtual void onScheduleStop( uint32_t _id ) = 0;
    };

	typedef stdex::intrusive_ptr<ScheduleListenerInterface> ScheduleListenerInterfacePtr;

    class ScheduleManagerInterface
        : public Factorable
    {
	public:
		virtual void setServiceProvider( ServiceProviderInterface * _serviceProvider ) = 0;
		virtual ServiceProviderInterface * getServiceProvider() const = 0;

    public:
        virtual uint32_t schedule( float _timing, const ScheduleListenerInterfacePtr & _listener ) = 0;

	public:
		virtual uint32_t timing( float _delay, const ScheduleListenerInterfacePtr & _listener ) = 0;

	public:
		virtual bool refresh( uint32_t _id, float _timing ) = 0;

	public:
		virtual bool exist( uint32_t _id ) const = 0;

	public:
        virtual bool remove( uint32_t _id ) = 0;
        virtual void removeAll() = 0;

        virtual bool freeze( uint32_t _id, bool _freeze ) = 0;
        virtual void freezeAll( bool _freeze ) = 0;
		virtual bool isFreezeAll() const = 0;
        virtual bool isFreeze( uint32_t _id ) const = 0;

        virtual float time( uint32_t _id ) const = 0;

	public:
		virtual void setSpeedFactor( float _factor ) = 0;
		virtual float getSpeedFactor() const = 0;

	public:
		virtual float getTiming() const = 0;

    public:
        virtual void update( float _current, float _timing ) = 0;
    };
}