/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikfrlb.h>
#include <barsread.h>
#include <gulicon.h>
#include <AknUtils.h>
#include <AknsControlContext.h>
#include <AknBidiTextUtils.h>
#include <aknlists.h>
#include <aknlayoutscalable_avkon.cdl.h>

#include <AknTasHook.h>
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#include <aknlistboxtfx.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <akntransitionutils.h>
#endif

#include "akntrace.h"

_LIT(KMarkReplacementString, "%S");
//
// CFormattedCellListBoxItemDrawer
//

EXPORT_C 
CFormattedCellListBoxItemDrawer::CFormattedCellListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, 
                                 const CFont* aFont, 
                                 CFormattedCellListBoxData* aFormattedCellData)
    : CTextListItemDrawer(aTextListBoxModel, aFont)
    {
    _AKNTRACE_FUNC_ENTER;
    SetData(aFormattedCellData);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C 
CFormattedCellListBoxItemDrawer::~CFormattedCellListBoxItemDrawer()
    {   
    _AKNTRACE_FUNC_ENTER;
    delete iPropertyArray;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CFormattedCellListBoxData* 
CFormattedCellListBoxItemDrawer::FormattedCellData() const
    {
    return STATIC_CAST(CFormattedCellListBoxData*,iData);
    }
EXPORT_C CFormattedCellListBoxData* 
CFormattedCellListBoxItemDrawer::ColumnData() const
    {
    return STATIC_CAST(CFormattedCellListBoxData*,iData);
    }


EXPORT_C void CFormattedCellListBoxView::DrawEmptyList(const TRect &aClientRect) const 
    {
    _AKNTRACE_FUNC_ENTER;    
    if ( RedrawDisabled() || !IsVisible() )
        {
        _AKNTRACE( "[%s][%s] RedrawDisabled or view invisible","CFormattedCellListBoxView",__FUNCTION__);
        _AKNTRACE_FUNC_EXIT;
        return;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    CWindowGc* systemGc = ( CWindowGc* )CAknTransitionUtils::GetData( ( TInt )this );
    AknDrawWithSkins::DrawEmptyList( aClientRect,
                                     systemGc ? *systemGc : *iGc,
                                     *EmptyListText(),
                                     ((CFormattedCellListBoxItemDrawer*)ItemDrawer())->FormattedCellData()->Control() );
#else
    AknDrawWithSkins::DrawEmptyList( aClientRect,
                                     *iGc,
                                     *EmptyListText(),
                                     ((CFormattedCellListBoxItemDrawer*)ItemDrawer())->FormattedCellData()->Control() );
#endif
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CFormattedCellListBoxView::CalcBottomItemIndex()
    {
    CListBoxView::CalcBottomItemIndex();

    CFormattedCellListBoxItemDrawer* itemDrawer = 
        STATIC_CAST(CFormattedCellListBoxItemDrawer*,iItemDrawer);
    if (itemDrawer && itemDrawer->FormattedCellData() &&
        itemDrawer->FormattedCellData()->Control())
        {
        CEikFormattedCellListBox* listbox = STATIC_CAST(CEikFormattedCellListBox*, 
            itemDrawer->FormattedCellData()->Control());
        listbox->SetIconSizes();
        }

    // The next piece of code removes filtering from find box when
    // new list items are added.
    if (Flags() & CListBoxView::EItemCountModified)
    {
    CAknFilteredTextListBoxModel *model = STATIC_CAST(CAknFilteredTextListBoxModel*,iModel);
    CAknListBoxFilterItems *filter = model ? model->Filter() : 0;
    if (filter) 
        {
        TRAP_IGNORE(filter->ResetFilteringL());
        }
    }
    }

EXPORT_C TAny* CFormattedCellListBoxView::Reserved_1()
    {
    return NULL;
    }

EXPORT_C void
CFormattedCellListBoxItemDrawer::DrawEmptyItem( TInt /*aItemIndex*/,
                                                TPoint aItemRectPos,
                                                TBool /*aViewIsDimmed*/ ) const
    {
    _AKNTRACE_FUNC_ENTER;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    TRect r( aItemRectPos, iItemCellSize );
    CCoeControl* control = FormattedCellData()->Control();
    
    const MCoeControlBackground* backgroundDrawer = control->FindBackground();
    
    if ( control )
        {
        MAknsControlContext *cc = AknsDrawUtils::ControlContext( control );

        if ( !cc )
            {
            cc = FormattedCellData()->SkinBackgroundContext();
            }

        if ( backgroundDrawer )
            {
            backgroundDrawer->Draw( *iGc, *control, r );
            }
        else if ( CAknEnv::Static()->TransparencyEnabled() )
            {
            AknsDrawUtils::Background( AknsUtils::SkinInstance(), cc, control, *iGc, r,
                                   KAknsDrawParamNoClearUnderImage );
            }
        else
            {
            AknsDrawUtils::Background( AknsUtils::SkinInstance(), cc, control, *iGc, r,
                                   KAknsDrawParamNoClearUnderImage |
                                   KAknsDrawParamBottomLevelRGBOnly );
            }
        }
    else
        {
        iGc->Clear( r );
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    _AKNTRACE_FUNC_EXIT;
    }

struct TLafTable;
const TLafTable &BgListPaneTable();

EXPORT_C
void CFormattedCellListBoxItemDrawer::DrawItemText( TInt aItemIndex,
                                                    const TRect& aItemTextRect,
                                                    TBool aItemIsCurrent,
                                                    TBool aViewIsEmphasized, 
                                                    TBool aItemIsSelected) const
    {
    _AKNTRACE_FUNC_ENTER;
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    iGc->SetPenColor(iTextColor);
    iGc->SetBrushColor(iBackColor);

    TPtrC temp=iModel->ItemText(aItemIndex);

    SetupGc(aItemIndex);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

    TBool removeicon = (!aItemIsSelected && !ItemMarkReverse()) || (aItemIsSelected && ItemMarkReverse());

    CFormattedCellListBoxData::TColors colors;
    colors.iText=iTextColor;
    colors.iBack=iBackColor;
    colors.iHighlightedText=iHighlightedTextColor;
    colors.iHighlightedBack=iHighlightedBackColor;

    DrawBackgroundAndSeparatorLines( aItemTextRect );
   
    TBool highlightShown = ETrue;
    
    if (FormattedCellData()->RespectFocus() && !aViewIsEmphasized)
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->Remove( MAknListBoxTfxInternal::EListHighlight );
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

        highlightShown = EFalse;
        }
        
    if (FormattedCellData()->IsMarqueeOn() && FormattedCellData()->CurrentMarqueeItemIndex() != aItemIndex && aItemIsCurrent)
        {
        FormattedCellData()->ResetMarquee();
        FormattedCellData()->SetCurrentMarqueeItemIndex(aItemIndex);
        }
    
    if ( aItemIsCurrent )
        {
        FormattedCellData()->SetCurrentItemIndex( aItemIndex );
        }
        
    FormattedCellData()->SetCurrentlyDrawnItemIndex( aItemIndex );
    
    // drawing with mark icon
    if ( Flags() & EDrawMarkSelection && ItemMarkPosition() != -1 && removeicon)
        {
        // Try to allocate buffer dynamically. If out of memory, just use normal drawing
        // without mark icon.
        // (+2 is for the possible 2 additional column separators)
        TPtrC repl;
        repl.Set( ItemMarkReplacement() );        
        TInt size = temp.Length() + repl.Length() + 2;
        //TBufC<KMaxTotalDataLength> target(KNullDesC);
        HBufC* buffer = HBufC::New( size );

        if( buffer )
            {
            TPtr des = buffer->Des();
            TInt markPos = ItemMarkPosition(); // -1 if not set
            TInt startPos(0);
            TInt endPos(0);
            
            while( endPos < temp.Length() && markPos >= 0 )
                {
                if( temp[endPos] == '\t' )
                    {
                    markPos--;
                    if( markPos == 0 )
                        {
                        startPos = endPos + 1; // +1 for column separator
                        }
                    }
                endPos++;
                }

            if( markPos > 0 ) // mark icon will go somewhere after item string...
                {
                startPos = temp.Length();
                endPos = temp.Length();
                des.Append( temp.Left( startPos ) ); // first part of string
                des.Append( '\t' ); // column separator before mark icon was missing                
                }
            else
                {
                des.Append( temp.Left( startPos ) ); // first part of string
                }

            TInt replace = repl.FindF(KMarkReplacementString);
            if (replace != KErrNotFound) // moving subcell
                {
                des.Append( repl.Left( replace ) );
                // now we have first part of string + mark subcell
                // then add 1 moved subcell
                des.Append( temp.Mid( startPos, endPos-startPos ) );

                // skip second moved subcell and add rest of the string
                while( endPos < temp.Length() )
                    {
                    if( temp[endPos] == '\t' )
                        {
                        break;
                        }
                    endPos++;
                    }
                if( endPos < temp.Length() ) // this cuts off '\t'
                    {
                    endPos++;
                    }
                des.Append( temp.Mid( endPos ) );
                
                //is this needed - currently not used in S60?
                //buffer.Append(aReplacement->Mid(replace+2)); // 2 == length of %s
                }
            else // just replacement
                {
                des.Append( repl ); // no '%s' in replacement string
                des.Append( '\t' );
                des.Append( temp.Mid( endPos ) );
                }

            des.Set( buffer->Des() );
            FormattedCellData()->Draw( Properties(aItemIndex),
                                       *iGc,
                                       &des,
                                       aItemTextRect,
                                       aItemIsCurrent && highlightShown,
                                       colors );
            delete buffer;
            return;
            }
        }

    // normal drawing without mark icon
    FormattedCellData()->Draw( Properties(aItemIndex),
                               *iGc,
                               &temp,
                               aItemTextRect,
                               aItemIsCurrent && highlightShown,
                               colors );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TSize 
CFormattedCellListBoxItemDrawer::MinimumCellSize() const 
    {
    CFormattedCellListBoxData* data=FormattedCellData();
    const TInt cells=data->LastSubCell();
    if (cells==-1)
        return CTextListItemDrawer::MinimumCellSize();
    TInt width=0;
    TInt height=0;
    for(TInt ii=0;ii<cells;ii++) 
        {
        TPoint endpos( data->SubCellPosition(ii) + data->SubCellSize(ii) );
        if (endpos.iX > width) width = endpos.iX;
        if (endpos.iY > height) height = endpos.iY;
        }
    height+=VerticalInterItemGap();
    return TSize(width,height);
    }


EXPORT_C void CFormattedCellListBoxItemDrawer::DrawItemMark(TBool /*aItemIsSelected*/, TBool /*aViewIsDimmed*/, const TPoint& /*aMarkPos*/) const
    {
    }


EXPORT_C TInt 
CFormattedCellListBoxItemDrawer::ItemWidthInPixels(TInt) const
    {
    TInt itemWidth = MinimumCellSize().iWidth;
    
    if (iDrawMark)
        itemWidth += (iMarkColumnWidth + iMarkGutter);
    return itemWidth;
    }

EXPORT_C void CFormattedCellListBoxItemDrawer::SetItemCellSize(
    const TSize& aSizeInPixels )
    {
    CTextListItemDrawer::SetItemCellSize( aSizeInPixels );

    // Data needs the cell size to create/reconfigure highlight animations
    FormattedCellData()->SetItemCellSize( iItemCellSize );
    }

EXPORT_C void CFormattedCellListBoxItemDrawer::SetTopItemIndex(TInt aTop)
    {
    iTopItemIndex = aTop;
    }

void 
CFormattedCellListBoxItemDrawer::DrawCurrentItemRect(const TRect& aRect) const
    {
    _AKNTRACE_FUNC_ENTER;    
    iGc->SetClippingRect(iViewRect);
    iGc->SetBrushStyle(CGraphicsContext::ENullBrush);
    iGc->SetPenColor(iHighlightedBackColor);
    iGc->DrawRect(aRect);
    iGc->CancelClippingRect();
    _AKNTRACE_FUNC_EXIT;
    }


//
// CEikFormattedCellListBox
//

EXPORT_C 
CEikFormattedCellListBox::CEikFormattedCellListBox()
    {
    AKNTASHOOK_ADD( this, "CEikFormattedCellListBox" );
    }

EXPORT_C void 
CEikFormattedCellListBox::ConstructFromResourceL(TResourceReader& aReader)
    {
    RestoreCommonListBoxPropertiesL(aReader);   
    iRequiredCellCharWidth=aReader.ReadInt16();

    iModel=new(ELeave) CAknFilteredTextListBoxModel;
    TInt array_id=aReader.ReadInt32();
    if (!array_id)
        {
        ((CTextListBoxModel*)iModel)->ConstructL();
        }
    else
        {
        CDesCArray* desArray=iCoeEnv->ReadDesCArrayResourceL(array_id);
        CleanupStack::PushL(desArray);

        ((CTextListBoxModel*)iModel)->ConstructL(desArray);
        CleanupStack::Pop();
        }
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);

    EnableExtendedDrawingL();

    ((CFormattedCellListBoxItemDrawer*)iItemDrawer)->SetCellWidthInChars(iRequiredCellCharWidth);
    CreateViewL();
    }

EXPORT_C void 
CEikFormattedCellListBox::ConstructL(const CCoeControl* aParent, 
                    TInt aFlags)
    {
    CAknFilteredTextListBoxModel* model=new(ELeave) CAknFilteredTextListBoxModel;
    iModel=model;
    model->ConstructL();
    CreateItemDrawerL();

    EnableExtendedDrawingL();

    iItemDrawer->SetDrawMark(EFalse);
    CEikListBox::ConstructL(aParent,aFlags);
    }

EXPORT_C CTextListBoxModel* 
CEikFormattedCellListBox::Model() const
    {
    return(CTextListBoxModel*)iModel;
    }

EXPORT_C CFormattedCellListBoxItemDrawer* 
CEikFormattedCellListBox::ItemDrawer() const
    {
    return(CFormattedCellListBoxItemDrawer*)iItemDrawer;
    }

EXPORT_C void CEikFormattedCellListBox::UseLogicalToVisualConversion(
    TBool aUseConversion )
    {
    static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer )->
        FormattedCellData()->UseLogicalToVisualConversion(
            aUseConversion );
    }

/**
* Note that it must be possible to call this method multiple times.
*/
EXPORT_C void CEikFormattedCellListBox::EnableExtendedDrawingL()
    {
    // Assert that the item drawer has been created before calling this method.
    __ASSERT_DEBUG( ItemDrawer() && ItemDrawer()->FormattedCellData(),
        Panic( EAknPanicListBoxItemDrawerNotCreated ) );

    CFormattedCellListBoxData* data = ItemDrawer()->FormattedCellData();

    data->SetControl( this );
    // Can be created only after the control has been set.
    data->CreatePictographInterfaceL();
    // Can be created only after the control has been set.
    data->CreateMarqueeControlL();
    }

#ifdef RD_LIST_STRETCH
EXPORT_C void CEikFormattedCellListBox::EnableStretching( const TBool aEnabled )
    {
    if ( ItemDrawer()->FormattedCellData()->StretchingEnabled() != aEnabled )
        {
        ItemDrawer()->FormattedCellData()->EnableStretching( aEnabled );
        SizeChanged();
        }
    }
#else
EXPORT_C void CEikFormattedCellListBox::EnableStretching( const TBool /*aEnabled*/ )
    {
    }
#endif // RD_LIST_STRETCH

#ifdef RD_LIST_STRETCH
EXPORT_C void CEikFormattedCellListBox::HideSecondRow( const TBool aHide )
    {
    if ( ItemDrawer()->FormattedCellData()->SecondRowHidden() != aHide )
        {
        ItemDrawer()->FormattedCellData()->HideSecondRow( aHide );
        SizeChanged();
        }
    }
#else
EXPORT_C void CEikFormattedCellListBox::HideSecondRow( const TBool /*aHide*/ )
    {
    }
#endif // RD_LIST_STRETCH

EXPORT_C void 
CEikFormattedCellListBox::CreateItemDrawerL()
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C TInt CEikFormattedCellListBox::AdjustRectHeightToWholeNumberOfItems(TRect &aRect) const
    {
    TInt remainder = aRect.Height() % iItemHeight;
    aRect.iBr.iY -= remainder;

    return remainder;
    }

EXPORT_C CListBoxView*
CEikFormattedCellListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CFormattedCellListBoxView);
    }

EXPORT_C void CEikFormattedCellListBox::FocusChanged( TDrawNow aDrawNow )
    {
    CEikTextListBox::FocusChanged( aDrawNow );

    // Data needs focus change information to control animations.
    if( IsFocused() )
        {
        ItemDrawer()->FormattedCellData()->FocusGained();
        }
    else
        {
        ItemDrawer()->FormattedCellData()->FocusLost();
        }
    }

EXPORT_C void 
CEikFormattedCellListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikTextListBox::GetColorUseListL(aColorUseList);
    }

