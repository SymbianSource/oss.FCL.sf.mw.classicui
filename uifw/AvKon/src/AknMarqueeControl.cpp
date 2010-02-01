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
* Description:  Text scrolling functionality.
*
*/



// INCLUDE FILES
#include "AknMarqueeControl.h"
#include <biditext.h>
#include <AknBidiTextUtils.h>
#include <AknUtils.h>
#include <AknLayout2ScalableDef.h>

// CONSTANTS
const TInt KAknMarqueeDelay     = 1000000; // start scrolling after a delay of 1 second
const TInt KAknMarqueeInterval  = 100000;  // scroll 10 times in a second
const TInt KAknMarqueeSpeed     = 7;       // scroll 3 pixels at time
const TInt KAknMarqueeLoops     = 1;
const TInt KAknSensibleLength   = 80;
// it does not make any sense to marquee texts longer than this
// since it will take hours and drain battery.
const TInt KAknMaxMarqueeLength = 512;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknMarqueeControl::CAknMarqueeControl
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknMarqueeControl::CAknMarqueeControl(const TInt aLoops, const TInt aScrollAmount, 
                                       const TInt aScrollDelay) : 
    iDelta(0),
    iDelay(aScrollDelay),
    iSpeed(aScrollAmount),
    iInterval(KAknMarqueeInterval),
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
void CAknMarqueeControl::ConstructL()
    {
    iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityIdle);
    ControlEnv()->AddForegroundObserverL(*this);
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknMarqueeControl* CAknMarqueeControl::NewLC(const TInt aLoops, 
                                                       const TInt aScrollAmount,
                                                       const TInt aScrollDelay)
    {
    CAknMarqueeControl* self = new( ELeave )CAknMarqueeControl(aLoops, aScrollAmount, aScrollDelay);
    
    CleanupStack::PushL( self );
    self->ConstructL();

    return self;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknMarqueeControl* CAknMarqueeControl::NewL(const TInt aLoops, 
                                                      const TInt aScrollAmount,
                                                      const TInt aScrollDelay)
    {
    CAknMarqueeControl* self = CAknMarqueeControl::NewLC(aLoops, aScrollAmount, aScrollDelay);
    CleanupStack::Pop();

    return self;
    }
    
// Destructor
CAknMarqueeControl::~CAknMarqueeControl()
    {
    if (iPeriodicTimer)
        {
        iPeriodicTimer->Cancel();
        delete iPeriodicTimer;
        }
    ControlEnv()->RemoveForegroundObserver(*this);
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetRedrawCallBack
// 
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::SetRedrawCallBack(TCallBack& aCallBack)
    {
    iCallBack = aCallBack;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DrawText
// 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknMarqueeControl::DrawText(
    CWindowGc& aGc,
    const TRect& aMarqueeRect,
    const TDesC& aText,
    const TInt aBaselineOffset,
    const CGraphicsContext::TTextAlign aAlign,
    const CFont& aFont )
    {       
    if (iLoops < iMaxLoops ||  // Has every loop been executed?
        iFlags.IsSet(EFlagIsWaitingForCallBack)) 
        {
        TInt textWidth = aFont.TextWidthInPixels(aText);
    
        if (TBidiText::TextDirectionality(aText) == TBidiText::ELeftToRight)
            iFlags.Set(EFlagIsWestern);
        else
            iFlags.Clear(EFlagIsWestern);

        // Does the text fit in the rect or is it wider
        if ( textWidth > aMarqueeRect.Width() )
            {
            // Logical-to-visual conversion.
            
            TInt maxTextLength = KAknSensibleLength;
            
            // Stack buffer is used with normal size texts or in OOM.
            TBuf<KAknSensibleLength + KAknBidiExtraSpacePerLine> visualText;

            HBufC* buffer = NULL;            
            const TDesC* textToBeDrawn = &aText;
            
            if ( iFlags.IsSet(EFlagUseVisualToLogicalConversion) )
                {            
                // If given text is too large for the stack buffer,
                // try to allocate a heap buffer.
                if ( aText.Length() > maxTextLength)
                    {
                    TInt len( aText.Length() < KAknMaxMarqueeLength ? aText.Length() : KAknMaxMarqueeLength );
                    buffer = HBufC::New( len + KAknBidiExtraSpacePerLine );
                    if ( buffer )
                        {
                        maxTextLength = len;
                        }
                    }

                if ( buffer )
                    {
                    TPtr p( buffer->Des() );
                    AknBidiTextUtils::ConvertToVisualAndClip(
                        aText.Left( maxTextLength ),
                        p,
                        aFont,
                        KMaxTInt, 
                        KMaxTInt );
                    textToBeDrawn = buffer;
                    }
                else
                    {
                    AknBidiTextUtils::ConvertToVisualAndClip(
                        aText.Left( maxTextLength ),
                        visualText,
                        aFont,
                        KMaxTInt, 
                        KMaxTInt );
                    textToBeDrawn = &visualText;
                    }
                }

            aGc.SetClippingRect(aMarqueeRect);

            if ( iFlags.IsSet(EFlagIsWestern) ) // Scrolls from right to left.
                {
                TRect rect = aMarqueeRect;
                rect.SetWidth(textWidth);
                if ( iFlags.IsSet(EFlagIsBeginningOfLoop) )
                    {
                    if (iFlags.IsSet(EFlagIsWaitingForCallBack))
                        {
                        rect.Move(-iDelta, 0);
                        }
                    Stop();     // Just in case
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign, 0);
                    rect.Move(iDelta, 0);
                    iFlags.Clear(EFlagIsBeginningOfLoop);
                    Start();
                    aGc.CancelClippingRect();
                    if ( buffer )
                        {
                        delete buffer;
                        }
                    return EFalse; // all drawn for first loop
                    }
                rect.Move(-iDelta, 0);

                // Sliding behaviour: When the last character is visible, scrolling stops
                // and starts from the beginning after a short delay.
                if (rect.iBr.iX >= aMarqueeRect.iBr.iX || iFlags.IsSet(EFlagIsWaitingForCallBack))
                    {
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign, 0);
                    iFlags.Clear(EFlagIsBeginningOfLoop);
                    if ( !iPeriodicTimer->IsActive() )
                        Start();
                    }
                else    // Last character has appeared, so let's make it reappear from the other 
                    {   // side after a delay                    
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign, 0);
                    //Stop();    // Cancel all outstanding requests.
                    iPeriodicTimer->Cancel();
                    iFlags.Set(EFlagIsBeginningOfLoop);
                    iFlags.Set(EFlagIsWaitingForCallBack);
                    iLastCharacter = ETrue;
                    iLoops++;                    
                    Start();
                    }
                }
            else    // Non-western, scrolls from left to right.
                {
                TRect rect = aMarqueeRect;
                // Prepare rect to be scrolled from l -> r
                rect.iTl.iX = rect.iTl.iX - (textWidth - rect.Width());
                
                if ( iFlags.IsSet(EFlagIsBeginningOfLoop) )
                    {
                    if (iFlags.IsSet(EFlagIsWaitingForCallBack))
                        {
                        rect.Move(iDelta, 0);
                        }
                    Stop();     // Just in case
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign, 0);
                    rect.Move(-iDelta, 0);
                    iFlags.Clear(EFlagIsBeginningOfLoop);
                    Start();
                    aGc.CancelClippingRect();
                    if ( buffer )
                        {
                        delete buffer;
                        }
                    return EFalse; // all drawn for first loop
                    }
                rect.Move(iDelta, 0);
                
                if (rect.iTl.iX < aMarqueeRect.iTl.iX || iFlags.IsSet(EFlagIsWaitingForCallBack)) 
                    {
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign, 0);
                    iFlags.Clear(EFlagIsBeginningOfLoop);
                    if ( !iPeriodicTimer->IsActive() )
                        Start();
                    }
                else    // Last character has appeared
                    {
                    aGc.DrawText(*textToBeDrawn, rect, aBaselineOffset, aAlign);
                    //Stop();    // Cancel all outstanding requests.
                    iPeriodicTimer->Cancel();
                    iFlags.Set(EFlagIsBeginningOfLoop);
                    iFlags.Set(EFlagIsWaitingForCallBack);
                    iLastCharacter = ETrue;
                    iLoops++;
                    Start();
                    }
                }

            delete buffer;
            aGc.CancelClippingRect();
            }

        // Time to let the parent know all loops aren't executed yet.
        return EFalse;
        }
    else    // No more loops to be executed -> draw text in the default position.
        {
        //aGc.DrawText(aText, aMarqueeRect, aBaselineOffset, aAlign, 0);
        Stop();         // No need to generate events any longer.
        return ETrue;   // Indicate the parent that marquee has stopped,  
                        // parent is then able to for example truncate the text.
        }               
    }

