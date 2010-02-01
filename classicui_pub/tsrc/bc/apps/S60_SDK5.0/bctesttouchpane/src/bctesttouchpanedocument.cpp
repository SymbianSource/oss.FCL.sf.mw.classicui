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
* Description:         Avkon TouchPane test application
*
*/









// INCLUDE FILES
#include "bctesttouchpanedocument.h"
#include "bctesttouchpaneappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestTouchPaneDocument* CBCTestTouchPaneDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestTouchPaneDocument* CBCTestTouchPaneDocument::NewL( CEikApplication& aApp )
    {
    CBCTestTouchPaneDocument* self = 
    	new( ELeave ) CBCTestTouchPaneDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestTouchPaneDocument::~CBCTestTouchPaneDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestTouchPaneDocument::~CBCTestTouchPaneDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestTouchPaneDocument::CBCTestTouchPaneDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestTouchPaneDocument::CBCTestTouchPaneDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestTouchPaneDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestTouchPaneDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestTouchPaneAppUi;
    }

