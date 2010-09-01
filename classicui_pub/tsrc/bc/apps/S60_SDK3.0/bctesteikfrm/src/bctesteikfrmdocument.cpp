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
#include "BCTestEikFrmDocument.h"
#include "BCTestEikFrmAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestEikFrmDocument* CBCTestEikFrmDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestEikFrmDocument* CBCTestEikFrmDocument::NewL( CEikApplication& aApp )
    {
    CBCTestEikFrmDocument* self = new( ELeave ) CBCTestEikFrmDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestEikFrmDocument::~CBCTestEikFrmDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestEikFrmDocument::~CBCTestEikFrmDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestEikFrmDocument::CBCTestEikFrmDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestEikFrmDocument::CBCTestEikFrmDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestEikFrmDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestEikFrmDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestEikFrmAppUi;
    }

// End of File
