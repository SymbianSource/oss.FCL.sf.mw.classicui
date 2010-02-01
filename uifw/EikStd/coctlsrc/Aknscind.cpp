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


#include <coecntrl.h>
#include <aknconsts.h>
#include "aknscbut.h"
#include "aknscind.h"
#include <avkon.mbg>
#include <eikenv.h>
#include <AknsDrawUtils.h>
#include <AknLayout.lag>
#include <AknIconUtils.h>
#include <AknUtils.h>
#include <AknsUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknappui.h>
#include <gulicon.h>
#include <AknsConstants.h>

static const TInt KNoOfIndicatorColors = 17;
static const TInt KMaxIndicatorIndex = KNoOfIndicatorColors - 1;
static const TInt KNoOfGrayMaskColors = 256;
static const TInt KMaxGrayMaskIndex = KNoOfGrayMaskColors - 1;
static const TInt KMinGrayMaskIndex = 0;
static const TInt KFullColor = 16;

const TUint8 KIndicatorColors[KNoOfIndicatorColors] =
    {
    0,
    226,
    227,
    228,
    229,
    230,
    231,
    232,
    233,
    234,
    235,
    236,
    237,
    238,
    239,
    240,
    241
    };

//
// Local panics + routine
//
enum TEikPanicResourceScrollerIndicator
    {
    EEikPanicScrollbarScrollRangeLow,
    EEikPanicScrollbarIndicatorOutOfRangeLow,
    EEikPanicScrollbarIndicatorOutOfRangeHigh,
    EEikPanicScrollbarScrollSpanLow,
    EEikPanicScrollbarFocusPosOutOfRange
    };

#if defined(_DEBUG)
LOCAL_C void Panic(TEikPanicResourceScrollerIndicator aPanic)
    {
    _LIT(KPanicCat,"AVKON-Scroll Indicator");
    User::Panic(KPanicCat, aPanic);
    }
#endif

CAknScrollIndicator::CAknScrollIndicator(CAknScrollButton::TType aType)
    : iFocusPosition(0), iScrollSpan(1), iType(aType), iTypeOfScrollBar(CAknScrollButton::EArrowHead)
    {
    }

