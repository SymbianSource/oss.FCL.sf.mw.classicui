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
* Description:         view class
*
*/








#include "bctestsearchfielddocument.h"
#include "bctestsearchfieldappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestSearchFieldDocument* CBCTestSearchFieldDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestSearchFieldDocument* CBCTestSearchFieldDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestSearchFieldDocument* self = new( ELeave ) 
        CBCTestSearchFieldDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestSearchFieldDocument::~CBCTestSearchFieldDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestSearchFieldDocument::~CBCTestSearchFieldDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestSearchFieldDocument::CBCTestSearchFieldDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestSearchFieldDocument::CBCTestSearchFieldDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestSearchFieldDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestSearchFieldDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestSearchFieldAppUi;
    }
