/*
* Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <barsread.h>
#include <gdi.h>
#include <gulicon.h>
#include <gulutil.h>

#include <eikenv.h>
#include <eikclbd.h>
#include <eikclb.h>
#include <eiklbi.h>
#include <eiktxlbm.h>
#include <eikedwin.h>
#include <eiklbv.h>
#include <AknUtils.h>
#include <eiksfont.h>
#include <AknsDrawUtils.h>
#include <AknsControlContext.h>
#include <aknlists.h>
#include <eikpanic.h>
#include <eikcoctlpanic.h>
#include <aknlayoutscalable_avkon.cdl.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST


#include <AknTasHook.h>

#include "akntrace.h"
//
// Class CEikColumnListBox
//

EXPORT_C CEikColumnListBox::CEikColumnListBox()
//
//    C'tor
//
    {
    __DECLARE_NAME(_S("CEikColumnListBox"));
    AKNTASHOOK_ADD( this, "CEikColumnListBox" );
    }

EXPORT_C void CEikColumnListBox::CreateModelL()
    {
    _AKNTRACE_FUNC_ENTER;
    CTextListBoxModel *model = new(ELeave) CTextListBoxModel;
    iModel = model;
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikColumnListBox::ConstructL(const CCoeControl* aParent,TInt aFlags)
//
//    Defered constructor
//
    {
    _AKNTRACE_FUNC_ENTER;
    CreateModelL();
    ((CTextListBoxModel*)iModel)->ConstructL();

    //CTextListBoxModel* model=new(ELeave) CTextListBoxModel;
    //iModel=model;
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);

    EnableExtendedDrawingL();

    CEikListBox::ConstructL(aParent,aFlags);

    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C TTypeUid::Ptr CEikColumnListBox::MopSupplyObject(TTypeUid aId)
    {
    if (aId.iUid == MAknsControlContext::ETypeId)
        {
        return MAknsControlContext::SupplyMopObject( aId, ItemDrawer()->ColumnData()->SkinBackgroundContext() );
        }
    return CEikTextListBox::MopSupplyObject(aId);
    }

EXPORT_C void CEikColumnListBox::ConstructFromResourceL(TResourceReader& aReader)
//
//    Override base classes resource contructor to provide column model and viewer
//
    {
    _AKNTRACE_FUNC_ENTER;

    RestoreCommonListBoxPropertiesL(aReader);
    iRequiredCellCharWidth=aReader.ReadInt16();
    //iModel=new(ELeave) CColumnListBoxModel;
    CreateModelL();
    //   iModel=new(ELeave) CTextListBoxModel;
    TInt array_id=aReader.ReadInt32();
    if (!array_id)
        {
        //((CColumnListBoxModel*)iModel)->ConstructL();
        ((CTextListBoxModel*)iModel)->ConstructL();
        }
    else
        {
        CDesCArray* desArray=iCoeEnv->ReadDesCArrayResourceL(array_id);
        CleanupStack::PushL(desArray);
        //((CColumnListBoxModel*)iModel)->ConstructL(desArray);
        ((CTextListBoxModel*)iModel)->ConstructL(desArray);
        CleanupStack::Pop();
        }
    // iItemDrawer=new(ELeave) CColumnListBoxItemDrawer((CColumnListBoxModel*)iModel,iEikonEnv->NormalFont());
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);

    EnableExtendedDrawingL();

    ((CColumnListBoxItemDrawer*)iItemDrawer)->SetCellWidthInChars(iRequiredCellCharWidth);
    CreateViewL();

    _AKNTRACE_FUNC_EXIT;
    }

/**
* Note that it must be possible to call this method multiple times.
*/
EXPORT_C void CEikColumnListBox::EnableExtendedDrawingL()
    {
    _AKNTRACE_FUNC_ENTER;
    // Assert that the item drawer has been created before calling this method.
    __ASSERT_DEBUG( ItemDrawer() && ItemDrawer()->ColumnData(),
                    User::Panic( _L("EIKCTL"), EEikPanicListBoxItemDrawerNotCreated ) );

    CColumnListBoxData* data = ItemDrawer()->ColumnData();

    data->SetControl( this );
    // Can be created only after the control has been set.
    data->CreatePictographInterfaceL();
    // Can be created only after the control has been set.
    data->CreateMarqueeControlL();

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CEikColumnListBox::CreateItemDrawerL()
    {
    _AKNTRACE_FUNC_ENTER;

    CColumnListBoxData* columnData=CColumnListBoxData::NewL(/*CCoeEnv::Static()->ScreenDevice(), this*/);
    CleanupStack::PushL( columnData );
    iItemDrawer=new(ELeave) CColumnListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), columnData);
    CleanupStack::Pop();

    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CTextListBoxModel* CEikColumnListBox::Model() const
    {
    //return(CColumnListBoxModel*)iModel;
    return(CTextListBoxModel*)iModel;
    }

