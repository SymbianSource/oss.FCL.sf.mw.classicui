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
* Description:  volume_control_api
 *
*/


#include "testsdkvolumecontainer.h"
#include "testsdkvolumeview.h"
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CVolumeControlContainer::CVolumeControlContainer()
    {

    }
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CVolumeControlContainer::~CVolumeControlContainer()
    {

    ResetControl();

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CVolumeControlContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();

    }

// ----------------------------------------------------------------------------
// CVolumeControlContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CVolumeControlContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor( KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }
// ---------------------------------------------------------------------------
// CVolumeControlContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CVolumeControlContainer::CountComponentControls() const
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
// CVolumeControlContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVolumeControlContainer::ComponentControl(TInt) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CVolumeControlContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CVolumeControlContainer::SetControlL(CCoeControl* aControl)
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
// CVolumeControlContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CVolumeControlContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }

// ---------------------------------------------------------------------------
// CVolumeControlContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CVolumeControlContainer::GetCoeEnv()
    {
    return iCoeEnv;
    }
