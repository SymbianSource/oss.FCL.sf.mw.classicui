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
* Description:  test AknWsEventObserver.h
*
*/



// INCLUDE FILES
#include <eikenv.h>
#include <aknappui.h>

#include "testsdkeventobserver.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKEventObserver::NewL
// -----------------------------------------------------------------------------
//
CTestSDKEventObserver* CTestSDKEventObserver::NewL()
    {
    CTestSDKEventObserver* self = new (ELeave) CTestSDKEventObserver;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::~CTestSDKEventObserver
// -----------------------------------------------------------------------------
//
CTestSDKEventObserver::~CTestSDKEventObserver()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::CTestSDKEventObserver
// -----------------------------------------------------------------------------
//
CTestSDKEventObserver::CTestSDKEventObserver(){};

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKEventObserver::ConstructL()
    {
    CreateWindowL();
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();

    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKEventObserver::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::Draw
// -----------------------------------------------------------------------------
//
void CTestSDKEventObserver::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKEventObserver::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKEventObserver::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestSDKEventObserver::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKEventObserver::HandleWsEventL
// -----------------------------------------------------------------------------
void CTestSDKEventObserver::HandleWsEventL( const TWsEvent& /*aEvent*/, CCoeControl* /*aDestination*/ )
    {
    
    }


