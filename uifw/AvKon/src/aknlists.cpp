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
* Description:  Avkon list layouts
*
*/


/*
 * AKNLISTS.CPP
 * 
 * This file has avkon listboxes
 */

#include <aknenv.h>
#include <aknlists.h>
#include <aknjavalists.h>
#include <eiklbv.h>
#include <eikclbd.h>
#include <AknPanic.h>
#include <barsread.h>
#include <AknAppGrid.h>
#include <aknsfld.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <layoutmetadata.cdl.h>
#include <skinlayout.cdl.h>

#include <AknTasHook.h>
#include "AknDebug.h"


#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST

#include <akntransitionutils.h>
#include "akntrace.h"

// non colorskinned additional icons
_LIT(KFirstIconReplacement, "0");

// for colorskinning additional icons
_LIT(KFirstCSIconReplacement, "-1");
_LIT(KFirstMovingCSIconReplacement, "-1\t%s");

#ifdef RD_LIST_STRETCH
_LIT(KEmptySpace, " ");
#endif // RD_LIST_STRETCH

//
// Drawing utilities
//

#ifdef AVKON_RDEBUG_ERROR
#define __LAYOUT_DEBUG(var, cmd) \
    if (!(var)) { cmd; }
#else
#define __LAYOUT_DEBUG(var, cmd)
#endif

enum TAknPopupLayoutPanicCodes
    {
    EAknPopupLayoutUnknownResolution
    };

void Panic(TAknPopupLayoutPanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknPopupLayout");
    User::Panic(KPanicCat, aPanic);
    }
    
// -----------------------------------------------------------------------------
// If a parent to the supplied control has its Gc set, this function will find 
// it and return it.
// -----------------------------------------------------------------------------
//
LOCAL_C CWindowGc* ReplaceGcWithCustomGc( const CEikListBox* aListBox )
    {
    _AKNTRACE( "[%s][%d].", __FUNCTION__, __LINE__ );
    const CCoeControl* parent = aListBox;
    CWindowGc* customGc;
    while ( parent )
        {
        customGc = parent->GetGc();
        if ( customGc )
            {
            CListItemDrawer* itemDrawer = aListBox->View()->ItemDrawer();
            CWindowGc* originalGc = itemDrawer->Gc();
            if ( customGc == originalGc )
                {
                return NULL;
                }
            else
                {
                itemDrawer->SetGc( customGc );
                return originalGc;
                }
            }
        parent = parent->Parent();
        }
    return NULL;
    }

// This is used by listboxes to handle item mark correctly. Can be used to other purposes too.

 // AVKON ITEM MARKS

_LIT(KReplacementString, "%S");

EXPORT_C void AknLAFUtils::ReplaceColumn(
    TPtr aTarget, TDesC* aSource, TDesC* aReplacement, TChar aColumnSeparator, TInt aColumn)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknLAFUtils", __FUNCTION__, __LINE__ );
    TBool bufferIsLargeEnough = EFalse;

    // Is the given buffer large enough to hold all column texts without truncation?
    // (+1 is for the last column separator)
    if ( aSource && aReplacement )
        {
        TInt maxSize = aSource->Length() + aReplacement->Length() + 1;
        if ( aColumn >= 0 )
            {
            maxSize += aColumn; // column separators
            }

        bufferIsLargeEnough = ( aTarget.MaxLength() >= maxSize );
        }

    TInt end=0;
    TInt column=0;
    TPtrC text;
    if (aSource)
        {
        text.Set(*aSource);
        }
    while (text.Length() || column<=aColumn) 
        {
        end = text.Locate(aColumnSeparator);
        if (end == KErrNotFound)
            {
            end = text.Length();
            }

        if (column == aColumn) 
            {
            if ( aReplacement ) 
                {
                TInt replace = aReplacement->FindF(KReplacementString);
                if (replace != KErrNotFound)
                    {
                    aTarget.Append(aReplacement->Left(replace));
                    aTarget.Append(text.Left(end));
                    aTarget.Append(aReplacement->Mid(replace+2)); // 2 == length of %s
                    }
                else
                    {
                    aTarget.Append(*aReplacement);
                    }

                if (end!=text.Length()) 
                    {
                    aTarget.Append(aColumnSeparator);
                    }
                }
            } 
        else 
            {
            if (bufferIsLargeEnough || end<KMaxColumnDataLength)
                {
                aTarget.Append(text.Left(end));
                }
            else
                {
                aTarget.Append(text.Left(KMaxColumnDataLength));
                }
            aTarget.Append(aColumnSeparator);
            }
        
        if (end<text.Length())
            {
            ++end;
            }
        text.Set(text.Mid(end));
        ++column;
        }
    }
 // END OF AVKON LAF


/** DEPRECATED
 *
 * Spec argument expects two things: ItemType typedef and ReadResource(TResourceReader&, ItemType&) method
 */
template<class Spec>
class CArrayReader : public CBase
    {
public:
    ~CArrayReader()
    { delete iArray; }
    void ConstructFromResourceL(TResourceReader &aResource);
    CArrayFix<typename Spec::ItemType> *iArray; // Public
    };

template<class Spec>
void CArrayReader<Spec>::ConstructFromResourceL(TResourceReader &aResource)
    {
#ifdef __WINS__
    iArray = new(ELeave) CArrayFixFlat<Spec::ItemType>(4);
#else
    iArray = new(ELeave) CArrayFixFlat<typename Spec::ItemType>(4);
#endif
    const TInt count = aResource.ReadInt16();
    for (TInt ii=0; ii<count; ++ii)
        {
        typename Spec::ItemType value;
        Spec::ReadResource(aResource, value);
        iArray->AppendL(value);
        }
    }


// Not for apps
struct SAknLayoutGfx
    {
    TInt id;    
    TInt C;
    TInt l, t, r, b, W, H;
    // the next ones are used by array resource reader template
    typedef SAknLayoutGfx ItemType;
    static void ReadResource(TResourceReader& aReader, ItemType& aTarget);    
    // Accessors for drawing code
    TInt Id() const;
    TInt Color() const;
    TRect Rect(const TRect &aParent) const;
    };
// Not for apps
struct SAknLayoutText 
    {
    TInt id; // must be first
    const CFont* font; 
    TInt C;
    TInt lm, rm, B, W;
    CGraphicsContext::TTextAlign align;

    typedef SAknLayoutText ItemType;
    static void ReadResource(TResourceReader& aReader, ItemType& aTarget);
    };
// Not for apps
struct SAknLayoutCmd
    {
    TInt id; // must be first
    TInt cmd;
    TInt data;
    
    typedef SAknLayoutCmd ItemType;
    static void ReadResource(TResourceReader& aReader, ItemType& aTarget);
    };

//
// Layout resource readers
//
void SAknLayoutPos::ReadResource(TResourceReader& aReader, ItemType& aTarget)
    {
    aTarget.l = aReader.ReadInt16();
    aTarget.t = aReader.ReadInt16();
    aTarget.r = aReader.ReadInt16();
    aTarget.b = aReader.ReadInt16();
    aTarget.W = aReader.ReadInt16();
    aTarget.H = aReader.ReadInt16();
    }

void SAknLayoutGfx::ReadResource(TResourceReader& aReader, ItemType& aTarget)
    {
    aTarget.id = aReader.ReadInt16();
    aTarget.C = aReader.ReadInt16();
    aTarget.l = aReader.ReadInt16();
    aTarget.t = aReader.ReadInt16();
    aTarget.r = aReader.ReadInt16();
    aTarget.b = aReader.ReadInt16();
    aTarget.W = aReader.ReadInt16();
    aTarget.H = aReader.ReadInt16();
    }

TInt SAknLayoutGfx::Id() const { return id; }

TInt SAknLayoutGfx::Color() const { return C; }

TRect SAknLayoutGfx::Rect(const TRect &aParent) const
    {
    return AknLayoutUtils::RectFromCoords(aParent,l, t, r, b, W, H);
    }
 
void SAknLayoutText::ReadResource(TResourceReader& aReader, ItemType& aTarget)
    {
    aTarget.id = aReader.ReadInt16();
    TInt fontid = aReader.ReadInt16();
    aTarget.font = AknLayoutUtils::FontFromId(fontid);

    aTarget.C = aReader.ReadInt16();
    aTarget.lm = aReader.ReadInt16();
    aTarget.rm = aReader.ReadInt16();
    aTarget.B = aReader.ReadInt16();
    aTarget.W = aReader.ReadInt16();
    TInt alignid = aReader.ReadInt16();
    aTarget.align = AknLayoutUtils::TextAlignFromId(alignid);
    }
void SAknLayoutCmd::ReadResource(TResourceReader& aReader, ItemType& aTarget)
    {
    aTarget.id = aReader.ReadInt16();
    aTarget.cmd = aReader.ReadInt16();
    aTarget.data = aReader.ReadInt16();
    }


//
// Resource reader for columnlistbox layouts
//

EXPORT_C void CAknGenericReader::ConstructL(TInt aResourceId)
    {
    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC(reader, aResourceId);
    ConstructFromResourceL(reader);
    CleanupStack::PopAndDestroy(); // reader
    }

EXPORT_C void CAknGenericReader::ConstructFromResourceL(TResourceReader &reader)
    {
    iGfx = new(ELeave) CArrayReader<SAknLayoutGfx>;
    iGfx->ConstructFromResourceL(reader);

    iText = new(ELeave) CArrayReader<SAknLayoutText>;
    iText->ConstructFromResourceL(reader);

    iCmd = new(ELeave) CArrayReader<SAknLayoutCmd>;
    iCmd->ConstructFromResourceL(reader);
    
    iArea = new(ELeave) CArrayReader<SAknLayoutGfx>;
    iArea->ConstructFromResourceL(reader);
    }

EXPORT_C CAknGenericReader::~CAknGenericReader()
    {
    delete iGfx;
    delete iText;
    delete iCmd;
    delete iArea;
    }

    
EXPORT_C const SAknLayoutGfx* CAknGenericReader::GfxItem(TInt aIndex) const
    {
    TInt index=KErrNotFound;
    TKeyArrayFix key(0,ECmpTInt);
    SAknLayoutGfx gfx;
    gfx.id = aIndex;
    TInt zeroiffound = iGfx->iArray->Find(gfx, key, index);
    if (zeroiffound!=0) return 0;
    return &iGfx->iArray->At(index);
    }

EXPORT_C const SAknLayoutText* CAknGenericReader::TextItem(TInt aIndex) const
    {
    TInt index=KErrNotFound;
    TKeyArrayFix key(0,ECmpTInt);
    SAknLayoutText text;
    text.id = aIndex;
    TInt zeroiffound = iText->iArray->Find(text, key, index);
    if (zeroiffound!=0) return 0;
    return &iText->iArray->At(index);
    }

EXPORT_C const SAknLayoutCmd* CAknGenericReader::CmdItem(TInt aIndex) const
    {       
    TInt index=KErrNotFound;
    TKeyArrayFix key(0,ECmpTInt);
    SAknLayoutCmd cmd;
    cmd.id = aIndex;
    TBool zeroiffound = iCmd->iArray->Find(cmd, key, index);
    if (zeroiffound!=0) return 0;
    return &iCmd->iArray->At(index);
    }

EXPORT_C const SAknLayoutGfx* CAknGenericReader::AreaItem(TInt aIndex) const
    {
    TInt index=KErrNotFound;
    TKeyArrayFix key(0,ECmpTInt);
    SAknLayoutGfx area;
    area.id = aIndex;
    TBool zeroiffound = iArea->iArray->Find(area, key, index);
    if (zeroiffound!=0) return 0;
    return &iArea->iArray->At(index);
    }



//
// Implementation of this module is completely Avkon LAF Code!
//

TBool IsEmptyVal(TInt aValue)
    {
    return aValue == ELayoutEmpty || aValue == -1;
    }


#define ITEM_EXISTS(x) (((x) > -1) && ((x) < aListBox->Model()->NumberOfItems()))
static void HandleItemRemovalBodyL(CEikListBox *aListBox, TInt currentitem, TInt topitem)
    {
    TInt lastitem = aListBox->Model()->NumberOfItems()-1;
    if (lastitem < topitem) topitem = lastitem;


    TInt numItems = aListBox->View()->NumberOfItemsThatFitInRect(aListBox->View()->ViewRect());
    if (!ITEM_EXISTS(topitem + numItems -1)) topitem = lastitem - numItems +1;
    if (topitem < 0) topitem = 0;
    if (topitem!=-1) aListBox->SetTopItemIndex(topitem);

    if (currentitem != -1 && lastitem != -1) aListBox->SetCurrentItemIndexAndDraw(currentitem > lastitem ? lastitem : currentitem);
    if (topitem==-1 || lastitem == -1) aListBox->DrawDeferred();
    }

EXPORT_C void AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aCurrentItemIndex , TBool /* aCurrentRemoved */)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxUtils", __FUNCTION__, __LINE__ );
    // Handle the actual positioning of the list and highlight
    TInt currentitem = aCurrentItemIndex;

    TInt topitem = aListBox->TopItemIndex();
    aListBox->HandleItemRemovalL();
    HandleItemRemovalBodyL(aListBox, currentitem, topitem);
    }

EXPORT_C void AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(CEikListBox *aListBox, TInt aCurrentItemIndex, CArrayFix<TInt> &aIndexes)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxUtils", __FUNCTION__, __LINE__ );
    TInt currentitem = aCurrentItemIndex;
    TInt topitem = aListBox->TopItemIndex();
    aListBox->HandleItemRemovalL(aIndexes);
    HandleItemRemovalBodyL(aListBox, currentitem, topitem);
    }

EXPORT_C void AknListBoxLayouts::SetupStandardListBox(CEikListBox& aListBox)
    {
    aListBox.SetBorder(TGulBorder::ENone);
    }

// Added for Selection Grid
EXPORT_C void AknListBoxLayouts::SetupStandardGrid(CAknGrid& aGrid)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    aGrid.SetBorder(TGulBorder::ENone);
    // This method is used by e.g. GMS grid and color selection grid. Text color
    // taken from color selection grid.
    TInt textColor = AKN_LAYOUT_TEXT_Cell_pane_texts__pop_up_large_graphic_colour_none__Line_1.iC;
    aGrid.ItemDrawer()->SetTextColor(AKN_LAF_COLOR_STATIC(textColor));
    aGrid.ItemDrawer()->SetBackColor(AKN_LAF_COLOR_STATIC(0));

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    /*
    * do not set highlight color here, since grid type is
    * unknown here and every grid which wants to set
    * it's highlightcolor  will do that in it's
    * SizeChanged() method
    *
    * so try to get an extended skin color and if that fails
    * use old code
    */
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG10 );
    if (error)
        {
        color = AKN_LAF_COLOR( textColor );
        aGrid.ItemDrawer()->SetHighlightedTextColor(color);
        }


    aGrid.ItemDrawer()->SetHighlightedBackColor(AKN_LAF_COLOR_STATIC(0));
    aGrid.ItemDrawer()->FormattedCellData()->SetSkinParentPos(aGrid.ItemDrawer()->FormattedCellData()->Control()->PositionRelativeToScreen());
    AknsUtils::RegisterControlPosition(aGrid.ItemDrawer()->FormattedCellData()->Control());
    }

void AknListBoxLayouts::SetupGridPos(CAknGrid& aGrid,
                                     const TAknWindowLineLayout &aLayout)
    {
    SetupGridPos(aGrid,aLayout.il, aLayout.it, aLayout.ir, aLayout.ib, aLayout.iW, aLayout.iH);
    }

EXPORT_C void AknListBoxLayouts::SetupGridPos(CAknGrid& aGrid,
                TInt l, TInt t, TInt r, TInt b, TInt W, TInt H) 
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    TSize sz( aGrid.Rect().Size() );
    TInt gridHeight = aGrid.Rect().Height();

    if (IsParentRelative(W)) { W = sz.iWidth - ELayoutP + W; }
    if (IsParentRelative(H)) { H = sz.iHeight - ELayoutP + H; }
    if (IsParentRelative(l)) { l = sz.iWidth - ELayoutP + l; }
    if (IsParentRelative(t)) { t = sz.iHeight - ELayoutP + t; }
    if (IsParentRelative(r)) { r = sz.iWidth - ELayoutP + r; }
    if (IsParentRelative(b)) { b = sz.iHeight - ELayoutP + b; }

    if (IsEmptyVal(W)) W = sz.iWidth - r - l;
    if (IsEmptyVal(H)) H = gridHeight - t - b;
    if (IsEmptyVal(l)) l = sz.iWidth - W - r;
    if (IsEmptyVal(t)) t = gridHeight - H - b;
    if (IsEmptyVal(r)) r = sz.iWidth - l - W;
    if (IsEmptyVal(b)) b = gridHeight - t - H;


    aGrid.SetColumnWidth(W);
    TRAP_IGNORE(aGrid.SetItemHeightL(H));
    aGrid.SetHorizontalMargin(l);
    aGrid.SetVerticalMargin(t);

    __LAYOUT_DEBUG(aGrid.ItemHeight() == H, RDebug::Print(_L("EEikPanicListboxSizeIsNotAccordingToLAFSpec")));
    __LAYOUT_DEBUG(aGrid.ColumnWidth() == W, RDebug::Print(_L("EEikPanicListboxSizeIsNotAccordingToLAFSpec")));

    __LAYOUT_DEBUG(aGrid.MinimumSize().iHeight % H == 0, RDebug::Print(_L("AknListBoxLayouts/GridPos: ERROR: Layout not according to LAF spec: %d/%d"),aGrid.MinimumSize().iHeight,H));
    __LAYOUT_DEBUG(aGrid.MinimumSize().iWidth % W == 0, RDebug::Print(_L("AknListBoxLayouts/GridPos: ERROR: aGrid.MinimumSize().iWidth[%d] != width[%d]. Please fix grid MinimumSize()"),aGrid.MinimumSize().iWidth,W));
    __LAYOUT_DEBUG(aGrid.View()->ViewRect().Size().iWidth % W == 0, RDebug::Print(_L("AknListBoxLayouts/GridPos: ERROR: aListBox.View()->ViewRect().Size().iWidth[%d] != width[%d]. Please fix grid Rect()"),aGrid.MinimumSize().iWidth,W));

    __LAYOUT_DEBUG(aGrid.View()->ViewRect().Size().iHeight % H == 0, RDebug::Print(_L("AknListBoxLayouts/GridPos: ERROR: ViewRect height not according to LAF spec: %d/%d"), aGrid.View()->ViewRect().Size().iHeight,H));
    __LAYOUT_DEBUG(aGrid.View()->ViewRect().iTl.iY - t == aGrid.Rect().iTl.iY, RDebug::Print(_L("AknListBoxLayouts/GridPos: ERROR: ViewRect position not according to LAF spec %d/%d"),aGrid.View()->ViewRect().iTl.iY - t,aGrid.Rect().iTl.iY));

    }

EXPORT_C void AknListBoxLayouts::SetupListboxPos(CEikListBox& aListBox, 
                   const TAknWindowLineLayout &aLayout)
{
    TRAP_IGNORE( SetupListboxPosL( aListBox, aLayout ) );
}

EXPORT_C void AknListBoxLayouts::SetupListboxPos(CEikListBox& aListBox,
                  TInt aStartX, TInt aStartY, TInt aEndX,TInt aEndY, TInt aWidth, TInt aHeight)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    // construct layout data from the given values
    TAknWindowLineLayout layout;
    layout.iC = ELayoutEmpty;
    layout.il = aStartX;
    layout.it = aStartY;
    layout.ir = aEndX;
    layout.ib = aEndY;
    layout.iW = aWidth;
    layout.iH = aHeight;

    TRAP_IGNORE( SetupListboxPosL( aListBox, layout ) );
    }