EXPORT_C void 
CEikFormattedCellListBox::HandleResourceChange(TInt aType)
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        _AKNTRACE("CEikFormattedCellListBox::HandleResourceChange type=KEikDynamicLayoutVariantSwitch");
        TRAP_IGNORE(
               ItemDrawer()->FormattedCellData()->SetupSkinContextL() );
        }
    	
    CEikTextListBox::HandleResourceChange(aType);
    ItemDrawer()->FormattedCellData()->HandleResourceChange( aType );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TTypeUid::Ptr CEikFormattedCellListBox::MopSupplyObject(TTypeUid aId)
    {
    if ( aId.iUid == MAknsControlContext::ETypeId )
        {
        return MAknsControlContext::SupplyMopObject(
            aId, ItemDrawer()->ColumnData()->SkinBackgroundContext() );
        }
    return CEikTextListBox::MopSupplyObject( aId );
    }

// This helper function sets icon sizes for visible list items.
void CEikFormattedCellListBox::SetIconSizes()
    {
    // No icon size setting when kinetic scrolling enabled
    if ( ItemDrawer()->ColumnData()->KineticScrollingEnabled() )
    	{
        return;    	
    	}
    // if you modify this method, check also eikclb.cpp
    if (!IsReadyToDraw())
        {
        return; // can't access listdata yet
        }

    TInt numOfItems = Model()->NumberOfItems();
    // we have a filtered list, and it's item count might not be correct
    // since this is called when filtered model and text list box model
    // have yet not synced their item count
    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,Model())->Filter();
    if (filter)
    //if ( Model()->MatchableTextArray() )  // read as: if ( HaveFilter() )
        {
        // so we need to use this ugly hack
        TInt n = Model()->MatchableTextArray()->MdcaCount();
        numOfItems = n > numOfItems ? numOfItems : n;
        }

    
    if (numOfItems == 0) // no need to parse anything
        return;

    CArrayPtr<CGulIcon>* icons = ItemDrawer()->FormattedCellData()->IconArray();

    if (!icons || icons->Count() == 0) // no icons set yet
        return;

    TPtrC iconText;
    TInt iconIndex;
    TSize iconSize(0,0);

    for (TInt row=View()->TopItemIndex(); row <= View()->BottomItemIndex(); row++)
        {
        if (row >= numOfItems)
            {
            continue; // grid may have bottomitemindex bigger than item count
            }
        const TDesC &txt = Model()->ItemText(row);

        for (TInt subCell=0; subCell<6; subCell++)
            {
            iconSize = ItemDrawer()->FormattedCellData()->GetSubCellIconSize(subCell);
            // only those subcells that have icons, have also icon size set
            if (iconSize.iWidth == 0 || iconSize.iHeight == 0)
                {
                continue; // no need to set icon size
                }
            TextUtils::ColumnText(iconText, subCell, &txt); // get icon index(text)

            TLex iconLex(iconText);

            if (iconLex.Val(iconIndex) != KErrNone)
                {
                iconIndex = -1;
                }

            CGulIcon *icon;
            CFbsBitmap *bitmap;
            TInt realIndex;
            
            while(iconIndex >= 0)
                {
                if (iconIndex > 0xffff)
                    {
                    realIndex = iconIndex >> 16; // first set highlight icon
                    iconIndex = iconIndex & 0xffff;
                    }
                else
                    {
                    realIndex = iconIndex;
                    iconIndex = -1;
                    }
                    
                if ( realIndex > icons->Count() -1 )
                    {
                    break;
                    }
                icon = (*icons)[realIndex];
                if (!icon)
                    {
                    break;
                    }
                bitmap = icon->Bitmap();
                if (!bitmap)
                    {
                    break;
                    }
                /* note, that SetSize() must be called with
                *  EAspectRatioPreservedAndUnusedSpaceRemoved,
                *  otherwise centering/aligning code in CColumnListBoxData::Draw()
                *  will not work. Default EAspectRatioPreserved parameter
                *  will fill icon with blank extra space, and icon will then
                *  be exactly same size as space reserved for it. Extra blank
                *  space would be added to right side of the icon.
                */
                AknIconUtils::SetSize( bitmap,
                                       iconSize,
                                       EAspectRatioPreservedAndUnusedSpaceRemoved );
                }
        
            
            
            /*switch(1)
                {
                case 1:
                default:
                    if ( iconIndex < 0 || iconIndex > icons->Count() -1 )
                        {
                        break;
                        }

                    icon = (*icons)[iconIndex];
                    if (!icon)
                        {
                        break;
                        }
            
                    bitmap = icon->Bitmap();
            
                    if (!bitmap)
                        {
                        break;
                        }*/
                    /* note, that SetSize() must be called with
                    *  EAspectRatioPreservedAndUnusedSpaceRemoved,
                    *  otherwise centering/aligning code in CColumnListBoxData::Draw()
                    *  will not work. Default EAspectRatioPreserved parameter
                    *  will fill icon with blank extra space, and icon will then
                    *  be exactly same size as space reserved for it. Extra blank
                    *  space would be added to right side of the icon.
                    */
//                    AknIconUtils::SetSize( bitmap,
//                                           iconSize,
//                                           EAspectRatioPreservedAndUnusedSpaceRemoved );
//                }
            } // end subCell for
        } // end row for
    }

