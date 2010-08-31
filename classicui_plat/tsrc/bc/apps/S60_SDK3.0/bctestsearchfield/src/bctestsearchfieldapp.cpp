/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implement BC test searchfield application
*
*/









#include <eikstart.h>

#include "bctestsearchfieldapp.h"
#include "bctestsearchfielddocument.h"


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestSearchFieldApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestSearchFieldApp::AppDllUid() const
    {
    return KUidBCTestSearchField;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestSearchFieldApp::CreateDocumentL()
// Creates CBCTestSearchFieldDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestSearchFieldApp::CreateDocumentL()
    {
    return CBCTestSearchFieldDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestSearchFieldApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestSearchFieldApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
