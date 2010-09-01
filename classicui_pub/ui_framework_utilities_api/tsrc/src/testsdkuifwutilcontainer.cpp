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
#include "testsdkuifwutilcontainer.h"

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::CTestUiFwUtilContainer
// -----------------------------------------------------------------------------
//
CTestUiFwUtilContainer::CTestUiFwUtilContainer() : iControl(NULL)
{}

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::~CTestUiFwUtilContainer
// -----------------------------------------------------------------------------
//
CTestUiFwUtilContainer::~CTestUiFwUtilContainer()
    {
    CCoeEnv::Static()->AppUi()->RemoveFromStack( this );
    iControl = NULL;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::NewL
// -----------------------------------------------------------------------------
//
CTestUiFwUtilContainer* CTestUiFwUtilContainer::NewL( TRect& aRect )
    {
    CTestUiFwUtilContainer* self = new ( ELeave ) CTestUiFwUtilContainer;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CCoeEnv::Static()->AppUi()->AddToStackL( self );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::CTestUiFwUtilContainer
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilContainer::ConstructL( TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );
    iRect = aRect;
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::SetComponentControlL
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilContainer::SetComponentControlL( CCoeControl* aControl )
    {
    iControl = aControl;
    iControl->ActivateL();
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CTestUiFwUtilContainer::CountComponentControls() const
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
// CTestUiFwUtilContainer::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CTestUiFwUtilContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iControl;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::Draw
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(KRgbBlue);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.Clear();
    gc.DrawRect(aRect);
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::ControlRect
// -----------------------------------------------------------------------------
//
TRect CTestUiFwUtilContainer::ControlRect()
    {
    return iRect;
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::ActiveControlGc
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilContainer::ActiveControlGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CTestUiFwUtilContainer::DeActiveControlGc
// -----------------------------------------------------------------------------
//
void CTestUiFwUtilContainer::DeActiveControlGc()
    {
    DeactivateGc();
    }

// End of file


