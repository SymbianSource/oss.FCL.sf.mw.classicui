/*
* Copyright (c) 2002-2010 Nokia Corporation and/or its subsidiary(-ies).
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

#include <AknLayout2ScalableDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>

#include <touchfeedback.h>
#include <aknlists.h>

const AknLayoutUtils::SAknLayoutRect KEmptyLayout =
    { ELayoutEmpty, 0, 0, 0, 0, ELayoutEmpty, ELayoutEmpty };

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


static TInt GetMaxListHeight( const TRect& aClientRect )
    {
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    
    TAknLayoutRect insideArea;
    insideArea.LayoutRect(
        aClientRect,
        AknLayoutScalable_Avkon::bg_popup_window_pane_g1( isLandscape ) );
        
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
void AknPopupLayouts::HandleSizeChanged( TAknPopupWindowLayoutDef& aDef,
                                         TAknPopupLayouts aLayout_1,
                                         TAknPopupLayoutsNode* aNode )
    {
    CAknPopupHeadingPane* heading =
        static_cast<CAknPopupHeadingPane*>(
            FindControl( aNode, EHeadingNode ) );

    CEikListBox* listBox =
        static_cast<CEikListBox*>( FindControl( aNode, EListNode ) );

    CCoeControl* windowOwningControl = FindControl( aNode, EWindowOwningNode );

    CAknMessageQueryControl* msgQueryCtrl =
        static_cast<CAknMessageQueryControl*>(
            FindControl( aNode, EMessageBoxNode ) );
    
    TInt layoutFlags = aLayout_1;
    TInt numofitems = listBox->Model()->NumberOfItems();

    // Position popup window's bottom correctly.
    TRect clientRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent,
                                       clientRect );
    
    TInt maxListHeight = GetMaxListHeight( clientRect );
    
    TRect nullRect( 0, 0, 0, 0 );

    TBool isLandscape = Layout_Meta_Data::IsLandscapeOrientation(); 
    
    // Set windowRect to minimum size - this will be adjusted later.
    TAknLayoutRect windowRectLayout;
    windowRectLayout.LayoutRect(
        clientRect,
        AknLayoutScalable_Avkon::popup_menu_window( isLandscape ? 19 : 8 ) );
    aDef.iWindowRect = windowRectLayout.Rect();

    TRAP_IGNORE( listBox->View()->ItemDrawer()->SetSkinEnabledL( ETrue ) );
    
    // Popup window when the size does not change based on the number of items.
    TBool fixedWindowSize = EFalse;
    if ( layoutFlags & EAknPopupLayoutsDynamic ||
         numofitems == 0 ||
         layoutFlags & EAknPopupLayoutsFind )
        {
        layoutFlags &= ~EAknPopupLayoutsDynamic;
        fixedWindowSize = ETrue;
        }
        
    // heading =============================================================
    TInt spaceForHeading = 0;
    if ( heading )
        {
        heading->SetLayout( CAknPopupHeadingPane::EListHeadingPane ); 
        TAknLayoutRect tempHeadingRect;
        tempHeadingRect.LayoutRect(
            clientRect,
            AknLayoutScalable_Avkon::heading_pane( 0 ) );
        spaceForHeading = tempHeadingRect.Rect().Height();
        maxListHeight -= spaceForHeading;
        }
    aDef.iPopupMenuWindowOffset.SetXY( 0, spaceForHeading );
        
    
    // findbox =============================================================
    TBool windowSizeFind = EFalse;
    TInt spaceForFind = 0;
    if ( layoutFlags & EAknPopupLayoutsFind )
        {
        layoutFlags &= ~EAknPopupLayoutsFind;
        windowSizeFind = ETrue;
        // Calculate space needed for find box.
        TAknLayoutRect tempFindRect;
        tempFindRect.LayoutRect(
            clientRect,
            AknLayoutScalable_Avkon::find_popup_pane_cp2( 0 ) );
        spaceForFind = tempFindRect.Rect().Height();
        maxListHeight -= spaceForFind;
        }
    
    // messagebox ==========================================================
    TRect messageRect;
    TInt messageNumOfLines = 0;
    TInt messageBoxItemVariety = 0;
    TBool messageBox = EFalse;
    TAknWindowComponentLayout messageBoxItemLayout;
    if ( msgQueryCtrl && msgQueryCtrl->Lines() > 0 )
        {
        messageBox = ETrue;
        messageNumOfLines = msgQueryCtrl->Lines();

        switch ( messageNumOfLines )
            {
            case 0:
            case 1:
                {
                messageBoxItemVariety = 0;
                break;
                }
            case 2:
                {
                messageBoxItemVariety = 1;
                break;
                }
            default:
                {
                messageBoxItemVariety = 2;
                break;
                }
            }           

        messageBoxItemLayout =
            AknLayoutScalable_Apps::loc_type_pane( messageBoxItemVariety );

        TAknLayoutRect layoutRect;
        layoutRect.LayoutRect( nullRect, messageBoxItemLayout );           
        messageRect = layoutRect.Rect();           
        maxListHeight -= messageRect.Height();
        }
    
    TInt minItems = 1;
    
    TRect scrollBarRect( nullRect );
    
    TAknWindowLineLayout listLayout;
    TAknLayoutScalableParameterLimits listLimits;
    
    switch ( layoutFlags )
        {
        case EPopupSNotePopupWindow:
        case EMenuUnknownColumnWindow:
        case EMenuUnknownFormattedCellWindow:
        case EMenuWindow:
            {
            minItems = heading ? 5 : 6;
            listLayout = AknLayoutScalable_Avkon::list_single_pane_cp2( 0 );
            listLimits = AknLayoutScalable_Avkon::list_single_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2( 0 );
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_pane_cp2_ParamLimits();
            break;
            }
        case EMenuGraphicHeadingWindow:
            {
            minItems = 5;
            listLayout = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2( 0 );
            listLimits = AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_pane_cp2( 0 );
            listLimits = AknLayoutScalable_Avkon::list_double_pane_cp2_ParamLimits();
            break;
            }
        case EMenuDoubleLargeGraphicWindow:
            {
            minItems = 3;
            listLayout = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2( 0 );
            listLimits = AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2_ParamLimits();
            break;
            }
        default:
            {
            break;
            }
        }
        
    if ( !fixedWindowSize )
        {
        minItems = 1;
        }

    // Last row is a zero based index, we need num items which is 1 based.
    TInt maxLayoutItems = listLimits.LastRow() + 1;
        
    TAknLayoutRect listItemRect;
    listItemRect.LayoutRect( aDef.iWindowRect, listLayout );
    TInt listItemHeight = listItemRect.Rect().Height();
    TInt maxItems = maxListHeight / listItemHeight;

    // minItems == 1 only if the popuplist is dynamically changeable
    if ( ( numofitems > 1 ) && ( minItems == 1 ) )
        {
        minItems = numofitems;
        }

    if ( minItems > maxItems )
        {
        minItems = maxItems;
        }

    // maxItems might be greater than max items from layout ->
    // use layout's maximum.
    if ( minItems > maxLayoutItems )
        {
        minItems = maxLayoutItems;
        }

    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );

    TAknLayoutRect temp;
    TAknLayoutRect layout;
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect ); 
    TAknWindowLineLayout lineLayout(
        AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ).LayoutLine() );
 
    temp.LayoutRect( windowRect, lineLayout );        

    layout.LayoutRect( temp.Rect(),
                       AknLayoutScalable_Avkon::list_menu_pane( 0 ) );

    // This is list's rect for the whole window.
    TRect tempListRect( layout.Rect() );
    
    // Subtract heading, find box and message box from tempListRect.
    tempListRect.iBr.iY -= spaceForFind;
    tempListRect.iTl.iY += spaceForHeading;
    tempListRect.iTl.iY += messageRect.Height();
    
    // We really don't want parent relative list layout here because find box
    // will be overwritten. Just calculate list height and use that.
    listLayout.iH = (TInt16)( minItems * listItemHeight );
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect( tempListRect, listLayout );

    // We have to scale iWindowRect to list rect - layout is not (yet) correct.
    TInt usedHeight = aDef.iListRect.Rect().Height()
        + spaceForFind
        + spaceForHeading
        + messageRect.Height();

    if ( layout.Rect().Height() < usedHeight )
        {
        aDef.iWindowRect.iTl.iY -= (usedHeight - layout.Rect().Height() );
        }
    
    AknLayoutUtils::TAknCbaLocation cbaLocation = AknLayoutUtils::CbaLocation();    
        
    // In landscape we have to center (on y-axis) popup window
    // (but not with bottom CBA).
    if ( isLandscape &&
         cbaLocation != AknLayoutUtils::EAknCbaLocationBottom )
        {
        TInt diff = ( clientRect.Height() - aDef.iWindowRect.Height() ) / 2;
        aDef.iWindowRect.iTl.iY -= diff;
        aDef.iWindowRect.iBr.iY -= diff;
                        
        // With right CBA, move window to the right side of the screen.
        if ( cbaLocation == AknLayoutUtils::EAknCbaLocationRight )
            {
            TInt offset = clientRect.Width() - aDef.iWindowRect.iBr.iX;
            aDef.iWindowRect.iTl.iX += offset;
            aDef.iWindowRect.iBr.iX += offset;
            }
        }

    TAknLayoutRect cbaRect;
    cbaRect.LayoutRect(
        screenRect, 
        AknLayoutScalable_Avkon::popup_sk_window( 0 ).LayoutLine() );
            
    TSize size( aDef.iWindowRect.Size() );

    // Add softkey height.
    size.iHeight += cbaRect.Rect().Height();
    
    // Reduce listbox's and popup's height if total height is more than
    // screen height.
    if ( size.iHeight > screenRect.Height() )
        {
        listLayout.iH -= ( size.iHeight - screenRect.Height() );
        aDef.iListRect.LayoutRect( tempListRect, listLayout );
        
        size.iHeight = screenRect.Height();
        }

    aDef.iWindowRect.SetRect( AknPopupUtils::Position( size, ETrue ), size );

    // Now we finally know the window rect: first setup heading.
    if ( heading )
        {
        aDef.iHeadingRect.LayoutRect(
            AknPopupLayouts::MenuRect( aDef ),
            AknLayoutScalable_Avkon::heading_pane( 0 ) );
        }
    
    MenuPopupWindowGraphics( aDef );
    windowOwningControl->SetRect( WindowRect( aDef ) );
    HandleSizeAndPositionOfComponents( aDef, listBox, heading );

    layout.LayoutRect( MenuRect( aDef ), lineLayout );
    TRect scrollBarClientRect( layout.Rect() );

    // Remove softkey height that was added earlier so that
    // scroll bar doesn't get behind the softkey.
    scrollBarClientRect.iBr.iY -= cbaRect.Rect().Height();

    if ( heading )
        {
        scrollBarClientRect.iTl.iY += spaceForHeading;                
        }
        
    if ( windowSizeFind )
        {
        scrollBarClientRect.iBr.iY -= spaceForFind;
        }
        
    if ( messageBox )
        {
        scrollBarClientRect.iTl.iY += messageRect.Height();
        }

    AknLayoutUtils::LayoutVerticalScrollBar(
        listBox->ScrollBarFrame(),
        scrollBarClientRect, 
        AknLayoutScalable_Avkon::scroll_pane_cp25( 0 ).LayoutLine() );
        
    if ( messageBox )
        {
        TAknLayoutRect msgQuery;
        msgQuery.LayoutRect( AknPopupLayouts::MenuRect( aDef ),
                             messageBoxItemLayout );
        msgQueryCtrl->SetRect( msgQuery.Rect() );
        }

    windowRect = WindowRect( aDef );
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( listBox );
    TBool defaultContext = EFalse;
    if ( !cc )
        {
        cc = listBox->View()->ItemDrawer()->SkinBackgroundControlContext();
        defaultContext = ETrue;
        }
    if ( cc )
        {
        CAknsBasicBackgroundControlContext* bcc =
            static_cast<CAknsBasicBackgroundControlContext*>( cc );
        bcc->SetBitmap( KAknsIIDQsnFrPopupCenter );
        
        if ( defaultContext )
            {
            bcc->SetRect( windowRect );
            bcc->SetParentPos( TPoint( 0, 0 ) );
            }
        else
            {
            bcc->SetParentPos( windowOwningControl->PositionRelativeToScreen() );
            }
        }
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
EXPORT_C void AknPopupLayouts::HandleDraw( CEikonEnv* /*aEikEnv*/,
                                           CWindowGc& aGc,
                                           const TAknPopupWindowLayoutDef& aDef, 
                                           CEikListBox* aListBox, 
                                           CAknPopupHeadingPane* aHeading )
    {
    TRect windowRect(
        MenuRect( const_cast<TAknPopupWindowLayoutDef&>( aDef ) ) );
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( aListBox );
    TBool windowFrameDrawn = EFalse;

    if ( !cc )
        {
        cc = aListBox->View()->ItemDrawer()->SkinBackgroundControlContext();
        }
    
    TRegionFix<5> dontDrawRegion;
    TRegionFix<22> drawRegion;
    if ( aListBox )
        {
        dontDrawRegion.AddRect( aListBox->Rect() );

        // If there are scroll bars and they draw their own background, take
        // them out of clipping region
        CEikScrollBarFrame* scrollBarFrame = aListBox->ScrollBarFrame();
        if ( scrollBarFrame )
            {
            CEikScrollBar* hBar = scrollBarFrame->GetScrollBarHandle(
                CEikScrollBar::EHorizontal );
            CEikScrollBar* vBar = scrollBarFrame->GetScrollBarHandle(
                CEikScrollBar::EVertical );
            TBool drawHorizontal = ETrue;
            TBool drawVertical = ETrue;
            scrollBarFrame->DrawBackgroundState( drawHorizontal, drawVertical );
            drawHorizontal = drawHorizontal && hBar && hBar->IsVisible();
            drawVertical = drawVertical && vBar && vBar->IsVisible();

            if ( drawHorizontal )
                {
                TRect scrollBarRect( hBar->Rect() );
                if ( hBar->OwnsWindow() )
                    {
                    TPoint windowPos( aDef.iWindowRect.iTl );
                    TPoint scrollBarPos( hBar->PositionRelativeToScreen() );
                    scrollBarRect.Move( scrollBarPos - windowPos );
                    }
                dontDrawRegion.AddRect( scrollBarRect );
                }

            if ( drawVertical )
                {
                TRect scrollBarRect( vBar->Rect() );
                if ( vBar->OwnsWindow() )
                    {
                    TPoint windowPos( aDef.iWindowRect.iTl );
                    TPoint scrollBarPos( vBar->PositionRelativeToScreen() );
                    scrollBarRect.Move( scrollBarPos - windowPos );
                    }

                dontDrawRegion.AddRect( scrollBarRect );
                }
            }
        }

    if ( aHeading )
        {
        dontDrawRegion.AddRect( aHeading->Rect() );
        }

    drawRegion.AddRect( windowRect );
    drawRegion.SubRegion( dontDrawRegion );

    if ( cc )
        {
        const TAknsItemID* popupBgId = &KAknsIIDQsnBgPopupBackground;
        AknsDrawUtils::DrawCachedImage( skin, aGc, windowRect, *popupBgId );

        const TAknsItemID* sliceId = &KAknsIIDQsnBgSlicePopup;
        TAknLayoutRect sliceRect;
        sliceRect.LayoutRect( windowRect,
                              AknLayoutScalable_Avkon::bg_list_pane_g5( 0 ) );
        AknsDrawUtils::DrawCachedImage( skin, aGc, sliceRect.Rect(), *sliceId );
        
        TAknWindowComponentLayout popupBgLayout(
            AknLayoutScalable_Avkon::bg_popup_window_pane( 0 ) ); 
        
        TAknWindowComponentLayout popupBgInnerLayout(
            AknLayoutScalable_Avkon::bg_popup_window_pane_g1(
                Layout_Meta_Data::IsLandscapeOrientation() ) );
        
        TAknLayoutRect topLeft;
        topLeft.LayoutRect(
            windowRect,
            TAknWindowComponentLayout::Compose(
                popupBgLayout,
                TAknWindowComponentLayout::Split( popupBgInnerLayout, 0 ) ) );
        TRect topLeftRect( topLeft.Rect() );

        TAknLayoutRect bottomRight;
        bottomRight.LayoutRect(
            windowRect,
            TAknWindowComponentLayout::Compose(
                popupBgLayout,
                TAknWindowComponentLayout::Split( popupBgInnerLayout, 8 ) ) );
        TRect bottomRightRect( bottomRight.Rect() );
        
        TRect outerRect( topLeftRect.iTl, bottomRightRect.iBr );
        TRect innerRect( topLeftRect.iBr, bottomRightRect.iTl );

        aGc.SetPenStyle( CGraphicsContext::ENullPen );

        const TAknsItemID* frameId = &KAknsIIDQsnFrPopup;
        const TAknsItemID* frameCenterId = &KAknsIIDQsnFrPopupCenter;

        aGc.SetClippingRegion( drawRegion );

        windowFrameDrawn = AknsDrawUtils::DrawFrame( skin,
                                                     aGc,
                                                     outerRect,
                                                     innerRect,
                                                     *frameId,
                                                     *frameCenterId );
        aGc.CancelClippingRegion();
        }

    if ( !windowFrameDrawn )
        {
        AknDraw::DrawWindowShadow( aGc,
                                   aDef.iCover,
                                   aDef.iSecond,
                                   aDef.iFirst,
                                   aDef.iOutline,
                                   aDef.iInside );
        }
    }
