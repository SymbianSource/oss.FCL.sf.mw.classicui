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
* Description:  Indicator ECOM Plugin interface implementation.
*
*/


// INCLUDES
#include <gulicon.h>

#include "AknIndicatorPlugin.h"
#include "aknindicatorpopupcontent.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknIndicatorPlugin::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknIndicatorPlugin* CAknIndicatorPlugin::NewL(
    const TUid& aImplementationUid )
    {
    // Get the instantiation
    return reinterpret_cast<CAknIndicatorPlugin*>(
        REComSession::CreateImplementationL(
            aImplementationUid,
            _FOFF( CAknIndicatorPlugin, iDtor_ID_Key ) ) );
    }


// ----------------------------------------------------
// Destructor
// ----------------------------------------------------
//
EXPORT_C CAknIndicatorPlugin::~CAknIndicatorPlugin()
    {
    REComSession::DestroyedImplementation( iDtor_ID_Key );
    }


// ----------------------------------------------------
// CAknIndicatorPlugin::TextL
// ----------------------------------------------------
//
EXPORT_C HBufC* CAknIndicatorPlugin::TextL( const TInt /*aUid*/,
                                            TInt& aTextType )
    {
    aTextType = 0;
    return NULL;
    }


// ----------------------------------------------------
// CAknIndicatorPlugin::IconL
// ----------------------------------------------------
//
EXPORT_C const CGulIcon* CAknIndicatorPlugin::IconL( const TInt /*aUid*/ )
    {
    return NULL;
    }
    
    
// ----------------------------------------------------
// CAknIndicatorPlugin::UpdateL
// ----------------------------------------------------
//
EXPORT_C void CAknIndicatorPlugin::UpdateL( TInt aUid )
    {
    if ( iPluginObserver )
        {
        iPluginObserver->HandlePluginUpdateL( aUid );
        }
    }


// ----------------------------------------------------
// CAknIndicatorPlugin::SetPluginObserver
// ----------------------------------------------------
//    
void CAknIndicatorPlugin::SetPluginObserver(
    CAknIndicatorPopupContent* aPluginObserver )
    {
    iPluginObserver = aPluginObserver;
    }

//  End of File
