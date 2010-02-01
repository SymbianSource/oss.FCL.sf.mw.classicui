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
* Description:         ServiceHandler test application
*
*/









// INCLUDE FILES
#include "bctestservicehandlerdocument.h"
#include "bctestservicehandlerappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestServiceHandlerDocument* CBCTestServiceHandlerDocument::NewL( CEikApplication& aApp )
    {
    CBCTestServiceHandlerDocument* self = new( ELeave ) CBCTestServiceHandlerDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestServiceHandlerDocument::~CBCTestServiceHandlerDocument()
    {
    }

// ----------------------------------------------------------------------------
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestServiceHandlerDocument::CBCTestServiceHandlerDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestServiceHandlerDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestServiceHandlerAppUi;
    }

// End of File
