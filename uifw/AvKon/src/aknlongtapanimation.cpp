/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of long tap animation feature.
*
*/


#include <AknBitmapAnimation.h>
#include <AknsConstants.h>
#include <AknUtils.h>
#include <apgwgnam.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h> // for testability hooks
#include <touchfeedback.h>
const TInt KStartIntensity = 1;
const TInt KEndIntensity = 100;
#include "aknlongtapanimation.h"

enum TInternalFlags
	{
	EAnimationStarted			     =	0x0001,
	EAnimationHasWindowGroup         =  0x0002
 	};

const TInt KConversionFromMillisecondsToMicroseconds = 1000;

/**  window group's priority */
const TInt KAknLongTapWindowPosition = 11; // window group's priority

/** Window`s Position when hiding the animation which  does not own Window Group */
const TInt KAknAnimationNotOwnWindowGroupWindowPosition = -10; // never at front  

/**  window group's name */
_LIT( KAknLongTapWgName, "LongTapAnim" ); // window groups name


// ============================ EXTENSION CLASS ===============================

NONSHARABLE_CLASS(CAknLongTapAnimationExtension) : public CBase
    {
    public:
        CAknLongTapAnimationExtension();
        ~CAknLongTapAnimationExtension();

    public: // data 
        TBool iVisible;
        TInt iIndex;
        TInt iFlags;
		CPeriodic* iTimer;
    };

CAknLongTapAnimationExtension::CAknLongTapAnimationExtension() : iIndex(-1)
    {
    
    }
CAknLongTapAnimationExtension::~CAknLongTapAnimationExtension()
    {
    
    }


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian two-phase constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapAnimation* CAknLongTapAnimation::NewL()
    {
    CAknLongTapAnimation* self = CAknLongTapAnimation::NewLC();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
// Symbian two-phase constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapAnimation* CAknLongTapAnimation::NewLC()
    {
    CAknLongTapAnimation* self = new( ELeave ) CAknLongTapAnimation;
    CleanupStack::PushL( self );
    self->ConstructL( ETrue );
    AKNTASHOOK_ADDL( self, "CAknLongTapAnimation" );
    return self;
    }

// ---------------------------------------------------------------------------
// CAknLongTapAnimation::NewL()
// ---------------------------------------------------------------------------
//
EXPORT_C CAknLongTapAnimation* CAknLongTapAnimation::NewL( TBool aOwnWindowGroup )
    {
    if ( aOwnWindowGroup )
        {
        return CAknLongTapAnimation::NewL();
        }
    else
        {
        CAknLongTapAnimation* self = new( ELeave ) CAknLongTapAnimation;
        CleanupStack::PushL( self );
        self->ConstructL( EFalse );
        CleanupStack::Pop( self );
        AKNTASHOOK_ADDL( self, "CAknLongTapAnimation" );
        return self;    
        }    
    }


// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAknLongTapAnimation::~CAknLongTapAnimation()
    {
    AKNTASHOOK_REMOVE();
    if( iExtension->iFlags & EAnimationHasWindowGroup )
        {
        iWindowGroup.Close();    
        }
	CancelAnimation();
	
    if (iExtension)
        {
	    delete iExtension->iTimer;
        }
    delete iAnim;
    delete iExtension;
    }
    

// ---------------------------------------------------------------------------
// CAknLongTapAnimation::ShowAnimationL()
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknLongTapAnimation::ShowAnimationL( const TInt aX, 
                                                    const TInt aY )
    {
    TAknLayoutRect layoutRect;
    TRect rect;
    AknLayoutUtils::LayoutMetricsRect( 
            AknLayoutUtils::EApplicationWindow, rect );
    layoutRect.LayoutRect( rect, AknLayoutScalable_Avkon::misc_graphics() );
    layoutRect.LayoutRect( layoutRect.Rect(), 
        AknLayoutScalable_Avkon::misc_graphics() );
    layoutRect.LayoutRect( layoutRect.Rect(),
        AknLayoutScalable_Avkon::texts_graphics() );
    layoutRect.LayoutRect( layoutRect.Rect(),
        AknLayoutScalable_Avkon::cursor_press_pane() );
    layoutRect.LayoutRect( layoutRect.Rect(),
        AknLayoutScalable_Avkon::cursor_press_pane_g1() );
    
    SetRect( TRect( TPoint(aX, aY), layoutRect.Rect().Size() ));
    
    // Position window so that it will be directly on top of
    // the location that was clicked.
    TPoint point( aX - Rect().Width() / 2, aY - Rect().Height() / 2 );
    Window().SetPosition( point );

    iAnim->SetSize( layoutRect.Rect().Size() );
    
    iAnim->SetPosition( Rect().iTl );
    
    // finally, make window visible
    if( iExtension->iFlags & EAnimationHasWindowGroup )
        {
        iWindowGroup.SetOrdinalPosition( 0, KAknLongTapWindowPosition );
        }
    else
        {
        //bring this window to front
        Window().SetOrdinalPosition( 0 );
        }    
    SetVisibility(ETrue);
    ActivateL();

    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        CBitmapAnimClientData* animData = iAnim->BitmapAnimData();	
		TInt interval = animData->FrameIntervalInMilliSeconds()
		             * KConversionFromMillisecondsToMicroseconds;
        TInt frameCount = animData->FrameArray().Count();

        // timeout should be greater than normal animation time 
        // so that timeout does not interfere into normal operation
        TInt timeout = interval * (frameCount+1); 
        feedback->StartFeedback( this, ETouchContinuousSmooth, NULL, KStartIntensity, timeout );
        }
	StartAnimation();
    }


