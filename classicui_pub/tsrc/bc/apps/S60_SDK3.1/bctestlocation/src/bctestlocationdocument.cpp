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
* Description:         Avkon Template test application
*
*/









// INCLUDE FILES
#include "BCTestLocationDocument.h"
#include "BCTestLocationAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestLocationDocument* CBCTestLocationDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestLocationDocument* CBCTestLocationDocument::NewL( CEikApplication& aApp )
    {
    CBCTestLocationDocument* self = new( ELeave ) CBCTestLocationDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestLocationDocument::~CBCTestLocationDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestLocationDocument::~CBCTestLocationDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestLocationDocument::CBCTestLocationDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestLocationDocument::CBCTestLocationDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestLocationDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestLocationDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestLocationAppUi;
    }

// End of File
