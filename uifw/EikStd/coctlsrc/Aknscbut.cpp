/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:
*
*/


#include <aknscbut.h>
#include <eiksfont.h>
#include <gulutil.h>
#include <eikenv.h>
#include <gulcolor.h>
#include <aknscind.h>

#include <AknsUtils.h>
#include <AknUtils.h>
#include <aknappui.h>

// const TInt KAknScrollButtonBorderWidth=0;
// const TInt KAknScrollButtonWidth=9;
// const TInt KAknScrollButtonHeight=10;

const TInt KTypeOfScrollBarMask = 0x000f;

EXPORT_C CAknScrollButton* CAknScrollButton::NewL(TType aType)
	{
	CAknScrollButton* self = new (ELeave) CAknScrollButton(aType);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

EXPORT_C CAknScrollButton::~CAknScrollButton()
	{
    AknsUtils::DeregisterControlPosition( iScrollIndicator );
	delete iScrollIndicator;
	}

EXPORT_C CAknScrollButton::TType CAknScrollButton::Type() const
	{
	return iType;
	}

EXPORT_C void CAknScrollButton::CreateWindowOnlyForArrowsL(const CCoeControl* aParent)
	{
	CreateWindowL(aParent);
    // "Parent absolute" skin layout requires every window to have a container window.
    iScrollIndicator->SetContainerWindowL(*this);
    if ( AknLayoutUtils::PenEnabled() )
    	{
    	iScrollIndicator->SetWindowOwning( ETrue );
    	}
	}

EXPORT_C TBool CAknScrollButton::IsNormalScrollBarUsingButton() const
	{
    if( AknLayoutUtils::PenEnabled() )
        {
        // correction: AND with 0x0 is always false!
        return (iFlag == ENormal);
        }
    else
        {
    	return (iFlag&ENormal);
        }
	}

/*
 * Set the type of scroll bar which owns the button.
 */
EXPORT_C void CAknScrollButton::SetTypeOfScrollBarUsingButton(TTypeOfScrollBar aTypeOfScrollBar)
	{
    iFlag &= (~KTypeOfScrollBarMask);
	iFlag |= aTypeOfScrollBar;
	}

EXPORT_C void CAknScrollButton::SetPosition(TInt aThumbPosition, TInt aScrollSpan)
	{
	iScrollIndicator->SetPosition(aThumbPosition, aScrollSpan); 
	DrawDeferred() ;
	}

CAknScrollButton::CAknScrollButton(CAknScrollButton::TType aType)
	: iType(aType)
	{
	}

void CAknScrollButton::ConstructL()
	{
	iScrollIndicator = CAknScrollIndicator::NewL(iType);
	iScrollIndicator->SetContainerWindowL(*this);
	SetNonFocusing();
	}

void CAknScrollButton::Draw(const TRect& /*aRect*/) const
	{
    CWindowGc& gc=SystemGc();

	if (!IsNormalScrollBarUsingButton())
	    {	    
		gc.SetBrushColor( iEikonEnv->ControlColor(EColorMenuPaneBackground, *this) );
	    }
	else
	    {	    
		gc.SetBrushColor(KRgbWhite);
	    }
	    
	DrawIndicator();
	}

void CAknScrollButton::SizeChanged()
	{
	iScrollIndicator->SetRect( Rect() );
	if (iOldRect != Rect())
	    {	    
	    AknsUtils::RegisterControlPosition( iScrollIndicator );
	    }
	iOldRect = Rect();
	}

void CAknScrollButton::DrawIndicator() const
	// Draws the indicator on the button 
	{
    if( AknLayoutUtils::PenEnabled() )
        {
        if(IsNormalScrollBarUsingButton())
            {
            // The rect has already been set by CAknDoubleSpanScrollBar
            iScrollIndicator->DrawScrollIndicator( Rect() );
            }
        }
    if ( iFlag == EArrowHead )
        {
        iScrollIndicator->DrawScrollIndicator( Rect() );
        }
	}


EXPORT_C CAknScrollButton* CAknScrollButton::NewL(TType aType, TTypeOfScrollBar aTypeOfScrollBar)
	{
	CAknScrollButton* self = new (ELeave) CAknScrollButton(aType);
	CleanupStack::PushL(self);
	self->ConstructL(aTypeOfScrollBar);
	CleanupStack::Pop();
	return self;
	}


void CAknScrollButton::ConstructL(TTypeOfScrollBar aTypeOfScrollBar)
	{
	SetTypeOfScrollBarUsingButton(aTypeOfScrollBar);
	iScrollIndicator = CAknScrollIndicator::NewL(iType, aTypeOfScrollBar);
	iScrollIndicator->SetContainerWindowL(*this);
	SetNonFocusing();
	}

void CAknScrollButton::SetContainerWindowL( const CCoeControl& aControl )
    {
    CCoeControl::SetContainerWindowL( aControl );
    if ( iScrollIndicator )
        {
        iScrollIndicator->SetContainerWindowL( *this );
        }
    }

TInt CAknScrollButton::CountComponentControls() const
    {
    if ( iScrollIndicator )
        {
        return 1; 
        }
    return 0;
    }
    
CCoeControl* CAknScrollButton::ComponentControl( TInt aIndex ) const
    {
    if ( iScrollIndicator && aIndex == 0 )
        {
        return iScrollIndicator;
        }
    return NULL;           
    }

