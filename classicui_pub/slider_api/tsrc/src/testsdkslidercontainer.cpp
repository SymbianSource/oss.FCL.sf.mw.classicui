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
* Description:  slider_api
 *
*/

#include "testsdkslidercontainer.h"
#include "testsdksliderview.h"
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CSliderContainer::CSliderContainer()
    {

    }
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CSliderContainer::~CSliderContainer()
    {

    ResetControl();

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CSliderContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();

    }

// ----------------------------------------------------------------------------
// CSliderContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CSliderContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor( KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }
// ---------------------------------------------------------------------------
// CSliderContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CSliderContainer::CountComponentControls() const
    {
    if (iControl)
        {
        return 1;
        }
    else
        {
        return 0;
        }
    }

// ---------------------------------------------------------------------------
// CSliderContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CSliderContainer::ComponentControl(TInt) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CSliderContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CSliderContainer::SetControlL(CCoeControl* aControl)
    {
    iControl = aControl;
    if (iControl)
        {
        // You can change the position and size
        iControl->SetExtent(Rect().iTl, Rect().Size() );
        iControl->ActivateL();
        DrawNow();
        }
    }

// ---------------------------------------------------------------------------
// CSliderContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CSliderContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CSliderContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CSliderContainer::GetCoeEnv()
    {
    return iCoeEnv;
    }
