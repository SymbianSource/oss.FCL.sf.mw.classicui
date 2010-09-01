/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknscbut.h, eiksbfrm.h, eikscbut.h and eikscrlb.h
*
*/

#include <eiksbfrm.h>

#include "testsdkscrollercontrol.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestScrollerControl::NewL
// -----------------------------------------------------------------------------
//
CTestScrollerControl* CTestScrollerControl::NewL()
    {
    CTestScrollerControl* self = new (ELeave) CTestScrollerControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::~CTestScrollerControl
// -----------------------------------------------------------------------------
//
CTestScrollerControl::~CTestScrollerControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::CTestScrollerControl
// -----------------------------------------------------------------------------
//
CTestScrollerControl::CTestScrollerControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestScrollerControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestScrollerControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::Draw
// -----------------------------------------------------------------------------
//
void CTestScrollerControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestScrollerControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestScrollerControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestScrollerControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestScrollerControl::SizeChanged()
    {
    }

//------------------------------------------------------------------------------
// CTestSDKScroller::HandleScrollEventL
//------------------------------------------------------------------------------
void CTestScrollerControl::HandleScrollEventL( CEikScrollBar* /*aScrollBar*/,
        TEikScrollEvent /*aEventType*/ )
    {
    }


