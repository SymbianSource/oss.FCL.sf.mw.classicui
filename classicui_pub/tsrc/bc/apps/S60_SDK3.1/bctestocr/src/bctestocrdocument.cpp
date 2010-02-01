/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Implements test bc for ocr document.
*
*/









// INCLUDE FILES
#include "bctestocrdocument.h"
#include "bctestocrappui.h"

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestOCRDocument* CBCTestOCRDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestOCRDocument* CBCTestOCRDocument::NewL( CEikApplication& aApp )
    {
    CBCTestOCRDocument* self = new( ELeave ) CBCTestOCRDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestOCRDocument::~CBCTestOCRDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestOCRDocument::~CBCTestOCRDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestOCRDocument::CBCTestOCRDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestOCRDocument::CBCTestOCRDocument( CEikApplication& aApp )
    : CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestOCRDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestOCRDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestOCRAppUi;
    }
