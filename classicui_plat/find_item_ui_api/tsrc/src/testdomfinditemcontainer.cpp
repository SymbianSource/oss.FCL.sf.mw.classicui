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
* Description:  test finditemdialog.h and finditemmenu.h
*
*/


#include "testdomfinditemcontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::CTestDOMFindItemContainer
// -----------------------------------------------------------------------------
//
CTestDOMFindItemContainer::CTestDOMFindItemContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::~CTestDOMFindItemContainer
// -----------------------------------------------------------------------------
//
CTestDOMFindItemContainer::~CTestDOMFindItemContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::NewL
// -----------------------------------------------------------------------------
//
CTestDOMFindItemContainer* CTestDOMFindItemContainer::NewL()
    {
    CTestDOMFindItemContainer* self = new ( ELeave ) CTestDOMFindItemContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDOMFindItemContainer::ConstructL()
    {
    CreateWindowL();
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestDOMFindItemContainer::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( Rect() );
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDOMFindItemContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDOMFindItemContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestDOMFindItemContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestDOMFindItemContainer::SizeChanged()
    {
    }

