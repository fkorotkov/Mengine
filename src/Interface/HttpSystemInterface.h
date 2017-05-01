#	pragma once

#	include "Interface/ServiceInterface.h"
#	include "Interface/StreamInterface.h"

#	include "Core/String.h"
#	include "Core/ConstString.h"
#	include "Core/FilePath.h"
#	include "Core/Params.h"

#	include "stdex/stl_map.h"

namespace Menge
{
	//////////////////////////////////////////////////////////////////////////
	typedef uint32_t HttpRequestID;
	//////////////////////////////////////////////////////////////////////////
	class HttpReceiver
	{
	public:
		virtual void onDownloadAssetComplete( HttpRequestID _id, const OutputStreamInterfacePtr & _stream, uint32_t _code, bool _successful ) = 0;
		virtual void onPostMessageComplete( HttpRequestID _id, const String & _response, uint32_t _code, bool _successful ) = 0;
		virtual void onGetMessageComplete( HttpRequestID _id, const String & _response, uint32_t _code, bool _successful ) = 0;
	};
	//////////////////////////////////////////////////////////////////////////
    class HttpSystemInterface
		: public ServiceInterface
	{
		SERVICE_DECLARE("HttpSystem")

	public:
		virtual HttpRequestID getMessage( const String & _url, HttpReceiver * _receiver ) = 0;
		virtual HttpRequestID postMessage( const String & _url, const TMapParams & _params, HttpReceiver * _receiver ) = 0;
		virtual HttpRequestID downloadAsset( const String & _url, const ConstString & _category, const FilePath & _path, HttpReceiver * _receiver ) = 0;

	public:
		virtual bool cancelRequest( HttpRequestID _id ) = 0;
	};

#   define HTTP_SYSTEM( serviceProvider )\
	SERVICE_GET(serviceProvider, Menge::HttpSystemInterface)
}
