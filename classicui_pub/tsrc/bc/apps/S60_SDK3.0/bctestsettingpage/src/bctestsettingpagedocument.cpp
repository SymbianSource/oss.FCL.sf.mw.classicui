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
* Description:         Avkon SettingPage test application
*
*/









// INCLUDE FILES
#include "BCTestSettingPageDocument.h"
#include "BCTestSettingPageAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestSettingPageDocument* CBCTestSettingPageDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestSettingPageDocument* CBCTestSettingPageDocument::NewL( CEikApplication& aApp )
    {
    CBCTestSettingPageDocument* self = new( ELeave ) CBCTestSettingPageDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestSettingPageDocument::~CBCTestSettingPageDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestSettingPageDocument::~CBCTestSettingPageDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestSettingPageDocument::CBCTestSettingPageDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestSettingPageDocument::CBCTestSettingPageDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestSettingPageDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestSettingPageDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestSettingPageAppUi;
    }

// End of File
