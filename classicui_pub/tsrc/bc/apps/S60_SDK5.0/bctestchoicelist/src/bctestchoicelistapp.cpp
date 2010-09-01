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
* Description:         test app
*
*/









// INCLUDE FILES
#include "BCTestChoicelistapp.h"
#include "BCTestChoicelistdocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCPopupChoicelistApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCPopupChoicelistApp::AppDllUid() const
    {
    return KUidBCPopupChoicelist;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCPopupChoicelistApp::CreateDocumentL()
// Creates CBCPopupChoicelistDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCPopupChoicelistApp::CreateDocumentL()
    {
    return CBCPopupChoicelistDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCPopupChoicelistApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCPopupChoicelistApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
