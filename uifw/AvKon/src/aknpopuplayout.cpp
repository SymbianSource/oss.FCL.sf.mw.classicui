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
*
*/


#include <aknpopuplayout.h>
#include <e32def.h>
#include <eiklbx.h>
#include <aknPopupHeadingPane.h>
#include <AknPanic.h>
#include <AknLayout.lag>
#include <aknenv.h>

#include <AknUtils.h>
#include <eiksfont.h>
#include <avkon.rsg>
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <eikfrlbd.h>
#include <AknsBasicBackgroundControlContext.h>
#include <aknmessagequerycontrol.h>
#include <aknsfld.h>

#include <skinlayout.cdl.h>

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>

#include <touchfeedback.h>
#include <aknlists.h>


static CCoeControl *FindControl(TAknPopupLayoutsNode *aNode, TInt aId)
    {
    while(aNode)
        {
        if (aId == aNode->iId)
            {
            return aNode->iControl;
            }
        aNode = aNode -> iNext;
        }
    return NULL;
    }

static TInt GetMaxListHeight()
    {
    TAknLayoutRect temp, layout;

    TRect mainPane;
    TRect statusPane;
    TRect controlPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EStatusPane, statusPane );
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPane, controlPane );
    
    // in landscape orientation popuplist can't go on top of statuspane
    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        mainPane.iTl.iY -= statusPane.Height();
        }

    // treat mainpane+statuspane area as popup window
    // too bad we can't use this, because e.g. QVGA landscape has border-size 7
    // in avkon layout and border-size 9 in skin drawing...
    /*temp.LayoutRect( mainPane, AknLayoutScalable_Avkon::listscroll_menu_pane(0));
    layout.LayoutRect( temp.Rect(), AknLayoutScalable_Avkon::list_menu_pane(0));
    return layout.Rect().Height();*/
        
    // shadow
    TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation();
    
    TAknLayoutRect insideArea;
    insideArea.LayoutRect(
        mainPane,
        AknLayoutScalable_Avkon::bg_popup_window_pane_g1(varietyIndex) );
        
    return insideArea.Rect().Height();
    }


EXPORT_C
void AknPopupLayouts::HandleSizeChanged( TAknPopupWindowLayoutDef &aDef, 
                                         TAknPopupLayouts aLayout_1,
                                         CAknPopupHeadingPane *aHeading,
                                         CEikListBox *aListBox,
                                         CCoeControl *aWindowOwningControl )
    {
    TAknPopupLayoutsNode list = { 0, EListNode, aListBox };
    TAknPopupLayoutsNode heading = { &list, EHeadingNode, aHeading };
    TAknPopupLayoutsNode windowOwning = { &heading, EWindowOwningNode, aWindowOwningControl };
    HandleSizeChanged(aDef, aLayout_1, &windowOwning);
    }


