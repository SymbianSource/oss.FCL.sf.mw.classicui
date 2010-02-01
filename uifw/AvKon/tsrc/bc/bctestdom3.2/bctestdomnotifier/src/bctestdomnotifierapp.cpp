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

#include "bctestdomnotifierapp.h"
#include "bctestdomnotifierdocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCDomainTestNotifierApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------

TUid CBCDomainTestNotifierApp::AppDllUid() const
    {
    return KUidBCDomainTestNotifier;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCDomainTestNotifierApp::CreateDocumentL()
// Creates CBCDomainTestNotifierDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCDomainTestNotifierApp::CreateDocumentL()
    {
    return CBCDomainTestNotifierDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCDomainTestNotifierApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCDomainTestNotifierApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
