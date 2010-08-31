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
* Description:         Invoke popup field's protected APIs.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <aknform.h>
#include <bctestpopups.rsg> 

#include "bctestsubpopupfieldtext.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopupFieldText* CBCTestSubPopupFieldText::NewL()
    {
    CBCTestSubPopupFieldText* self = new( ELeave ) CBCTestSubPopupFieldText();
    CleanupStack::PushL( self );
    self->ConstructL();   
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopupFieldText::CBCTestSubPopupFieldText():CAknPopupField() 
    {
    } 

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopupFieldText::~CBCTestSubPopupFieldText()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSubPopupFieldText::ConstructL()
    {
    CAknPopupField::ConstructL();
    }