EXPORT_C CColumnListBoxItemDrawer* CEikColumnListBox::ItemDrawer() const
    {
    return (CColumnListBoxItemDrawer*) iItemDrawer;
    }

/**
* Creates an item editor in column aColumn, if one does not already exist, and
* starts editing the current item up to a maximum length of aMaxLength characters.
*
* @since ER5U
*/
EXPORT_C void CEikColumnListBox::EditItemL(TInt aColumn, TInt aMaxLength)
    // Start editing given column listbox item
    {
    _AKNTRACE_FUNC_ENTER;

    // if not a bitmap column and the extension exists
    if (!STATIC_CAST(CColumnListBoxItemDrawer*,iItemDrawer)->ColumnData()->ColumnIsGraphics(aColumn))
        {
        MEikListBoxEditor* editor=ItemEditor();
        if (!editor)
            {
            SetItemEditor(new (ELeave) CEikColumnListBoxEditor(Model()));
            const TInt index=View()->CurrentItemIndex();
            TRect rect(View()->ItemPos(index),View()->ItemSize());
            if (STATIC_CAST(CColumnListBoxItemDrawer*,iItemDrawer)->ColumnData()->MakeColumnRect(aColumn,rect))
                {
                SetReasonForFocusLostL(EFocusLostToInternalEditor);
                STATIC_CAST(CEikColumnListBoxEditor*,ItemEditor())->ConstructL(aColumn);
                ItemEditor()->StartEditingL(*this,rect,index,aMaxLength );
                SetReasonForFocusLostL(EFocusLostToExternalControl);
                }
            }
        }

    _AKNTRACE_FUNC_EXIT;
    }

/**
* Gets the list of logical colors employed in the drawing of the control,
* paired with an explanation of how they are used. Appends the list to aColorUseList.
*
* @since ER5U
*/
EXPORT_C void CEikColumnListBox::GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const
    {
    CEikTextListBox::GetColorUseListL(aColorUseList);
    }

/**
* Handles a change to the control's resources of type aType
* which are shared across the environment, e.g. colors or fonts.
*
* @since ER5U
*/
EXPORT_C void CEikColumnListBox::HandleResourceChange(TInt aType)
    {
    _AKNTRACE( "[%s][%s] aType = %d", "CEikColumnListBox", __FUNCTION__, aType );
    // first update ESS text colors
    if( aType == KAknsMessageSkinChange || aType == KEikDynamicLayoutVariantSwitch)
        {
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color;

        // set ESS text color
        TInt error = AknsUtils::GetCachedColor( skin,
                                                color,
                                                KAknsIIDQsnTextColors,
                                                EAknsCIQsnTextColorsCG6 );
        if ( !error )
            {
            ItemDrawer()->ColumnData()->SetESSTextColor( color );
            }

        // set ESS highlighted text color
        error = AknsUtils::GetCachedColor( skin,
                                           color,
                                           KAknsIIDQsnTextColors,
                                           EAknsCIQsnTextColorsCG10 );
        if ( !error )
            {
            ItemDrawer()->ColumnData()->SetESSHighlightedTextColor( color );
            }
        }

    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        TRAP_IGNORE( ItemDrawer()->ColumnData()->SetupSkinContextL() );
        }

    CEikTextListBox::HandleResourceChange(aType);
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SizeChanged();  // is this really needed here ?
        }

    ItemDrawer()->ColumnData()->HandleResourceChange( aType );
    }