void AknListBoxLayouts::SetupListboxPosL( CEikListBox& aListBox,
                                          const TAknWindowLineLayout& aLayout ) // layout of first item
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );;
    // this is quite akward in order to adapt into "legacy" code
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( TRect( aListBox.Size() ), aLayout );
    
    TRect rect( layoutRect.Rect() );
    
    aListBox.SetHorizontalMargin( rect.iTl.iX );
    aListBox.SetVerticalMargin( rect.iTl.iY );
    aListBox.SetItemHeightL( rect.Height() );
    aListBox.View()->ItemDrawer()->SetItemCellSize( rect.Size() );
    }


EXPORT_C void AknListBoxLayouts::SetupStandardColumnListbox(CColumnListBoxItemDrawer* aItemDrawer)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    __ASSERT_ALWAYS(aItemDrawer, Panic(EAknPanicInvalidValue));
    // Text color taken from single item listbox.
    TInt textColor = AKN_LAYOUT_TEXT_List_pane_texts__single__Line_1(0,0).iC;
    aItemDrawer->SetTextColor(AKN_LAF_COLOR_STATIC(textColor));
    aItemDrawer->SetBackColor(AKN_LAF_COLOR_STATIC(0));
    
    TRgb color = AKN_LAF_COLOR_STATIC( textColor );
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, 
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG10 );

    aItemDrawer->SetHighlightedTextColor(color);
    aItemDrawer->SetHighlightedBackColor(AKN_LAF_COLOR_STATIC(
        AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_2(TRect()).iC));
    }


EXPORT_C void AknListBoxLayouts::SetupStandardFormListbox(CFormattedCellListBoxItemDrawer* aItemDrawer)
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    __ASSERT_ALWAYS(aItemDrawer, Panic(EAknPanicInvalidValue));
    // Text color taken from double item listbox.
    TInt textColor = AKN_LAYOUT_TEXT_List_pane_texts__double__Line_1(0).iC;
    aItemDrawer->SetTextColor(AKN_LAF_COLOR_STATIC(textColor));
    aItemDrawer->SetBackColor(AKN_LAF_COLOR_STATIC(0));
    
    TRgb color = AKN_LAF_COLOR_STATIC( textColor );
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(), color, 
                    KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG10 );

    aItemDrawer->SetHighlightedTextColor(color);
    aItemDrawer->SetHighlightedBackColor(AKN_LAF_COLOR_STATIC(
        AKN_LAYOUT_WINDOW_List_pane_highlight_graphics__various__Line_2(TRect(0,0,0,0)).iC));
    }
    
TInt AknListBoxLayouts::AdjustPopupLayoutData( const TRect& aScreenRect )
    {
    _AKNTRACE( "[%s][%s][%d].", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    TInt width = aScreenRect.Width();
    TInt height = aScreenRect.Height();
    
    if (  width ==640 &&  height ==360 ) //QHD
        {
        return 32;
        }
    else if(( width ==320 && height ==240 ) //QVGA, QVGA2
            ||( width ==640 && height ==480 )) //VGA, VAG3
        {
        return 0;
        }
    else
        {
        Panic( EAknPopupLayoutUnknownResolution );
        return 0;
        }
    }
// -----------------------------------------------------------------------------
// IdFromTextAlign
// -----------------------------------------------------------------------------
//
static TInt IdFromTextAlign( const CGraphicsContext::TTextAlign aAlign )
    {
    TInt id;
    
    switch( aAlign ) 
        {
        case CGraphicsContext::ELeft:
            id = ELayoutAlignLeft;
            break;
            
        case CGraphicsContext::ECenter:
            id = ELayoutAlignCenter;
            break;
            
        case CGraphicsContext::ERight:
            id = ELayoutAlignRight;
            break;
            
        default:
            id = ELayoutAlignLeft;
        }
    _AKNTRACE( "[%s] return id = %d", __FUNCTION__, id );
    return id;
    }

static const TAknsItemID *LinePositionToItemId(TAknSeparatorLinePosition pos)
    {
    const TAknsItemID * id = &KAknsIIDNone;
    switch(pos)
        {
        case EAColumn: 
            id = &KAknsIIDQsnBgColumn0; 
            break;
        case EABColumn: id = &KAknsIIDQsnBgColumnA; break;
        case EBCColumn: 
        case EBCColumnStretched:
            id = &KAknsIIDQsnBgColumnAB;  break;
        case ENoLine: id = &KAknsIIDNone; break;
        default:
            ; 
            break;
        };
    _AKNTRACE( "[%s] return id = %d", __FUNCTION__, id );    
    return id;
    }

static const TAknsItemID *LinePositionToListEndId(TAknSeparatorLinePosition pos)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    const TAknsItemID *listEndId = &KAknsIIDNone;
    switch(pos)
        {
        case EAColumn: listEndId = &KAknsIIDQsnBgSliceList0;  break;
        case EABColumn: listEndId = &KAknsIIDQsnBgSliceListA;  break;
        case EBCColumn: 
        case EBCColumnStretched:
            listEndId = &KAknsIIDQsnBgSliceListAB;  break;
        case ENoLine: break;
        default: ; break;
        };
    return listEndId;
    }

static void SetSeparatorLinePosition(const CEikFormattedCellListBox *aListBox, TAknSeparatorLinePosition pos)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    aListBox->ItemDrawer()->FormattedCellData()->SetSeparatorLinePosition(pos);
    TAknWindowLineLayout tile(SkinLayout::Column_background_and_list_slice_skin_placing_Line_2());

    switch(pos)
        {
        case EAColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_1();
            break;
        case EABColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_2();
            break;
        case EBCColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_3();
            break;
        case ENoLine: break;
        default: ; break;
        };

    TAknWindowLineLayout listEnd(SkinLayout::Column_background_and_list_slice_skin_placing_Line_7());

    TAknLayoutRect tileLayout;
    tileLayout.LayoutRect(aListBox->Rect(), tile);
    aListBox->ItemDrawer()->FormattedCellData()->SetSkinStyle(LinePositionToItemId(pos), tileLayout.Rect());

    TAknLayoutRect listEndLayout;
    listEndLayout.LayoutRect(aListBox->Rect(), listEnd);
    aListBox->ItemDrawer()->FormattedCellData()->SetListEndSkinStyle(LinePositionToListEndId(pos), listEndLayout.Rect());

    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,aListBox->Model())->Filter();
    if (filter)
        {
        CAknSearchField *find = (CAknSearchField*)filter->FindBox();
        if (find)
            {
            find->SetLinePos(pos);
            }
        }

    }
    
static void SetSeparatorLinePosition(CEikColumnListBox *aListBox, TAknSeparatorLinePosition pos)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    aListBox->ItemDrawer()->ColumnData()->SetSeparatorLinePosition(pos);

    TAknWindowLineLayout tile(SkinLayout::Column_background_and_list_slice_skin_placing_Line_2());
    switch(pos)
        {
        case EAColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_1();
            break;
        case EABColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_2();
            break;
        case EBCColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_3();
            break;
        case EBCColumnStretched:
            {
            TAknWindowComponentLayout l1 = AknLayoutScalable_Avkon::bg_list_pane( 0 );
            TAknWindowComponentLayout l2 = 
                AknLayoutScalable_Avkon::bg_list_pane_g1( 4 );
            
            tile = TAknWindowComponentLayout::Compose( l1, l2 ).LayoutLine();
            }
            break;
        case ENoLine: break;
        default: ; break;
        };

    TAknWindowLineLayout listEnd(SkinLayout::Column_background_and_list_slice_skin_placing_Line_7());

    TAknLayoutRect tileLayout;
    tileLayout.LayoutRect(aListBox->Rect(), tile);
    aListBox->ItemDrawer()->ColumnData()->SetSkinStyle(LinePositionToItemId(pos), tileLayout.Rect());

    TAknLayoutRect listEndLayout;
    listEndLayout.LayoutRect(aListBox->Rect(), listEnd);
    aListBox->ItemDrawer()->ColumnData()->SetListEndSkinStyle(LinePositionToListEndId(pos), listEndLayout.Rect());


    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,aListBox->Model())->Filter();
    if (filter)
        {
        CAknSearchField *find = (CAknSearchField*)filter->FindBox();
        if (find)
            {
            find->SetLinePos(pos);
            }
        }

    }

static void SetSeparatorLinePosition(CAknGrid *aGrid, TAknSeparatorLinePosition pos)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    aGrid->ItemDrawer()->FormattedCellData()->SetSeparatorLinePosition(pos);
    TAknWindowLineLayout tile(SkinLayout::Column_background_and_list_slice_skin_placing_Line_2());
    switch(pos)
        {
        case EABColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_2();
            break;
        case EBCColumn:
            tile = SkinLayout::Column_background_and_list_slice_skin_placing_Line_3();
            break;
        case EAColumn:
        case ENoLine: break;
        default: ; break;
        };

    TAknLayoutRect tileLayout;
    tileLayout.LayoutRect(aGrid->Rect(), tile);
    aGrid->ItemDrawer()->FormattedCellData()->SetSkinStyle(&KAknsIIDNone, tileLayout.Rect());
    }

void CommonSetupScrollbarLayout( CAknListBoxFilterItems * /*aFilter*/, 
                                 CEikScrollBarFrame *aScrollBarFrame,
                                 TBool /*aExternalFindBox*/,
                                 const CEikListBox* aListBox )
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose( 
        AknLayoutScalable_Avkon::listscroll_gen_pane(0),
        AknLayoutScalable_Avkon::scroll_pane()); 
     
    TRect scrollBarParent( aListBox->Rect() );    
    AknLayoutUtils::LayoutVerticalScrollBar( aScrollBarFrame,
                                             scrollBarParent,
                                             layout.LayoutLine() );
    }

// for setting up scrollbar layout in square - used by predefined list layouts
static void SetupScrollbarLayout(const CEikFormattedCellListBox *aListBox, CEikScrollBarFrame *aScrollBarFrame)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,aListBox->Model())->Filter();
    CommonSetupScrollbarLayout(filter, aScrollBarFrame, EFalse, aListBox);
    }

static void SetupScrollbarLayout(const CEikColumnListBox *aListBox, CEikScrollBarFrame *aScrollBarFrame)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    CAknListBoxFilterItems *filter = STATIC_CAST(CAknFilteredTextListBoxModel*,aListBox->Model())->Filter();

    TBool findBox = static_cast<CAknColumnListBoxView*>(aListBox->View())
        ->GetFindEmptyListState();

    CommonSetupScrollbarLayout(filter, aScrollBarFrame, findBox, aListBox);
    }


TSize ListBoxItemSize(CEikListBox &aListBox, CColumnListBoxItemDrawer* aItemDrawer)
    {
    TSize size(aItemDrawer->LafItemSize().iWidth,aListBox.View()->ItemSize().iHeight);
    return size;
    }

TSize ListBoxItemSize(CEikListBox &aListBox, CFormattedCellListBoxItemDrawer *aItemDrawer)
    {
    TSize size( aItemDrawer->LafItemSize().iWidth, aListBox.View()->ItemSize().iHeight);
    return size;
    }

void SetupColumnGfxCellL(CEikListBox& aListBox, CColumnListBoxItemDrawer* aItemDrawer, TInt index,
                                  TInt l, TInt t, TInt r, TInt b, TInt W, TInt H, TInt startx, TInt endx)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TSize sz( ListBoxItemSize( aListBox, aItemDrawer ) );
    
    if ( IsParentRelative( W ) ) { W = sz.iWidth - ELayoutP + W; }
    if ( IsParentRelative( H ) ) { H = sz.iHeight - ELayoutP + H; }
    if ( IsParentRelative( r ) ) { r = sz.iWidth - ELayoutP + r; }
    if ( IsParentRelative( b ) ) { b = sz.iHeight - ELayoutP + b; }
    if ( IsParentRelative( l ) ) { l = sz.iWidth - ELayoutP + l; }
    if ( IsParentRelative( t ) ) { t = sz.iHeight - ELayoutP + t; }

    // position graphics by left/right and size
    TAknWindowLineLayout windowLine;

    if ( IsEmptyVal( l ) )
        {
        windowLine.ir = r;
        windowLine.il = ELayoutEmpty;
        }
    else
        {
        windowLine.il = l;
        windowLine.ir = ELayoutEmpty;
        }

    if ( IsEmptyVal( l ) ) { l = sz.iWidth - r - W; }
    if ( IsEmptyVal( W ) ) { W = sz.iWidth - r - l; }
    if ( IsEmptyVal( r ) ) { r = sz.iWidth - l - W; }
    if ( IsEmptyVal( t ) ) { t = sz.iHeight - b - H; }
    if ( IsEmptyVal( H ) ) { H = sz.iHeight - b - t; }
    if ( IsEmptyVal( b ) ) { b = sz.iHeight - t - H; }

    windowLine.it = t;
    windowLine.iW = W;
    windowLine.iH = H;

    aItemDrawer->ColumnData()->SetGraphicSubCellL( index, windowLine );
    aItemDrawer->ColumnData()->SetColumnAlignmentL( index, CGraphicsContext::ECenter );
    
    if ( endx < startx )
        {
        aItemDrawer->ColumnData()->SetOptionalColumnL( index, ETrue );
        }
        
    aItemDrawer->ColumnData()->SubCellsMightIntersect( ETrue );        
    }

EXPORT_C void AknListBoxLayouts::SetupColumnGfxCell(CEikListBox& aListBox, CColumnListBoxItemDrawer* aItemDrawer, TInt index,
                                  TInt l, TInt t, TInt r, TInt b, TInt W, TInt H, TInt startx, TInt endx)
    {
    TRAP_IGNORE(SetupColumnGfxCellL(aListBox, aItemDrawer, index, l, t, r, b, W, H, startx, endx));
    }

void SetupColumnTextCellL(CEikListBox& aListBox, CColumnListBoxItemDrawer* aItemDrawer, TInt index,
                const CFont *font, TInt C, TInt lm, TInt rm, TInt B, TInt W, CGraphicsContext::TTextAlign aAlign, TInt /*startx*/, TInt /*endx*/)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TSize size( ListBoxItemSize( aListBox, aItemDrawer ) );

    if ( IsParentRelative( lm ) ) { lm = size.iWidth - ELayoutP + lm; }
    if ( IsParentRelative( rm ) ) { rm = size.iWidth - ELayoutP + rm; }
    if ( IsParentRelative( W ) ) { W = size.iWidth - ELayoutP + W; }

    if ( IsEmptyVal( lm ) ) { lm = size.iWidth - rm - W; }
    if ( IsEmptyVal( rm ) ) { rm = size.iWidth - lm - W; }
    if ( IsEmptyVal( W ) ) { W = size.iWidth - lm - rm; }

    TAknTextLineLayout textLine;
    textLine.iC = C;                        // color
    textLine.il = lm;                       // left
    textLine.ir = rm;                       // right
    textLine.iB = B;                        // baseline
    textLine.iW = ELayoutEmpty;             // width
    textLine.iJ = IdFromTextAlign( aAlign );// justification
    textLine.iFont = EAknLogicalFontPrimaryFont;       // a default font id
    textLine.iBaselineSkip = 0;           
    textLine.iNumberOfLinesShown = 1;
    
    aItemDrawer->ColumnData()->SetTextSubCellL( index, textLine );
    aItemDrawer->ColumnData()->SetColumnFontL( index, font );
    aItemDrawer->ColumnData()->SubCellsMightIntersect( ETrue );        
    }     
    
EXPORT_C void AknListBoxLayouts::SetupColumnTextCell(CEikListBox& aListBox, CColumnListBoxItemDrawer* aItemDrawer, TInt index,
                const CFont *font, TInt C, TInt lm, TInt rm, TInt B, TInt W, CGraphicsContext::TTextAlign aAlign, TInt startx, TInt endx)
    {
    TRAP_IGNORE(SetupColumnTextCellL(aListBox, aItemDrawer, index, font, C,lm,rm,B,W,aAlign,startx,endx));
    }

void SetupFormGfxCellL(CEikListBox& aListBox, CFormattedCellListBoxItemDrawer* aItemDrawer, TInt index,
                                TInt l, TInt t, TInt r, TInt b, TInt W, TInt H, TPoint /*p1*/, TPoint /*p2*/)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TSize sz( ListBoxItemSize( aListBox, aItemDrawer ) );
    
    if ( IsParentRelative( W ) ) { W = sz.iWidth - ELayoutP + W; }
    if ( IsParentRelative( H ) ) { H = sz.iHeight - ELayoutP + H; }
    if ( IsParentRelative( r ) ) { r = sz.iWidth - ELayoutP + r; }
    if ( IsParentRelative( b ) ) { b = sz.iHeight - ELayoutP + b; }
    if ( IsParentRelative( l ) ) { l = sz.iWidth - ELayoutP + l; }
    if ( IsParentRelative( t ) ) { t = sz.iHeight - ELayoutP + t; }

    // position graphics by left/right and size
    TAknWindowLineLayout windowLine;

    if ( IsEmptyVal( l ) )
        {
        windowLine.ir = r;
        windowLine.il = ELayoutEmpty;
        }
    else
        {
        windowLine.il = l;
        windowLine.ir = ELayoutEmpty;
        }

    if ( IsEmptyVal( l ) ) { l = sz.iWidth - r - W; }
    if ( IsEmptyVal( W ) ) { W = sz.iWidth - r - l; }
    if ( IsEmptyVal( r ) ) { r = sz.iWidth - l - W; }
    if ( IsEmptyVal( t ) ) { t = sz.iHeight - b - H; }
    if ( IsEmptyVal( H ) ) { H = sz.iHeight - b - t; }
    if ( IsEmptyVal( b ) ) { b = sz.iHeight - t - H; }

    windowLine.it = t;
    windowLine.iW = W;
    windowLine.iH = H;

    aItemDrawer->FormattedCellData()->SetGraphicSubCellL( index, windowLine );
    aItemDrawer->FormattedCellData()->SubCellsMightIntersect( ETrue );
    }

EXPORT_C void AknListBoxLayouts::SetupFormGfxCell(CEikListBox& aListBox, CFormattedCellListBoxItemDrawer* aItemDrawer, TInt index,
                                TInt l, TInt t, TInt r, TInt b, TInt W, TInt H, TPoint p1, TPoint p2)
    {
    TRAP_IGNORE(SetupFormGfxCellL(aListBox, aItemDrawer, index, l,t,r,b,W,H,p1,p2));
    }


EXPORT_C void AknListBoxLayouts::SetupGridFormGfxCell(CAknGrid& aGrid, CFormattedCellListBoxItemDrawer* aItemDrawer, TInt aIndex,
                                TInt l, TInt t, TInt r, TInt b, TInt W, TInt H, TPoint aP1, TPoint aP2)
    {
    TRAP_IGNORE(SetupFormGfxCellL(aGrid, aItemDrawer, aIndex, l,t,r,b,W,H,aP1,aP2));
    }


EXPORT_C void AknListBoxLayouts::SetupGridFormGfxCell(CAknGrid& aGrid, CFormattedCellListBoxItemDrawer* aItemDrawer, TInt aIndex,
                                const TAknWindowLineLayout &aLine,
                                TPoint& aP1, TPoint& aP2)
    {
    TRAP_IGNORE(SetupFormGfxCellL(aGrid, aItemDrawer, aIndex, aLine.il, aLine.it, aLine.ir, aLine.ib, aLine.iW, aLine.iH,aP1,aP2));
    }

EXPORT_C void AknListBoxLayouts::SetupColumnTextCell(CEikListBox& aListBox, 
                                CColumnListBoxItemDrawer* aItemDrawer, 
                                TInt aIndex,
                                const TAknTextLineLayout &aLayout,
                                TInt startx, 
                                TInt endx)
    {
    TSize sz( ListBoxItemSize(aListBox, aItemDrawer) );
    TInt B = AknLayoutUtils::CorrectBaseline(sz.iHeight, aLayout.iB, aLayout.FontId());
    const CFont *font = AknLayoutUtils::FontFromId(aLayout.FontId());
    CGraphicsContext::TTextAlign align = AknLayoutUtils::TextAlignFromId(aLayout.iJ);
    SetupColumnTextCell(aListBox, aItemDrawer, aIndex, font, aLayout.iC, aLayout.il, aLayout.ir, B, aLayout.iW, align, startx,endx);
    }

