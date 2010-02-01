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
#include "BCTestEHDocument.h"
#include "BCTestEHAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestEHDocument* CBCTestEHDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestEHDocument* CBCTestEHDocument::NewL( CEikApplication& aApp )
    {
    CBCTestEHDocument* self = new( ELeave ) CBCTestEHDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestEHDocument::~CBCTestEHDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestEHDocument::~CBCTestEHDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestEHDocument::CBCTestEHDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestEHDocument::CBCTestEHDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestEHDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestEHDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestEHAppUi;
    }

// End of File
