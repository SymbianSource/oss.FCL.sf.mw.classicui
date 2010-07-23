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
#include "BCTestServerappDocument.h"
#include "BCTestServerappAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestServerappDocument* CBCTestServerappDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestServerappDocument* CBCTestServerappDocument::NewL( CEikApplication& aApp )
    {
    CBCTestServerappDocument* self = new( ELeave ) CBCTestServerappDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestServerappDocument::~CBCTestServerappDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestServerappDocument::~CBCTestServerappDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestServerappDocument::CBCTestServerappDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestServerappDocument::CBCTestServerappDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestServerappDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestServerappDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestServerappAppUi;
    }

// End of File