EXPORT_C void CEikColumnListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CEikTextListBox::HandlePointerEventL(aPointerEvent);
    }

EXPORT_C void* CEikColumnListBox::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

EXPORT_C void CEikColumnListBox::CEikListBox_Reserved()
    {
    }

EXPORT_C CListBoxView* CEikColumnListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CColumnListBoxView);
    }


// This helper function sets icon sizes for visible list items.
void CEikColumnListBox::SetIconSizes()
    {
    // No icon size setting when kinetic scrolling enabled
    if ( ItemDrawer()->ColumnData()->KineticScrollingEnabled() )
        {
        return;
        }

    // if you modify this, check eikfrlb.cpp also
    if (!IsReadyToDraw())
        {
        return; // can't access listdata yet
        }

    TInt numOfItems = Model()->NumberOfItems();
    // we have a filtered list, and it's item count might not be correct
    // since this is called when filtered model and text list box model
    // have yet not synced their item count
    if ( Model()->MatchableTextArray() )  // read as: if ( HaveFilter() )
        {
        // so we need to use this ugly hack
        TInt n = Model()->MatchableTextArray()->MdcaCount();
        numOfItems = n > numOfItems ? numOfItems : n;
        }

    if (numOfItems == 0) // no need to parse anything
        return;

    CArrayPtr<CGulIcon>* icons = ItemDrawer()->ColumnData()->IconArray();

    if (!icons || icons->Count() == 0) // no icons set yet
        {
        return;
        }

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

        TBool textValid(ETrue);
        for (TInt subCell=0; subCell<6; subCell++)
            {
            iconSize = ItemDrawer()->ColumnData()->GetSubCellIconSize(subCell);

            // only those subcells that have icons, have also icon size set
            if (iconSize.iWidth == 0 || iconSize.iHeight == 0)
                {
                continue; // no need to set icon size
                }
            TextUtils::ColumnText(iconText, subCell, &txt); // get icon index(text)
            /*
            * it is possible, that we get something like  24037K/24M
            * as iconText. iconLex will happily then return 24037 as value
            * and code crashes when trying to access icon 24037 in
            * icon array
            */

            textValid = ETrue;
            for ( TInt i = 0; i < iconText.Length(); i++ )
                {
                TChar c(iconText[i]);
                if (! c.IsDigit())
                    {
                    textValid = EFalse;
                    break;
                    }
                }
            if ( !textValid )
                {
                continue;
                }

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
                    if ( iconIndex <0 || iconIndex > icons->Count() -1 )
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
                    //AknIconUtils::SetSize( bitmap,
                    //                       iconSize,
                    //                       EAspectRatioPreservedAndUnusedSpaceRemoved );
                //}
            } // end subCell for
        } // end row for
    }

EXPORT_C void CEikColumnListBox::FocusChanged( TDrawNow aDrawNow )
    {
    _AKNTRACE( "[%s][%s][%d].", "CEikColumnListBox", __FUNCTION__, __LINE__ );
    CEikTextListBox::FocusChanged( aDrawNow );

    // Data needs focus change information to control animations.
    if( IsFocused() )
        {
        ItemDrawer()->ColumnData()->FocusGained();
        }
    else
        {
        ItemDrawer()->ColumnData()->FocusLost();
        }
    }

#ifdef RD_LIST_STRETCH
EXPORT_C void CEikColumnListBox::EnableStretching( const TBool aEnabled )
    {
    if ( ItemDrawer()->ColumnData()->StretchingEnabled() != aEnabled )
        {
        ItemDrawer()->ColumnData()->EnableStretching( aEnabled );
        SizeChanged();
        }
    }
