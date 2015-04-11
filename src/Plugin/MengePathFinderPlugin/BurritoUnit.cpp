#	include "BurritoUnit.h"

namespace Menge
{
	//////////////////////////////////////////////////////////////////////////
	BurritoUnit::BurritoUnit()
		: m_node(nullptr)
		, m_radius(0.f)
		, m_velocity(0.f, 0.f, 0.f)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	BurritoUnit::~BurritoUnit()
	{
	}
	//////////////////////////////////////////////////////////////////////////
	void BurritoUnit::initialize( Node * _node, float _radius )
	{
		m_node = _node;
		m_radius = _radius;
	}
	//////////////////////////////////////////////////////////////////////////
	void BurritoUnit::setVelocity( const mt::vec3f & _velocity )
	{
		m_velocity = _velocity;
	}
	//////////////////////////////////////////////////////////////////////////
	const mt::vec3f & BurritoUnit::getVelocity() const
	{
		return m_velocity;
	}
}