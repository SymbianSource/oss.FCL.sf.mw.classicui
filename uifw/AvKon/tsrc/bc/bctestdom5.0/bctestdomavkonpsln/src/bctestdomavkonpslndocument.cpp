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
* Description:  ?Description
*
*/


#include "bctestdomavkonpslndocument.h"
#include "bctestdomavkonpslnappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnDocument* CBCTestDomAvkonPslnDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnDocument* CBCTestDomAvkonPslnDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestDomAvkonPslnDocument* self = 
        new( ELeave ) CBCTestDomAvkonPslnDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnDocument::~CBCTestDomAvkonPslnDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnDocument::~CBCTestDomAvkonPslnDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAvkonPslnDocument::CBCTestDomAvkonPslnDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAvkonPslnDocument::CBCTestDomAvkonPslnDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestDomAvkonPslnDocument::CreateAppUiL()
// Constructs CBCTestDomVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomAvkonPslnDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomAvkonPslnAppUi;
    }

// End of File
