#include "ServiceProvider.h"

#include "Interface/ServiceInterface.h"

#include <string.h>

//////////////////////////////////////////////////////////////////////////
SERVICE_PROVIDER_FACTORY( ServiceProvider, Mengine::ServiceProvider );
//////////////////////////////////////////////////////////////////////////
namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    ServiceProvider::ServiceProvider()
        : m_servicesCount( 0 )
        , m_dependenciesCount( 0 )
        , m_waitsCount( 0 )
    {
        for( uint32_t index = 0; index != MENGINE_SERVICE_PROVIDER_COUNT; ++index )
        {
            ServiceDesc & desc = m_services[index];

            desc.name[0] = '\0';
            desc.service = nullptr;
        }

        for( uint32_t index = 0; index != MENGINE_SERVICE_PROVIDER_DEPENDENCY_COUNT; ++index )
        {
            DependencyDesc & desc = m_dependencies[index];

            desc.name[0] = '\0';
            desc.dependency[0] = '\0';
        }

        for( uint32_t index = 0; index != MENGINE_SERVICE_PROVIDER_MAX_WAIT; ++index )
        {
            WaitDesc & desc = m_waits[index];

            desc.name[0] = '\0';
            desc.lambda = nullptr;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    ServiceProvider::~ServiceProvider()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    ServiceInterfacePtr ServiceProvider::generateService( TServiceProviderGenerator _generator )
    {
        if( _generator == nullptr )
        {
            return nullptr;
        }

        ServiceInterfacePtr service;
        if( (*_generator)(&service) == false )
        {
            return nullptr;
        }

        if( service->initializeService() == false )
        {
            return nullptr;
        }

        return service;
    }
    //////////////////////////////////////////////////////////////////////////
    bool ServiceProvider::initializeService( TServiceProviderGenerator _generator, const Char * _doc, const Char * _file, uint32_t _line )
    {
        ServiceInterfacePtr service = this->generateService( _generator );

        if( service == nullptr )
        {
            MENGINE_THROW_EXCEPTION_FL( _file, _line )("invalid generate service doc '%s'"
                , _doc
                );

            return false;
        }

        const Char * name = service->getServiceID();

        if( strlen( name ) + 1 > MENGINE_SERVICE_PROVIDER_NAME_SIZE )
        {
            MENGINE_THROW_EXCEPTION_FL( _file, _line )("invalid service name '%s' max size '%d' > '%d'"
                , name
                , strlen( name + 1 )
                , MENGINE_SERVICE_PROVIDER_NAME_SIZE
                );

            return false;
        }

        for( uint32_t index = 0; index != MENGINE_SERVICE_PROVIDER_COUNT; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( desc.service == nullptr )
            {
                strcpy( desc.name, name );
            }
            else if( strcmp( desc.name, name ) != 0 )
            {
                continue;
            }
            else
            {
                desc.service->finalizeService();
                desc.service = nullptr;
            }

            desc.service = service;

            ++m_servicesCount;

            this->checkWaits_( name );

            return true;
        }

        MENGINE_THROW_EXCEPTION_FL( _file, _line )("invalid allocate service name '%s' max count '%d'"
            , name
            , MENGINE_SERVICE_PROVIDER_COUNT
            );

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    bool ServiceProvider::finalizeService( const Char * _name )
    {
        for( uint32_t index = 0; index != m_dependenciesCount; ++index )
        {
            const DependencyDesc & desc = m_dependencies[index];

            if( strcmp( desc.dependency, _name ) != 0 )
            {
                continue;
            }

            this->finalizeService( desc.name );
        }

        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( strcmp( desc.name, _name ) != 0 )
            {
                continue;
            }

            if( desc.service == nullptr )
            {
                break;
            }

            desc.service->finalizeService();

            return true;
        }

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    bool ServiceProvider::destroyService( const Char * _name )
    {
        for( uint32_t index = 0; index != m_dependenciesCount; ++index )
        {
            const DependencyDesc & desc = m_dependencies[index];

            if( strcmp( desc.dependency, _name ) != 0 )
            {
                continue;
            }

            this->destroyService( desc.name );
        }

        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( strcmp( desc.name, _name ) != 0 )
            {
                continue;
            }

            if( desc.service == nullptr )
            {
                break;
            }

            this->removeDependency_( _name );

            desc.service->finalizeService();
            desc.service = nullptr;

            --m_servicesCount;

            return true;
        }

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::dependencyService( const Char * _name, const Char * _dependency )
    {
        DependencyDesc & desc = m_dependencies[m_dependenciesCount++];

        strcpy( desc.name, _name );
        strcpy( desc.dependency, _dependency );
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::waitService( const Char * _name, const LambdaWaitService & _lambda )
    {
        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( strcmp( desc.name, _name ) != 0 )
            {
                continue;
            }

            if( desc.service == nullptr )
            {
                break;
            }

            _lambda();

            return;
        }

        WaitDesc & desc = m_waits[m_waitsCount++];

        strcpy( desc.name, _name );
        desc.lambda = _lambda;
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::removeDependency_( const Char * _name )
    {
        for( uint32_t index = 0; index != m_dependenciesCount; )
        {
            DependencyDesc & desc = m_dependencies[index];

            if( desc.name[0] != '\0' )
            {
                ++index;

                continue;
            }

            if( strcmp( desc.name, _name ) != 0 )
            {
                ++index;

                continue;
            }

            DependencyDesc & last_desc = m_dependencies[--m_dependenciesCount];

            strcpy( desc.name, last_desc.name );
            strcpy( desc.dependency, last_desc.dependency );
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::checkWaits_( const Char * _name )
    {
        for( uint32_t index = 0; index != m_waitsCount; )
        {
            WaitDesc & desc = m_waits[index];

            if( strcmp( desc.name, _name ) != 0 )
            {
                ++index;

                continue;
            }

            desc.lambda();

            WaitDesc & last_desc = m_waits[--m_waitsCount];

            strcpy( desc.name, last_desc.name );
            desc.lambda = last_desc.lambda;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    bool ServiceProvider::existService( const Char * _name ) const
    {
        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            const ServiceDesc & desc = m_services[index];

            if( desc.service == nullptr )
            {
                continue;
            }

            if( strcmp( desc.name, _name ) != 0 )
            {
                continue;
            }

            return true;
        }

        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    const ServiceInterfacePtr & ServiceProvider::getService( const Char * _name ) const
    {
        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            const ServiceDesc & desc = m_services[index];

            if( strcmp( desc.name, _name ) != 0 )
            {
                continue;
            }

            if( desc.service == nullptr )
            {
                break;
            }

            return desc.service;
        }

        return ServiceInterfacePtr::none();
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::destroy()
    {
        for( uint32_t index = 0; index != m_waitsCount; ++index )
        {
            WaitDesc & desc = m_waits[index];

            desc.lambda = nullptr;
        }

        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( desc.service == nullptr )
            {
                continue;
            }

            desc.service->finalizeService();
        }

        for( uint32_t index = m_servicesCount; index != 0; --index )
        {
            ServiceDesc & desc = m_services[index - 1];

            if( desc.service == nullptr )
            {
                continue;
            }

            desc.service = nullptr;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    void ServiceProvider::stopServices()
    {
        for( uint32_t index = 0; index != m_servicesCount; ++index )
        {
            ServiceDesc & desc = m_services[index];

            if( desc.service == nullptr )
            {
                continue;
            }

            desc.service->stopService();
        }
    }
}