EXPORT_C TBool CAknMarqueeControl::DrawText( 
    CWindowGc& aGc,
    const TRect& aRect,
    const TAknTextComponentLayout& aTextLayout,
    const TDesC& aText,
    const CFont* aFont)
    {
    RDebug::Print(_L("Warning: Deprecated method CAknMarqueeControl::DrawText( CWindowGc&, TRect&, TAknTextComponentLayout&, TDesC&, CFont* called" ) );
    RDebug::Print(_L("Call CAknMarqueeControl::DrawText(CWindowGc&,,,,, TRgb aColor ) instead") );
    return DrawText( aGc, aRect, aTextLayout, aText, aFont, KRgbBlack );
    }
// -----------------------------------------------------------------------------
// CAknMarqueeControl::DrawText
// 
// -----------------------------------------------------------------------------
//
EXPORT_C TBool CAknMarqueeControl::DrawText(
    CWindowGc& aGc,
    const TRect& aRect,
    const TAknTextComponentLayout& aTextLayout,
    const TDesC& aText,
    const CFont* aFont,
    TRgb  aColor )
    {
    // In this function, TAknLayoutText::DrawText performs logical-to-visual
    // conversion for the given text.
    if ( iLoops < iMaxLoops ) // Has every loop been executed?
        {
        TAknLayoutText textLayout;
        
        if ( aFont )
            {
            textLayout.LayoutText( aRect, aTextLayout, aFont );
            }
        else
            {
            textLayout.LayoutText( aRect, aTextLayout );
            }

        TRect marqueeRect( textLayout.TextRect() );
        TInt textWidth = textLayout.Font()->TextWidthInPixels( aText );
    
        if ( TBidiText::TextDirectionality( aText ) == TBidiText::ELeftToRight )
            iFlags.Set( EFlagIsWestern );
        else
            iFlags.Clear( EFlagIsWestern );

        aGc.SetClippingRect( marqueeRect );

        if ( iFlags.IsSet( EFlagIsWestern ) ) // Scrolls from right to left.
            {
            // Does the text fit in the rect or is it wider
            if ( textWidth > marqueeRect.Width() )   
                {
                TRect rect = aRect;
                rect.SetWidth( aRect.Width() + ( textWidth - marqueeRect.Width() ) );
                if ( iFlags.IsSet( EFlagIsBeginningOfLoop ) &&
                    !iFlags.IsSet( EFlagIsWaitingForCallBack ) )
                    {
                    Stop();     // Just in case
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Clear( EFlagIsBeginningOfLoop );
                    Start();
                    aGc.CancelClippingRect();
                    return EFalse; // all drawn for first loop
                    }
                    
                if ( iDelta == 0 ) // we are still drawing non-scrolling text (2 line lists need this)
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    aGc.CancelClippingRect();
                    return EFalse;
                    }
                    
                rect.Move(-iDelta, 0);

                // ESRY-7M5A33
                // Due to text rolling region is not actual parent region, 
                // textLayout.TextRect() is incorrect. Introduce a temparory layout to recalculate.   
                TAknTextLineLayout  tmpTextLineLayout = aTextLayout;
                tmpTextLineLayout.iW = textWidth;
                // ESLM-7SE7HE 
                // If left margin isn't given reasonable value, calculate it from other values in advance
                if (IsParentRelative(tmpTextLineLayout.il))
                	{
                	tmpTextLineLayout.il = rect.Width() - tmpTextLineLayout.ir -  tmpTextLineLayout.iW;
                   	}
                if ( aFont )
                    {
                    textLayout.LayoutText( rect, tmpTextLineLayout, aFont );
                    }
                else
                    {
                    textLayout.LayoutText( rect, tmpTextLineLayout );
                    }
                    
                if ( iFlags.IsSet( EFlagIsWaitingForCallBack ) )
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    aGc.CancelClippingRect();
                    return EFalse; // all drawn for end delay
                    }

                // Sliding behaviour: When the last character is visible, scrolling stops
                // and starts from the beginning after a short delay.
                if ( textLayout.TextRect().iBr.iX >= marqueeRect.iBr.iX )
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Clear( EFlagIsBeginningOfLoop );
                    if ( !iPeriodicTimer->IsActive() )
                        Start();
                    }
                else    // Last character has appeared, so let's make it reappear from the other 
                    {   // side after a delay
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Set( EFlagIsBeginningOfLoop );
                    iFlags.Set( EFlagIsWaitingForCallBack );
                    iLastCharacter = ETrue;
                    Stop();    // Cancel all outstanding requests.
                    ++iLoops;
                    Start();
                    }
                }
            }
        else    // Non-western, scrolls from left to right.
            {
            if ( textWidth > marqueeRect.Width() )
                {
                TRect rect = aRect;
                // Prepare rect to be scrolled from l -> r
                rect.iTl.iX = rect.iTl.iX - ( textWidth - marqueeRect.Width() );
                
                if ( iFlags.IsSet( EFlagIsBeginningOfLoop ) &&
                    !iFlags.IsSet( EFlagIsWaitingForCallBack ) )
                    {
                    Stop();     // Just in case
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Clear( EFlagIsBeginningOfLoop );
                    Start();
                    aGc.CancelClippingRect();
                    return EFalse; // all drawn for first loop
                    }
                
                if ( iDelta == 0 ) // we are still drawing non-scrolling text (2 line lists need this)
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    aGc.CancelClippingRect();
                    return EFalse;
                    }

                rect.Move(iDelta, 0);

                // note refer to case western               
                TAknTextLineLayout  tmpTextLineLayout = aTextLayout;
                tmpTextLineLayout.iW = textWidth;
                // ESLM-7SE7HE 
                // If right margin isn't given reasonable value, calculate it from other values in advance
                if (IsParentRelative(tmpTextLineLayout.ir))
                    {
                    tmpTextLineLayout.ir = rect.Width() - tmpTextLineLayout.il -  tmpTextLineLayout.iW;
                    }
                if ( aFont )
                    {
                    textLayout.LayoutText( rect, tmpTextLineLayout, aFont );
                    }
                else
                    {
                    textLayout.LayoutText( rect, tmpTextLineLayout );
                    }
                
                if ( iFlags.IsSet( EFlagIsWaitingForCallBack ) )
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    aGc.CancelClippingRect();
                    return EFalse; // all drawn for end delay
                    }
                
                if ( textLayout.TextRect().iTl.iX < marqueeRect.iTl.iX ) 
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Clear( EFlagIsBeginningOfLoop );
                    if ( !iPeriodicTimer->IsActive() )
                        Start();
                    }
                else    // Last character has appeared
                    {
                    textLayout.DrawText( aGc, aText, iFlags.IsSet( EFlagUseVisualToLogicalConversion ), aColor );
                    iFlags.Set( EFlagIsBeginningOfLoop );
                    iFlags.Set( EFlagIsWaitingForCallBack );
                    iLastCharacter = ETrue;
                    Stop();    // Cancel all outstanding requests.
                    ++iLoops;
                    Start();
                    }
                }
            }

        aGc.CancelClippingRect();
        // Time to let the parent know all loops aren't executed yet.
        return EFalse;
        }
    else    // No more loops to be executed -> draw text in the default position.
        {
        //aGc.DrawText(aText, aMarqueeRect, aBaselineOffset, aAlign, 0);
        Stop();         // No need to generate events any longer.
        return ETrue;   // Indicate the parent that marquee has stopped,  
        }               // parent is then able to for example truncate the text.
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Draw
// Draws the text to the proper position.
// -----------------------------------------------------------------------------
//
void CAknMarqueeControl::Draw(const TRect& /*aRect*/) const
    {
    /* nothing to do here really */
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Start
// Starts scrolling the text.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::Start()
    {
    if ( iFlags.IsSet( EFlagIsOn ) ) 
        {
        if ( !iPeriodicTimer->IsActive() )  // start timer if not already started
            {
            iPeriodicTimer->Start( TTimeIntervalMicroSeconds32( iDelay ),
                                   TTimeIntervalMicroSeconds32( iInterval ), 
                                   TCallBack( CAknMarqueeControl::ScrollEvent, this ) );
            }
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::Stop
// Stops scrolling the text.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::Stop()
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
EXPORT_C void CAknMarqueeControl::Reset()
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
EXPORT_C const TBool CAknMarqueeControl::IsMarqueeOn()
    {
    return iFlags.IsSet( EFlagIsOn );
    }
#else
EXPORT_C TBool CAknMarqueeControl::IsMarqueeOn()
    {
    return iFlags.IsSet( EFlagIsOn );
    }
#endif // __WINS__

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetSpeedInPixels
// sets scrolling speed in pixels
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::SetSpeedInPixels(TInt aSpeed)
    {
    if ( aSpeed <= 0 )
        aSpeed = KAknMarqueeSpeed;
    iSpeed = aSpeed;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetDelay
// Sets delay between loops
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::SetDelay(TInt aDelay)
    {
    if ( aDelay < 0 )
        aDelay = KAknMarqueeDelay;
    iDelay = aDelay;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetInterval
// Sets scrolling interval
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::SetInterval(TInt aInterval)
    {
    iInterval = aInterval;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::SetLoops
// Sets the amount of maximum loops to be executed.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::SetLoops(TInt aLoops)
    {
    if ( aLoops < 0 )
        aLoops = KAknMarqueeLoops;
    iMaxLoops = aLoops;
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::DoScroll
// advances text position and instructs parent control to do a redraw
// -----------------------------------------------------------------------------
//
void CAknMarqueeControl::DoScroll()
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
TInt CAknMarqueeControl::ScrollEvent(TAny * aPtr)
    {
    ( ( CAknMarqueeControl* ) aPtr )->DoScroll();
    return TRUE; // run again
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::EnableMarquee
// Enables/disables marquee feature.
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknMarqueeControl::EnableMarquee(TBool aEnable)
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
// CAknMarqueeControl::HandleResourceChange
// Handle fade and unfade message for starts and stops scrolling the text.
// -----------------------------------------------------------------------------
//
void CAknMarqueeControl::HandleResourceChange(TInt aType)
    {
    if( aType == KEikMessageUnfadeWindows )
        {
        if ( ( !iFlags.IsSet( EFlagIsBeginningOfLoop ) 
            && !iFlags.IsSet( EFlagIsWaitingForCallBack ) ) 
            || iLastCharacter )
            {
            iLastCharacter = EFalse;
            Start();        
            }
        }
    else if ( aType == KEikMessageFadeAllWindows )
        {
            Stop();
        }
    CCoeControl::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::HandleGainingForeground
// -----------------------------------------------------------------------------
//
void CAknMarqueeControl::HandleGainingForeground()
    {
    // AJUA-7JCDRR, set marquee text to beginning.
    if ( ( !iFlags.IsSet( EFlagIsBeginningOfLoop ) 
        && !iFlags.IsSet( EFlagIsWaitingForCallBack ) ) 
        || iLastCharacter )
        {
        iLastCharacter = EFalse;
        Start();        
        }
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::HandleLosingForeground
// -----------------------------------------------------------------------------
//
void CAknMarqueeControl::HandleLosingForeground()
    {
    // AJUA-7JCDRR, do not reset it, just then marquee can be resumed    
    Stop();        
    }

// -----------------------------------------------------------------------------
// CAknMarqueeControl::UseLogicalToVisualConversion
// -----------------------------------------------------------------------------
//

EXPORT_C void CAknMarqueeControl::UseLogicalToVisualConversion(
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
