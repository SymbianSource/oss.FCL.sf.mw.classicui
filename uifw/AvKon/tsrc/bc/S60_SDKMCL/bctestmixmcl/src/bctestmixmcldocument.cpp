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
* Description:  document
*
*/


#include "bctestmixmcldocument.h"
#include "bctestmixmclappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestMixMCLDocument::NewL()
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestMixMCLDocument* CBCTestMixMCLDocument::NewL( CEikApplication& aApp )
    {
    CBCTestMixMCLDocument* self = new( ELeave ) CBCTestMixMCLDocument( aApp );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLDocument::~CBCTestMixMCLDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMixMCLDocument::~CBCTestMixMCLDocument()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLDocument::CBCTestMixMCLDocument()
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestMixMCLDocument::CBCTestMixMCLDocument( CEikApplication& aApp )
    : CEikDocument( aApp )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMixMCLDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestMixMCLDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestMixMCLAppUi;
    }
