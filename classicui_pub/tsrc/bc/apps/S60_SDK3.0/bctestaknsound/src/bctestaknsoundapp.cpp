/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon Sound test app
*
*/









// INCLUDE FILES
#include "bctestaknsoundapp.h"
#include "bctestaknsounddocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestAknSoundApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestAknSoundApp::AppDllUid() const
    {
    return KUidBCTestAknSound;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestAknSoundApp::CreateDocumentL()
// Creates CBCTestAknSoundDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestAknSoundApp::CreateDocumentL()
    {
    return CBCTestAknSoundDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestAknSoundApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestAknSoundApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }


