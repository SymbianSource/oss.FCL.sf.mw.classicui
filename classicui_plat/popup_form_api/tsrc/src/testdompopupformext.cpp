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
* Description:  test aknpopupform.h
*
*/


#include <aknpopupform.h>

#include "testdompopupformext.h"

// ============================= MEMBER FUNCTIONS ==============================


// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoConstructL
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoConstructL()
    {
    ConstructL();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoPlayTone
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoPlayTone()
    {
    PlayTone();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoStaticDeleteL
// -----------------------------------------------------------------------------
//
TInt CAknPopupFormExt::DoStaticDeleteL( TAny* aThis )
    {
    return StaticDeleteL( aThis );
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoSoundSystem
// -----------------------------------------------------------------------------
//
CAknKeySoundSystem* CAknPopupFormExt::DoSoundSystem() const
    {
    return SoundSystem();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoLayoutAndDraw
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoLayoutAndDraw()
    {
    LayoutAndDraw();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoPostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoPostLayoutDynInitL()
    {
    PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoSizeChanged
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoSizeChanged()
    {
    SizeChanged();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoOfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CAknPopupFormExt::DoOfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                TEventCode aModifiers )
    {
    return OfferKeyEventL( aKeyEvent, aModifiers );
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoHandlePointerEventL
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoHandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    HandlePointerEventL( aPointerEvent );
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoActivateGc
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoActivateGc()
    {
    ActivateGc();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DoDeactivateGc
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DoDeactivateGc()
    {
    DeactivateGc();
    }

// -----------------------------------------------------------------------------
// CAknPopupFormExt::DialogDismissedL
// -----------------------------------------------------------------------------
//
void CAknPopupFormExt::DialogDismissedL( TInt /*aButtonId*/ )
    {
    }