EXPORT_C
void AknPopupLayouts::HandleSizeChanged( TAknPopupWindowLayoutDef &aDef,
                                         TAknPopupLayouts aLayout_1,
                                         TAknPopupLayoutsNode *aNode)
    {
    CAknPopupHeadingPane *aHeading = (CAknPopupHeadingPane*)FindControl(aNode, EHeadingNode);
    CEikListBox *aListBox = (CEikListBox*)FindControl(aNode, EListNode);
    CCoeControl *aWindowOwningControl = FindControl(aNode, EWindowOwningNode);
    CAknMessageQueryControl *aMsgQueryCtrl = (CAknMessageQueryControl*)FindControl(aNode, EMessageBoxNode);
    
    TInt aLayout = aLayout_1;
    TInt numofitems = aListBox->Model()->NumberOfItems();

    aListBox->View()->ItemDrawer()->SetSkinEnabledL(ETrue);
    
    TInt maxListHeight = GetMaxListHeight();

    // position popup window's bottom correctly
    TRect clientRect;
    AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EPopupParent, clientRect);
    // set windowrect to minimum size - this will be adjusted later    
    TAknLayoutRect windowRect;
    windowRect.LayoutRect( clientRect, AknLayoutScalable_Avkon::popup_menu_window(8));
    aDef.iWindowRect = windowRect.Rect();
    TRAP_IGNORE( aListBox->View()->ItemDrawer()->SetSkinEnabledL(ETrue) );
    
    // Popup window when the size does not change based on
    // the number of items.
    TBool fixedWindowSize = EFalse;
    if ( (aLayout & EAknPopupLayoutsDynamic) || numofitems == 0 ||
         (aLayout & EAknPopupLayoutsFind) )
        {
        aLayout &= ~EAknPopupLayoutsDynamic;
        fixedWindowSize = ETrue;
        }
        
    // heading =============================================================
    TInt spaceForHeading = 0;
    if (aHeading)
        {
        aHeading->SetLayout( CAknPopupHeadingPane::EListHeadingPane ); 
        TAknLayoutRect tempHeadingRect;
        tempHeadingRect.LayoutRect(clientRect,
            AknLayoutScalable_Avkon::heading_pane(0));
        spaceForHeading = tempHeadingRect.Rect().Height();
        maxListHeight -= spaceForHeading;
        }
    aDef.iPopupMenuWindowOffset=TPoint(0,spaceForHeading);
        
    
    // findbox =============================================================
    TBool windowSizeFind = EFalse;
    TInt spaceForFind = 0;
    if (aLayout & EAknPopupLayoutsFind)
        {
        aLayout &= ~EAknPopupLayoutsFind;
        windowSizeFind = ETrue;
        // calculate space needed for find
        TAknLayoutRect tempFindRect;
        tempFindRect.LayoutRect(clientRect,AknLayoutScalable_Avkon::find_popup_pane_cp2(0));
        spaceForFind = tempFindRect.Rect().Height();
        maxListHeight -= spaceForFind;
        }
    
    // messagebox ==========================================================
    TRect messageRect;
    TInt messageNumOfLines = 0;
    TBool messageBox = EFalse;
    if (aMsgQueryCtrl && aMsgQueryCtrl->Lines() > 0)
        {
        messageBox = ETrue;
        messageNumOfLines = aMsgQueryCtrl->Lines();
        TInt varietyIndex = 0;
        switch(messageNumOfLines)
            {
            case (0):
            case (1): varietyIndex = 0;
            break;          
            case (2): varietyIndex = 1;
            break;
            default : varietyIndex = 2;
            }           
        TAknWindowLineLayout lay = AknLayoutScalable_Apps::loc_type_pane(varietyIndex).LayoutLine();
        TAknLayoutRect layout;
        layout.LayoutRect( TRect(0,0,0,0), lay );           
        messageRect =  layout.Rect();           
        maxListHeight -= messageRect.Height();
        }
    
    TInt minItems = 1;
    
    TRect scrollBarRect(0,0,0,0);
    
    TAknWindowLineLayout listLayout;
    TAknLayoutScalableParameterLimits listLimits;
    
    switch(aLayout)
        {
        case EPopupSNotePopupWindow:
        case EMenuUnknownColumnWindow:
        case EMenuUnknownFormattedCellWindow:
        case EMenuWindow:
            {
            minItems = aHeading ? 5 : 6;
            listLayout = AknLayoutScalable_Avkon::list_single_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicHeadingWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_double_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleLargeGraphicWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2(0);
            listLimits = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2_ParamLimits();
            break;
            }
        }
        
    if (!fixedWindowSize)
        {
        minItems = 1;
        }

    TInt maxLayoutItems = listLimits.LastRow() + 1; // last row is a zero based index, we need num items which is 1 based
        
    //aDef.iVertLineExt1.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
    //aDef.iVertLineExt2.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
        
    TAknLayoutRect listItemRect;
    listItemRect.LayoutRect( aDef.iWindowRect, listLayout);
    TInt listItemHeight = listItemRect.Rect().Height();
    TInt maxItems = maxListHeight / listItemHeight;
    // minItems == 1 only if the popuplist is dynamically changeable
    if ( (numofitems > 1) && (minItems == 1) )
        {
        minItems = numofitems;
        }
    if (minItems > maxItems)
        {
        minItems = maxItems;
        }
    // maxItems might be greater than max items from layout -> use layout's maximum
    if (minItems > maxLayoutItems)
        {
        minItems = maxLayoutItems;
        }

    TRect window_rect = AknPopupLayouts::MenuRect(aDef);

    TAknLayoutRect temp, layout;
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect ); 
    TAknWindowLineLayout lineLayout = AknLayoutScalable_Avkon::listscroll_menu_pane(0).LayoutLine();
 
    // Layout data of listscroll_menu_pane are changed for CR 417-35260.
    // The change is just for QHD landscape model.
    // The CR makes listscroll_menu_pane's ir or il bigger than normal,
    // so that width of list item is smaller than needs. Then, first cell 
    // of list item can not be drawn on proper position.
    // Adjustment of layout is a solution for this problem. This is not a perfect idea, but
    // creating a new layout for popuplist is too complex to do that. Adjustment is a must.
    if(Layout_Meta_Data::IsLandscapeOrientation())       
        {
        TInt offset  = AknListBoxLayouts::AdjustPopupLayoutData( screenRect );
        if (!AknLayoutUtils::LayoutMirrored())
            {
            lineLayout.ir -= offset;
            }
        else
            {
            lineLayout.il -= offset;
            }
        }
    temp.LayoutRect( window_rect, lineLayout);        

    layout.LayoutRect( temp.Rect(), AknLayoutScalable_Avkon::list_menu_pane(0));
    TRect tempListRect = layout.Rect(); // this is list's rect for the whole window
    
    // subtract heading, findbox and messagebox from tempListRect
    tempListRect.iBr.iY -= spaceForFind;
    tempListRect.iTl.iY += spaceForHeading;
    tempListRect.iTl.iY += messageRect.Height();
    
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    listLayout.iH = (TInt16)(minItems * listItemHeight);
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(tempListRect,
        listLayout);

    // we have to scale iWindowRect to list rect - layout is not (yet) correct
    TInt usedHeight = aDef.iListRect.Rect().Height()
        + spaceForFind
        + spaceForHeading
        + messageRect.Height();
        
    // popupwindow's inside area
    TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation();
    
    TAknLayoutRect insideArea;
    insideArea.LayoutRect(
        window_rect,
        AknLayoutScalable_Avkon::bg_popup_window_pane_g1(varietyIndex) );

    if (layout.Rect().Height() < usedHeight)
        {
        aDef.iWindowRect.iTl.iY -= (usedHeight - layout.Rect().Height());
        }
    
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();    
        
    // In landscape we have to center (on y-axis) popup window (but not with bottom CBA)
    if (varietyIndex == 1 && cbaLocation != AknLayoutUtils::EAknCbaLocationBottom)
        {
        TRect mainPane;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
        TInt diff = (mainPane.Height()-aDef.iWindowRect.Height()) / 2;
        aDef.iWindowRect.iTl.iY -= diff;
        aDef.iWindowRect.iBr.iY -= diff;
                        
        // with right CBA, move window to the right side of the screen
        if (cbaLocation == AknLayoutUtils::EAknCbaLocationRight)
            {
            TInt offset = mainPane.Width()-aDef.iWindowRect.iBr.iX;
            aDef.iWindowRect.iTl.iX += offset;
            aDef.iWindowRect.iBr.iX += offset;
            }        
        
        //should this be uncommented??
        // If we have left CBA, we move window to left side of screen (on x-axis).       
        /*else if (cbaLocation == AknLayoutUtils::EAknCbaLocationLeft)
            {
            TInt xOffset = aDef.iWindowRect.iTl.iX;
            if ( xOffset > 0 )
                {
                aDef.iWindowRect.iTl.iX = 0;
                aDef.iWindowRect.iBr.iX -= xOffset;
                }
            }*/
        }                                                                              
      
    TRect screen;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
        
    TAknLayoutRect cbaRect;
    cbaRect.LayoutRect( screen, 
        AknLayoutScalable_Avkon::popup_sk_window( 0  ).LayoutLine() );
            
    if ( AknLayoutUtils::PenEnabled() )
        {
        TSize size( aDef.iWindowRect.Size() );
        // add softkey height
        size.iHeight += cbaRect.Rect().Height();
        
        // Reduce listbox's and popup's height if total height is more than
        // screen height.
        if ( size.iHeight > screen.Height() )
            {
            listLayout.iH -= ( size.iHeight - screen.Height() );
            aDef.iListRect.LayoutRect( tempListRect, listLayout );
            
            size.iHeight = screen.Height();
            }

        aDef.iWindowRect.SetRect( AknPopupUtils::Position( size, ETrue ), size );
        }

    // now we finally know the window rect: first setup heading
    if (aHeading)
        {
        aDef.iHeadingRect.LayoutRect(AknPopupLayouts::MenuRect(aDef),
            AknLayoutScalable_Avkon::heading_pane(0));
        }
    
    MenuPopupWindowGraphics(aDef);
    aWindowOwningControl->SetRect(WindowRect(aDef));
    HandleSizeAndPositionOfComponents(aDef, aListBox, aHeading);

    layout.LayoutRect(MenuRect(aDef), lineLayout);
    TRect scrollBarClientRect(layout.Rect());
        
    if ( AknLayoutUtils::PenEnabled() )
        {
        // remove softkey height that was added earlier so that
        // scroll bar doesn't get behind the softkey 
        scrollBarClientRect.iBr.iY -= cbaRect.Rect().Height();
        }

    if (aHeading)
        {
        scrollBarClientRect.iTl.iY += spaceForHeading;                
        }
        
    if (windowSizeFind)
        {
        scrollBarClientRect.iBr.iY -= spaceForFind;
        }
        
    if (messageBox)
        {
        scrollBarClientRect.iTl.iY += messageRect.Height();
        }
    varietyIndex = 0;
    AknLayoutUtils::LayoutVerticalScrollBar(
        aListBox->ScrollBarFrame(),
        scrollBarClientRect, 
        AknLayoutScalable_Avkon::scroll_pane_cp25(varietyIndex).LayoutLine() ) ;
        
    if (messageBox)
        {
        TAknLayoutRect msgQuery;
      
        TInt varietyIndex = 0;
        switch(messageNumOfLines)
            {
            case (0):
            case (1): varietyIndex = 0;
            break;          
            case (2): varietyIndex = 1;
            break;
            default : varietyIndex = 2;
            }
        msgQuery.LayoutRect( AknPopupLayouts::MenuRect(aDef),
           AknLayoutScalable_Apps::loc_type_pane(varietyIndex).LayoutLine() );
        aMsgQueryCtrl->SetRect(msgQuery.Rect());
        }

    window_rect = WindowRect(aDef);
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( aListBox );
    TBool defaultContext = EFalse;
    if (!cc)
        {
        cc = aListBox->View()->ItemDrawer()->SkinBackgroundControlContext();
        defaultContext = ETrue;
        }
    if (cc)
        {
        CAknsBasicBackgroundControlContext *bcc = (CAknsBasicBackgroundControlContext*)cc;
        TAknLayoutRect popupBgRect;
        popupBgRect.LayoutRect(window_rect,
                               SkinLayout::Popup_windows_skin_placing__background_slice__Line_1(window_rect));
        bcc->SetBitmap(KAknsIIDQsnFrPopupCenter);
        if (defaultContext) bcc->SetRect(popupBgRect.Rect());
        bcc->SetParentPos(aWindowOwningControl->PositionRelativeToScreen());
        if (defaultContext)
            bcc->SetParentPos(TPoint(0,0));
        }
