/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknchoicelist.h
*
*/


//  INCLUDES
#include <eikenv.h>
#include <aknappui.h> 

#include "testsdkchoicelistcontrol.h"

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::NewL
// -----------------------------------------------------------------------------
CTestSDKChoiceListControl* CTestSDKChoiceListControl::NewLC()
    {
    CTestSDKChoiceListControl* self = new (ELeave) CTestSDKChoiceListControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::~CTestSDKChoiceListControl
// -----------------------------------------------------------------------------
CTestSDKChoiceListControl::~CTestSDKChoiceListControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::CTestSDKChoiceListControl
// -----------------------------------------------------------------------------
CTestSDKChoiceListControl::CTestSDKChoiceListControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::ConstructL
// -----------------------------------------------------------------------------
void CTestSDKChoiceListControl::ConstructL()
    {
    CreateWindowL();
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::OfferKeyEventL
// -----------------------------------------------------------------------------
TKeyResponse CTestSDKChoiceListControl::OfferKeyEventL( const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/ )
    {
    return EKeyWasConsumed;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::HandlePointerEventL
// -----------------------------------------------------------------------------
void CTestSDKChoiceListControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    CCoeControl::HandlePointerEventL( aPointerEvent );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::Draw
// -----------------------------------------------------------------------------
void CTestSDKChoiceListControl::Draw( const TRect& /*aRect*/ ) const
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::CountComponentControls
// -----------------------------------------------------------------------------
TInt CTestSDKChoiceListControl::CountComponentControls() const
    {
    return 0;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::ComponentControl
// -----------------------------------------------------------------------------
CCoeControl* CTestSDKChoiceListControl::ComponentControl( TInt aIndex ) const
    {
    switch(aIndex)
        {
        default:
            return NULL;
        }
    
    }

// -----------------------------------------------------------------------------
// CTestSDKChoiceListControl::SizeChanged
// -----------------------------------------------------------------------------
void CTestSDKChoiceListControl::SizeChanged()
    {
    
    }
