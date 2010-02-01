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
* Description:         document
*
*/








#include "bctestquerydocument.h"
#include "bctestqueryappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestQueryDocument* CBCTestQueryDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestQueryDocument* CBCTestQueryDocument::NewL( CEikApplication& aApp )
    {
    CBCTestQueryDocument* self = new( ELeave ) CBCTestQueryDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestQueryDocument::~CBCTestQueryDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestQueryDocument::~CBCTestQueryDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestQueryDocument::CBCTestQueryDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestQueryDocument::CBCTestQueryDocument( CEikApplication& aApp )
    : CAknDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestQueryDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestQueryDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestQueryAppUi;
    }


