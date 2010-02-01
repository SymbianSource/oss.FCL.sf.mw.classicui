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
* Description:         Avkon Misc test application
*
*/









// INCLUDE FILES
#include "bctestmiscdocument.h"
#include "bctestmiscappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestMiscDocument* CBCTestMiscDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestMiscDocument* CBCTestMiscDocument::NewL( CEikApplication& aApp )
    {
    CBCTestMiscDocument* self = new( ELeave ) CBCTestMiscDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestMiscDocument::~CBCTestMiscDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestMiscDocument::~CBCTestMiscDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestMiscDocument::CBCTestMiscDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestMiscDocument::CBCTestMiscDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestMiscDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestMiscDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestMiscAppUi;
    }

