#	pragma once

#	include "Kernel/ResourceReference.h"

#	include "Math/vec4.h"

#	include "Core/BinaryVector.h"

namespace Menge
{
	class Glyph
	{
	public:
        Glyph();
		Glyph( const mt::vec4f & _uv, const mt::vec2f & _offset, float _ratio, const mt::vec2f & _size );

	public:
		const mt::vec4f & getUV() const;
		const mt::vec2f & getOffset() const;
		float getRatio() const;
		const mt::vec2f & getSize() const;

	public:
		void addKerning( WChar _char, float _kerning );
		float getKerning( WChar _char ) const;

	protected:
		mt::vec4f m_uv;
		mt::vec2f m_offset;
		float m_ratio;
		mt::vec2f m_size;

		typedef BinaryVector<WChar, float> TMapKerning;
		TMapKerning m_kernings;
	};
}