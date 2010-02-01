/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test application
*
*/


// INCLUDE FILES
#include "bctestMultiDriverdocument.h"
#include "bctestMultiDriverappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CMultiDriverDocument* CMultiDriverDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CMultiDriverDocument* CMultiDriverDocument::NewL( CEikApplication& aApp )
    {
    CMultiDriverDocument* self = new( ELeave ) CMultiDriverDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CMultiDriverDocument::~CMultiDriverDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CMultiDriverDocument::~CMultiDriverDocument()
    {
    }

// ----------------------------------------------------------------------------
// CMultiDriverDocument::CMultiDriverDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CMultiDriverDocument::CMultiDriverDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }
 
// ----------------------------------------------------------------------------
// CEikAppUi* CMultiDriverDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CMultiDriverDocument::CreateAppUiL()
    {
    return new( ELeave ) CMultiDriverAppUi;
    }

// End of File
