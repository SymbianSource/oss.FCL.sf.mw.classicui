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
* Description:         Avkon SliderAndIcons test application
*
*/









// INCLUDE FILES
#include "BCTestSliderAndIconsDocument.h"
#include "BCTestSliderAndIconsAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestSliderAndIconsDocument* CBCTestSliderAndIconsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestSliderAndIconsDocument* CBCTestSliderAndIconsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestSliderAndIconsDocument* self = new( ELeave ) CBCTestSliderAndIconsDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestSliderAndIconsDocument::~CBCTestSliderAndIconsDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestSliderAndIconsDocument::~CBCTestSliderAndIconsDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestSliderAndIconsDocument::CBCTestSliderAndIconsDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestSliderAndIconsDocument::CBCTestSliderAndIconsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestSliderAndIconsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestSliderAndIconsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestSliderAndIconsAppUi;
    }

// End of File
