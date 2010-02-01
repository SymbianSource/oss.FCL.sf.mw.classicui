/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         document
*
*/









#include "bctestmix50document.h"
#include "bctestmix50appui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestMix50Document::NewL()
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50Document* CBCTestMix50Document::NewL( CEikApplication& aApp )
    {
    CBCTestMix50Document* self = new( ELeave ) CBCTestMix50Document( aApp );
    return self;
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Document::~CBCTestMix50Document()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50Document::~CBCTestMix50Document()
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Document::CBCTestMix50Document()
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestMix50Document::CBCTestMix50Document( CEikApplication& aApp )
    : CEikDocument( aApp )
    {
    }


// ---------------------------------------------------------------------------
// CBCTestMix50Document::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestMix50Document::CreateAppUiL()
    {
    return new( ELeave ) CBCTestMix50AppUi;
    }
