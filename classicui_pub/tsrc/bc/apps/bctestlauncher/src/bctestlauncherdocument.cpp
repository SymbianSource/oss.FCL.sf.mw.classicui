/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements document class for application.
*
*/









#include "bctestlauncherdocument.h"
#include "bctestlauncherappui.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CBCTestLauncherDocument::CBCTestLauncherDocument( CEikApplication& aApp )
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CBCTestLauncherDocument::CBCTestLauncherDocument( CEikApplication& aApp )
                   : CAknDocument( aApp ) 
    {
    }

// ---------------------------------------------------------------------------
// CAknAtPbarDocument::~CBCTestLauncherDocument
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestLauncherDocument::~CBCTestLauncherDocument()
    {
    }

// ---------------------------------------------------------------------------
// CAknAtPbarDocument::ConstructL
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CBCTestLauncherDocument::ConstructL()
    {
    }

// ---------------------------------------------------------------------------
// CAknAtPbarDocument::NewL
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestLauncherDocument* CBCTestLauncherDocument::NewL
                           ( CEikApplication& aApp )
                           // CBCTestLauncherApp reference
    {
    CBCTestLauncherDocument* self = 
        new( ELeave ) CBCTestLauncherDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
    
// ---------------------------------------------------------------------------
// CBCTestLauncherDocument::CreateAppUiL()
// constructs CBCTestLauncherAppUi
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestLauncherDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestLauncherAppUi;
    }

