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



// INCLUDE FILES
#include "bctestdomcdldocument.h"
#include "bctestdomcdlappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDomCdlDocument* CBCTestDomCdlDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCdlDocument* CBCTestDomCdlDocument::NewL( CEikApplication& aApp )
    {
    CBCTestDomCdlDocument* self = new( ELeave ) CBCTestDomCdlDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDomCdlDocument::~CBCTestDomCdlDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCdlDocument::~CBCTestDomCdlDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDomCdlDocument::CBCTestDomCdlDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomCdlDocument::CBCTestDomCdlDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDomCdlDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomCdlDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomCdlAppUi;
    }