// handled in CFormattedCellListBoxDataExtension, since listbox does not always cover whole
// window rect (listquery/popup list), especially when items are added after construction        
/*
    // note, that cleanup is done in ~CFormattedCellListBoxData()
    // or ( shudder ) in ~CColumnListBoxData()
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if( feedback )
        {       
        feedback->SetFeedbackArea( aListBox, 0, aListBox->Rect(), 
                    ETouchFeedbackBasic, ETouchEventStylusDown );                                   
        }
*/
}

EXPORT_C void AknPopupLayouts::HandleSizeAndPositionOfComponents(const TAknPopupWindowLayoutDef &aDef, 
                             CCoeControl *aContent, 
                             CAknPopupHeadingPane *aHeading)
    {
    __ASSERT_DEBUG(aContent->MinimumSize() == aDef.iListRect.Rect().Size(), RDebug::Print(_L("AknPopupLayouts:ERROR, control minimumsize and LAF spec does not match!")));
    TRect lbrect = aDef.iListRect.Rect();
    TRect headrect; 
    
    aContent->SetRect(lbrect);
    if (aHeading) 
        {
        headrect = aDef.iHeadingRect.Rect();
        aHeading->SetRect(headrect);
        }
    }

EXPORT_C void AknPopupLayouts::CheckRange(TInt &aValue, TInt aMin, TInt aMax)
    {
    if (aValue > aMax) aValue = aMax;
    if (aValue < aMin) aValue = aMin;
    }

