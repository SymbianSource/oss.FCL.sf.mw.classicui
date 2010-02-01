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
* Description:         Avkon Grids test application
*
*/









// INCLUDE FILES
#include "bctestgridsdocument.h"
#include "bctestgridsappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestGridsDocument* CBCTestGridsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestGridsDocument* CBCTestGridsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestGridsDocument* self = new( ELeave ) CBCTestGridsDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestGridsDocument::~CBCTestGridsDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestGridsDocument::~CBCTestGridsDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestGridsDocument::CBCTestGridsDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestGridsDocument::CBCTestGridsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestGridsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestGridsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestGridsAppUi;
    }

