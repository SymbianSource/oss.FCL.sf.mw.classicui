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
* Description:         Avkon Template test application
*
*/









// INCLUDE FILES
#include "BCTestTreeListDocument.h"
#include "BCTestTreeListAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestTemplateDocument* CBCTestTemplateDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestTreeListDocument* CBCTestTreeListDocument::NewL( CEikApplication& aApp )
    {
    CBCTestTreeListDocument* self = new( ELeave ) CBCTestTreeListDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestTemplateDocument::~CBCTestTemplateDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestTreeListDocument::~CBCTestTreeListDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestTemplateDocument::CBCTestTemplateDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestTreeListDocument::CBCTestTreeListDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestTemplateDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestTreeListDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestTreeListAppUi;
    }

// End of File