#pragma warning(default : 4100)


EXPORT_C TRect AknPopupLayouts::MenuRect(TAknPopupWindowLayoutDef &aDef)
    {
    return TRect(TPoint(0,0), aDef.iWindowRect.Size());
    }


EXPORT_C void AknPopupLayouts::MenuPopupWindowGraphics(
    TAknPopupWindowLayoutDef& aDef )
    {
    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );

    aDef.iCover.LayoutRect(
        windowRect, AknLayoutScalable_Avkon::bg_popup_window_pane_cp2( 0 ) );
    aDef.iSecond.LayoutRect( windowRect, KEmptyLayout );
    aDef.iFirst.LayoutRect(  windowRect, KEmptyLayout );
    aDef.iOutline.LayoutRect(
        windowRect, AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ) );
    aDef.iInside.LayoutRect(
        windowRect, AknLayoutScalable_Avkon::list_menu_pane( 0 ) );
    }


EXPORT_C void AknPopupLayouts::SetupMenuPopupWindow( TAknPopupWindowLayoutDef& aDef,
                                                     TInt aNum,
                                                     TBool aHeading )
    {
    SetupDefaults( aDef );
    
    CommonSetup( aDef,
                 AknLayoutScalable_Avkon::list_single_number_heading_pane_cp2( 0 ),
                 aNum,
                 aHeading,
                 ETrue );
    }


