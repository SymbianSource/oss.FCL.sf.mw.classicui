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
* Description:  misc_controls_api
*
*/

#include "testsdkmisccontrolcontainer.h"
// ---------------------------------------------------------------------------
// C++ default Constructor
// ---------------------------------------------------------------------------
//
CMiscControlsContainer::CMiscControlsContainer()
    {

    }
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMiscControlsContainer::~CMiscControlsContainer()
    {

    ResetControl();

    }

// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CMiscControlsContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect(aRect);
    ActivateL();

    }

// ----------------------------------------------------------------------------
// CMiscControlsContainer::Draw
// Fills the window's rectangle.
// ----------------------------------------------------------------------------
//
void CMiscControlsContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor( KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }
// ---------------------------------------------------------------------------
// CMiscControlsContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CMiscControlsContainer::CountComponentControls() const
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
// CMiscControlsContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CMiscControlsContainer::ComponentControl(TInt) const
    {
    return iControl;
    }

// ---------------------------------------------------------------------------
// CMiscControlsContainer::SetControlL
// ---------------------------------------------------------------------------
//
void CMiscControlsContainer::SetControlL(CCoeControl* aControl)
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
// CMiscControlsContainer::ResetControl
// ---------------------------------------------------------------------------
//
void CMiscControlsContainer::ResetControl()
    {
    delete iControl;
    iControl = NULL;
    }
            

// ---------------------------------------------------------------------------
// CMiscControlsContainer::GetCoeEnv
// ---------------------------------------------------------------------------
//
CCoeEnv* CMiscControlsContainer::GetCoeEnv()
    {
    return iCoeEnv;
    }
// -----------------------------------------------------------------------------
// CMiscControlsContainer::ActivateGc
// -----------------------------------------------------------------------------
//
void CMiscControlsContainer::ActivateGc() const
    {
    CCoeControl::ActivateGc();
    }
// -----------------------------------------------------------------------------
// CMiscControlsContainer::DeactivateGc
// -----------------------------------------------------------------------------
//
void CMiscControlsContainer::DeactivateGc() const
    {
    CCoeControl::DeactivateGc();
    }
