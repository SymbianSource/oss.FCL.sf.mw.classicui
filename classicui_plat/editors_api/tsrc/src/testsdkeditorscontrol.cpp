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
* Description:  Test EIKEDWIN.h
 *
*/


// [INCLUDE FILES]

#include <eikenv.h>
#include <aknappui.h> 

#include "testsdkeditorscontrol.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestControl::NewL
// -----------------------------------------------------------------------------
//
CTestEditorsControl* CTestEditorsControl::NewL()
    {
    CTestEditorsControl* self = new (ELeave) CTestEditorsControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::~CTestEditorsControl
// -----------------------------------------------------------------------------
//
CTestEditorsControl::~CTestEditorsControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::CTestEditorsControl
// -----------------------------------------------------------------------------
//
CTestEditorsControl::CTestEditorsControl(){};

// -----------------------------------------------------------------------------
// CTestEditorsControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestEditorsControl::ConstructL()
    {
    CreateWindowL();
    SetRect(iEikonEnv->EikAppUi()->ClientRect());
    ActivateL();

    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestEditorsControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::Draw
// -----------------------------------------------------------------------------
//
void CTestEditorsControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestEditorsControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestEditorsControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestEditorsControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestEditorsControl::SizeChanged()
    {
    }

// End of file
