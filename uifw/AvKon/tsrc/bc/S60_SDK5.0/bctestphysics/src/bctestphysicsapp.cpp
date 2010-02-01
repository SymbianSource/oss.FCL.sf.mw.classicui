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
* Description:  container
*
*/

#include <eikstart.h>

#include "bctestphysicsapp.h"
#include "bctestphysicsdocument.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// TUid CBCTestPhysicsApp::AppDllUid()
// Returns application UID.
// ---------------------------------------------------------------------------
//
TUid CBCTestPhysicsApp::AppDllUid() const
    {
    return KUidBCTestPhysics;
    }

// ---------------------------------------------------------------------------
// CApaDocument* CBCTestPhysicsApp::CreateDocumentL()
// Creates CbctestphysicsDocument object.
// ---------------------------------------------------------------------------
//
CApaDocument* CBCTestPhysicsApp::CreateDocumentL()
    {
    return CBCTestPhysicsDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ================================
//
// ---------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CBCTestPhysicsApp.
// Returns: CApaDocument*: created application object
// ---------------------------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CBCTestPhysicsApp;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