// Disable "unreferenced formal parameter" for when aEikEnv is not used in the AKN_LAF_COLOR_ENV macro.
#pragma warning(disable : 4100)
EXPORT_C void AknPopupLayouts::HandleDraw(CEikonEnv* /*aEikEnv*/,
                  CWindowGc &aGc,
                  const TAknPopupWindowLayoutDef &aDef, 
                  CEikListBox* aListBox, 
                  CAknPopupHeadingPane* aHeading)
    {
    TRect windowRect = MenuRect(const_cast<TAknPopupWindowLayoutDef&>(aDef));
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( aListBox );
    TBool windowFrameDrawn = EFalse;
    if (!cc) cc = aListBox->View()->ItemDrawer()->SkinBackgroundControlContext();
    
    TRegionFix<5> dontDrawRegion;
    TRegionFix<22> drawRegion;
    if ( aListBox )
        {
        dontDrawRegion.AddRect( aListBox->Rect() );

        // If there are scroll bars and they draw their own background, take
        // them out of clipping region
        CEikScrollBarFrame* scrollBarFrame = aListBox->ScrollBarFrame();
        if (scrollBarFrame)
            {
            CEikScrollBar* hBar = scrollBarFrame->GetScrollBarHandle(
                CEikScrollBar::EHorizontal);
            CEikScrollBar* vBar = scrollBarFrame->GetScrollBarHandle(
                CEikScrollBar::EVertical);
            TBool drawHorizontal = ETrue;
            TBool drawVertical = ETrue;
            scrollBarFrame->DrawBackgroundState(drawHorizontal, drawVertical);
            drawHorizontal = drawHorizontal && hBar && hBar->IsVisible();
            drawVertical = drawVertical && vBar && vBar->IsVisible();
            if (drawHorizontal)
                {
                TRect scrollBarRect(hBar->Rect());
                if (hBar->OwnsWindow())
                    {
                    TPoint windowPos = aDef.iWindowRect.iTl;
                    TPoint scrollBarPos = hBar->PositionRelativeToScreen();
                    scrollBarRect.Move(scrollBarPos - windowPos);
                    }
                dontDrawRegion.AddRect(scrollBarRect);
                }
            if (drawVertical)
                {
                TRect scrollBarRect(vBar->Rect());
                if (vBar->OwnsWindow())
                    {
                    TPoint windowPos = aDef.iWindowRect.iTl;
                    TPoint scrollBarPos = vBar->PositionRelativeToScreen();
                    scrollBarRect.Move(scrollBarPos - windowPos);
                    }
                dontDrawRegion.AddRect(scrollBarRect);
                }
            }
        }
    if ( aHeading )
        {
        dontDrawRegion.AddRect( aHeading->Rect() );
        }
    drawRegion.AddRect( windowRect );
    drawRegion.SubRegion( dontDrawRegion );
    if (cc)
        {
        const TAknsItemID *popupBgId = &KAknsIIDQsnBgPopupBackground;
        TAknLayoutRect popupBgRect;
        popupBgRect.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__background_slice__Line_1(windowRect));
        AknsDrawUtils::DrawCachedImage(skin, aGc, popupBgRect.Rect(), *popupBgId);

        const TAknsItemID *sliceId = &KAknsIIDQsnBgSlicePopup;
        TAknLayoutRect sliceRect;
        sliceRect.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__background_slice__Line_2());
        AknsDrawUtils::DrawCachedImage(skin, aGc, sliceRect.Rect(), *sliceId);
            
        TAknLayoutRect topLeft;
        topLeft.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_2());

        TAknLayoutRect bottomRight;
        bottomRight.LayoutRect(windowRect, SkinLayout::Popup_windows_skin_placing__frame_general__Line_5());

        TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
        TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
        aGc.SetPenStyle(CGraphicsContext::ENullPen);
        const TAknsItemID *frameId = &KAknsIIDQsnFrPopup;
        const TAknsItemID *frameCenterId = &KAknsIIDQsnFrPopupCenter;
        aGc.SetClippingRegion( drawRegion );
        windowFrameDrawn = AknsDrawUtils::DrawFrame(skin, aGc, outerRect, innerRect, *frameId, *frameCenterId);
        aGc.CancelClippingRegion();
        }
    if (!windowFrameDrawn)
        {
        AknDraw::DrawWindowShadow(aGc, aDef.iCover, aDef.iSecond, aDef.iFirst, aDef.iOutline, aDef.iInside);
        }
    }