EXPORT_C void CEikFormattedCellListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    _AKNTRACE_FUNC_ENTER;
    CEikTextListBox::HandlePointerEventL(aPointerEvent);
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void* CEikFormattedCellListBox::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CEikFormattedCellListBox::CEikListBox_Reserved() 
    {
    }

#define ITEM_EXISTS_BEGIN TInt no_of_items__ = iModel->NumberOfItems()
#define ITEM_EXISTS(x) (((x) > -1) && ((x) < no_of_items__))

#define ITEM_EXISTS_ONCE(x) (((x) > -1) && ((x) < iModel->NumberOfItems()))

EXPORT_C void
CFormattedCellListBoxView::Draw(const TRect* clipRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    if ( RedrawDisabled() || !IsVisible() )
        {
        _AKNTRACE("CFormattedCellListBoxView::Draw return because redraw disabled or invisible");
        _AKNTRACE_FUNC_EXIT;
        return;
        }

   if(clipRect && clipRect->IsEmpty())
        {
        _AKNTRACE("CFormattedCellListBoxView::Draw return because clip rect is empty");
        _AKNTRACE_FUNC_EXIT;
        return;
        }
                
    TInt i = iTopItemIndex;
    CFormattedCellListBoxItemDrawer *itemDrawer = static_cast<CFormattedCellListBoxItemDrawer*>( iItemDrawer );
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    CCoeControl* control = itemDrawer->FormattedCellData()->Control();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( control );
    
    if ( !cc )
        {
        cc = itemDrawer->FormattedCellData()->SkinBackgroundContext();
        }
    
    itemDrawer->SetTopItemIndex( iTopItemIndex );

    if ( iModel->NumberOfItems() > 0 )
        {
		TBool drawingInitiated = ETrue;
		
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi =
            CAknListLoader::TfxApiInternal( iGc );
#endif // RD_UI_TRANSITION_EFFECTS_LIST
		
		if ( CAknEnv::Static()->TransparencyEnabled() )
		    {
    		if ( iWin && iWin->GetDrawRect() == TRect::EUninitialized )
	    		{
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                drawingInitiated = transApi && !transApi->EffectsDisabled();
#else
                drawingInitiated = EFalse;
#endif
    			}

	    	if ( !drawingInitiated )
		    	{
    			iWin->Invalidate( *clipRect );
	    		iWin->BeginRedraw( *clipRect );
		    	}
		    }

        TInt lastPotentialItemIndex = Min( iModel->NumberOfItems(), iTopItemIndex + NumberOfItemsThatFitInRect( iViewRect ) );

        while ( i < lastPotentialItemIndex )      
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iGc->SetClippingRect( iViewRect );
            
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            DrawItem( i++ );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

            iGc->CancelClippingRect();
            
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
        if ( i > iBottomItemIndex + 1 )
            {
            i = iBottomItemIndex + 1;
            }
        TRect usedPortionOfViewRect( iViewRect.iTl+TSize(0,iVerticalOffset), TSize( iViewRect.Width(), ( i - iTopItemIndex ) * iItemHeight ) );
#else
        // clear the unused portion of the viewing area
        TRect usedPortionOfViewRect( iViewRect.iTl.iX, iViewRect.iTl.iY + iVerticalOffset, iViewRect.Width(), ItemPos( lastPotentialItemIndex ).iY );
        
        if ( clipRect )
            {
            usedPortionOfViewRect.iBr.iX = clipRect->iBr.iX;
            }

#endif

        // also clear area behind scroll bar.
        // this is a terrible hack, which is unfortunately needed since layouts
        // leave 2 pixel (in double res) wide margins to both sides of the
        // scroll bar, and there is no other way to do this. This hack is
        // only really valid for main pane lists, but it does not seem to
        // break popup lists, popup field lists or setting page radiobutton
        // lists.
        // See also: eikslb.cpp, eikclb.cpp
        TRect sbbg( iViewRect );   // whole area behind scroll bar
        TRect margin( iViewRect ); // it gets even worse in mirrored layouts
        
        if ( AknLayoutUtils::LayoutMirrored() )
            {
            _AKNTRACE("CFormattedCellListBoxView::Draw Layout mirrored");
            sbbg.iBr.iX = iViewRect.iBr.iX - itemDrawer->LafItemSize().iWidth;

            // in mirrored layouts we also need to draw a margin slice in right
            TRect mainPane;
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
                                               mainPane );
            TAknLayoutRect listscrollAppPane;
            listscrollAppPane.LayoutRect( mainPane,
                                          AknLayoutScalable_Avkon::listscroll_app_pane( 0 ) );

            TInt rMargin = mainPane.iBr.iX - listscrollAppPane.Rect().iBr.iX;
            margin.iTl.iX = margin.iBr.iX - rMargin;
            }
        else
            {
            sbbg.iTl.iX = iViewRect.iTl.iX + itemDrawer->LafItemSize().iWidth;
            }
        
        // Unused portion will be cleared only if listbox background is drawn.
        if ( itemDrawer->ColumnData()->IsBackgroundDrawingEnabled() ) 
            {
            if ( control )
                {
                if ( !control->FindBackground() )
                    {
                    AknsDrawUtils::BackgroundBetweenRects( skin, 
                                                       cc, 
                                                       control, 
                                                       *iGc, 
                                                       iViewRect, 
                                                       usedPortionOfViewRect );

                    AknsDrawUtils::Background( skin, cc, control, *iGc, sbbg );
                
                    if ( AknLayoutUtils::LayoutMirrored() )
                        {
                        AknsDrawUtils::Background( skin, cc, control, *iGc, margin );
                        }
                    }
                }
            else
                {
                iGc->SetBrushColor( BackColor() );
                DrawUtils::ClearBetweenRects( *iGc, iViewRect, usedPortionOfViewRect );
                iGc->Clear( sbbg );
                
                if ( AknLayoutUtils::LayoutMirrored() )
                    {
                    iGc->Clear( margin );
                    }
                }
            }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST  
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST      


		if ( CAknEnv::Static()->TransparencyEnabled() && !drawingInitiated )
			{
			iWin->EndRedraw();
			}
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CFormattedCellListBoxItemDrawer::ClearAllPropertiesL()
    {
    delete iPropertyArray;
    iPropertyArray = NULL;
    iPropertyArray = new (ELeave) CArrayFixFlat<SListProperties>(2);    
    }

EXPORT_C void CFormattedCellListBoxItemDrawer::SetPropertiesL(TInt aItemIndex, TListItemProperties aProperty)
    {
    if (!iPropertyArray) ClearAllPropertiesL();
    TInt index;
    TKeyArrayFix key(0,ECmpTInt);
    SListProperties prop;
    prop.iItem = aItemIndex;
    TInt error = iPropertyArray->FindIsq(prop, key, index);
    if (error)
    { // not found, error is nonzero.
    iPropertyArray->InsertIsqL(prop, key);
    iPropertyArray->FindIsq(prop, key, index);
    }
    iPropertyArray->At(index).iProperties = aProperty;
    }

EXPORT_C 
TListItemProperties CFormattedCellListBoxItemDrawer::Properties(TInt aItemIndex) const
    {

    if (!iPropertyArray) return CTextListItemDrawer::Properties(aItemIndex);
    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,iModel)->Filter();
    if (filter)
    {
    aItemIndex = filter->FilteredItemIndex(aItemIndex);
    }
    TKeyArrayFix key(0,ECmpTInt);
    SListProperties prop;
    prop.iItem = aItemIndex;
    TInt index;
    TInt error = iPropertyArray->FindIsq(prop, key, index);
    if (error) return CTextListItemDrawer::Properties(aItemIndex);
    return iPropertyArray->At(index).iProperties;
    }