EXPORT_C void AknListBoxLayouts::SetupFormTextCell( CEikListBox& /*aListBox*/,
                                                   CFormattedCellListBoxItemDrawer* aItemDrawer,
                                                   TInt aIndex,
                                                   const TAknTextLineLayout &aLayout,
                                                   const TPoint& p1,
                                                   const TPoint& p2 )
    {
    _AKNTRACE( "[%s][%s][%d]", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    CFormattedCellListBoxData* d( aItemDrawer->FormattedCellData() );
    TRAP_IGNORE( d->SetTextSubCellL( aIndex, aLayout ) );
    d->SubCellsMightIntersect( ETrue );

    // new layout system sets subcell's position etc. However, if this
    // fallback method is used, old p1 and p2 need to override
    // position given by layout. Subcell position & size are not used
    // by new drawing system, but might be queried by 3rd party apps.
    TRAP_IGNORE( d->SetSubCellPositionL( aIndex, p1 );
                 d->SetSubCellSizeL( aIndex,TSize( (p2-p1).iX, (p2-p1).iY ) ));
    d->UseScalableLayoutData( ETrue );
    }

EXPORT_C void AknListBoxLayouts::SetupColumnGfxCell(CEikListBox& aListBox, 
                   CColumnListBoxItemDrawer* aItemDrawer, 
                   TInt aIndex,
                   const TAknWindowLineLayout &aLayout,
                   TInt startx, 
                   TInt endx)
    {
    SetupColumnGfxCell(aListBox, aItemDrawer, aIndex, aLayout.il, aLayout.it, aLayout.ir, aLayout.ib, aLayout.iW, aLayout.iH, startx, endx);
    }

EXPORT_C void
AknListBoxLayouts::SetupFormGfxCell( CEikListBox& /*aListBox*/, 
                                     CFormattedCellListBoxItemDrawer* aItemDrawer, 
                                     TInt aIndex,
                                     const TAknWindowLineLayout &aLayout,
                                     const TPoint& p1, 
                                     const TPoint& p2 )
    {
    _AKNTRACE( "[%s][%s][%d]", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    CFormattedCellListBoxData* d( aItemDrawer->FormattedCellData() );
    TRAP_IGNORE( d->SetGraphicSubCellL( aIndex, aLayout ) );
    d->SubCellsMightIntersect( ETrue );

    // new layout system sets subcell's position etc. However, if this
    // fallback method is used, old p1 and p2 need to override
    // position given by layout. Subcell position & size are not used
    // by new drawing system, but might be queried by 3rd party apps.
    TRAP_IGNORE( d->SetSubCellPositionL( aIndex, p1 );
                 d->SetSubCellSizeL( aIndex, TSize( (p2-p1).iX, (p2-p1).iY)));
    d->UseScalableLayoutData( ETrue );
    }

EXPORT_C void AknListBoxLayouts::SetupFormTextCell(CEikListBox& aListBox, CFormattedCellListBoxItemDrawer* aItemDrawer, 
                 TInt index,
                 const CFont *font, 
                 TInt C, 
                 TInt lm, 
                 TInt rm, 
                 TInt B, 
                 TInt W, 
                 CGraphicsContext::TTextAlign aAlign, 
                 TPoint /*p1*/, 
                 TPoint /*p2*/)
    {
    _AKNTRACE( "[%s][%s][%d]", "AknListBoxLayouts", __FUNCTION__, __LINE__ );
    TSize size( ListBoxItemSize( aListBox, aItemDrawer ) );

    if ( IsParentRelative( lm ) ) { lm = size.iWidth - ELayoutP + lm; }
    if ( IsParentRelative( rm ) ) { rm = size.iWidth - ELayoutP + rm; }
    if ( IsParentRelative( W ) ) { W = size.iWidth - ELayoutP + W; }

    if ( IsEmptyVal( lm ) ) { lm = size.iWidth - rm - W; }
    if ( IsEmptyVal( rm ) ) { rm = size.iWidth - lm - W; }
    if ( IsEmptyVal( W ) ) { W = size.iWidth - lm - rm; }

    TAknTextLineLayout textLine;
    textLine.iC = C;                        // color
    textLine.il = lm;                       // left
    textLine.ir = rm;                       // right
    textLine.iB = B;                        // baseline
    textLine.iW = ELayoutEmpty;             // width
    textLine.iJ = IdFromTextAlign( aAlign );// justification
    // font id - must not be ELayoutEmpty, because it will crash in chinece variant
    textLine.iFont = EAknLogicalFontPrimaryFont;
    textLine.iBaselineSkip = 0;           
    textLine.iNumberOfLinesShown = 1;
    
    TRAP_IGNORE( aItemDrawer->FormattedCellData()->SetTextSubCellL( index, textLine );
                 aItemDrawer->FormattedCellData()->SetSubCellFontL( index, font ) );
    aItemDrawer->FormattedCellData()->SubCellsMightIntersect( ETrue );
    aItemDrawer->FormattedCellData()->UseScalableLayoutData( ETrue );
    if (C != 215) // Black is default text color and we don't want to set all colors... 
        {
        CFormattedCellListBoxData::TColors colors;
        colors.iText = AKN_LAF_COLOR_STATIC(C);
        colors.iBack = aItemDrawer->BackColor();
        colors.iHighlightedText = aItemDrawer->HighlightedTextColor();
        colors.iHighlightedBack = aItemDrawer->HighlightedBackColor();
        TRAP_IGNORE( 
            aItemDrawer->FormattedCellData()->SetSubCellColorsL(index, colors));
        }
    }

EXPORT_C void AknListBoxLayouts::SetupFormAntiFlickerTextCell(CEikListBox& /*aListBox*/, CFormattedCellListBoxItemDrawer* aItemDrawer,
                           TInt aIndex,
                           const TAknTextLineLayout &aLayout,
                           const TPoint& /*p1*/,
                           const TPoint& /*p2*/)
    {
    TRAP_IGNORE( aItemDrawer->FormattedCellData()->SetTextSubCellL( aIndex, aLayout ) );
    aItemDrawer->FormattedCellData()->SubCellsMightIntersect( ETrue );
    }

EXPORT_C void AknListBoxLayouts::SetupFormAntiFlickerTextCell(CEikListBox& aListBox, CFormattedCellListBoxItemDrawer* aItemDrawer, 
                 TInt index,
                 const CFont *font, 
                 TInt C, 
                 TInt lm, 
                 TInt rm, 
                 TInt B, 
                 TInt W, 
                 CGraphicsContext::TTextAlign aAlign, 
                 TPoint p1, 
                 TPoint p2)
    {
    SetupFormTextCell( aListBox, aItemDrawer, index, font, C, lm, rm, B, W, aAlign, p1, p2 );
    }

// this is common popuplist setup code
static TSize PopupListItemSize(const TAknWindowLineLayout &aL)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TAknLayoutRect temp, layout;
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );

    temp.LayoutRect( mainPane, AknLayoutScalable_Avkon::popup_menu_window(13));
    
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
    layout.LayoutRect( temp.Rect(), lineLayout);
   
    temp.LayoutRect( layout.Rect(), AknLayoutScalable_Avkon::list_menu_pane(0));
    layout.LayoutRect( temp.Rect(), aL);

    return layout.Rect().Size();
    }

static void SetupCommonPopupListL(CEikFormattedCellListBox* aListBox, const TAknWindowLineLayout &aLayout )
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    CFormattedCellListBoxItemDrawer *itemDrawer = aListBox->ItemDrawer();

    AknListBoxLayouts::SetupStandardListBox( *aListBox );
    AknListBoxLayouts::SetupStandardFormListbox( itemDrawer );
    AknListBoxLayouts::SetupListboxPosL( *aListBox, aLayout );

    itemDrawer->FormattedCellData()->ResetSLSubCellArray();
    itemDrawer->SetItemCellSize( PopupListItemSize( aLayout ) );
    }

//
// AVKON STYLE LISTBOXES!
//

static TAknLayoutRect CommonLayoutRect(TAknWindowLineLayout aLayoutLine,
                                       TAknWindowLineLayout aParent)
    {
    TAknLayoutRect parent;

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    parent.LayoutRect( mainPane, aParent );

    TAknLayoutRect layout;
    layout.LayoutRect(parent.Rect(), aLayoutLine);
    return layout;
    }

static TAknLayoutRect CommonLayoutRect(TAknWindowLineLayout aLayoutLine,
                                       TAknWindowLineLayout aParent,
                                       TAknWindowLineLayout aGrandParent)
    {    
    TAknLayoutRect parent = CommonLayoutRect(aParent, aGrandParent);
    TAknLayoutRect layout;
    layout.LayoutRect(parent.Rect(), aLayoutLine);
    return layout;
    }

// extended skin support
static void SetESSTextColor( CListItemDrawer* aItemDrawer,
                             TAknsQsnTextColorsIndex aIndex )
    {
    TRgb color( KRgbBlack );  // sane default for nonskinned case

    // unfortunately, we still need to check this. It is still
    // possible in 3.0 to create an application, that is not
    // skinned. If skinning is not checked here, it is possible to
    // have a list with white background and white text.
    
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, aIndex );
        }

    aItemDrawer->SetTextColor( color );
    }


// extended skin support
static void SetESSHighlightedTextColor( CListItemDrawer* aItemDrawer,
                                        TAknsQsnTextColorsIndex aIndex )
    {
    TRgb color( KRgbBlack );
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, aIndex );
        }
    aItemDrawer->SetHighlightedTextColor( color );
    }

static void SetESSHighlightedTextColor( CListItemDrawer* aItemDrawer )
    {
    SetESSHighlightedTextColor( aItemDrawer, EAknsCIQsnTextColorsCG10 );
    }


// extended skin support
static void SetESSHighlightedTextColor( CFormattedCellListBoxData::TColors& aColors,
                                        TAknsQsnTextColorsIndex aIndex )
    {
    TRgb color( aIndex == EAknsCIQsnTextColorsCG12 ? KRgbWhite : KRgbBlack );
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, aIndex );
        }

    aColors.iHighlightedText = color;
    }

static void SetESSTextColor( CFormattedCellListBoxData::TColors& aColors,
                             TAknsQsnTextColorsIndex aIndex )
    {
    TRgb color( aIndex == EAknsCIQsnTextColorsCG12 ? KRgbWhite : KRgbBlack );
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        // this does not modify color unless it gets a correct one
        // no real need to check errors
        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
                                   color, KAknsIIDQsnTextColors, aIndex );
        }
    aColors.iText = color;
    }


// -----------------------------------------------------------------------------
// SetupStretchableListL
// -----------------------------------------------------------------------------
//
static void SetupStretchableListL( 
            CEikFormattedCellListBox* aListBox,
            const TAknWindowComponentLayout& aNormalLayout,
#ifdef RD_LIST_STRETCH
            const TAknWindowComponentLayout& aStretchedLayout,
#else            
            const TAknWindowComponentLayout& /*aStretchedLayout*/,
#endif // RD_LIST_STRETCH
            const TBool aSetColors = ETrue )
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    const TAknWindowComponentLayout* listLayout;

#ifdef RD_LIST_STRETCH
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         aListBox->ItemDrawer()->FormattedCellData()->StretchingEnabled() )
        {
        listLayout = &aStretchedLayout;
        }
    else
#endif // RD_LIST_STRETCH
        {
        listLayout = &aNormalLayout;
        }
    
    TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose(
        AknLayoutScalable_Avkon::listscroll_gen_pane( 0 ),
        TAknWindowComponentLayout::Compose( 
        AknLayoutScalable_Avkon::list_gen_pane( 0 ), *listLayout ) );

    AknListBoxLayouts::SetupStandardListBox( *aListBox );
    AknListBoxLayouts::SetupStandardFormListbox( aListBox->ItemDrawer() );
    AknListBoxLayouts::SetupListboxPosL( *aListBox, layout.LayoutLine() );
    
    if ( aSetColors && AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( aListBox->ItemDrawer() );
        SetESSTextColor( aListBox->ItemDrawer(), EAknsCIQsnTextColorsCG6 );
        }

    aListBox->ItemDrawer()->FormattedCellData()->ResetSLSubCellArray();
    }

// -----------------------------------------------------------------------------
// SetupStretchableListL
// -----------------------------------------------------------------------------
//
static void SetupStretchableListL( 
            CEikColumnListBox* aListBox,
            const TAknWindowComponentLayout& aNormalLayout,
            const TAknWindowComponentLayout& aStretchedLayout )
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    const TAknWindowComponentLayout* listLayout;
    
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        listLayout = &aStretchedLayout;
        }
    else
        {
        listLayout = &aNormalLayout;
        }
    
    TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose(
        AknLayoutScalable_Avkon::listscroll_gen_pane( 0 ),
        TAknWindowComponentLayout::Compose( 
        AknLayoutScalable_Avkon::list_gen_pane( 0 ), *listLayout ) );

    AknListBoxLayouts::SetupStandardListBox( *aListBox );
    AknListBoxLayouts::SetupStandardColumnListbox( aListBox->ItemDrawer() );
    AknListBoxLayouts::SetupListboxPosL( *aListBox, layout.LayoutLine() );
    
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( aListBox->ItemDrawer() );
        SetESSTextColor( aListBox->ItemDrawer(), EAknsCIQsnTextColorsCG6 );
        }

    aListBox->ItemDrawer()->ColumnData()->ResetSLSubCellArray();
    }

// -----------------------------------------------------------------------------
// SetupListL
// -----------------------------------------------------------------------------
//
static void SetupListL( CEikColumnListBox* aListBox,
                       const TAknWindowComponentLayout& aNormalLayout )
    {
    SetupStretchableListL( aListBox, aNormalLayout, aNormalLayout );
    }

// -----------------------------------------------------------------------------
// ShowAllRows
// -----------------------------------------------------------------------------
//
#ifdef RD_LIST_STRETCH
static TBool ShowAllRows( CFormattedCellListBoxData* aData )
    {
    TBool result( aData->SecondRowHidden() & aData->StretchingEnabled() );
    result &= Layout_Meta_Data::IsLandscapeOrientation();
    result &= Layout_Meta_Data::IsListStretchingEnabled();
    result |= !aData->SecondRowHidden();

    return result;
    }
#else
static TBool ShowAllRows( CFormattedCellListBoxData* /*aData*/ )
    {
    return ETrue;    
    }
#endif // RD_LIST_STRETCH

EXPORT_C CAknSingleStyleListBox::CAknSingleStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_A_COLUMN) { AKNTASHOOK_ADD( this, "CAknSingleStyleListBox" ); }

EXPORT_C CAknSingleNumberStyleListBox::CAknSingleNumberStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN) { AKNTASHOOK_ADD( this, "CAknSingleNumberStyleListBox" ); }

EXPORT_C CAknSingleHeadingStyleListBox::CAknSingleHeadingStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN) { AKNTASHOOK_ADD( this, "CAknSingleHeadingStyleListBox" ); }

EXPORT_C void CAknSingleHeadingStyleListBox::CreateItemDrawerL() 
    {
    CColumnListBoxData* columnData=CColumnListBoxData::NewL();
    CleanupStack::PushL(columnData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CSingleHeadingStyleItemDrawer(Model(), iEikonEnv->NormalFont(), columnData);
    CleanupStack::Pop();
    }


EXPORT_C void CAknSetStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CSettingItemEditingListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknFormGraphicStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormGraphicListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }


EXPORT_C void CAknDoublePopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknSinglePopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknSingleGraphicPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknSingleGraphicHeadingPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknSingleHeadingPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }





EXPORT_C void CAknDoubleLargeGraphicPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }


EXPORT_C void CAknSingle2GraphicPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknDoubleGraphicPopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }



EXPORT_C CListBoxView*
CAknSingleHeadingStyleListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CSingleHeadingStyleView);
    }

EXPORT_C CAknSingleGraphicStyleListBox::CAknSingleGraphicStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN) 
    {
    iCoeEnv = CCoeEnv::Static();
    AKNTASHOOK_ADD( this, "CAknSingleGraphicStyleListBox" );
    }


EXPORT_C void CSingleHeadingStyleItemDrawer::SetTopItemIndex(TInt aTop)
    {
    iTopItemIndex = aTop; 
    }

EXPORT_C void CDoubleLargeStyleItemDrawer::DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const
    {
    CFormattedCellListBoxItemDrawer::DrawItem(aItemIndex, aItemRectPos, aItemIsSelected, aItemIsCurrent, aViewIsEmphasized, aViewIsDimmed);
    }


EXPORT_C void CSingleHeadingStyleItemDrawer::DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const
    {
    TRect actualItemRect(aItemRectPos, iItemCellSize);
    DrawActualItem(aItemIndex,actualItemRect,aItemIsCurrent, aViewIsEmphasized, aViewIsDimmed, aItemIsSelected);

    }


EXPORT_C void 
CWordWrappedFormattedCellItemDrawer::DrawItem( TInt aItemIndex,
                                               TPoint aItemRectPos,
                                               TBool aItemIsSelected,
                                               TBool aItemIsCurrent,
                                               TBool aViewIsEmphasized,
                                               TBool aViewIsDimmed ) const
    {
    CFormattedCellListBoxItemDrawer::DrawItem( aItemIndex,
                                               aItemRectPos,
                                               aItemIsSelected,
                                               aItemIsCurrent,
                                               aViewIsEmphasized,
                                               aViewIsDimmed );
    }


// -----------------------------------------------------------------------------
// CWordWrappedFormattedCellItemDrawer::DrawItemText
// -----------------------------------------------------------------------------
//
EXPORT_C void 
CWordWrappedFormattedCellItemDrawer::DrawItemText( TInt aItemIndex,
                                                   const TRect& aItemTextRect,
                                                   TBool aItemIsCurrent,
                                                   TBool /*aViewIsEmphasized*/, 
                                                   TBool aItemIsSelected ) const
    {
    _AKNTRACE( "[%s][%s][%d]", "CWordWrappedFormattedCellItemDrawer", __FUNCTION__, __LINE__ );
    iGc->SetPenColor(iTextColor);
    iGc->SetBrushColor(iBackColor);
    
    TPtrC itemText = iModel->ItemText( aItemIndex );

    SetupGc(aItemIndex);


    TBufC<KMaxTotalDataLength> target;
    // AVKON ITEM MARKS!

    TPtrC repl;
    TInt pos = -1;

    TBool removeicon = (!aItemIsSelected && !ItemMarkReverse()) || (aItemIsSelected && ItemMarkReverse());
    if ( Flags() & EDrawMarkSelection && ItemMarkPosition() != -1 && removeicon)
        {
        repl.Set( ItemMarkReplacement() );
        pos = ItemMarkPosition();
        } 

#ifdef RD_LIST_STRETCH
    // +2 is for the last column separator and space between the first and the
    // second text lines in case they are concanated.
    TInt size( itemText.Length() + repl.Length() + 2 );
#else
    // (+1 is for the last column separator)
    TInt size = itemText.Length() + repl.Length() + 1;
#endif // RD_LIST_STRETCH
    if ( pos >= 0 )
        {
        size += pos; // space for other column separators
        }

    HBufC* buffer = HBufC::New( size );
    if ( !buffer )
        {
        return;
        }

    TPtr des = ( buffer ? buffer->Des() : target.Des() );
    // Note that ReplaceColumn does not update correct length in variable 'des',
    // because it is not a reference parameter :(
    AknLAFUtils::ReplaceColumn(des, &itemText, &repl, '\t', pos);
    des.Set( buffer->Des() );

    // END OF ITEM MARKS!
    
    TPtr targetptr = des;
    TBufC<KMaxTotalDataLength> target2(KNullDesC);

    // Try to allocate buffer dynamically. If out of memory, use the fixed size stack buffer.
    // This size should be sufficient.
    size = targetptr.Length() * 2;
    HBufC* buffer2 = HBufC::New( size );
    if ( !buffer2 )
        {
        delete buffer;
        return;
        }

    TPtr des2 = buffer2->Des();

#ifdef RD_LIST_STRETCH
    // If list strecthing is enabled and the device is in landscape orientation
    // then one-line layout should be used -> we must move the second text line 
    // after the first line if two independent lines are specified. 
    // Otherwerwise the first text line can be used as it is.
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         FormattedCellData()->StretchingEnabled() )
        {
        TPtrC itemText;
        TextUtils::ColumnText( itemText, iSubCell, &targetptr );

        TPtrC secondaryText;
        TextUtils::ColumnText( secondaryText, iSubCell2, &targetptr );
        
        if ( secondaryText.Length() > 0 )
            {
            // append secondary text after the item text
            TInt columnPos = targetptr.FindF( secondaryText );
            
            if ( columnPos != KErrNotFound )
                {
                --columnPos; // subtract column separator
                targetptr.Replace( columnPos, secondaryText.Length(), secondaryText );
                targetptr[columnPos + secondaryText.Length()] = '\t';
                targetptr.Insert( columnPos, KEmptySpace );
                }
            }
        
        des2.Append( targetptr );
        }
    else
        {
        WordWrapListItem(des2, targetptr, iSubCell,iSubCell2, aItemIndex);
        // Set again because ReplaceColumn in WordWrapListItem does not update the length to 'des2' !
        des2.Set( buffer2 ? buffer2->Des() : target2.Des() );
        }
