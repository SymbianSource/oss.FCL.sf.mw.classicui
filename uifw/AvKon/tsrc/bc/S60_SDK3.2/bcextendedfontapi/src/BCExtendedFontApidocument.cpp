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


#include "BCExtendedFontApidocument.h"
#include "BCExtendedFontApiappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCExtendedFontApiDocument* CBCExtendedFontApiDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiDocument* CBCExtendedFontApiDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCExtendedFontApiDocument* self = 
        new( ELeave ) CBCExtendedFontApiDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiDocument::~CBCExtendedFontApiDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiDocument::~CBCExtendedFontApiDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCExtendedFontApiDocument::CBCExtendedFontApiDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCExtendedFontApiDocument::CBCExtendedFontApiDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCExtendedFontApiDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCExtendedFontApiDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCExtendedFontApiAppUi;
    }

// End of File