// ---------------------------------------------------------
// CAknLongTapAnimation::HideAnimation
// ---------------------------------------------------------
//
EXPORT_C void CAknLongTapAnimation::HideAnimation()
    {
    if( iExtension->iFlags & EAnimationHasWindowGroup )
        {
        iWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
        }
    else
        {
        //bring this window to back
        Window().SetOrdinalPosition( KAknAnimationNotOwnWindowGroupWindowPosition );
            
        }    

	CancelAnimation();
    iExtension->iIndex = 0;
    DrawNow();
		
    SetVisibility(EFalse);
    }


// ---------------------------------------------------------------------------
// CAknLongTapAnimation::CAknLongTapAnimation()
// ---------------------------------------------------------------------------
//
CAknLongTapAnimation::CAknLongTapAnimation()
    {
    }


// -----------------------------------------------------------------------------
// CAknLongTapAnimation::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknLongTapAnimation::ConstructL( TBool aOwnWindowGroup )
    {
	if (!iExtension)
        {
        iExtension = new( ELeave ) CAknLongTapAnimationExtension;
        }

    if ( aOwnWindowGroup )
        {
        //add flag
        iExtension->iFlags |= EAnimationHasWindowGroup; 
        
        // create a window group for volume popup
        // needed to prevent apps noticing this window
        RWsSession& wsSession = iCoeEnv->WsSession();
        iWindowGroup = RWindowGroup( wsSession );
        User::LeaveIfError( iWindowGroup.Construct( 
                                    (TUint32) &iWindowGroup, EFalse ) );
        iWindowGroup.AutoForeground(EFalse);

        CApaWindowGroupName* name = 
                CApaWindowGroupName::NewLC( wsSession, (TUint32) &iWindowGroup );
        name->SetHidden( ETrue );
        name->SetCaptionL( KAknLongTapWgName );
        User::LeaveIfError( name->SetWindowGroupName( iWindowGroup ));
        CleanupStack::PopAndDestroy();  //name

        iWindowGroup.SetOrdinalPosition( 0, ECoeWinPriorityNeverAtFront );
        
        // create control's window to own window group
        CreateWindowL( &iWindowGroup );    
        Window().SetNonFading(ETrue);
        }
    else
        {
        //remove flag
        iExtension->iFlags &= ~EAnimationHasWindowGroup; 
        //create window
        CreateWindowL();
        Window().SetOrdinalPosition( KAknAnimationNotOwnWindowGroupWindowPosition );
        }    

    EnableWindowTransparency();
    Window().SetShadowDisabled(ETrue);

    iExtension->iTimer = CPeriodic::NewL(CActive::EPriorityStandard);
   
    iAnim = CAknBitmapAnimation::NewL();
    iAnim->ConstructFromSkinL( KAknsIIDQgnGrafLongPressAnim );

    // set default behaviour
    SetVisibility(EFalse);
    }
  

