#pragma once

#include "Interface/ServiceInterface.h"
#include "Interface/StreamInterface.h"

#include "Core/FilePath.h"

namespace Mengine
{
	//////////////////////////////////////////////////////////////////////////
	class FileOutputStreamInterface
		: public OutputStreamInterface
	{
	public:
		virtual bool open( const FilePath & _relationPath, const FilePath & _folderPath, const FilePath & _filePath ) = 0;
	};
    //////////////////////////////////////////////////////////////////////////
    typedef IntrusivePtr<FileOutputStreamInterface> FileOutputStreamInterfacePtr;
	//////////////////////////////////////////////////////////////////////////
}


