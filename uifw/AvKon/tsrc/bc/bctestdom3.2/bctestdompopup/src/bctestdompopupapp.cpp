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
* Description:  app
*
*/


#include <eikstart.h>

#include "bctestdompopupapp.h"
#include "bctestdompopupudocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCDomainTestPopupApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCDomainTestPopupApp::AppDllUid() const
    {
    return KUidBCTestDomPopup;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCDomainTestPopupApp::CreateDocumentL()
// Creates CBCDomainTestPopupDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCDomainTestPopupApp::CreateDocumentL()
    {
    return CBCDomainTestPopupDocument::NewL( *this );
    } 

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCDomainTestPopupApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCDomainTestPopupApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