EXPORT_C void AknPopupLayouts::SetupPopupMenuGraphicWindow(
    TAknPopupWindowLayoutDef &aDef,
    TInt aNum,
    TBool aHeading )
    {
    SetupDefaults( aDef );
    
    CommonSetup( aDef,
                 AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2( 0 ),
                 aNum,
                 aHeading,
                 ETrue );
    }


EXPORT_C void AknPopupLayouts::SetupPopupMenuGraphicHeadingWindow(
    TAknPopupWindowLayoutDef &aDef,
    TInt aNum,
    TBool aHeading )
    {
    CommonSetup( aDef,
                 AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2( 0 ),
                 aNum,
                 aHeading,
                 EFalse );

    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );
    aDef.iHeadingRect.LayoutRect( windowRect,
                                  AknLayoutScalable_Avkon::heading_pane( 0 ) );
    }


EXPORT_C void AknPopupLayouts::SetupPopupMenuDoubleWindow(
    TAknPopupWindowLayoutDef& aDef,
    TInt aNum,
    TBool aHeading )
    {
    SetupDefaults( aDef );
    
    CommonSetup( aDef,
                 AknLayoutScalable_Avkon::list_double2_graphic_pane_cp2( 0 ),
                 aNum,
                 aHeading,
                 EFalse );

    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );
    aDef.iHeadingRect.LayoutRect( windowRect,
                                  AknLayoutScalable_Avkon::heading_pane( 0 ) );
    }


