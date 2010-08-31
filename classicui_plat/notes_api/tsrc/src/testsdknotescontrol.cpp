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
* Description:  Test AknNoteWrappers.h
 *
*/


// [INCLUDE FILES]

#include <eikenv.h>
#include <aknappui.h> 

#include "testsdknotescontrol.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestNotesControl::NewL
// -----------------------------------------------------------------------------
//
CTestNotesControl* CTestNotesControl::NewL()
    {
    CTestNotesControl* self = new (ELeave) CTestNotesControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestNotesControl::~CTestNotesControl
// -----------------------------------------------------------------------------
//
CTestNotesControl::~CTestNotesControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestNotesControl::CTestNotesControl
// -----------------------------------------------------------------------------
//
CTestNotesControl::CTestNotesControl(){};

// -----------------------------------------------------------------------------
// CTestNotesControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestNotesControl::ConstructL()
    {
    CreateWindowL();
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();

    }

// -----------------------------------------------------------------------------
// CTestNotesControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestNotesControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestNotesControl::Draw
// -----------------------------------------------------------------------------
//
void CTestNotesControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestNotesControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestNotesControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestNotesControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestNotesControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestNotesControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestNotesControl::SizeChanged()
    {
    }

// End of file
