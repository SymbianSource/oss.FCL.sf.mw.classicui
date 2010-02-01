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
* Description:         Avkon Notifier test app
*
*/









// INCLUDE FILES
#include "BCTestNotifierApp.h"
#include "BCTestNotifierDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestNotifierApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestNotifierApp::AppDllUid() const
    {
    return KUidBCTestNotifier;
    
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestNotifierApp::CreateDocumentL()
// Creates CBCTestTemplateDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestNotifierApp::CreateDocumentL()
    {
    return CBCTestNotifierDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestSettingPageApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestNotifierApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
