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
* Description:  Indicator for double span scroll bar.
*    
*
*/


#include "AknDoubleSpanScrollIndicator.h"
#include "AknDoubleSpanScrollIndicatorItem.h"
#include <aknconsts.h>
#include <avkon.mbg>
#include <AknUtils.h>
#include <AknsDrawUtils.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknappui.h>
#include <AknDef.h>
#include <AknPriv.hrh>
#include <AknTasHook.h>
#include <AknsDrawUtils.h>

CAknDoubleSpanScrollIndicator* CAknDoubleSpanScrollIndicator::NewL(CEikScrollBar::TOrientation aOrientation)
    {
    CAknDoubleSpanScrollIndicator* self = new (ELeave) CAknDoubleSpanScrollIndicator();
    CleanupStack::PushL(self);
    self->ConstructL(aOrientation);
    CleanupStack::Pop();
    return self;
    }

CAknDoubleSpanScrollIndicator::CAknDoubleSpanScrollIndicator() 
: iOwnsWindow(EFalse), iTransparentBackground(EFalse), iDrawBackground(ETrue), 
    iBackgroundHighlight(EFalse)
    {
    AKNTASHOOK_ADD( this, "CAknDoubleSpanScrollIndicator" );
    }

CAknDoubleSpanScrollIndicator::~CAknDoubleSpanScrollIndicator()
    {
    AKNTASHOOK_REMOVE();
    AknsUtils::DeregisterControlPosition( this );
    
    delete iBackgroundBar;
    delete iHighlightBackgroundBar;
    delete iHandleBar;
    delete iHighlightHandleBar;
    
 
    }

void CAknDoubleSpanScrollIndicator::ConstructL(CEikScrollBar::TOrientation aOrientation)
    {
    iOrientation = aOrientation;
    CreateScrollBarItemsL();
    UpdateScrollBarLayout();
    }

void CAknDoubleSpanScrollIndicator::Draw(const TRect& /*aRect*/) const
    {
    CWindowGc& gc = SystemGc();
    if( iDrawBackground || iForceDrawBackground )

        {
        DrawBackground();
        }
    
    CAknDoubleSpanScrollIndicatorItem* handleBackgroundBar = 
        iBackgroundHighlight && iHighlightBackgroundBar ?
            iHighlightBackgroundBar : iBackgroundBar;
    
    DrawTiled(gc, iBackgroundRect, handleBackgroundBar);

    TBool showHandleBarBackground = iFieldPosition >= 0 && iFieldSize > 0; 
    if(showHandleBarBackground)
        {
        DrawTiled(gc, iHandleBackgroundRect, iHighlightBackgroundBar);
        }

    CAknDoubleSpanScrollIndicatorItem* handleBar = 
        iHandleHighlight && iHighlightHandleBar ?
        iHighlightHandleBar : iHandleBar;

    DrawTiled(gc, iHandleRect, handleBar);
    }
void CAknDoubleSpanScrollIndicator::UpdateScrollBarLayout()
    {
    iHeadItemSize = 12;
    iMidItemSize = 12 * 5;
    iTailItemSize = 12;
    
    TRect rect = Rect();
    if(rect.IsEmpty())
        {        
        return;
        }
    
    TInt varietyIndex ( 0 );
    if ( iOrientation == CEikScrollBar::EHorizontal )
        {
        varietyIndex = 1;
        }

    TAknLayoutRect layRect;
    TAknWindowComponentLayout layout = AknLayoutScalable_Avkon::scroll_bg_pane_g1( varietyIndex ); //top
    layRect.LayoutRect( rect, layout.LayoutLine() );    
    TSize newSize = layRect.Rect().Size();  
    iHeadItemSize = (iOrientation == CEikScrollBar::EVertical?newSize.iHeight:newSize.iWidth);
    
    layout = AknLayoutScalable_Avkon::scroll_bg_pane_g3(varietyIndex); // bottom
    layRect.LayoutRect(rect, layout.LayoutLine());
    newSize = layRect.Rect().Size();
    iTailItemSize =  (iOrientation == CEikScrollBar::EVertical?newSize.iHeight:newSize.iWidth);
        
    layout = AknLayoutScalable_Avkon::scroll_bg_pane_g2(varietyIndex); //middle
    layRect.LayoutRect(rect, layout.LayoutLine());
    newSize = layRect.Rect().Size();    
 //   iMidItemSize = (iOrientation == CEikScrollBar::EVertical?newSize.iHeight:newSize.iWidth) * 5;
    }