#else
EXPORT_C void CEikColumnListBox::EnableStretching( const TBool /*aEnabled*/ )
    {
    }
#endif // RD_LIST_STRETCH

//
//    Class CColumnListBoxItemDrawer
//

EXPORT_C CColumnListBoxItemDrawer::CColumnListBoxItemDrawer() {}
EXPORT_C CColumnListBoxItemDrawer::CColumnListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel,
                                                            const CFont* aFont,
                                                            CColumnListBoxData* aColumnData)
    : CTextListItemDrawer(aTextListBoxModel, aFont)
    {
    __DECLARE_NAME(_S("CColumnListBoxItemDrawer"));
    SetData(aColumnData);
    }

EXPORT_C CColumnListBoxItemDrawer::~CColumnListBoxItemDrawer()
    {
    delete iPropertyArray;
    }

EXPORT_C TSize CColumnListBoxItemDrawer::MinimumCellSize() const
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxData* data=ColumnData();
    const TInt columns=data->LastColumn();
    if (columns==-1)
        {
        _AKNTRACE( "[%s][%s][%d] return.", "CColumnListBoxItemDrawer", __FUNCTION__, __LINE__ );
        return CTextListItemDrawer::MinimumCellSize();
        }
    TInt width=0;
    TInt height=0;
    TBool graphicsColumn=EFalse;
    for (TInt ii=0;ii<=columns;ii++)
        {
        width+=data->ColumnWidthPixel(ii);
        if (data->ColumnIsGraphics(ii))
            {
            graphicsColumn=ETrue;
            }
        else
            {
            const CFont* font=data->ColumnFont(ii);
            if(font)
                {
                height=Max(height,font->HeightInPixels());
                }
            else
                {
                height=Max(height, iFont->HeightInPixels());
                }
            }
        }
    if (graphicsColumn)
        {
        CArrayPtr<CGulIcon>* iconArray=data->IconArray();
        if (iconArray)
            {
            const TInt count=iconArray->Count();
            for (TInt jj=0;jj<count;jj++)
                height=Max(height,(*iconArray)[jj]->Bitmap()->SizeInPixels().iHeight);
            }
        }
    height = Max (iData->FontBoundValues().iHeightInPixels, height);
    height+=VerticalInterItemGap();
    _AKNTRACE_FUNC_EXIT;
    return TSize(width,height);
    }

EXPORT_C TInt CColumnListBoxItemDrawer::ItemWidthInPixels(TInt /*aItemIndex*/) const
    {
    CColumnListBoxData* data=ColumnData();
    const TInt columns=data->LastColumn();
    TInt itemWidth = 0;
    if (iDrawMark)
        {
        itemWidth += (iMarkColumnWidth + iMarkGutter);
        }
    for (TInt ii=0;ii<=columns;ii++)
        {
        if (!ColumnData()->ColumnIsOptional(ii))
            {
            itemWidth+=data->ColumnWidthPixel(ii);
            }
        }
    _AKNTRACE( "[%s][%s] itemWidth = %d", "CColumnListBoxItemDrawer", __FUNCTION__, itemWidth );
    return itemWidth;
    }

EXPORT_C void CColumnListBoxItemDrawer::SetItemCellSize(
    const TSize& aSizeInPixels)
    {
    _AKNTRACE( "[%s][%s] aSizeInPixels(w = %d, h = %d).", "CColumnListBoxItemDrawer", \
            __FUNCTION__, aSizeInPixels.iWidth, aSizeInPixels.iHeight );
    CTextListItemDrawer::SetItemCellSize( aSizeInPixels );

    // Data needs the cell size to create/reconfigure highlight animations
    CColumnListBoxData* data = ColumnData();
    data->SetItemCellSize( iItemCellSize );
    }

