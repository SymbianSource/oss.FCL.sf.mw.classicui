/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
*   This file contains the implementation of the view and component
*   of the picture grid component, as specified in the application LAF.
*
*
*/

#include "AknGMSStyleGrid.h"
#include <barsread.h>
#include <aknlists.h>
#include <gulicon.h> // gul icons
#include <aknpopuplayout.h>
#include <aknPopupHeadingPane.h>

#include <applayout.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>

using namespace AppLayout;


// ----------------------------------------------------------------------------
EXPORT_C CAknGMSStyleGridView::CAknGMSStyleGridView()
    {
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGridView::Draw(const TRect* aClipRect/* = NULL*/) const
    {
    CAknGridView::Draw(aClipRect);

    TInt horLines = MaxNumOfHorLines();
    TInt verLines = MaxNumOfVerLines();
    
    if ( iModel->NumberOfItems() > 0 )
        {
        for( TInt i1=0 ; i1<horLines ; i1++ )
            {
            iHorLine[i1].DrawRect(*iGc);
            }
        for( TInt i2=0 ; i2<verLines ; i2++ )
            {
            iVerLine[i2].DrawRect(*iGc);
            }
        }
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGridView::SetupLayout(const TRect& aRect, TBool aIsPopup /*=EFalse */, TInt aNum /*=-1*/)
    {
    iRect = &aRect;
    TInt horLines = MaxNumOfHorLines();
    TInt verLines = MaxNumOfVerLines();
    
    if (aIsPopup) 
        {
        for(TInt i1=0 ; i1<horLines ; i1++)
            {
            iHorLine[i1].LayoutRect(aRect,
                                    Graphical_message_image_selection_pop_up_window_elements_Line_1(i1));
            }

        // aNum must be 1..4
        for(TInt i2=0 ; i2<verLines ; i2++)
            {
            iVerLine[i2].LayoutRect(aRect,
                                    Graphical_message_image_selection_pop_up_window_elements_Line_2(i2, aNum-1));
            }
        }
    else
        {
        for (TInt i1=0 ; i1<horLines ; i1++)
            {
            iHorLine[i1].LayoutRect(aRect, Graphical_message_selection_layout_elements_Line_1(i1));
            }
        for (TInt i2=0 ; i2<verLines ; i2++)
            {
            iVerLine[i2].LayoutRect(aRect, Graphical_message_selection_layout_elements_Line_2(i2));
            }
        }
    }

EXPORT_C TAny* CAknGMSStyleGridView::Reserved_1()
    {
    return NULL;
    }

TInt CAknGMSStyleGridView::MaxNumOfHorLines() const
    {
    //TODO: calculate maximum number of horizontal lines in GMS grid
    return 5;
    }

TInt CAknGMSStyleGridView::MaxNumOfVerLines() const
    {
    //TODO: calculate maximum number of vertical lines in GMS grid
    return 3;
    }

// ============================================================================
// CAknGMSStyleGrid
// ============================================================================

// ----------------------------------------------------------------------------
EXPORT_C CAknGMSStyleGrid::CAknGMSStyleGrid()
    : AKNGRID(), iIsPopup(EFalse)
    {
 
    }

EXPORT_C CAknGMSStyleGrid::CAknGMSStyleGrid(TBool aIsPopup)
    : AKNGRID(), iIsPopup(aIsPopup)
    {
 
    }



EXPORT_C CAknGMSStyleGrid::~CAknGMSStyleGrid()
    {
    }

TSize CAknGMSStyleGrid::KCELL_SIZE()
    {
    //return TSize(72,28);
    return TSize(0,0); // this is not used anywhere, afaik  
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGrid::ConstructL(const CCoeControl* aParent, 
                                           TInt aRows /*=4*/, TInt aCols/*=2*/)
    {
    AKNGRID::ConstructL(aParent, EAknListBoxMarkableList);
    TAknLayoutRect r;
    r.LayoutRect(Rect(), cell_gms_pane(0,0));
    
    TInt cellWidth = r.Rect().Width();    // was 80
    TInt cellHeight = r.Rect().Height();  // was 34

    SetLayoutL(EFalse, ETrue, ETrue, aCols, aRows, TSize(cellWidth,cellHeight), 1, 1);
    SetPrimaryScrollingType(CAknGridView::EScrollFollowsItemsAndLoops);
    SetSecondaryScrollingType(CAknGridView::EScrollIncrementLineAndLoops);        
        
    ActivateL();        
    }

// ----------------------------------------------------------------------------
EXPORT_C  CAknGMSStyleGrid* CAknGMSStyleGrid::NewL(
    const CCoeControl* aParent, TBool aIsPopup)
    {
    CAknGMSStyleGrid* self = new (ELeave) CAknGMSStyleGrid(aIsPopup);
    CleanupStack::PushL(self);
    self->ConstructL(aParent);
    CleanupStack::Pop(); // self
    return self;
    }

// ----------------------------------------------------------------------------
void CAknGMSStyleGrid::_LOG(const TDesC& /*aText*/)
    {
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGrid::SetupLayout()
    {
    STATIC_CAST(CAknGMSStyleGridView*, View())->SetupLayout(Rect());
    }

EXPORT_C TSize CAknGMSStyleGrid::MinimumSize()
    {
    TAknLayoutRect r;
    if ( iIsPopup )
        {
        r.LayoutRect( Rect(), grid_large_graphic_popup_pane(0) );
        }
    else
        {
        r.LayoutRect( Rect(), grid_gms_pane() );
        }

    return TSize( r.Rect().Width(), r.Rect().Height() );
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGrid::SizeChanged()
    {
    // call the super method
    AKNGRID::SizeChanged();

    TAknLayoutRect r;
    TInt cellWidth;
    TInt cellHeight;
    TInt ml(0), mt(0), mW(0)/*, mH(0)*/; // for marked item indication in grid cell

    if (iIsPopup)
        {
        r.LayoutRect( Rect(), cell_large_graphic_popup_pane(0, 0) );
        cellWidth  = r.Rect().Width();
        cellHeight = r.Rect().Height();
        TPoint pTl(0,0);
        TPoint pBr(cellWidth,cellHeight);
        AknListBoxLayouts::SetupGridFormGfxCell( //place an graphics to cell
            *this, // whic grid
            ItemDrawer(), // which itemdrawer is responsible for drawing
            0, // cell index (also from item string)
            Cell_pane_elements__popup_large_graphic_gms__Line_1(),
            pTl, pBr);
        }
    else
        {
        r.LayoutRect( Rect(), cell_gms_pane(0, 0) );
        cellWidth  = r.Rect().Width();
        cellHeight = r.Rect().Height();

        TAknLayoutRect mr;
        mr.LayoutRect( Rect(), Graphical_message_cell_elements_Line_2() );
        ml = mr.Rect().iTl.iX;
        mt = mr.Rect().iTl.iY;
        mW = mr.Rect().Width();
        // mH = mr.Rect().Height(); 

        TPoint pTl(0,0);
        TPoint pBr(cellWidth,cellHeight);
        AknListBoxLayouts::SetupGridFormGfxCell( //place an graphics to cell
            *this, // which grid
            ItemDrawer(), // which itemdrawer is responsible for drawing
            0, // cell index (also from item string)
            Graphical_message_cell_elements_Line_1(),
            pTl, pBr);

        }

    AknListBoxLayouts::SetupStandardGrid(*this);
    AknListBoxLayouts::SetupGridPos(*this, 0, 0, -1, -1, cellWidth, cellHeight);
    
    if (!iIsPopup)
        {
        TRAP_IGNORE(
            {
            ItemDrawer()->FormattedCellData()->SetTransparentSubCellL(1, ETrue);
            ItemDrawer()->FormattedCellData()->SetNotAlwaysDrawnSubCellL(1, ETrue);
            });
        
        ItemDrawer()->SetItemMarkPosition(1);
        _LIT(KZero,"0");
        ItemDrawer()->SetItemMarkReplacement(KZero);
        ItemDrawer()->SetItemMarkReverse(ETrue);
        TPoint pTl(ml,mt);
        TPoint pBr(ml+mW,mt+mW);
        AknListBoxLayouts::SetupGridFormGfxCell(
            *this, 
            ItemDrawer(), 
            1,
            Graphical_message_cell_elements_Line_2(),
            pTl, pBr);
        }

    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGrid::Draw(const TRect& aRect) const
    {
    AKNGRID::Draw(aRect);
    }

// ----------------------------------------------------------------------------
EXPORT_C CListBoxView* CAknGMSStyleGrid::MakeViewClassInstanceL()
    {
    CListBoxView* view = new (ELeave) CAknGMSStyleGridView();
    return view;
    }

// ----------------------------------------------------------------------------
EXPORT_C void CAknGMSStyleGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSelectionGridTypedef::HandlePointerEventL(aPointerEvent); 
    }

EXPORT_C void* CAknGMSStyleGrid::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }
    
// ----------------------------------------------------------------------------
EXPORT_C TKeyResponse CAknGMSStyleGrid::OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                                       TEventCode aType)
    {
    return AKNGRID::OfferKeyEventL(aKeyEvent, aType);
    }

// ----------------------------------------------------------------------------

EXPORT_C void CAknGMSPopupGrid::CalcPopupGridLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef, TRect aRect, TInt num)
    {
    // Find window layout variaties based on CBA location
    TInt variety = 0;
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();
    if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
        { // Variety numbers for right CBA are 4-7
        variety = num-1+4;
        }
    else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
        { // Variety numbers for right CBA are 8-11
        variety = num-1+8;
        }
    else // bottom
        {
        variety = num-1;
        }
    TAknLayoutRect popup_menu_window;
    //popup_menu_window.LayoutRect(aRect, 0, ELayoutEmpty,ELayoutEmpty,0,0,176,77+(114-77)*(num-1));
    popup_menu_window.LayoutRect(aRect, AknLayoutScalable_Apps::popup_grid_large_graphic_window(variety));
    aDef.iWindowRect = popup_menu_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }

EXPORT_C void CAknGMSPopupGrid::PopupGridLargeGraphicGraphics(TAknPopupWindowLayoutDef &aDef)
    {
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);

    aDef.iCover.LayoutRect(  window_rect, Graphical_message_image_selection_pop_up_window_graphics_Line_1(window_rect));
    aDef.iSecond.LayoutRect( window_rect, Graphical_message_image_selection_pop_up_window_graphics_Line_2(window_rect));
    aDef.iFirst.LayoutRect(  window_rect, Graphical_message_image_selection_pop_up_window_graphics_Line_3(window_rect));
    aDef.iOutline.LayoutRect(window_rect, Graphical_message_image_selection_pop_up_window_graphics_Line_4(window_rect));
    aDef.iInside.LayoutRect( window_rect, Graphical_message_image_selection_pop_up_window_graphics_Line_5(window_rect));
    }
    
EXPORT_C void CAknGMSPopupGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknPopupList::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CAknGMSPopupGrid::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknGMSPopupGrid::SetupPopupGridLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef, 
                                                                 TInt aNum, 
                                                                 TBool /*aHeading*/)
    {
    AknPopupLayouts::SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    aDef.iListRect.LayoutRect(window_rect, grid_large_graphic_popup_pane(aNum-1));

    // combine list heading pane layouts for GMS grid
    TAknLayoutRect grid;
    TAknLayoutRect head;

    grid.LayoutRect(window_rect, Graphical_message_image_selection_pop_up_window_descendants_Line_1());
    head.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8);

    //aDef.iHeadingRect.LayoutRect(window_rect, 0, 3,6, ELayoutEmpty, ELayoutEmpty, 168, 23);
    aDef.iHeadingRect.LayoutRect( window_rect,
                                  0, // can not really set here, so drawing should set color
                                  head.Rect().iTl.iX,
                                  head.Rect().iTl.iY, ELayoutEmpty, ELayoutEmpty,
                                  grid.Rect().Width(),
                                  grid.Rect().Height() );

    PopupGridLargeGraphicGraphics(aDef);
    }