#else
    WordWrapListItem(des2, targetptr, iSubCell,iSubCell2, aItemIndex);
#endif // RD_LIST_STRETCH    

    // Set again because ReplaceColumn in WordWrapListItem does not update the length to 'des2' !
    des2.Set( buffer2->Des() );

    DrawBackgroundAndSeparatorLines( aItemTextRect );

    if( aItemIsCurrent )
        {
        FormattedCellData()->SetCurrentItemIndex(aItemIndex); // fonts for java
        }
        
    FormattedCellData()->SetCurrentlyDrawnItemIndex( aItemIndex );
    
    CFormattedCellListBoxData::TColors colors;
    colors.iText=iTextColor;
    colors.iBack=iBackColor;
    colors.iHighlightedText=iHighlightedTextColor;
    colors.iHighlightedBack=iHighlightedBackColor;
    FormattedCellData()->Draw( Properties( aItemIndex ),
                               *iGc,
                               &des2,
                               aItemTextRect,
                               aItemIsCurrent, colors );
    
    delete buffer2;
    delete buffer;
    }

EXPORT_C void CAknColumnListBoxView::EnableFindEmptyList()
    {
    SetFindEmptyListState(ETrue);
    }

EXPORT_C void CAknColumnListBoxView::SetFindEmptyListState(TBool aUsedWithFind)
    {
    iEmptyListWithFind = aUsedWithFind;
    }

TBool CAknColumnListBoxView::GetFindEmptyListState()
    {
    return iEmptyListWithFind;
    }

EXPORT_C void CAknColumnListBoxView::DrawEmptyList(const TRect &aClientRect) const 
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknColumnListBoxView", __FUNCTION__, __LINE__ );
    if (RedrawDisabled() || !IsVisible())
        return;
    CColumnListBoxItemDrawer *id = (CColumnListBoxItemDrawer*)ItemDrawer();
    if (id && id->ColumnData()) // OOM test of itemdrawer and data.
        { 
        if (!iEmptyListWithFind)
            {
            AknDrawWithSkins::DrawEmptyList(aClientRect, *iGc, *EmptyListText(), id->ColumnData()->Control());
            } 
        else
            {
            AknDrawWithSkins::DrawEmptyListWithFind(aClientRect, *iGc, *EmptyListText(), id->ColumnData()->Control());
            }
        }
    }

EXPORT_C void CAknColumnListBoxView::CalcBottomItemIndex()
    {
    CColumnListBoxView::CalcBottomItemIndex();
    //
    // The next piece of code removes filtering from find box when
    // new list items are added.
    //     
    if (Flags() & EItemCountModified)
    {
    CAknFilteredTextListBoxModel *model = STATIC_CAST(CAknFilteredTextListBoxModel*,iModel);
    CAknListBoxFilterItems *filter = model ? model->Filter() : 0;
    if (filter) 
        {
        TRAP_IGNORE(filter->ResetFilteringL());

        }
    }
    }

EXPORT_C TAny* CAknColumnListBoxView::Reserved_1()
    {
    return NULL;
    }


EXPORT_C void CSingleHeadingStyleView::DrawEmptyList(const TRect& aClientRect) const 
    {
    CAknColumnListBoxView::DrawEmptyList(aClientRect);
    }

EXPORT_C TAny* CSingleHeadingStyleView::Reserved_1()
    {
    return NULL;
    }


EXPORT_C void CAknSetStyleListBox::Draw(const TRect& aRect) const
    {
    // NOTE THIS DRAW METHOD MUST NOT CALL THE BASE CLASS METHODS!
    // THE ClearMargins() call should NOT be called with Set Style Lists!

    if (iModel->NumberOfItems() == 0)
        {
        iView->DrawEmptyList(Rect());
        }
    else
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iItemDrawer->Gc() );
        if ( transApi )
            {
            transApi->BeginRedraw( MAknListBoxTfxInternal::EListView, Rect() );
            }
#endif
        iView->Draw(&aRect);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        if ( transApi )
            {
            transApi->EndViewRedraw( aRect );
            }
#endif        
        }
    }

EXPORT_C TTypeUid::Ptr CAknSetStyleListBox::MopSupplyObject(TTypeUid aId)
    {
    return CEikTextListBox::MopSupplyObject( aId );
    }


EXPORT_C void CSingleHeadingStyleView::Draw(const TRect *aRect) const
    {
    // Expects certain itemdrawer implementation!
    STATIC_CAST(CSingleHeadingStyleItemDrawer*,iItemDrawer)->SetTopItemIndex(iTopItemIndex);
    CAknColumnListBoxView::Draw(aRect);
    }

EXPORT_C CSingleHeadingStyleItemDrawer::CSingleHeadingStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData)
    : CColumnListBoxItemDrawer(aTextListBoxModel, aFont, aColumnData)
    {
    SetData(aColumnData);
    }



EXPORT_C CSingleHeadingStyleItemDrawer::~CSingleHeadingStyleItemDrawer()
    {
    }


EXPORT_C void CAknSingleGraphicHeadingStyleListBox::CreateItemDrawerL() 
    {
    CColumnListBoxData* columnData=CColumnListBoxData::NewL();
    CleanupStack::PushL(columnData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CSingleHeadingStyleItemDrawer(Model(), iEikonEnv->NormalFont(), columnData);
    CleanupStack::Pop();
    }

EXPORT_C void CAknDoubleLargeStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CDoubleLargeStyleItemDrawer(Model(), iEikonEnv->NormalFont(), cellData, this);
    CleanupStack::Pop();
    }

EXPORT_C void CAknDoubleStyle2ListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CWordWrappedFormattedCellItemDrawer(Model(), iEikonEnv->NormalFont(), cellData, this, 1,2);
    CleanupStack::Pop();
    }


EXPORT_C CDoubleLargeStyleItemDrawer::CDoubleLargeStyleItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox *aListBox)
    : CFormattedCellListBoxItemDrawer(aTextListBoxModel, aFont, aFormattedCellData)
    {
    iListBox_tmp = aListBox;
    }

EXPORT_C void CDoubleLargeStyleItemDrawer::CFormattedCellListBoxItemDrawer_Reserved()
    {
    }


EXPORT_C CWordWrappedFormattedCellItemDrawer::CWordWrappedFormattedCellItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData, CEikListBox * /*aListBox*/, TInt aSubCell, TInt aSubCell2)
    : CFormattedCellListBoxItemDrawer(aTextListBoxModel, aFont, aFormattedCellData)
    {
    iSubCell = aSubCell;
    iSubCell2 = aSubCell2;
    }

EXPORT_C void CWordWrappedFormattedCellItemDrawer::CFormattedCellListBoxItemDrawer_Reserved()
    {
    }

EXPORT_C CListBoxView*
CAknSingleGraphicHeadingStyleListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CSingleHeadingStyleView);
    }

EXPORT_C CListBoxView*
CAknColumnListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CAknColumnListBoxView);
    }

EXPORT_C void CAknColumnListBox::CreateModelL()
    {
    __ASSERT_DEBUG(iModel == 0, Panic(EAknPanicOutOfRange));
    CTextListBoxModel* model=new(ELeave) CAknFilteredTextListBoxModel;
    iModel=model;
    }

EXPORT_C TInt CAknFormGraphicStyleListBox::AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknFormGraphicStyleListBox", __FUNCTION__, __LINE__ );
    // the last item in the list does not need a border, so we need to remove the remainder
    __LAYOUT_DEBUG(aRect.Height() % iItemHeight == 0, RDebug::Print(_L("FormGraphicStyleListBox Rect() is odd?")));
    TInt remainder = 18-21;
    aRect.iBr.iY -= remainder;
    return remainder;
    }

EXPORT_C TInt CAknColumnListBox::AdjustRectHeightToWholeNumberOfItems(TRect &aRect)  const
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknColumnListBox", __FUNCTION__, __LINE__ );
    // This code used to be in eiklbx.cpp.
    TInt remainder = aRect.Height() % iItemHeight;
    if (remainder != 0)
    {
    aRect.iBr.iY -= remainder;
    }
    return remainder;
    }
    
EXPORT_C void CAknColumnListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBox::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void* CAknColumnListBox::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

EXPORT_C void CAknColumnListBox::CEikListBox_Reserved() 
    {
    }

EXPORT_C void CAknSingleNumberHeadingStyleListBox::CreateItemDrawerL() 
    {
    CColumnListBoxData* columnData=CColumnListBoxData::NewL();
    CleanupStack::PushL(columnData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CSingleHeadingStyleItemDrawer(Model(), iEikonEnv->NormalFont(), columnData);
    CleanupStack::Pop();
    }

EXPORT_C CListBoxView*
CAknSingleNumberHeadingStyleListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CSingleHeadingStyleView);
    }

EXPORT_C CAknSingleGraphicHeadingStyleListBox::CAknSingleGraphicHeadingStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN) { AKNTASHOOK_ADD( this, "CAknSingleGraphicHeadingStyleListBox" ); }

EXPORT_C CAknSingleNumberHeadingStyleListBox::CAknSingleNumberHeadingStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN) { AKNTASHOOK_ADD( this, "CAknSingleNumberHeadingStyleListBox" ); }

EXPORT_C CAknSingleLargeStyleListBox::CAknSingleLargeStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN_X) { AKNTASHOOK_ADD( this, "CAknSingleLargeStyleListBox" ); }

EXPORT_C CAknSingle2GraphicStyleListBox::CAknSingle2GraphicStyleListBox() : AKNCOLUMNLISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN) 
    {
    iCoeEnv = CCoeEnv::Static();
    }

EXPORT_C CAknDoubleStyleListBox::CAknDoubleStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_A_COLUMN) { AKNTASHOOK_ADD( this, "CAknDoubleStyleListBox" ); }

EXPORT_C CAknDoubleNumberStyleListBox::CAknDoubleNumberStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN_XX) { AKNTASHOOK_ADD( this, "CAknDoubleNumberStyleListBox" ); }

EXPORT_C CAknDoubleGraphicStyleListBox::CAknDoubleGraphicStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN) { AKNTASHOOK_ADD( this, "CAknDoubleGraphicStyleListBox" ); }

EXPORT_C CAknDoubleLargeStyleListBox::CAknDoubleLargeStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN_XX) { AKNTASHOOK_ADD( this, "CAknDoubleLargeStyleListBox" ); }

EXPORT_C CAknDoubleTimeStyleListBox::CAknDoubleTimeStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN) { AKNTASHOOK_ADD( this, "CAknDoubleTimeStyleListBox" ); }


//CAknDouble2GraphicStyleListBox
EXPORT_C void CAknDouble2GraphicStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CWordWrappedFormattedCellItemDrawer(Model(), iEikonEnv->NormalFont(), cellData, this, 1,2);
    CleanupStack::Pop();
    }

EXPORT_C CAknDouble2GraphicStyleListBox::CAknDouble2GraphicStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN) { AKNTASHOOK_ADD( this, "CAknDouble2GraphicStyleListBox" ); }

//CAknDouble2LargeStyleListBox
EXPORT_C void CAknDouble2LargeStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CWordWrappedFormattedCellItemDrawer(Model(), iEikonEnv->NormalFont(), cellData, this, 1,2);
    CleanupStack::Pop();
    }

EXPORT_C CAknDouble2LargeStyleListBox::CAknDouble2LargeStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_BC_COLUMN_XX) { AKNTASHOOK_ADD( this, "CAknDouble2LargeStyleListBox" ); }


//CAknDouble2GraphicLargeStyleListBox
EXPORT_C void CAknDouble2GraphicLargeStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CWordWrappedFormattedCellItemDrawer(Model(), iEikonEnv->NormalFont(), cellData, this, 2, 3);
    CleanupStack::Pop();
    }

EXPORT_C CAknDouble2GraphicLargeStyleListBox::CAknDouble2GraphicLargeStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN_XX) { }

// CAknDouble2GraphicLargeGraphicStyleListBox
EXPORT_C void CAknDouble2GraphicLargeGraphicStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( cellData );
    iItemDrawer=new(ELeave) CWordWrappedFormattedCellItemDrawer( Model(), iEikonEnv->NormalFont(),
                                                                 cellData, this, 2, 3 );
    CleanupStack::Pop();
    }

EXPORT_C CAknDouble2GraphicLargeGraphicStyleListBox::CAknDouble2GraphicLargeGraphicStyleListBox() : AKNDOUBLELISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN_XX) { AKNTASHOOK_ADD( this, "CAknDouble2GraphicLargeGraphicStyleListBox" ); }

EXPORT_C CAknSettingStyleListBox::CAknSettingStyleListBox() : AKNSETTINGLISTBOXNAME(R_LIST_PANE_LINES_A_COLUMN_X) { AKNTASHOOK_ADD( this, "CAknSettingStyleListBox" ); }

EXPORT_C CAknSettingNumberStyleListBox::CAknSettingNumberStyleListBox() : AKNSETTINGLISTBOXNAME(R_LIST_PANE_LINES_AB_COLUMN_X) { AKNTASHOOK_ADD( this, "CAknSettingNumberStyleListBox" ); }

EXPORT_C void CAknSingleGraphicBtPopupMenuStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknSingleGraphicPopupMenuStyleListBox::SizeChanged();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C CAknSingleHeadingPopupMenuStyleListBox::CAknSingleHeadingPopupMenuStyleListBox() { AKNTASHOOK_ADD( this, "CAknSingleHeadingPopupMenuStyleListBox" ); }

EXPORT_C CAknSingleGraphicHeadingPopupMenuStyleListBox::CAknSingleGraphicHeadingPopupMenuStyleListBox() { AKNTASHOOK_ADD( this, "CAknSingleGraphicHeadingPopupMenuStyleListBox" ); }

// deprecated 
EXPORT_C void CAknSinglePopupSubmenuStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    _AKNTRACE_FUNC_EXIT;
    }

// deprecated 
void CAknSinglePopupSubmenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    // not used in Series 60 - no need to remove magic numbers
    CEikFormattedCellListBox &aListBox = *this;
    CFormattedCellListBoxItemDrawer *itemDrawer = aListBox.ItemDrawer();

    TInt width = aListBox.MinimumSize().iWidth;
    TInt textwidth=0;
     
    if (!(width == 60 ||width == 81 ||width == 102)) width = 60;

    __LAYOUT_DEBUG((width == 60 || width == 81 || width ==102),
                   RDebug::Print(_L("EEikPanicListboxSizeIsNotAccordingToLAFSpec")));
    
    AknListBoxLayouts::SetupStandardListBox(aListBox);
    AknListBoxLayouts::SetupStandardFormListbox(itemDrawer);
    AknListBoxLayouts::SetupListboxPos(aListBox, 0, 0, -1, -1, width, 18);

    if (width == 60) textwidth = 38;
    if (width == 59) textwidth = 59;
    if (width == 102) textwidth = 88; 
    AknListBoxLayouts::SetupFormAntiFlickerTextCell(aListBox, itemDrawer, 0,
                LatinBold12(), 215, 8, 6, 12, textwidth, CGraphicsContext::ELeft, TPoint(0,0), TPoint(width,18));
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknDouble2PopupMenuStyleListBox::CreateItemDrawerL() 
    {
    CFormattedCellListBoxData* cellData=CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL(cellData);
    __ASSERT_DEBUG(iItemDrawer == 0, Panic(EAknPanicOutOfRange));
    iItemDrawer=new(ELeave)CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), cellData);
    CleanupStack::Pop();
    }


/**
 * list_single_2graphic_pane_cp2
 *
 * list item string format: "0\t1\tTextLabel\t2\t3"
 * where 0,1,2,3 are index to the icon array 
 */

EXPORT_C CAknSingle2GraphicPopupMenuStyleListBox::CAknSingle2GraphicPopupMenuStyleListBox() { AKNTASHOOK_ADD( this, "CAknSingle2GraphicPopupMenuStyleListBox" ); }

EXPORT_C CAknDoubleGraphicPopupMenuStyleListBox ::CAknDoubleGraphicPopupMenuStyleListBox() { AKNTASHOOK_ADD( this, "CAknDoubleGraphicPopupMenuStyleListBox" ); }

EXPORT_C void CAknSetStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void CAknSetStyleListBoxView::DrawEmptyList(const TRect &aClientRect) const
    {
    if (RedrawDisabled() ||!IsVisible()) 
        return;
    
    CFormattedCellListBoxItemDrawer *itemDrawer = (CFormattedCellListBoxItemDrawer*)iItemDrawer;
    AknDrawWithSkins::DrawEmptyListForSettingPage(aClientRect, *iGc, *EmptyListText(), itemDrawer->FormattedCellData()->Control());
    }

EXPORT_C TAny* CAknSetStyleListBoxView::Reserved_1()
    {
    return NULL;
    }

EXPORT_C CListBoxView*
CAknSetStyleListBox::MakeViewClassInstanceL()
    {
    return (new(ELeave) CAknSetStyleListBoxView);
    }


EXPORT_C void CAknFormGraphicStyleListBox::ConstructWithWindowL(const CCoeControl *aParent,
                   TInt aFlags)
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknFormGraphicStyleListBox", __FUNCTION__, __LINE__ );
    CAknFilteredTextListBoxModel* model=new(ELeave) CAknFilteredTextListBoxModel;
    __ASSERT_DEBUG(iModel == 0, Panic(EAknPanicOutOfRange));
    iModel=model;
    model->ConstructL();
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);
    
    iListBoxFlags = aFlags;
    CreateWindowL(aParent);
    if ( AknLayoutUtils::PenEnabled() )
        {
        SetGloballyCapturing(ETrue);
        SetPointerCapture(ETrue);
        }
    EnableDragEvents();
    Window().SetPointerGrab(ETrue);
    if (iListBoxFlags & EIncrementalMatching)
    CreateMatchBufferL();
    CreateViewL();
    }

// ---------------------------------------------------------
// CAknFormGraphicStyleListBox::HandlePointerEventL
// Handles pointerevents of popupfield list in forms
// Closes popup if clicked outside of list. 
// ---------------------------------------------------------
//

EXPORT_C void CAknFormGraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknFormGraphicStyleListBox", __FUNCTION__, __LINE__ );
    if ( AknLayoutUtils::PenEnabled() )    
        {
        TRect rect(Rect());
    
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down && !rect.Contains(aPointerEvent.iPosition) )
            {
            // Clicked outside listbox rect, pointer event to popupfield
            Parent()->HandlePointerEventL(aPointerEvent);
            IgnoreEventsUntilNextPointerUp();
            }
        else 
            {           
            TPointerEvent newPointerEvent = aPointerEvent;
            
            // Remove Shift and Ctrl modifiers from PointerEvent to get radiobuttons to work
            // without multiselection   
            newPointerEvent.iModifiers &= ~EModifierShift;
            newPointerEvent.iModifiers &= ~EModifierCtrl;
                    
            CEikListBox::HandlePointerEventL(newPointerEvent);
            }
        }
    }

 
