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
* Description:         Avkon listbox test application
*
*/









// INCLUDE FILES
#include "BCTestListDocument.h"
#include "BCTestListAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestListDocument* CBCTestListDocument::NewL( CEikApplication& )
// Symbian two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestListDocument* CBCTestListDocument::NewL( CEikApplication& aApp )
    {
    CBCTestListDocument* self = new( ELeave ) CBCTestListDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestListDocument::~CBCTestListDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestListDocument::~CBCTestListDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestListDocument::CBCTestListDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestListDocument::CBCTestListDocument( CEikApplication& aApp )
    :   CAknDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// void CBCTestListDocument::ConstructL()
// Symbian 2nd phase constructor.
// ----------------------------------------------------------------------------
//
void CBCTestListDocument::ConstructL()
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestListDocument::CreateAppUiL()
// Constructs CBCTestListAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestListDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestListAppUi;
    }

// End of File