EXPORT_C void CAknGMSPopupGrid::SetupWindowLayout(AknPopupLayouts::TAknPopupLayouts)
    {
    TAknPopupWindowLayoutDef &aDef = Layout();
    CAknPopupHeadingPane *aHeading = iTitle;
    CEikListBox *aListBox = ListBox();
    CCoeControl *aWindowOwningControl = this;

    CAknGMSStyleGrid *grid = (CAknGMSStyleGrid*)aListBox;

    if ( aHeading )
        {
        aHeading->SetLayout( CAknPopupHeadingPane::EListHeadingPane );
        }

    TInt numOfRows;

    switch( aListBox->Model()->NumberOfItems() )
        {
        case 1:
        case 2:
            numOfRows = 1;
            break;
        case 3:
        case 4:
            numOfRows = 2;
            break;
        case 5:
        case 6:
            numOfRows = 3;
            break;
        default:
            numOfRows = 4;
            break;
        }

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );

    // Find window layout variaties based on CBA location
    TInt variety = 0;
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();
    if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
        { // Variety numbers for right CBA are 4-7
        variety = 3+4;
        }
    else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
        { // Variety numbers for right CBA are 8-11
        variety = 3+8;
        }
    else // bottom
        {
        variety = 3; // why this is 3?
        }

    TAknLayoutRect r; 
    r.LayoutRect( mainPane, AknLayoutScalable_Apps::popup_grid_large_graphic_window(variety) );

    TRect clientRect = r.Rect();

    TInt minRows = 1;
    TInt maxRows = 3;
    AknPopupLayouts::CheckRange(numOfRows, minRows,maxRows);
    CalcPopupGridLargeGraphicWindow(aDef, clientRect, numOfRows);

    SetupPopupGridLargeGraphicWindow(aDef, numOfRows, aHeading != 0);
            
    aWindowOwningControl->SetRect(AknPopupLayouts::WindowRect(aDef));
    AknPopupLayouts::HandleSizeAndPositionOfComponents(aDef, aListBox, aHeading);

    ((CAknGMSStyleGridView*)grid->View())->SetupLayout(
        AknPopupLayouts::MenuRect( aDef ), ETrue, numOfRows );
    }


EXPORT_C CAknGMSPopupGrid* CAknGMSPopupGrid::NewL(CEikListBox* aListBox, TInt aCbaResource, AknPopupLayouts::TAknPopupLayouts aType)
    {
    CAknGMSPopupGrid* self = new(ELeave)CAknGMSPopupGrid;        
    CleanupStack::PushL(self);
    self->ConstructL(aListBox, aCbaResource, aType);
    CleanupStack::Pop();        // self
    return self;
    }

// END OF FILE