void CColumnListBoxItemDrawer::DrawCurrentItemRect(const TRect& aRect) const
//
//    Draw the item background
//
    {
    iGc->SetClippingRect(iViewRect);
    iGc->SetBrushStyle(CGraphicsContext::ENullBrush);
    iGc->SetPenColor(iHighlightedBackColor);    // KDefaultLbxHighlightRectColor
    iGc->DrawRect(aRect);
    iGc->CancelClippingRect();
    }

/**
* Returns a pointer to the column data. Does not imply transfer of ownership.
*
* @since ER5U
*/
EXPORT_C CColumnListBoxData* CColumnListBoxItemDrawer::ColumnData() const
    {
    return STATIC_CAST(CColumnListBoxData*,iData);
    }

EXPORT_C void CColumnListBoxItemDrawer::DrawItemMark(TBool /*aItemIsSelected*/, TBool /*aViewIsDimmed*/, const TPoint& /*aMarkPos*/) const
    {
    // not used in S60
    }

EXPORT_C
void CColumnListBoxItemDrawer::DrawItemText( TInt aItemIndex,
                                             const TRect& aItemTextRect,
                                             TBool aItemIsCurrent,
                                             TBool /*aViewIsEmphasized*/,
                                             TBool aItemIsSelected ) const
//
//    Draw the items text
//
    {

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    iGc->SetPenColor(iTextColor);
    iGc->SetBrushColor(iBackColor);
    TPtrC temp=iModel->ItemText(aItemIndex);
    SetupGc(aItemIndex);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

    TBufC<256> target(KNullDesC);
    // SERIES60 ITEM MARKS! SAPLAF (the same code is in eikfrlb.cpp and eikclb.cpp)
    TPtrC repl;
    TInt pos = -1;

    TBool removeicon = (!aItemIsSelected && !ItemMarkReverse()) || (aItemIsSelected && ItemMarkReverse());
    if ( Flags() & EDrawMarkSelection && ItemMarkPosition() != -1 && removeicon)
        {
        repl.Set( ItemMarkReplacement() );
        pos = ItemMarkPosition();
        }

    // Try to allocate buffer dynamically. If out of memory, use the fixed size stack buffer.
    // (+1 is for the last column separator)
    TInt size = temp.Length() + repl.Length() + 1;
    if ( pos >= 0 )
        {
        size += pos; // space for other column separators
        }

    HBufC* buffer = NULL;
    if ( size > 256 )
        {
        buffer = HBufC::New( size );
        }

    TPtr des = ( buffer ? buffer->Des() : target.Des() );
    // Note that ReplaceColumn does not update correct length in variable 'des',
    // because it is not a reference parameter :(
    AknLAFUtils::ReplaceColumn(des, &temp, &repl, '\t', pos);
    des.Set( buffer ? buffer->Des() : target.Des() );

    // END OF ITEM MARKS! SAPLAF

    CColumnListBoxData::TColors colors;
    colors.iText=iTextColor;
    colors.iBack=iBackColor;
    colors.iHighlightedText=iHighlightedTextColor;
    colors.iHighlightedBack=iHighlightedBackColor;

    if (ColumnData()->CurrentMarqueeItemIndex() != aItemIndex && aItemIsCurrent)
        {
        ColumnData()->ResetMarquee();
        ColumnData()->SetCurrentMarqueeItemIndex(aItemIndex);
        }
    ColumnData()->SetCurrentItemIndex(aItemIndex);
    ColumnData()->Draw(Properties(aItemIndex), *iGc,&des,aItemTextRect,(aItemIsCurrent /*|| aViewIsEmphasized*/),colors);

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListNotSpecified );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    iGc->DiscardFont();
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    // end of SERIES60 LAF code.

    delete buffer;
    }

EXPORT_C TAny* CColumnListBoxItemDrawer::Reserved_1()
    {
    return NULL;
    }

//
// Class CEikColumnListBoxEditor
//

EXPORT_C CEikColumnListBoxEditor::CEikColumnListBoxEditor(MListBoxModel* aModel)
    : CEikListBoxTextEditor( aModel )
    {
    AKNTASHOOK_ADD( this, "CEikColumnListBoxEditor" );
    }

