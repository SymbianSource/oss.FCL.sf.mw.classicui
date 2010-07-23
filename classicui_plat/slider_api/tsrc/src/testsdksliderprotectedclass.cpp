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


//  INCLUDES
#include <aknslider.h>
#include <aknutils.h> 
#include <aknsutils.h> 

#include "testsdksliderprotectedclass.h"

// -----------------------------------------------------------------------------
// CTestAknSlider::CTestAknSlider
// -----------------------------------------------------------------------------
//
CTestAknSlider::CTestAknSlider()
    {

    }
// -----------------------------------------------------------------------------
// CTestAknSlider::MinimumSize
// -----------------------------------------------------------------------------
//
TSize CTestAknSlider::MinimumSize()
    {
    TSize size;
    return size;
    }
// -----------------------------------------------------------------------------
// CTestAknSlider::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CTestAknSlider::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/)
    {
    TKeyResponse key = EKeyWasNotConsumed;
    return key;
    }
// -----------------------------------------------------------------------------
// CTestAknSlider::Draw
// -----------------------------------------------------------------------------
//
void CTestAknSlider::Draw(const TRect& /*aRect*/) const
    {

    }
// -----------------------------------------------------------------------------
// CTestAknSlider::SizeChanged
// -----------------------------------------------------------------------------
//
void CTestAknSlider::SizeChanged()
    {

    }

