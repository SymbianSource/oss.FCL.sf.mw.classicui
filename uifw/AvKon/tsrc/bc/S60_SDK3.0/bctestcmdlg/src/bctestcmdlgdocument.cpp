/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon Template test application
*
*/


// INCLUDE FILES
#include "BCTestCmDlgDocument.h"
#include "BCTestCmDlgAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestCmDlgDocument* CBCTestCmDlgDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestCmDlgDocument* CBCTestCmDlgDocument::NewL( CEikApplication& aApp )
    {
    CBCTestCmDlgDocument* self = new( ELeave ) CBCTestCmDlgDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestCmDlgDocument::~CBCTestCmDlgDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestCmDlgDocument::~CBCTestCmDlgDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestCmDlgDocument::CBCTestCmDlgDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestCmDlgDocument::CBCTestCmDlgDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestCmDlgDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestCmDlgDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestCmDlgAppUi;
    }

// End of File
