/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implementation of application class.
*
*/









#include <eikstart.h>

#include "bctestlauncherapp.h"
#include "bctestlauncherdocument.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CBCTestLauncherApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------------------------
//
TUid CBCTestLauncherApp::AppDllUid() const
    {
    return KUidBCTestLauncher;
    }

// ---------------------------------------------------------------------------
// CBCTestLauncherApp::CreateDocumentL()
// Creates CAknAtPbarDocument object
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestLauncherApp::CreateDocumentL()
    {
    return CBCTestLauncherDocument::NewL( *this );
    }

// ========================== OTHER EXPORTED FUNCTIONS =======================

// ---------------------------------------------------------------------------
// NewApplication() 
// Constructs CBCTestLauncherApp
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestLauncherApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

 

