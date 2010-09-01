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

#include "bctestphysicsdocument.h"
#include "bctestphysicsappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestPhysicsDocument* CBCTestPhysicsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestPhysicsDocument* CBCTestPhysicsDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestPhysicsDocument* self = 
        new( ELeave ) CBCTestPhysicsDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsDocument::~CBCTestPhysicsDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestPhysicsDocument::~CBCTestPhysicsDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPhysicsDocument::CBCTestPhysicsDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestPhysicsDocument::CBCTestPhysicsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestPhysicsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestPhysicsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPhysicsAppUi;
    }

// End of File