void CAknDoubleSpanScrollIndicator::DrawTiled(
        CWindowGc& aGc, const TRect& aRect, 
        CAknDoubleSpanScrollIndicatorItem *aIndicatorItem) const
    {
    if (aRect.IsEmpty())
        return;

    TRect headRect = aRect;
    TRect tailRect = aRect;
    TRect midRect = aRect;
    TInt midDrawLength;
    TSize midSize;
    if (iOrientation == CEikScrollBar::EVertical)
        {
        if ((iHeadItemSize + iTailItemSize) <= aRect.Height())
            {
            headRect.SetHeight(iHeadItemSize);
            tailRect.iTl.iY = tailRect.iBr.iY - iTailItemSize;
            }
        else
            {
            headRect.SetHeight((aRect.Height() >> 1));
            tailRect.iTl.iY = tailRect.iBr.iY - headRect.Height();
            }
        midRect.iTl.iY += headRect.Height();
        midRect.iBr.iY -= tailRect.Height();
        midDrawLength = midRect.Height();
        midSize.SetSize(midRect.Width(), iMidItemSize);
        }
    else
        {
        headRect.SetWidth( iHeadItemSize );
        tailRect.iTl.iX = tailRect.iBr.iX - iTailItemSize;

        midRect.iTl.iX += iHeadItemSize;
        midRect.iBr.iX -= iTailItemSize;
        midDrawLength = midRect.Width();
        midSize.SetSize(iMidItemSize, midRect.Height());
        }
   
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    CFbsBitmap *bmp = NULL; 
    CFbsBitmap *mask = NULL;
    AknsUtils::GetCachedMaskedBitmap(skin, aIndicatorItem->iTopId, bmp, mask);
    AknIconUtils::SetSize(bmp, headRect.Size(), EAspectRatioNotPreserved);
    AknIconUtils::SetSize(mask, headRect.Size(), EAspectRatioNotPreserved);
    aGc.BitBltMasked(headRect.iTl, bmp, TRect(TPoint(0, 0), headRect.Size()), mask, ETrue);
    
    AknsUtils::GetCachedMaskedBitmap(skin, aIndicatorItem->iMidId, bmp, mask);
    AknIconUtils::SetSize(bmp, midSize, EAspectRatioNotPreserved);
    AknIconUtils::SetSize(mask, midSize, EAspectRatioNotPreserved);

    TInt count = midDrawLength / iMidItemSize;
    TPoint destPos(midRect.iTl.iX, midRect.iTl.iY);
    TRect sourRect(TPoint(0, 0), bmp->SizeInPixels());
    for(TInt i = 0; i < count; i++)
        {
        aGc.BitBltMasked(destPos, bmp, sourRect, mask, ETrue);
        iOrientation == CEikScrollBar::EVertical?destPos.iY += iMidItemSize : destPos.iX += iMidItemSize;
        }
    iOrientation == CEikScrollBar::EVertical?sourRect.iBr.iY = midRect.Height() % iMidItemSize
                    :sourRect.iBr.iX = midRect.Width() % iMidItemSize;
    aGc.BitBltMasked(destPos, bmp, sourRect, mask, ETrue);

    AknsUtils::GetCachedMaskedBitmap(skin, aIndicatorItem->iBottomId, bmp, mask);
    AknIconUtils::SetSize(bmp, tailRect.Size(), EAspectRatioNotPreserved);
    AknIconUtils::SetSize(mask, tailRect.Size(), EAspectRatioNotPreserved);
    aGc.BitBltMasked(tailRect.iTl, bmp, TRect(TPoint(0, 0), tailRect.Size()), mask, ETrue);
    }

