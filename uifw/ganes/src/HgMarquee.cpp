/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:       Text scrolling functionality.
*
*/


// INCLUDE FILES
#include "HgMarquee.h"
#include <biditext.h>
#include <AknBidiTextUtils.h>
#include <AknUtils.h>
#include <AknLayout2ScalableDef.h>
#include "HgConstants.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknMarqueeControl::CAknMarqueeControl
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CHgMarquee::CHgMarquee(const TInt aLoops, const TInt aScrollAmount, 
                                       const TInt aScrollDelay) : 
    iDelta(0),
    iDelay(aScrollDelay),
    iSpeed(aScrollAmount),
    iInterval(KHgMarqueeInterval),
    iLoops(0),
    iMaxLoops(aLoops),
    iLastCharacter(EFalse)
    {
    iFlags.Set( EFlagIsBeginningOfLoop );
    iFlags.Set( EFlagUseVisualToLogicalConversion );
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgMarquee::ConstructL()
    {
    iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityIdle);
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgMarquee* CHgMarquee::NewLC(const TInt aLoops, 
                                                       const TInt aScrollAmount,
                                                       const TInt aScrollDelay)
    {
    CHgMarquee* self = new( ELeave )CHgMarquee(aLoops, aScrollAmount, aScrollDelay);
    
    CleanupStack::PushL( self );
    self->ConstructL();

    return self;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgMarquee* CHgMarquee::NewL(const TInt aLoops, 
                                                      const TInt aScrollAmount,
                                                      const TInt aScrollDelay)
    {
    CHgMarquee* self = CHgMarquee::NewLC(aLoops, aScrollAmount, aScrollDelay);
    CleanupStack::Pop( self );

    return self;
    }
    
// Destructor
CHgMarquee::~CHgMarquee()
    {
    if (iPeriodicTimer)
        {
        iPeriodicTimer->Cancel();
        delete iPeriodicTimer;
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetRedrawCallBack
// 
// -----------------------------------------------------------------------------
//
void CHgMarquee::SetRedrawCallBack(TCallBack& aCallBack)
    {
    iCallBack = aCallBack;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DrawText
// 
// -----------------------------------------------------------------------------
//
TBool CHgMarquee::DrawText(
    CWindowGc& aGc,
    const TRect& aRect,
    const TAknTextComponentLayout& aTextLayout,
    const TDesC& aText,
    const TRgb& aColor )
    {
    // In this function, TAknLayoutText::DrawText performs logical-to-visual
    // conversion for the given text.
    if ( iLoops < iMaxLoops && aText.Length() < KAknSensibleLength ) // Has every loop been executed
        {
        TAknLayoutText textLayout;
        textLayout.LayoutText( aRect, aTextLayout );

        TRect marqueeRect( textLayout.TextRect() );
        TInt textWidth = textLayout.Font()->TextWidthInPixels( aText );
        if ( textWidth <= marqueeRect.Width() )
            {
            iLoops = iMaxLoops;
            return ETrue;
            }
    
        if ( TBidiText::TextDirectionality( aText ) == TBidiText::ELeftToRight )
            iFlags.Set( EFlagIsWestern );
        else
            iFlags.Clear( EFlagIsWestern );

        aGc.SetClippingRect( marqueeRect );
        
        if ( iFlags.IsSet( EFlagIsBeginningOfLoop ) &&
            !iFlags.IsSet( EFlagIsWaitingForCallBack ) )
            {
            Stop();     // Just in case
            textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
            iFlags.Clear( EFlagIsBeginningOfLoop );
            Start();
            }
        else if ( iDelta == 0 ) // we are still drawing non-scrolling text (2 line lists need this)
            {
            textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
            }
        else if ( iFlags.IsSet( EFlagIsWestern ) ) // Scrolls from right to left.
            {
            DrawWestern(
                    aGc, 
                    aRect, 
                    marqueeRect, 
                    aTextLayout, 
                    textLayout, 
                    aText, 
                    textWidth, 
                    aColor);
            }
        else    // Non-western, scrolls from left to right.
            {
            DrawNonWestern(
                    aGc, 
                    aRect, 
                    marqueeRect, 
                    aTextLayout, 
                    textLayout, 
                    aText, 
                    textWidth, 
                    aColor);
            }

        aGc.CancelClippingRect();
        // Time to let the parent know if all loops aren't executed yet.
        return EFalse;
        }
    else    // No more loops to be executed -> draw text in the default position.
        {
        Stop();         // No need to generate events any longer.
        return ETrue;   // Indicate the parent that marquee has stopped,  
        }               // parent is then able to for example truncate the text.
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DrawWestern
// Starts scrolling the text.
// -----------------------------------------------------------------------------
//
void CHgMarquee::DrawWestern( CWindowGc& aGc,
                         const TRect& aRect,
                         const TRect& aMarqueeRect,
                         const TAknTextComponentLayout& aTextLayout,
                         TAknLayoutText aLayout,
                         const TDesC& aText,
                         TInt aTextWidth,
                         const TRgb& aColor )
    {
    TRect rect = aRect;
    rect.SetWidth( aRect.Width() + ( aTextWidth - aMarqueeRect.Width() ) );
    rect.Move(-iDelta, 0);

    // ESRY-7M5A33
    // Due to text rolling region is not actual parent region, 
    // textLayout.TextRect() is incorrect. Introduce a temparory layout to recalculate.   
    TAknTextLineLayout  tmpTextLineLayout = aTextLayout;
    tmpTextLineLayout.iW = aTextWidth;
    aLayout.LayoutText( rect, tmpTextLineLayout );
        
    aLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );

    if ( iFlags.IsSet( EFlagIsWaitingForCallBack ) )
        {
        // do nothing
        }
    // Sliding behaviour: When the last character is visible, scrolling stops
    // and starts from the beginning after a short delay.
    else if ( aLayout.TextRect().iBr.iX >= aMarqueeRect.iBr.iX )
        {
        iFlags.Clear( EFlagIsBeginningOfLoop );
        if ( !iPeriodicTimer->IsActive() )
            Start();
        }
    else    // Last character has appeared, so let's make it reappear from the other 
        {   // side after a delay
        iFlags.Set( EFlagIsBeginningOfLoop );
        iFlags.Set( EFlagIsWaitingForCallBack );
        iLastCharacter = ETrue;
        Stop();    // Cancel all outstanding requests.
        ++iLoops;
        Start();
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DrawNonWestern
// Starts scrolling the text.
// -----------------------------------------------------------------------------
//
void CHgMarquee::DrawNonWestern( CWindowGc& aGc,
                         const TRect& aRect,
                         const TRect& aMarqueeRect,
                         const TAknTextComponentLayout& aTextLayout,
                         TAknLayoutText aLayout,
                         const TDesC& aText,
                         TInt aTextWidth,
                         const TRgb& aColor )
    {
    TRect rect = aRect;
    // Prepare rect to be scrolled from l -> r
    rect.iTl.iX = rect.iTl.iX - ( aTextWidth - aMarqueeRect.Width() );
    rect.Move(iDelta, 0);

    // note refer to case western               
    TAknTextLineLayout  tmpTextLineLayout = aTextLayout;
    tmpTextLineLayout.iW = aTextWidth;
    aLayout.LayoutText( rect, tmpTextLineLayout );
    
    aLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );

    if ( iFlags.IsSet( EFlagIsWaitingForCallBack ) )
        {
        // do nothing
        }
    else if ( aLayout.TextRect().iTl.iX < aMarqueeRect.iTl.iX ) 
        {
        iFlags.Clear( EFlagIsBeginningOfLoop );
        if ( !iPeriodicTimer->IsActive() )
            Start();
        }
    else    // Last character has appeared
        {
        iFlags.Set( EFlagIsBeginningOfLoop );
        iFlags.Set( EFlagIsWaitingForCallBack );
        iLastCharacter = ETrue;
        Stop();    // Cancel all outstanding requests.
        ++iLoops;
        Start();
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Start
// Starts scrolling the text.
// -----------------------------------------------------------------------------
//
void CHgMarquee::Start()
    {
    if ( iFlags.IsSet( EFlagIsOn ) ) 
        {
        if ( !iPeriodicTimer->IsActive() )  // start timer if not already started
            {
            iPeriodicTimer->Start( TTimeIntervalMicroSeconds32( iDelay ),
                                   TTimeIntervalMicroSeconds32( iInterval ), 
                                   TCallBack( CHgMarquee::ScrollEvent, this ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Stop
// Stops scrolling the text.
// -----------------------------------------------------------------------------
//
void CHgMarquee::Stop()
    {
    //Stop the timer if it is active
    if ( iPeriodicTimer->IsActive() )
        {
        iPeriodicTimer->Cancel();
        }
    if ( !iFlags.IsSet(EFlagIsWaitingForCallBack) )
        {
        iDelta = 0;            // reset scroll position
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Reset
// Resets the animation data.
// -----------------------------------------------------------------------------
//
void CHgMarquee::Reset()
    {
    iDelta = 0;            // reset scroll position
    iLoops = 0;
    iLastCharacter = EFalse;
    Stop();
    iFlags.Set( EFlagIsBeginningOfLoop );
    iFlags.Clear( EFlagIsWaitingForCallBack );
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::IsMarqueeOn
// Returns marquee status
// Two versions to discard compiler warnings
// -----------------------------------------------------------------------------
//
#ifdef __WINS__
const TBool CHgMarquee::IsMarqueeOn()
    {
    return iFlags.IsSet( EFlagIsOn );
    }
#else
TBool CHgMarquee::IsMarqueeOn()
    {
    return iFlags.IsSet( EFlagIsOn );
    }
#endif // __WINS__

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetSpeedInPixels
// sets scrolling speed in pixels
// -----------------------------------------------------------------------------
//
void CHgMarquee::SetSpeedInPixels(TInt aSpeed)
    {
    if ( aSpeed <= 0 )
        aSpeed = KHgMarqueeSpeed;
    iSpeed = aSpeed;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetDelay
// Sets delay between loops
// -----------------------------------------------------------------------------
//
void CHgMarquee::SetDelay(TInt aDelay)
    {
    if ( aDelay < 0 )
        aDelay = KHgMarqueeDelay;
    iDelay = aDelay;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetInterval
// Sets scrolling interval
// -----------------------------------------------------------------------------
//
void CHgMarquee::SetInterval(TInt aInterval)
    {
    iInterval = aInterval;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetLoops
// Sets the amount of maximum loops to be executed.
// -----------------------------------------------------------------------------
//
void CHgMarquee::SetLoops(TInt aLoops)
    {
    if ( aLoops < 0 )
        aLoops = KHgMarqueeLoops;
    iMaxLoops = aLoops;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DoScroll
// advances text position and instructs parent control to do a redraw
// -----------------------------------------------------------------------------
//
void CHgMarquee::DoScroll()
    {
    if ( !iFlags.IsSet( EFlagIsWaitingForCallBack ) )
        {
        iDelta += iSpeed;            // advance text
        }
  
    iFlags.Clear( EFlagIsWaitingForCallBack );
    
    if ( !iCallBack.CallBack() )   // stop timer if callback returns false
        {
        iPeriodicTimer->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::ScrollEvent
// This static function is called by the periodic timer
// -----------------------------------------------------------------------------
//
TInt CHgMarquee::ScrollEvent(TAny * aPtr)
    {
    ( ( CHgMarquee* ) aPtr )->DoScroll();
    return TRUE; // run again
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::EnableMarquee
// Enables/disables marquee feature.
// -----------------------------------------------------------------------------
//
void CHgMarquee::EnableMarquee(TBool aEnable)
    {
    if ( aEnable )
        {
        iFlags.Set( EFlagIsOn );
        }
    else
        {
        iFlags.Clear( EFlagIsOn );
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::UseLogicalToVisualConversion
// -----------------------------------------------------------------------------
//

void CHgMarquee::UseLogicalToVisualConversion(
    TBool aUseConversion )
    {
    if ( aUseConversion )
        {
        iFlags.Set( EFlagUseVisualToLogicalConversion );
        }
    else
        {
        iFlags.Clear( EFlagUseVisualToLogicalConversion );
        }
    }

//  End of File  
