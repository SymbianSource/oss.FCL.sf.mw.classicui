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
* Description:  Test AknButton.h
 *
*/


/*
 *  [INCLUDE FILES]
 */
#include <eikenv.h>
#include <aknappui.h> 
#include <testsdksettingpages.rsg>
#include <aknsettingpage.h>

#include "testparentcontrol.h"
#include "testaknpasswordsettingpageprotected.h"
#include "testsdksettingpagesstdinclude.h"


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestParentControl::NewL
// -----------------------------------------------------------------------------
//
CTestParentControl* CTestParentControl::NewL()
    {
    CTestParentControl* self = new (ELeave) CTestParentControl;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::~CTestParentControl
// -----------------------------------------------------------------------------
//
CTestParentControl::~CTestParentControl()
    {

    }

// -----------------------------------------------------------------------------
// CTestParentControl::CTestParentControl
// -----------------------------------------------------------------------------
//
CTestParentControl::CTestParentControl(){};

// -----------------------------------------------------------------------------
// CTestParentControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestParentControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestParentControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/ )
    {
    return EKeyWasConsumed;

    }

// -----------------------------------------------------------------------------
// CTestParentControl::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CTestParentControl::HandlePointerEventL(const TPointerEvent& /*aPointerEvent*/ )
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::Draw
// -----------------------------------------------------------------------------
//
void CTestParentControl::Draw(const TRect& /*aRect*/ ) const
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestParentControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestParentControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestParentControl::ComponentControl(TInt aIndex) const
    {
    switch(aIndex)
        {
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CTestParentControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestParentControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestParentControl::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestParentControl::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestParentControl::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestParentControl::DoDeactivateGc()
    {
    DeactivateGc();
    }
/*
 * End file
 */


