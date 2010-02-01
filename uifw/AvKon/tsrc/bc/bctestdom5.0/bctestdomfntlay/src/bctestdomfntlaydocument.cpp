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
* Description:  document class
*
*/


// INCLUDE FILES
#include "bctestdomfntlaydocument.h"
#include "bctestdomfntlayappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDomFntlayDocument* CBCTestDomFntlayDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomFntlayDocument* CBCTestDomFntlayDocument::NewL( CEikApplication& aApp )
    {
    CBCTestDomFntlayDocument* self = new( ELeave ) CBCTestDomFntlayDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDomFntlayDocument::~CBCTestDomFntlayDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomFntlayDocument::~CBCTestDomFntlayDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDomFntlayDocument::CBCTestDomFntlayDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomFntlayDocument::CBCTestDomFntlayDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDomFntlayDocument::CreateAppUiL()
// Constructs CBCTestDomVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomFntlayDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomFntlayAppUi;
    }
