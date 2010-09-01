/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  document
*
*/


#include "bctesttemplatedocument.h"
#include "bctesttemplateappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestTemplateDocument* CBCTestTemplateDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCTestTemplateDocument* CBCTestTemplateDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestTemplateDocument* self = 
        new( ELeave ) CBCTestTemplateDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateDocument::~CBCTestTemplateDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestTemplateDocument::~CBCTestTemplateDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestTemplateDocument::CBCTestTemplateDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestTemplateDocument::CBCTestTemplateDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestTemplateDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestTemplateDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestTemplateAppUi;
    }

// End of File
