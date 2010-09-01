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
* Description:         Avkon volume test app
*
*/









// INCLUDE FILES
#include "BCTestVolumeApp.h"
#include "BCTestVolumeDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CBCTestVolumeApp::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CBCTestVolumeApp::AppDllUid() const
    {
    return KUidBCTestVolume;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CBCTestVolumeApp::CreateDocumentL()
// Creates CBCTestVolumeDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CBCTestVolumeApp::CreateDocumentL()
    {
    return CBCTestVolumeDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================
//
// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestVolumeApp.
// Returns: CApaDocument*: created application object
// ----------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestVolumeApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File