EXPORT_C void AknPopupLayouts::SetupImageSelectionMenuPopupWindow(
    TAknPopupWindowLayoutDef& aDef,
    TInt aNum,
    TBool aHeading )
    {
    SetupDefaults( aDef );

    CommonSetup( aDef,
                 AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2( 0 ),
                 aNum,
                 aHeading,
                 EFalse );
    
    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );
    aDef.iHeadingRect.LayoutRect( windowRect,
                                  AknLayoutScalable_Avkon::heading_pane( 0 ) );
    }


EXPORT_C void AknPopupLayouts::SetupPopupSNoteGroupWindow(
    TAknPopupWindowLayoutDef &aDef,
    TInt aNum,
    TBool /*aHeading*/ )
    {
    // Not used (at least by AvKon) - no need to remove magic numbers.
    SetupDefaults( aDef );
    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );
    aDef.iListRect.LayoutRect( windowRect,
                               0,
                               3,
                               11,
                               ELayoutEmpty,
                               ELayoutEmpty,
                               168,
                               38 + ( 57 - 38 ) * ( aNum - 2 ) );

    TAknWindowLineLayout part1(
        AknLayoutScalable_Avkon::heading_pane( 0 ).LayoutLine() );

    TAknWindowLineLayout part2(
        TAknWindowComponentLayout::Compose(
            TAknWindowComponentLayout::Compose(
                TAknWindowComponentLayout::SiblingAsChild(
                    AknLayoutScalable_Avkon::popup_window_general( 1 ),
                    AknLayoutScalable_Avkon::popup_window_general( 0 ) ),
                AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ) ),
            AknLayoutScalable_Avkon::list_menu_pane( 0 ) ).LayoutLine() );
    
    // Combine two layouts togeher.
    if ( part2.iC != ELayoutEmpty ) part1.iC = part2.iC;
    if ( part2.il != ELayoutEmpty ) part1.il = part2.il;
    if ( part2.it != ELayoutEmpty ) part1.it = part2.it;
    if ( part2.ir != ELayoutEmpty ) part1.ir = part2.ir;
    if ( part2.ib != ELayoutEmpty ) part1.ib = part2.ib;
    if ( part2.iW != ELayoutEmpty ) part1.iW = part2.iW;
    if ( part2.iH != ELayoutEmpty ) part1.iH = part2.iH;

    aDef.iHeadingRect.LayoutRect( windowRect, part1 );

    TInt p = windowRect.Size().iHeight;
    const AknLayoutUtils::SAknLayoutRect shadow[] =
    {   
        { 0,   0, 0,  ELayoutEmpty, ELayoutEmpty, 176, p },
        { 86,  7, 12, ELayoutEmpty, ELayoutEmpty, 167, p - 16 },
        { 221, 4, 10, ELayoutEmpty, ELayoutEmpty, 169, p - 15 },
        { 215, 2, 8,  ELayoutEmpty, ELayoutEmpty, 170, p - 14 },
        { 0,   3, 9,  ELayoutEmpty, ELayoutEmpty, 168, p - 16 }
    };

    aDef.iCover.LayoutRect( windowRect, shadow[0] );
    aDef.iSecond.LayoutRect( windowRect, shadow[1] );
    aDef.iFirst.LayoutRect( windowRect, shadow[2] );
    aDef.iOutline.LayoutRect(windowRect, shadow[3] );
    aDef.iInside.LayoutRect( windowRect, shadow[4] );    
    }


