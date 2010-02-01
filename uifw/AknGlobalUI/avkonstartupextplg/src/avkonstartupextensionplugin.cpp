/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of CAvkonStartupExtensionPlugIn class.
*
*/


#include <e32property.h>
#include <centralrepository.h>
#include <akneiksrvc.h>
#include <palette.h>
#include <UikonInternalPSKeys.h>
#include <AknSkinsInternalCRKeys.h>

#include "avkonstartupextensionplugin.h"

// Parameters
_LIT( KPalette, "set palette" );
_LIT( KEnableApps, "enable apps key" );
_LIT( KEnableNotes, "enable global notes" );
_LIT( KShutdown, "shutdown apps" );

// 7 seconds time for applications to close themself
const TInt KTimeToKillAppsNicely = 7000000;

// UID of this DLL for the shutdown operation
const TUid KAknStartupExtPluginUID = { 0x1020506D };

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructor
//
// ---------------------------------------------------------------------------
//
CAvkonStartupExtensionPlugIn* CAvkonStartupExtensionPlugIn::NewL(
    TAny* aConstructionParameters )
    {
    CAvkonStartupExtensionPlugIn* self =
        new( ELeave ) CAvkonStartupExtensionPlugIn( aConstructionParameters );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Destructor
//
// ---------------------------------------------------------------------------
//
CAvkonStartupExtensionPlugIn::~CAvkonStartupExtensionPlugIn()
    {
    iAknUiServer.Close();
    }


// ---------------------------------------------------------------------------
// First phase constructor
//
// ---------------------------------------------------------------------------
//
CAvkonStartupExtensionPlugIn::CAvkonStartupExtensionPlugIn(
    TAny* aConstructionParameters )
  : CSystemStartupExtension( aConstructionParameters ), iActive(EFalse)
    {
    }


// ---------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::ConstructL
//
// ---------------------------------------------------------------------------
//
void CAvkonStartupExtensionPlugIn::ConstructL()
    {
    }


// ---------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::ExecuteL
//
// ---------------------------------------------------------------------------
//
void CAvkonStartupExtensionPlugIn::ExecuteL(
    TRequestStatus& aStatus,
    const TDesC& aParams )
    {
    aStatus = KRequestPending;
    TRequestStatus* status = &aStatus;

    TInt errorCode = KErrNone;
    if ( aParams == KPalette )
        {
        User::RequestComplete( status, SetColorPalette() );
        }
    else if ( aParams == KEnableApps )
        {
        User::RequestComplete( status, EnableAppsKey() );
        }
    else if ( aParams == KEnableNotes )
        {
        User::RequestComplete( status, EnableGlobalNotes() );
        }
    else if ( aParams == KShutdown )
        {
        if ( !iAknUiServer.Handle() )
            {
            errorCode = iAknUiServer.Connect();
            }

        if ( errorCode == KErrNone )
            {
            iAknUiServer.ShutdownApps(
                KAknStartupExtPluginUID, KTimeToKillAppsNicely, aStatus );
                
            iActive = ETrue;
            }
        else
            {
            User::RequestComplete( status, errorCode );
            }
        }
    else
        {
        User::RequestComplete( status, KErrNotSupported );
        }
    }


// ---------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::Cancel
//
// ---------------------------------------------------------------------------
//
void CAvkonStartupExtensionPlugIn::Cancel()
    {
    if ( iActive )
        {
        iAknUiServer.CancelShutdownApps();
        iActive = EFalse;
        }
    }


// -----------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::SetColorPalette
//
// -----------------------------------------------------------------------------
//
TInt CAvkonStartupExtensionPlugIn::SetColorPalette()
    {
    CRepository* repository = NULL;
    TRAPD( errorCode, repository = CRepository::NewL( KCRUidPersonalisation ) );

    if ( errorCode == KErrNone )
        {
        TInt scheme( 0 );
        errorCode = repository->Get( KPslnColorPalette, scheme );

        if ( errorCode == KErrNone )
            {
            DynamicPalette::SetColor256Util((DynamicPalette::TIndex)scheme);
            }
        }

    delete repository;

    return errorCode;
    }


// ---------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::EnableAppsKey
//
// ---------------------------------------------------------------------------
//
TInt CAvkonStartupExtensionPlugIn::EnableAppsKey()
    {
    RAknUiServer aknSrv;
    TInt errorCode = aknSrv.Connect();
    if ( errorCode == KErrNone )
        {
        errorCode = aknSrv.EnableTaskList( ETrue );
        aknSrv.Close();
        }

    return errorCode;
    }


// ---------------------------------------------------------------------------
// CAvkonStartupExtensionPlugIn::EnableGlobalNotes
//
// ---------------------------------------------------------------------------
//
TInt CAvkonStartupExtensionPlugIn::EnableGlobalNotes()
    {
    return RProperty::Set( KPSUidUikon, KUikGlobalNotesAllowed, 1 );
    }
