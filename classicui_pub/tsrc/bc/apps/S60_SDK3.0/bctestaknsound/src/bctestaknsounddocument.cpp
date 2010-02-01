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
* Description:         Avkon Template test application
*
*/









// INCLUDE FILES
#include "bctestaknsounddocument.h"
#include "bctestaknsoundappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestAknSoundDocument* CBCTestAknSoundDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestAknSoundDocument* CBCTestAknSoundDocument::NewL( CEikApplication& aApp )
    {
    CBCTestAknSoundDocument* self = new( ELeave ) CBCTestAknSoundDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestAknSoundDocument::~CBCTestAknSoundDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestAknSoundDocument::~CBCTestAknSoundDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestAknSoundDocument::CBCTestAknSoundDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestAknSoundDocument::CBCTestAknSoundDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestAknSoundDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestAknSoundDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestAknSoundAppUi;
    }

