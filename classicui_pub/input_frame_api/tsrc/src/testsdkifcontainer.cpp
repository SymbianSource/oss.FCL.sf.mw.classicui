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
* Description:  input_frame_api
 *
*/

#include "testsdkifcontainer.h"

    // ---------------------------------------------------------------------------
    // C++ default Constructor
    // ---------------------------------------------------------------------------
    //
    CInputFrameContainer::CInputFrameContainer()
    {

    }
    // ---------------------------------------------------------------------------
    // Destructor
    // ---------------------------------------------------------------------------
    //
    CInputFrameContainer::~CInputFrameContainer()
    {
 
    ResetControl();

    }

    // ---------------------------------------------------------------------------
    // Symbian 2nd Constructor
    // ---------------------------------------------------------------------------
    //
    void CInputFrameContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetRect( aRect );
    ActivateL();

    }

    // ----------------------------------------------------------------------------
    // CInputFrameContainer::Draw
    // Fills the window's rectangle.
    // ----------------------------------------------------------------------------
    //
    void CInputFrameContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor( KRgbGray);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }
    // ---------------------------------------------------------------------------
    // CInputFrameContainer::CountComponentControls
    // ---------------------------------------------------------------------------
    //
    TInt CInputFrameContainer::CountComponentControls() const
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

    // ---------------------------------------------------------------------------
    // CInputFrameContainer::ComponentControl
    // ---------------------------------------------------------------------------
    //
    CCoeControl* CInputFrameContainer::ComponentControl( TInt ) const
        {
        return iControl;
        }

    // ---------------------------------------------------------------------------
    // CInputFrameContainer::SetControlL
    // ---------------------------------------------------------------------------
    //
    void CInputFrameContainer::SetControlL( CCoeControl* aControl )
        {
        iControl = aControl;
        if ( iControl )
            {
            // You can change the position and size
            iControl->SetExtent( Rect().iTl, Rect().Size() );
            iControl->ActivateL();
            DrawNow();
            }
        }

    // ---------------------------------------------------------------------------
    // CInputFrameContainer::ResetControl
    // ---------------------------------------------------------------------------
    //
    void CInputFrameContainer::ResetControl()
        {
        delete iControl;
        iControl = NULL;
        }
            
    // ---------------------------------------------------------------------------
    // CInputFrameContainer::GetCoeEnv
    // ---------------------------------------------------------------------------
    //
    CCoeEnv* CInputFrameContainer::GetCoeEnv() 
        {
        return iCoeEnv;
        }
