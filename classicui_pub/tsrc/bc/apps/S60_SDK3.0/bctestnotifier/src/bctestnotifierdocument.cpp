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
* Description:         Avkon SettingPage test application
*
*/









// INCLUDE FILES
#include "BCTestNotifierDocument.h"
#include "BCTestNotifierAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestNotifierDocument* CBCTestNotifierDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestNotifierDocument* CBCTestNotifierDocument::NewL( CEikApplication& aApp )
    {
    CBCTestNotifierDocument* self = new( ELeave ) CBCTestNotifierDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestNotifierDocument::~CBCTestNotifierDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestNotifierDocument::~CBCTestNotifierDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestNotifierDocument::CBCTestNotifierDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestNotifierDocument::CBCTestNotifierDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestNotifierDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestNotifierDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestNotifierAppUi;
    }

// End of File
