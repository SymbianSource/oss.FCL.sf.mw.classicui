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
* Description:  test ui framework utilities api
*
*/


// INCLUDE FILES
#include <coeaui.h>

#include "testdomstylusactivepopupcontainer.h"

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::CTestStyleActivePopUpContainer
// -----------------------------------------------------------------------------
//
CTestStyleActivePopUpContainer::CTestStyleActivePopUpContainer() : iControl(NULL)
{}

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::~CTestStyleActivePopUpContainer
// -----------------------------------------------------------------------------
//
CTestStyleActivePopUpContainer::~CTestStyleActivePopUpContainer()
    {
    CCoeEnv::Static()->AppUi()->RemoveFromStack( this );
    iControl = NULL;
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::NewL
// -----------------------------------------------------------------------------
//
CTestStyleActivePopUpContainer* CTestStyleActivePopUpContainer::NewL( TRect& aRect )
    {
    CTestStyleActivePopUpContainer* self = new ( ELeave ) CTestStyleActivePopUpContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CCoeEnv::Static()->AppUi()->AddToStackL( self );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::CTestStyleActivePopUpContainer
// -----------------------------------------------------------------------------
//
void CTestStyleActivePopUpContainer::ConstructL( TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    iRect = aRect;
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::SetComponentControlL
// -----------------------------------------------------------------------------
//
void CTestStyleActivePopUpContainer::SetComponentControlL( CCoeControl* aControl )
    {
    iControl = aControl;
    iControl->SetExtent( Rect().iTl, Rect().Size() );
    iControl->ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestStyleActivePopUpContainer::CountComponentControls() const
    {
    if ( iControl )
        {
        return 1;
        }
    else
        {
        return 0;
        }
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestStyleActivePopUpContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iControl;
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestStyleActivePopUpContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbBlue);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.Clear();
    gc.DrawRect(aRect);
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::ControlRect
// -----------------------------------------------------------------------------
//
TRect CTestStyleActivePopUpContainer::ControlRect()
    {
    return iRect;
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::ActiveControlGc
// -----------------------------------------------------------------------------
//
void CTestStyleActivePopUpContainer::ActiveControlGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestStyleActivePopUpContainer::DeActiveControlGc
// -----------------------------------------------------------------------------
//
void CTestStyleActivePopUpContainer::DeActiveControlGc()
    {
    DeactivateGc();
    }

// End of file


