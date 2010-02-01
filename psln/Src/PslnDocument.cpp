/*
* Copyright (c) 2002-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Document class for psln.
*
*/


#include "PslnDocument.h"
#include "PslnUi.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian constructor.
// ---------------------------------------------------------------------------
//
CPslnDocument* CPslnDocument::NewL( CEikApplication& aApp )
    {
    CPslnDocument* self = new(ELeave) CPslnDocument( aApp );
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CPslnDocument::~CPslnDocument()
    {
    }

// ---------------------------------------------------------------------------
// C++ constructor.
// ---------------------------------------------------------------------------
//
CPslnDocument::CPslnDocument( CEikApplication& aApp ) : CAknDocument( aApp ) 
    {
    }

// ---------------------------------------------------------------------------
// From CEikDocument.
// Create an CPslnAppUi instance and return it.
// ---------------------------------------------------------------------------
//
CEikAppUi* CPslnDocument::CreateAppUiL()
    {
    return new (ELeave) CPslnUi;
    }

//  End of File  
