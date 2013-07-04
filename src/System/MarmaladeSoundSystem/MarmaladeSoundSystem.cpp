#	include "MarmaladeSoundSystem.h"
#	include "Config/Config.h"

#	include "MarmaladeError.h"

#	include "Logger/Logger.h"

#	include <algorithm>
#	include <stdio.h>
#	include <stdarg.h>

//////////////////////////////////////////////////////////////////////////
SERVICE_FACTORY( SoundSystem, Menge::SoundSystemInterface, Menge::MarmaladeSoundSystem );
//////////////////////////////////////////////////////////////////////////
namespace Menge
{
#	define MAX_SOUND_SOURCES 32
#	define MAX_SOUND_BUFFERS 16

	//////////////////////////////////////////////////////////////////////////
	MarmaladeSoundSystem::MarmaladeSoundSystem()
		: m_serviceProvider(nullptr)
		, m_context(nullptr)
		, m_device(nullptr)
	{
	}
	//////////////////////////////////////////////////////////////////////////
	MarmaladeSoundSystem::~MarmaladeSoundSystem()
	{     

	}
    //////////////////////////////////////////////////////////////////////////
    void MarmaladeSoundSystem::setServiceProvider( ServiceProviderInterface * _serviceProvider )
    {
        m_serviceProvider = _serviceProvider;
    }
    //////////////////////////////////////////////////////////////////////////
    ServiceProviderInterface * MarmaladeSoundSystem::getServiceProvider() const
    {
        return m_serviceProvider;
    }
	//////////////////////////////////////////////////////////////////////////
	bool MarmaladeSoundSystem::initialize()
	{
		LOGGER_INFO(m_serviceProvider)( "Starting OpenAL Sound System..." );

		//const ALCchar *devices = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);//

		//MENGE_LOG_ERROR( "OALSoundSystem.initialize: devices '%s'"
		//	, devices
		//	);
				
		// open default device
        alcInit();
		
		m_device = alcOpenDevice( NULL );
			
		if( m_device == NULL )
		{
			LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem.initialize: Failed to open 'generic software' sound device try default..." );

			const ALCchar* str = alcGetString( NULL, ALC_DEVICE_SPECIFIER );

            printf("ALC_DEVICE_SPECIFIER [%s]\n"
                , str                
                );

			// ��������� ����������� ����������
			//m_device = alcOpenDevice("Generic Software");
			m_device = alcOpenDevice( "Generic Software" );

			if( m_device == NULL )
			{
				LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem.initialize: Failed to open default sound device try hardware" );

    			// open hardware device
	    		m_device = alcOpenDevice( "Generic Hardware" );	

    			if( m_device == NULL )
	    		{
		    		LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem.initialize: Failed to open hardware sound device.." );

				    return false;
			    }			
            }
		}

		m_context = alcCreateContext( m_device, NULL );

		if( m_context == NULL )
		{
            LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem: Failed to create context" );

			alcCloseDevice( m_device );
			m_device = NULL;

			return false;
		}

		if( alcMakeContextCurrent( m_context ) == ALC_FALSE )
        {
            LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem: Failed to make context current" );

            alcDestroyContext( m_context );
            m_context = NULL;

            alcCloseDevice( m_device );
            m_device = NULL;

            return false;
        }
        		

		LOGGER_INFO(m_serviceProvider)( "OpenAL driver properties" );

		LOGGER_INFO(m_serviceProvider)( "Version: " );
		LOGGER_INFO(m_serviceProvider)( alGetString( AL_VERSION ) );

		LOGGER_INFO(m_serviceProvider)( "Vendor: " );
		LOGGER_INFO(m_serviceProvider)( alGetString( AL_VENDOR ) );

		LOGGER_INFO(m_serviceProvider)( "Renderer: " );
		LOGGER_INFO(m_serviceProvider)( alGetString( AL_RENDERER ) );

		if( alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_TRUE )
		{
			LOGGER_INFO(m_serviceProvider)( "Device Specifier: " );
			LOGGER_INFO(m_serviceProvider)( alcGetString( m_device, ALC_DEVICE_SPECIFIER ) );
		}
		//LOG( alGetString( AL_EXTENSIONS ) );

		float lposition[] = { 0.0f, 0.0f, 0.0f };
		float lvelocity[] = { 0.0f, 0.0f, 0.0f };
		float lorient[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
		alListenerfv( AL_POSITION, lposition );
		alListenerfv( AL_VELOCITY, lvelocity );
		alListenerfv( AL_ORIENTATION, lorient );

		return true;
	}
    //////////////////////////////////////////////////////////////////////////
    void MarmaladeSoundSystem::finalize()
    {
        if( m_device )
        {
            alcMakeContextCurrent( NULL );

            if( m_context )
            {
                alcDestroyContext( m_context );
                m_context = NULL;
            }

#   ifndef _DEBUG
            alcCloseDevice( m_device );
#   endif
            m_device = NULL;
        }
        
        delete this;
    }
	//////////////////////////////////////////////////////////////////////////
	void MarmaladeSoundSystem::onTurnSound( bool _turn )
	{
        (void)_turn;
		//if( _turn == false )
		//{
		//	alcMakeContextCurrent( NULL );
		//	OAL_CHECK_ERROR();

		//	alcSuspendContext( m_context );
		//	OAL_CHECK_ERROR();
		//}
		//else
		//{
		//	alcMakeContextCurrent( m_context );
		//	OAL_CHECK_ERROR();

		//	alcProcessContext( m_context );
		//	OAL_CHECK_ERROR();
		//}
	}
	//////////////////////////////////////////////////////////////////////////
	SoundSourceInterface* MarmaladeSoundSystem::createSoundSource( bool _isHeadMode, SoundBufferInterface * _sample )
	{
		//OALSoundSource* soundSource = m_soundSources.get();
		MarmaladeSoundSource * soundSource = m_poolOALSoundSource.createObjectT();

        soundSource->initialize( m_serviceProvider, this );
        		
		soundSource->setHeadMode( _isHeadMode );
		soundSource->loadBuffer( _sample );

		return soundSource;
	}
	//////////////////////////////////////////////////////////////////////////
	SoundBufferInterface* MarmaladeSoundSystem::createSoundBuffer( const SoundDecoderInterfacePtr & _soundDecoder, bool _isStream )
	{
		MarmaladeSoundBufferBase * base = NULL;

        if( _isStream == false )
        {
            MarmaladeSoundBuffer * buffer = m_poolOALSoundBuffer.createObjectT();
            
            buffer->initialize( m_serviceProvider, this );

            base = buffer;
        }
        else
        {
            MarmaladeSoundBufferStream * buffer = m_poolOALSoundBufferStream.createObjectT();

            buffer->initialize( m_serviceProvider, this );

            base = buffer;
        }

		if( base->load( _soundDecoder ) == false )
		{
			LOGGER_ERROR(m_serviceProvider)( "OALSoundSystem: Failed to create sound buffer from stream" 
				);

			base->destroy();
			
            return nullptr;
		}

		return base;
	}
	//////////////////////////////////////////////////////////////////////////
	ALuint MarmaladeSoundSystem::genSourceId()
	{
		ALuint sourceId = 0;
		alGenSources( 1, &sourceId );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);

		return sourceId;
	}
	//////////////////////////////////////////////////////////////////////////
	void MarmaladeSoundSystem::releaseSourceId( ALuint _sourceId )
	{
		alDeleteSources( 1, &_sourceId );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
	}
	//////////////////////////////////////////////////////////////////////////
	ALuint MarmaladeSoundSystem::genBufferId()
	{
		ALuint bufferId = 0;
		alGenBuffers( 1, &bufferId );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);

