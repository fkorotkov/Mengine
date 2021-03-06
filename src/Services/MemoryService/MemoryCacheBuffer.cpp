#include "MemoryCacheBuffer.h"

#include "MemoryService.h"

#include "Interface/MemoryInterface.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    MemoryCacheBuffer::MemoryCacheBuffer()
        : m_memoryManager( nullptr )
        , m_bufferId( 0 )
        , m_data( nullptr )
        , m_size( 0 )
    {
    }
    //////////////////////////////////////////////////////////////////////////
    MemoryCacheBuffer::~MemoryCacheBuffer()
    {
        this->uncache_();
    }
    //////////////////////////////////////////////////////////////////////////
    void MemoryCacheBuffer::setMemoryManager( MemoryService * _memoryManager )
    {
        m_memoryManager = _memoryManager;
    }
    //////////////////////////////////////////////////////////////////////////
    void MemoryCacheBuffer::uncache_()
    {
        if( m_bufferId != 0 )
        {
            m_memoryManager->unlockBuffer( m_bufferId );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void MemoryCacheBuffer::setBuffer( const void * _ptr, size_t _size, const Char * _doc, const Char * _file, uint32_t _line )
    {
        void * buffer = this->newBuffer( _size, _doc, _file, _line );

        stdex::memorycopy( buffer, 0, _ptr, _size );
    }
    //////////////////////////////////////////////////////////////////////////
    Pointer MemoryCacheBuffer::newBuffer( size_t _size, const Char * _doc, const Char * _file, uint32_t _line )
    {
        this->uncache_();

        void * memory;
        uint32_t bufferId = m_memoryManager->lockBuffer( _size, &memory, _doc, _file, _line );

        if( bufferId == INVALID_CACHE_BUFFER_ID )
        {
            return nullptr;
        }

        m_bufferId = bufferId;

        m_data = memory;
        m_size = _size;

        return m_data;
    }
}
