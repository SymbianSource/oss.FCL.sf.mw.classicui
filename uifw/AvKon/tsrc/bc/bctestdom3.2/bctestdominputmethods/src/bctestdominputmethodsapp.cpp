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
* Description:  DomInputMethods test app
*
*/


// INCLUDE FILES
#include <eikstart.h>

#include "bctestdominputmethodsapp.h"
#include "bctestdominputmethodsdocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestDomInputMethodsApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestDomInputMethodsApp::AppDllUid() const
    {
    return KUidBCTESTDomInputMethods;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestDomInputMethodsApp::CreateDocumentL()
// Creates CBCTestDomInputMethodsDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestDomInputMethodsApp::CreateDocumentL()
    {
    return CBCTestDomInputMethodsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestDomInputMethodsApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestDomInputMethodsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