void CAknDoubleSpanScrollIndicator::CalculateRects()
    {
    iBackgroundRect = Rect();
    
    // 
    // sanity checks for values used in drawing   
    //
    TInt checkedScrollSpan    = iScrollSpan; // all items
    TInt checkedFocusPosition = iFocusPosition; // current item
    TInt checkedWindowSize    = iWindowSize; // number of visible items
    TInt checkedFieldPosition = iFieldPosition; // position in sub list
    TInt checkedFieldSize     = iFieldSize; // number of visible items in sub list
       
    CheckValues(checkedScrollSpan, 
        checkedFocusPosition, 
        checkedWindowSize, 
        checkedFieldPosition, 
        checkedFieldSize);
    
    TBool wasEmpty = iBackgroundRect.IsEmpty();
    TBool isEmpty = EFalse;

    // If span (max number of items) is zero, then draw only the background
    if ( checkedScrollSpan == 0 || ( checkedScrollSpan <= checkedWindowSize ) )
        {
        iBackgroundRect = TRect( 0, 0, 0, 0 );
        iHandleBackgroundRect = TRect(0,0,0,0);
        iHandleRect = TRect(0,0,0,0);
        iForceDrawBackground = ETrue; // to enable background drawing
        isEmpty = ETrue;
        }
    else
        {
        iForceDrawBackground = EFalse;
        }
    if ( wasEmpty != isEmpty || iForceDrawBackground )
        {
        DrawDeferred();
        }
    
    if ( isEmpty )
        {
        return;
        }

    // 
    // Transform values into pixels and rects.
    //
    TInt scrollBarHeightInPixels( 0 );
    
    if ( iOrientation == CEikScrollBar::EHorizontal )
        {
        scrollBarHeightInPixels = iBackgroundRect.Width();
        }
    else
        {
        scrollBarHeightInPixels = iBackgroundRect.Height();
        }
    
    // The code block below was probably used to prevent
    // a truncation-vs-rounding error from happening
    /*
    if ((checkedWindowSize > 0) && (checkedScrollSpan > 0))
        {
        if((checkedFocusPosition + checkedWindowSize) == checkedScrollSpan)
            windowSizeInPixels = scrollBarHeightInPixels - focusPositionInPixels;
        else
            windowSizeInPixels = scrollBarHeightInPixels*checkedWindowSize/checkedScrollSpan;
        }
    */
    
    TInt windowSizeInPixels = 
        Max( checkedWindowSize * scrollBarHeightInPixels / checkedScrollSpan,
             HandleBackgroundMinSizeInPixels() );
    
    TInt roomForMovementInSpan   = checkedScrollSpan - checkedWindowSize;
    TInt roomForMovementInPixels = 
        scrollBarHeightInPixels - windowSizeInPixels;    
    
    TInt focusPositionInPixels( 0 );
        
    if ( roomForMovementInSpan > 0 && roomForMovementInPixels > 0 )
        {
        focusPositionInPixels =
            checkedFocusPosition * roomForMovementInPixels /
            roomForMovementInSpan;
        }

    // If window would cover whole scrollbar, then modify 
    // it to leave the thumb little short from bottom
    TInt scrollBarHandleMaxSizeInPixels =  ScrollHandleMaxVisibleSizeInPixels();
    if (windowSizeInPixels >= scrollBarHeightInPixels)
        {
        windowSizeInPixels = scrollBarHandleMaxSizeInPixels;    
        }

    TBool doubleSpanInUse = (checkedFieldPosition >= 0) && (checkedFieldSize > 0);
    TInt minHandleBackgroundSize = 0;
    TInt fieldSizeInPixels = 0; // sub field size
    TInt fieldPositionInPixels = 0;
    if (doubleSpanInUse)
        {
        fieldSizeInPixels = windowSizeInPixels/checkedFieldSize;
        fieldPositionInPixels = windowSizeInPixels*checkedFieldPosition/checkedFieldSize;
        minHandleBackgroundSize = HandleBackgroundMinSizeInPixels();
        }
    else
        {
        minHandleBackgroundSize = HandleMinSizeInPixels();
        }
    
    TInt handleMinSize = HandleMinSizeInPixels();
    // Similar compensation for handle if double span is in use
    if (doubleSpanInUse && (fieldSizeInPixels < handleMinSize))
        {
        TInt extraPixels = 0;
        TInt extraPixelCompensationInterval = 0;
        TInt extraPixelCompensation = 0;
        extraPixels = handleMinSize - fieldSizeInPixels;
        extraPixelCompensationInterval = windowSizeInPixels/extraPixels;
        if (extraPixelCompensationInterval != 0)
            {
            extraPixelCompensation = fieldPositionInPixels/extraPixelCompensationInterval;
            if (extraPixelCompensation > handleMinSize)
                {
                extraPixelCompensation = handleMinSize;
                }
            }

        if ((fieldPositionInPixels - extraPixelCompensation) > 0)
            {
            fieldPositionInPixels -= extraPixelCompensation;
            }
        
        // Additional compensation at the end is sometimes needed as above compensation is not
        // always accurate because the fieldPositionInPixels is not anymore in "right" place. 
        if (checkedFieldPosition < (checkedFieldSize - 1))
            {           
            if ((fieldPositionInPixels + handleMinSize) >= windowSizeInPixels - 1)
                {
                fieldPositionInPixels = windowSizeInPixels - (handleMinSize + 2);
                }
            }            
        fieldSizeInPixels = handleMinSize;
        }
    
    
    // If orientation is horizontal, then rotate rects here first
    // 90 degrees. At the end of this function rotate them back again.
    if (iOrientation == CEikScrollBar::EHorizontal)
        {
        TRect original = iBackgroundRect;
        iBackgroundRect.iBr.iX = original.iTl.iX + original.Height();
        iBackgroundRect.iBr.iY = original.iTl.iY + original.Width();
        iHandleBackgroundRect = TRect(0,0,0,0);
        iHandleRect = TRect(0,0,0,0);
        }
    
    // handle background
    iHandleBackgroundRect = iBackgroundRect;
    iHandleBackgroundRect.iTl.iY += focusPositionInPixels;
    iHandleBackgroundRect.iBr.iY = iHandleBackgroundRect.iTl.iY + windowSizeInPixels; 
  
    if (iHandleBackgroundRect.iBr.iY > iBackgroundRect.iBr.iY)
        {
        iHandleBackgroundRect.iBr.iY = iBackgroundRect.iBr.iY;
        iHandleBackgroundRect.iTl.iY = iBackgroundRect.iBr.iY - windowSizeInPixels;
        }

    // fields
    iHandleRect= iHandleBackgroundRect;
    iHandleRect.iTl.iY += fieldPositionInPixels;
    iHandleRect.iBr.iY = iHandleRect.iTl.iY + fieldSizeInPixels;
    if (iHandleRect.iTl.iY < iHandleBackgroundRect.iTl.iY)
        {
        iHandleRect.iTl.iY = iHandleBackgroundRect.iTl.iY;
        }

    if (iHandleRect.iBr.iY > iHandleBackgroundRect.iBr.iY)
        {
        iHandleRect.iBr.iY = iHandleBackgroundRect.iBr.iY;
        }    

    // if double span is not used, set the handle to cover whole handle background area.
    if (!doubleSpanInUse)
        {
        iHandleRect.SetHeight(iHandleBackgroundRect.Height());
        }
        
    // check overflow 
    if (iHandleBackgroundRect.iBr.iY > iBackgroundRect.iBr.iY)
        {
        
        iHandleBackgroundRect.iBr.iY = iBackgroundRect.iBr.iY;
        iHandleBackgroundRect.iTl.iY = iBackgroundRect.iBr.iY - minHandleBackgroundSize;
        }
    if (iHandleBackgroundRect.iTl.iY < iBackgroundRect.iTl.iY)
        {
        iHandleBackgroundRect.iTl.iY = iBackgroundRect.iTl.iY;
        }

    // check overflow
    if (iHandleRect.iBr.iY > iHandleBackgroundRect.iBr.iY)
        {
        iHandleRect.iBr.iY = iHandleBackgroundRect.iBr.iY;
        iHandleRect.iTl.iY = iHandleBackgroundRect.iBr.iY - handleMinSize;
        }
    if (iHandleRect.iTl.iY < iHandleBackgroundRect.iTl.iY)
        {
        iHandleRect.iTl.iY = iHandleBackgroundRect.iTl.iY;
        }
    
    // If calculations were done to 90 degrees rotated rects, rotate those back here. 
    if (iOrientation == CEikScrollBar::EHorizontal)
        {
        TRect originalBackgroundRect = iBackgroundRect;
        iBackgroundRect.SetWidth(originalBackgroundRect.Height());
        iBackgroundRect.SetHeight(originalBackgroundRect.Width());
        
        TRect originalHandleBackgroundRect = iHandleBackgroundRect;
        iHandleBackgroundRect = iBackgroundRect;

        iHandleBackgroundRect.iTl.iX += originalHandleBackgroundRect.iTl.iY - originalBackgroundRect.iTl.iY;
        iHandleBackgroundRect.iBr.iX = iHandleBackgroundRect.iTl.iX + originalHandleBackgroundRect.Height();

        TRect originalHandleRect = iHandleRect;
        iHandleRect = iBackgroundRect;
 
        iHandleRect.iTl.iX += originalHandleRect.iTl.iY - originalBackgroundRect.iTl.iY;
        iHandleRect.iBr.iX = iHandleRect.iTl.iX + originalHandleRect.Height();
        }
    }


