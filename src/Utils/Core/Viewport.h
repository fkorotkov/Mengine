#	pragma once

#	include "Math/box2.h"

namespace Menge
{
	class Viewport
	{
	public:
		Viewport();
		Viewport( const Viewport & _viewport );
		Viewport( const mt::vec2f & _begin, const mt::vec2f & _end );
		Viewport( float _beginX, float _beginY, float _endX, float _endY );

	public:
		void initialize( const mt::vec2f & _begin, const mt::vec2f & _end );

	public:
        bool equalViewport( const Viewport & _vp ) const;

		bool testPoint( const mt::vec2f & _point ) const;
		bool testBBox( const mt::box2f& _bbox ) const;
		bool testRectangle( const mt::vec2f & _min,  const mt::vec2f & _max ) const;

		bool existBBox( const mt::box2f& _bbox ) const;
		bool existRectangle( const mt::vec2f & _min,  const mt::vec2f & _max ) const;

		bool intersectBBox( const mt::box2f& _bbox ) const;

		float getIntersectionSquareBBox( const mt::box2f& _bbox ) const;
		float getSquare() const;

		void toBBox( mt::box2f & _box ) const;

	public:
		void parallax( const mt::vec2f & _factor );
		void scale( const mt::vec2f & _value );
		void inflate( const mt::vec2f & _value );
		void translate( const mt::vec2f & _value );
		void clamp( const Viewport & _vp );

	public:
		float getWidth() const;
		float getHeight() const;

		bool empty() const;

	public:
		void calcSize( mt::vec2f & _size ) const;
		void centerize( const mt::vec2f & _center );
		void getCenter( mt::vec2f & _point ) const;
		
	public:
		mt::vec2f begin;
		mt::vec2f end;
	};
}
