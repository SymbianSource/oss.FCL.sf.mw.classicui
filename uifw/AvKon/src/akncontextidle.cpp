/*
* Copyright (c) 2002-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Container control for skinnable clock control
*                in idle status pane layout.
*
*/


// INCLUDE FILES
#include "akncontextidle.h"
#include "AknSkinnableClock.h"

#include <AknTasHook.h>
// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CAknIdleContextPane::CAknIdleContextPane
// C++ default constructor can NOT contain any code, that
// might leave.
// ---------------------------------------------------------------------------
//
CAknIdleContextPane::CAknIdleContextPane()
	{
	AKNTASHOOK_ADD( this, "CAknIdleContextPane" );
    }


// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CAknIdleContextPane::~CAknIdleContextPane()
	{
	AKNTASHOOK_REMOVE();
    delete iClock;
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::ConstructFromResourceL
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::ConstructFromResourceL( TResourceReader& /*aReader*/ )
    {
    iClock = CAknSkinnableClock::NewL( this, ETrue, ETrue );     
    iClock->ActivateL();
	}


// ---------------------------------------------------------------------------
// CAknIdleContextPane::SizeChanged
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::SizeChanged()
    {
    TPoint tl = Rect().iTl;
    iClock->SetExtent( tl, Size() );
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::CountComponentControls
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
TInt CAknIdleContextPane::CountComponentControls() const
    {
    return iClock ? 1 : 0;
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::ComponentControl
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
CCoeControl* CAknIdleContextPane::ComponentControl( TInt /*aIndex*/ ) const
    {
    return iClock;
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::Draw
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::Draw( const TRect& /*aRect*/ ) const
    {
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::SetDimmed
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::SetDimmed( TBool aDimmed )
    {
    CCoeControl::SetDimmed( aDimmed );
    if ( iClock )
        {
        iClock->SetDimmed( aDimmed );
        }
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::HandleResourceChange
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::HandleResourceChange( TInt aType )
    {
    if( iClock )
        {
        iClock->HandleResourceChange( aType );
        }
    }


// ---------------------------------------------------------------------------
// CAknIdleContextPane::MakeVisible
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CAknIdleContextPane::MakeVisible( TBool aVisible )
    {
    CCoeControl::MakeVisible( aVisible );
    if ( iClock )
        {
        iClock->MakeVisible( aVisible );
        }
    }

//  End of File  


