/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Control to fill sides of compatibility mode window
*
*/


#include <gulicon.h>
#include <aknenv.h>
#include <AknsSkinInstance.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <AknUtils.h>

#include "akncompaside.h"
#include "akncompautils.h"

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSide* CAknCompaSide::NewL()
    {
    CAknCompaSide* self = new (ELeave) CAknCompaSide();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
CAknCompaSide::~CAknCompaSide()
    {
    delete iBgContext;
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSide::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // If skin background draw fails, flat color will be used
    if(!AknsDrawUtils::Background(skin, iBgContext, this, gc, aRect))
        { 
        TRgb backgroundColor;
        AknsUtils::GetCachedColor(skin, backgroundColor,
            KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG20);
            
        gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
        gc.SetPenColor(backgroundColor);
        gc.SetBrushColor(backgroundColor);
        // Draw window rect
        gc.DrawRect(Rect());
        }
    }

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSide::SetBackground(TPoint aOrigin)
    {
    TPoint origo(0, 0);
    TRect screenRect = AknLayout::screen().Rect();
    
    // Skin background context
    iBgContext->SetParentPos(origo);
    AknCompaUtils::ScaleRect(screenRect, -aOrigin.iX, 0);
    iBgContext->SetRect(screenRect);
    }
    
// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------
void CAknCompaSide::ConstructL()
    {
    CreateWindowL();
    RWindow& window = Window();
    // Prevent fading when appication displays a dialog
    window.SetNonFading(ETrue);
    // Ordinal priority is not usually set for application windows
    // (only for window groups). Side control is set to high ordinal
    // priority. This keeps it always at front and prevents compa
    // mode application drawing on top of it.
    const TInt KOrdinalPriority = ECoeWinPriorityAlwaysAtFront + 1;
    window.SetOrdinalPosition(window.OrdinalPosition(), KOrdinalPriority);
    iBgContext = CAknsBasicBackgroundControlContext::NewL(
        KAknsIIDQsnBgScreen, Rect(), ETrue);
    // Control is left unactivated after construction. ActivateL() should
    // be called to display it.
    }
