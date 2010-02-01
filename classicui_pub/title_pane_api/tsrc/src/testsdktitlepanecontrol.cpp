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
* Description:  test akntitle.h
*
*/


//INCLUDE FILES
#include "testsdktitlepanecontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::NewL
// -----------------------------------------------------------------------------
//
CTestTitlePaneControl* CTestTitlePaneControl::NewL()
    {
    CTestTitlePaneControl* self = new (ELeave) CTestTitlePaneControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::~CTestTitlePaneControl
// -----------------------------------------------------------------------------
//
CTestTitlePaneControl::~CTestTitlePaneControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::CTestTitlePaneControl
// -----------------------------------------------------------------------------
//
CTestTitlePaneControl::CTestTitlePaneControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::HandleTitlePaneEventL
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::HandleTitlePaneEventL( TInt /*aEventID*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestTitlePaneControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::Draw
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestTitlePaneControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestTitlePaneControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestTitlePaneControl::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestTitlePaneControl::DoDeactivateGc()
    {
    DeactivateGc();
    }