EXPORT_C CEikColumnListBoxEditor::~CEikColumnListBoxEditor()
    {
    AKNTASHOOK_REMOVE();
    }

EXPORT_C void CEikColumnListBoxEditor::ConstructL(TInt aColumn)
    {
    iColumnIndex = aColumn;
    }

EXPORT_C TPtrC CEikColumnListBoxEditor::ItemText()
    {
    TPtrC desColumn = static_cast<MTextListBoxModel*>(ListBoxModel())->ItemText(ItemIndex());
    TPtrC des;
    TextUtils::ColumnText(des, iColumnIndex, &desColumn);
    return des;
    }

EXPORT_C TBool CEikColumnListBoxEditor::UpdateModelL()
    {
    _AKNTRACE( "[%s][%s][%d].", "CEikColumnListBoxEditor", __FUNCTION__, __LINE__ );

    if (!Editor())
        {
        return EFalse; // quit if editing is not currently on
        }
    const MDesCArray* matchableTextArray = STATIC_CAST(CTextListBoxModel*,ListBoxModel())->MatchableTextArray();
    CDesCArray* textArray = (CDesCArray*)matchableTextArray; // !!! why bother with this cast
    TPtrC oldItem=textArray->MdcaPoint(ItemIndex());
    TBuf<128> newItem; // !!! magic number
    TPtrC column;
    HBufC* newText = Editor()->GetTextInHBufL();
    if (!newText)
        {
        return ETrue;     // if user tries to insert an empty text...
        }
    CleanupStack::PushL(newText);
    TInt i=0;
    while ( !TextUtils::ColumnText( column, i, &oldItem ) )
        {
        if ( i!=iColumnIndex )
            {
            newItem.Append( column );
            }
        else
            {
            newItem.Append( *newText );
            }

        newItem.Append( TChar( KColumnListSeparator ) );
        i++;
        }
    textArray->InsertL(ItemIndex(), newItem);
    textArray->Delete(ItemIndex()+1);
    CleanupStack::PopAndDestroy(); // newText
    return ETrue;
    }

EXPORT_C TInt CEikColumnListBoxEditor::Column() const
    {
    return iColumnIndex;
    }

EXPORT_C void CEikColumnListBoxEditor::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    CEikListBoxTextEditor::HandlePointerEventL(aPointerEvent);
    }

EXPORT_C void* CEikColumnListBoxEditor::ExtensionInterface( TUid /*aInterface*/ )
    {
    return NULL;
    }

#define ITEM_EXISTS_BEGIN TInt no_of_items__ = iModel->NumberOfItems()
#define ITEM_EXISTS(x) (((x) > -1) && ((x) < no_of_items__))

#define ITEM_EXISTS_ONCE(x) (((x) > -1) && ((x) < iModel->NumberOfItems()))