EXPORT_C void AknPopupLayouts::CalcPopupMenuWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt aNum )
    {
    TInt variety;
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // Popup menu window is wider in landscape orientation.
        variety = ( aNum < 7 ) ? 20 - aNum : 43;
        }
    else
        {
        variety = 7 + aNum;
        }

    TAknLayoutRect popupMenuWindow;
    popupMenuWindow.LayoutRect(
        aRect,
        AknLayoutScalable_Avkon::popup_menu_window( variety ) );
    aDef.iWindowRect = popupMenuWindow.Rect();
    aDef.iPopupMenuWindowOffset.SetXY( 0, 0 );
    }


EXPORT_C void AknPopupLayouts::CalcPopupMenuGraphicWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt aNum )
    {
    CalcPopupMenuWindow( aDef, aRect, aNum );
    }


EXPORT_C void AknPopupLayouts::CalcPopupMenuGraphicHeadingWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt aNum )
    {
    CalcPopupMenuWindow( aDef, aRect, aNum );
    }


EXPORT_C void AknPopupLayouts::CalcPopupMenuDoubleWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt aNum )
    {
    TBool isLandscape( Layout_Meta_Data::IsLandscapeOrientation() );
    
    TInt variety = isLandscape ? 26 : 2;
    if ( aNum == 2 )
        {
        variety = isLandscape ? 25 : 1;
        }
    else if ( aNum == 1 )
        {
        variety = isLandscape ? 24 : 0;
        }

    TAknLayoutRect popupMenuDoubleWindow;
    popupMenuDoubleWindow.LayoutRect(
        aRect, AknLayoutScalable_Avkon::popup_menu_window( variety ) );
    aDef.iWindowRect = popupMenuDoubleWindow.Rect();
    aDef.iPopupMenuWindowOffset.SetXY( 0, 0 );
    }


