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
* Description:         Avkon KeyLock test application
*
*/









// INCLUDE FILES
#include "BCTestKeyLockDocument.h"
#include "BCTestKeyLockAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestKeyLockDocument* CBCTestKeyLockDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestKeyLockDocument* CBCTestKeyLockDocument::NewL( CEikApplication& aApp )
    {
    CBCTestKeyLockDocument* self = new( ELeave ) CBCTestKeyLockDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestKeyLockDocument::~CBCTestKeyLockDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestKeyLockDocument::~CBCTestKeyLockDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestKeyLockDocument::CBCTestKeyLockDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestKeyLockDocument::CBCTestKeyLockDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestKeyLockDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestKeyLockDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestKeyLockAppUi;
    }

// End of File
