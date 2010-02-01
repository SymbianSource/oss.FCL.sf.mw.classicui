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
* Description:         Implements test bc for popups control document.
*
*/









// INCLUDE FILES 
#include "bctestpopupsdocument.h"
#include "bctestpopupsappUi.h"

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestPopupsDocument* CBCTestPopupsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestPopupsDocument* CBCTestPopupsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestPopupsDocument* self = new( ELeave ) CBCTestPopupsDocument( aApp );
    return self;  
  
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsDocument::~CBCTestPopupsDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestPopupsDocument::~CBCTestPopupsDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestPopupsDocument::CBCTestPopupsDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestPopupsDocument::CBCTestPopupsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestPopupsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestPopupsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPopupsAppUi;
    }
