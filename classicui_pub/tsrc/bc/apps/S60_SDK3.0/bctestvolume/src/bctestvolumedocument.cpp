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
* Description:         Avkon volume test application
*
*/









// INCLUDE FILES
#include "BCTestVolumeDocument.h"
#include "BCTestVolumeAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestVolumeDocument* CBCTestVolumeDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeDocument* CBCTestVolumeDocument::NewL( CEikApplication& aApp )
    {
    CBCTestVolumeDocument* self = new( ELeave ) CBCTestVolumeDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeDocument::~CBCTestVolumeDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeDocument::~CBCTestVolumeDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestVolumeDocument::CBCTestVolumeDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestVolumeDocument::CBCTestVolumeDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestVolumeDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestVolumeDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestVolumeAppUi;
    }

// End of File
