/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  DomInputMethods test application
*
*/


// INCLUDE FILES
#include "bctestdominputmethodsdocument.h"
#include "bctestdominputmethodsappui.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTestDomInputMethodsDocument* CBCTestDomInputMethodsDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomInputMethodsDocument* CBCTestDomInputMethodsDocument::NewL( CEikApplication& aApp )
    {
    CBCTestDomInputMethodsDocument* self = new( ELeave ) CBCTestDomInputMethodsDocument( aApp );
    return self;
    }

// ----------------------------------------------------------------------------
// CBCTestDomInputMethodsDocument::~CBCTestDomInputMethodsDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTestDomInputMethodsDocument::~CBCTestDomInputMethodsDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTestDomInputMethodsDocument::CBCTestDomInputMethodsDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTestDomInputMethodsDocument::CBCTestDomInputMethodsDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTestDomInputMethodsDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTestDomInputMethodsDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTestDomInputMethodsAppUi;
    }

// End of File