EXPORT_C void CAknSetStyleListBox::ConstructWithWindowL(const CCoeControl *aParent,
                   TInt aFlags)
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknSetStyleListBox", __FUNCTION__, __LINE__ );
    CAknFilteredTextListBoxModel* model=new(ELeave) CAknFilteredTextListBoxModel;
    __ASSERT_DEBUG(iModel == 0, Panic(EAknPanicOutOfRange));
    iModel=model;
    model->ConstructL();
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);
    
    iListBoxFlags = aFlags;
    CreateWindowL(aParent);
    EnableDragEvents();
    Window().SetPointerGrab(ETrue);
    if (iListBoxFlags & EIncrementalMatching)
    CreateMatchBufferL();
    CreateViewL();
    }

EXPORT_C void CAknAppStyleGrid::SetShortcutEnabledL(TBool aValue)
    {
    AKNSHORTCUTGRID::SetShortcutEnabledL(aValue);
    }

EXPORT_C void CAknAppStyleGrid::DrawBackgroundAroundGrid(CWindowGc &aGc, const TRect &aClientRect, const TRect &aGridRect)
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknAppStyleGrid", __FUNCTION__, __LINE__ );
    MAknsControlContext *cc = AknsDrawUtils::ControlContext( this );
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    if (!cc) cc = ItemDrawer()->FormattedCellData()->SkinBackgroundContext();
    AknsDrawUtils::BackgroundBetweenRects(skin, cc, aGc, aClientRect, aGridRect);
    }

EXPORT_C void CAknAppStyleGrid::ConstructL(const CCoeControl* aParent, TInt aFlags)
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknAppStyleGrid", __FUNCTION__, __LINE__ );
    AKNSHORTCUTGRID::ConstructL(aParent, aFlags);

    TResourceReader reader;
    CEikonEnv::Static()->CreateResourceReaderLC(reader, R_AVKON_GRID_STYLE_APP_GRID_AUTOMATIC_MIRRORING);
    SetLayoutFromResourceL(reader);
    CleanupStack::PopAndDestroy();
    }

EXPORT_C void CAknAppStyleGrid::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    // remember current data index  in case this is layout switch
    TInt currentDataIndex = GridView()->CurrentDataIndex(); 

    // this needs to be called before baseclass to set layouts correctly
    TRAP_IGNORE( SizeChangedL() );

    // so baseclass has up to date information here
    CAknGrid::SizeChanged();
    
    // restore current data index
    GridView()->SetCurrentDataIndex( currentDataIndex );

    // UpdateScrollBarsL(); already called by CAknGrid::SizeChanged();
    _AKNTRACE_FUNC_EXIT;
    }

enum
    {
    EAknAppStyleGrid3x3 = 0,
    EAknAppStyleGrid3x4 = 1,
    EAknAppStyleGrid4x3 = 2
    };

void CAknAppStyleGrid::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CAknGrid &listbox = *this;
    CFormattedCellListBoxItemDrawer *itemDrawer( listbox.ItemDrawer() );
    CFormattedCellListBoxData* d( itemDrawer->FormattedCellData() );
    AknListBoxLayouts::SetupStandardGrid(listbox);  // TODO ??
    
    TRect parentRect( Rect() );
    
    // First is checked if 3x4 or 4x3 items fits to the grid.
    TAknWindowLineLayout listscrollAppPaneLayout;        
    TAknWindowLineLayout gridAppPaneLayout;
    TAknWindowLineLayout cellAppPaneLayout;
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        // Layout data for 4x3 grid
        listscrollAppPaneLayout = AknLayoutScalable_Avkon::listscroll_app_pane(1); 
        gridAppPaneLayout = AknLayoutScalable_Avkon::grid_app_pane(3);        
        cellAppPaneLayout = AknLayoutScalable_Avkon::cell_app_pane(2, 0, 0);       
        }
    else
        {
        // Layout data for 3x4 grid
        listscrollAppPaneLayout = AknLayoutScalable_Avkon::listscroll_app_pane(1); 
        gridAppPaneLayout = AknLayoutScalable_Avkon::grid_app_pane(2);          
        cellAppPaneLayout = AknLayoutScalable_Avkon::cell_app_pane(1, 0, 0);       
        }
    
    TAknLayoutRect listscrollAppPane;
    TAknLayoutRect gridAppPane;
    TAknLayoutRect gridItem;
    
    listscrollAppPane.LayoutRect( parentRect, listscrollAppPaneLayout); 
    gridAppPane.LayoutRect( listscrollAppPane.Rect(), gridAppPaneLayout); 
    gridItem.LayoutRect( gridAppPane.Rect(), cellAppPaneLayout);
    
    TInt gridLayout = EAknAppStyleGrid3x3;
    
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        if (gridItem.Rect().Width() * 4 <= parentRect.Width() && 
            gridItem.Rect().Height() * 3 <= parentRect.Height())
            {
            // 4x3 grid is used if the items fit
            gridLayout = EAknAppStyleGrid4x3;
            }
        }
    else
        {
        if (gridItem.Rect().Width() * 3 <= parentRect.Width() && 
            gridItem.Rect().Height() * 4 <= parentRect.Height())
            {
            // 3x4 grid is used if the items fit
            gridLayout = EAknAppStyleGrid3x4;          
            }           
        }

    if ( gridLayout == EAknAppStyleGrid3x3 )
        {
        // 4x3 or 3x4 grid did not fit to the main pane. 
        // 3x3 grid is used instead. Layout data of 3x3 grid is needed
        listscrollAppPaneLayout = AknLayoutScalable_Avkon::listscroll_app_pane(0);        
        if (Layout_Meta_Data::IsLandscapeOrientation())
            {
            gridAppPaneLayout = AknLayoutScalable_Avkon::grid_app_pane(1);
            }
        else
            {
            gridAppPaneLayout = AknLayoutScalable_Avkon::grid_app_pane(0);                
            }
        cellAppPaneLayout = AknLayoutScalable_Avkon::cell_app_pane(0, 0, 0);

        listscrollAppPane.LayoutRect( parentRect, listscrollAppPaneLayout );
        gridAppPane.LayoutRect( listscrollAppPane.Rect(), gridAppPaneLayout );
        gridItem.LayoutRect( gridAppPane.Rect(), cellAppPaneLayout );
        }

    // set up grid size, and number of items in both orientations
    TRect itemRect( gridItem.Rect() );
    TInt primaryItems, secondaryItems;
                    
    switch( gridLayout )
        {
        case EAknAppStyleGrid3x4:
            primaryItems = 3;
            secondaryItems = 4;
            break;

        case EAknAppStyleGrid4x3:
            primaryItems = 4;
            secondaryItems = 3;
            break;
        case EAknAppStyleGrid3x3:  // fall trough
        default:                    
            primaryItems = 3;
            secondaryItems = 3;
            break;
        }

    TSize itemSize( itemRect.Size() );
    SetLayoutL( EFalse,                            //aVerticalOrientation
                !AknLayoutUtils::LayoutMirrored(), //aLeftToRight
                ETrue,                             //aTopToBottom
                primaryItems,                      //aNumOfItemsInPrimaryOrient
                secondaryItems,                    //aNumOfItemsInSecondaryOrient
                itemSize );                        //aSizeOfItems
    
    // Left margin is needed for a/h layouts to make room for the scroll bar
    TInt leftMargin = 0;

    if ( AknLayoutUtils::LayoutMirrored() )
        {
        TAknLayoutRect scrollPane;
        scrollPane.LayoutRect( listscrollAppPane.Rect(), AknLayoutScalable_Avkon::scroll_pane_cp15(0) );
        leftMargin = scrollPane.Rect().Width();
        }

    AknListBoxLayouts::SetupGridPos( listbox,
                                     cellAppPaneLayout.il + leftMargin,
                                     cellAppPaneLayout.it,
                                     cellAppPaneLayout.ir,
                                     cellAppPaneLayout.ib,
                                     gridItem.Rect().Width(),
                                     gridItem.Rect().Height() );

//    AknListBoxLayouts::SetupListboxPosL( listbox, gridAppPaneLayout );
    // TODO: should check the varieties. No need to worry too much,
    // since adaptation layer did not chech these either...
    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::cell_app_pane_g1( 0 ) );
    d->SetTextSubCellL(    1, AknLayoutScalable_Avkon::cell_app_pane_t1( 0 ) );
    d->SetGraphicSubCellL( 2, AknLayoutScalable_Avkon::cell_app_pane_g2( 0 ) );
    
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( itemDrawer, EAknsCIQsnTextColorsCG11 );
        SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG9 );
        }

    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );
    SetSeparatorLinePosition(this, ENoLine);
    _AKNTRACE_FUNC_EXIT;
    }
 

EXPORT_C void CAknPinbStyleGrid::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CAknGrid::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    _AKNTRACE_FUNC_EXIT;
    }

void CAknPinbStyleGrid::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    TAknLayoutRect gridLayout;
    gridLayout.LayoutRect( Rect(), AknLayoutScalable_Apps::cell_pinb_pane( 0, 0 ) );

    SetLayoutL( ETrue,  // aVerticalOrientation
                !AknLayoutUtils::LayoutMirrored(),   // aLeftToRight
                ETrue,   // aTopToBottom
                5,       // aNumOfItemsInPrimaryOrient
                5,       // aNumOfItemsInSecondaryOrient
                gridLayout.Rect().Size(), // aSizeOfItems
                0,      // aWidthOfSpaceBetweenItems=0
                0 );    // aHeightOfSpaceBetweenItems=0 

    SetPrimaryScrollingType( CAknGridView::EScrollFollowsItemsAndStops );
    SetSecondaryScrollingType( CAknGridView::EScrollFollowsItemsAndLoops );

    CFormattedCellListBoxItemDrawer *itemDrawer = ItemDrawer();

    AknListBoxLayouts::SetupStandardGrid( *this );
    AknListBoxLayouts::SetupGridPos( *this, AknLayoutScalable_Apps::cell_pinb_pane( 0, 0 ) );
    
    itemDrawer->FormattedCellData()->SetGraphicSubCellL( 0, 
        AknLayoutScalable_Apps::cell_pinb_pane_g1( 1 ).LayoutLine() );
        
    itemDrawer->FormattedCellData()->SetGraphicSubCellL( 1, 
        AknLayoutScalable_Apps::cell_pinb_pane_g2( 0 ).LayoutLine() );
        
    itemDrawer->FormattedCellData()->SetGraphicSubCellL( 2, 
        AknLayoutScalable_Apps::cell_pinb_pane_g3( 0 ).LayoutLine() );

    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );
  
    SetSeparatorLinePosition( this, ENoLine );
    
    itemDrawer->FormattedCellData()->SetBackgroundSkinStyle( &KAknsIIDQsnBgAreaMainPinb, Rect() );

    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( itemDrawer, EAknsCIQsnTextColorsCG11 );
        SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknQdialStyleGrid::SizeChanged() 
    {    
    _AKNTRACE_FUNC_ENTER;
    CAknGrid::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    _AKNTRACE_FUNC_EXIT;
    }

void CAknQdialStyleGrid::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    TInt i;

    TInt v = 0;  // variety
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        v = 1;
        }
        
    
    TAknLayoutRect gridLayout;
    gridLayout.LayoutRect(Rect(), AknLayoutScalable_Apps::cell_qdial_pane(0,0));

    SetLayoutL( EFalse,  // aVerticalOrientation
                ETrue,   // aLeftToRight
                ETrue,   // aTopToBottom
                3,       // aNumOfItemsInPrimaryOrient
                3,       // aNumOfItemsInSecondaryOrient
                // aSizeOfItems
                gridLayout.Rect().Size(),
                0,      // aWidthOfSpaceBetweenItems=0
                0 );    // aHeightOfSpaceBetweenItems=0 
    
    SetPrimaryScrollingType( CAknGridView::EScrollFollowsItemsAndStops );
    SetSecondaryScrollingType( CAknGridView::EScrollFollowsItemsAndLoops );

    CAknGrid &listbox = *this;
    CFormattedCellListBoxItemDrawer *itemDrawer = listbox.ItemDrawer();
    CFormattedCellListBoxData* d = itemDrawer->FormattedCellData();
    AknListBoxLayouts::SetupStandardGrid(listbox);

    // set up text cells, 2 options:
    // either subcells 0, 3, 4: up to 3 lines of text
    // or     subcells 2, 3, 4: up to 3 lines of text with
    //        small numbertype indication icon in 1st line
    // subcells 3 and 4 are same in both cases

    // 1st text line, without image
    d->SetTextSubCellL( 0, AknLayoutScalable_Apps::cell_qdial_pane_t1(0).LayoutLine() );

    // 1st text line with image. the image is in subcell #1
    d->SetTextSubCellL( 2, AknLayoutScalable_Apps::cell_qdial_pane_t1(1).LayoutLine() );

    // 2nd text line
    d->SetTextSubCellL( 3, AknLayoutScalable_Apps::cell_qdial_pane_t2(0).LayoutLine() );

    // 3rd text line
    d->SetTextSubCellL( 4, AknLayoutScalable_Apps::cell_qdial_pane_t3(0).LayoutLine() );

    // ----------------------------------------------------------------------
    //
    // set up graphical subcells
    // subcell  1: number type indication. Used with texts
    // subcell 16: marked item indication
    // subcell 15: voice mbox / large number icon, different size from thumbnail
    // subcells 6, 8, 10, 12, 14 : numbertype indication icon, similar to 1 but
    //                             used with thumbnail images
    // subcells 5, 7, 9, 11, 13  : thumbnail image, all same size, this many
    //                             needed for legacy support
    // multiple subcells should be eventually phased out without breaking
    // 

    // subcell 1: number type indication for list items with texts, variety 1
    d->SetGraphicSubCellL( 1, AknLayoutScalable_Apps::cell_qdial_pane_g2(1).LayoutLine() );

    // subcells 5, 7, 9, 11, 13, all same size (thumbnail)
    for ( i = 5; i <= 13; i+=2 )
        {
        d->SetGraphicSubCellL( i, AknLayoutScalable_Apps::thumbnail_qdial_pane(v).LayoutLine() );
        }

    // subcells 6, 8, 10, 12, 14, all same size (numbertype indication for thumbnail items)
    for ( i = 6; i <= 14; i+=2 )
        {
        d->SetGraphicSubCellL( i, AknLayoutScalable_Apps::cell_qdial_pane_g2(0).LayoutLine() );
        }

    // subcell 15 (large icon)
    d->SetGraphicSubCellL( 15, AknLayoutScalable_Apps::cell_qdial_pane_g1(v).LayoutLine() );

    // subcell 16: marked item indication
    // This must be in last subcell because of drawing order
    itemDrawer->SetItemMarkPosition( 16 );
    itemDrawer->SetItemMarkReplacement( KFirstCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );
  
    d->SetGraphicSubCellL( 16, AknLayoutScalable_Apps::cell_qdial_pane_g2(v).LayoutLine() );
    
    SetSeparatorLinePosition(this, ENoLine);
    
    d->SetBackgroundSkinStyle( &KAknsIIDQsnBgAreaMainQdial, Rect() );

    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( itemDrawer, EAknsCIQsnTextColorsCG11 );
        SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
        }
    
    DisableScrolling( ETrue );
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknCaleMonthStyleGrid::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CAknGrid::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    _AKNTRACE_FUNC_EXIT;
    }

void CAknCaleMonthStyleGrid::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    // currently not used
    SetLayoutL(ETrue,ETrue,ETrue,7, 8, TSize(21,19), 1, 1);
    SetPrimaryScrollingType(CAknGridView::EScrollFollowsItemsAndStops);
    SetSecondaryScrollingType(CAknGridView::EScrollFollowsItemsAndLoops);

    CAknGrid &aGrid = *this;

    CFormattedCellListBoxItemDrawer *itemDrawer = aGrid.ItemDrawer();
    AknListBoxLayouts::SetupStandardGrid(aGrid);

    AknListBoxLayouts::SetupGridPos(aGrid,0,0,-1,-1,22,20);


    // The rectangle needs to be a bitmap.
    // 21x19 bitmap (draw separator lines inside the bitmap)
    AknListBoxLayouts::SetupFormGfxCell(aGrid, itemDrawer, 0,
                0,0, -1,-1, 21,19,
                TPoint(0,0),TPoint(21,19));


    // needs transparency (5x5 bitmap)
    itemDrawer->FormattedCellData()->SetTransparentSubCellL(1, ETrue);
    itemDrawer->FormattedCellData()->SetNotAlwaysDrawnSubCellL(1,ETrue);
    AknListBoxLayouts::SetupFormGfxCell(aGrid, itemDrawer, 1,
                16,14, -1,-1, 5,5,
                TPoint(16,14),TPoint(21,19));

    // needs transparency (day number)
    itemDrawer->FormattedCellData()->SetTransparentSubCellL(2, ETrue);
    itemDrawer->FormattedCellData()->SetNotAlwaysDrawnSubCellL(2,ETrue);

    AknListBoxLayouts::SetupFormAntiFlickerTextCell(aGrid, itemDrawer, 2,
                 LatinBold12(), 215, 3,4,14,14,CGraphicsContext::ECenter,
                 TPoint(0,0),TPoint(21,19));

    SetSeparatorLinePosition(this, ENoLine);
    
    DisableScrolling( ETrue );
    _AKNTRACE_FUNC_EXIT;
    }

//
//
//   MinimumSize() methods for concrete listboxes
//
//

TSize MinimumSizeImpl(CEikListBox *aListBox, TBool /*aFindPossible*/)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    // this must be equal to "old" main pane lists or dialogs will break (sigh)
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );

    TSize ret = mainPane.Size();
    TInt height = 0;

    // If we have find pane, then listbox has less space.
    CAknListBoxFilterItems *filter = static_cast<CAknFilteredTextListBoxModel*>( aListBox->Model())->Filter();

    if ( filter && filter->FindBox() && filter->FindBox()->IsVisible() )
        {
        height = filter->FindBox()->Rect().Height();
        }

    ret.SetSize(ret.iWidth,ret.iHeight - height );
    return ret;
    }

EXPORT_C TSize CAknSingleStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknSingleNumberStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknSingleHeadingStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknSingleGraphicStyleListBox::MinimumSize()
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknSingleGraphicStyleListBox", __FUNCTION__, __LINE__ );
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    TRect parentrect( TPoint( 0, 0 ),TSize( mainPane.Width(), mainPane.Height() ) );
    
    // If we have find pane, then listbox has less space.
    CAknListBoxFilterItems *filter = static_cast<CAknFilteredTextListBoxModel*>( this->Model())->Filter();

    TInt height;
    // If it is popup find that is not visible, treat it like no find at all.
    if ( filter && filter->FindBox() && filter->FindBox()->IsVisible() )
        {
        //TInt bb = AknLayoutScalable_Avkon::popup_find_window().LayoutLine().Rect().Height();
        TInt findHight = filter->FindBox()->Rect().Height();
        height = parentrect.Height() - findHight;
        }
    else
        {
        height = parentrect.Height();
        } 
    
    return TSize( parentrect.Width(), height );
    }

EXPORT_C TSize CAknSingleGraphicHeadingStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknSingleNumberHeadingStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknSingleLargeStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknSingle2GraphicStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, ETrue);
    }

EXPORT_C TSize CAknDoubleStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDoubleNumberStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDoubleTimeStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDoubleLargeStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDoubleGraphicStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDouble2GraphicStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDouble2LargeStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDouble2GraphicLargeStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknDouble2GraphicLargeGraphicStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknSettingStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

EXPORT_C TSize CAknSettingNumberStyleListBox::MinimumSize()
    {
    return MinimumSizeImpl(this, EFalse);
    }

