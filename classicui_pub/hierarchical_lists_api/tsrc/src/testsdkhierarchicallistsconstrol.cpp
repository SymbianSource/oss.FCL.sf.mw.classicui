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
* Description:  test aknsinglecolumnstyletreelist.h
*
*/


// [INCLUDE FILES]
#include <eikenv.h>
#include <aknappui.h>

#include "testsdkhierarchicallistscontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestControl::NewL
// -----------------------------------------------------------------------------
//
CTestControl* CTestControl::NewL()
    {
    CTestControl* self = new (ELeave) CTestControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestControl::~CTestControl
// -----------------------------------------------------------------------------
//
CTestControl::~CTestControl(){}

// -----------------------------------------------------------------------------
// CTestControl::CTestControl
// -----------------------------------------------------------------------------
//
CTestControl::CTestControl(){};

// -----------------------------------------------------------------------------
// CTestControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestControl::ConstructL()
    {
    CreateWindowL();
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestControl::Draw
// -----------------------------------------------------------------------------
//
void CTestControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestControl::SizeChanged()
    {
    }
