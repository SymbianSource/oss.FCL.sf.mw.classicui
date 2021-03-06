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
* Description:         For bctestform application
*
*/









// INCLUDE FILES
#include "BCTestFormDocument.h"
#include "BCTestFormAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestFormDocument* CBCTestFormDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestFormDocument* CBCTestFormDocument::NewL( CEikApplication& aApp )
    {
    CBCTestFormDocument* self = new( ELeave ) CBCTestFormDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestFormDocument::~CBCTestFormDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestFormDocument::~CBCTestFormDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestFormDocument::CBCTestFormDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestFormDocument::CBCTestFormDocument( CEikApplication& aApp )
:   CAknDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestFormDocument::CreateAppUiL()
// Constructs CBCTestFormAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestFormDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestFormAppUi;
    }

// End of File