// ---------------------------------------------------------
// CAknLongTapAnimation::SetVisibility
// ---------------------------------------------------------
//
void CAknLongTapAnimation::SetVisibility(TBool aVisibility)
    {
    iExtension->iVisible = aVisibility;
    MakeVisible( aVisibility );
    }


// ---------------------------------------------------------
// CAknLongTapAnimation::Draw
// ---------------------------------------------------------
//
void CAknLongTapAnimation::Draw(const TRect& /*aRect*/) const
 	{	
  	CWindowGc& gc = SystemGc();
    gc.Reset();	
    
 	if (!iExtension->iVisible || iExtension->iIndex < 0)
 		{
 		return;
 		}
 
    CBitmapAnimClientData* animData = iAnim->BitmapAnimData();	
    		
    CFbsBitmap* bit  = animData->FrameArray().At(iExtension->iIndex)->Bitmap();
    CFbsBitmap* mask = animData->FrameArray().At(iExtension->iIndex)->Mask();

	TPoint pos = animData->FrameArray().At( iExtension->iIndex )->Position();
    
    if (mask)
    	{
    	gc.BitBltMasked(pos, bit, TRect(TPoint(0,0), bit->SizeInPixels()), mask, ETrue);
    	}
    else
    	{
    	gc.BitBlt(pos, bit, TRect(TPoint(0,0), bit->SizeInPixels()));
    	}
 	}


// ---------------------------------------------------------
// CAknLongTapAnimation::StartAnimation
// ---------------------------------------------------------
//
void CAknLongTapAnimation::StartAnimation()
	{
	iExtension->iIndex = -1;
 	if (!(iExtension->iFlags & EAnimationStarted))
		{
		TCallBack callback(AnimationCallback, this);
		
		TInt interval = iAnim->BitmapAnimData()->FrameIntervalInMilliSeconds() *
			KConversionFromMillisecondsToMicroseconds;
		
		iExtension->iTimer->Start(0, interval, callback);
		iExtension->iFlags |= EAnimationStarted;
		}		
	}

// ---------------------------------------------------------
// CAknLongTapAnimation::CancelAnimation
// ---------------------------------------------------------
//
void CAknLongTapAnimation::CancelAnimation()
	{
    if (iExtension->iFlags & EAnimationStarted)
		{
		iExtension->iTimer->Cancel();
		iExtension->iFlags &= ~EAnimationStarted;
        MTouchFeedback* feedback = MTouchFeedback::Instance();
        if ( feedback )
            {
            feedback->StopFeedback( this );
            }
		}
	}


// ---------------------------------------------------------
// CAknLongTapAnimation::NextFrame
// ---------------------------------------------------------
//
void CAknLongTapAnimation::NextFrame()
	{
	CBitmapAnimClientData* animData = iAnim->BitmapAnimData();	
    TInt frameCount = animData->FrameArray().Count();
		
	iExtension->iIndex++;
	if (iExtension->iIndex == frameCount)
	{
		iExtension->iIndex = frameCount - 1;
	}
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        // intensity should go from 0 to 100
        TInt intensity = KEndIntensity
                       * (iExtension->iIndex+1) / frameCount;
        feedback->ModifyFeedback( this, intensity );
        }
	DrawNow();
	}


// ---------------------------------------------------------
// CAknLongTapAnimation::AnimationCallback
// ---------------------------------------------------------
//
TInt CAknLongTapAnimation::AnimationCallback(TAny* aPtr)
	{
	CAknLongTapAnimation* ptr = (CAknLongTapAnimation*)aPtr;
	ptr->NextFrame();
	return KErrNone;
	}
	
//  End of File  