static TSize CalcPopupSize(CEikListBox *aListbox,
                           const TAknWindowLineLayout &aL,
                           const TAknLayoutScalableParameterLimits &aLimits,
                           TInt aMinItems = 1) // how to get rid of this?
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    TInt num = aListbox->Model()->NumberOfItems();
    TInt maxItems = aLimits.LastRow() + 1; // last row is a zero based index, we need num items which is 1 based
        
    TSize itemSize( PopupListItemSize(aL) );

    if (num < aMinItems) num = aMinItems;
    if (num > maxItems) num = maxItems;    
    return TSize(itemSize.iWidth, itemSize.iHeight*num);
    }

static TSize CalcPopupSize(CEikListBox *aListbox, 
                           TAknWindowLineLayout aWindowLineLayout,
                           TAknWindowLineLayout aParent,
                           TAknWindowLineLayout aGrandParent,
                           TInt aMinItems, TInt aMaxItems)
    {
    _AKNTRACE( "[%s][%d]", __FUNCTION__, __LINE__ );
    __ASSERT_DEBUG(aMinItems <= aMaxItems, Panic(EAknPanicOutOfRange));
    
    TAknLayoutRect layout = CommonLayoutRect(aWindowLineLayout, aParent, aGrandParent);
    TInt num = aListbox->Model()->NumberOfItems();

    if (num < aMinItems) num = aMinItems;
    if (num > aMaxItems) num = aMaxItems;    
    return TSize(layout.Rect().Width(), layout.Rect().Height()*num);
    }

EXPORT_C TSize CAknSinglePopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_single_pane_cp2(0),
        AknLayoutScalable_Avkon::list_single_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknSingleGraphicPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_single_graphic_pane_cp2(0),
        AknLayoutScalable_Avkon::list_single_graphic_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknSingleGraphicHeadingPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2(0),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknSingleHeadingPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_single_heading_pane_cp2(0),
        AknLayoutScalable_Avkon::list_single_heading_pane_cp2_ParamLimits());
    }


EXPORT_C TSize CAknDoublePopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_double_pane_cp2(0),
        AknLayoutScalable_Avkon::list_double_pane_cp2_ParamLimits());
    }

// deprecated 
EXPORT_C TSize CAknSinglePopupSubmenuStyleListBox::MinimumSize()
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknSinglePopupSubmenuStyleListBox", __FUNCTION__, __LINE__ );
    // most likely will never be used
    TAknLayoutRect layout = CommonLayoutRect(AKN_LAYOUT_WINDOW_list_single_popup_submenu_pane(0,0),
        AKN_LAYOUT_WINDOW_list_submenu_pane(0, 5),
        AKN_LAYOUT_WINDOW_Pop_up_windows__main_pane_as_parent__Line_2(5));
    TInt num = Model()->NumberOfItems();

    if (num < 1) num = 1;
    if (num > 2) num = 2;    
    return TSize(layout.Rect().Width(), layout.Rect().Height()*num);
    }
EXPORT_C TSize CAknDoubleLargeGraphicPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2(0),
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknDouble2PopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_double2_pane_cp2(0),
        AknLayoutScalable_Avkon::list_double2_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknSingle2GraphicPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_cp2(0),
        AknLayoutScalable_Avkon::list_single_2graphic_pane_cp2_ParamLimits());
    }

EXPORT_C TSize CAknDoubleGraphicPopupMenuStyleListBox::MinimumSize()
    {
    return CalcPopupSize(this,
        AknLayoutScalable_Avkon::list_double_graphic_pane_cp2(0),
        AknLayoutScalable_Avkon::list_double_graphic_pane_cp2_ParamLimits());
    }


EXPORT_C TSize CAknSetStyleListBox::MinimumSize()
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknSetStyleListBox", __FUNCTION__, __LINE__ );
    const TInt minItems = 2;
    const TInt maxItems = 6;
    
    TInt num = this->Model()->NumberOfItems();
    
    if (num < minItems) num = minItems;
    if (num > maxItems) num = maxItems;

    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );
    
    CEikFormattedCellListBox &aListBox = *this;
    CFormattedCellListBoxItemDrawer *itemDrawer = aListBox.ItemDrawer();

    TAknLayoutRect layout;
    if (itemDrawer->ColumnData()->IsBackgroundDrawingEnabled())
        {
        layout.LayoutRect(mainPane, AKN_LAYOUT_WINDOW_list_set_pane(num - 1));
        }
    else
        {
        layout.LayoutRect(mainPane, AKN_LAYOUT_WINDOW_list_set_trans_pane(num - 1));
        }
    
    return TSize(layout.Rect().Width(), layout.Rect().Height());
    }

EXPORT_C TSize CAknFormGraphicStyleListBox::MinimumSize()
    {
    TAknLayoutScalableParameterLimits paneLimits = AknLayoutScalable_Avkon::form_field_popup_pane_ParamLimits();
    TInt maxItems = paneLimits.LastVariety() + 1; // last variety is a zero based index, we need num items which is 1 based
    maxItems -= 1;
    TAknWindowLineLayout pane = AKN_LAYOUT_WINDOW_list_form_graphic_pane(0);
    TAknWindowLineLayout pane2 = AKN_LAYOUT_WINDOW_list_form_pane(0);
    TAknWindowLineLayout pane3 = AKN_LAYOUT_WINDOW_form_field_popup_pane(0,0);
    return CalcPopupSize(this, pane, pane2, pane3, 2, maxItems);
    }

EXPORT_C TSize CAknFormGraphicWideStyleListBox::MinimumSize()
    {
    TAknLayoutScalableParameterLimits paneLimits = AknLayoutScalable_Avkon::form_field_popup_wide_pane_ParamLimits();
    TInt maxItems = paneLimits.LastVariety() + 1; // last variety is a zero based index, we need num items which is 1 based
    maxItems -= 1;
    TAknWindowLineLayout pane = AKN_LAYOUT_WINDOW_list_form_graphic_wide_pane(0);
    TAknWindowLineLayout pane2 = AKN_LAYOUT_WINDOW_list_form_wide_pane(0,0);
    TAknWindowLineLayout pane3 = AKN_LAYOUT_WINDOW_form_field_popup_wide_pane(0,0);

    return CalcPopupSize(this, pane, pane2, pane3, 2, maxItems);
    }


EXPORT_C TSize CAknAppStyleGrid::MinimumSize()
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknAppStyleGrid", __FUNCTION__, __LINE__ );
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPane );

    TAknLayoutRect layout;
    layout.LayoutRect(mainPane, AKN_LAYOUT_WINDOW_grid_app_pane);

    return layout.Rect().Size();
    }

EXPORT_C TSize CAknPinbStyleGrid::MinimumSize()
    {
    // currently not used
    return TSize(165,145);
    }

EXPORT_C TSize CAknQdialStyleGrid::MinimumSize()
    {
    _AKNTRACE( "[%s][%s][%d]", "CAknQdialStyleGrid", __FUNCTION__, __LINE__ );
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
    TAknLayoutRect r;
    r.LayoutRect( screen, AknLayoutScalable_Avkon::application_window( 0 ) );
    // main pane varieties:
    // 1 portrait, no status pane, possibly touch pane
    // 4 landscape with both upper & lower stacon(?) panes, possibly touch pane
    TInt mainPaneVariety( Layout_Meta_Data::IsLandscapeOrientation() ? 4 : 1 );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Avkon::main_pane( mainPaneVariety ) );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Apps::main_qdial_pane() );
    r.LayoutRect( r.Rect(), AknLayoutScalable_Apps::grid_qdial_pane() );
    return r.Rect().Size();
    }


EXPORT_C TSize CAknCaleMonthStyleGrid::MinimumSize()
    {
    // currently not used
    return TSize(176,144);
    }
    
EXPORT_C void CAknCaleMonthStyleGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSelectionGridTypedef::HandlePointerEventL(aPointerEvent); 
    }    

static MAknsControlContext *LinesDefaultContext(const CEikFormattedCellListBox *aListBox)
    {
    return aListBox->ItemDrawer()->FormattedCellData()->SkinBackgroundContext();
    }

static MAknsControlContext *LinesDefaultContext(const CEikColumnListBox *aListBox)
    {
    return aListBox->ItemDrawer()->ColumnData()->SkinBackgroundContext();
    }

template<class T>
EXPORT_C AknListBoxLinesTemplate<T>::AknListBoxLinesTemplate(TInt /*aResourceId*/)
    {
    iResized = EFalse;
    }

template<class T>
EXPORT_C void AknListBoxLinesTemplate<T>::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    T::SizeChanged();
    iResized = ETrue;
    _AKNTRACE_FUNC_EXIT;
    }
    
template<class T>
EXPORT_C void AknPopupListEmpty<T>::Draw(const TRect &aRect) const
    {
    if (this->iModel->NumberOfItems() == 0)
        {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        CAknTransitionUtils::SetData( ( TInt )this->iView, &this->SystemGc() );
#endif
        this->iView->DrawEmptyList(this->Rect());
        
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
        CAknTransitionUtils::RemoveData( ( TInt )this->iView );
#endif
        }
    else
        {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
        MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal( this->iItemDrawer->Gc() );
            if ( transApi )
                {
                transApi->SetListType( MAknListBoxTfxInternal::EListBoxTypePopup );
            }
#endif //RD_UI_TRANSITION_EFFECTS_LIST

        T::Draw(aRect);
        }
    }

template<class T>
EXPORT_C void AknListBoxLinesTemplate<T>::Draw(const TRect& aRect) const
    {
    if (!iResized)
        {
        return;
        }

    CWindowGc* gc = this->iItemDrawer->Gc();

    // If a parent has a custom gc, draw listbox using that gc
    CWindowGc* replacedGc = ReplaceGcWithCustomGc(
                                    static_cast<const CEikListBox*>( this ) );

    if (this->iModel->NumberOfItems() == 0)
        {
        this->iView->DrawEmptyList(this->Rect());

        if ( replacedGc )
            {
            // Stop using the custom gc
            this->iItemDrawer->SetGc( replacedGc );
            }
        return;
        }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( gc );
    
    if ( transApi )
        {
        transApi->SetListType( MAknListBoxTfxInternal::EListBoxTypeMainPane );
        transApi->BeginRedraw( MAknListBoxTfxInternal::EListView, this->Rect() );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    if (!this->iView->RedrawDisabled())
        {
        MAknsControlContext *cc = AknsDrawUtils::ControlContext( this );
        if (!cc) cc = ::LinesDefaultContext(this);

        if (gc)
            {
            TRect clientRect;
            this->RestoreClientRectFromViewRect(clientRect);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST           
            if ( transApi )
                {
                transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
                }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
            gc->SetBrushColor(this->BackColor());
            AknsDrawUtils::BackgroundBetweenRects( AknsUtils::SkinInstance(), cc, this, *gc, clientRect, this->iView->ViewRect() );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            if ( transApi )
                {
                transApi->StopDrawing();
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
            }
        }
    if ( this->iModel->NumberOfItems() )
        {
        // finally, draw the actual list
        this->iView->Draw(&aRect);
        }
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->EndViewRedraw( aRect );
        }
#endif //RD_UI_TRANSITION_EFFECTS_LIST
    if ( replacedGc )
        {
        // Stop using the custom gc
        this->iItemDrawer->SetGc( replacedGc );
        }
    }

template<class T>
EXPORT_C TInt AknListBoxLinesTemplate<T>::CountComponentControls() const
    {
    return T::CountComponentControls();
    }

template<class T>
EXPORT_C CCoeControl* AknListBoxLinesTemplate<T>::ComponentControl(TInt aIndex) const
    {
    TInt count = T::CountComponentControls();
    if (aIndex < count) 
    {
    return T::ComponentControl(aIndex);
    } else return 0;
    }       

EXPORT_C TBool AknListBoxUtils::ListBoxLinesShown( MAknsSkinInstance *aInstance,
                                                   MAknsControlContext* /*aCc*/ )
    {  // DEPRECATED
    return AknsDrawUtils::IsListSeperatorLines( aInstance );
    }

EXPORT_C void CAknPinbStyleGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSelectionGridTypedef::HandlePointerEventL(aPointerEvent); 
    }   

EXPORT_C void CAknQdialStyleGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSelectionGridTypedef::HandlePointerEventL(aPointerEvent); 
    }
    
EXPORT_C void CAknDoubleStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDoubleStyle2ListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknDoubleStyleListBox::HandlePointerEventL(aPointerEvent); 
    }    

EXPORT_C void CAknSettingStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikSettingsListBoxTypedef::HandlePointerEventL( aPointerEvent ); 
    }    
    
EXPORT_C void CAknDoubleTimeStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknFormDoubleStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknDoubleStyleListBox::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDoubleLargeStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleLargeStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }     
    
EXPORT_C void CAknDouble2LargeStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDoubleNumberStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleNumberStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDoubleGraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSettingNumberStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikSettingsListBoxTypedef::HandlePointerEventL( aPointerEvent );
    }    
    
EXPORT_C void CAknSingleGraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleHeadingStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDouble2GraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    } 
    
EXPORT_C void CAknDoublePopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }       

EXPORT_C void CAknFormGraphicWideStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknFormGraphicStyleListBox::HandlePointerEventL(aPointerEvent); 
    }
    
EXPORT_C void CAknSinglePopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknDouble2PopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknFormDoubleGraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknDoubleGraphicStyleListBox::HandlePointerEventL(aPointerEvent); 
    }    
    
// deprecated 
EXPORT_C void CAknSinglePopupSubmenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }  
    
EXPORT_C void CAknSingleNumberHeadingStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }      
    
EXPORT_C void CAknSingleGraphicHeadingStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikColumnListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleGraphicPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }    
    
EXPORT_C void CAknSingleHeadingPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }
    
EXPORT_C void CAknSingleGraphicBtPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CAknSingleGraphicPopupMenuStyleListBox::HandlePointerEventL(aPointerEvent); 
    }
    
EXPORT_C void CAknDoubleLargeGraphicPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }
    
EXPORT_C void CAknSingleGraphicHeadingPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }     
    
EXPORT_C void CAknSingle2GraphicPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }     
    
EXPORT_C void CAknDoubleGraphicPopupMenuStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBox::HandlePointerEventL(aPointerEvent); 
    }     

EXPORT_C void CAknDouble2GraphicLargeGraphicStyleListBox::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    { 
    CEikFormattedCellListBoxTypedef::HandlePointerEventL(aPointerEvent); 
    }               

