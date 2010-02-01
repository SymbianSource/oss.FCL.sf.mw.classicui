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
* Description:         Document
*
*/









#include "BCTestUtilitiesDocument.h"
#include "BCTestUtilitiesAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestUtilitiesDocument* CBCTestUtilitiesDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestUtilitiesDocument* CBCTestUtilitiesDocument::NewL( CEikApplication& aApp )
    {
    CBCTestUtilitiesDocument* self = new( ELeave ) CBCTestUtilitiesDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestUtilitiesDocument::~CBCTestUtilitiesDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestUtilitiesDocument::~CBCTestUtilitiesDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestUtilitiesDocument::CBCTestUtilitiesDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestUtilitiesDocument::CBCTestUtilitiesDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestUtilitiesDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestUtilitiesDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestUtilitiesAppUi;
    }


