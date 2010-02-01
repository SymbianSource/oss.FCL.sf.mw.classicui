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
* Description:  text aknmarqueecontrol.h
*
*/


// [INCLUDE FILES]
#include "testdomtextscrollercontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::NewL
// -----------------------------------------------------------------------------
//
CTestTextScrollerContainer* CTestTextScrollerContainer::NewL()
    {
    CTestTextScrollerContainer* self = new (ELeave) CTestTextScrollerContainer;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::~CTestTextScrollerContainer
// -----------------------------------------------------------------------------
//
CTestTextScrollerContainer::~CTestTextScrollerContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::CTestTextScrollerContainer
// -----------------------------------------------------------------------------
//
CTestTextScrollerContainer::CTestTextScrollerContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestTextScrollerContainer::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestTextScrollerContainer::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestTextScrollerContainer::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestTextScrollerContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestTextScrollerContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestTextScrollerContainer::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestTextScrollerContainer::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestTextScrollerContainer::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestTextScrollerContainer::DoDeactivateGc()
    {
    DeactivateGc();
    }