#pragma warning(default : 4100)


EXPORT_C TRect AknPopupLayouts::MenuRect(TAknPopupWindowLayoutDef &aDef)
    {
    return TRect(TPoint(0,0), aDef.iWindowRect.Size());
    }


EXPORT_C void AknPopupLayouts::MenuPopupWindowGraphics(TAknPopupWindowLayoutDef &aDef)
    {
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout s0 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_graphics_Line_1(window_rect);
    TAknWindowLineLayout s1 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_graphics_Line_2(window_rect);
    TAknWindowLineLayout s2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_graphics_Line_3(window_rect);
    TAknWindowLineLayout s3 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_graphics_Line_4(window_rect);
    TAknWindowLineLayout s4 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_graphics_Line_5(window_rect);

    aDef.iCover.LayoutRect(  window_rect, s0);
    aDef.iSecond.LayoutRect( window_rect, s1);
    aDef.iFirst.LayoutRect(  window_rect, s2);
    aDef.iOutline.LayoutRect(window_rect, s3);
    aDef.iInside.LayoutRect( window_rect, s4);
}

EXPORT_C void AknPopupLayouts::SetupMenuPopupWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool heading)
    {
    SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout listLayout = AKN_LAYOUT_WINDOW_list_menu_pane(heading?1:0, num-1);
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    TRect listItemRect = RectFromLayout(nullRect, AknLayoutScalable_Avkon::list_single_number_heading_pane_cp2(0));
    listLayout.iH = (TInt16)(num * listItemRect.Height());
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(window_rect, listLayout);

    //aDef.iListRect.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_list_menu_pane(heading?1:0, num-1));
    
    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_Line_2;

    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect(window_rect, part1);

    //MenuPopupWindowGraphics(aDef);
    }