// -----------------------------------------------------------------------------
// CEikFormattedCellListBox derivatives.
// Following functions use the new listbox layout system.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// CAknDoubleGraphicStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleGraphicStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleGraphicStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleGraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer* itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );
    if ( !formattedCellData->SecondRowHidden() )
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_double_graphic_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_graphic_pane_vc( 0 ) );
        }
    else
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_single_graphic_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_graphic_pane_vc( 0 ) );
        }

    SetSeparatorLinePosition( this, EABColumn );

    if ( ShowAllRows( formattedCellData ) )
        {
        formattedCellData->SetStretchableGraphicSubCellL(
            0,
            AknLayoutScalable_Avkon::list_double_graphic_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL(
            1,
            AknLayoutScalable_Avkon::list_double_graphic_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL(
            2,
            AknLayoutScalable_Avkon::list_double_graphic_pane_t2( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_t2( 0 ) );
            
        formattedCellData->SetStretchableGraphicSubCellL(
            3,
            AknLayoutScalable_Avkon::list_double_graphic_pane_g3( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_g3( 0 ) );

        formattedCellData->SetStretchableGraphicSubCellL(
            4,
            AknLayoutScalable_Avkon::list_double_graphic_pane_g2( 1 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_g2( 1 ) );

        // New icon below g1. 
        formattedCellData->SetGraphicSubCellL(
            5,
            AknLayoutScalable_Avkon::list_double_graphic_pane_g4( 0 ) );

        // On default new cell is always drawn but this cell should NOT be drawn!
        formattedCellData->SetNotAlwaysDrawnSubCellL( 5, ETrue );
            
        // Conditional subcells must be added in priority order!
        formattedCellData->SetStretchableConditionalSubCellL(
            4,
            AknLayoutScalable_Avkon::list_double_graphic_pane_t1( 2 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_t2( 2 ), 1, 2 );

        formattedCellData->SetStretchableConditionalSubCellL(
            3,
            AknLayoutScalable_Avkon::list_double_graphic_pane_t1( 1 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_t2( 1 ), 1, 2 );
        }
    else
        {
        formattedCellData->SetStretchableGraphicSubCellL(
            0,
            AknLayoutScalable_Avkon::list_single_graphic_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL(
            1,
            AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_graphic_pane_vc_t1( 0 ) );
        }
  
    itemDrawer->SetItemMarkReverse( ETrue );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front' checkbox icon
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 3 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );
    if ( !formattedCellData->SecondRowHidden() )
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_double_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_pane_vc( 0 ) );
        }
    else
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_single_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_pane_vc( 0 ) );
        }

    SetSeparatorLinePosition( this, EAColumn );

    if ( ShowAllRows( formattedCellData ) )
        {
        // Assertion fails in CFormattedCellListBoxData::DrawFormattedSimple if 
        // this cell does not exist.
        formattedCellData->SetStretchableTextSubCellL( 0,
            AknLayoutScalable_Avkon::list_double_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_double_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 2,
            AknLayoutScalable_Avkon::list_double_pane_t2( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t2( 0 ) );
            
        formattedCellData->SetStretchableGraphicSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableGraphicSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_pane_g2( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_g2( 0 ) );

        // Conditional subcells must be added in priority order!
        formattedCellData->SetStretchableConditionalSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_pane_t1( 2 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t2( 2 ), 1, 2 );

        formattedCellData->SetStretchableConditionalSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_pane_t1( 1 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t2( 1 ), 1, 2 );
        }
    else
        {
        // Assertion fails in CFormattedCellListBoxData::DrawFormattedSimple if 
        // this cell does not exist.
        formattedCellData->SetStretchableTextSubCellL( 0,
            AknLayoutScalable_Avkon::list_single_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_single_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_pane_vc_t1( 0 ) );
        }        

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleNumberStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleNumberStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleNumberStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleNumberStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );
    if ( !formattedCellData->SecondRowHidden() )
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_double_number_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_number_pane_vc( 0 ) );
        }
    else
        {
        SetupStretchableListL( this,
                              AknLayoutScalable_Avkon::list_single_number_pane( 0 ),
                              AknLayoutScalable_Avkon::list_double_number_pane_vc( 0 ) );
        }

    SetSeparatorLinePosition( this, EABColumn );
    
    if ( ShowAllRows( formattedCellData ) )
        {
        formattedCellData->SetStretchableTextSubCellL( 0,
            AknLayoutScalable_Avkon::list_double_number_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_double_number_pane_t2( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t2( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 2,
            AknLayoutScalable_Avkon::list_double_number_pane_t3( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t3( 0 ) );
            
        formattedCellData->SetStretchableGraphicSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_number_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableGraphicSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_number_pane_g2( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_g2( 0 ) );

        // Conditional subcells must be added in priority order!
        formattedCellData->SetStretchableConditionalSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_number_pane_t2( 2 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t3( 2 ), 1, 2 );

        formattedCellData->SetStretchableConditionalSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_number_pane_t2( 1 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t3( 1 ), 1, 2 );
        }
    else
        {
        formattedCellData->SetStretchableTextSubCellL( 0,
            AknLayoutScalable_Avkon::list_single_number_pane_t2( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_single_number_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_number_pane_vc_t2( 0 ) );
        }

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleTimeStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleTimeStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleTimeStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleTimeStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* d( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double_time_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double_time_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EBCColumn );
    
    d->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_time_pane_t4( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t4( 0 ) );

    d->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_time_pane_t3( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t3( 0 ) );

    d->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_time_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t1( 4 ) );
        
    d->SetStretchableTextSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_time_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t2( 0 ) );

    d->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_time_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_g1( 0 ) );

    d->SetStretchableGraphicSubCellL( 5,
        AknLayoutScalable_Avkon::list_double_time_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetStretchableConditionalSubCellL( 5,
        AknLayoutScalable_Avkon::list_double_time_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t2( 2 ), 2, 3 );

    d->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_time_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double_time_pane_vc_t2( 1 ), 2, 3 );
    _AKNTRACE_FUNC_EXIT;
    }
    
// -----------------------------------------------------------------------------
// CAknDoubleLargeStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleLargeStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();

    if ( !ItemDrawer()->FormattedCellData()->SecondRowHidden() )
        {
        TRAP_IGNORE( SetupStretchableListL( this,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc( 0 ) ) );
        }
    else
        {
        TRAP_IGNORE( SetupStretchableListL( this,
            AknLayoutScalable_Avkon::list_single_large_graphic_pane( 0, 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc( 0 ) ) );
        }
                                                
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknDoubleLargeStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
void CAknDoubleLargeStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetSeparatorLinePosition( this, EBCColumn );
    
    if ( ShowAllRows( formattedCellData ) )
        {
        formattedCellData->SetStretchableGraphicSubCellL( 0,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_t1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 2,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_t2( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_t2( 0 ) );
            
        formattedCellData->SetStretchableGraphicSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_g2( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_g2( 1 ) );

        formattedCellData->SetStretchableGraphicSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_g3( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_g3( 0 ) );

        // Following code sets additional information icon cell. This is specified 
        // in the LAF data but there's no CR to enable it so the code will be 
        // commented out untill there's an official request.
        /*formattedCellData->SetStretchableGraphicSubCellL( 5,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_g4( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_g4( 0 ) );*/

        // Conditional subcells must be added in priority order!
        formattedCellData->SetStretchableConditionalSubCellL( 4,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1( 2 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_t2( 2 ), 1, 2 );

        formattedCellData->SetStretchableConditionalSubCellL( 3,
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1( 1 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_t2( 1 ), 1, 2 );
        }
    else
        {
        formattedCellData->SetStretchableGraphicSubCellL( 0,
            AknLayoutScalable_Avkon::list_single_large_graphic_pane_g1( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_g1( 0 ) );

        formattedCellData->SetStretchableTextSubCellL( 1,
            AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ),
            AknLayoutScalable_Avkon::list_double_large_graphic_pane_vc_t1( 0 ) );
        }
        
    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;
    }
    
// -----------------------------------------------------------------------------
// CAknDoubleStyle2ListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleStyle2ListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknDoubleStyle2ListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleStyle2ListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double2_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double2_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EAColumn );
    
    // Assertion fails in CFormattedCellListBoxData::DrawFormattedSimple if this
    // cell does not exist.
    formattedCellData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_t1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_t1( 0 ) );

    // This cell is never drawn if the list is stretched but it needs to be
    // created because list item's format string contains it.
    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_t1( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_t1( 2 ), 1, 1 );

    formattedCellData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double2_pane_vc_t1( 1 ), 1, 1 );

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2GraphicStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDouble2GraphicStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2GraphicStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDouble2GraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double2_graphic_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double2_graphic_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EABColumn );
    
    formattedCellData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_t1( 0 ) );

    // This cell is never drawn if the list is stretched but it needs to be
    // created because list item's format string contains it.
    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_t1( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_g2( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_g3( 0 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_t1( 2 ), 1, 1 );

    formattedCellData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_graphic_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double2_graphic_pane_vc_t1( 1 ), 1, 1 );

    itemDrawer->SetItemMarkReverse( ETrue );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front' checkbox
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 3 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknDouble2LargeStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDouble2LargeStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2LargeStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDouble2LargeStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double2_large_graphic_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EBCColumn );
    
    formattedCellData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_t1( 0 ) );

    // This cell is never drawn if the list is stretched but it needs to be
    // created because list item's format string contains it.
    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_t1( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_g2( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_g3( 0 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_t1( 2 ), 1, 1 );

    formattedCellData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double2_large_graphic_pane_vc_t1( 1 ), 1, 1 );

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknDouble2GraphicLargeGraphicStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDouble2GraphicLargeGraphicStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2GraphicLargeGraphicStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDouble2GraphicLargeGraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane( 0 ),
                          AknLayoutScalable_Avkon::list_single_large_graphic_pane( 0, 0 ) );

    
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         formattedCellData->StretchingEnabled() )
        {
        SetSeparatorLinePosition( this, EBCColumn );
        }
    else
        {
        SetSeparatorLinePosition( this, EABColumn );
        }

    // selection indication
    formattedCellData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g4( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g4_cp2() );
        
    // thumbnail image
    formattedCellData->SetStretchableGraphicSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g1( 0 ) );
        
    // item text 1st line
    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ) );
        
    // item text 2nd line (this is never drawn in stretched layout)
    formattedCellData->SetStretchableTextSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ) );
        
    // outer additional icon
    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g2( 0 ) );
        
    // inner additional icon
    formattedCellData->SetStretchableGraphicSubCellL( 5,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g3( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g3( 0 ) );
        
    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 5,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 2 ), 2, 2 );
        
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 1 ), 2, 2 );
    
    itemDrawer->SetItemMarkPosition( 0 );
    itemDrawer->SetItemMarkReplacement( KFirstCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknDouble2GraphicLargeStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDouble2GraphicLargeStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2GraphicLargeStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDouble2GraphicLargeStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane( 0 ),
                          AknLayoutScalable_Avkon::list_single_large_graphic_pane( 0, 0 ) );
    
    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         formattedCellData->StretchingEnabled() )
        {
        SetSeparatorLinePosition( this, EBCColumn );
        }
    else
        {
        SetSeparatorLinePosition( this, EABColumn );
        }

    // selection indication
    formattedCellData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g4( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g4_cp2() );
        
    // thumbnail image
    formattedCellData->SetStretchableGraphicSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g1( 0 ) );
        
    // item text 1st line
    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ) );
        
    // item text 2nd line (this is never drawn in stretched layout)
    formattedCellData->SetStretchableTextSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ) );
        
    // outer additional icon
    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g2( 0 ) );
        
    // inner additional icon
    formattedCellData->SetStretchableGraphicSubCellL( 5,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_g3( 0 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_g3( 0 ) );
        
    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 5,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 2 ), 2, 2 );
        
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double2_graphic_large_graphic_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 1 ), 2, 2 );
    
    itemDrawer->SetItemMarkPosition( 0 );
    itemDrawer->SetItemMarkReplacement( KFirstCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknSettingStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSettingStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNSETTINGSLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSettingStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSettingStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_setting_pane( 0 ),
                          AknLayoutScalable_Avkon::list_setting_pane_vc( 0 ),
                          EFalse );

    SetSeparatorLinePosition( this, EAColumn );
    
    // Assertion fails in CFormattedCellListBoxData::DrawFormattedSimple if this
    // cell does not exist.
    formattedCellData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_setting_number_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_t1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_setting_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_setting_pane_vc_t1( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::set_value_pane_cp( 0 ),
        AknLayoutScalable_Avkon::set_value_pane_cp_vc( 0 ) );
        
    formattedCellData->SetStretchableTextSubCellL( 3,
        TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane_cp( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() ),
        TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane_cp_vc( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() ) );

    formattedCellData->SetStretchableTextSubCellL( 4,
        AknLayoutScalable_Avkon::list_setting_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_setting_pane_vc_t2( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 5,
        AknLayoutScalable_Avkon::list_setting_pane_t4( 3 ),
        AknLayoutScalable_Avkon::list_single_pane_t1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 6,
        AknLayoutScalable_Avkon::list_setting_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_setting_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 7,
        AknLayoutScalable_Avkon::list_setting_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_setting_pane_vc_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 7,
        AknLayoutScalable_Avkon::list_setting_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_pane_t1( 2 ), 1, 5 );

    formattedCellData->SetStretchableConditionalSubCellL( 6,
        AknLayoutScalable_Avkon::list_setting_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_pane_t1( 1 ), 1, 5 );

    // text colors
    CFormattedCellListBoxData::TColors colors;
    SetESSTextColor( colors, EAknsCIQsnTextColorsCG7 );
    SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG10 );
    // support for non skinned case. Bg values are note used in skinned draw.
    colors.iBack = AKN_LAF_COLOR( 0 );
    colors.iHighlightedBack = AKN_LAF_COLOR( 244 );
    
    formattedCellData->SetSubCellColorsL( 0, colors );
    formattedCellData->SetSubCellColorsL( 1, colors );
    formattedCellData->SetSubCellColorsL( 5, colors );

    // color of valuetext
    SetESSTextColor( colors, EAknsCIQsnTextColorsCG12 );
    SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG12 );
    // support for non skinned case. Bg values are note used in skinned draw.
    colors.iBack = AKN_LAF_COLOR( 244 ); // light purplish blue
    colors.iHighlightedBack = AKN_LAF_COLOR( 243 ); // dark blue
    formattedCellData->SetSubCellColorsL( 3, colors );

    // there's no skin id for mandatory setting indication color
    colors.iText = AKN_LAF_COLOR( 20 ); // red
    colors.iHighlightedText = AKN_LAF_COLOR( 20 );
    colors.iBack = AKN_LAF_COLOR( 0 ); // white
    colors.iHighlightedBack = AKN_LAF_COLOR( 244 );
    formattedCellData->SetSubCellColorsL( 4, colors );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknSettingNumberStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSettingNumberStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNSETTINGSLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() ); 
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSettingNumberStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSettingNumberStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_setting_number_pane( 0 ),
                          AknLayoutScalable_Avkon::list_setting_number_pane_vc( 0 ),
                          EFalse );

    SetSeparatorLinePosition( this, EABColumn );
    
    formattedCellData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_setting_number_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_t1( 0 ) );
        
    formattedCellData->SetNumberCellL( 0, ETrue ); // This will enable locale-specific number conversion

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_setting_number_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_vc_t2( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::set_value_pane( 0 ),
        AknLayoutScalable_Avkon::set_value_pane_vc( 0 ) );

    TAknTextComponentLayout normal = TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() );
    TAknTextComponentLayout stretched = TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane_vc( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() );

    formattedCellData->SetStretchableTextSubCellL( 3,
        TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() ),
        TAknWindowComponentLayout::ComposeText( AknLayoutScalable_Avkon::set_value_pane_vc( 0 ), AknLayoutScalable_Avkon::set_value_pane_t1() ) );

    formattedCellData->SetStretchableTextSubCellL( 4,
        AknLayoutScalable_Avkon::list_setting_number_pane_t3( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_vc_t3( 0 ) );
        
    formattedCellData->SetStretchableTextSubCellL( 5,
        AknLayoutScalable_Avkon::list_setting_number_pane_t5( 3 ),
        AknLayoutScalable_Avkon::list_single_number_pane_t1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 6,
        AknLayoutScalable_Avkon::list_setting_number_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 7,
        AknLayoutScalable_Avkon::list_setting_number_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_setting_number_pane_vc_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 7,
        AknLayoutScalable_Avkon::list_setting_number_pane_t2( 2 ),
        AknLayoutScalable_Avkon::list_single_number_pane_t1( 2 ), 1, 5 );

    formattedCellData->SetStretchableConditionalSubCellL( 6,
        AknLayoutScalable_Avkon::list_setting_number_pane_t2( 1 ),
        AknLayoutScalable_Avkon::list_single_number_pane_t1( 1 ), 1, 5 );


    // text colors
    CFormattedCellListBoxData::TColors colors;
    SetESSTextColor( colors, EAknsCIQsnTextColorsCG7 );
    SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG10 );
    // support for non skinned case. Bg values are note used in skinned draw.
    colors.iBack = AKN_LAF_COLOR( 0 );
    colors.iHighlightedBack = AKN_LAF_COLOR( 244 );
    
    formattedCellData->SetSubCellColorsL( 0, colors );
    formattedCellData->SetSubCellColorsL( 1, colors );
    formattedCellData->SetSubCellColorsL( 5, colors );

    // color of valuetext
    SetESSTextColor( colors, EAknsCIQsnTextColorsCG12 );
    SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG12 );
    // support for non skinned case. Bg values are note used in skinned draw.
    colors.iBack = AKN_LAF_COLOR( 244 ); // light purplish blue
    colors.iHighlightedBack = AKN_LAF_COLOR( 243 ); // dark blue
    formattedCellData->SetSubCellColorsL( 3, colors );

    // there's no skin id for mandatory setting indication color
    colors.iText = AKN_LAF_COLOR( 20 ); // red
    colors.iHighlightedText = AKN_LAF_COLOR( 20 );
    colors.iBack = AKN_LAF_COLOR( 0 ); // white
    colors.iHighlightedBack = AKN_LAF_COLOR( 244 );
    formattedCellData->SetSubCellColorsL( 4, colors );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknFormDoubleStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFormDoubleStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );

    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknFormDoubleStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknFormDoubleStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double_heading_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double_heading_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EAColumn );
    
    // Assertion fails in CFormattedCellListBoxData::DrawFormattedSimple if this
    // cell does not exist.
    formattedCellData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_t1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_t1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_heading_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_t2( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_heading_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_heading_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_heading_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_t2( 2 ), 1, 2 );

    formattedCellData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_heading_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double_heading_pane_vc_t2( 1 ), 1, 2 );

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknFormDoubleGraphicStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknFormDoubleGraphicStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNFORMATTEDLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );

    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknFormDoubleGraphicStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknFormDoubleGraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_double_graphic_heading_pane( 0 ),
                          AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc( 0 ) );

    SetSeparatorLinePosition( this, EABColumn );
    
    formattedCellData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_g1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_t1( 0 ) );

    formattedCellData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_t2( 0 ) );
        
    formattedCellData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_g2( 0 ) );

    formattedCellData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_g3( 0 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_t2( 2 ), 1, 2 );

    formattedCellData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_double_graphic_heading_pane_vc_t2( 1 ), 1, 2 );

    itemDrawer->SetItemMarkReverse( ETrue );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front' checkbox
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 3 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CEikFormattedCellListBox derived popup listboxes.
// Following functions use the new listbox layout system.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// CAknDoubleLargeGraphicPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleLargeGraphicPopupMenuStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDoubleLargeGraphicPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleLargeGraphicPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData( itemDrawer->FormattedCellData() );

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_double_large_graphic_pane_cp2( 0 ) );

    formattedCellData->SetGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_g1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_g2_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_g3_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1_cp2( 2 ).LayoutLine(), 1 );

    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_large_graphic_pane_t1_cp2( 1 ).LayoutLine(), 1 );

    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDoublePopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoublePopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDoublePopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoublePopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_double_pane_cp2( 0 ) );

    formattedCellData->SetTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_pane_g1_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_pane_g2_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_pane_t1_cp2( 2 ).LayoutLine(), 0 );

    formattedCellData->SetConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_pane_t1_cp2( 1 ).LayoutLine(), 0 );

    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2PopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDouble2PopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDouble2PopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDouble2PopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_double2_pane_cp2( 0 ) );

    formattedCellData->SetTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_double2_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double2_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_pane_g1_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_pane_g2_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double2_pane_t1_cp2( 2 ).LayoutLine(), 0 );

    formattedCellData->SetConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_double2_pane_t1_cp2( 1 ).LayoutLine(), 0 );

    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDoubleGraphicPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknDoubleGraphicPopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknDoubleGraphicPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknDoubleGraphicPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_double_graphic_pane_cp2( 0 ) );

    formattedCellData->SetGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_double_graphic_pane_g1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_double_graphic_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_double_graphic_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_graphic_pane_g3_cp2().LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_graphic_pane_g2_cp2( 1 ).LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_double_graphic_pane_t1_cp2( 2 ).LayoutLine(), 1 );

    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_double_graphic_pane_t1_cp2( 1 ).LayoutLine(), 1 );

    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleGraphicHeadingPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleGraphicHeadingPopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleGraphicHeadingPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleGraphicHeadingPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_single_graphic_heading_pane_cp2( 0 ) );

    formattedCellData->SetGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g4_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g5_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1_cp2( 2 ).LayoutLine(), 2 );

    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1_cp2( 1 ).LayoutLine(), 2 );

    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSinglePopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSinglePopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSinglePopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSinglePopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_single_pane_cp2( 0 ) );

    formattedCellData->SetTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_pane_g1_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_pane_g2_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_pane_t1_cp2( 2 ).LayoutLine(), 0 );

    formattedCellData->SetConditionalSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_pane_t1_cp2( 1 ).LayoutLine(), 0 );

    itemDrawer->SetItemMarkPosition( 1 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleGraphicPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleGraphicPopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleGraphicPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleGraphicPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_single_graphic_pane_cp2( 0 ) );

    formattedCellData->SetGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_graphic_pane_g1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_graphic_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_graphic_pane_g2_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_pane_g3_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_pane_t1_cp2( 2 ).LayoutLine(), 1 );

    formattedCellData->SetConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_graphic_pane_t1_cp2( 1 ).LayoutLine(), 1 );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front checkbox'
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 2 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
        
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleHeadingPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleHeadingPopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleHeadingPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleHeadingPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_single_heading_pane_cp2( 0 ) );

    formattedCellData->SetTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_heading_pane_t2_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_heading_pane_g1_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_heading_pane_g2_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1_cp2( 2 ).LayoutLine(), 1 );

    formattedCellData->SetConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1_cp2( 1 ).LayoutLine(), 1 );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement );  // should not colorskin 'front checkbox'
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 2 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
        
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingle2GraphicPopupMenuStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingle2GraphicPopupMenuStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    TRAP_IGNORE( SizeChangedL() );
    CEikFormattedCellListBox::SizeChanged();
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknSingle2GraphicPopupMenuStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingle2GraphicPopupMenuStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* formattedCellData = itemDrawer->FormattedCellData();

    SetupCommonPopupListL( this, AknLayoutScalable_Avkon::list_single_2graphic_pane_cp2( 0 ) );

    formattedCellData->SetGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_g4_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_g1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_t1_cp2( 0 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_g2_cp2( 1 ).LayoutLine() );

    formattedCellData->SetGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_g3_cp2().LayoutLine() );

    // Conditional subcells must be added in priority order!
    formattedCellData->SetConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_t1_cp2( 2 ).LayoutLine(), 2 );

    formattedCellData->SetConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_2graphic_pane_t1_cp2( 1 ).LayoutLine(), 2 );

    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    itemDrawer->SetItemMarkReverse( ETrue );

    SetESSHighlightedTextColor( itemDrawer );
    SetESSTextColor( itemDrawer, EAknsCIQsnTextColorsCG6 );
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CEikColumnListBox derivatives.
// Following functions use the new listbox layout system.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// CAknSingleHeadingStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleHeadingStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleHeadingStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleHeadingStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* columnData( itemDrawer->ColumnData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_single_heading_pane( 0 ),
                          AknLayoutScalable_Avkon::list_single_heading_pane_vc( 0 ) );

    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         columnData->StretchingEnabled() )
        {
        SetSeparatorLinePosition( this, EBCColumnStretched );
        }
    else
        {
        SetSeparatorLinePosition( this, EBCColumn );
        }
    
    columnData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_heading_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_vc_t2( 0 ) );

    columnData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_vc_t1( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_heading_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_vc_g1( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_heading_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    columnData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_vc_t1( 2 ), 1, 1 );

    columnData->SetStretchableConditionalSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_heading_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_heading_pane_vc_t1( 1 ), 1, 1 );

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 2 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknSingleNumberHeadingStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleNumberHeadingStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleNumberHeadingStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleNumberHeadingStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* columnData( itemDrawer->ColumnData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_single_number_heading_pane( 0 ),
                          AknLayoutScalable_Avkon::list_single_number_heading_pane_vc( 0 ) );

    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         columnData->StretchingEnabled() )
        {
        SetSeparatorLinePosition( this, EBCColumnStretched );
        }
    else
        {
        SetSeparatorLinePosition( this, EBCColumn );
        }
    
    columnData->SetStretchableTextSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_t3( 0 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_t3( 0 ) );

    columnData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_t2( 0 ) );

    columnData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_t1( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_g1( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_g2( 0 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    columnData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_t1( 2 ), 2, 2 );

    columnData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_number_heading_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_number_heading_pane_vc_t1( 1 ), 2, 2 );

    itemDrawer->SetItemMarkReverse( ETrue );
    itemDrawer->SetItemMarkPosition( 3 );
    itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
    _AKNTRACE_FUNC_EXIT;    
    }
    
