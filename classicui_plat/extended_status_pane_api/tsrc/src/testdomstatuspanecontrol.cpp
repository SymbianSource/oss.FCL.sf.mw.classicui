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
* Description:  test aknsgcc.h, aknstatuspaneutils.h and aknsyncdraw.h
*
*/



#include <aknsgcc.h>

#include "testdomstatuspanecontrol.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::NewL
// -----------------------------------------------------------------------------
//
CTestStatusPaneControl* CTestStatusPaneControl::NewL()
    {
    CTestStatusPaneControl* self = new ( ELeave ) CTestStatusPaneControl;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::~CTestStatusPaneControl
// -----------------------------------------------------------------------------
//
CTestStatusPaneControl::~CTestStatusPaneControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::CTestStatusPaneControl
// -----------------------------------------------------------------------------
//
CTestStatusPaneControl::CTestStatusPaneControl()
    {
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::ConstructL
// -----------------------------------------------------------------------------
//
void CTestStatusPaneControl::ConstructL()
    {
    CreateWindowL();
    //add controls
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestStatusPaneControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::Draw
// -----------------------------------------------------------------------------
//
void CTestStatusPaneControl::Draw(const TRect& /*aRect*/) const
    {
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestStatusPaneControl::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestStatusPaneControl::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestStatusPaneControl::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::BlockServerStatusPaneRedrawsL
// -----------------------------------------------------------------------------
//
void CTestStatusPaneControl::BlockServerStatusPaneRedrawsL()
    {
    }

// -----------------------------------------------------------------------------
// CTestStatusPaneControl::RedrawServerStatusPane
// -----------------------------------------------------------------------------
//
void CTestStatusPaneControl::RedrawServerStatusPane()
    {
    }

// -----------------------------------------------------------------------------
// CAknSgcImplExt::MoveApp
// -----------------------------------------------------------------------------
//
void CAknSgcImplExt::MoveApp( TInt /*aAppWindowGroupId*/,
        TSgcMoveAppToWhere /*aWhere*/ )
    {
    }