EXPORT_C void AknPopupLayouts::CalcPopupMenuDoubleLargeGraphicWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt aNum )
    {
    CalcPopupMenuDoubleWindow( aDef, aRect, aNum );
    }


EXPORT_C void AknPopupLayouts::CalcPopupSNoteGroupWindow(
    TAknPopupWindowLayoutDef& aDef,
    TRect aRect,
    TInt /*aNum*/ )
    {
    // Layout for this isn't specified in the layout data,
    // use the provided rect. 
    aDef.iWindowRect = aRect;
    aDef.iPopupMenuWindowOffset.SetXY( 0, 0 );
    }    


EXPORT_C TRect AknPopupLayouts::WindowRect(TAknPopupWindowLayoutDef &aDef) {return aDef.iWindowRect; }


EXPORT_C void AknPopupLayouts::ModifyWindowGraphicForHeading(
    TAknPopupWindowLayoutDef& aDef )
    {
    TRect nullRect( 0, 0, 0, 0 );
    TAknLayoutRect nullHeadingRect;

    TAknWindowComponentLayout popupWindowLayout(
        TAknWindowComponentLayout::SiblingAsChild(
                    AknLayoutScalable_Avkon::popup_window_general( 0 ),
                    AknLayoutScalable_Avkon::popup_window_general( 1 ) ) );
    
    // Find out how much space is needed for heading.
    nullHeadingRect.LayoutRect( nullRect, popupWindowLayout );
    TInt spaceForHeading = nullHeadingRect.Rect().Height();

    // This is necessary to position it correctly.
    aDef.iWindowRect.iTl.iY -= spaceForHeading;

    // this is because b=0 in parent of coverrect and because
    // parent's height is used in the child...
    TRect windowRect( aDef.iWindowRect );

    aDef.iCover.LayoutRect( windowRect, popupWindowLayout );
    aDef.iSecond.LayoutRect( windowRect, KEmptyLayout );
    aDef.iFirst.LayoutRect( windowRect, KEmptyLayout );
    aDef.iOutline.LayoutRect( windowRect, KEmptyLayout );
    aDef.iInside.LayoutRect( windowRect, KEmptyLayout );
    
    aDef.iPopupMenuWindowOffset.SetXY( 0, spaceForHeading );
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


void AknPopupLayouts::CommonSetup( TAknPopupWindowLayoutDef& aDef,
                                   const TAknWindowComponentLayout& aItemLayout,
                                   TInt aNum,
                                   TBool aHeading,
                                   TBool aLayoutHeading )
    {
    TRect windowRect( AknPopupLayouts::MenuRect( aDef ) );

    TAknWindowLineLayout listWithHeadingLayout(
        TAknWindowComponentLayout::Compose(
            TAknWindowComponentLayout::Compose(
                TAknWindowComponentLayout::SiblingAsChild(
                    AknLayoutScalable_Avkon::popup_window_general( 1 ),
                    AknLayoutScalable_Avkon::popup_window_general( 0 ) ),
                AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ) ),
            AknLayoutScalable_Avkon::list_menu_pane( 0 ) ).LayoutLine() );

    TAknWindowLineLayout listLayout( listWithHeadingLayout );
    
    if ( !aHeading )
        {
        listLayout = TAknWindowComponentLayout::Compose(
            AknLayoutScalable_Avkon::listscroll_menu_pane( 0 ),
            AknLayoutScalable_Avkon::list_menu_pane( 0 ) ).LayoutLine();
        }
    
    // We really don't want parent relative list layout here because findbox
    // will be overwritten. Just calculate list height and use that.
    TRect nullRect( 0, 0, 0, 0 );
    TRect listItemRect( RectFromLayout( nullRect, aItemLayout ) );
    listLayout.iH = (TInt16)( aNum * listItemRect.Height() );
    listLayout.ib = ELayoutEmpty;

    aDef.iListRect.LayoutRect( windowRect, listLayout );

    if ( aLayoutHeading )
        {
        TAknWindowLineLayout part1(
            AknLayoutScalable_Avkon::heading_pane( 0 ).LayoutLine() );
        TAknWindowLineLayout part2( listWithHeadingLayout );
    
        // Combine two layouts togeher.
        if ( part2.iC != ELayoutEmpty ) part1.iC = part2.iC;
        if ( part2.il != ELayoutEmpty ) part1.il = part2.il;
        if ( part2.it != ELayoutEmpty ) part1.it = part2.it;
        if ( part2.ir != ELayoutEmpty ) part1.ir = part2.ir;
        if ( part2.ib != ELayoutEmpty ) part1.ib = part2.ib;
        if ( part2.iW != ELayoutEmpty ) part1.iW = part2.iW;
        if ( part2.iH != ELayoutEmpty ) part1.iH = part2.iH;
    
        aDef.iHeadingRect.LayoutRect( windowRect, part1 );
        }
    }

// End of File