CAknScrollIndicator* CAknScrollIndicator::NewL(CAknScrollButton::TType aType)
    {
    CAknScrollIndicator* self = new(ELeave) CAknScrollIndicator(aType);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

    
CAknScrollIndicator* CAknScrollIndicator::NewL(CAknScrollButton::TType aType, CAknScrollButton::TTypeOfScrollBar aTypeOfScrollBar)
    {
    CAknScrollIndicator* self = new(ELeave) CAknScrollIndicator(aType);
    CleanupStack::PushL(self);
    self->ConstructL(aTypeOfScrollBar);
    CleanupStack::Pop();
    return self;
    }
    
void CAknScrollIndicator::ConstructL(CAknScrollButton::TTypeOfScrollBar aTypeOfScrollBar)
    {
    iTypeOfScrollBar = aTypeOfScrollBar;
    ConstructL();
    }

void CAknScrollIndicator::ConstructL()
    {
    iIsWindowOwningScrollBar = EFalse;
    if( AknLayoutUtils::PenEnabled() && (iTypeOfScrollBar == CAknScrollButton::ENormal) )
        {
        // TODO: Load bitmaps for double span scroll bar buttons when they become available
        // Get the correct sizes from LAF when the support for the buttons is available
        // Initalize the bitmap devices and graphics contexts correctly        
        TInt err;         
        TAknsItemID indicator; 
        TAknWindowComponentLayout buttonLayout;
        TAknWindowComponentLayout scrollpaneLayout;
        
        switch( iType )
            {
            case CAknScrollButton::ENudgeUp:        	        
                buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_up_pane( 1 );  
                indicator = KAknsIIDQgnGrafScrollArrowUp;
                scrollpaneLayout = AknLayoutScalable_Avkon::scroll_pane();
                break;
            case CAknScrollButton::ENudgeDown:
                buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_down_pane( 1 );  
                indicator = KAknsIIDQgnGrafScrollArrowDown;
                scrollpaneLayout = AknLayoutScalable_Avkon::scroll_pane();
                break;
            case CAknScrollButton::ENudgeLeft:
                buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_left_pane();  
                indicator = KAknsIIDQgnGrafScrollArrowLeft;
                scrollpaneLayout = AknLayoutScalable_Avkon::scroll_pane(1);
                break;
            case CAknScrollButton::ENudgeRight:
                buttonLayout = AknLayoutScalable_Avkon::scroll_sc2_right_pane();
                indicator = KAknsIIDQgnGrafScrollArrowRight;
                scrollpaneLayout = AknLayoutScalable_Avkon::scroll_pane(1);
                break;
            default:
                return;
            }
        
        TAknLayoutRect scrollpaneLayoutRect, buttonLayoutRect;
        
        // Using mainpanerect only for counting the size of button bitmap
        TRect mainpaneRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainpaneRect );
        scrollpaneLayoutRect.LayoutRect( mainpaneRect, scrollpaneLayout.LayoutLine() ); 
        buttonLayoutRect.LayoutRect( scrollpaneLayoutRect.Rect(), buttonLayout.LayoutLine() ); 
        
        // trapping possible leave in this phase when there's no bitmaps in other skins        
        
        TRAP( err, iIcon = AknsUtils::CreateGulIconL( AknsUtils::SkinInstance(), 
                            indicator, EFalse ) );
        
        if( err == KErrNone )
            {
            AknIconUtils::SetSize( iIcon->Bitmap(),  buttonLayoutRect.Rect().Size() );    
            AknIconUtils::SetSize( iIcon->Mask(),  buttonLayoutRect.Rect().Size() );    
            }             
        }
    else
        {
        TInt indicator;
        TSize indiSize;


        // screen
        TRect screenRect = iAvkonAppUi->ApplicationRect();
    
        //TAknWindowLineLayout screenLayout = AknLayout::screen();
        //TRect screenRect = screenLayout.Rect();

        // app window
        TAknWindowLineLayout applicationWindowLayout =
            AknLayout::application_window(screenRect);
    
        TAknLayoutRect applicationWindowLayoutRect;
        applicationWindowLayoutRect.LayoutRect(screenRect, applicationWindowLayout);
        TRect applicationWindowRect = applicationWindowLayoutRect.Rect(); 

        // control pane
        TAknWindowLineLayout controlPaneLayout =
            AknLayout::control_pane(applicationWindowRect);

        TAknLayoutRect controlPaneLayoutRect;
        controlPaneLayoutRect.LayoutRect(applicationWindowRect, controlPaneLayout);
        TRect controlPaneRect = controlPaneLayoutRect.Rect(); 

    
        if (iType == CAknScrollButton::ENudgeUp)
            {
            // scroll up
            TAknWindowLineLayout scrollLayout =
                AknLayout::Control_pane_elements_Line_1();
            TAknLayoutRect scrollLayoutRect;
            scrollLayoutRect.LayoutRect(controlPaneRect, scrollLayout);
            TRect scrollRect = scrollLayoutRect.Rect(); 

            indicator=EMbmAvkonQgn_indi_scroll_a;        
            indiSize = scrollRect.Size();
            }
        else
            {
            // scroll down
            TAknWindowLineLayout scrollLayout =
                AknLayout::Control_pane_elements_Line_2();
            TAknLayoutRect scrollLayoutRect;
            scrollLayoutRect.LayoutRect(controlPaneRect, scrollLayout);
            TRect scrollRect = scrollLayoutRect.Rect(); 

            indicator=EMbmAvkonQgn_indi_scroll_b;
            indiSize = scrollRect.Size();
            }

//  iBitmap = new (ELeave) CFbsBitmap();
//  User::LeaveIfError(iBitmap->Load(KAvkonBitmapFile,
//      indicator,ETrue));

//    iBitmap = AknIconUtils::CreateIconL(KAvkonBitmapFile, indicator);
    
        iBitmap = new (ELeave) CEikImage();    
        CFbsBitmap* mask = NULL;
        CFbsBitmap* bitmap = NULL;
    
        // Use bitmap id for both mask and bitmap because of 1-bit icons.
        AknIconUtils::CreateIconL(
            bitmap, mask, KAvkonBitmapFile, indicator, indicator ); 
        AknIconUtils::SetSize(bitmap,indiSize);
        // Also note that in the drawing time mask is used as bitmap. We store the bitmap
        // only because AknIconUtils requires to do so.
        iBitmap->SetBitmap(bitmap);
        iBitmap->SetMask(mask);

        iColorBitmap = new (ELeave) CFbsBitmap();
        User::LeaveIfError( iColorBitmap->Create( bitmap->SizeInPixels(),
            iEikonEnv->ScreenDevice()->DisplayMode() ) );
        iColorBmpDev = CFbsBitmapDevice::NewL( iColorBitmap );
//      User::LeaveIfError( iColorBmpDev->Resize( bitmap->SizeInPixels()));
        iColorBmpGc = CFbsBitGc::NewL();
        iColorBmpGc->Activate( iColorBmpDev );

        iMaskBitmap = new (ELeave) CFbsBitmap();
        //8-bit bitmap
        User::LeaveIfError( iMaskBitmap->Create( bitmap->SizeInPixels(),
            EGray256 ));
        iMaskBmpDev = CFbsBitmapDevice::NewL( iMaskBitmap );
//      User::LeaveIfError( iMaskBmpDev->Resize( bitmap->SizeInPixels()));
        iMaskBmpGc = CFbsBitGc::NewL();
        iMaskBmpGc->Activate( iMaskBmpDev );
        }
    }

