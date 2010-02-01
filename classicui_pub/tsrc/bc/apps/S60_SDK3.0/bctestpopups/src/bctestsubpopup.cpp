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
* Description:         Invoke popup list's protected APIs.
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <bctestpopups.rsg> 

#include "bctestsubpopup.h"
#include "bctestpopups.hrh"
#include "autotestcommands.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopup* CBCTestSubPopup::NewL(  
        CEikListBox *aListBox, TInt aCbaResource, 
        AknPopupLayouts::TAknPopupLayouts aType )
    {
    CBCTestSubPopup* self = new( ELeave ) CBCTestSubPopup();
    CleanupStack::PushL( self );  
    self->ConstructL( aListBox, aCbaResource, aType );
    CleanupStack::Pop( self );
    return self; 
    }

// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopup::CBCTestSubPopup()
    {
    } 

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestSubPopup::~CBCTestSubPopup()
    {
    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestSubPopup::ConstructL( 
        CEikListBox *aListBox, TInt aCbaResource, 
        AknPopupLayouts::TAknPopupLayouts aType )
    {
    CAknPopupList::ConstructL( aListBox, aCbaResource, aType );
    }

    





    
   

    
