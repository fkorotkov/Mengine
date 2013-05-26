#	include "OALSoundBufferBase.h"

#	include "Interface/SoundCodecInterface.h"

namespace Menge
{
	//////////////////////////////////////////////////////////////////////////
	OALSoundBufferBase::OALSoundBufferBase()
        : m_format(0)
        , m_frequency(0)
        , m_channels(0)
        , m_time_total(0.f)
        , m_isStereo(false)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	OALSoundBufferBase::~OALSoundBufferBase()
	{
	}
    //////////////////////////////////////////////////////////////////////////
    bool OALSoundBufferBase::_destroy()
    {
        return true;
    }
	//////////////////////////////////////////////////////////////////////////
	bool OALSoundBufferBase::load( const SoundDecoderInterfacePtr & _soundDecoder )
	{
		// determine data parameters
		const SoundCodecDataInfo * dataInfo = _soundDecoder->getCodecDataInfo();

		m_frequency = dataInfo->frequency;
		m_channels = dataInfo->channels;
		m_time_total = dataInfo->time_total_secs;
		if( m_channels == 1 )
		{
			m_format = AL_FORMAT_MONO16;
			m_isStereo = false;
		}
		else
		{
			m_format = AL_FORMAT_STEREO16;
			m_isStereo = true;
		}

		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	void OALSoundBufferBase::play( ALenum _source, bool _looped, float _pos )
	{
        (void)_source;
        (void)_looped;
        (void)_pos;
		// nothing to do
	}
	//////////////////////////////////////////////////////////////////////////
	void OALSoundBufferBase::pause( ALenum _source )
	{
        (void)_source;
		// nothing to do
	}
	//////////////////////////////////////////////////////////////////////////
	void OALSoundBufferBase::stop( ALenum _source )
	{
        (void)_source;
		// nothing to do
	}
	//////////////////////////////////////////////////////////////////////////
	bool OALSoundBufferBase::getTimePos( ALenum _source, float & _pos ) const
	{
        (void)_source;
        (void)_pos;

		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	bool OALSoundBufferBase::isStereo() const
	{
		return m_isStereo;
	}
	//////////////////////////////////////////////////////////////////////////
	float OALSoundBufferBase::getTimeTotal() const
	{
		return m_time_total;
	}
	//////////////////////////////////////////////////////////////////////////
	void OALSoundBufferBase::update()
	{
		// do nothing
	}
	//////////////////////////////////////////////////////////////////////////
}	// namespace Menge
