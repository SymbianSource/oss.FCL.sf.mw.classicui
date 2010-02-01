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
* Description:         Application
*
*/









#include <eikstart.h>

#include "BCTestUtilitiesApp.h"
#include "BCTestUtilitiesDocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestUtilitiesApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestUtilitiesApp::AppDllUid() const
    {
    return KUidBCTestUtilities;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestUtilitiesApp::CreateDocumentL()
// Creates CBCTestUtilitiesDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestUtilitiesApp::CreateDocumentL()
    {
    return CBCTestUtilitiesDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestUtilitiesApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestUtilitiesApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

