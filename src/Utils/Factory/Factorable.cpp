#	include "Factorable.h"
#	include "Factory.h"

namespace Menge
{
    //////////////////////////////////////////////////////////////////////////
    Factorable::Factorable()
	    : m_factory(nullptr)
#   ifdef MENGINE_FACTORABLE_DEBUG
        , m_destroy(false)
#   endif
    {
    }
    //////////////////////////////////////////////////////////////////////////
    Factorable::~Factorable()
    {
#   ifdef MENGINE_FACTORABLE_DEBUG
        if( m_destroy == false && m_factory != nullptr )
        {            
            STDEX_THROW_EXCEPTION("Factorable deleter but not destroy!!");
        }
#   endif
    }
    //////////////////////////////////////////////////////////////////////////
    void Factorable::setFactory( Factory * _factory )
    {
	    m_factory = _factory;
    }
    //////////////////////////////////////////////////////////////////////////
    void Factorable::destroy()
    {
#   ifdef MENGINE_FACTORABLE_DEBUG
        if( m_destroy == true )
        {
            STDEX_THROW_EXCEPTION("m_destroy == true");
        }
#   endif

#   ifdef MENGINE_FACTORABLE_DEBUG
		m_destroy = true;
#   endif

        this->_destroy();

#   ifdef MENGINE_FACTORABLE_DEBUG
		this->_checkDestroy();
#   endif

		m_factory->destroyObject( this );
    }
#   ifdef MENGINE_FACTORABLE_DEBUG
    //////////////////////////////////////////////////////////////////////////
	bool Factorable::isDestroyed() const
	{
		return m_destroy;
	}
	//////////////////////////////////////////////////////////////////////////
    void Factorable::_checkDestroy()
    {
        //Empty
    }
#   endif
    //////////////////////////////////////////////////////////////////////////
    void Factorable::_destroy()
    {
    }
}