void CAknDoubleSpanScrollIndicator::CheckValues(TInt& aScrollSpan, TInt& aFocusPosition, TInt& aWindowSize, TInt& aFieldPosition, TInt& aFieldSize) const
    {
    // Scrollspan
    if (aScrollSpan <= 0)
        {
        // Default values, only background will be drawn
        aScrollSpan = 0; 
        aWindowSize = 0;
        aFocusPosition = 0;
        aFieldSize = 0;
        aFieldPosition = 0;
        return;
        }

    // Window size
    if (aWindowSize < 1)
        {
        aWindowSize = 1;
        }
    if (aWindowSize > aScrollSpan)
        {
        aWindowSize = aScrollSpan;
        }

    // FocusPosition
    if (aFocusPosition < 0)
        {
        aFocusPosition = 0;
        }
    if (aFocusPosition + aWindowSize > aScrollSpan)
        {
        aFocusPosition = aScrollSpan - aWindowSize;
        }

    // Field size & position
    if (aFieldSize <= 0)
        {
        aFieldSize = 0;
        aFieldPosition = 0;
        }
    else
        {
        // Field position
        if (aFieldPosition < 0)
            {
            aFieldPosition = 0;
            }
        if (aFieldPosition > aFieldSize - 1)
            {
            aFieldPosition = aFieldSize - 1;
            }

        }
    }


