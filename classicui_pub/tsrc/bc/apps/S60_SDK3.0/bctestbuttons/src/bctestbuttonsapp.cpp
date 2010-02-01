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
* Description:         avkon buttons test app
*
*/









// INCLUDE FILES
#include <eikstart.h>

#include "bctestbuttonsapp.h"
#include "bctestbuttonsdocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestButtonsApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestButtonsApp::AppDllUid() const
    {
    return KUidBCTestButtons;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestButtonsApp::CreateDocumentL()
// Creates CBCTestButtonsDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestButtonsApp::CreateDocumentL()
    {
    return CBCTestButtonsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestButtonsApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestButtonsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }


