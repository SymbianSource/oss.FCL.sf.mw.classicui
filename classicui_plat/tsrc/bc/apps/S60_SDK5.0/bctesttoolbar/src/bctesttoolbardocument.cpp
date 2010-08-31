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
* Description:         test application
*
*/









// INCLUDE FILES
#include "bctesttoolbardocument.h"
#include "bctesttoolbarappui.h"

// ================= MEMBER FUNCTIONS =======================================

// --------------------------------------------------------------------------
// CBCTestToolBarDocument* CBCTestToolBarDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// --------------------------------------------------------------------------
//
CBCTestToolBarDocument* CBCTestToolBarDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestToolBarDocument* self = 
        new( ELeave ) CBCTestToolBarDocument( aApp );
    return self;
    }

// --------------------------------------------------------------------------
// CBCTestToolBarDocument::~CBCTestToolBarDocument()
// Destructor.
// --------------------------------------------------------------------------
//
CBCTestToolBarDocument::~CBCTestToolBarDocument()
    {
    }

// --------------------------------------------------------------------------
// CBCTestToolBarDocument::CBCTestToolBarDocument( CEikApplication& )
// Overload constructor.
// --------------------------------------------------------------------------
//
CBCTestToolBarDocument::CBCTestToolBarDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// --------------------------------------------------------------------------
// CEikAppUi* CBCTestToolBarDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// --------------------------------------------------------------------------
//
CEikAppUi* CBCTestToolBarDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestToolBarAppUi;
    }

// End of File
