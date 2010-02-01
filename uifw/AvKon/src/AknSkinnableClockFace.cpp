/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation for skinnable clock face.
*
*/


// SYSTEM INCLUDE FILES
#include <e32math.h>
#include <bitdev.h>
#include <AknsUtils.h>
#include <AknIconUtils.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>

// USER INCLUDE FILES
#include "AknUtils.h"
#include "AknSkinnableClockFace.h"
#include "AknStatuspaneUtils.h"

// LOCAL CONSTANTS AND MACROS
_LIT( KAmPm, "%B" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceDigital::CAknSkinnableClockFaceDigital
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceDigital::CAknSkinnableClockFaceDigital()
    {
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceDigital::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceDigital::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceDigital::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceDigital* CAknSkinnableClockFaceDigital::NewL()
    {
    CAknSkinnableClockFaceDigital* self =
        new ( ELeave ) CAknSkinnableClockFaceDigital;

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceDigital::~CAknSkinnableClockFaceDigital()
    {
    }

// -----------------------------------------------------------------------------
// Helper method to check if latin digits should be used in the clock
// even if locale data defines otherwise.
// -----------------------------------------------------------------------------
//
inline TBool IsNonLatinDigitsUsed()
    {
    TLanguage uiLanguage = AknLangUtils::UserLanguage();
    TLocale locale;
    locale.Refresh();
    TDigitType digitType( locale.DigitType() );

    if ( uiLanguage == ELangUrdu )
        {
        return EFalse;
        }

    return ( AknTextUtils::DigitModeQuery() &&
             digitType != EDigitTypeDevanagari );
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceDigital::DrawTimeToBitmap
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceDigital::DrawTimeToBitmapL( TRect& aRect,
                                          CBitmapContext& aBufferGc,
                                                        TTime& aTime )
    {
    TRect bufferRect( aRect );
    
    TAknWindowLineLayout smallClockPaneLayout(
        AknLayoutScalable_Apps::popup_clock_digital_window() );
        
    TBool smallClock( bufferRect.Width() <= smallClockPaneLayout.iW );
    
    TAknLayoutText amPmIndication;

    TBool isExtendedLayoutActive( AknStatuspaneUtils::ExtendedLayoutActive() );
    TBool isIdleLayoutActive( AknStatuspaneUtils::IdleLayoutActive() );

    if ( isExtendedLayoutActive &&
         isIdleLayoutActive )
        {
        amPmIndication.LayoutText(
            bufferRect,
            AknLayoutScalable_Avkon::popup_clock_digital_window_t1( 1 ) );

        }
    else if ( smallClock )
        {
        amPmIndication.LayoutText(
            bufferRect,
            AknLayoutScalable_Apps::popup_clock_digital_window_t1() );
        }
    else
        {    
        amPmIndication.LayoutText(
            bufferRect,
            AknLayoutScalable_Apps::popup_clock_digital_window_cp02_t1( 0 ) );
        }

    TAknLayoutRect qsnCpClockDigitalLine[4];

    if ( isExtendedLayoutActive &&
         isIdleLayoutActive )
            {
            qsnCpClockDigitalLine[0].LayoutRect(
                bufferRect,
                AknLayoutScalable_Avkon::clock_digital_number_pane( 2 ) );

            qsnCpClockDigitalLine[1].LayoutRect(
                bufferRect,
                AknLayoutScalable_Avkon::clock_digital_number_pane_cp03( 2 ) );

            qsnCpClockDigitalLine[2].LayoutRect(
                bufferRect,
                AknLayoutScalable_Avkon::clock_digital_number_pane_cp02( 2 ) );

            qsnCpClockDigitalLine[3].LayoutRect(
                bufferRect,
                AknLayoutScalable_Avkon::clock_digital_number_pane_cp04( 2 ) );
            }
    else if ( smallClock )
        {
        TAknWindowComponentLayout digitLayout(
            AknLayoutScalable_Apps::clock_digital_number_pane_g1() );

        qsnCpClockDigitalLine[0].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane( 0 ),
                digitLayout ) );

        qsnCpClockDigitalLine[1].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp03( 0 ),
                digitLayout ) );

        qsnCpClockDigitalLine[2].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp02( 0 ),
                    digitLayout ) );

        qsnCpClockDigitalLine[3].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp04( 0 ),
                digitLayout ) );
        }
    else
        {
        TAknWindowComponentLayout digitLayout(
            AknLayoutScalable_Apps::clock_digital_number_pane_cp10_g1(1) );

        qsnCpClockDigitalLine[0].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp10( 0 ),
                digitLayout ) );

        qsnCpClockDigitalLine[1].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp11( 0 ),
                digitLayout ) );

        qsnCpClockDigitalLine[2].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp12( 0 ),
                    digitLayout ) );

        qsnCpClockDigitalLine[3].LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_number_pane_cp13( 0 ),
                digitLayout ) );
        }

    TAknLayoutRect qsnCpClockDigitalSeparator;

    if ( isExtendedLayoutActive &&
         isIdleLayoutActive )
        {
        qsnCpClockDigitalSeparator.LayoutRect(
            bufferRect,
            AknLayoutScalable_Avkon::clock_digital_separator_pane( 2 ) );
        }
    else if ( smallClock )
        {
        qsnCpClockDigitalSeparator.LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_separator_pane( 0 ),
                AknLayoutScalable_Apps::clock_digital_separator_pane_g1() ) );
        }
    else
        {
        qsnCpClockDigitalSeparator.LayoutRect(
            bufferRect,
            TAknWindowComponentLayout::Compose(
                AknLayoutScalable_Apps::clock_digital_separator_pane_cp10( 0 ),
                AknLayoutScalable_Apps::clock_digital_separator_pane_cp10_g1(1) ) );
        }

    TDateTime dateTime( aTime.DateTime() );

    TInt hour   = dateTime.Hour();
    TInt minute = dateTime.Minute();
    TBool time24h = ETrue;
    if( TLocale().TimeFormat() == ETime12 )
        {
        time24h = EFalse;
        if ( hour < 1 )
            {
            hour = 12;
            }
        if ( hour > 12 )
            {
            hour -= 12;
            }
        }

    TInt digits[4];
    digits[0] = hour / 10;
    digits[1] = hour % 10;
    digits[2] = minute / 10;
    digits[3] = minute % 10;

    if( !digits[0] && !time24h )
        {
        digits[0] = -1;
        }

    TInt delimiterDigit =
        EAknsMinorQsnCpClockDigitalColon - EAknsMinorQsnCpClockDigitalZero;
    if( TLocale().TimeSeparator(1) == TChar('.') )
        {
        delimiterDigit =
            EAknsMinorQsnCpClockDigitalStop - EAknsMinorQsnCpClockDigitalZero;
        }

    // First, blit with soft masks (w/ halo)

    for( TInt i = 0; i < 4; i++ )
        {
        if( digits[i] >= 0 )
            {
            BlendDigitL( 
                         aBufferGc,
                         qsnCpClockDigitalLine[i].Rect(),
                         digits[i],
                         EFalse );
            }
        }

    // Separator character
    BlendDigitL(
                 aBufferGc,
                 qsnCpClockDigitalSeparator.Rect(),
                 delimiterDigit,
                 EFalse );

    // Then, re-blit with hard masks.
    // This removes any halo bleeded to adjacent digits.

    BlendDigitL(  aBufferGc,
        qsnCpClockDigitalSeparator.Rect(), delimiterDigit, ETrue );

    for( TInt i = 0; i < 4; i++ )
        {
        if( digits[i] >= 0 )
            {
            BlendDigitL(// bufferRect,
                         aBufferGc,
                         qsnCpClockDigitalLine[i].Rect(),
                         digits[i],
                         ETrue );
            }
        }

    if( !time24h )
        {
        TBuf<KMaxAmPmName + 1> amPmText;
        aTime.FormatL( amPmText, KAmPm );
        TRgb ampmColor = KRgbBlack;
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   ampmColor,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG1 );
        amPmIndication.DrawText( aBufferGc, amPmText, ETrue, ampmColor);
        }
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceDigital::BlendDigitL
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceDigital::BlendDigitL( CBitmapContext& aBufferGc,
                                                 const TRect& aRect,
                                                 const TInt aDigit,
                                                 const TBool aHardMask )
    {


    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TInt baseID         = EAknsMinorQsnCpClockDigitalZero;
    TInt baseSoftMaskID = EAknsMinorQsnCpClockDigitalZeroMaskSoft; // Only for bitmaps
    TInt baseHardMaskID = EAknsMinorQsnCpClockDigitalZeroMaskHard; // Only for SVGs

    if( IsNonLatinDigitsUsed() )
        {
        // Arabic-Indic digits
        baseID         = EAknsMinorQsnCpClockDigitalAhZero;
        baseSoftMaskID = EAknsMinorQsnCpClockDigitalAhZeroMaskSoft;
        baseHardMaskID = EAknsMinorQsnCpClockDigitalAhZeroMaskHard;
        }

    TAknsItemID iid;
    CFbsBitmap* digitBitmap       = NULL;
    CFbsBitmap* digitDirectMask   = NULL;
    CFbsBitmap* digitSeparateMask = NULL;

    TBool separateMaskIsSoft( ETrue );
    TInt separateMaskID = baseSoftMaskID + aDigit;

    iid.Set( EAknsMajorSkin, baseID + aDigit );
    AknsUtils::GetCachedMaskedBitmap( skin, iid, digitBitmap, digitDirectMask );
    if( digitBitmap )
        {
        // Legacy digits
        if( AknIconUtils::IsMifIcon( digitBitmap ) )
            {
            separateMaskIsSoft = EFalse;
            separateMaskID     = baseHardMaskID + aDigit;
            }

        iid.Set( EAknsMajorSkin, separateMaskID );
        digitSeparateMask = AknsUtils::GetCachedBitmap( skin, iid );
        }
    else
        {
        // New digits
        baseID         = EAknsMinorQsnCpClockDigitalNewZero;
        baseHardMaskID = EAknsMinorQsnCpClockDigitalNewZeroShape;

        TLocale locale;
        locale.Refresh();
        TDigitType digitType( locale.DigitType() );
        if( IsNonLatinDigitsUsed() )
            {
            // Arabic-Indic digits
            baseID         = EAknsMinorQsnCpClockDigitalAhNewZero;
            baseHardMaskID = EAknsMinorQsnCpClockDigitalAhNewZeroShape;
            }

        iid.Set( EAknsMajorSkin, baseID + aDigit );
        AknsUtils::GetCachedMaskedBitmap( skin, iid, digitBitmap, digitDirectMask );

        if( !digitBitmap )
            {
            // No digit to render
            return;
            }

        separateMaskIsSoft = EFalse;
        separateMaskID     = baseHardMaskID + aDigit;

        iid.Set( EAknsMajorSkin, separateMaskID );
        digitSeparateMask = AknsUtils::GetCachedBitmap( skin, iid );
        }

    TScaleMode scalemode( EAspectRatioNotPreserved );
    User::LeaveIfError( AknIconUtils::SetSize(
        digitBitmap, aRect.Size(),
        scalemode ) );

    if( digitSeparateMask )
        {
        User::LeaveIfError( AknIconUtils::SetSize(
            digitSeparateMask, aRect.Size(),
            scalemode ) );
        }

    CFbsBitmap* digitHardMask = digitSeparateMask;
    CFbsBitmap* digitSoftMask = digitDirectMask;
    if( separateMaskIsSoft )
        {
        digitHardMask = digitDirectMask;
        digitSoftMask = digitSeparateMask;
        }

    // In case the mask sizes do not match (incorrect graphics),
    // select the smaller for rendering
    TSize digitRenderingSize = digitBitmap->SizeInPixels();
    if( digitSeparateMask )
        {
        TSize separateMaskSize = digitSeparateMask->SizeInPixels();
        if( separateMaskSize.iWidth < digitRenderingSize.iWidth )
            {
            digitRenderingSize.iWidth = separateMaskSize.iWidth;
            }
        if( separateMaskSize.iHeight < digitRenderingSize.iHeight )
            {
            digitRenderingSize.iHeight = separateMaskSize.iHeight;
            }
        }

    if( aHardMask && digitBitmap && digitHardMask &&
        // This check is needed because in some skins the
        // bitmap and hard mask might use the same display mode,
        // in which case the graphics become corrupted.
        digitHardMask->DisplayMode() < digitBitmap->DisplayMode() )
        {
        aBufferGc.BitBltMasked( aRect.iTl,
                                digitBitmap,
                                TRect( TPoint(0,0), digitRenderingSize ),
                                digitHardMask,
                                EFalse );
        }
    else if( !aHardMask && digitBitmap && digitSoftMask )
        {
        aBufferGc.BitBltMasked( aRect.iTl,
                                digitBitmap,
                                TRect( TPoint(0,0), digitRenderingSize ),
                                digitSoftMask,
                                ETrue );
        }
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceAnalogue::CAknSkinnableClockFaceAnalogue
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceAnalogue::CAknSkinnableClockFaceAnalogue(
    const TBool aShowDate ) : iShowDate( aShowDate )
    {
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceAnalogue::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceAnalogue::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceAnalogue::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceAnalogue* CAknSkinnableClockFaceAnalogue::NewL(
    const TBool aShowDate )
    {
    CAknSkinnableClockFaceAnalogue* self =
        new( ELeave ) CAknSkinnableClockFaceAnalogue( aShowDate );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
CAknSkinnableClockFaceAnalogue::~CAknSkinnableClockFaceAnalogue()
    {
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceAnalogue::DrawTimeToBitmap
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceAnalogue::DrawTimeToBitmapL( TRect& aRect,
	                                        CBitmapContext& aBufferGc,
                                                         TTime& aTime )
    {


    TRect bufferRect(aRect);

    TBool idleLayoutActive( AknStatuspaneUtils::IdleLayoutActive() );

    TAknLayoutText currentDate;
    if ( idleLayoutActive )
        {
        currentDate.LayoutText( bufferRect,
            AknLayoutScalable_Apps::popup_clock_analogue_window_t1() );
        }
    else
        {
        currentDate.LayoutText( bufferRect,
            AknLayoutScalable_Apps::popup_clock_analogue_window_cp10_t1(1) );
        }

    TSize faceSize( bufferRect.Size() );


    TDateTime dateTime( aTime.DateTime() );

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    // 1-2: Face number 1

    CFbsBitmap* skinBmp     = NULL;
    CFbsBitmap* softMaskBmp = NULL;

    AknsUtils::GetCachedMaskedBitmap( skin,
                                      KAknsIIDQsnCpClockAnalogueFace1,
                                      skinBmp,
                                      softMaskBmp );
    if( !softMaskBmp )
        {
        softMaskBmp = AknsUtils::GetCachedBitmap( skin,
            KAknsIIDQsnCpClockAnalogueFace1MaskSoft );
        }

    // If there is no bitmap, don't draw
    if( !skinBmp )
        {
        return;
        }

    User::LeaveIfError( AknIconUtils::SetSize( skinBmp, faceSize ) );

    if( softMaskBmp )
        {
        User::LeaveIfError( AknIconUtils::SetSize( softMaskBmp, faceSize) );
        aBufferGc.BitBltMasked( bufferRect.iTl,
                                skinBmp,
                                TRect( TPoint(0,0), skinBmp->SizeInPixels() ),
                                softMaskBmp,
                                ETrue );
        }
    else
        {
        aBufferGc.BitBlt( TPoint(0,0), skinBmp );
        }

    aBufferGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    aBufferGc.SetPenStyle( CGraphicsContext::ESolidPen );

    // 3: Date
    TBool skindateflag = EFalse;
    TRAPD( error, ( skindateflag = AknsUtils::BooleanPropertyL(
        skin, KAknsIIDPropertyAnalogueClockDate ) ) );
    if (error)
        {
        skindateflag = ETrue;
        }

    if ( AknStatuspaneUtils::ExtendedLayoutActive() &&
         idleLayoutActive &&
         iShowDate )
        {
        skindateflag = EFalse; // Date is not shown in extended sp idle clock
        }

    if( skindateflag && iShowDate )
        {
        CAknsMaskedBitmapItemData* skinMaskedBmp =
            static_cast<CAknsMaskedBitmapItemData*>(
            skin->GetCachedItemData( KAknsIIDQsnCpClockAnalogueBorderNum,
            EAknsITMaskedBitmap ) );

        if( skinMaskedBmp )
            {
            User::LeaveIfError( AknIconUtils::SetSize(
                skinMaskedBmp->Bitmap(), faceSize) );

            aBufferGc.BitBltMasked(
                    bufferRect.iTl,
                skinMaskedBmp->Bitmap(),
                TRect( TPoint(0,0), skinMaskedBmp->Bitmap()->SizeInPixels() ),
                skinMaskedBmp->Mask(),
                EFalse );
            }

        TBuf<2> dateText;
        dateText.Num( aTime.DayNoInMonth() + 1 );
        TRgb dateColor = KRgbBlack;
        AknsUtils::GetCachedColor( skin,
                                   dateColor,
                                   KAknsIIDQsnIconColors,
                                   EAknsCIQsnIconColorsCG1 );
        currentDate.DrawText( aBufferGc, dateText, ETrue, dateColor );
        }

    // X: Hands

    DrawHands( aBufferGc, bufferRect, dateTime );

    // 4-5: Face number 2 (glass)

    AknsUtils::GetCachedMaskedBitmap(
            skin, KAknsIIDQsnCpClockAnalogueFace2,
            skinBmp, softMaskBmp );
    if( !softMaskBmp )
        {
        softMaskBmp = AknsUtils::GetCachedBitmap( skin,
            KAknsIIDQsnCpClockAnalogueFace2MaskSoft );
        }

    if( skinBmp && softMaskBmp )
        {
        User::LeaveIfError( AknIconUtils::SetSize( skinBmp, faceSize ) );
        User::LeaveIfError( AknIconUtils::SetSize( softMaskBmp, faceSize ) );
        aBufferGc.BitBltMasked( bufferRect.iTl,
                                skinBmp,
                                TRect(TPoint(0,0), skinBmp->SizeInPixels() ),
                                softMaskBmp,
                                ETrue );
        }
    }

// -----------------------------------------------------------------------------
// CAknSkinnableClockFaceAnalogue::DrawHands
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CAknSkinnableClockFaceAnalogue::DrawHands( CBitmapContext& aBufferGc,
                                                const TRect& aBufferRect,
                                                const TDateTime& aDateTime )
    {
    TRect rect( aBufferRect );
    
    TAknWindowLineLayout smallClockLayout(
        AknLayoutScalable_Apps::popup_clock_analogue_window() );

    TAknWindowComponentLayout layout1(
        AknLayoutScalable_Apps::popup_clock_analogue_window_g3() );
    TAknWindowComponentLayout layout2(
        AknLayoutScalable_Apps::popup_clock_analogue_window_g4() );

    if ( !AknStatuspaneUtils::IdleLayoutActive() &&
         rect.Width() > smallClockLayout.iW )
        {
        layout1 = AknLayoutScalable_Apps::popup_clock_analogue_window_cp10_g3(1);
        layout2 = AknLayoutScalable_Apps::popup_clock_analogue_window_cp10_g4(1);
        }

    TAknLayoutRect hourPointerLayout;
    hourPointerLayout.LayoutRect( aBufferRect,
                                  layout1 );
    TAknLayoutRect minutePointerLayout;
    minutePointerLayout.LayoutRect( aBufferRect,
                                    layout2 );

    TAknLayoutRect scalableHourPointerLayout;
    TAknLayoutRect scalableMinutePointerLayout;

    if ( AknStatuspaneUtils::ExtendedLayoutActive() &&
         AknStatuspaneUtils::IdleLayoutActive() &&
         iShowDate)
        {
        // status pane clock in extended status pane
        scalableHourPointerLayout.LayoutRect( aBufferRect,
            AknLayoutScalable_Avkon::popup_clock_analogue_window_g3() );

        scalableMinutePointerLayout.LayoutRect( aBufferRect,
            AknLayoutScalable_Avkon::popup_clock_analogue_window_g4() );
        }
    else
        {
        // Main pane clock or landscape idle clock
        scalableHourPointerLayout.LayoutRect( aBufferRect,
                                              layout1 );
        scalableMinutePointerLayout.LayoutRect( aBufferRect,
                                                layout2 );
        }

    TRect scalableHourPointerRect( scalableHourPointerLayout.Rect() );
    TRect scalableMinutePointerRect( scalableMinutePointerLayout.Rect() );

    CFbsBitmap* hrbitmap = NULL;
    CFbsBitmap* hrmask   = NULL;

    CFbsBitmap* minbitmap = NULL;
    CFbsBitmap* minmask   = NULL;

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsUtils::GetCachedMaskedBitmap(
            skin, KAknsIIDQsnCpClockAnaloguePointerHour,
            hrbitmap, hrmask );
    AknsUtils::GetCachedMaskedBitmap(
            skin, KAknsIIDQsnCpClockAnaloguePointerMinute,
            minbitmap, minmask );

    TReal angle, length;
    TPoint handEndPoint;
    TReal sin, cos, temp;
    TInt mathErr( KErrNone );

    TRect hourPointerRect( hourPointerLayout.Rect() );
    TRect minutePointerRect( minutePointerLayout.Rect() );
    
    TInt hour   = aDateTime.Hour();
    TInt minute = aDateTime.Minute();

    if ( !hrbitmap || !hrmask )
        {
        angle = TReal( hour * 60 + minute ) *
                KPi / 360.0 - KPiBy2;
        length = TReal( hourPointerRect.Height() );
        mathErr = Math::Sin( sin, angle );
        mathErr |= Math::Cos( cos, angle );
        mathErr |= Math::Round( temp, cos * length, 0 );
        handEndPoint.iX = TInt( temp );
        mathErr |= Math::Round( temp, sin * length, 0 );
        handEndPoint.iY = TInt( temp );
        handEndPoint += hourPointerRect.iTl;

        if( !mathErr )
            {
            aBufferGc.SetPenColor( hourPointerLayout.Color() );
            aBufferGc.SetPenSize( TSize( hourPointerRect.Width(),
                                         hourPointerRect.Width() ) );
            aBufferGc.DrawLine( hourPointerRect.iTl, handEndPoint );
            }
        }
    else
        {
        // Ignore possible error.
        AknIconUtils::SetSizeAndRotation(
            hrbitmap,
            scalableHourPointerRect.Size(),
            EAspectRatioPreserved,
            hour * 30 + minute / 2 );

        aBufferGc.BitBltMasked( scalableHourPointerRect.iTl,
                                hrbitmap,
                                TRect( TPoint(0,0), hrbitmap->SizeInPixels() ),
                                hrmask,
                                EFalse );
        }

    if ( !minbitmap || !minmask )
        {
        angle = TReal( minute * 6 ) * KPi / 180.0 - KPiBy2;
        length = TReal( minutePointerRect.Height() );
        mathErr |= Math::Sin( sin, angle );
        mathErr |= Math::Cos( cos, angle );
        mathErr |= Math::Round( temp, cos * length, 0 );
        handEndPoint.iX = TInt( temp );
        mathErr |= Math::Round( temp, sin * length, 0 );
        handEndPoint.iY = TInt( temp );
        handEndPoint += minutePointerRect.iTl;

        if( !mathErr )
            {
            aBufferGc.SetPenColor( minutePointerLayout.Color() );
            aBufferGc.SetPenSize( TSize( minutePointerRect.Width(),
                                         minutePointerRect.Width() ) );
            aBufferGc.DrawLine( minutePointerRect.iTl, handEndPoint );
            }
        }
    else
        {
        // Ignore possible error.
        AknIconUtils::SetSizeAndRotation(
            minbitmap,
            scalableMinutePointerRect.Size(),
            EAspectRatioPreserved,
            minute * 6 );

        aBufferGc.BitBltMasked( scalableMinutePointerRect.iTl,
                                minbitmap,
                                TRect( TPoint(0,0), minbitmap->SizeInPixels() ),
                                minmask,
                                EFalse );
        }
    }

//  End of File
