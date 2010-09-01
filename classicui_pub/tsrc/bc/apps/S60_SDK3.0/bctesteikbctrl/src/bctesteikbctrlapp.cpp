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
* Description:         Avkon eikbctrl test app
*
*/









#include <eikstart.h>

#include "BCTesteikbctrlApp.h"
#include "BCTesteikbctrlDocument.h"

 
// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTesteikbctrlApp::AppDllUid()
// Returns application UID. 
// ----------------------------------------------------------------------------
//
TUid CBCTesteikbctrlApp::AppDllUid() const
    { 
    return KUidBCTesteikbctrl;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTesteikbctrlApp::CreateDocumentL()
// Creates CBCTesteikbctrlDocument object.
// ----------------------------------------------------------------------------

CApaDocument* CBCTesteikbctrlApp::CreateDocumentL()
    {
    return CBCTesteikbctrlDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTesteikbctrlApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTesteikbctrlApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