// -----------------------------------------------------------------------------
// CAknSingleGraphicHeadingStyleListBox::SizeChanged
// -----------------------------------------------------------------------------
//
EXPORT_C void CAknSingleGraphicHeadingStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// -----------------------------------------------------------------------------
// CAknSingleGraphicHeadingStyleListBox::SizeChangedL
// -----------------------------------------------------------------------------
//
void CAknSingleGraphicHeadingStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* columnData( itemDrawer->ColumnData() );

    SetupStretchableListL( this,
                          AknLayoutScalable_Avkon::list_single_graphic_heading_pane( 0 ),
                          AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc( 0 ) );

    if ( Layout_Meta_Data::IsLandscapeOrientation() &&
         Layout_Meta_Data::IsListStretchingEnabled() &&
         columnData->StretchingEnabled() )
        {
        SetSeparatorLinePosition( this, EBCColumnStretched );
        }
    else
        {
        SetSeparatorLinePosition( this, EBCColumn );
        }
    
    columnData->SetStretchableGraphicSubCellL( 0,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g1( 0 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_g1( 0 ) );

    columnData->SetStretchableTextSubCellL( 1,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t2( 0 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_t2( 0 ) );

    columnData->SetStretchableTextSubCellL( 2,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1( 0 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_t1( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g4( 0 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_g4( 0 ) );

    columnData->SetStretchableGraphicSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g5( 0 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_g5( 0 ) );

    // Conditional subcells must be added in priority order!
    columnData->SetStretchableConditionalSubCellL( 4,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1( 2 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_t1( 2 ), 2, 2 );

    columnData->SetStretchableConditionalSubCellL( 3,
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_t1( 1 ),
        AknLayoutScalable_Avkon::list_single_graphic_heading_pane_vc_t1( 1 ), 2, 2 );

    itemDrawer->SetItemMarkReverse( ETrue );

    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front checkbox'
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 3 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
    _AKNTRACE_FUNC_EXIT;    
    }


///---------------------------------------------------------------------------------------------------------------------
EXPORT_C void CAknSingle2GraphicStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// a java list
// list item string format: "0\t1\tTextLabel\t2\t3"
// where 0,1,2,3 are index to the icon array 

void CAknSingle2GraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* d( itemDrawer->ColumnData() );

    SetupListL( this, AknLayoutScalable_Avkon::list_single_2graphic_pane( 0 ) );

    SetSeparatorLinePosition( this, EABColumn );

    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_single_2graphic_pane_g4( 0 ) );
    d->SetGraphicSubCellL( 1, AknLayoutScalable_Avkon::list_single_2graphic_pane_g1( 0 ) );
    d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 0 ) );
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_2graphic_pane_g2( 0 ) );
    d->SetGraphicSubCellL( 4, AknLayoutScalable_Avkon::list_single_2graphic_pane_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetConditionalSubCellL( 4, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 2 ), 2 );
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 1 ), 2 );
    
    
    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front checkbox'
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 3 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        }
    itemDrawer->SetItemMarkReverse(ETrue);
    _AKNTRACE_FUNC_EXIT;    
    }


EXPORT_C void CAknSingleGraphicStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// list item string format: "0\tTextLabel\t1\t2"
// where 0,1,2 are index to the icon array 
void CAknSingleGraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* d( itemDrawer->ColumnData() );
    SetupListL( this, AknLayoutScalable_Avkon::list_single_graphic_pane( 0 ) );
    SetSeparatorLinePosition( this, EABColumn );

    TAknTextComponentLayout textLayout = AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 0 );

    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_single_graphic_pane_g1( 0 ) );
    d->SetTextSubCellL( 1, textLayout );

    // This is needed in order to retain compatibility with some applications. Without this call
    // the list items are not visible due to incorrect baseline position.
    d->SetColumnBaselinePosL(1, AknLayoutUtils::CorrectBaseline(itemDrawer->ItemCellSize().iHeight,
                                                                d->ColumnBaselinePos(1),
                                                                textLayout.Font()));

    d->SetGraphicSubCellL( 2, AknLayoutScalable_Avkon::list_single_graphic_pane_g2( 0 ) );
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_graphic_pane_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 2 ), 1 );
    d->SetConditionalSubCellL( 2, AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 1 ), 1 );



    if ( iListBoxFlags & EAknListBoxFlagsMultiselectionCheck )
        {
        itemDrawer->SetItemMarkPosition( 0 );
        itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // should not colorskin 'front checkbox'
        itemDrawer->SetItemMarkReverse( ETrue );
        }
    else
        {
        itemDrawer->SetItemMarkPosition( 2 );
        itemDrawer->SetItemMarkReplacement( KFirstMovingCSIconReplacement );
        itemDrawer->SetItemMarkReverse( ETrue );
        }
    _AKNTRACE_FUNC_EXIT;    
    }


EXPORT_C void CAknSingleLargeStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );

    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// list item string format: "1\tTextLabel\t0\t0"
void CAknSingleLargeStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* d( itemDrawer->ColumnData() );
    SetupListL( this, AknLayoutScalable_Avkon::list_single_large_graphic_pane( 0, 0 ) );  // TODO - check if different varieties should be used
    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_single_large_graphic_pane_g1( 0 ) );
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 0 ) );
    d->SetGraphicSubCellL( 2, AknLayoutScalable_Avkon::list_single_large_graphic_pane_g2( 0 ) );
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_large_graphic_pane_g3( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 2 ), 1 );
    d->SetConditionalSubCellL( 2, AknLayoutScalable_Avkon::list_single_large_graphic_pane_t1( 1 ), 1 );


    itemDrawer->SetItemMarkPosition(2);
    itemDrawer->SetItemMarkReplacement(KFirstMovingCSIconReplacement);
    itemDrawer->SetItemMarkReverse(ETrue);

    SetSeparatorLinePosition(this, EBCColumn);
    _AKNTRACE_FUNC_EXIT;    
    }

EXPORT_C void CAknSingleNumberStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );

    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// list item string format: "2\tTextLabel\t0\t1"
// where 0 and 1 are indexes to icon array
void CAknSingleNumberStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* d( itemDrawer->ColumnData() );
    SetupListL( this, AknLayoutScalable_Avkon::list_single_number_pane( 0 ) );
    SetSeparatorLinePosition( this, EABColumn );

    d->SetTextSubCellL( 0, AknLayoutScalable_Avkon::list_single_number_pane_t2( 0 ) );
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_single_number_pane_t1( 0 ) );
    d->SetGraphicSubCellL( 2, AknLayoutScalable_Avkon::list_single_number_pane_g1( 0 ) );
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_number_pane_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_number_pane_t1( 2 ), 1 );
    d->SetConditionalSubCellL( 2, AknLayoutScalable_Avkon::list_single_number_pane_t1( 1 ), 1 );

    itemDrawer->SetItemMarkPosition(2);
    itemDrawer->SetItemMarkReplacement(KFirstMovingCSIconReplacement);
    itemDrawer->SetItemMarkReverse(ETrue);
    _AKNTRACE_FUNC_EXIT;    
    }


EXPORT_C void CAknSingleStyleListBox::SizeChanged() 
    {
    _AKNTRACE_FUNC_ENTER;
    AKNCOLUMNLISTBOX::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );

    SetupScrollbarLayout( this, iSBFrame );
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;    
    }

// list item string format: "\tTextLabel\t0\t1"
void CAknSingleStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CColumnListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CColumnListBoxData* d( itemDrawer->ColumnData() );
    SetupListL( this, AknLayoutScalable_Avkon::list_single_pane( 0 ) );
    SetSeparatorLinePosition( this, EAColumn );

    // A-column exists, but there is no layout for it.
    // it is never drawn
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_single_pane_t1( 0 ) );
    d->SetGraphicSubCellL( 2, AknLayoutScalable_Avkon::list_single_pane_g1( 0 ) );
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_pane_g2( 0 ) );

    // Conditional subcells must be added in priority order!
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_pane_t1( 2 ), 1 );
    d->SetConditionalSubCellL( 2, AknLayoutScalable_Avkon::list_single_pane_t1( 1 ), 1 );

    itemDrawer->SetItemMarkPosition(2);
    itemDrawer->SetItemMarkReplacement(KFirstMovingCSIconReplacement);
    itemDrawer->SetItemMarkReverse(ETrue);
    _AKNTRACE_FUNC_EXIT;    
    }
 
 
EXPORT_C void CAknFormGraphicStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    TBool redrawDisabled = iView->RedrawDisabled();
    iView->SetDisableRedraw( ETrue );
    TRAP_IGNORE( SizeChangedL() );
    CEikFormattedCellListBox::SizeChanged();
    iView->SetDisableRedraw( redrawDisabled );
    _AKNTRACE_FUNC_EXIT;    
    }

//  * list item string format: "1\tShortLabel"
//  * list item string format: "\t\tLongLabel"
void CAknFormGraphicStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* d( itemDrawer->FormattedCellData() );
    
    // setuplist won't work with this, since this is not a mainpane list
    SetBorder(TGulBorder::ENone);
    d->ResetSLSubCellArray();
    
    TAknLayoutRect lr;
    lr.LayoutRect( TRect( Rect().Size() ),
                   AknLayoutScalable_Avkon::list_form_graphic_pane(0) );
    TRect itemRect( lr.Rect() );
    SetVerticalMargin( itemRect.iTl.iY );
    SetHorizontalMargin( itemRect.iTl.iX );
    iView->SetItemHeight( itemRect.Height() );
    itemDrawer->SetItemCellSize( itemRect.Size() );


    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_form_graphic_pane_g1() );
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_form_graphic_pane_t1( 0 ) );
    d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_form_graphic_pane_t1( 1 ) );
    
    itemDrawer->SetItemMarkPosition(0);
    itemDrawer->SetItemMarkReplacement(KFirstCSIconReplacement);
    itemDrawer->SetItemMarkReverse(ETrue);

    // TODO: check if this could be reduced a bit
    CFormattedCellListBoxData::TColors colors;
    /* colors can be hardcoded here, because
    *  1. They are not available in layouts
    *  2. extended color skinning can be used to override hardcoded values
    */
    colors.iText = AKN_LAF_COLOR(215);            // black
    colors.iBack = AKN_LAF_COLOR(0);              // white
    colors.iHighlightedText = AKN_LAF_COLOR(0);   // white
    colors.iHighlightedBack = AKN_LAF_COLOR(243);  // blue

    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG10 );
        SetESSTextColor( colors, EAknsCIQsnTextColorsCG8 );
        }
    d->SetSubCellColorsL(1, colors);
    d->SetSubCellColorsL(2, colors);
    _AKNTRACE_FUNC_EXIT;    
    }
 
EXPORT_C void CAknFormGraphicWideStyleListBox::SizeChanged()
        {
    _AKNTRACE_FUNC_ENTER;
        TBool redrawDisabled = iView->RedrawDisabled();
        iView->SetDisableRedraw( ETrue );
        TRAP_IGNORE( SizeChangedL() );
        CEikFormattedCellListBox::SizeChanged();
        iView->SetDisableRedraw( redrawDisabled );
    _AKNTRACE_FUNC_EXIT;    
        }

void CAknFormGraphicWideStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* d( itemDrawer->FormattedCellData() );
    
    // setuplist won't work with this, since this is not a mainpane list
    SetBorder(TGulBorder::ENone);
    d->ResetSLSubCellArray();
    
    TAknLayoutRect lr;
    lr.LayoutRect( TRect( Rect().Size() ),
                   AknLayoutScalable_Avkon::list_form_graphic_pane_cp(0) );  // this does not seem to exist in LAF !
    TRect itemRect( lr.Rect() );
    SetVerticalMargin( itemRect.iTl.iY );
    SetHorizontalMargin( itemRect.iTl.iX );
    iView->SetItemHeight( itemRect.Height() );
    itemDrawer->SetItemCellSize( itemRect.Size() );

    // these are borrowed from other form
    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_form_graphic_pane_g1() );
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_form_graphic_pane_t1( 0 ) );
    d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_form_graphic_pane_t1( 1 ) );
    
    itemDrawer->SetItemMarkPosition(0);
    itemDrawer->SetItemMarkReplacement(KFirstCSIconReplacement);
    itemDrawer->SetItemMarkReverse(ETrue);

    // TODO: check if this could be reduced a bit
    CFormattedCellListBoxData::TColors colors;
    /* colors can be hardcoded here, because
    *  1. They are not available in layouts
    *  2. extended color skinning can be used to override hardcoded values
    */
    colors.iText = AKN_LAF_COLOR(215);            // black
    colors.iBack = AKN_LAF_COLOR(0);              // white
    colors.iHighlightedText = AKN_LAF_COLOR(0);   // white
    colors.iHighlightedBack = AKN_LAF_COLOR(243);  // blue
    
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG10 );
        SetESSTextColor( colors, EAknsCIQsnTextColorsCG8 );
        }
    d->SetSubCellColorsL(1, colors);
    d->SetSubCellColorsL(2, colors);
    _AKNTRACE_FUNC_EXIT;    
    }

EXPORT_C void CAknSetStyleListBox::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    CEikFormattedCellListBox::SizeChanged();
    TRAP_IGNORE( SizeChangedL() );
    _AKNTRACE_FUNC_EXIT;    
    }


//  * list item string format: "1\tShortLabel"
//  * list item string format: "\t\tLongLabel"

void CAknSetStyleListBox::SizeChangedL()
    {
    _AKNTRACE_FUNC_ENTER;
    CFormattedCellListBoxItemDrawer *itemDrawer( ItemDrawer() );
    CFormattedCellListBoxData* d( itemDrawer->FormattedCellData() );

    // setuplist won't work with this, since this is not a mainpane list
    SetBorder(TGulBorder::ENone);
    d->ResetSLSubCellArray();
    
    TAknLayoutRect lr;
    lr.LayoutRect( TRect( Rect().Size() ),
                   AknLayoutScalable_Avkon::list_set_graphic_pane_copy1( 0 ) );
    TRect itemRect( lr.Rect() );
    SetVerticalMargin( itemRect.iTl.iY );
    SetHorizontalMargin( itemRect.iTl.iX );
    SetItemHeightL( itemRect.Height() );
    itemDrawer->SetItemCellSize( itemRect.Size() );
    
    d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_set_graphic_pane_g1_copy1( 0 ) );
    d->SetTextSubCellL( 1, AknLayoutScalable_Avkon::list_set_graphic_pane_t1_copy1( 0 ) );
    // long label. No layout exist, but probably not used.
    d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_set_graphic_pane_t1_copy1( 0 ) );
    // protected setting indication. Probably not used.
    d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_set_graphic_pane_g2_copy1( 0 ) );
    d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_set_graphic_pane_t1_copy1( 1 ), 1 );

    itemDrawer->SetItemMarkPosition(0);
    itemDrawer->SetItemMarkReplacement( KFirstIconReplacement ); // do not colorskin
    itemDrawer->SetItemMarkReverse(ETrue);
    
    CFormattedCellListBoxData::TColors colors;
    colors.iBack = AKN_LAF_COLOR_STATIC(0);
    colors.iHighlightedText = AKN_LAF_COLOR_STATIC(0);
    colors.iHighlightedBack = AKN_LAF_COLOR_STATIC(243);

    // normal setting page or transparency setting page are all referred to skin text color
    //for avoiding highlight background is white error.
    colors.iText = AKN_LAF_COLOR_STATIC(215);
    if ( AknsUtils::AvkonSkinEnabled() )
        {
        SetESSHighlightedTextColor( colors, EAknsCIQsnTextColorsCG12 );
        SetESSTextColor( colors, EAknsCIQsnTextColorsCG7 );
        }
    
    itemDrawer->FormattedCellData()->SetSubCellColorsL(0, colors);
    itemDrawer->FormattedCellData()->SetSubCellColorsL(1, colors);
    itemDrawer->FormattedCellData()->SetSubCellColorsL(2, colors);
    itemDrawer->SetTextColor(colors.iText);
    itemDrawer->SetBackColor(colors.iBack);
    itemDrawer->SetHighlightedTextColor(colors.iHighlightedText);
    itemDrawer->SetHighlightedBackColor(colors.iHighlightedBack);
    _AKNTRACE_FUNC_EXIT;    
    }

CAknSingle2GraphicListBoxItemDrawer::CAknSingle2GraphicListBoxItemDrawer( MTextListBoxModel* aTextListBoxModel,
                                                                          const CFont* aFont,
                                                                          CColumnListBoxData* aColumnData )
    : CColumnListBoxItemDrawer( aTextListBoxModel, aFont, aColumnData),
      iMoveIcon( EFalse )
    {
    }

CAknSingle2GraphicListBoxItemDrawer::~CAknSingle2GraphicListBoxItemDrawer()
    {
    }

void CAknSingle2GraphicListBoxItemDrawer::DrawItemText( TInt aItemIndex,
                                                        const TRect& aItemTextRect,
                                                        TBool aItemIsCurrent,
                                                        TBool aViewIsEmphasized,
                                                        TBool aItemIsSelected ) const
    {
    TInt error;
    TRAP( error, if ( iMoveIcon )
        {
        TPtrC itemText = iModel->ItemText( aItemIndex );
        TPtrC columnText;
        TextUtils::ColumnText( columnText, 1, &itemText );
        CColumnListBoxData* d( ColumnData() );

        d->ResetSLSubCellArray();
        d->SetGraphicSubCellL( 0, AknLayoutScalable_Avkon::list_single_2graphic_pane_g4( 0 ) );
        d->SetGraphicSubCellL( 1, AknLayoutScalable_Avkon::list_single_2graphic_pane_g1( 0 ) );
        d->SetGraphicSubCellL( 3, AknLayoutScalable_Avkon::list_single_2graphic_pane_g2( 0 ) );
        d->SetGraphicSubCellL( 4, AknLayoutScalable_Avkon::list_single_2graphic_pane_g3( 0 ) );

        if ( columnText == KNullDesC )
            {
            // needs own layout - borrow this for now.
            d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 0 ) );
            d->SetConditionalSubCellL( 4, AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 2 ), 2 );
            d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_graphic_pane_t1( 1 ), 2 );
            }
        else
            {
            d->SetTextSubCellL( 2, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 0 ) );
            d->SetConditionalSubCellL( 4, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 2 ), 2 );
            d->SetConditionalSubCellL( 3, AknLayoutScalable_Avkon::list_single_2graphic_pane_t1( 1 ), 2 );
            }
        }); // end trap
    if ( iMoveIcon && error != KErrNone ) return; // better not crash in draw with hosed layout
    CColumnListBoxItemDrawer::DrawItemText( aItemIndex, aItemTextRect, aItemIsCurrent, aViewIsEmphasized, aItemIsSelected );
    }

void CAknSingle2GraphicListBoxItemDrawer::UseEmptyIconSpace( TBool aUse )
    {
    iMoveIcon = aUse;
    }

EXPORT_C void CAknSingle2GraphicStyleListBox::CreateItemDrawerL()
    {
    CColumnListBoxData* columnData = CColumnListBoxData::NewL();
    CleanupStack::PushL( columnData );
    iItemDrawer=new(ELeave) CAknSingle2GraphicListBoxItemDrawer( Model(), iEikonEnv->NormalFont(), columnData );
    CleanupStack::Pop();
    }

EXPORT_C void CAknSingle2GraphicStyleListBox::UseEmptyIconSpace( TBool aUse )
    {
    __ASSERT_ALWAYS( iItemDrawer, Panic( EAknPanicListBoxItemDrawerNotCreated ) );
    CAknSingle2GraphicListBoxItemDrawer* d = static_cast<CAknSingle2GraphicListBoxItemDrawer*>(iItemDrawer);
    d->UseEmptyIconSpace( aUse );
    }
// End of File
