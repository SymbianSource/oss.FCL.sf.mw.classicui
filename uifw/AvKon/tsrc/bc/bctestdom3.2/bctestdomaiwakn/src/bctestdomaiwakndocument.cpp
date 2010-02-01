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


#include "bctestdomaiwakndocument.h"
#include "bctestdomaiwaknappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknDocument* CBCTestDomAiwAknDocument::NewL( CEikApplication&)
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknDocument* CBCTestDomAiwAknDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestDomAiwAknDocument* self = 
        new( ELeave ) CBCTestDomAiwAknDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknDocument::~CBCTestDomAiwAknDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknDocument::~CBCTestDomAiwAknDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestDomAiwAknDocument::CBCTestDomAiwAknDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestDomAiwAknDocument::CBCTestDomAiwAknDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestDomAiwAknDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomAiwAknDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomAiwAknAppUi;
    }

// End of File
