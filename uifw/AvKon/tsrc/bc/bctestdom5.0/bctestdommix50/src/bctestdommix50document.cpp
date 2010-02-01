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


#include "bctestdommix50document.h"
#include "bctestdommix50appui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestDomMix50Document::NewL()
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Document* CBCTestDomMix50Document::NewL( CEikApplication& aApp )
    {
    CBCTestDomMix50Document* self = new( ELeave ) CBCTestDomMix50Document( aApp );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Document::~CBCTestDomMix50Document()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Document::~CBCTestDomMix50Document()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Document::CBCTestDomMix50Document()
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomMix50Document::CBCTestDomMix50Document( CEikApplication& aApp )
    : CEikDocument( aApp )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestDomMix50Document::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomMix50Document::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomMix50AppUi;
    }
