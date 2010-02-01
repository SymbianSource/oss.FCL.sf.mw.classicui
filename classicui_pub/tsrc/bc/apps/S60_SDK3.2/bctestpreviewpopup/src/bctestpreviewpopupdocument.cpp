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
* Description:         Avkon PreviewPopup test application
*
*/









// INCLUDE FILES
#include "BCTestPreviewPopupDocument.h"
#include "BCTestPreviewPopupAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestPreviewPopupDocument* CBCTestPreviewPopupDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestPreviewPopupDocument* CBCTestPreviewPopupDocument::NewL( CEikApplication& aApp )
    {
    CBCTestPreviewPopupDocument* self = new( ELeave ) CBCTestPreviewPopupDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestPreviewPopupDocument::~CBCTestPreviewPopupDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestPreviewPopupDocument::~CBCTestPreviewPopupDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestPreviewPopupDocument::CBCTestPreviewPopupDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestPreviewPopupDocument::CBCTestPreviewPopupDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestPreviewPopupDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestPreviewPopupDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestPreviewPopupAppUi;
    }

// End of File
