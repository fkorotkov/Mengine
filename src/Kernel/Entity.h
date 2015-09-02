#	pragma once

#   include "Interface/PrototypeManagerInterface.h"

#	include "Node.h"

namespace Menge
{
	class Entity
		: public Node
	{
    public:
        Entity();
        ~Entity();

	public:
		void setPrototype( const ConstString & _prototype );
		const ConstString & getPrototype() const;

	public:
		void setScriptEventable( Eventable * _eventable );
		Eventable * getScriptEventable() const;

	public:
		void setScriptObject( const pybind::object & _object );
		const pybind::object & getScriptObject() const;
		
    public:
        void onCreate();

	protected:
		bool _activate() override;
		void _afterActivate() override;
        
        void _deactivate() override;
		void _afterDeactivate() override;
		
        bool _compile() override;
		void _release() override;
			
	public:
		void destroy() override;
		void _destroy() override;

	protected:
		void _unshallowGrave() override;

	protected:
		ConstString m_prototype;

		Eventable * m_scriptEventable;
		pybind::object m_object;
	};
}