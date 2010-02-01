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
* Description:         Avkon Template test application
*
*/









// INCLUDE FILES
#include "BCTestButtonDocument.h"
#include "BCTestButtonAppUi.h"

// ================= MEMBER FUNCTIONS =======================================

// ---------------------------------------------------------------------------
// CBCTestButtonDocument* CBCTestButtonDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonDocument* CBCTestButtonDocument::NewL( CEikApplication& aApp )
    {
    CBCTestButtonDocument* self = new( ELeave ) CBCTestButtonDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestButtonDocument::~CBCTestButtonDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonDocument::~CBCTestButtonDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestButtonDocument::CBCTestButtonDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonDocument::CBCTestButtonDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestButtonDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestButtonDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestButtonAppUi;
    }

// End of File
