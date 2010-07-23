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
* Description:         Avkon ScreenClearer test application
*
*/









// INCLUDE FILES
#include "bctestscreenclearerdocument.h"
#include "bctestscreenclearerappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestScreenClearerDocument* CBCTestScreenClearerDocument::NewL( 
//    CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestScreenClearerDocument* CBCTestScreenClearerDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestScreenClearerDocument* self = 
        new( ELeave ) CBCTestScreenClearerDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestScreenClearerDocument::~CBCTestScreenClearerDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestScreenClearerDocument::~CBCTestScreenClearerDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestScreenClearerDocument::CBCTestScreenClearerDocument( 
//    CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestScreenClearerDocument::CBCTestScreenClearerDocument( 
    CEikApplication& aApp ):   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestScreenClearerDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestScreenClearerDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestScreenClearerAppUi;
    }

