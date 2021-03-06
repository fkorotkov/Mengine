#include "PythonFramework.h"

#include "Interface/ScriptServiceInterface.h"
#include "Interface/StringizeServiceInterface.h"

#include "ConstsScriptEmbedding.h"
#include "EngineScriptEmbedding.h"
#include "EntityScriptEmbedding.h"
#include "GameScriptEmbedding.h"
#include "HelperScriptEmbedding.h"
#include "MathScriptEmbedding.h"
#include "NodeScriptEmbedding.h"
#include "SoundScriptEmbedding.h"

#include "Kernel/FactorableUnique.h"

#define ADD_SCRIPT_EMBEDDING(NAME)\
    if(SCRIPT_SERVICE()->addScriptEmbedding( STRINGIZE_STRING_LOCAL(#NAME), new FactorableUnique<NAME>())==false) return false

#define REMOVE_SCRIPT_EMBEDDING(NAME)\
    SCRIPT_SERVICE()->removeScriptEmbedding( STRINGIZE_STRING_LOCAL(#NAME))

//////////////////////////////////////////////////////////////////////////
SERVICE_FACTORY( Framework, Mengine::PythonFramework );
//////////////////////////////////////////////////////////////////////////
namespace Mengine
{
    //////////////////////////////////////////////////////////////////////////
    PythonFramework::PythonFramework()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    PythonFramework::~PythonFramework()
    {
    }
    //////////////////////////////////////////////////////////////////////////
    bool PythonFramework::_initializeService()
    {
        ADD_SCRIPT_EMBEDDING( ConstsScriptEmbedding );
        ADD_SCRIPT_EMBEDDING( MathScriptEmbedding );
        ADD_SCRIPT_EMBEDDING( HelperScriptEmbedding );
        ADD_SCRIPT_EMBEDDING( NodeScriptEmbedding );
        ADD_SCRIPT_EMBEDDING( EntityScriptEmbedding );        
        ADD_SCRIPT_EMBEDDING( SoundScriptEmbedding );
        ADD_SCRIPT_EMBEDDING( EngineScriptEmbedding );

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void PythonFramework::_finalizeService()
    {
        REMOVE_SCRIPT_EMBEDDING( ConstsScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( MathScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( HelperScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( NodeScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( EntityScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( SoundScriptEmbedding );
        REMOVE_SCRIPT_EMBEDDING( EngineScriptEmbedding );
    }
    //////////////////////////////////////////////////////////////////////////
    bool PythonFramework::onFrameworkInitialize()
    {
        ADD_SCRIPT_EMBEDDING( GameScriptEmbedding );

        return true;
    }
    //////////////////////////////////////////////////////////////////////////
    void PythonFramework::onFrameworkFinalize()
    {
        REMOVE_SCRIPT_EMBEDDING( GameScriptEmbedding );
    }
}
