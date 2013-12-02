#	pragma once

#	include "Codec/ImageDecoder.h"

namespace Menge
{
	class ImageDecoderPVRTZ 
		: public Menge::ImageDecoder
	{
	public:
		ImageDecoderPVRTZ();
		~ImageDecoderPVRTZ();

	public:
		bool _initialize( bool & _version ) override;

	public:
		size_t decode( void * _buffer, size_t _bufferSize ) override;

	private:
		size_t m_uncompress_size;
		size_t m_compress_size;
	};
}