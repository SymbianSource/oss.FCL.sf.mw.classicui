/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Document class implementation for BCTestGlobalListMsgQuery.
*
*/

// INCLUDE FILES
#include "bctestgloballistmsgquerydocument.h"
#include "bctestgloballistmsgqueryappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryDocument::NewL()
// ----------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryDocument* CBCTestGlobalListMsgQueryDocument::NewL( CEikApplication& aApp )
    {
    CBCTestGlobalListMsgQueryDocument* self = new( ELeave ) CBCTestGlobalListMsgQueryDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryDocument::~CBCTestGlobalListMsgQueryDocument()
// ----------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryDocument::~CBCTestGlobalListMsgQueryDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryDocument::CBCTestGlobalListMsgQueryDocument()
// ----------------------------------------------------------------------------
//
CBCTestGlobalListMsgQueryDocument::CBCTestGlobalListMsgQueryDocument( CEikApplication& aApp )
    : CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CBCTestGlobalListMsgQueryDocument::CreateAppUiL()
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestGlobalListMsgQueryDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestGlobalListMsgQueryAppUi;
    }

// End of file
