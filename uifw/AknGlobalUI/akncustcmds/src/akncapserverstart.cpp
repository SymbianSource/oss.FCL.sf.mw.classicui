/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description : Implementation of CAknCapServerStart class.
*
*/
#include <AknCapServerClient.h>
#include <AknSkinsInternalCRKeys.h>
#include <centralrepository.h>
#include <palette.h>

#include "akncapserverstart.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// SetColorPalette
//
// ---------------------------------------------------------------------------
//
static void SetColorPaletteL()
    {
    CRepository* repository = CRepository::NewLC( KCRUidPersonalisation );
    TInt scheme( 0 );
    User::LeaveIfError( repository->Get( KPslnColorPalette, scheme ) );
    DynamicPalette::SetColor256Util((DynamicPalette::TIndex)scheme);
    CleanupStack::PopAndDestroy( repository );
    }


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknCapServerStart::NewL
//
// ---------------------------------------------------------------------------
//
CAknCapServerStart* CAknCapServerStart::NewL()
	{
	CAknCapServerStart* self = new ( ELeave ) CAknCapServerStart;
	return self;
	}


// ---------------------------------------------------------------------------
// Destructor
//
// ---------------------------------------------------------------------------
//
CAknCapServerStart::~CAknCapServerStart()
    {
    }


// ---------------------------------------------------------------------------
// CAknCapServerStart::Initialize
//
// ---------------------------------------------------------------------------
//
TInt CAknCapServerStart::Initialize( CSsmCustomCommandEnv* /*aCmdEnv*/ )
    {
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CAknCapServerStart::Execute
//
// ---------------------------------------------------------------------------
//
void CAknCapServerStart::Execute(
    const TDesC8& /*aParams*/,
    TRequestStatus& aRequest )
    {
    aRequest = KRequestPending;

    TRAP_IGNORE( SetColorPaletteL() );
    TRAPD( err, RAknUiServer::StartAknCapserverL() );
    RDebug::Print( _L( "RAknUiServer::StartAknCapserverL leave code %d" ), err );

    TRequestStatus* request = &aRequest;
    User::RequestComplete( request, err );
    }


// ---------------------------------------------------------------------------
// CAknCapServerStart::ExecuteCancel
//
// ---------------------------------------------------------------------------
//
void CAknCapServerStart::ExecuteCancel()
    {
    // Nothing to do.
    }


// ---------------------------------------------------------------------------
// CAknCapServerStart::Release
//
// ---------------------------------------------------------------------------
//
void CAknCapServerStart::Release()
    {
	delete this;
    }


// ---------------------------------------------------------------------------
// CAknCapServerStart::Close
//
// ---------------------------------------------------------------------------
//
void CAknCapServerStart::Close()
    {
    // Nothing to do.
    }


// ---------------------------------------------------------------------------
// First phase constructor
//
// ---------------------------------------------------------------------------
//
CAknCapServerStart::CAknCapServerStart()
    {
    }

