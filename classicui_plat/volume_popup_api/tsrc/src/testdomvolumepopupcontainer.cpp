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
* Description:  volume_popup_api
 *
*/


#include "testdomvolumepopupcontainer.h"

// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CVolumePopupContainer::CVolumePopupContainer()
    {

    }
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CVolumePopupContainer::~CVolumePopupContainer()
    {

    ResetControl();

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CVolumePopupContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();

    }

// ----------------------------------------------------------------------------
// CVolumePopupContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CVolumePopupContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor( KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }
// ---------------------------------------------------------------------------
// CVolumePopupContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CVolumePopupContainer::CountComponentControls() const
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
// CVolumePopupContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVolumePopupContainer::ComponentControl(TInt) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CVolumePopupContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CVolumePopupContainer::SetControlL(CCoeControl* aControl)
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
// CVolumePopupContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CVolumePopupContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CVolumePopupContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CVolumePopupContainer::GetCoeEnv()
    {
    return iCoeEnv;
    }
