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
* Description:         Avkon eikbctrl test application
*
*/









#include "BCTesteikbctrlDocument.h"
#include "BCTesteikbctrlAppUi.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CBCTesteikbctrlDocument* CBCTesteikbctrlDocument::NewL( CEikApplication& )
// Symbian OS two-phased constructor.
// ----------------------------------------------------------------------------
//
CBCTesteikbctrlDocument* CBCTesteikbctrlDocument::NewL( CEikApplication& aApp )
    {
    CBCTesteikbctrlDocument* self = new( ELeave ) CBCTesteikbctrlDocument( aApp );
    return self;
    }  
 
// ----------------------------------------------------------------------------
// CBCTesteikbctrlDocument::~CBCTesteikbctrlDocument()
// Destructor.
// ----------------------------------------------------------------------------
//
CBCTesteikbctrlDocument::~CBCTesteikbctrlDocument()
    {
    }

// ----------------------------------------------------------------------------
// CBCTesteikbctrlDocument::CBCTesteikbctrlDocument( CEikApplication& )
// Overload constructor.
// ----------------------------------------------------------------------------
//
CBCTesteikbctrlDocument::CBCTesteikbctrlDocument( CEikApplication& aApp )
    :   CEikDocument( aApp )
    {
    }

// ----------------------------------------------------------------------------
// CEikAppUi* CBCTesteikbctrlDocument::CreateAppUiL()
// Constructs CBCTestVolumeAppUi.
// ----------------------------------------------------------------------------
//
CEikAppUi* CBCTesteikbctrlDocument::CreateAppUiL()
    {
    return new( ELeave ) CBCTesteikbctrlAppUi;
    }

// End of File
