#pragma once

#include "FactoryPrototypeGenerator.h"

#include "Kernel/ConstString.h"

#include "Kernel/FactoryPool.h"

#include "Kernel/Logger.h"

namespace Mengine
{
    template<class Type, uint32_t Count>
    class DefaultPrototypeGenerator
        : public FactoryPrototypeGenerator
    {
    protected:
        typedef IntrusivePtr<Type> TypePtr;

    protected:
        FactoryPtr _initializeFactory() override
        {
            FactoryPtr factory = new FactoryPool<Type, Count>();

            return factory;
        }

    protected:
        FactorablePointer generate( const Char * _doc ) override
        {
            const FactoryPtr & factory = this->getFactory();

            TypePtr object = factory->createObject( _doc );

            if( object == nullptr )
            {
                LOGGER_ERROR( "DefaultPrototypeGenerator::generate can't generate %s %s doc '%s'"
                    , this->getCategory().c_str()
                    , this->getPrototype().c_str()
					, _doc
                );

                return nullptr;
            }

            return object;
        }
    };
}