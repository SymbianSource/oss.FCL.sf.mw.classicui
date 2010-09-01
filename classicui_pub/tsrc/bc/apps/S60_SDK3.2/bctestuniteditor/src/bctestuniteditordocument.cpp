/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         Avkon UnitEditor test application
*
*/









// INCLUDE FILES
#include "BCTestUnitEditorDocument.h"
#include "BCTestUnitEditorAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestUnitEditorDocument* CBCTestUnitEditorDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestUnitEditorDocument* CBCTestUnitEditorDocument::NewL( CEikApplication& aApp )
    {
    CBCTestUnitEditorDocument* self = new( ELeave ) CBCTestUnitEditorDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestUnitEditorDocument::~CBCTestUnitEditorDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestUnitEditorDocument::~CBCTestUnitEditorDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestUnitEditorDocument::CBCTestUnitEditorDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestUnitEditorDocument::CBCTestUnitEditorDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestUnitEditorDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestUnitEditorDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestUnitEditorAppUi;
    }

// End of File
