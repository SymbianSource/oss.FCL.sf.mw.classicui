/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CAknConfDocument implementation
 *
*/


// INCLUDE FILES
#include "aknconfappui.h"
#include "aknconfdocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknConfDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknConfDocument* CAknConfDocument::NewL( CEikApplication& aApp )
    {
    CAknConfDocument* self = NewLC( aApp );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CAknConfDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknConfDocument* CAknConfDocument::NewLC(CEikApplication& aApp)
    {
    CAknConfDocument* self = new ( ELeave ) CAknConfDocument( aApp );

    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CAknConfDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknConfDocument::ConstructL()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CAknConfDocument::CAknConfDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CAknConfDocument::CAknConfDocument(CEikApplication& aApp) :
    CAknDocument(aApp)
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CAknConfDocument::~CAknConfDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CAknConfDocument::~CAknConfDocument()
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CAknConfDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CAknConfDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it
    // the framework takes ownership of this object
    return new ( ELeave )CAknConfAppUi;
    }

// End of File
