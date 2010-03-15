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

// INCLUDE FILES

#include "HgVgScrollBar.h"
#include "HgVgDrawBuffer.h"
#include "HgVgHelper.h"
#include "HgScrollbar.h"
#include <VG/vgu.h>
#include <gulicon.h>



// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CHgVgScrollBar::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHgVgScrollBar* CHgVgScrollBar::NewL( MHgScrollbarObserver& aObserver, 
        TRect aScrollbarRect,
                    TSize aTotalSize,
                    TSize aViewSize,
                    TBool aLandscapeScrolling,
                    CHgScroller::THgScrollBarType aScrollBarType )
    {
    CHgVgScrollBar* self = new ( ELeave ) CHgVgScrollBar( ); 
    CleanupStack::PushL (self );
    self->ConstructL( aObserver, aScrollbarRect, aTotalSize, aViewSize, aLandscapeScrolling, aScrollBarType );
    CleanupStack::Pop ( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgVgScrollBar::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgVgScrollBar::ConstructL ( MHgScrollbarObserver& aObserver, TRect aScrollbarRect,
        TSize aTotalSize,
        TSize aViewSize,
        TBool aLandscapeScrolling,
        CHgScroller::THgScrollBarType aScrollBarType )
    {
    ResizeL(aObserver, aScrollbarRect, aTotalSize, aViewSize, aLandscapeScrolling, 
            aScrollBarType);
    
    CreateImagesL();
    }


// -----------------------------------------------------------------------------
// CHgVgScrollBar::CreateImagesL()
// -----------------------------------------------------------------------------
//
void CHgVgScrollBar::CreateImagesL()
    {
    if(!iScrollbar->IsStatic())
        {
        iScrollbarBg = HgVgHelper::CreateVgImageFromIconL(*iScrollbar->ScrollbarBg());
        iScrollbarBgSelected = HgVgHelper::CreateVgImageFromIconL(*iScrollbar->ScrollbarBgSelected());
        iScrollbarHandle = HgVgHelper::CreateVgImageFromIconL(*iScrollbar->ScrollbarHandle());
        iScrollbarHandleSelected = HgVgHelper::CreateVgImageFromIconL(*iScrollbar->ScrollbarHandleSelected());
        //iScrollbarHandleBg = HgVgHelper::CreateVgImageFromIconL(iScrollbar->ScrollbarHandleBg());
        }
    }


// -----------------------------------------------------------------------------
// CHgVgScrollBar::CHgVgMediaWall()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgVgScrollBar::CHgVgScrollBar(  ) : 
iEnabled(ETrue)
    {
    }
        
// -----------------------------------------------------------------------------
// CHgVgScrollBar::~CHgVgScrollBar()
// Destructor.
// -----------------------------------------------------------------------------
//
CHgVgScrollBar::~CHgVgScrollBar ( )
    {

    vgDestroyImage(iScrollbarBg);
    vgDestroyImage(iScrollbarBgSelected);
    vgDestroyImage(iScrollbarHandle);
    vgDestroyImage(iScrollbarHandleSelected);
    //vgDestroyImage(iScrollbarHandleBg);
    
    delete iScrollbar;
    
    }


void CHgVgScrollBar::SetViewPosition( TPoint aPosition )
    {
    iScrollbar->SetViewPosition(aPosition);
    }

TBool CHgVgScrollBar::HandlePointerEventL( const TPointerEvent& aEvent )
    {
    if (!iEnabled)
        return EFalse;
    
    return iScrollbar->HandlePointerEventL(aEvent);
    }

void CHgVgScrollBar::Draw(const TRect& aWindowRect, TReal aAlpha) const
    {
    if (!iEnabled || iScrollbar->IsStatic())
        return;
    
    TRect scrollbarRect = iScrollbar->ScrollbarRect();
    TPoint handlePosition = iScrollbar->HandlePosition();
    const CGulIcon* scrollbarBg = iScrollbar->ScrollbarBg();
    const CGulIcon* scrollbarBgSelected = iScrollbar->ScrollbarBgSelected();
    const CGulIcon* scrollbarHandle = iScrollbar->ScrollbarHandle();
    const CGulIcon* scrollbarHandleSelected = iScrollbar->ScrollbarHandleSelected();
    const CGulIcon* scrollbarHandleBg = iScrollbar->ScrollbarHandleBg();
    
    if(scrollbarBg && scrollbarHandle && scrollbarHandleBg)
        {
        if(iScrollbar->Handler() && !iScrollbar->IsStatic())
            {
            DrawImage(scrollbarRect.iTl,
                    iScrollbarBgSelected, 
                    scrollbarBgSelected->Bitmap()->SizeInPixels(), aWindowRect, aAlpha);
            
            DrawImage(scrollbarRect.iTl + handlePosition, 
                    iScrollbarHandleSelected,
                    scrollbarHandleSelected->Bitmap()->SizeInPixels(), aWindowRect, aAlpha);
            }
        else
            {
            DrawImage(scrollbarRect.iTl, 
                    iScrollbarBg,
                    scrollbarBg->Bitmap()->SizeInPixels(), aWindowRect, aAlpha);
            
            DrawImage(scrollbarRect.iTl + handlePosition,
                    iScrollbarHandleBg,
                    scrollbarHandleBg->Bitmap()->SizeInPixels(), aWindowRect, aAlpha);

            DrawImage(scrollbarRect.iTl + handlePosition, 
                    iScrollbarHandle,
                    scrollbarHandle->Bitmap()->SizeInPixels(), aWindowRect, aAlpha);
            }
        }    
    }

void CHgVgScrollBar::DrawImage(const TPoint& aPosition, VGImage aImage, 
        const TSize& /*aSize*/, const TRect& aWindowRect, TReal aAlpha) const
    {
    TRgb color(255, 255, 255, aAlpha * 255.0f);
    HgVgHelper::DrawImageColorized(aImage, color, aPosition, aWindowRect, EFalse, iLandscape);
    }

TBool CHgVgScrollBar::IsEnabled() const
    {
    return iEnabled;
    }

void CHgVgScrollBar::SetEnabled(TBool aEnabled)
    {
    iEnabled = aEnabled;
    }

void CHgVgScrollBar::ResizeL(
        MHgScrollbarObserver& aObserver, 
        TRect aScrollbarRect,
        TSize aTotalSize,
        TSize aViewSize,
        TBool aLandscapeScrolling,
        CHgScroller::THgScrollBarType /*aScrollBarType */)
    {
    iScrollbar = CHgScrollbar::NewL(aObserver);

    iScrollbar->InitScrollBarL(aScrollbarRect, aTotalSize, aViewSize, aLandscapeScrolling);    
    }

void CHgVgScrollBar::EnableLandscapeRendering(TBool aEnabled)
{
    iLandscape = aEnabled;
}


// End of File
