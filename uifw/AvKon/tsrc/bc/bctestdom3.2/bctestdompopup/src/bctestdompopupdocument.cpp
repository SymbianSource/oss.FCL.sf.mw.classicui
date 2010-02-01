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


#include "bctestdompopupudocument.h"
#include "bctestdompopupappui.h"


// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCDomainTestPopupDocument* CBCDomainTestPopupDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupDocument* CBCDomainTestPopupDocument::NewL( 
    CEikApplication& aApp )
    {
    CBCDomainTestPopupDocument* self = 
        new( ELeave ) CBCDomainTestPopupDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupDocument::~CBCDomainTestPopupDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupDocument::~CBCDomainTestPopupDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCDomainTestPopupDocument::CBCDomainTestPopupDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCDomainTestPopupDocument::CBCDomainTestPopupDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCDomainTestPopupDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCDomainTestPopupDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCDomainTestPopupAppUi;
    }

// End of File
