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
* Description:         avkon buttons test application
*
*/









// INCLUDE FILES
#include "bctestbuttonsdocument.h"
#include "bctestbuttonsappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestButtonsDocument* CBCTestButtonsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonsDocument* CBCTestButtonsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestButtonsDocument* self = 
        new( ELeave ) CBCTestButtonsDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestButtonsDocument::~CBCTestButtonsDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonsDocument::~CBCTestButtonsDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestButtonsDocument::CBCTestButtonsDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestButtonsDocument::CBCTestButtonsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestButtonsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestButtonsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestButtonsAppUi;
    }




