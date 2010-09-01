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
#include "BCTestSkinsDocument.h"
#include "BCTestSkinsAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestSkinsDocument* CBCTestSkinsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestSkinsDocument* CBCTestSkinsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestSkinsDocument* self = new( ELeave ) CBCTestSkinsDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestSkinsDocument::~CBCTestSkinsDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestSkinsDocument::~CBCTestSkinsDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestSkinsDocument::CBCTestSkinsDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestSkinsDocument::CBCTestSkinsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestSkinsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestSkinsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestSkinsAppUi;
    }

// End of File
