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
* Description:  test application
*
*/


// INCLUDE FILES
#include "bctestdomcoreuidocument.h"
#include "bctestdomcoreuiappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDomCoreUiDocument* CBCTestDomCoreUiDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCoreUiDocument* CBCTestDomCoreUiDocument::NewL( CEikApplication& aApp )
    {
    CBCTestDomCoreUiDocument* self = new( ELeave ) CBCTestDomCoreUiDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDomCoreUiDocument::~CBCTestDomCoreUiDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCoreUiDocument::~CBCTestDomCoreUiDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDomCoreUiDocument::CBCTestDomCoreUiDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCoreUiDocument::CBCTestDomCoreUiDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDomCoreUiDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomCoreUiDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomCoreUiAppUi;
    }

// End of File
