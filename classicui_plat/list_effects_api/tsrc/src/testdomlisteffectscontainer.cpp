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
* Description:  test aknlistloadertfx.h
*
*/


#include "testdomlisteffectscontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::CTestDOMListsEffectsContainer
// -----------------------------------------------------------------------------
//
CTestDOMListsEffectsContainer::CTestDOMListsEffectsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::~CTestDOMListsEffectsContainer
// -----------------------------------------------------------------------------
//
CTestDOMListsEffectsContainer::~CTestDOMListsEffectsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::NewL
// -----------------------------------------------------------------------------
//
CTestDOMListsEffectsContainer* CTestDOMListsEffectsContainer::NewL()
    {
    CTestDOMListsEffectsContainer* self = new ( ELeave ) CTestDOMListsEffectsContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDOMListsEffectsContainer::ConstructL()
    {
    CreateWindowL();
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestDOMListsEffectsContainer::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( Rect() );
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDOMListsEffectsContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDOMListsEffectsContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestDOMListsEffectsContainer::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestDOMListsEffectsContainer::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestDOMListsEffectsContainer::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestDOMListsEffectsContainer::DoDeactivateGc()
    {
    DeactivateGc();
    }

