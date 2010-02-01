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
* Description : Implementation of CAknEnableAppsKeyAndGlobalNotes class.
*
*/
#include <AknCapServerClient.h>
#include <e32property.h>

#include "aknenableappskeyandglobalnotes.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::NewL
//
// ---------------------------------------------------------------------------
//
CAknEnableAppsKeyAndGlobalNotes* CAknEnableAppsKeyAndGlobalNotes::NewL()
	{
	CAknEnableAppsKeyAndGlobalNotes* self =
	    new ( ELeave ) CAknEnableAppsKeyAndGlobalNotes;
	return self;
	}


// ---------------------------------------------------------------------------
// Destructor
//
// ---------------------------------------------------------------------------
//
CAknEnableAppsKeyAndGlobalNotes::~CAknEnableAppsKeyAndGlobalNotes()
    {
    }


// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::Initialize
//
// ---------------------------------------------------------------------------
//
TInt CAknEnableAppsKeyAndGlobalNotes::Initialize(
    CSsmCustomCommandEnv* /*aCmdEnv*/ )
    {
    return KErrNone;
    }


// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::Execute
//
// ---------------------------------------------------------------------------
//
void CAknEnableAppsKeyAndGlobalNotes::Execute(
    const TDesC8& /*aParams*/,
    TRequestStatus& aRequest )
    {
    aRequest = KRequestPending;

    RAknUiServer aknSrv;
    TInt errorCode = aknSrv.Connect();
    if ( errorCode == KErrNone )
        {
        errorCode = aknSrv.EnableTaskList( ETrue );
        aknSrv.Close();
        }

    TRequestStatus* request = &aRequest;
    User::RequestComplete( request, errorCode );
    }


// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::ExecuteCancel
//
// ---------------------------------------------------------------------------
//
void CAknEnableAppsKeyAndGlobalNotes::ExecuteCancel()
    {
    // Nothing to do.
    }


// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::Release
//
// ---------------------------------------------------------------------------
//
void CAknEnableAppsKeyAndGlobalNotes::Release()
    {
	delete this;
    }


// ---------------------------------------------------------------------------
// CAknEnableAppsKeyAndGlobalNotes::Close
//
// ---------------------------------------------------------------------------
//
void CAknEnableAppsKeyAndGlobalNotes::Close()
    {
    // Nothing to do.
    }


// ---------------------------------------------------------------------------
// First phase constructor
//
// ---------------------------------------------------------------------------
//
CAknEnableAppsKeyAndGlobalNotes::CAknEnableAppsKeyAndGlobalNotes()
    {
    }

