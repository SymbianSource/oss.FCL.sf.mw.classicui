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
* Description:         test application
*
*/









// INCLUDE FILES
#include "bctestlocalizerdocument.h"
#include "bctestlocalizerappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestLocalizerDocument* CBCTestLocalizerDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestLocalizerDocument* CBCTestLocalizerDocument::NewL( CEikApplication& aApp )
    {
    CBCTestLocalizerDocument* self = new( ELeave ) CBCTestLocalizerDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestLocalizerDocument::~CBCTestLocalizerDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestLocalizerDocument::~CBCTestLocalizerDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestLocalizerDocument::CBCTestLocalizerDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestLocalizerDocument::CBCTestLocalizerDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestLocalizerDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestLocalizerDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestLocalizerAppUi;
    }

// End of File
