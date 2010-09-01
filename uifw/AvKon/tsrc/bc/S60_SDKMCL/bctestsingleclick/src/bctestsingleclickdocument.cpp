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
* Description:  Document class of bctestsingleclick.
*
*/

#include "bctestsingleclickdocument.h"
#include "bctestsingleclickappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTESTSingleClickDocument* CBCTESTSingleClickDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickDocument* CBCTESTSingleClickDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTESTSingleClickDocument* self = 
        new( ELeave ) CBCTESTSingleClickDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickDocument::~CBCTESTSingleClickDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickDocument::~CBCTESTSingleClickDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTESTSingleClickDocument::CBCTESTSingleClickDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTESTSingleClickDocument::CBCTESTSingleClickDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTESTSingleClickDocument::CreateAppUiL()
// 
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTESTSingleClickDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTESTSingleClickAppUi;
    }

// End of File
