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
* Description:         Avkon PrivateUIFrm test application
*
*/









// INCLUDE FILES
#include "BCTestPrivateUIFrmDocument.h"
#include "BCTestPrivateUIFrmAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestPrivateUIFrmDocument* CBCTestPrivateUIFrmDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestPrivateUIFrmDocument* CBCTestPrivateUIFrmDocument::NewL( CEikApplication& aApp )
    {
    CBCTestPrivateUIFrmDocument* self = new( ELeave ) CBCTestPrivateUIFrmDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestPrivateUIFrmDocument::~CBCTestPrivateUIFrmDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPrivateUIFrmDocument::~CBCTestPrivateUIFrmDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestPrivateUIFrmDocument::CBCTestPrivateUIFrmDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestPrivateUIFrmDocument::CBCTestPrivateUIFrmDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestPrivateUIFrmDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestPrivateUIFrmDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPrivateUIFrmAppUi;
    }

// End of File