static TBool WasClippedHack( const TDesC& aColumntowrap,
                             const TDesC& aWrappedText,
                             const TDesC& aSecondLine )

    {
    // this seems to be only way of chekcing if WrapToArrayL() clipped
    // text or not. Unless you rewrite half of AknBidiTextUtils &&
    // AknTextWrapper. sigh.
    TBool clipped2( EFalse );
    TInt len ( aColumntowrap.Length() ); // length of given text
    TInt wl( aWrappedText.Length() ); // length of 1st + 2nd line
    
    // text will be wrapped at \n or ' ' and that whitespace will be
    // discarded. a BIG assumption is made here, that there are no
    // double spaces in item string at wrapping point. If there are,
    // this does not work as intended.
    len--;
    
    if (  len > wl ) 
        {
        clipped2 = ETrue;
        }
    else if ( len == wl )
        {
        // border case. Only way to check the wrapping is really to
        // check for ellipsis... too bad that WrapToArrayL() does not
        // return any info about clipping. Ellipsis will be either at
        // end of the 2nd string or at start of 2nd string, if
        // mirrored layout is used. Of course, this fails, if length
        // is suitable and there is a ellipsis in the item string. Or
        // if someone manages to create a item string with say arabic
        // & latin characters in such way, that WrapToArrayL() inserts
        // ellipsis in the middle of the string.
        if ( aSecondLine[0] == KEllipsis || aSecondLine[aSecondLine.Length() - 1] == KEllipsis )
            {
            clipped2 = ETrue;
            }
        }
    return clipped2;
    }

