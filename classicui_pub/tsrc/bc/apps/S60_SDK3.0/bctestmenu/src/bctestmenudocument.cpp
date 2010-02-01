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
* Description:         Avkon Menu test application
*
*/









// INCLUDE FILES
#include "BCTestmenuDocument.h"
#include "BCTestmenuAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestMenuDocument* CBCTestMenuDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestMenuDocument* CBCTestMenuDocument::NewL( CEikApplication& aApp )
    {
    CBCTestMenuDocument* self = new( ELeave ) CBCTestMenuDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestMenuDocument::~CBCTestMenuDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestMenuDocument::~CBCTestMenuDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestMenuDocument::CBCTestMenuDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestMenuDocument::CBCTestMenuDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestMenuDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestMenuDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestMenuAppUi;
    }

// End of File