void CAknDoubleSpanScrollIndicator::SizeChanged()
    {
    TRect rect( Rect() );
    if(iOldRect != rect)
        {
        iOldRect = rect;        
        AknsUtils::RegisterControlPosition( this );
        CalculateRects();

        UpdateScrollBarLayout();
        
        if (IsVisible() & iOwnsWindow)
            DrawDeferred();
        }
    }

void CAknDoubleSpanScrollIndicator::SetIndicatorValues(TInt aScrollSpan, TInt aFocusPosition, TInt aWindowSize, TInt aFieldPosition, TInt aFieldSize)
    {
    // if nothing changed
    if((iScrollSpan == aScrollSpan) &&
    (iFocusPosition == aFocusPosition) &&
    (iWindowSize == aWindowSize) &&
    (iFieldPosition == aFieldPosition) &&
    (iFieldSize == aFieldSize))
        return;
    
    iScrollSpan = aScrollSpan;
    iFocusPosition = aFocusPosition;
    iWindowSize = aWindowSize;
    iFieldPosition = aFieldPosition;
    iFieldSize = aFieldSize;
    
    // Calculate the sizes for graphics
    CalculateRects();            
    if( iWindowSize > 0 )
        {   
        // layout handle graphics
        LayoutHandleGraphics();
        }
    }

