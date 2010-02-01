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
* Description:         test application
*
*/









// INCLUDE FILES
#include "BCTestChoicelistdocument.h"
#include "BCTestChoicelistappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCPopupChoicelistDocument* CBCPopupChoicelistDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------

CBCPopupChoicelistDocument* CBCPopupChoicelistDocument::NewL( CEikApplication& aApp )
    {
    CBCPopupChoicelistDocument* self = 
    	new( ELeave ) CBCPopupChoicelistDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCPopupChoicelistDocument::~CBCPopupChoicelistDocument()
// Destructor.
// ----------------------------------------------------------------------------

CBCPopupChoicelistDocument::~CBCPopupChoicelistDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCPopupChoicelistDocument::CBCPopupChoicelistDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCPopupChoicelistDocument::CBCPopupChoicelistDocument( CEikApplication& aApp )
    :CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCPopupChoicelistDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------

CEikAppUi* CBCPopupChoicelistDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCPopupChoicelistAppUi;
    }

// End of File