void
CFormattedCellListBoxItemDrawer::WordWrapListItem( TPtr& aTarget,
                                                   const TDesC &aItemString,
                                                   TInt aFirstIndex,
                                                   TInt aSecondIndex,
                                                   TInt aItemIndex ) const
    {
    TPtrC columntowrap;
    TextUtils::ColumnText(columntowrap, aFirstIndex, &aItemString);

    if ( !columntowrap.Length() )
        {
        // if nothing to wrap, return string unmodified. Wrapping
        // empty string results in chaos.
        aTarget.Append( aItemString );
        return;
        }
    
    // Set to real values after wrapping successfully done
    TInt firstWordWrappedSubcellIndex = -1;
    TInt secondWordWrappedSubcellIndex = -1;

    // for informing CurrentItemTextWasClipped() about clipping performed here
    TBool clipped1( EFalse );
    TBool clipped2( EFalse );
    // must be cleared, otherwize this will leave bits on
    FormattedCellData()->SetClippedByWrap( 0, EFalse );

    // we have to adjust column widths here if there are any optional icons shown
    TRect firstRect( FormattedCellData()->SubCellPosition(aFirstIndex),
                     FormattedCellData()->SubCellSize(aFirstIndex) );
    TRect secondRect( FormattedCellData()->SubCellPosition(aSecondIndex),
                      FormattedCellData()->SubCellSize(aSecondIndex) );
    TRect overlapRect;
    TInt lastSC = FormattedCellData()->LastSubCell();

    TPtrC scString;
    TBool firstClippedLeft = EFalse;
    TBool firstClippedRight = EFalse;
    TBool secondClippedLeft = EFalse;
    TBool secondClippedRight = EFalse;

    // this should be rewritten for drawformatted_simple - no need to
    // compare rects when layoutdata provides info directly.
    // it might be possible to get rid of compabitility code in
    // SetGraphic|Text|ConditionalSubcell then, altough
    // some exported methods in Eikfrlbd.cpp might benefit from them

    for (TInt subCell=0; subCell <= lastSC; subCell++ )
        {
        TextUtils::ColumnText(scString, subCell, &aItemString);
        if ( scString.Length()
             && FormattedCellData()->SubCellIsNotAlwaysDrawn(subCell) )
            {
            // we have possible overlapping subcell, adjust both firstWidth and
            // secondWidth accordingly
            overlapRect.SetRect( FormattedCellData()->SubCellPosition(subCell),
                                 FormattedCellData()->SubCellSize(subCell) );
            if (firstRect.Intersects(overlapRect))
                {
                if ((overlapRect.iTl.iX-firstRect.iTl.iX) > (firstRect.iBr.iX-overlapRect.iBr.iX))
                    {
                    // overlapping rect is on the right side of first rect
                    firstRect.iBr.iX = overlapRect.iTl.iX;
                    firstClippedRight = ETrue;
                    }
                else
                    {
                    // overlapping rect is on the left side of first rect
                    firstRect.iTl.iX = overlapRect.iBr.iX;
                    firstClippedLeft = ETrue;
                    }
                }
            if (secondRect.Intersects(overlapRect))
                {
                if ((overlapRect.iTl.iX-firstRect.iTl.iX) > (firstRect.iBr.iX-overlapRect.iBr.iX))
                    {
                    // overlapping rect is on the right side of second rect
                    secondRect.iBr.iX = overlapRect.iTl.iX;
                    secondClippedRight = ETrue;
                    }
                else
                    {
                    // overlapping rect is on the left side of second rect
                    secondRect.iTl.iX = overlapRect.iBr.iX;
                    secondClippedLeft = ETrue;
                    }
                }
            }
        else
            {
            continue;
            }
        }

    
    TRAPD( error,
        {
        TPtrC firstString=columntowrap;
        TPtrC secondString;
        TextUtils::ColumnText(secondString, aSecondIndex, &aItemString);

        TInt firstWidth = firstRect.Width();
        if (!firstClippedLeft)
            {
            firstWidth -= FormattedCellData()->SubCellMargins(aFirstIndex).iLeft;
            }
        if (!firstClippedRight)
            {
            firstWidth -= FormattedCellData()->SubCellMargins(aFirstIndex).iRight;
            }

        TInt secondWidth = secondRect.Width();
        if (!secondClippedLeft)
            {
            secondWidth -= FormattedCellData()->SubCellMargins(aSecondIndex).iLeft;
            }
        if (!secondClippedRight)
            {
            secondWidth -= FormattedCellData()->SubCellMargins(aSecondIndex).iRight;
            }

        CArrayFixFlat<TPtrC>* resultArray = new( ELeave ) CArrayFixFlat<TPtrC>( 2 );
        CleanupStack::PushL( resultArray );

        HBufC *wrapped = HBufC::NewLC( KMaxTotalDataLength + 2 * KAknBidiExtraSpacePerLine );
        HBufC *temptarget = HBufC::NewLC( KMaxTotalDataLength );

        // java, among others, may use separate fonts for each row
        const CFont* font1 = FormattedCellData()->RowAndSubCellFont( aItemIndex, aFirstIndex )
            ? FormattedCellData()->RowAndSubCellFont( aItemIndex, aFirstIndex )
            : FormattedCellData()->SubCellFont( aFirstIndex );

        const CFont* font2 = FormattedCellData()->RowAndSubCellFont( aItemIndex, aSecondIndex )
            ? FormattedCellData()->RowAndSubCellFont( aItemIndex, aSecondIndex )
            : FormattedCellData()->SubCellFont( aSecondIndex );

        // If second string is not empty, truncate both first and second
        // line separately in their own lines. It is assumed here that these 2 lines
        // are completely separate and do not share any context.

        if ( secondString.Length() )
            {
            HBufC* convertedLine1 = HBufC::NewLC( firstString.Size()
                                                  + KAknBidiExtraSpacePerLine );

            TPtr ptr1 = convertedLine1->Des();

            HBufC* convertedLine2 = HBufC::NewLC( secondString.Size()
                                                  + KAknBidiExtraSpacePerLine );

            TPtr ptr2 = convertedLine2->Des();

            clipped1 = AknBidiTextUtils::ConvertToVisualAndClip(
                firstString,
                ptr1,
                font1 ? *font1 : *LatinBold13(),
                firstWidth,
                firstWidth );
            
            resultArray->AppendL( TPtrC( *convertedLine1 ) ); 

            clipped2 = AknBidiTextUtils::ConvertToVisualAndClip(
                secondString,
                ptr2,
                font2 ? *font2 : *LatinBold13(),
                secondWidth,
                secondWidth );

            resultArray->AppendL( TPtrC( *convertedLine2 ) ); 
            }
        else         // Otherwise, wrap the first string in 2 lines
            {
            CArrayFixFlat<TInt>* lineWidthArray =
                new( ELeave ) CArrayFixFlat<TInt>( 2 );
            CleanupStack::PushL( lineWidthArray );
            
            lineWidthArray->AppendL(firstWidth);
            lineWidthArray->AppendL(secondWidth);

            *wrapped = columntowrap.Left( KMaxTotalDataLength );
            TPtr ptr = wrapped->Des();

            // this fails to truncate correctly, if lines use different fonts
            AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
                ptr,
                *lineWidthArray,
                font1 ? *font1 : *LatinBold13(),
                *resultArray,
                ETrue );

            CleanupStack::PopAndDestroy(); // lineWidthArray
            }
        
        TInt count = resultArray->Count();
        if (count > 0)
            {
            TPtr ttp = temptarget->Des();
            AknLAFUtils::ReplaceColumn( ttp,
                                        CONST_CAST(TDesC*,&aItemString),
                                        &resultArray->At(0),
                                        '\t',
                                        aFirstIndex );
            
            firstWordWrappedSubcellIndex = aFirstIndex;
            
            if (count > 1)
                {
                AknLAFUtils::ReplaceColumn( aTarget,
                                            temptarget,
                                            &resultArray->At(1),
                                            '\t',
                                            aSecondIndex );
                secondWordWrappedSubcellIndex = aSecondIndex;
                }
            else
                {
                TPtrC empty = secondString;
                AknLAFUtils::ReplaceColumn( aTarget,
                                            temptarget,
                                            &empty,
                                            '\t',
                                            aSecondIndex );
                }
            
            // unfortunately, ConvertToVisualAndWrapToArrayL() does
            // not tell if last line was clipped. Hack around.
            if ( count > 1 )
                {
                clipped2 = WasClippedHack( columntowrap, wrapped->Des(), resultArray->At(1) );
                }
            }
        else
            {
            // Error, use default
            TPtrC empty = firstString;
            AknLAFUtils::ReplaceColumn( aTarget, &empty, &empty,
                                        '\t', aFirstIndex );                 
            }
        
        CleanupStack::PopAndDestroy(); // temptarget
        if (secondString.Length())
            {
            CleanupStack::PopAndDestroy(2); // convertedLine1, convertedLine2
            }
        
        CleanupStack::PopAndDestroy(2); // wrapped, resultArray
        } 

        ); // end of TRAP
    if ( error != KErrNone )
        {
        aTarget.Append(aItemString);
        }

    // Inform drawing routine of word wrapped subcells, which are already
    // converted from logical to visual form.
    // This method is called for each list item before drawing it.
    FormattedCellData()->SetWordWrappedSubcellIndices( 
        firstWordWrappedSubcellIndex,
        secondWordWrappedSubcellIndex );

    // pass info for CurrentItemTextWasClipped()
    TInt clippedCells( 0 );
    
    if ( clipped1 )
        {
        clippedCells |= ( 1 << firstWordWrappedSubcellIndex );
        }

    if ( clipped2 )
        {
        clippedCells |= ( 1 << secondWordWrappedSubcellIndex );
        }
    
    FormattedCellData()->SetClippedByWrap( clippedCells, ETrue );
    }

