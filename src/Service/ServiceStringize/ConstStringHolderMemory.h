#pragma once

#include "Config/String.h"

#include "Core/ConstStringHolder.h"

namespace Mengine
{
    class ConstStringHolderMemory
        : public ConstStringHolder
    {
	public:
		ConstStringHolderMemory();
        ~ConstStringHolderMemory() override;

	public:
		void setValue( const Char * _value, ConstStringHolder::size_type _size, hash_type _hash );
        
    protected:			
		Char * m_buff;
    };
}