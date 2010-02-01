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
#include "BCTestPtiEngDocument.h"
#include "BCTestPtiEngAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestPtiEngDocument* CBCTestPtiEngDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestPtiEngDocument* CBCTestPtiEngDocument::NewL( CEikApplication& aApp )
    {
    CBCTestPtiEngDocument* self = new( ELeave ) CBCTestPtiEngDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestPtiEngDocument::~CBCTestPtiEngDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPtiEngDocument::~CBCTestPtiEngDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestPtiEngDocument::CBCTestPtiEngDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestPtiEngDocument::CBCTestPtiEngDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestPtiEngDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestPtiEngDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPtiEngAppUi;
    }

// End of File
