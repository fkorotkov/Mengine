#include "SDLFileGroupDirectory.h"

#include "Interface/UnicodeSystemInterface.h"
#include "Interface/PlatformInterface.h"

#include "SDLFileInputStream.h"
#include "SDLFileOutputStream.h"
#include "SDLFileMappedStream.h"
#include "SDLFileHelper.h"

#include "Kernel/FactoryPool.h"
#include "Kernel/AssertionFactory.h"
#include "Kernel/AssertionNotImplemented.h"
#include "Kernel/Logger.h"
#include "Kernel/String.h"

#include "SDL_rwops.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    SDLFileGroupDirectory::SDLFileGroupDirectory()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    SDLFileGroupDirectory::~SDLFileGroupDirectory()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::initialize( const ConstString & _name, const FileGroupInterfacePtr & _category, const FilePath & _folderPath )
    {
		m_name = _name;
		m_category = _category;
        m_folderPath = _folderPath;

        m_factoryInputStream = new FactoryPool<SDLFileInputStream, 8>();
        m_factoryOutputStream = new FactoryPool<SDLFileOutputStream, 4>();

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void SDLFileGroupDirectory::finalize()
    {
        m_category = nullptr;

        MENGINE_ASSERTION_FACTORY_EMPTY( m_factoryInputStream );
        MENGINE_ASSERTION_FACTORY_EMPTY( m_factoryOutputStream );

        m_factoryInputStream = nullptr;
        m_factoryOutputStream = nullptr;
    }
    //////////////////////////////////////////////////////////////////////////
    const ConstString & SDLFileGroupDirectory::getName() const
    {
        return m_name;
    }
    //////////////////////////////////////////////////////////////////////////
    const FileGroupInterfacePtr & SDLFileGroupDirectory::getCategory() const
    {
        return m_category;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::isPacked() const
    {
        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    const FilePath & SDLFileGroupDirectory::getRelationPath() const
    {
        return m_relationPath;
    }
    //////////////////////////////////////////////////////////////////////////
    const FilePath & SDLFileGroupDirectory::getFolderPath() const
    {
        return m_folderPath;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::existFile( const FilePath & _fileName ) const
    {
        // SDL doesn't have this, so we're emulating ... ugly way :(

        Char filePath[MENGINE_MAX_PATH];
        if( Helper::concatenateFilePath( m_relationPath, m_folderPath, _fileName, filePath, MENGINE_MAX_PATH ) == false )
        {
            LOGGER_ERROR("invlalid concatenate filePath '%s':'%s'"
                , m_folderPath.c_str()
                , _fileName.c_str()
                );

            return false;
        }

        SDL_RWops* rwops = SDL_RWFromFile( filePath, "rb" );

        if( rwops != nullptr )
        {           
            SDL_RWclose( rwops );
            
            return true;
        }

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::existDirectory( const FilePath & _folderName ) const
    {
        const FilePath & relationPath = this->getRelationPath();
        const FilePath & folderPath = this->getFolderPath();

        PathString accountString;
        accountString.append( relationPath );
        accountString.append( folderPath );
        accountString.append( _folderName );
        accountString.append( '/' );

        if( PLATFORM_SERVICE()
            ->existDirectory( accountString.c_str() ) == false )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::createDirectory( const FilePath & _folderName ) const
    {
        const FilePath & relationPath = this->getRelationPath();
        const FilePath & folderPath = this->getFolderPath();

        PathString accountString;
        accountString.append( relationPath );
        accountString.append( folderPath );
        accountString.append( _folderName );

        if( PLATFORM_SERVICE()
            ->existDirectory( accountString.c_str() ) == true )
        {
            return true;
        }

        if( PLATFORM_SERVICE()
            ->createDirectory( accountString.c_str() ) == false )
        {
            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::findFiles( const FilePath & _folderPath, const Char * _mask, const LambdaFiles & _lambda ) const
    {
        MENGINE_UNUSED( _folderPath );
        MENGINE_UNUSED( _mask );
        MENGINE_UNUSED( _lambda );

        MENGINE_ASSERTION_NOT_IMPLEMENTED();

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    InputStreamInterfacePtr SDLFileGroupDirectory::createInputFile( const FilePath & _fileName, bool _streaming, const Char * _doc )
    {
        (void)_fileName;
        (void)_streaming;

        SDLFileInputStreamPtr inputStream = m_factoryInputStream->createObject( _doc );

        return inputStream;
    }
    //////////////////////////////////////////////////////////////////////////
    bool SDLFileGroupDirectory::openInputFile( const FilePath & _filePath, const InputStreamInterfacePtr & _stream, size_t _offset, size_t _size, bool _streaming )
    {
        (void)_streaming;

        if( _stream == nullptr )
        {
            LOGGER_ERROR("failed _stream == NULL"
                );

            return false;
        }

        FileInputStreamInterface * file = stdex::intrusive_get<FileInputStreamInterface *>(_stream);

        if( file->open( m_relationPath, m_folderPath, _filePath, _offset, _size, _streaming ) == false )
        {
            LOGGER_ERROR("failed open file '%s':'%s'"
                , m_folderPath.c_str()
                , _filePath.c_str()
                );

            return false;
        }

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    OutputStreamInterfacePtr SDLFileGroupDirectory::createOutputFile( const Char * _doc )
    {
		SDLFileOutputStreamPtr outputStream = m_factoryOutputStream->createObject( _doc );

        return outputStream;
    }
    //////////////////////////////////////////////////////////////////////////	
    bool SDLFileGroupDirectory::openOutputFile( const FilePath & _filePath, const OutputStreamInterfacePtr & _stream )
    {
        if( _stream == nullptr )
        {
            LOGGER_ERROR("failed _stream == NULL"
                );

            return false;
        }

        FileOutputStreamInterface * file = stdex::intrusive_get<FileOutputStreamInterface *>(_stream);

        if( file->open( m_relationPath, m_folderPath, _filePath ) == false )
        {
            LOGGER_ERROR("failed open file '%s':'%s'"
                , m_folderPath.c_str()
                , _filePath.c_str()
                );

            return false;
        }
                
        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void SDLFileGroupDirectory::setRelationPath( const FilePath & _relationPath )
    {
        m_relationPath = _relationPath;
    }
    //////////////////////////////////////////////////////////////////////////
}   // namespace Mengine
