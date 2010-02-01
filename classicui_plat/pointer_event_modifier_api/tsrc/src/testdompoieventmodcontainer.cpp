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
* Description:  test aknpointereventmodifier.h
*
*/


#include "testdompoieventmodcontainer.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::CTestDOMPoiEventModContainer
// -----------------------------------------------------------------------------
//
CTestDOMPoiEventModContainer::CTestDOMPoiEventModContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::~CTestDOMPoiEventModContainer
// -----------------------------------------------------------------------------
//
CTestDOMPoiEventModContainer::~CTestDOMPoiEventModContainer()
    {
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::NewL
// -----------------------------------------------------------------------------
//
CTestDOMPoiEventModContainer* CTestDOMPoiEventModContainer::NewL()
    {
    CTestDOMPoiEventModContainer* self = new ( ELeave ) CTestDOMPoiEventModContainer;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::ConstructL
// -----------------------------------------------------------------------------
//
void CTestDOMPoiEventModContainer::ConstructL()
    {
    CreateWindowL();
    SetRect( Rect() );
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestDOMPoiEventModContainer::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbGray );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );  
    gc.DrawRect( Rect() );
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestDOMPoiEventModContainer::CountComponentControls() const
    {
    return 0;
    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestDOMPoiEventModContainer::ComponentControl(TInt /*aIndex*/) const
    {
    return NULL;

    }

// -----------------------------------------------------------------------------
// CTestDOMPoiEventModContainer::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestDOMPoiEventModContainer::SizeChanged()
    {
    }

