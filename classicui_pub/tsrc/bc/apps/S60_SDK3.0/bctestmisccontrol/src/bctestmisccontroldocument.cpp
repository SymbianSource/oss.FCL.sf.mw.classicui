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
* Description:         Implements test bc for misc control document.
*
*/









// INCLUDE FILES 
#include "bctestmisccontroldocument.h"
#include "bctestmisccontrolappUi.h"

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestMiscControlDocument* CBCTestMiscControlDocument
// ::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestMiscControlDocument* CBCTestMiscControlDocument
    ::NewL( CEikApplication& aApp )
    {
    CBCTestMiscControlDocument* self = 
        new( ELeave ) CBCTestMiscControlDocument( aApp );
    return self; 
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlDocument::~CBCTestMiscControlDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestMiscControlDocument::~CBCTestMiscControlDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestMiscControlDocument::CBCTestMiscControlDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestMiscControlDocument::CBCTestMiscControlDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestMiscControlDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestMiscControlDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestMiscControlAppUi; 
    }