TInt CAknDoubleSpanScrollIndicator::ScrollSpan()
    {
    return iScrollSpan;
    }

TInt CAknDoubleSpanScrollIndicator::FocusPosition()
    {
    return iFocusPosition;
    }

TInt CAknDoubleSpanScrollIndicator::WindowSize()
    {
    return iWindowSize;
    }

TInt CAknDoubleSpanScrollIndicator::FieldPosition()
    {
    return iFieldPosition;
    }

TInt CAknDoubleSpanScrollIndicator::FieldSize()
    {
    return iFieldSize;
    }

void CAknDoubleSpanScrollIndicator::SetTransparentBackground(TBool aTransparentBackground)
    {
    iTransparentBackground = aTransparentBackground;
    }

TBool CAknDoubleSpanScrollIndicator::TransparentBackground()
    {
    return iTransparentBackground;
    }

void CAknDoubleSpanScrollIndicator::HandleResourceChange(TInt aType)
    {
    if ( aType == KAknMessageFocusLost || KEikMessageUnfadeWindows == aType )
        {
        if( HandleHighlight() )
            {
            SetHandleHighlight(EFalse);
            DrawDeferred();
            }
        if( BackgroudHighlight() )
            {
        	SetBackgroudHighlight( EFalse );
            }
        
        }
    
    // SizeChanged handles this. The Scb is always layouted by its parent
    // if(aType == KEikDynamicLayoutVariantSwitch)

        
    CCoeControl::HandleResourceChange(aType);
    }

CAknDoubleSpanScrollIndicatorItem* CAknDoubleSpanScrollIndicator::LoadScrollIndicatorItemL(
        const TAknsItemID &aTopId,
        const TAknsItemID &aMidId,
        const TAknsItemID &aBottomId)
    {
    return CAknDoubleSpanScrollIndicatorItem::NewL(ETrue,
        aTopId, 0, 0,
        aMidId, 0, 0,
        aBottomId, 0, 0); 
    }


void CAknDoubleSpanScrollIndicator::CreateScrollBarItemsL()
    {
    // create items
    if(iOrientation == CEikScrollBar::EVertical)
        {
        iBackgroundBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollBgTop,
                KAknsIIDQsnCpScrollBgMiddle,
                KAknsIIDQsnCpScrollBgBottom);
        
        iHandleBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHandleTop,
                KAknsIIDQsnCpScrollHandleMiddle,
                KAknsIIDQsnCpScrollHandleBottom);
        
        
       
        if(AknLayoutUtils::PenEnabled())
            {
            iHighlightBackgroundBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHandleBgTop,
                KAknsIIDQsnCpScrollHandleBgMiddle,
                KAknsIIDQsnCpScrollHandleBgBottom);
            
            iHighlightHandleBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHandleTopPressed,
                KAknsIIDQsnCpScrollHandleMiddlePressed,
                KAknsIIDQsnCpScrollHandleBottomPressed);
            }
        }
    else
        {
        iBackgroundBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHorizontalBgTop,
                KAknsIIDQsnCpScrollHorizontalBgMiddle,
                KAknsIIDQsnCpScrollHorizontalBgBottom);
        
        iHandleBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHorizontalHandleTop,
                KAknsIIDQsnCpScrollHorizontalHandleMiddle,
                KAknsIIDQsnCpScrollHorizontalHandleBottom);

        
        
        if(AknLayoutUtils::PenEnabled())
            {
            //Handle background bar image missing....
            /*
            iHandleBackgroundBar = LoadScrollIndicatorItem(
                KAknsIIDQsnCpScrollHorizontalHandleBgTop,
                KAknsIIDQsnCpScrollHorizontalHandleBgMiddle,
                KAknsIIDQsnCpScrollHorizontalHandleBgBottom);
            */
            
            iHighlightHandleBar = LoadScrollIndicatorItemL(
                KAknsIIDQsnCpScrollHorizontalHandleTopPressed,
                KAknsIIDQsnCpScrollHorizontalHandleMiddlePressed,
                KAknsIIDQsnCpScrollHorizontalHandleBottomPressed);
            }
        }    
    }

