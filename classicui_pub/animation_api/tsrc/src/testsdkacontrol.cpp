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
* Description:  Test AknBitmapAnimation.h
*
*/


#include <barsread.h>
#include <coeaui.h>
#include <testsdkanimation.rsg>
#include <eikappui.h>

#include "testsdkacontrol.h"
#include "testsdkanimation.h"

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestControl::NewL
// -----------------------------------------------------------------------------
CTestControl* CTestControl::NewL()
    {
    CTestControl* self = new (ELeave) CTestControl;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    
    }

// -----------------------------------------------------------------------------
// CTestControl::~CTestControl
// -----------------------------------------------------------------------------
CTestControl::~CTestControl()
    {
    delete iBitmapAnimation;
    
    }
    
// -----------------------------------------------------------------------------
// CTestControl::TestRunL
// -----------------------------------------------------------------------------
void CTestControl::TestRunL()
    {
    iBitmapAnimation->SetContainerWindowL( *this );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_ANIMATION_DATA );
    iBitmapAnimation->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iBitmapAnimation->StartAnimationL();
    
    }

// -----------------------------------------------------------------------------
// CTestControl::CTestControl
// -----------------------------------------------------------------------------
CTestControl::CTestControl()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestControl::ConstructL
// -----------------------------------------------------------------------------
void CTestControl::ConstructL()
    {
    CreateWindowL();
    ActivateL();
    iBitmapAnimation = CAknBitmapAnimation::NewL();
    
    }

// -----------------------------------------------------------------------------
// CTestControl::OfferKeyEventL
// -----------------------------------------------------------------------------
TKeyResponse CTestControl::OfferKeyEventL( const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/ )
    {
    return EKeyWasConsumed;
    
    }

// -----------------------------------------------------------------------------
// CTestControl::Draw
// -----------------------------------------------------------------------------
void CTestControl::Draw( const TRect& /*aRect*/ ) const
    {
    
    }

// -----------------------------------------------------------------------------
// CTestControl::CountComponentControls
// -----------------------------------------------------------------------------
TInt CTestControl::CountComponentControls() const
    {
    return 0;
    
    }

// -----------------------------------------------------------------------------
// CTestControl::ComponentControl
// -----------------------------------------------------------------------------
CCoeControl* CTestControl::ComponentControl( TInt aIndex ) const
    {
    switch( aIndex )
        {
        default:
            return NULL;
        }
    
    }

// -----------------------------------------------------------------------------
// CTestControl::SizeChanged
// -----------------------------------------------------------------------------
void CTestControl::SizeChanged()
    {
    
    }

// -----------------------------------------------------------------------------
// CTestControl::SetFrameIndexL
// -----------------------------------------------------------------------------
void CTestControl::SetFrameIndexL( TInt aIndex )
    {
    iBitmapAnimation->SetContainerWindowL( *this );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_ANIMATION_DATA );
    iBitmapAnimation->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iBitmapAnimation->SetFrameIndexL( aIndex );
    iBitmapAnimation->StartAnimationL();
    
    
    }

// -----------------------------------------------------------------------------
// CTestControl::SetFrameIntervalL
// -----------------------------------------------------------------------------
void CTestControl::SetFrameIntervalL( TInt aFrameIntervalInMilliSeconds )
    {
    iBitmapAnimation->SetContainerWindowL( *this );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_ANIMATION_DATA );
    iBitmapAnimation->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iBitmapAnimation->SetFrameIntervalL( aFrameIntervalInMilliSeconds );
    iBitmapAnimation->StartAnimationL();
    
    }

// -----------------------------------------------------------------------------
// CTestControl::TestCancelL
// -----------------------------------------------------------------------------
void CTestControl::TestCancelL()
    {
    iBitmapAnimation->SetContainerWindowL( *this );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_ANIMATION_DATA );
    iBitmapAnimation->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    iBitmapAnimation->StartAnimationL();
    iBitmapAnimation->CancelAnimation();
    
    }
