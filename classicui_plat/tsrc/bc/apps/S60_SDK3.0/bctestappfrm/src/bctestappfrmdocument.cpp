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
#include "bctestappfrmdocument.h"
#include "bctestappfrmappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestAppFrmDocument* CBCTestAppFrmDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestAppFrmDocument* CBCTestAppFrmDocument::NewL( CEikApplication& aApp )
    {
    CBCTestAppFrmDocument* self = new( ELeave ) CBCTestAppFrmDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestAppFrmDocument::~CBCTestAppFrmDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestAppFrmDocument::~CBCTestAppFrmDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestAppFrmDocument::CBCTestAppFrmDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestAppFrmDocument::CBCTestAppFrmDocument( CEikApplication& aApp )
    :   CAknDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestAppFrmDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestAppFrmDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestAppFrmAppUi;
    }