EXPORT_C void AknPopupLayouts::SetupPopupMenuGraphicWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool heading)
    {
    SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout listLayout = AKN_LAYOUT_WINDOW_list_menu_graphic_pane(heading?1:0, num-1);
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    TRect listItemRect = RectFromLayout(nullRect, AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2(0));
    listLayout.iH = (TInt16)(num * listItemRect.Height());
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(window_rect, listLayout);

    //aDef.iListRect.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_list_menu_graphic_pane(heading?1:0, num-1));
    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_Line_2;

    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect(window_rect, part1); 

    //MenuPopupWindowGraphics(aDef);
    }

EXPORT_C void AknPopupLayouts::SetupPopupMenuGraphicHeadingWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool heading)
    {
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout listLayout = AKN_LAYOUT_WINDOW_list_menu_graphic_heading_pane(heading?1:0, num-1);
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    TRect listItemRect = RectFromLayout(nullRect, AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2(0));
    listLayout.iH = (TInt16)(num * listItemRect.Height());
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(window_rect, listLayout);

    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_and_elements__single_graphic_heading__Line_2;
    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect(window_rect, part1);
    
    //MenuPopupWindowGraphics(aDef);

    const TAknWindowLineLayout lines[] =
        {
        AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_and_elements__single_graphic_heading__Line_3(heading?1:0),
        AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_and_elements__single_graphic_heading__Line_3(1)
        };
    TRect inner_rect = window_rect; 
    aDef.iVertLineExt1.LayoutRect( inner_rect, lines[0]);
    aDef.iVertLineExt2.LayoutRect( inner_rect, lines[1]);
    }

EXPORT_C void AknPopupLayouts::SetupPopupMenuDoubleWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool heading)
    {
    SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout listLayout = AKN_LAYOUT_WINDOW_list_menu_double_pane_list_menu_double2_pane(heading?1:0, num-1);
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    TRect listItemRect = RectFromLayout(nullRect, AknLayoutScalable_Avkon::list_double2_graphic_pane_cp2(0));
    listLayout.iH = (TInt16)(num * listItemRect.Height());
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(window_rect, listLayout);

    //aDef.iListRect.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_list_menu_double_pane_list_menu_double2_pane(heading?1:0, num-1 ));
    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants__double__Line_2;
    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect(window_rect, part1);

    //MenuPopupWindowGraphics(aDef);
    }
    
