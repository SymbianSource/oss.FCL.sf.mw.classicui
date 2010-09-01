/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test app
*
*/


// INCLUDE FILES
#include "bctestMultiDriverapp.h"
#include "bctestMultiDriverdocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CMultiDriverApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CMultiDriverApp::AppDllUid() const
    {
    return KUidMultiDriver;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CMultiDriverApp::CreateDocumentL()
// Creates CMultiDriverDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CMultiDriverApp::CreateDocumentL()
    {
    return CMultiDriverDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CMultiDriverApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CMultiDriverApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
