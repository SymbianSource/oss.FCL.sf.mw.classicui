/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implement m3g application class
*
*/


#include <eikstart.h>

#include "bctestdomm3gapp.h"
#include "bctestdomm3gdocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestDomM3gApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestDomM3gApp::AppDllUid() const
    {
    return KUidBCTestM3g;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestDomM3gApp::CreateDocumentL()
// Creates CBCTestDomM3gDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestDomM3gApp::CreateDocumentL()
    {
    return CBCTestDomM3gDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomM3gApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomM3gApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }
