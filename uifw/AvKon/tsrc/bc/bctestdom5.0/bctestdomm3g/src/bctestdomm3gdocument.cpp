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
* Description:  Implement document class
*
*/


#include "bctestdomm3gdocument.h"
#include "bctestdomm3gappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDomM3gDocument* CBCTestDomM3gDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomM3gDocument* CBCTestDomM3gDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCTestDomM3gDocument* self = new( ELeave ) 
        CBCTestDomM3gDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDomM3gDocument::~CBCTestDomM3gDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomM3gDocument::~CBCTestDomM3gDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDomM3gDocument::CBCTestDomM3gDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomM3gDocument::CBCTestDomM3gDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDomM3gDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomM3gDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomM3gAppUi;
    }