TInt CAknDoubleSpanScrollIndicator::IndicatorWidth()
    {
    TAknWindowComponentLayout layout;
    
    if(iOrientation == CEikScrollBar::EHorizontal)
        layout = AknLayoutScalable_Avkon::scroll_pane(1);
    else
        layout = AknLayoutScalable_Avkon::scroll_pane(0);
    
    TAknLayoutRect layRect;
    TRect mainpaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainpaneRect );
    layRect.LayoutRect(mainpaneRect, layout.LayoutLine());
    
    if(iOrientation == CEikScrollBar::EHorizontal)
        return layRect.Rect().Height();
    else
        return layRect.Rect().Width();
    }

TInt CAknDoubleSpanScrollIndicator::ScrollHandleMaxVisibleSizeInPixels()
    {
    TRect scbRect = Rect();
    if ( iOrientation == CEikScrollBar::EHorizontal )
        scbRect.SetRect(scbRect.iTl, TSize(scbRect.Height(), scbRect.Width()));
    
    TAknLayoutRect layRect;
    TAknWindowComponentLayout layout = AknLayoutScalable_Avkon::aid_size_max_handle();
    layRect.LayoutRect(scbRect, layout.LayoutLine());
    return layRect.Rect().Height();
    }

TInt CAknDoubleSpanScrollIndicator::HandleBackgroundMinSizeInPixels()
    {
    return HandleMinSizeInPixels();
    }

TInt CAknDoubleSpanScrollIndicator::HandleMinSizeInPixels()
    {
    // We have the minimum size as aid value, do not layout to the handle layout as it is not correct
    // on behalf of height argument (not set as maximum)
    TRect scbRect = Rect();
    if ( iOrientation == CEikScrollBar::EHorizontal )
        scbRect.SetRect(scbRect.iTl, TSize(scbRect.Height(), scbRect.Width()));
    
    TAknLayoutRect layRect;
    TAknWindowComponentLayout layout = AknLayoutScalable_Avkon::aid_size_min_handle();
    layRect.LayoutRect(scbRect, layout.LayoutLine());
    
    return layRect.Rect().Height();
    }


void CAknDoubleSpanScrollIndicator::SetAsWindowOwning(TBool aOwnsWindow)
    {
    iOwnsWindow = aOwnsWindow;
    }
    
void CAknDoubleSpanScrollIndicator::SetDrawBackgroundState(TBool aDraw)
    {
    iDrawBackground = aDraw;
    }
    
TBool CAknDoubleSpanScrollIndicator::DrawBackgroundState()
    {
    return iDrawBackground;
    }


void CAknDoubleSpanScrollIndicator::DrawBackground() const
    {
    CWindowGc& gc=SystemGc();
    TPoint pos = Position();
    TRect rect = Rect();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    
    if(!iTransparentBackground)
        {
        if (iOwnsWindow ) // owns window
            {
            // Redraw the background to bitmap if the skin or the size is changed.
            // Note that the indicator itself is not window owning but the actual window owning 
            // component is the scrollbar class, therefore the window may be in different position
            // and size than the indicator itself
            RWindow& win = Window();
            TRect bmpRect(win.Position() + pos, rect.Size()); // There may be an arrow on top of scb

            AknsDrawUtils::DrawBackground( skin, cc, NULL, gc,
                rect.iTl, bmpRect, KAknsDrawParamNoClearUnderImage );
            }
        else             //SB is non-window-owning
            {
            AknsDrawUtils::Background( skin, cc, this, gc, rect, 
                    KAknsDrawParamNoClearUnderImage );
            }
        }
    }

