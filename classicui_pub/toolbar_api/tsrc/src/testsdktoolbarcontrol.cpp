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
* Description:  test AknToolbar.h,akntoolbarextension.h and AknToolbarObserver.h
*
*/


// [INCLUDE FILES]
#include "testsdktoolbarcontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestToolbarControl::NewL
// -----------------------------------------------------------------------------
//
CTestToolbarControl* CTestToolbarControl::NewL()
    {
    CTestToolbarControl* self = new (ELeave) CTestToolbarControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::~CTestToolbarControl
// -----------------------------------------------------------------------------
//
CTestToolbarControl::~CTestToolbarControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::CTestToolbarControl
// -----------------------------------------------------------------------------
//
CTestToolbarControl::CTestToolbarControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestToolbarControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CTestToolbarControl::OfferToolbarEventL
// ---------------------------------------------------------------------------
//
void CTestToolbarControl::OfferToolbarEventL( TInt /*aCommand*/ )
    {
    }

// ---------------------------------------------------------------------------
// CTestToolbarControl::DoDynInitToolbarL
// ---------------------------------------------------------------------------
//
void CTestToolbarControl::DoDynInitToolbarL( TInt aResourceId, CAknToolbar* aToolbar )
    {
    DynInitToolbarL( aResourceId, aToolbar );
    }

// ---------------------------------------------------------------------------
// CTestToolbarControl::DoMAknToolbarObserver_Reserved_1
// ---------------------------------------------------------------------------
//
TInt CTestToolbarControl::DoMAknToolbarObserver_Reserved_1()
    {
    return MAknToolbarObserver_Reserved_1();
    }

// ---------------------------------------------------------------------------
// CTestToolbarControl::DoMAknToolbarObserver_Reserved_2
// ---------------------------------------------------------------------------
//
TInt CTestToolbarControl::DoMAknToolbarObserver_Reserved_2()
    {
    return MAknToolbarObserver_Reserved_2();
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestToolbarControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::Draw
// -----------------------------------------------------------------------------
//
void CTestToolbarControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestToolbarControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestToolbarControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestToolbarControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestToolbarControl::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestToolbarControl::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestToolbarControl::DoDeactivateGc()
    {
    DeactivateGc();
    }