EXPORT_C void
CColumnListBoxView::Draw( const TRect* aRect ) const
    {

    if (RedrawDisabled() || !IsVisible())
        {
        return;
        }

    TInt i=0;

    CColumnListBoxItemDrawer* lbi = (CColumnListBoxItemDrawer*)ItemDrawer();
    CEikListBox* listbox = static_cast<CEikListBox*>( lbi->ColumnData()->Control() );
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( listbox );

    if ( !cc )
        {
        cc = lbi->ColumnData()->SkinBackgroundContext();
        }

    // draw the whole background at once, this is faster than drawing it in separate items
    if ( listbox && listbox->BackgroundDrawingSuppressed() )
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
                }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        AknsDrawUtils::Background( skin, cc, listbox, *iGc, *aRect );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
    else if ( !listbox )
        {
        iGc->Clear();
        }

    TInt firstPotentialItemIndex = iTopItemIndex;
    TInt lastPotentialItemIndex = iTopItemIndex + NumberOfItemsThatFitInRect(iViewRect) - 1;

    if (iModel->NumberOfItems() == 0)
        {
        // Empty
        }
    else
        {
        if ( lastPotentialItemIndex > iBottomItemIndex )
            {
            // Fix for EAAA-797CKC
            lastPotentialItemIndex = iBottomItemIndex;
            }
        ITEM_EXISTS_BEGIN;
        for (i = firstPotentialItemIndex; i <= lastPotentialItemIndex; i++)
            {
            if (ITEM_EXISTS(i))
                {
                DrawItem(i);
                }
            else
                {
                break;
                }
            }
        }

    if ( listbox && !listbox->BackgroundDrawingSuppressed() )
        {
        // clear the unused portion of the viewing area (this handles drawing the vertical line too :)
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( iGc );

        if ( transApi )
            {
            transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST

        TRect usedPortionOfViewRect( iViewRect.iTl + TSize( 0, iVerticalOffset ), TSize( iViewRect.Width(), ( i - iTopItemIndex ) * iItemHeight ) );

        // also clear area behind scroll bar.
        // this is a terrible hack, which is unfortunately needed since layouts
        // leave 2 pixel (in double res) wide margins to both sides of the
        // scroll bar, and there is no other way to do this. This hack is
        // only really valid for main pane lists, but it does not seem to
        // break popup lists, popup field lists or setting page radiobutton
        // lists.
        TRect sbbg( iViewRect );   // whole area behind scroll bar
        TRect margin( iViewRect ); // it gets even worse in mirrored layouts

        if ( AknLayoutUtils::LayoutMirrored() )
            {
            sbbg.iBr.iX = iViewRect.iBr.iX - lbi->LafItemSize().iWidth;

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
            sbbg.iTl.iX = iViewRect.iTl.iX + lbi->LafItemSize().iWidth;
            }

        // Unused portion will be cleared only if listbox background is drawn.
        if ( listbox )
            {
            AknsDrawUtils::BackgroundBetweenRects( skin,
                                                   cc,
                                                   listbox,
                                                   *iGc,
                                                   iViewRect,
                                                   usedPortionOfViewRect );

            AknsDrawUtils::Background( skin, cc, listbox, *iGc, sbbg );

            if ( AknLayoutUtils::LayoutMirrored() )
                {
                AknsDrawUtils::Background( skin, cc, listbox, *iGc, margin );
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

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->StopDrawing();
            }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
        }
    }

EXPORT_C void CColumnListBoxView::CalcBottomItemIndex()
    {
    CListBoxView::CalcBottomItemIndex();
    }


EXPORT_C TAny* CColumnListBoxView::Reserved_1()
    {
    return NULL;
    }

EXPORT_C void CColumnListBoxItemDrawer::ClearAllPropertiesL()
    {
    delete iPropertyArray;
    iPropertyArray = NULL;
    iPropertyArray = new (ELeave) CArrayFixFlat<SListProperties>(2);
    }

EXPORT_C void CColumnListBoxItemDrawer::SetPropertiesL(TInt aItemIndex, TListItemProperties aProperty)
    {
    _AKNTRACE( "[%s][%s][%d].", "CColumnListBoxItemDrawer", __FUNCTION__, __LINE__ );
    if (!iPropertyArray) ClearAllPropertiesL();
    TInt index;
    TKeyArrayFix key(0,ECmpTInt);
    SListProperties prop;
    prop.iItem = aItemIndex;

    if (iPropertyArray->FindIsq(prop, key, index))
        {
        iPropertyArray->InsertIsqL(prop, key);
        iPropertyArray->FindIsq(prop, key, index);
        }
    iPropertyArray->At(index).iProperties = aProperty;
    }

EXPORT_C
TListItemProperties CColumnListBoxItemDrawer::Properties(TInt aItemIndex) const
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
    if (iPropertyArray->FindIsq(prop, key, index)) return CTextListItemDrawer::Properties(aItemIndex);
    return iPropertyArray->At(index).iProperties;
    }

EXPORT_C void CColumnListBoxItemDrawer::CColumnListBoxItemDrawer_Reserved()
    {
    }

// End of File