CAknScrollIndicator::~CAknScrollIndicator()
    {
    delete iBitmap;
    delete iColorBitmap;
    delete iColorBmpDev;
    delete iColorBmpGc;
    delete iMaskBmpGc;
    delete iMaskBmpDev;
    delete iMaskBitmap;    
    delete iIcon;
        
        
    }


/**
 * Main method. Calculates the index of the appropriate scroller
 * indicator bitmap color and draws it.
 *
 * Alternatively draws a transparent indicator using 8-bit
 * greyscale mask.
 */
void CAknScrollIndicator::DrawScrollIndicator(const TRect& aRect)
    {
    if( AknLayoutUtils::PenEnabled() && (iTypeOfScrollBar == CAknScrollButton::ENormal) )
        {        
        CWindowGc& gc = SystemGc();
       
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
        if ( iIsWindowOwningScrollBar )
            {            
            TRect rect( Window().Position() + aRect.iTl, aRect.Size() ); 
            AknsDrawUtils::DrawBackground( skin, cc, NULL, gc, aRect.iTl, rect , KAknsDrawParamNoClearUnderImage );
            }
        else
            {
            AknsDrawUtils::Background( skin, cc, this, gc, aRect, KAknsDrawParamNoClearUnderImage );
            }
        
        if( iIcon )
            {
            gc.BitBltMasked( aRect.iTl, iIcon->Bitmap(), aRect.Size(), iIcon->Mask(), ETrue );            
            }        
        }
    else
        {
        
        if (Size().iWidth)  // only draw bitmaps if the button has some size to it
            {
            CWindowGc& gc=SystemGc();   // graphics context we draw to
            TInt indicator( 0 );            // which indicator color to draw
            TInt grayIndicator( KMinGrayMaskIndex );
            
            // if focus position is at the lower limit the color is the 0th...
            if (iFocusPosition <= 0) {}// do nothing
            // at the upper limit it is the MAXth...
            else if (iFocusPosition >= iScrollSpan-1)
                {
                indicator = KMaxIndicatorIndex;
                grayIndicator = KMaxGrayMaskIndex;
                }
                // ...all other indicator colors are spread evenly between
                // all other focus positions...
            else
                {
                // all indicators minus top & bottom
                TInt variableIndicatorRange( KNoOfIndicatorColors-2 );
                TInt maxVariableIndex( iScrollSpan-1 );
                // Calculate the indicator value...
                indicator=((iFocusPosition*variableIndicatorRange)+
                    (maxVariableIndex-1))/maxVariableIndex;
                
                grayIndicator = KMaxGrayMaskIndex -
                    ( maxVariableIndex - iFocusPosition ) *
                    ( KMaxGrayMaskIndex - KMinGrayMaskIndex ) /
                    maxVariableIndex;
                }
            // Sanity checks...
            __ASSERT_DEBUG(indicator>=0,
                Panic( EEikPanicScrollbarIndicatorOutOfRangeLow));
            __ASSERT_DEBUG(indicator<=KMaxIndicatorIndex,
                Panic(EEikPanicScrollbarIndicatorOutOfRangeHigh));
            __ASSERT_DEBUG(grayIndicator>=0,
                Panic( EEikPanicScrollbarIndicatorOutOfRangeLow));
            __ASSERT_DEBUG(grayIndicator<=KMaxGrayMaskIndex,
                Panic(EEikPanicScrollbarIndicatorOutOfRangeHigh));
            
            // reverse the colors for down buttons
            if ( iType == CAknScrollButton::ENudgeDown )
                {
                indicator = KMaxIndicatorIndex - indicator;
                grayIndicator = KMaxGrayMaskIndex - grayIndicator;
                }
            MAknsSkinInstance* skin = AknsUtils::SkinInstance();
            MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
            
            AknsDrawUtils::Background( skin, cc, this, gc, aRect );
            
            if( indicator )
                {
                CFbsBitmap* mask = NULL;
                if (iType == CAknScrollButton::ENudgeUp)
                    {
                    mask = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnIndiScrollUpMask );
                    if ( mask )
                        {
                        AknIconUtils::SetSize( mask, aRect.Size() );
                        }
                    }
                else
                    {
                    mask = AknsUtils::GetCachedBitmap( skin, KAknsIIDQgnIndiScrollDownMask );
                    if ( mask )
                        {
                        AknIconUtils::SetSize( mask, aRect.Size() );
                        }
                    }
                
                
                const CFbsBitmap* blitMask = mask;
                if( !blitMask )
                    {
                    blitMask = iBitmap->Mask();
                    }
                
                
                TRgb color( AKN_LAF_COLOR( KIndicatorColors[indicator] ) );
                
                TInt err( AknsUtils::GetCachedColor( skin, color, KAknsIIDQsnScrollColors, KFullColor ) );
                
                const TRect bmpRect( TPoint( 0,0 ), aRect.Size() );
                
                iColorBmpGc->SetPenStyle( CGraphicsContext::ENullPen );
                iColorBmpGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
                
                if ( err == KErrNone )
                    {
                    TRgb gray( 0,0,0 );
                    //mask bitmap with right gray color
                    iMaskBmpGc->SetPenStyle( CGraphicsContext::ENullPen );
                    iMaskBmpGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
                    iMaskBmpGc->SetBrushColor( gray.Gray256( grayIndicator ) );
                    iMaskBmpGc->DrawRect( bmpRect );
                    
                    //bitmap temporarily filled with black
                    iColorBmpGc->SetBrushColor( TRgb( 0, 0, 0 ) );
                    iColorBmpGc->DrawRect( bmpRect );
                    
                    //create the mask with gray colored shape
                    iMaskBmpGc->SetBrushStyle( CGraphicsContext::ENullBrush );
                    iMaskBmpGc->BitBltMasked( aRect.iTl, iColorBitmap,
                        bmpRect, blitMask, EFalse );
                    
                    //set the skin color
                    iColorBmpGc->SetBrushColor( color );
                    iColorBmpGc->DrawRect( bmpRect );
                    
                    //blit to screen with transparent color
                    gc.SetBrushStyle( CGraphicsContext::ENullBrush );
                    gc.BitBltMasked( aRect.iTl, iColorBitmap,
                        bmpRect, iMaskBitmap, ETrue );
                    }
                else
                    {
                    iColorBmpGc->SetBrushColor( color );
                    iColorBmpGc->DrawRect( bmpRect );
                    
                    //draw default color
                    gc.BitBltMasked( aRect.iTl, iColorBitmap, bmpRect,
                        blitMask, ETrue );
                    }
                }
            }
        } //end of else
    }



void CAknScrollIndicator::SetPosition(const TInt aFocusPosition, const TInt aScrollSpan)
    /**
    / Sets the new focus position in the list and the list length.
    */
    {
    // check parameters valid
    // scrollspan can now be zero and focusposition -1 for empty lists.
    __ASSERT_DEBUG(aScrollSpan>=0,Panic(EEikPanicScrollbarScrollSpanLow));
    __ASSERT_DEBUG((aFocusPosition>=-1) && (aFocusPosition<=aScrollSpan),Panic(EEikPanicScrollbarFocusPosOutOfRange));

    iFocusPosition = aFocusPosition;
    iScrollSpan = aScrollSpan;
    }
void CAknScrollIndicator::SetWindowOwning( const TBool aBool )
    {   
    iIsWindowOwningScrollBar = aBool;
    }


