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
#include "BCTestImageDocument.h"
#include "BCTestImageAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestImageDocument* CBCTestImageDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestImageDocument* CBCTestImageDocument::NewL( CEikApplication& aApp )
    {
    CBCTestImageDocument* self = new( ELeave ) CBCTestImageDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestImageDocument::~CBCTestImageDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestImageDocument::~CBCTestImageDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestImageDocument::CBCTestImageDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestImageDocument::CBCTestImageDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestImageDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestImageDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestImageAppUi;
    }

// End of File
