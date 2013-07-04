#	pragma once

#	include "Interface/SoundSystemInterface.h"

#	include <AL/al.h>

namespace Menge
{
	class MarmaladeSoundBufferBase
		: public SoundBufferInterface
	{
	public:
		MarmaladeSoundBufferBase();
		virtual ~MarmaladeSoundBufferBase();

	public:
		void update() override;
        
	public:
		virtual bool load( const SoundDecoderInterfacePtr & _soundDecoder );

		virtual void play( ALenum _source, bool _looped, float _pos );
		virtual	void pause( ALenum _source );
		virtual void stop( ALenum _source );
		virtual bool getTimePos( ALenum _source, float & _pos ) const;

		bool isStereo() const;
		float getTimeTotal() const;

	protected:
        ALenum m_format;

		int m_frequency;
		int m_channels;
		float m_time_total;
		bool m_isStereo;		
	};
}	// namespace Menge