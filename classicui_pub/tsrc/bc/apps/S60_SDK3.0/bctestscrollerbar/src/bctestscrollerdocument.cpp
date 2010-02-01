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
* Description:         Avkon Scroller test application
*
*/









// INCLUDE FILES
#include "BCTestScrollerDocument.h"
#include "BCTestScrollerAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestScrollerDocument* CBCTestScrollerDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestScrollerDocument* CBCTestScrollerDocument::NewL( CEikApplication& aApp )
    {
    CBCTestScrollerDocument* self = new( ELeave ) CBCTestScrollerDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestScrollerDocument::~CBCTestScrollerDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestScrollerDocument::~CBCTestScrollerDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestScrollerDocument::CBCTestScrollerDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestScrollerDocument::CBCTestScrollerDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestScrollerDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestScrollerDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestScrollerAppUi;
    }

// End of File