EXPORT_C void AknPopupLayouts::SetupImageSelectionMenuPopupWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool heading)
    {
    SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    TAknWindowLineLayout listLayout = AKN_LAYOUT_WINDOW_list_menu_double_large_graphic_pane(heading?1:0, num-1);
    // We really don't want parent relative list layout here because findbox will be overwritten.
    // Just calculate list height and use that.
    TRect nullRect(0,0,0,0);
    TRect listItemRect = RectFromLayout(nullRect, AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2(0));
    listLayout.iH = (TInt16)(num * listItemRect.Height());
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect(window_rect, listLayout);

    //aDef.iListRect.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_list_menu_double_large_graphic_pane(heading?1:0, num-1));

    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants__double__Line_2;

    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;
    aDef.iHeadingRect.LayoutRect(window_rect, part1);

    //MenuPopupWindowGraphics(aDef);
    }


EXPORT_C void AknPopupLayouts::SetupPopupSNoteGroupWindow(TAknPopupWindowLayoutDef &aDef, TInt num, TBool /*heading*/)
    {
    // not used (at least by AvKon) - no need to remove magic numbers
    SetupDefaults(aDef);
    TRect window_rect = AknPopupLayouts::MenuRect(aDef);
    aDef.iListRect.LayoutRect(window_rect, 0, 3, 11, ELayoutEmpty, ELayoutEmpty, 168, 38+(57-38)*(num-2) );
    TAknWindowLineLayout part1 = AKN_LAYOUT_WINDOW_Pop_up_window_list_pane_descendants_Line_8;
    TAknWindowLineLayout part2 = AKN_LAYOUT_WINDOW_Menu_pop_up_window_descendants_Line_2;

    // Combine two layouts togeher.
    if (part2.iC != ELayoutEmpty) part1.iC = part2.iC;
    if (part2.il != ELayoutEmpty) part1.il = part2.il;
    if (part2.it != ELayoutEmpty) part1.it = part2.it;
    if (part2.ir != ELayoutEmpty) part1.ir = part2.ir;
    if (part2.ib != ELayoutEmpty) part1.ib = part2.ib;
    if (part2.iW != ELayoutEmpty) part1.iW = part2.iW;
    if (part2.iH != ELayoutEmpty) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect(window_rect, part1);

    TInt p = window_rect.Size().iHeight;
    const AknLayoutUtils::SAknLayoutRect shadow[] =
    {   
        { 0,0,0,ELayoutEmpty, ELayoutEmpty,   176, p },
        { 86,7,12,ELayoutEmpty, ELayoutEmpty,   167, p -16 },
        { 221,4,10,ELayoutEmpty, ELayoutEmpty,  169, p -15 },
        { 215,2,8,ELayoutEmpty, ELayoutEmpty,  170, p -14 },
        { 0,3,9,ELayoutEmpty, ELayoutEmpty,  168, p -16 }
    };

    aDef.iCover.LayoutRect(  window_rect, shadow[0]);
    aDef.iSecond.LayoutRect( window_rect, shadow[1]);
    aDef.iFirst.LayoutRect(  window_rect, shadow[2]);
    aDef.iOutline.LayoutRect(window_rect, shadow[3]);
    aDef.iInside.LayoutRect( window_rect, shadow[4]);    
    }



EXPORT_C void AknPopupLayouts::CalcPopupMenuWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_window;
    popup_menu_window.LayoutRect(aRect, AKN_LAYOUT_WINDOW_popup_menu_window(num-1));
    aDef.iWindowRect = popup_menu_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }
EXPORT_C void AknPopupLayouts::CalcPopupMenuGraphicWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_graphic_window;
    popup_menu_graphic_window.LayoutRect(aRect, AKN_LAYOUT_WINDOW_popup_menu_graphic_window(num-1));
    aDef.iWindowRect = popup_menu_graphic_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }
EXPORT_C void AknPopupLayouts::CalcPopupMenuGraphicHeadingWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_graphic_heading_window;
    popup_menu_graphic_heading_window.LayoutRect(aRect,AKN_LAYOUT_WINDOW_popup_menu_graphic_heading_window(num-1));
    aDef.iWindowRect = popup_menu_graphic_heading_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }
