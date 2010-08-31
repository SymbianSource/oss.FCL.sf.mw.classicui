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
* Description:  Test Aknsedsts.H
*
*/


//  INCLUDES
#include <eikenv.h>
#include <aknappui.h>

#include "testsdkeditorsedstateobserver.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::NewL
// -----------------------------------------------------------------------------
//
CTestSDKEditorsEdStateObserver* CTestSDKEditorsEdStateObserver::NewL()
    {
    CTestSDKEditorsEdStateObserver* self = new (ELeave) CTestSDKEditorsEdStateObserver;
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::~CTestSDKEditorsEdStateObserver
// -----------------------------------------------------------------------------
//
CTestSDKEditorsEdStateObserver::~CTestSDKEditorsEdStateObserver(){}

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::CTestControl
// -----------------------------------------------------------------------------
//
CTestSDKEditorsEdStateObserver::CTestSDKEditorsEdStateObserver(){};

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::ConstructL
// -----------------------------------------------------------------------------
//
void CTestSDKEditorsEdStateObserver::ConstructL()
    {
    CreateWindowL();
    SetRect(iEikonEnv->EikAppUi()->ClientRect());
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestSDKEditorsEdStateObserver::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::Draw
// -----------------------------------------------------------------------------
//
void CTestSDKEditorsEdStateObserver::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestSDKEditorsEdStateObserver::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestSDKEditorsEdStateObserver::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestSDKEditorsEdStateObserver::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::HandleAknEdwinStateEventL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdStateObserver::HandleAknEdwinStateEventL ( 
                                     CAknEdwinState */*aAknEdwinState*/, 
                                     EAknEdwinStateEvent /*aEventType*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::SetEmphasis
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdStateObserver::SetEmphasis( CCoeControl */*aMenuControl*/, TBool /*aEmphasis*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::ProcessCommandL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdStateObserver::ProcessCommandL( TInt /*aCommandId*/ )
    {
    
    }

// -----------------------------------------------------------------------------
// CTestSDKEditorsEdStateObserver::HandleCursorOverParserL
// -----------------------------------------------------------------------------
void CTestSDKEditorsEdStateObserver::HandleCursorOverParserL( const TDesC& /*aDoItText*/ )
    {
    
    }
