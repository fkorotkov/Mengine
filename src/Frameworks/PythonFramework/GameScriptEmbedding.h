#pragma once

#include "Interface/ScriptEmbeddingInterface.h"

#include "Kernel/Factorable.h"

namespace Mengine
{
    class GameScriptEmbedding
        : public ScriptEmbeddingInterface
        , public Factorable
    {
    public:
        GameScriptEmbedding();
        ~GameScriptEmbedding() override;

    public:
        bool embedding() override;
        void ejecting() override;

    protected:
        FactorablePtr m_implement;
    };
}