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
* Description:         Avkon misc test application
*
*/









// INCLUDE FILES
#include "bctestmisc32document.h"
#include "bctestmisc32appui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestmisc32Document* CBCTestmisc32Document::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestmisc32Document* CBCTestmisc32Document::NewL( CEikApplication& aApp )
    {
    CBCTestmisc32Document* self = new( ELeave ) CBCTestmisc32Document( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestmisc32Document::~CBCTestmisc32Document()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestmisc32Document::~CBCTestmisc32Document()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestmisc32Document::CBCTestmisc32Document( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestmisc32Document::CBCTestmisc32Document( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestmisc32Document::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestmisc32Document::CreateAppUiL()
    {
    return new( ELeave ) CBCTestmisc32AppUi;
    }

// End of File