EXPORT_C void AknPopupLayouts::CalcPopupMenuDoubleWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_double_window;
    TInt items = 2;
    if (num == 2) items = 1;
    if (num == 1) items = 0;
    popup_menu_double_window.LayoutRect(aRect, AKN_LAYOUT_WINDOW_popup_menu_double_window(items));
    aDef.iWindowRect = popup_menu_double_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }

EXPORT_C void AknPopupLayouts::CalcPopupMenuDoubleLargeGraphicWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_double_large_graphic_window;
    TInt items = 2;
    if (num == 2) items = 1;
    if (num == 1) items = 0;
    popup_menu_double_large_graphic_window.LayoutRect(aRect, AKN_LAYOUT_WINDOW_popup_menu_double_large_graphic_window(items));
    aDef.iWindowRect = popup_menu_double_large_graphic_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }    


EXPORT_C void AknPopupLayouts::CalcPopupSNoteGroupWindow(TAknPopupWindowLayoutDef &aDef,TRect aRect, TInt num)
    {
    TAknLayoutRect popup_menu_snote_window;
    if (num-2 < 0) { num = 2; }
    popup_menu_snote_window.LayoutRect(aRect, AKN_LAYOUT_WINDOW_popup_snote_group_window(num-2));
    aDef.iWindowRect = popup_menu_snote_window.Rect();
    aDef.iPopupMenuWindowOffset=TPoint(0,0);
    }    


EXPORT_C TRect AknPopupLayouts::WindowRect(TAknPopupWindowLayoutDef &aDef) {return aDef.iWindowRect; }

EXPORT_C void AknPopupLayouts::ModifyWindowGraphicForHeading(TAknPopupWindowLayoutDef &aDef)
    {
    TRect nullRect(0,0,0,0);
    TAknLayoutRect nullHeadingRect;
    // find out, how much space is needed for heading (spaceForHeading was 23)
    nullHeadingRect.LayoutRect(nullRect,AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_1(nullRect));
    TInt spaceForHeading = nullHeadingRect.Rect().Height();


    aDef.iWindowRect.iTl.iY -= spaceForHeading; // This is necessary to position it correctly 
                                // this is because b=0 in parent of coverrect and because
                                // parent's height is used in the child...

    TRect window_rect = aDef.iWindowRect;

    aDef.iCover.LayoutRect(  window_rect, AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_1(window_rect));
    aDef.iSecond.LayoutRect( window_rect, AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_2(window_rect));
    aDef.iFirst.LayoutRect(  window_rect, AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_3(window_rect));
    aDef.iOutline.LayoutRect(window_rect, AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_4(window_rect));
    aDef.iInside.LayoutRect( window_rect, AKN_LAYOUT_WINDOW_Pop_up_menu_with_heading_window_graphics_Line_5(window_rect));
    
    aDef.iPopupMenuWindowOffset=TPoint(0,spaceForHeading);
    }

EXPORT_C void AknPopupLayouts::ModifyWindowGraphicForMessageBox(TAknPopupWindowLayoutDef &aDef, TInt aNumberOfLines)
    {        
    TInt varietyIndex = 0;
    switch (aNumberOfLines)
        {       
        case (2): varietyIndex = 1;
        break;
        case (3): varietyIndex = 2;
        }
                                
    TAknWindowLineLayout lay = AknLayoutScalable_Apps::loc_type_pane(varietyIndex).LayoutLine();
    TAknLayoutRect layout;
    layout.LayoutRect( TRect(0,0,0,0), lay );
    TRect messageRect( layout.Rect() );
    
    aDef.iWindowRect.iTl.iY -= messageRect.Height();
    }

EXPORT_C void AknPopupLayouts::SetupDefaults(TAknPopupWindowLayoutDef &aDef)
    {
    aDef.iVertLineExt1.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
    aDef.iVertLineExt2.LayoutRect(TRect(1,1,1,1), 0, 0,0, ELayoutEmpty, ELayoutEmpty, 0,0);
    }


EXPORT_C TAknPopupWindowLayoutDef::TAknPopupWindowLayoutDef()
    : iMaximumHeight(0)
    {
    
    }

TRect AknPopupLayouts::RectFromLayout(TRect aParent, const TAknWindowComponentLayout &aComponentLayout)
    {
    TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect(aParent,lineLayout);
    return layoutRect.Rect();
    }

// End of File
