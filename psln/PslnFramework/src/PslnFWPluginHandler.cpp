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
* Description:  Base class for plugins containing other plugins.
*
*/


// INCLUDE FILES
#include "pslnfwpluginhandler.h"
#include "PslnDebug.h"

const TInt KPslnFWGeneralThemeViewLocation = 0;
const TInt KPslnFWWallpaperViewLocation = 3;
const TInt KPslnFWScreensaverViewLocation = 4;

// ========================= MEMBER FUNCTIONS ================================

// ---------------------------------------------------------------------------
// CPslnFWPluginHandler::NewL()
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWPluginHandler* CPslnFWPluginHandler::NewL(
    CAknViewAppUi* aAppUi, CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray )
    {
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::NewL");
    CPslnFWPluginHandler* self =
        new ( ELeave) CPslnFWPluginHandler( aAppUi, aPluginArray );
    return self;
    }

// ---------------------------------------------------------------------------
// CPslnFWPluginHandler::CPslnFWPluginHandler()
// ---------------------------------------------------------------------------
//
CPslnFWPluginHandler::CPslnFWPluginHandler(
    CAknViewAppUi* aAppUi, CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray )
    : iAppUi( aAppUi ), iPluginArray( aPluginArray )
    {
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWPluginHandler::~CPslnFWPluginHandler()
    {
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::destructor");
    iImplInfoArray.ResetAndDestroy();
    // iPluginArray is not owned, and thus not deleted.
    }

// ---------------------------------------------------------------------------
// Loads all found plugins.
// ---------------------------------------------------------------------------
//
EXPORT_C void CPslnFWPluginHandler::LoadPluginsL(
    CArrayPtrFlat<CPslnFWPluginInterface>* aPluginArray )
    {
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::LoadPluginsL BEGIN");
    if ( iPluginArray )
        {
        iPluginArray = aPluginArray;
        }
    else
        {
        User::Leave( KErrArgument );
        }

    REComSession::ListImplementationsL(
        KPslnFWPluginInterfaceUid,
        iImplInfoArray );

    // Reset iterator:
    iImplInfoArrayIterator = 0;

    LoadNextPlugin();
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::LoadPluginsL END");
    }

// ---------------------------------------------------------------------------
// Loads one specific plugin.
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWPluginInterface* CPslnFWPluginHandler::LoadPluginL( const TUid aPluginId )
    {
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::LoadPluginL BEGIN");
    REComSession::ListImplementationsL(
        KPslnFWPluginInterfaceUid,
        iImplInfoArray );

    // Reset iterator:
    iImplInfoArrayIterator = 0;

    // Iterate through iImplInfoArray.
    for( ; iImplInfoArrayIterator < iImplInfoArray.Count();  )
        {
        CImplementationInformation* info =
            iImplInfoArray[ iImplInfoArrayIterator ];
        TUid implUid = info->ImplementationUid();

        if ( implUid.iUid == aPluginId.iUid )
            {
            // Create a plugin.
            CPslnFWPluginInterface* plugin = CPslnFWPluginInterface::NewL(
                aPluginId,
                iAppUi );
            // Ownership transferred.
            PSLN_TRACE_DEBUG("CPslnFWPluginHandler::LoadPluginL plugin found");
            return plugin;
            }

        iImplInfoArrayIterator++;
        }
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::LoadPluginL END");
    return NULL;
    }

// ---------------------------------------------------------------------------
// Constructor without array.
// ---------------------------------------------------------------------------
//
EXPORT_C CPslnFWPluginHandler* CPslnFWPluginHandler::NewL( CAknViewAppUi* aAppUi )
    {
    PSLN_TRACE_DEBUG("CPslnFWPluginHandler::NewL 2");
    CPslnFWPluginHandler* self =
        new ( ELeave) CPslnFWPluginHandler( aAppUi, NULL );
    return self;
    }

// ----------------------------------------------------------------------------
// Iterate through iImplInfoArray. Load the plugin if it is eligible for
// loading. Loaded plugin is added to iPluginArray.
// ----------------------------------------------------------------------------
//
void CPslnFWPluginHandler::LoadNextPlugin()
    {
    // Iterate through iImplInfoArray.
    for( ; iImplInfoArrayIterator < iImplInfoArray.Count();  )
        {
        CImplementationInformation* info =
            iImplInfoArray[ iImplInfoArrayIterator ];
        TUid implUid = info->ImplementationUid();

        iImplInfoArrayIterator++;

        // Load plugin - if it fails, just go to next one.
        TRAP_IGNORE( AppendPluginL( implUid ) );
        }
    }

// ----------------------------------------------------------------------------
// Inserts plugin to plugin-array.
// ----------------------------------------------------------------------------
//
void CPslnFWPluginHandler::AppendPluginL( const TUid& aImplUid )
    {
    // Create a plugin.
    CPslnFWPluginInterface* plugin = CPslnFWPluginInterface::NewL(
        aImplUid,
        iAppUi );
    CleanupStack::PushL ( plugin );

    CPslnFWPluginInterface::TPslnFWLocationType locType =
        CPslnFWPluginInterface::EPslnFWNotSpecified;
    TInt location = KErrNotFound;
    plugin->GetLocationTypeAndIndex( locType, location );


    // If plugin claims invalid location, OR location is not specified,
    // append to the end.
    if ( IsInvalidLocation( location ) ||
        locType == CPslnFWPluginInterface::EPslnFWNotSpecified )
        {
        if ( iPluginArray )
            {
            iPluginArray->AppendL( plugin );
            }
        }
    else
        {
        CPslnFWPluginInterface* arrayPlugin = NULL;

        CPslnFWPluginInterface::TPslnFWLocationType pluginLocType =
            CPslnFWPluginInterface::EPslnFWNotSpecified;
        TInt pluginLoc = KErrNotFound;
        TInt count = iPluginArray->Count();

        // Exception - first item, is always appended
        if ( count == 0 )
            {
            iPluginArray->AppendL( plugin );
            }
        else
            {
            // Loop through the plugin array, trying to find best location for the plugin.
            TBool breakLoop = EFalse;
            for ( TInt i = 0; i < count; i++ )
                {
                arrayPlugin = iPluginArray->At( i );
                arrayPlugin->GetLocationTypeAndIndex( pluginLocType, pluginLoc );
                if ( pluginLocType == CPslnFWPluginInterface::EPslnFWNotSpecified )
                    {
                    // There are no more valid locations, insert here
                    iPluginArray->InsertL( i, plugin );
                    breakLoop = ETrue;
                    }
                if ( pluginLoc == location )
                    {
                    // Mismatch - plugin location already claimed.
                    // Append plugin to last position in the array.
                    iPluginArray->AppendL( plugin );
                    breakLoop = ETrue;
                    }
                else if ( pluginLoc < location )
                    {
                    // Do nothing go to next inserted plugin
                    }
                else
                    {
                    // This location is best for the new plugin.
                    iPluginArray->InsertL( i, plugin );
                    breakLoop = ETrue;
                    }
                // If plugin has been inserted, or appended, break the loop.
                if ( breakLoop )
                    {
                    i = count;
                    }
                }
            }
        }

    // Transfer ownership to array.
    CleanupStack::Pop ( plugin );
    }

// ----------------------------------------------------------------------------
// Checks if the plugin tries to claim invalid location.
// ----------------------------------------------------------------------------
//
TBool CPslnFWPluginHandler::IsInvalidLocation( const TInt& aLoc ) const
    {
    TBool retVal = ETrue;
    if ( aLoc == KPslnFWGeneralThemeViewLocation ||
         aLoc == KPslnFWWallpaperViewLocation ||
         aLoc == KPslnFWScreensaverViewLocation )
        {
        retVal = EFalse;
        }
    return retVal;
    }

// End of File