EXPORT_C void CFormattedCellListBoxItemDrawer::CFormattedCellListBoxItemDrawer_Reserved()
    {
    }

void CFormattedCellListBoxItemDrawer::DrawBackgroundAndSeparatorLines( const TRect& aItemTextRect ) const
    {
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    CCoeControl* control = FormattedCellData()->Control();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( control );

    if ( !cc )
        {
        cc = FormattedCellData()->SkinBackgroundContext();
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    
    if ( transApi && !transApi->EffectsDisabled() )
        {
        MAknListBoxTfx* tfxApi = CAknListLoader::TfxApi( iGc );

        if ( tfxApi )
            {
            tfxApi->EnableEffects( FormattedCellData()->IsBackgroundDrawingEnabled() );
            }
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    // background
    if ( FormattedCellData()->IsBackgroundDrawingEnabled() )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        TBool bgDrawn( EFalse );
        if ( control )
            {
            const MCoeControlBackground* backgroundDrawer =
                control->FindBackground();
            
            if ( backgroundDrawer )
                {
                backgroundDrawer->Draw( *iGc, *control, aItemTextRect );
                bgDrawn = ETrue;
                }
            else if ( CAknEnv::Static()->TransparencyEnabled() )
                {
                bgDrawn = AknsDrawUtils::Background(
                    skin, cc, control, *iGc, aItemTextRect,
                    KAknsDrawParamNoClearUnderImage );
                }
            else
                {
                bgDrawn = AknsDrawUtils::Background(
                    skin, cc, control, *iGc, aItemTextRect,
                    KAknsDrawParamNoClearUnderImage | 
                    KAknsDrawParamBottomLevelRGBOnly );
                }
            }
        if ( !bgDrawn )
            {
            iGc->Clear( aItemTextRect );
            }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST  
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
    }

// End of File