		return bufferId;
	}
	//////////////////////////////////////////////////////////////////////////
	void MarmaladeSoundSystem::releaseBufferId( ALuint _bufferId )
	{
		alDeleteBuffers( 1, &_bufferId );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
	}
	//////////////////////////////////////////////////////////////////////////
	void MarmaladeSoundSystem::clearSourceId( ALuint _sourceId )
	{
		ALint process_count = 0;
		// �������� ���������� ������������ �������
		alGetSourcei( _sourceId, AL_BUFFERS_PROCESSED, &process_count );
		MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);

		// ���� ������� ���������� ��
		while( process_count-- > 0 )
		{
			// ��������� �� �� �������
			ALuint buffer = 0;

			alSourceUnqueueBuffers( _sourceId, 1, &buffer );
			MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
		}

		alSourceStop( _sourceId );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);

		ALint queued_count = 0;
		// unqueue remaining buffers
		alGetSourcei( _sourceId, AL_BUFFERS_QUEUED, &queued_count );
		MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);

		while( queued_count-- > 0 )
		{
			// ��������� �� �� �������
			ALuint buffer = 0;

			alSourceUnqueueBuffers( _sourceId, 1, &buffer );
			MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
		}

		ALint state;
		do 
		{			
			alGetSourcei( _sourceId, AL_SOURCE_STATE, &state );
			MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
		}
		while( state == AL_PLAYING );
        
		alSourcei( _sourceId, AL_BUFFER, 0 );
        MARMALADE_SOUND_CHECK_ERROR(m_serviceProvider);
	}
}	// namespace Menge