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
* Description:         Avkon PreviewPopup test app
*
*/









// INCLUDE FILES
#include "BCTestPreviewPopupApp.h"
#include "BCTestPreviewPopupDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestPreviewPopupApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestPreviewPopupApp::AppDllUid() const
    {
    return KUidBCTestPreviewPopup;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestPreviewPopupApp::CreateDocumentL()
// Creates CBCTestPreviewPopupDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestPreviewPopupApp::CreateDocumentL()
    {
    return CBCTestPreviewPopupDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestPreviewPopupApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestPreviewPopupApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
