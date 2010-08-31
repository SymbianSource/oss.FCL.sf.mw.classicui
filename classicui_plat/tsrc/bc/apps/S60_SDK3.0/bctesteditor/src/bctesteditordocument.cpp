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
* Description:         Avkon Editor test application
*
*/









// INCLUDE FILES
#include "BCTestEditorDocument.h"
#include "BCTestEditorAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestEditorDocument* CBCTestEditorDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestEditorDocument* CBCTestEditorDocument::NewL( CEikApplication& aApp )
    {
    CBCTestEditorDocument* self = new( ELeave ) CBCTestEditorDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestEditorDocument::~CBCTestEditorDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestEditorDocument::~CBCTestEditorDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestEditorDocument::CBCTestEditorDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestEditorDocument::CBCTestEditorDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestEditorDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestEditorDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestEditorAppUi;
    }

// End of File