void CAknDoubleSpanScrollIndicator::LayoutHandleGraphics()
    {
    
    // We layout the handle middle graphics here according to the given inidcator values
    TRect rect = Rect();
    
    if (!iHandleBar || rect.IsEmpty())
        return;
    
    TInt varietyIndex = 0;
    TInt varietyIndexForHandle = 0;
    if (iOrientation == CEikScrollBar::EHorizontal)
        {        
        varietyIndex = 1;
        varietyIndexForHandle = 2;
        }
    
    TAknLayoutRect layRect;
    TAknWindowComponentLayout // layout handle bottom & top as they do not scale according to handle size
    layout = AknLayoutScalable_Avkon::scroll_handle_pane(varietyIndexForHandle); // handle (the shadow if two handles)
    layRect.LayoutRect(rect, layout.LayoutLine());
    layout = AknLayoutScalable_Avkon::scroll_handle_focus_pane(varietyIndex); // focus handle
    // The horizontal data for focus handle is missing so switch the values from the vertical data
    TAknWindowLineLayout layoutLine = layout.LayoutLine();
    if (iOrientation == CEikScrollBar::EHorizontal)
        {
        TInt height = layoutLine.iH;
        TInt width = layoutLine.iW;
        layoutLine.iW = height;
        layoutLine.iH = width;
        }
    layRect.LayoutRect(layRect.Rect(), layoutLine);
    rect = layRect.Rect(); // parent rect is now the focus handle
    
    // the retangle includes the variated length of the middle, 
    // the top and bottom graphics must subtracted from the value
    
    // do not change the handle retangle, the full size is needed in drawing
    // set the width or height to be correct
    if (iOrientation == CEikScrollBar::EVertical)
        {
        iHandleRect.iTl.iX = rect.iTl.iX;
        iHandleRect.iBr.iX = rect.iBr.iX;
        }
    else
        {
        iHandleRect.iTl.iY = rect.iTl.iY;
        iHandleRect.iBr.iY = rect.iBr.iY;
        }
    }

TInt CAknDoubleSpanScrollIndicator::GetCurrentThumbSpanInPixels()
    {
    return ( iOrientation == CEikScrollBar::EVertical ?
             iHandleBackgroundRect.Height() :
             iHandleBackgroundRect.Width() );
    }
    
TInt CAknDoubleSpanScrollIndicator::GetCurrentThumbPositionInPixels()
    {
    TInt ret;
    
    if ( iOrientation == CEikScrollBar::EHorizontal )
        {
        ret = iHandleBackgroundRect.iTl.iX -
            iBackgroundRect.iTl.iX;
        }
    else
        {
        ret = iHandleBackgroundRect.iTl.iY -
            iBackgroundRect.iTl.iY;
        }
        
    return ret;
    }

void CAknDoubleSpanScrollIndicator::SetHandleHighlight( TBool aHandleHighlight )
    {
    // This does nothing in non-touch
    iHandleHighlight = aHandleHighlight;
    SetBackgroudHighlight(aHandleHighlight);
    }
    
TBool CAknDoubleSpanScrollIndicator::HandleHighlight() const
    {
    return iHandleHighlight;
    }
    

 void CAknDoubleSpanScrollIndicator::SetBackgroudHighlight( TBool aBackgroudHighlight )
    {
    // This does nothing in non-touch
    iBackgroundHighlight = aBackgroudHighlight;
    }
    
TBool CAknDoubleSpanScrollIndicator::BackgroudHighlight() const
    {
    return iBackgroundHighlight;
    }

