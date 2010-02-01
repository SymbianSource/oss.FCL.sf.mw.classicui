/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include "HgScrollbar.h"
#include <ganes/HgScrollbarObserverIface.h>
#include "HgConstants.h"

#include <AknsUtils.h>
#include <AknUtils.h>
#include <AknsDrawUtils.h>

#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>

#include <bitstd.h>
#include <gulicon.h>

#include <AknIconUtils.h>
#include <AknsUtils.h>
#include <AknsConstants.h>
#include <w32std.h>

// -----------------------------------------------------------------------------
// CHgScrollbar::NewL()
// -----------------------------------------------------------------------------
//
CHgScrollbar* CHgScrollbar::NewL( MHgScrollbarObserver& aObserver )
    {
    CHgScrollbar* self = new (ELeave) CHgScrollbar( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::~CHgScrollbar()
// -----------------------------------------------------------------------------
//
CHgScrollbar::~CHgScrollbar()
    {
    delete iScrollbarBg;
    delete iScrollbarHandle;
    delete iScrollbarHandleBg;
    delete iScrollbarBgSelected;
    delete iScrollbarHandleSelected;
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::CHgScrollbar()
// -----------------------------------------------------------------------------
//
CHgScrollbar::CHgScrollbar( MHgScrollbarObserver& aObserver )
    : iObserver( aObserver )
    {
    
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::ConstructL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::SetScrollbarL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::InitScrollBarL(
        TRect aRect,
        TSize aTotalSize,
        TSize aViewSize,
        TBool aLandscapeScrolling )
    {
    if( iTotalSize == aTotalSize 
            && iViewSize == aViewSize 
            && iLandscapeScrolling == aLandscapeScrolling )
        {
        return;
        }
    
    TInt variety = aLandscapeScrolling ? 1 : 0;
    
    TAknLayoutRect layout;
    layout.LayoutRect(aRect, AknLayoutScalable_Avkon::scroll_pane( variety ));
    iScrollbarRect = layout.Rect();
    
    if((aTotalSize.iHeight <= aViewSize.iHeight && !aLandscapeScrolling)
            || (aTotalSize.iWidth <= aViewSize.iWidth && aLandscapeScrolling) )
        {
        iTotalSize = aViewSize;
        iStatic = ETrue;
        }
    else
        {
        iTotalSize = aTotalSize;
        iStatic = EFalse;
        }

    TBool viewChanged = iViewSize != aViewSize;
    
    iViewSize = aViewSize;
    iLandscapeScrolling = aLandscapeScrolling;
    iHandlePosition.SetXY(0,0);

    if(iLandscapeScrolling)
        {
        iTotalLength = iTotalSize.iWidth - iViewSize.iWidth;
        }
    else
        {
        iTotalLength = iTotalSize.iHeight - iViewSize.iHeight;
        }

    InitIconsL( viewChanged );    
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::SetViewPosition()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::SetViewPosition( TPoint aPosition )
    {
    if(!iStatic)
        {
        if(iLandscapeScrolling)
            {
            if (AknLayoutUtils::LayoutMirrored())
                {
                iHandlePosition.iX = (iScrollLength) * (1.0 - aPosition.iX / TReal(iTotalLength));
                }
            else
                {
                iHandlePosition.iX = (iScrollLength) * (aPosition.iX / TReal(iTotalLength));            
                }
            }
        else
            {
            iHandlePosition.iY = (iScrollLength) * (aPosition.iY / TReal(iTotalLength));
            }
        CheckHandlePosition( EFalse );
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::HandlePointerEventL()
// -----------------------------------------------------------------------------
//
TBool CHgScrollbar::HandlePointerEventL( const TPointerEvent& aEvent )
    {
    return HandleScrollBarPointerEvent( aEvent );
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::HandleScrollBarPointerEvent()
// -----------------------------------------------------------------------------
//
TBool CHgScrollbar::HandleScrollBarPointerEvent( const TPointerEvent& aEvent )
    {
    TBool ret = EFalse;
    // Quick and dirty hack, remove when logic for fetching the correct drag rect is available
    TRect dragArea( iScrollbarRect );
    dragArea.iBr.iX += KScrollAreaOffset; 
    dragArea.iTl.iX -= KScrollAreaOffset;

    // Start drag
    if( aEvent.iType == TPointerEvent::EButton1Down && dragArea.Contains(aEvent.iPosition))
        {
        TSize size(iHandleSize);
        size.iWidth += KScrollAreaOffset*2;
        TRect handleRect( dragArea.iTl + iHandlePosition, size );
        iDragging = handleRect.Contains( aEvent.iPosition );
        iPrevDrag = aEvent.iPosition;
        iHandler = ret = ETrue;
        CheckHandlePosition( !iStatic );
        }

    // Drag
    if( aEvent.iType == TPointerEvent::EDrag && iHandler)
        {
        if( iDragging )
            {
            if(iLandscapeScrolling)
                {
                iHandlePosition.iX -= iPrevDrag.iX - aEvent.iPosition.iX;
                }
            else
                {
                iHandlePosition.iY -= iPrevDrag.iY - aEvent.iPosition.iY;
                }
            CheckHandlePosition( !iStatic );
            
            iPrevDrag = aEvent.iPosition;
            }
        ret = ETrue;
        }

    // End drag
    if( aEvent.iType == TPointerEvent::EButton1Up && iHandler)
        {
        if(!iDragging)
            {
            TBool below = iLandscapeScrolling ? 
                    aEvent.iPosition.iX > iHandlePosition.iX 
                    : aEvent.iPosition.iY > iHandlePosition.iY;
            iHandlePosition += below ? iHandleSize.AsPoint() : -iHandleSize.AsPoint();
            }
        CheckHandlePosition( !iStatic );
        iHandler = iDragging = EFalse; 
        ret = ETrue;
        }

    return ret;    
    }


// -----------------------------------------------------------------------------
// CHgScrollbar::Draw()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::Draw( CWindowGc& aGc )
    {
    DrawScrollbar( aGc );
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::DrawScrollbar()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::DrawScrollbar( CWindowGc& aGc )
    {
    if(iScrollbarBg && iScrollbarHandle && iScrollbarHandleBg)
        {
        if(iHandler && !iStatic)
            {
            aGc.BitBltMasked(iScrollbarRect.iTl, 
                    iScrollbarHandleBg->Bitmap(),
                    iScrollbarHandleBg->Bitmap()->SizeInPixels(),
                    iScrollbarHandleBg->Mask(),
                    EFalse);
            
            aGc.BitBltMasked(iScrollbarRect.iTl + iHandlePosition, 
                    iScrollbarHandleSelected->Bitmap(),
                    iScrollbarHandleSelected->Bitmap()->SizeInPixels(),
                    iScrollbarHandleSelected->Mask(),
                    EFalse);
            }
        else
            {
            aGc.BitBltMasked(iScrollbarRect.iTl, 
                    iScrollbarBg->Bitmap(),
                    iScrollbarBg->Bitmap()->SizeInPixels(),
                    iScrollbarBg->Mask(),
                    EFalse);
            
            aGc.BitBltMasked(iScrollbarRect.iTl + iHandlePosition, 
                    iScrollbarHandle->Bitmap(),
                    iScrollbarHandle->Bitmap()->SizeInPixels(),
                    iScrollbarHandle->Mask(),
                    EFalse);
            }
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::CheckHandlePosition()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::CheckHandlePosition( TBool aReportChange )
    {

    if(iLandscapeScrolling)
        {
        iHandlePosition.iY = 0;
        if(iHandlePosition.iX < 0 )
            iHandlePosition.iX = 0;
        if(iHandlePosition.iX > iScrollLength)
            iHandlePosition.iX = iScrollLength;
        }
    else
        {
        iHandlePosition.iX = 0;
        if(iHandlePosition.iY < 0 )
            iHandlePosition.iY = 0;
        if(iHandlePosition.iY > iScrollLength)
            iHandlePosition.iY = iScrollLength;
        }
    if( aReportChange )
        {
        TPoint pos (iViewSize.iWidth/2, iViewSize.iHeight/2);
        if(iLandscapeScrolling)
            {
            if (AknLayoutUtils::LayoutMirrored())
                {
                pos.iX += (1.0 - iHandlePosition.iX / TReal(iScrollLength)) * (iTotalLength);
                }
            else
                {
                pos.iX += (iHandlePosition.iX / TReal(iScrollLength)) * (iTotalLength);            
                }
            }
        else
            {
            pos.iY += (iHandlePosition.iY / TReal(iScrollLength)) * (iTotalLength);
            }
        
        iObserver.ScrollBarPositionChanged( pos );
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::InitIconsL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::InitIconsL( TBool aInitBgIcons )
    {
    if(aInitBgIcons)
        {
        delete iScrollbarBg; iScrollbarBg = NULL;
        delete iScrollbarBgSelected; iScrollbarBgSelected = NULL;
        delete iScrollbarHandleBg; iScrollbarHandleBg = NULL;
    
        CreateIconL(iScrollbarBg, iScrollbarRect.Size());
        CreateIconL(iScrollbarBgSelected, iScrollbarRect.Size());
        CreateIconL(iScrollbarHandleBg, iScrollbarRect.Size());
        }
    
    TReal xFactor = iScrollbarRect.Width()/TReal(iTotalSize.iWidth);
    TReal yFactor = iScrollbarRect.Height()/TReal(iTotalSize.iHeight); 
    
    iHandleSize = TSize ( iViewSize.iWidth * xFactor, iViewSize.iHeight * yFactor );

    if(iLandscapeScrolling)
        {
        TInt min = 2*iHandleSize.iHeight;
        if( iHandleSize.iWidth < min )
            {
            iHandleSize.iWidth = min;
            }
        iScrollLength = iScrollbarRect.Width() - iHandleSize.iWidth;
        }
    else
        {
        TInt min = 2*iHandleSize.iWidth;
        if( iHandleSize.iHeight < min )
            {
            iHandleSize.iHeight = min;
            }
        iScrollLength = iScrollbarRect.Height() - iHandleSize.iHeight;
        }
    
    delete iScrollbarHandle; iScrollbarHandle = NULL;
    delete iScrollbarHandleSelected; iScrollbarHandleSelected = NULL;

    CreateIconL(iScrollbarHandle, iHandleSize );
    CreateIconL(iScrollbarHandleSelected, iHandleSize );
    
    if( iLandscapeScrolling )
        {
        if( aInitBgIcons )
            {
            DrawIconL( *iScrollbarBg, 
                    KAknsIIDQsnCpScrollHorizontalBgTop, 
                    KAknsIIDQsnCpScrollHorizontalBgMiddle, 
                    KAknsIIDQsnCpScrollHorizontalBgBottom );
    
            // TODO, check if this is needed.
    //        DrawIconL( *iScrollbarHandleBg, 
    //                KAknsIIDQsnCpScrollHorizontalHandleBgTop, 
    //                KAknsIIDQsnCpScrollHorizontalHandleBgMiddle, 
    //                KAknsIIDQsnCpScrollHorizontalHandleBgBottom );
            
            DrawIconL( *iScrollbarBgSelected, 
                    KAknsIIDQsnCpScrollHorizontalBgTopPressed, 
                    KAknsIIDQsnCpScrollHorizontalBgMiddlePressed, 
                    KAknsIIDQsnCpScrollHorizontalBgBottomPressed );
            }
        
        DrawIconL( *iScrollbarHandle, 
                KAknsIIDQsnCpScrollHorizontalHandleTop, 
                KAknsIIDQsnCpScrollHorizontalHandleMiddle, 
                KAknsIIDQsnCpScrollHorizontalHandleBottom);

        DrawIconL( *iScrollbarHandleSelected, 
                KAknsIIDQsnCpScrollHorizontalHandleTopPressed, 
                KAknsIIDQsnCpScrollHorizontalHandleMiddlePressed, 
                KAknsIIDQsnCpScrollHorizontalHandleBottomPressed );        
        }
    else
        {
        if(aInitBgIcons)
            {
            DrawIconL( *iScrollbarBg, 
                    KAknsIIDQsnCpScrollBgTop, 
                    KAknsIIDQsnCpScrollBgMiddle, 
                    KAknsIIDQsnCpScrollBgBottom );
            
            DrawIconL( *iScrollbarHandleBg, 
                    KAknsIIDQsnCpScrollHandleBgTop, 
                    KAknsIIDQsnCpScrollHandleBgMiddle, 
                    KAknsIIDQsnCpScrollHandleBgBottom );
            
            DrawIconL( *iScrollbarBgSelected, 
                    KAknsIIDQsnCpScrollBgTopPressed, 
                    KAknsIIDQsnCpScrollBgMiddlePressed, 
                    KAknsIIDQsnCpScrollBgBottomPressed );
            }
        
        DrawIconL( *iScrollbarHandle, 
                KAknsIIDQsnCpScrollHandleTop, 
                KAknsIIDQsnCpScrollHandleMiddle, 
                KAknsIIDQsnCpScrollHandleBottom);

        DrawIconL( *iScrollbarHandleSelected, 
                KAknsIIDQsnCpScrollHandleTopPressed, 
                KAknsIIDQsnCpScrollHandleMiddlePressed, 
                KAknsIIDQsnCpScrollHandleBottomPressed );        
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::CreateIconL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::CreateIconL( CGulIcon*& aIcon, TSize aSize)
    {
    CFbsBitmap* bmap = new (ELeave) CFbsBitmap;
    CleanupStack::PushL( bmap );
    User::LeaveIfError( bmap->Create( aSize , EColor64K));
    
    CFbsBitmap* mask = new (ELeave) CFbsBitmap;
    CleanupStack::PushL( mask );
    User::LeaveIfError( mask->Create( aSize , EGray256));
    
    aIcon = CGulIcon::NewL( bmap, mask );
    
    CleanupStack::Pop(2, bmap);
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::DrawIconL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::DrawIconL( CGulIcon& aIcon,
        const TAknsItemID& aTop,
        const TAknsItemID& aMiddle,
        const TAknsItemID& aBottom )
    {
    TRect rect;
    TSize iconSize(aIcon.Bitmap()->SizeInPixels());
    TSize tSize;
    TPoint point(0,0);
    if(iLandscapeScrolling)
        {
        tSize.SetSize(iconSize.iHeight, iconSize.iHeight);
        }
    else
        {
        tSize.SetSize(iconSize.iWidth, iconSize.iWidth);
        }
    
    // TOP
    rect.SetRect(point, tSize);
    DrawBitmapL( aIcon, aTop, rect );

    // MIDDLE
    TSize middlesize(iconSize);
    if(iLandscapeScrolling)
        {
        point.iX = tSize.iWidth;
        middlesize.iWidth -= 2*tSize.iWidth;
        }
    else
        {
        point.iY = tSize.iHeight;
        middlesize.iHeight -= 2*tSize.iHeight;
        }
    rect.SetRect(point, middlesize);
    DrawBitmapL( aIcon, aMiddle, rect);
    
    // BOTTOM
    point = iconSize.AsPoint()-tSize;
    rect.SetRect(point, tSize);
    DrawBitmapL( aIcon, aBottom, rect );
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::DrawBitmapL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::DrawBitmapL( CGulIcon& aIcon,
        const TAknsItemID& aItem,
        const TRect& aDestRect )
    {
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    TRAP_IGNORE( AknsUtils::CreateIconL(AknsUtils::SkinInstance(), aItem, bitmap, mask, KNullDesC, -1, -1); )

    if(!bitmap)
        {
        AknsUtils::CreateIconL(AknsUtils::SkinInstance(), aItem, bitmap, KNullDesC, -1);        
        }
    
    AknIconUtils::SetSize(bitmap, aDestRect.Size(), EAspectRatioNotPreserved);
    ScaleBitmapL(aDestRect, aIcon.Bitmap(), bitmap);
    
    if(mask)
        {
        AknIconUtils::SetSize(mask, aDestRect.Size(), EAspectRatioNotPreserved);
        ScaleBitmapL(aDestRect, aIcon.Mask(), mask);
        }
    
    delete bitmap; bitmap = NULL;
    delete mask; mask = NULL;
    }


// -----------------------------------------------------------------------------
// CHgScrollbar::ScaleBitmapL()
// -----------------------------------------------------------------------------
//
void CHgScrollbar::ScaleBitmapL( const TRect& aDestRect,
        CFbsBitmap* aDest,
        const CFbsBitmap* aSrc)
    {
    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(aDest);
    CleanupStack::PushL(device);

    CFbsBitGc* gc = NULL;
    User::LeaveIfError(device->CreateContext(gc));
    CleanupStack::PushL(gc);
    
    gc->DrawBitmap(aDestRect, aSrc);
    
    CleanupStack::PopAndDestroy(2, device);
    }

// -----------------------------------------------------------------------------
// CHgScrollbar::ScrollbarBg()
// -----------------------------------------------------------------------------
//
const CGulIcon* CHgScrollbar::ScrollbarBg() const
    {
    return iScrollbarBg;
    }   


const CGulIcon* CHgScrollbar::ScrollbarHandleBg() const
    {
    return iScrollbarHandleBg;
    }

const CGulIcon* CHgScrollbar::ScrollbarHandle() const
    {
    return iScrollbarHandle;
    }

const CGulIcon* CHgScrollbar::ScrollbarBgSelected() const
    {
    return iScrollbarBgSelected;
    }

const CGulIcon* CHgScrollbar::ScrollbarHandleSelected() const
    {
    return iScrollbarHandleSelected;
    }

const TRect& CHgScrollbar::ScrollbarRect() const
    {
    return iScrollbarRect;
    }

const TPoint& CHgScrollbar::HandlePosition() const
    {
    return iHandlePosition;
    }

TBool CHgScrollbar::IsStatic() const
    {
    return iStatic;
    }

TBool CHgScrollbar::IsDragging() const
    {
    return iDragging;
    }

TBool CHgScrollbar::Handler() const
    {
    return iHandler;
    }

void CHgScrollbar::Reset()
    {
    iHandler = iDragging = EFalse; 
    }

// End of file
