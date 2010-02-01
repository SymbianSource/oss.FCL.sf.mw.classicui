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
#include <ganes/HgScrollerWithTitle.h>
#include <ganes/HgDoubleGraphicList.h>
#include <ganes/HgDoubleTextList.h>
#include <ganes/HgSingleGraphicList.h>
#include <ganes/HgSingleLargeList.h>
#include <ganes/HgSingleTextList.h>
#include <ganes/HgSingleTextListWithIcon.h>
#include <ganes/HgGrid.h>
#include <ganes/HgItem.h>

#include "HgConstants.h"
#include "HgLayoutData.h"

#include <ganes.mbg>

#include <AknIconUtils.h>
#include <avkon.mbg>
#include <AknsDrawUtils.h>
#include <touchfeedback.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknLayout2ScalableDef.h>

using namespace AknLayoutScalable_Avkon;


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::NewL()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgScrollerWithTitle* CHgScrollerWithTitle::NewL(
        const TRect& aRect, 
        TInt aItemCount, 
        THgScrollerType aScrollerType,
        CGulIcon* aDefaultIcon )
    {
    CHgScrollerWithTitle* self = new (ELeave) CHgScrollerWithTitle();
    CleanupStack::PushL( self );
    self->ConstructL( aRect, aItemCount, aScrollerType, aDefaultIcon );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHgScrollerWithTitle::ConstructL (const TRect& aRect,
        TInt aItemCount, 
        THgScrollerType aScrollerType,
        CGulIcon* aDefaultIcon )
    {
    // Create a window for this application view
    CreateWindowL ( );

    switch( aScrollerType )
        {
        case EHgScrollerDoubleGraphicList:
            {
            iScroller = 
                CHgDoubleGraphicList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerDoubleTextList:
            {
            iScroller = 
                CHgDoubleTextList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerSingleGraphicList:
            {
            iScroller = 
                CHgSingleGraphicList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerSingleLargeList:
            {
            iScroller = 
                CHgSingleLargeList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerSingleTextList:
            {
            iScroller = 
                CHgSingleTextList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerGrid:
            {
            iScroller = 
                CHgGrid::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerSingleTextListWithIcon:
            {
            iScroller = 
                CHgSingleTextListWithIcon::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        case EHgScrollerDoubleGraphicListFlat:
            {
            iScroller = 
                CHgDoubleGraphicList::NewL( aRect, aItemCount, aDefaultIcon );
            break;
            }
        default:
            User::Leave( KErrArgument );            
        }
    
    iScroller->SetMopParent( this );
    
    iLayoutData = CHgListLayoutData::NewL();
    iTitleItem = CHgItem::NewL( );
    
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::Scroller()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgScroller& CHgScrollerWithTitle::Scroller()
    {
    return *iScroller;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::InitScreenL()
// -----------------------------------------------------------------------------
//
EXPORT_C void CHgScrollerWithTitle::InitScreenL( const TRect& aRect )
    {
    // Set the windows size
    SetRect ( aRect );
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::TitleItem()
// -----------------------------------------------------------------------------
//
EXPORT_C CHgItem& CHgScrollerWithTitle::TitleItem()
    {
    return *iTitleItem;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::CHgScrollerWithTitle()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHgScrollerWithTitle::CHgScrollerWithTitle()
    {
    // No implementation required
    }
        
// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::~CHgScrollerWithTitle()
// Destructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CHgScrollerWithTitle::~CHgScrollerWithTitle ( )
    {
    delete iLayoutData;
    delete iScroller;
    delete iTitleItem;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CHgScrollerWithTitle::Draw ( const TRect& /*aRect*/ ) const
    {
    // Draw background skin
    CWindowGc& gc = SystemGc();

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::DrawBackground( skin, cc, this, gc,
            TPoint(0,0), iTitleRect, KAknsDrawParamDefault );
    
    // Draw background rect. Rect is just a little smaller
    // than the actual item slot.
    TRect recthg(iTitleRect);
    TRect rect(recthg);
    rect.Shrink(2,2);
    AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(),
           gc,
           recthg,
           rect,
           KAknsIIDQsnFrPopup,
           KAknsIIDQsnFrPopupCenter );
    
    // Draw title icon if it exists.
    CGulIcon* icon = iTitleItem->Icon();

    if(icon)
        {
        // Draw the icon
        TAknLayoutRect image;
        image.LayoutRect(iTitleRect, iLayoutData->IconLayout());
        image.DrawImage(gc, icon->Bitmap(), icon->Mask());
        }
    
    // Draw first text line.
    TAknLayoutText textLayout;
    textLayout.LayoutText(iTitleRect, iLayoutData->TitleLayout(0) );
    textLayout.DrawText(gc, iTitleItem->Title(), ETrue, iColor );

    // Draw second text line.
    textLayout.LayoutText(iTitleRect, iLayoutData->TextLayout() );
    textLayout.DrawText(gc, iTitleItem->Text(), ETrue, iColor );        
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHgScrollerWithTitle::SizeChanged ( )
    {
    // Initialize layout data object
    iLayoutData->SetItemLayout(list_double_large_graphic_pane( 0 ));
    iLayoutData->SetIconLayout(list_double_large_graphic_pane_g1( 2 ));
    for(TInt i = 0; i <= KMaxNumberOfTitleIndicators; ++i)
        iLayoutData->SetTitleLayout(i, list_double_large_graphic_pane_t1( i ));
    iLayoutData->SetTextLayout(list_double_large_graphic_pane_t2( 2 ));
    iLayoutData->SetFirstIndicatorLayout(list_double_large_graphic_pane_g3(0));
    iLayoutData->SetSecondIndicatorLayout(list_double_large_graphic_pane_g2(0));
    iLayoutData->SetBaseLayout(AknLayoutScalable_Avkon::list_gen_pane(0));    
    
    TAknLayoutRect layout;
    layout.LayoutRect(Rect(), iLayoutData->ItemLayout());

    // Rect for the title item.
    iTitleRect = layout.Rect();
    
    // Set size for the compound control.
    TRect scrollerRect( PositionRelativeToScreen(), Size() );
    scrollerRect.iTl.iY += iTitleRect.Height();
    TRAP_IGNORE( iScroller->InitScreenL( scrollerRect ); )

    // Resolve color for normal items            
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( 
                AknsUtils::SkinInstance(),
                iColor,
                KAknsIIDQsnTextColors,
                EAknsCIQsnTextColorsCG6 );                        
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::CountComponentControls()
// -----------------------------------------------------------------------------
//
TInt CHgScrollerWithTitle::CountComponentControls() const
    {
    // We have only one child
    return 1;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::ComponentControl()
// -----------------------------------------------------------------------------
//
CCoeControl* CHgScrollerWithTitle::ComponentControl(TInt aIndex) const
    {
    if( aIndex == 0 )
        {
        return iScroller;
        }
    
    return NULL;
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::ComponentControl()
// -----------------------------------------------------------------------------
//
void CHgScrollerWithTitle::FocusChanged(TDrawNow aDrawNow)
    {
    if(iScroller)
        {
        iScroller->SetFocus(IsFocused(), aDrawNow);
        }
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::OfferKeyEventL()
// -----------------------------------------------------------------------------
//
TKeyResponse CHgScrollerWithTitle::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    // send key events to children.
    return iScroller->OfferKeyEventL( aKeyEvent, aType );
    }

// -----------------------------------------------------------------------------
// CHgScrollerWithTitle::PreferredImageSize()
// -----------------------------------------------------------------------------
//
EXPORT_C TSize CHgScrollerWithTitle::PreferredImageSize()
    {
    // Fetch icon size from the layout.
    TAknLayoutRect image;
    image.LayoutRect(TRect(), AknLayoutScalable_Avkon::list_double_large_graphic_pane_g1( 2 ));
    return image.Rect().Size();
    }


// End of File
