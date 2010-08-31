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
* Description:  test aknstyluspopupmenu.h
*
*/



// INCLUDE FILES
#include <eikenv.h>
#include <aknappui.h>

#include "testsdkmenuobserver.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::NewL
// -----------------------------------------------------------------------------
//
CTestSDKMenuObserver* CTestSDKMenuObserver::NewL()
    {
    CTestSDKMenuObserver* self = new (ELeave) CTestSDKMenuObserver;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::~CTestSDKMenuObserver
// -----------------------------------------------------------------------------
//
CTestSDKMenuObserver::~CTestSDKMenuObserver()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::CTestSDKMenuObserver
// -----------------------------------------------------------------------------
//
CTestSDKMenuObserver::CTestSDKMenuObserver(){};

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKMenuObserver::ConstructL()
    {
    CreateWindowL();
    SetRect(CEikonEnv::Static()->EikAppUi()->ClientRect());
    ActivateL();

    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKMenuObserver::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::Draw
// -----------------------------------------------------------------------------
//
void CTestSDKMenuObserver::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKMenuObserver::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKMenuObserver::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestSDKMenuObserver::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestSDKMenuObserver::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
//CTestSDKMenuObserver::SetEmphasis
// -----------------------------------------------------------------------------
void CTestSDKMenuObserver::SetEmphasis( CCoeControl* /*aMenuControl*/, TBool /*aEmphasis*/ )
    {
    
    }

// -----------------------------------------------------------------------------
//CTestSDKMenuObserver::HandleServerAppExit
// -----------------------------------------------------------------------------
void CTestSDKMenuObserver::ProcessCommandL( TInt /*aCommandId*/ )
    {
    
    }

