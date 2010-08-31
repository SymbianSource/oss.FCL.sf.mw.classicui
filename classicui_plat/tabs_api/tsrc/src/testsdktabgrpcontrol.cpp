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
* Description:  test akntabgrp.h
*
*/


//INCLUDE FILES
#include "testsdktabgrpcontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestTabsControl::NewL
// -----------------------------------------------------------------------------
//
CTestTabsControl* CTestTabsControl::NewL()
    {
    CTestTabsControl* self = new (ELeave) CTestTabsControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::~CTestTabsControl
// -----------------------------------------------------------------------------
//
CTestTabsControl::~CTestTabsControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::CTestTabsControl
// -----------------------------------------------------------------------------
//
CTestTabsControl::CTestTabsControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestTabsControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestTabsControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::Draw
// -----------------------------------------------------------------------------
//
void CTestTabsControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestTabsControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestTabsControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestTabsControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestTabsControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestTabsControl::SizeChanged()
    {
    }
// -----------------------------------------------------------------------------
// CTestTabsControl::TabChangedL
// -----------------------------------------------------------------------------
//
void CTestTabsControl::TabChangedL( TInt /*aIndex*/ )
    {
    }
