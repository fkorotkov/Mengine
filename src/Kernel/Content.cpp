#include "Content.h"

namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
	Content::Content()
		: m_validNoExist( false )
    {
    }
    //////////////////////////////////////////////////////////////////////////
	Content::~Content()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    void Content::setFilePath( const FilePath & _filePath )
    {
        m_filePath = _filePath;
    }
    //////////////////////////////////////////////////////////////////////////
    const FilePath & Content::getFilePath() const
    {
        return m_filePath;
    }
    //////////////////////////////////////////////////////////////////////////
	void Content::setCodecType( const ConstString & _codecType )
	{
		m_codecType = _codecType;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConstString & Content::getCodecType() const
	{
		return m_codecType;
	}
	//////////////////////////////////////////////////////////////////////////
	void Content::setConverterType( const ConstString & _converterType )
	{
		m_converterType = _converterType;
	}
	//////////////////////////////////////////////////////////////////////////
	const ConstString & Content::getConverterType() const
	{
		return m_converterType;
	}
	//////////////////////////////////////////////////////////////////////////
	void Content::setValidNoExist( bool _validNoExist )
	{
		m_validNoExist = _validNoExist;
	}
	//////////////////////////////////////////////////////////////////////////
	bool Content::isValidNoExist() const
	{
		return m_validNoExist;
	}
}
