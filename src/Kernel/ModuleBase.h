#pragma once

#include "Interface/ModuleInterface.h"

#include "Kernel/Factorable.h"

namespace Mengine
{
    class ModuleBase
        : public ModuleInterface
        , public Factorable
    {
    public:
        ModuleBase();
        ~ModuleBase() override;

    public:
        void setName( const ConstString & _name ) override;
        const ConstString & getName() const override;

    public:
        bool initializeModule() override;
        void finalizeModule() override;

    public:
        bool isAvailableModule() const override;

    protected:
        virtual bool _initializeModule();
        virtual void _finalizeModule();

    protected:
        virtual bool _availableModule() const;

    public:
        void update( bool _focus ) override;

    protected:
        virtual void _update( bool _focus );

    public:
        void tick( const UpdateContext * _context ) override;
        void render( const RenderContext * _state ) override;

    protected:
        virtual void _tick( const UpdateContext * _context );
        virtual void _render( const RenderContext * _state );

    public:
        void message( const ConstString & _messageName, const MapWParams & _params ) override;
        void messageAll( const ConstString & _messageName, const MapWParams & _params ) override;

    protected:
        virtual void _message( const ConstString & _messageName, const MapWParams & _params );
        virtual void _messageAll( const ConstString & _messageName, const MapWParams & _params );

    protected:
        ConstString m_name;

        bool m_available;
    };
}