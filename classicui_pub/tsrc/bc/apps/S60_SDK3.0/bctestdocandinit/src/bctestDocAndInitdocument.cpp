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
* Description:         Avkon DocAndInit test application
*
*/









// INCLUDE FILES
#include "BCTestDocAndInitDocument.h"
#include "BCTestDocAndInitAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDocAndInitDocument* CBCTestDocAndInitDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDocAndInitDocument* CBCTestDocAndInitDocument::NewL( CEikApplication& aApp )
    {
    CBCTestDocAndInitDocument* self = new( ELeave ) CBCTestDocAndInitDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDocAndInitDocument::~CBCTestDocAndInitDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDocAndInitDocument::~CBCTestDocAndInitDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDocAndInitDocument::CBCTestDocAndInitDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDocAndInitDocument::CBCTestDocAndInitDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDocAndInitDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDocAndInitDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDocAndInitAppUi;
    }

// End of File
