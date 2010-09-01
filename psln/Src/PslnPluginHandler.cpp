/*
* Copyright (c) 2005-2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Handles application specific theme plugins.
*
*/



// INCLUDE FILES
#include "PslnPluginHandler.h"
#include "PslnUi.h"
#include "PslnDebug.h"

// Framework
#include <pslnfwplugininterface.h>
#include <pslnfwpluginhandler.h>

// CONSTANTS
// Plugins granularity.
const TInt KPslnPluginGranularity = 4;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// C++ constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPslnPluginHandler::CPslnPluginHandler( CPslnUi* aPslnUi ) : iPslnUi( aPslnUi )
    {
    }

// -----------------------------------------------------------------------------
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CPslnPluginHandler::ConstructL()
    {
    // Load the plugin views.
    iPluginArray = 
        new CArrayPtrFlat<CPslnFWPluginInterface>( KPslnPluginGranularity );
    CPslnFWPluginHandler* pluginLoader = 
        CPslnFWPluginHandler::NewL( iPslnUi, iPluginArray );
    CleanupStack::PushL( pluginLoader );
    pluginLoader->LoadPluginsL( iPluginArray );
    CleanupStack::PopAndDestroy( pluginLoader );
    
    for ( TInt i = 0; i < iPluginArray->Count(); i ++ )
        {
        CPslnFWPluginInterface* plugin = iPluginArray->operator[]( i );
        iPslnUi->AddNewViewL( plugin );
        }
    }

// -----------------------------------------------------------------------------
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CPslnPluginHandler* CPslnPluginHandler::NewL( CPslnUi* aPslnUi )
    {
    CPslnPluginHandler* self = new( ELeave ) CPslnPluginHandler( aPslnUi );
    
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// Destructor
CPslnPluginHandler::~CPslnPluginHandler()
    {
    // Reset also deletes the plugins
    if ( iPluginArray )
        {
        iPluginArray->Reset();
        REComSession::FinalClose();
        delete iPluginArray;
        }
    }

// ---------------------------------------------------------------------------
// CPslnPluginHandler::GetPluginArray
// ---------------------------------------------------------------------------
//
CArrayPtrFlat<CPslnFWPluginInterface>* CPslnPluginHandler::GetPluginArray() const
    {
    return iPluginArray;
    }

// ---------------------------------------------------------------------------
// CPslnPluginHandler::GetPlugin
// 
// ---------------------------------------------------------------------------
//
CPslnFWPluginInterface* CPslnPluginHandler::GetPlugin( const TUid& aUid )
    {
    CPslnFWPluginInterface* pluginToFind = NULL;
    PSLN_TRACE_DEBUG1("CPslnPluginHandler::GetPlugin Plugin Uid=%d", aUid.iUid );
    if ( iPluginArray )
        {
        TInt pluginCount = iPluginArray->Count();
        PSLN_TRACE_DEBUG1("CPslnPluginHandler::GetPlugin Plugin count=%d", pluginCount );

        // Go through all the plugins and add the info to tab group.
        TInt i = 0;
        for ( ; i < pluginCount; i++ )
            {
            CPslnFWPluginInterface* plugin = iPluginArray->operator[]( i );
            if ( plugin )
                {
                PSLN_TRACE_DEBUG1("CPslnPluginHandler::GetPlugin Id=%d", plugin->Id().iUid );
                if ( plugin->Id().iUid == aUid.iUid )
                    {
                    PSLN_TRACE_DEBUG("CPslnPluginHandler::GetPlugin found");
                    pluginToFind = plugin;
                    break;
                    }
                }
            else
                {
                PSLN_TRACE_DEBUG("CPslnPluginHandler::GetPlugin Plugin fails");
                }
            }
        if ( !pluginToFind )
            {
            PSLN_TRACE_DEBUG("CPslnPluginHandler::GetPlugin not found");
            }
        }
    else
        {
        PSLN_TRACE_DEBUG("CPslnPluginHandler::GetPlugin No plugin array");
        }
    return pluginToFind;
    }
//  End of File  
