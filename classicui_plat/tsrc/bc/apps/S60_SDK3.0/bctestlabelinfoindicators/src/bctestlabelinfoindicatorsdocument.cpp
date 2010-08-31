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
* Description:         Implements test bc for labelinfoindicators document.
*
*/









// INCLUDE FILES
#include "bctestlabelinfoindicatorsdocument.h"
#include "bctestlabelinfoindicatorsappUi.h"

// ================= MEMBER FUNCTIONS ========================================

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsDocument* CBCTestLabelInfoIndicatorsDocument
//   ::NewL( CEikApplication& )
// Symbian OS two-phased constructor. 
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsDocument* CBCTestLabelInfoIndicatorsDocument
    ::NewL( CEikApplication& aApp )
    {
    CBCTestLabelInfoIndicatorsDocument* self = new( ELeave ) 
        CBCTestLabelInfoIndicatorsDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsDocument::~CBCTestLabelInfoIndicatorsDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsDocument::~CBCTestLabelInfoIndicatorsDocument()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestLabelInfoIndicatorsDocument::
//  CBCTestLabelInfoIndicatorsDocument( CEikApplication& )
// Overload constructor.
// ---------------------------------------------------------------------------
//
CBCTestLabelInfoIndicatorsDocument
    ::CBCTestLabelInfoIndicatorsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ---------------------------------------------------------------------------
// CEikAppUi* CBCTestLabelInfoIndicatorsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CBCTestLabelInfoIndicatorsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestLabelInfoIndicatorsAppUi;
    }
