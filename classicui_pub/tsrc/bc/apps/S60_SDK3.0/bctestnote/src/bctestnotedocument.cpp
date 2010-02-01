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
* Description:         Implements test bc for note control document.
*
*/









// INCLUDE FILES
#include "bctestnotedocument.h"
#include "bctestnoteappUi.h" 

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestNoteDocument* CBCTestNoteDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestNoteDocument* CBCTestNoteDocument::NewL( CEikApplication& aApp )
    {
    CBCTestNoteDocument* self = new( ELeave ) CBCTestNoteDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestNoteDocument::~CBCTestNoteDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestNoteDocument::~CBCTestNoteDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestNoteDocument::CBCTestNoteDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestNoteDocument::CBCTestNoteDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestNoteDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestNoteDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestNoteAppUi;
    }
