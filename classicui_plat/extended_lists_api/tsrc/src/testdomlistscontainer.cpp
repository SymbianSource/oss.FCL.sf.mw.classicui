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
* Description:  test aknjavalists.h, aknshortcuts.h and eikslbd.h
*
*/


// [INCLUDE FILES]
#include "testdomlistscontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestListsContainer::NewL
// -----------------------------------------------------------------------------
//
CTestListsContainer* CTestListsContainer::NewL()
    {
    CTestListsContainer* self = new (ELeave) CTestListsContainer;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::~CTestListsContainer
// -----------------------------------------------------------------------------
//
CTestListsContainer::~CTestListsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::CTestListsContainer
// -----------------------------------------------------------------------------
//
CTestListsContainer::CTestListsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestListsContainer::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestListsContainer::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestListsContainer::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestListsContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestListsContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestListsContainer::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestListsContainer::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestListsContainer::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestListsContainer::DoDeactivateGc()
    {
    DeactivateGc();
    }
