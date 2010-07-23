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
* Description:  derived from eikscrlb.h
*
*/


// [ INCLUDE FILES]
#include <eikscrlb.h>
#include <coecntrl.h>

#include "testsdkscrollereikscrlb.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CEikScrollBarExt::DoComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CEikScrollBarExt::DoComponentControl(TInt aIndex) const
    {
    return ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CEikScrollBarExt::DoComponentControl
// -----------------------------------------------------------------------------
//
TInt CEikScrollBarExt::DoCountComponentControls() const
    {
    return CountComponentControls();
    }

// -----------------------------------------------------------------------------
// CEikScrollBarExt::DoSetButtonPositionL
// -----------------------------------------------------------------------------
//
void CEikScrollBarExt::DoSetButtonPositionL(CAknScrollButton* aButton)
    {
    SetButtonPositionL( aButton );
    }

// -----------------------------------------------------------------------------
// CEikScrollBarExt::SizeChanged
// -----------------------------------------------------------------------------
//
void CEikScrollBarExt::SizeChanged()
    {
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::CAknDouSpanScBarExt
// -----------------------------------------------------------------------------
//
CAknDouSpanScBarExt::CAknDouSpanScBarExt( CCoeControl* aParentWindow ):CAknDoubleSpanScrollBar( aParentWindow )
    {
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::~CAknDouSpanScBarExt
// -----------------------------------------------------------------------------
//
CAknDouSpanScBarExt::~CAknDouSpanScBarExt()
    {
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::CreateButtonL
// -----------------------------------------------------------------------------
//
void CAknDouSpanScBarExt::CreateButtonL( CAknScrollButton*& /*aButton*/,
        CAknScrollButton::TType /*aType*/ )
    {
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::SetButtonPositionL
// -----------------------------------------------------------------------------
//
void CAknDouSpanScBarExt::SetButtonPositionL( CAknScrollButton* /*aButton*/ )
    {
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::DoComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CAknDouSpanScBarExt::DoComponentControl(TInt aIndex) const
    {
    return ComponentControl( aIndex );
    }

// -----------------------------------------------------------------------------
// CAknDouSpanScBarExt::DoComponentControl
// -----------------------------------------------------------------------------
//
TInt CAknDouSpanScBarExt::DoCountComponentControls() const
    {
    return CountComponentControls();
    }

