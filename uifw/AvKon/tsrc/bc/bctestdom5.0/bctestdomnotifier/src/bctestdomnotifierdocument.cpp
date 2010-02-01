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


#include "bctestdomnotifierdocument.h"
#include "bctestdomnotifierappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierDocument* CBCDomainTestNotifierDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierDocument* CBCDomainTestNotifierDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCDomainTestNotifierDocument* self = 
        new( ELeave ) CBCDomainTestNotifierDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierDocument::~CBCDomainTestNotifierDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierDocument::~CBCDomainTestNotifierDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestNotifierDocument::CBCDomainTestNotifierDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestNotifierDocument::CBCDomainTestNotifierDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCDomainTestNotifierDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCDomainTestNotifierDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCDomainTestNotifierAppUi;
    }

// End of File
