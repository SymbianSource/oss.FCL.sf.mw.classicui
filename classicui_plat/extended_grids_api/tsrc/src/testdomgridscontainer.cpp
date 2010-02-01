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
* Description:  test aknappgrid.h
*
*/


#include "testdomgridscontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::CTestDOMGridsContainer
// -----------------------------------------------------------------------------
//
CTestDOMGridsContainer::CTestDOMGridsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::~CTestDOMGridsContainer
// -----------------------------------------------------------------------------
//
CTestDOMGridsContainer::~CTestDOMGridsContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::NewL
// -----------------------------------------------------------------------------
//
CTestDOMGridsContainer* CTestDOMGridsContainer::NewL()
    {
    CTestDOMGridsContainer* self = new ( ELeave ) CTestDOMGridsContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDOMGridsContainer::ConstructL()
    {
    CreateWindowL();
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestDOMGridsContainer::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( Rect() );
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDOMGridsContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDOMGridsContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestDOMGridsContainer::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::DoActivateGc
// -----------------------------------------------------------------------------
//
void CTestDOMGridsContainer::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestDOMGridsContainer::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CTestDOMGridsContainer::DoDeactivateGc()
    {
    DeactivateGc();
    }

