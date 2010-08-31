/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon FontInput test application
*
*/









// INCLUDE FILES
#include "BCTestfontinputDocument.h"
#include "BCTestfontinputAppUi.h"

// ================= MEMBER FUNCTIONS =========================================
 
// ----------------------------------------------------------------------------
// CBCTestfontinputDocument* CBCTestfontinputDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestFontInputDocument* CBCTestFontInputDocument::NewL( CEikApplication& aApp )
    {
    CBCTestFontInputDocument* self = new( ELeave ) CBCTestFontInputDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestFontInputDocument::~CBCTestFontInputDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFontInputDocument::~CBCTestFontInputDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestFontInputDocument::CBCTestFontInputDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestFontInputDocument::CBCTestFontInputDocument( CEikApplication& aApp )
    :CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestFontInputDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestFontInputDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestFontInputAppUi;
    }

// End of File
