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
* Description:         Document
*
*/









#include "BCTestPaneDocument.h"
#include "BCTestPaneAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestPaneDocument* CBCTestPaneDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestPaneDocument* CBCTestPaneDocument::NewL( CEikApplication& aApp )
    {
    CBCTestPaneDocument* self = new( ELeave ) CBCTestPaneDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestPaneDocument::~CBCTestPaneDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPaneDocument::~CBCTestPaneDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestPaneDocument::CBCTestPaneDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestPaneDocument::CBCTestPaneDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestPaneDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestPaneDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPaneAppUi;
    }
