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
* Description:  Implementation for colour selection grid.
*
*/


// INCLUDE FILES
#include <aknPopupHeadingPane.h> 
#include <AknIconArray.h>
#include <eikenv.h>
#include <eikcapc.h>
#include <aknlists.h>
#include <bitstd.h>
#include <gulicon.h>
#include <fbs.h>
#include <AknsDrawUtils.h>
#include <AknsBasicBackgroundControlContext.h>
#include <barsread.h>
#include <AknLayout.lag>
#include <aknenv.h>
#include <skinlayout.cdl.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <layoutmetadata.cdl.h>
#include <AknUtils.h>
#include <akntranseffect.h>

#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eikenvinterface.h>
#include <uikon/eikdefmacros.h>
#endif

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
#include <aknlistloadertfx.h>
#include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST

#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
#include <gfxtranseffect/gfxtranseffect.h>
#include <akntransitionutils.h>
#endif

#include <touchfeedback.h>
#include "AknColourSelectionGrid.h"
#include "akntrace.h"

enum TCSelGridFlags
    {
    ECSelGridCloseAfterDPageClicked = 0x01
    };
  
 
// ============================= LOCAL FUNCTIONS ===============================


TRect ColourSelectionDialogRect()
    {
    TInt colourPopupVariety = 0;
    if (Layout_Meta_Data::IsLandscapeOrientation())
        {
        switch (AknLayoutUtils::CbaLocation())
            {
            case AknLayoutUtils::EAknCbaLocationBottom:
                //Bottom softkeyt
                colourPopupVariety = 1;
                break;
            case AknLayoutUtils::EAknCbaLocationRight:
                //Right softkeyt
                colourPopupVariety = 2;
                break;
            case AknLayoutUtils::EAknCbaLocationLeft:
                //Left softkeyt
                colourPopupVariety = 3;
                break;
            default:
                break;
            }
        }
    
    TRect mainPane;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EPopupParent, mainPane );
    
    TAknLayoutRect colourPopupWindow;
    colourPopupWindow.LayoutRect(mainPane, AknLayoutScalable_Avkon::popup_large_graphic_colour_window(colourPopupVariety));     
    return colourPopupWindow.Rect();
    }

// -----------------------------------------------------------------------------
// DrawGrayLines
// Draws gray grid to colour selection grid
// -----------------------------------------------------------------------------
void DrawGrayLines(
    CWindowGc& aGc,
    const TRect& aRect,
    const TBool aNoneExist=ETrue)
    {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( &aGc );
    if ( transApi )
        {
        transApi->StartDrawing( MAknListBoxTfxInternal::EListView );
        }
#endif
        // get the colour 
        TRgb separatorColor;
        AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), separatorColor, KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG5 );
        aGc.SetPenStyle(CGraphicsContext::ESolidPen);
        aGc.SetBrushStyle(CGraphicsContext::ENullBrush);
        aGc.SetPenColor(separatorColor);

        TInt paneSeparatorVarietyIndex = aNoneExist;
        TInt gridVarietyIndex = paneSeparatorVarietyIndex;

        // list scroll is inside popup pane
        TAknLayoutRect listScroll;
        listScroll.LayoutRect(aRect, AknLayoutScalable_Avkon::listscroll_popup_colour_pane());
        TRect listScrollRect = listScroll.Rect();

        // the grid is inside listscroll
        TAknLayoutRect grid;
        grid.LayoutRect(listScrollRect, AknLayoutScalable_Avkon::grid_large_graphic_colour_popup_pane(gridVarietyIndex));
        TRect gridRect = grid.Rect();

        // get some layout data
        TAknLayoutScalableParameterLimits limits = AknLayoutScalable_Avkon::cell_large_graphic_colour_popup_pane_ParamLimits();
        
        // we have to use a hardcoded width for the grid separators, 
        // because we have to make the same assumptions as the grid implementation
        // about how much gap there is between cells

        TInt cols = limits.LastColumn() + 1;
        TInt rows = limits.LastRow() + 1;

        TAknLayoutRect colourCellSize;
        if (aNoneExist)
            {
            colourCellSize.LayoutRect(gridRect, AknLayoutScalable_Avkon::aid_size_cell_colour_3_pane(1));
            }
        else
            {
            colourCellSize.LayoutRect(gridRect, AknLayoutScalable_Avkon::aid_size_cell_colour_1_pane(1));
            }
    
        TInt cellWidth = colourCellSize.Rect().Width();
        TInt cellHeight = colourCellSize.Rect().Height();

        TInt left = gridRect.iTl.iX;
        TInt right = gridRect.iTl.iX + (cols * cellWidth);
        
        TInt top = gridRect.iTl.iY;
        TInt bottom = gridRect.iTl.iY + (rows * cellHeight);

        // horizontal lines
        for(TInt row = 0; row < rows; row++)
            {
            // but cheat by dividing the grid rect into four rows 
            TInt y = top + ((row + 1) * cellHeight);
            TPoint start(left, y); // the start of the separator is before the start of the next cell
            TPoint end(right, y);
            aGc.DrawLine( start, end );
            }

        // vertical lines
        for(TInt col = 0; col <cols; col++)
            {
            // but cheat by dividing the grid rect into four cols 
            TInt x = left + ((col + 1) * cellWidth);
            TPoint start(x, top); // the start of the separator is before the start of the next cell
            TPoint end(x, bottom);
            aGc.DrawLine( start, end );
            }

        // fix for TSW error EVWG-7MCBBC
        gridRect.iBr += TPoint( 1, 1 );

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->StopDrawing();
        }
#endif
    aGc.DrawRect( gridRect );
};
 
// CLASS DECLARATION

/**
* CColorGridView
*
*
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CColorGridView) : public CAknGridView
    {
    public:    
        /**
        * C++ default constructor.
        */
        CColorGridView();

    public: // from CAknGridView
        /**
        * draws gray grid
        * @since 2.0
        * @param aClipRect
        */
        void Draw(const TRect* aClipRect = NULL) const;

        /**
        * Sets iRect and InoneExist
        * @since 2.0
        * @param aRect
        * @param aNoneExist
        */
        void SetRect(const TRect& aRect, const TBool& aNoneExist);
        
        TPoint ItemPos(TInt aItemIndex) const;

    private: // data
        TAknLayoutRect iHorLine[5];
        TAknLayoutRect iVerLine[5];
        TRect iRect;
        TBool iNoneExist;
        CCoeControl *iControl;
    };

// ----------------------------------------------------------------------------
// CColorGridView::CColorGridView()
//
// ---------------------------------------------------------
//
CColorGridView::CColorGridView()
    {
    }

// ---------------------------------------------------------
// CColorGridView::SetRect()
//
// ---------------------------------------------------------
//
void CColorGridView::SetRect(const TRect& aRect, const TBool& aNoneExist)
    {
    _AKNTRACE( "[%s] The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   __FUNCTION__, 
    		   aRect.iTl.iX, aRect.iTl.iY, 
    		   aRect.iBr.iX, aRect.iBr.iY );
    iRect.SetRect(aRect.iTl, aRect.iBr);
    iNoneExist = aNoneExist;
    }


// ---------------------------------------------------------
// CColorGridView::Draw()
//
// ---------------------------------------------------------
//
void CColorGridView::Draw(const TRect* aClipRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    _AKNTRACE( "The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   aClipRect->iTl.iX, aClipRect->iTl.iY, 
    		   aClipRect->iBr.iX, aClipRect->iBr.iY );
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    MAknListBoxTfxInternal *transApi = CAknListLoader::TfxApiInternal( iGc );
    if ( transApi )
        {
        TRect drawRect = ViewRect();
        transApi->BeginRedraw(  MAknListBoxTfxInternal::EListView, drawRect );
        }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
    CAknGridView::Draw(aClipRect);
    DrawGrayLines(*iGc, iRect, iNoneExist);
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    if ( transApi )
        {
        transApi->EndRedraw( MAknListBoxTfxInternal::EListView );
        }
#endif
    _AKNTRACE_FUNC_EXIT;
    }

TPoint CColorGridView::ItemPos( TInt aItemIndex ) const
    {
    TPoint p = CAknGridView::ItemPos( aItemIndex );
    p += TPoint(1,1);
    return p;
    }

/**
* Color grid
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CColorGrid) : public CAknGrid
    {    
public: // from CEikListBox
        void SizeChanged();
    
public: // from CAknGrid
        /**
        * OfferKeyEventL
        * @since 2.0
        * @param aKeyEvent
        * @param aType
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        /**
        * MakeViewClassInstanceL
        * Overriden from CAknGrid. Create the grid view for thus grid class.
        * @since 2.0
        * @ return grid view
        */ 
        CListBoxView* MakeViewClassInstanceL();

        /**
        * Set value to tel does none exist
        * Set value to iNoneExist
        * @since 2.0
        * @param aNoneExist Value to iNoneExist
        */
        void SetNoneExist(const TBool aNoneExist) {iNoneExist = aNoneExist;};
        void SetLegacyMode(TBool aLegacyMode);
        TBool IsLegacyMode();

public: // new functions

    /**
    * Draws the pressed down highlight to the currently selected grid item. 
    */
    void SetPressedDownState();
    
    /**
    * Clears the pressed down highlight if currently drawn.
    */
    void CleanPressedDownState();

private: // data

    TBool iNoneExist;
    TBool iLegacyMode;        
    TBool iSingleClickEnabled;
    };

// ---------------------------------------------------------
// CColorGrid::SizeChanged()
//
// ---------------------------------------------------------
void CColorGrid::SizeChanged()
    {            
    _AKNTRACE_FUNC_ENTER;
    // First call the parent SizeChanged()
    CAknGrid::SizeChanged();
    
    // Retrieve the itemDrawer
    CFormattedCellListBoxItemDrawer* itemDrawer = ItemDrawer();
    
    // Start setting up the grid
    AknListBoxLayouts::SetupStandardGrid(*this);
            
    // we have to calculate the size of each cell so that they match the grid lines
    TRect gridRect = Rect();
    
    // get some layout data
    TAknLayoutScalableParameterLimits limits = AknLayoutScalable_Avkon::cell_large_graphic_colour_popup_pane_ParamLimits();
    
    TInt cols = limits.LastColumn() + 1;
    TInt rows = limits.LastRow() + 1;
    
    TAknLayoutRect colourCellSize;
    if (iNoneExist)
        {
        colourCellSize.LayoutRect(gridRect, AknLayoutScalable_Avkon::aid_size_cell_colour_3_pane(1));
        }
    else
        {
        colourCellSize.LayoutRect(gridRect, AknLayoutScalable_Avkon::aid_size_cell_colour_1_pane(1));
        }

    TInt cellWidth = colourCellSize.Rect().Width() - 1;
    TInt cellHeight = colourCellSize.Rect().Height() - 1;
    
    // Define the overall size of the cell
    AknListBoxLayouts::SetupGridPos(*this, 0, 0, 0, 0, cellWidth, cellHeight);
    
    TPoint pointLT(0,0);
    TPoint pointWH(cellWidth, cellHeight);
    
    AknListBoxLayouts::SetupGridFormGfxCell( *this,
        itemDrawer,
        0/* cell index */,
        AknLayout::colour( iNoneExist ? 0 : 1 ),
        pointLT,
        pointWH );

    // Grid skinning starts
    TAknLayoutRect qsnFrPopupCenter;
    qsnFrPopupCenter.LayoutRect(gridRect,
        SkinLayout::Popup_windows_skin_placing__frame_general__Line_1(gridRect));
    itemDrawer->FormattedCellData()->SetBackgroundSkinStyle(
        &KAknsIIDQsnFrPopupCenter, qsnFrPopupCenter.Rect()); 
                   
    DisableScrolling( ETrue );   
    // Check single click flag
    iSingleClickEnabled = iAvkonAppUi->IsSingleClickCompatible();
    _AKNTRACE_FUNC_EXIT;
    }

// ---------------------------------------------------------
// CColorGrid::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
//
// ---------------------------------------------------------
TKeyResponse CColorGrid::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    TInt code = aKeyEvent.iCode;
      
    // With single click first key event enables highlight
    if ( iSingleClickEnabled
            && ItemDrawer()->Flags()
            & CListItemDrawer::ESingleClickDisabledHighlight )
        {      
        _AKNTRACE_FUNC_EXIT;
        return CAknGrid::OfferKeyEventL( aKeyEvent,aType );
        }
    
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;

    TBool shiftKeyPressed = (aKeyEvent.iModifiers & EModifierShift);
    if (iListBoxFlags & EMultipleSelection)
        {
        if (shiftKeyPressed && iListBoxFlags & EShiftEnterMarks)
            {
            View()->SetAnchor(View()->CurrentItemIndex());
            selectionMode = CListBoxView::EDisjointMarkSelection;
            }
        else
            selectionMode = CListBoxView::ENoSelection;
        }
    
    TInt rowIndex = 0;
    TInt colIndex = 0;
    CAknGridView *view = (CAknGridView*)iView;
    switch (code)
        {
    case EKeyUpArrow:
        view->LogicalPosFromDataIndex(view->CurrentDataIndex(), rowIndex, colIndex);

        if (rowIndex ==0 )
            {
            _AKNTRACE_FUNC_EXIT;
            return EKeyWasNotConsumed;
            }
        iView->MoveCursorL(CListBoxView::ECursorPreviousItem, selectionMode);
        ClearMatchBuffer();
        _AKNTRACE( "[%s] EKeyUpArrow",__FUNCTION__ );
        break;
    case EKeyDownArrow:
        iView->MoveCursorL(CListBoxView::ECursorNextItem, selectionMode);
        ClearMatchBuffer();
        _AKNTRACE( "[%s] EKeyDownArrow",__FUNCTION__ );
        break;

    case EKeyLeftArrow:
        iView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
        ClearMatchBuffer();
        _AKNTRACE( "[%s] EKeyLeftArrow",__FUNCTION__ );
        break;
    case EKeyRightArrow:
        iView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
        ClearMatchBuffer();
        _AKNTRACE( "[%s] EKeyRightArrow",__FUNCTION__ );
        break;

#if defined(_DEBUG) // only needed when debuging
    case EKeyPageUp:
        iView->MoveCursorL(CListBoxView::ECursorPreviousPage, selectionMode);
        ClearMatchBuffer();
        break;
    case EKeyPageDown:
        iView->MoveCursorL(CListBoxView::ECursorNextPage, selectionMode);
        ClearMatchBuffer();
        break;
    case EKeyHome:
        iView->MoveCursorL(CListBoxView::ECursorFirstItem, selectionMode);
        ClearMatchBuffer();
        break;
    case EKeyEnd:
        iView->MoveCursorL(CListBoxView::ECursorLastItem, selectionMode);
        ClearMatchBuffer();
        break;
#endif// end of debug code
    default:
    	_AKNTRACE_FUNC_EXIT;
        return CEikListBox::OfferKeyEventL(aKeyEvent,aType);
        }

    if (iListBoxFlags & EStateChanged)
        {
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        iListBoxFlags &= (~EStateChanged);
        }

    _AKNTRACE_FUNC_EXIT;
    return EKeyWasConsumed;
    }

CListBoxView* CColorGrid::MakeViewClassInstanceL()
    {
    CListBoxView* view = new (ELeave) CColorGridView();
    return view;
    }


void CColorGrid::SetLegacyMode(TBool aLegacyMode)
    {
    iLegacyMode = aLegacyMode;
    }

TBool CColorGrid::IsLegacyMode()
    {
    return iLegacyMode;
    }
// ---------------------------------------------------------------------------
// Switches the normal highlight from the highlighted grid item to the
// pressed down highlight.
// ---------------------------------------------------------------------------
//
void CColorGrid::SetPressedDownState()
    {
    TBool wasPressedDown =
        GridView()->ItemDrawer()->Flags() & CListItemDrawer::EPressedDownState;
    if ( !wasPressedDown )
        {
        GridView()->ItemDrawer()->SetFlags( CListItemDrawer::EPressedDownState );
        GridView()->DrawItem( CurrentItemIndex() );
        }
    }

// ---------------------------------------------------------------------------
// Switches the pressed down highlight from the highlighted grid item
// to the normal highlight.
// ---------------------------------------------------------------------------
//
void CColorGrid::CleanPressedDownState()
    {
    TBool wasPressedDown =
        GridView()->ItemDrawer()->Flags() & CListItemDrawer::EPressedDownState;
    if ( wasPressedDown )
        {
        GridView()->ItemDrawer()->ClearFlags( CListItemDrawer::EPressedDownState );
        GridView()->DrawItem( CurrentItemIndex() );
        }
    }    


// CLASS DECLARATION

/**
* None field
*
* Control to none field
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CNoneField) : public CCoeControl
    {
    public:
        /**
        * C++ default constructor.
        */
        CNoneField( TBool aSingleClickEnabled );
		
        /**
        * destructor.
        */
        ~CNoneField();
    
    public: // New functions

        /**
        * Sets the skin context for the control.
        *
        * @param  aSkinContext  Skin context.
        */
        void SetSkinContext( MAknsControlContext* aSkinContext );

        void SetLegacyMode(TBool aLegacyMode);
        TBool IsLegacyMode();
                
        void SetPressDownEffect( TBool aEnable );
    public: // from CCoeControl
        /**
        * SizeChanged
        * @since 2.0
        */
        void SizeChanged();
        
        /**
        * Draw
        * @since 2.0
        * @param aRect
        */
        void Draw(const TRect& aRect) const;
        
        /**
        * ConstructFromResourceL
        * @since 2.0
        * @param aReader
        */
        void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * From CCoeControl        
        * HandlePointerEventL handles pointerevents.
        * @param aPointerEvent pointerevent to be handled
        */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent );
        
        /**            
        * Sets iNoneObserver to be as observer
        * @param aObserver pointer to observer
        */
        void SetNoneFieldObserver( MCoeControlObserver* aObserver  );
 
    private: //data
        // TRect iRect; 
        MAknsControlContext *iSkinContext;
        HBufC *iText;
        MCoeControlObserver *iNoneObserver;
        TBool iLegacyMode;
        TBool iIsEnablePressDownEffect;
        TBool iSingleClickEnabled;
    };
CNoneField::CNoneField( TBool aSingleClickEnabled ) 
    : iIsEnablePressDownEffect ( EFalse ), 
      iSingleClickEnabled( aSingleClickEnabled ) 
    {
    }

CNoneField::~CNoneField()
    {
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->RemoveFeedbackForControl( this );
        }
    delete iText;
    iText = NULL;
    }


// ---------------------------------------------------------------------------
// Sets the skin context for the control.
// ---------------------------------------------------------------------------
//
void CNoneField::SetSkinContext( MAknsControlContext* aSkinContext )
    {
    iSkinContext = aSkinContext;
    }


void CNoneField::SetLegacyMode(TBool aLegacyMode)
    {
    iLegacyMode = aLegacyMode;
    }

TBool CNoneField::IsLegacyMode()
    {
    return iLegacyMode;
    }

void CNoneField::SetPressDownEffect( TBool aEnable )
    {
    if ( !iSingleClickEnabled )
        {
        iIsEnablePressDownEffect = aEnable;
        }
    }

// ---------------------------------------------------------
// CNoneField::SizeChanged()
//
// ---------------------------------------------------------
void CNoneField::SizeChanged()
    {
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        feedback->ChangeFeedbackArea( this, 0, Rect() ); 
        }
    }
// ---------------------------------------------------------
// CNoneField::ConstructFromResourceL(TResourceReader& aReader)
//
// ---------------------------------------------------------
void CNoneField::ConstructFromResourceL(TResourceReader& aReader)
    {
    _AKNTRACE_FUNC_ENTER;
    if (iLegacyMode)
        {
        aReader.ReadInt16();
        aReader.ReadInt16();
        aReader.ReadInt16();
        aReader.ReadInt16();
        aReader.ReadInt16();
        TPtrC ptr = aReader.ReadTPtrC();
        iText = ptr.AllocL();        
        }
    else
        {            
        TPtrC ptr = aReader.ReadTPtrC();
        iText = ptr.AllocL();
        }
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        CFeedbackSpec* fbSpec = CFeedbackSpec::New();
        if ( fbSpec )
            {
            // on down event list basic feedback + audio
            fbSpec->AddFeedback( ETouchEventStylusDown,
                                 ETouchFeedbackBasicItem );
            
            // on up event list basic feedback, no audio
            fbSpec->AddFeedback( ETouchEventStylusUp,
                                 ETouchFeedbackBasicItem,
                                 ETouchFeedbackVibra );

            feedback->SetFeedbackArea( this,
                                       0,
                                       Rect(),
                                       fbSpec );
            delete fbSpec;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }
// ---------------------------------------------------------
// CNoneField::Draw(const TRect& aRect) const
//
// ---------------------------------------------------------
void CNoneField::Draw(const TRect& /*aRect*/) const
    {
    _AKNTRACE_FUNC_ENTER;
    
    TRect rect = Rect();
    
    CWindowGc& gc=SystemGc();
    
    // Set skin
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext(this);
    if (cc)
        {
        gc.SetPenStyle(CGraphicsContext::ENullPen);
        AknsDrawUtils::Background( skin, cc, gc, rect );
        }
    
    // Draw none -text
    TAknLayoutText noneText;
    noneText.LayoutText(rect, AknLayoutScalable_Avkon::cell_large_graphic_colour_none_popup_pane_t1());


    
    TAknLayoutId LayoutId;
    iAvkonEnv->GetCurrentLayoutId( LayoutId );
    
    // Draw focus
    if (IsFocused())
        {
        TAknLayoutRect gridHighlightPane;
        gridHighlightPane.LayoutRect( rect, AknLayoutScalable_Avkon::grid_highlight_pane_cp5());

        TBool windowFrameDrawn = EFalse;
        if (cc)
            {
            TAknLayoutRect topLeft;
            topLeft.LayoutRect(gridHighlightPane.Rect(), SkinLayout::Highlight_skin_placing__grid__Line_2());

            TAknLayoutRect bottomRight;
            bottomRight.LayoutRect(gridHighlightPane.Rect(), SkinLayout::Highlight_skin_placing__grid__Line_5());

            TRect outerRect = TRect(topLeft.Rect().iTl, bottomRight.Rect().iBr);
            TRect innerRect = TRect(topLeft.Rect().iBr, bottomRight.Rect().iTl);
            gc.SetPenStyle(CGraphicsContext::ENullPen);
            const TAknsItemID *frameId = iIsEnablePressDownEffect ? &KAknsIIDQsnFrGridPressed : &KAknsIIDQsnFrGrid;
            windowFrameDrawn = AknsDrawUtils::DrawFrame(skin, gc, outerRect, innerRect, *frameId, KAknsIIDNone);
            }
        if( !windowFrameDrawn )
            {
            gc.SetPenStyle(CGraphicsContext::ESolidPen);
            gc.SetPenColor(gridHighlightPane.Color());
            gridHighlightPane.DrawOutLineRect(gc);
            }
        }
    
    TRgb color( KRgbBlack );
    AknsUtils::GetCachedColor( skin,
                               color,
                               KAknsIIDQsnTextColors,
                               // text #19 popup windows popup windows text
                               EAknsCIQsnTextColorsCG19 );
    
    noneText.DrawText( gc, *iText, ETrue, color );
    
    TRgb separatorColor;
    AknsUtils::GetCachedColor(AknsUtils::SkinInstance(), separatorColor, KAknsIIDQsnLineColors, EAknsCIQsnLineColorsCG5 );
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetPenColor(separatorColor);
    TRect out(Rect());
    gc.DrawRect( out );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Handles pointer events in none field. If none is already focused, then
// this is second click to none field and we can inform observer to
// close itself.
// ---------------------------------------------------------------------------
//
void CNoneField::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up &&
         Rect().Contains( aPointerEvent.iPosition ) )
        { 
        /* Check whether `this' is still valid. */
        HBufC **text = &iText;

        if ( iNoneObserver && IsFocused() )
            {
            iNoneObserver->HandleControlEventL(
                this,
                MCoeControlObserver::EEventRequestExit );
            }
        
        if ( *text )
            {
            SetPressDownEffect( EFalse );
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CNoneField::SetNoneFieldObserver
// Set iNoneObserver to be observer of nonefield. 
// -----------------------------------------------------------------------------
//
void CNoneField::SetNoneFieldObserver( MCoeControlObserver* aObserver  )
    {
    iNoneObserver = aObserver;
    }
 
// CLASS DECLARATION
/**
* CAknColorSelectionGridControl
*
* 
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CAknColorSelectionGridControl) : public CCoeControl
    {
    public:
        /**
        * C++ default constructor.
        */
        CAknColorSelectionGridControl(CColorGrid *aGrid, 
            CNoneField* aNoneField, TBool aSingleClickEnabled );
        /**
        * destructor.
        */
        ~CAknColorSelectionGridControl();

    public: // New methods
        /**
        * Grid
        * @since 2.0
        */
        CColorGrid *Grid() const;
 
        /**
        * Grid
        * @since 2.0
        */
        CNoneField *NoneField() const;
        
        void SetParentRects(TRect aScreenSize, TRect aColourSelectionDialogRect);

    public: // from CCoeControl


        void SizeChanged();

        /**
        * CountComponentControls
        * @since 2.0
        * @return 
        */
        TInt CountComponentControls() const;
        
        
        /**
        * ComponentControl
        * @since 2.0
        * @return 
        */
        CCoeControl *ComponentControl(TInt aItem) const;
        
        
       /**
        * MinimumSize.
        * @since 2.0
        * @return minimum size of this control
        */
        TSize MinimumSize();
        
        
        /**
        * ?member_description.
        * @since 2.0
        * @param aDrawNow flag 
        */
        void FocusChanged(TDrawNow aDrawNow);

        /**
        * Draw
        * @since 2.0
        */
        void Draw(const TRect& /*aRect*/) const;

        /**
        * OfferKeyEventL
        * @since 2.0
        * @param aKeyEvent 
        * @param aType 
        * @return 
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * ConstructFromResourceL.
        * @since 2.0
        * @param aRes 
        */
        void ConstructFromResourceL(TResourceReader &aRes);
        
        /**
        * HandlePointerEventL
        * @param aPointerEvent pointer event information
        * @return
        */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    private:    // Data
        CColorGrid *iGrid;
        CNoneField* iNoneField;
        TRect iScreenSize;
        TRect iColourSelectionDialogRect;
        TBool iSingleClickEnabled;
    };

CAknColorSelectionGridControl::CAknColorSelectionGridControl(CColorGrid *aGrid, 
    CNoneField* aNoneField, TBool aSingleClickEnabled ) 
    : iGrid(aGrid), 
      iNoneField(aNoneField), 
      iSingleClickEnabled( aSingleClickEnabled ) 
    {
    }

CAknColorSelectionGridControl::~CAknColorSelectionGridControl() 
    { 
    delete iGrid; 
    if ( iNoneField && !iNoneField->IsLegacyMode())
        {        
        delete iNoneField;
        }
    }

void CAknColorSelectionGridControl::ConstructFromResourceL(TResourceReader &aRes)
    {
    _AKNTRACE_FUNC_ENTER;
    if (iNoneField)
        {
        iNoneField->SetContainerWindowL(*this);
        iNoneField->CopyControlContextFrom(this);
        if ( !iNoneField->IsLegacyMode() )
            {            
            iNoneField->ConstructFromResourceL(aRes);
            }
        }
    else
        {
        if (!iGrid->IsLegacyMode())
            {            
            aRes.ReadTPtrC(); // none text
            }
        }
        
    
    iGrid->SetContainerWindowL(*this);
    iGrid->CopyControlContextFrom(this);
    iGrid->ConstructFromResourceL(aRes);
    iGrid->ScrollBarFrame()->SetScrollBarVisibilityL(
                CEikScrollBarFrame::EOff, CEikScrollBarFrame::EOff );
    _AKNTRACE_FUNC_EXIT;
    }



CColorGrid* CAknColorSelectionGridControl::Grid() const
    { 
    return iGrid;
    }

CNoneField* CAknColorSelectionGridControl::NoneField() const
    {
    return iNoneField;
    }

void CAknColorSelectionGridControl::SetParentRects(TRect aScreenSize, TRect aColourSelectionDialogRect)
    {
    iScreenSize = aScreenSize;
    iColourSelectionDialogRect = aColourSelectionDialogRect;
    }
    
void CAknColorSelectionGridControl::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect applicationRect = iAvkonAppUi->ApplicationRect();
    if (applicationRect != iScreenSize)
        {
        iColourSelectionDialogRect = ColourSelectionDialogRect();
        iScreenSize = applicationRect;
        }
        
    TRect rect = Rect();
    TRect parent = TRect( 0, 0, rect.Width(), rect.Height() );
    TAknLayoutRect listScrollPopupColourPane;
    listScrollPopupColourPane.LayoutRect(parent , AknLayoutScalable_Avkon::listscroll_popup_colour_pane());

    TInt gridColourPopupPaneVariety = 0;
    if (iNoneField)
        {
        TAknLayoutRect noneFieldPane;
        noneFieldPane.LayoutRect(listScrollPopupColourPane.Rect(), AknLayoutScalable_Avkon::cell_large_graphic_colour_none_popup_pane(0));
        iNoneField->SetRect(noneFieldPane.Rect());
        gridColourPopupPaneVariety = 1;
        }
    TAknLayoutRect gridColourPopupPane;
    gridColourPopupPane.LayoutRect(listScrollPopupColourPane.Rect(), AknLayoutScalable_Avkon::grid_large_graphic_colour_popup_pane(gridColourPopupPaneVariety));
    iGrid->SetRect(gridColourPopupPane.Rect());
    
    STATIC_CAST(CColorGridView*,iGrid->View())->SetRect(parent, iNoneField != 0);    
    _AKNTRACE_FUNC_EXIT;
    }

TInt CAknColorSelectionGridControl::CountComponentControls() const
    {
    if (iNoneField)
        {                
        return 2; 
        }
    else
        {
        return 1;
        }
    }

CCoeControl* CAknColorSelectionGridControl::ComponentControl(TInt aItem) const 
    {
    if (iNoneField && aItem == 0)
        {
        return iNoneField;
        }
    else
        {                    
        return iGrid; 
        }
    }


TSize CAknColorSelectionGridControl::MinimumSize() 
    {    
    TRect applicationRect = iAvkonAppUi->ApplicationRect();
    if (applicationRect != iScreenSize)
        {
        iColourSelectionDialogRect = ColourSelectionDialogRect();
        iScreenSize = applicationRect;
        }

    TAknLayoutRect listScrollPopupColourPane;
    listScrollPopupColourPane.LayoutRect(iColourSelectionDialogRect , AknLayoutScalable_Avkon::listscroll_popup_colour_pane());
    return listScrollPopupColourPane.Rect().Size();
    }

void CAknColorSelectionGridControl::FocusChanged(TDrawNow /*aDrawNow*/)
    {
    if ( AknLayoutUtils::PenEnabled() )  
        {
        if ( !IsFocused() )
            {
            iGrid->ClearSelection();
            } 
        }
    }




void CAknColorSelectionGridControl::Draw(const TRect& /*aRect*/) const
    {
    _AKNTRACE_FUNC_ENTER;
    // Set skin
    CWindowGc& gc=SystemGc();
    
    MAknsSkinInstance *skin = AknsUtils::SkinInstance();
    MAknsControlContext *cc = AknsDrawUtils::ControlContext(this);
    gc.SetPenStyle(CGraphicsContext::ESolidPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    TRect rect = Rect();
        
    TRect outerRect = TRect(rect.iTl, iColourSelectionDialogRect.Size());
    TRect innerRect = iGrid->Rect();
    AknsDrawUtils::BackgroundBetweenRects( 
        skin, cc, gc, outerRect, innerRect );
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Handles key events in the color selection grid control.
// ---------------------------------------------------------------------------
//
TKeyResponse CAknColorSelectionGridControl::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    _AKNTRACE_FUNC_ENTER;
    // With single click first key event enables highlight
    if ( iSingleClickEnabled
            && iGrid->ItemDrawer()->Flags()
            & CListItemDrawer::ESingleClickDisabledHighlight )
        {
        // Highlight will be restored to grid control
        if ( iNoneField )
            {
            iNoneField->SetFocus( EFalse );
            }
        iGrid->SetFocus( ETrue );
        _AKNTRACE_FUNC_EXIT;
        return iGrid->OfferKeyEventL( aKeyEvent, aType ); 
        }
    if ( iNoneField && iNoneField->IsFocused() )
        {        
        if ( aKeyEvent.iCode == EKeyDownArrow )
            {
            iNoneField->SetFocus( EFalse );
            iGrid->SetFocus( ETrue );
            DrawDeferred();
            }

        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }

    TKeyResponse consumed = iGrid->OfferKeyEventL( aKeyEvent, aType );
    if ( iNoneField &&
         consumed == EKeyWasNotConsumed &&
         iGrid->IsFocused() &&
         aKeyEvent.iCode == EKeyUpArrow )
        {
        iGrid->SetFocus( EFalse );
        iNoneField->SetFocus( ETrue );
        DrawDeferred();

        _AKNTRACE_FUNC_EXIT;
        return EKeyWasConsumed;
        }

    _AKNTRACE_FUNC_EXIT;
    return consumed;
    }


// ---------------------------------------------------------------------------
// Handle the pointer event to the color selection grid control.
// ---------------------------------------------------------------------------
//
void CAknColorSelectionGridControl::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( AknLayoutUtils::PenEnabled() ) 
        {
        // Pointer on None-field
        if ( iNoneField &&
             iNoneField->Rect().Contains( aPointerEvent.iPosition ) )
            {
            switch ( aPointerEvent.iType )
                {
                case TPointerEvent::EButton1Down:
                    {
                    _AKNTRACE( "[%s] TPointerEvent::EButton1Down", 
                    		   __FUNCTION__ );
                    // Change focus from color grid to none-field.
                    if ( iGrid->IsFocused() )                                              
                        {
                        iGrid->SetFocus( EFalse );
                        }
                    iNoneField->SetPressDownEffect( ETrue );
                    iNoneField->SetFocus( ETrue );
                    DrawDeferred();
                    break;
                    }
                    
                case TPointerEvent::EDrag:
                    {
                    _AKNTRACE( "[%s] TPointerEvent::EDrag", 
                    		   __FUNCTION__ );
                    if ( iGrid->IsFocused() )                                              
                        {
                        iGrid->CleanPressedDownState(); 
                        iGrid->SetFocus( EFalse );
                        DrawDeferred();
                        }
                    break;
                    }
                        
                default:
                    {
                    break;
                    }
                }

            iNoneField->HandlePointerEventL( aPointerEvent );
            _AKNTRACE_FUNC_EXIT;
            return;
            }
        
        // Pointer on grid
        CAknGridView *gridView =
            static_cast<CAknGridView*>( iGrid->GridView() );
        
        TSize itemSize( gridView->ItemSize( 0 ) );
        TRect visibleItemsRect(
            gridView->ViewRect().iTl, 
            TSize(
                itemSize.iWidth * gridView->NumberOfColsInView(), 
                itemSize.iHeight * gridView->NumberOfRowsInView() ) );
        
        if ( visibleItemsRect.Contains( aPointerEvent.iPosition ) )
            {
            switch ( aPointerEvent.iType )
                {
                case TPointerEvent::EButton1Down:
                    {
                    _AKNTRACE( "[%s] TPointerEvent::EButton1Down", 
                    		   __FUNCTION__ );
                    if ( iNoneField && iNoneField->IsFocused() )
                        {
                        // Change focus from none-field to color grid.
                        iNoneField->SetFocus( EFalse );
                        iNoneField->SetPressDownEffect( EFalse );
                        iNoneField->DrawDeferred();
                        }
                    iGrid->SetFocus( ETrue, EDrawNow );
                    break;
                    }
                    
                case TPointerEvent::EDrag:
                    {
                    _AKNTRACE( "[%s] TPointerEvent::EDrag", 
                    		   __FUNCTION__ );
                    if ( iNoneField && iNoneField->IsFocused() )
                        {
                        iNoneField->SetPressDownEffect( EFalse );
                        iNoneField->SetFocus( EFalse );
                        DrawDeferred();
                        }
                    }
                    
                case TPointerEvent::EButton1Up:
                    {
                    _AKNTRACE( "[%s] TPointerEvent::EButton1Up", 
                    		   __FUNCTION__ );
                    if ( !iGrid->IsFocused() )
                        {
                        _AKNTRACE_FUNC_EXIT;
                        return; // Ignore if move from none field to color grid
                        }
                    break;
                    }
                default:
                    {
                    break;
                    }
                }
            }
        else
            {
            iGrid->CleanPressedDownState();

            if ( iNoneField )
                {   
                iNoneField->SetPressDownEffect( EFalse );
                }

            DrawDeferred();
            }

        iGrid->HandlePointerEventL( aPointerEvent );  
        }
    _AKNTRACE_FUNC_EXIT;
    }
    

// CLASS DECLARATION

/**
* CMainTextArray
*
* 
*
*  @lib avkon
*  @since 2.0
*/

NONSHARABLE_CLASS(CMainTextArray) : public MDesCArray, public CBase
    {
    public:

        /**
        * C++ default constructor.
        */
        CMainTextArray(TBool &aNoneExist);
        /**
        * Destructor.
        */
        ~CMainTextArray();
    
        /**
        * MdcaCount
        * @since 2.0
        * @return 
        */
        virtual TInt MdcaCount() const;
        
        /**
        * MdcaPoint
        * @since 2.0
        * @param aIndex 
        * @return 
        */
        virtual TPtrC MdcaPoint(TInt aIndex) const;
        
        /**
        * ConstructL
        * @since 2.0
        * @param aColours Array of colours to be in grid
        */
        void ConstructL(CArrayFixFlat<TRgb>* aColours);

    public: // Data
        CGulIcon* iIcon[16];

    private:    // Data
        mutable TInt iIndex;
        TInt iColourNmbr;
        TBool iNoneExist;
        CArrayFixFlat<TRgb>* iColours;
        CFbsBitmap* iBitmap[16];
        CFbsBitmapDevice* iBmpDevice[16];
        HBufC *iString;

    };

// ---------------------------------------------------------
// CMainTextArray::CMainTextArray()
//
// ---------------------------------------------------------
//
CMainTextArray::CMainTextArray(TBool &aNoneExist)
        : iNoneExist(aNoneExist)
    {
    }
// ---------------------------------------------------------
// CMainTextArray::~CMainTextArray()
//
// ---------------------------------------------------------
//
CMainTextArray::~CMainTextArray()
    {
    for (TInt i = 0;i<iColourNmbr;i++)
        {
        delete iBitmap[i];
        delete iBmpDevice[i];
        }
    delete iString;
    }

// ---------------------------------------------------------
// CMainTextArray::ConstructL()
// 
// ---------------------------------------------------------
//
void CMainTextArray::ConstructL(CArrayFixFlat<TRgb>* aColours)
    {

    this->iColours = aColours;
    iColourNmbr = aColours->Count();
    if (iColourNmbr > 16)
        {
        iColourNmbr = 16;
        }

    TAknLayoutRect r;
    TAknLayoutRect r_pane;
    TInt w, h;
        r_pane.LayoutRect(TRect(0,0,0,0), AknLayoutScalable_Avkon::cell_large_graphic_colour_popup_pane(iNoneExist, 0, 0).LayoutLine());
        r.LayoutRect(r_pane.Rect(), AknLayoutScalable_Avkon::cell_large_graphic_colour_popup_pane_g1().LayoutLine());
        w = r.Rect().Width();
        h = r.Rect().Height();
    TSize bmpsize(w,h);

    for (TInt i = 0;i<iColourNmbr;i++)
        {
        iBitmap[i] = new (ELeave) CFbsBitmap();
        iBitmap[i]->Create(bmpsize,EColor4K);
        iIcon[i] = CGulIcon::NewL(iBitmap[i]);
        iIcon[i]->SetBitmapsOwnedExternally(ETrue);
        iBmpDevice[i] = CFbsBitmapDevice::NewL(iBitmap[i]);
        iBmpDevice[i]->Resize(iBitmap[i]->SizeInPixels());
        }

    iString = HBufC::NewL(10);
    }


// ---------------------------------------------------------
// CMainTextArray::MdcaCount()
//
// ---------------------------------------------------------
//
TInt CMainTextArray::MdcaCount() const
    {
    return(iColourNmbr);
    }

// ---------------------------------------------------------
// CMainTextArray::MdcaPoint()
//
// ---------------------------------------------------------
//
TPtrC CMainTextArray::MdcaPoint(TInt aIndex) const
    {
    TRAP_IGNORE(
        {

        CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
        CleanupStack::PushL( fbsBitGc );

        fbsBitGc->Activate(iBmpDevice[aIndex]);

        fbsBitGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
        if (aIndex < iColourNmbr)
            {
            fbsBitGc->SetBrushColor(iColours->At(aIndex));
            }

        fbsBitGc->Clear();

        CleanupStack::PopAndDestroy(); // fbsBitGc
        });
    //fix for TSW error AJUA-7MTAXE
    iString->Des().Num(aIndex); 
    
    return *iString;
    }

// ============================ MEMBER FUNCTIONS ===============================

// ----------------------------------------------------------------------------
// Extension class
// 
// ----------------------------------------------------------------------------
//
NONSHARABLE_CLASS(CAknColourSelectionGridExtension): public CBase
    {
    public:
    CAknColourSelectionGridExtension();
    ~CAknColourSelectionGridExtension();
    
    public:
    TInt iFlags;
    TBool iIsDragged;
    };

CAknColourSelectionGridExtension::CAknColourSelectionGridExtension()
    : iFlags(0), iIsDragged( EFalse )
    {
    }
    
CAknColourSelectionGridExtension::~CAknColourSelectionGridExtension()
    {
    }
 
// ---------------------------------------------------------
// CAknColourSelectionGrid::CAknColourSelectionGrid()
//
// ---------------------------------------------------------
CAknColourSelectionGrid::CAknColourSelectionGrid()  
    {
#ifdef RD_UI_TRANSITION_EFFECTS_POPUPS
    GfxTransEffect::Register( this, KGfxContextMenuControlUid );
#endif
    iWsBufferRequestID = iAvkonEnv->RequestWsBuffer( 15000 );
    }

// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CAknColourSelectionGrid *CAknColourSelectionGrid::NewL(
                           CArrayFixFlat<TRgb> *aColours,
                           TBool aNoneExist,
                           TBool& aNoneChosen,
                           TRgb& aColourChosen)
    {
    

    CAknColourSelectionGrid *self = new(ELeave)CAknColourSelectionGrid;
    
    self->iColours = aColours;
    self->iNoneExist = aNoneExist;
    self->iNoneChosen = &aNoneChosen;
    self->iColourChosen = &aColourChosen;
    
    return (self);

    }


// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::~CAknColourSelectionGrid
// Destructor
// -----------------------------------------------------------------------------
//
EXPORT_C CAknColourSelectionGrid::~CAknColourSelectionGrid()
    {
    iAvkonEnv->CancelWsBufferRequest( iWsBufferRequestID );
    delete iExtension;
    }


// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::PreLayoutDynInitL()
// 
// -----------------------------------------------------------------------------
//
void CAknColourSelectionGrid::PreLayoutDynInitL()
    {
    _AKNTRACE_FUNC_ENTER;
    iExtension = new (ELeave) CAknColourSelectionGridExtension;
    
    CAknIconArray* theIcons = new(ELeave) CAknIconArray(iColours->Count());
    CleanupStack::PushL(theIcons);

    CMainTextArray* iconArrays = new (ELeave) CMainTextArray(iNoneExist);
    CleanupStack::PushL(iconArrays);
    iconArrays->ConstructL(iColours);
    for (TInt i=0;i<iColours->Count();i++)
        {
        theIcons->AppendL( iconArrays->iIcon[i] );
        }
    // Load the icon array into the grid
    CCoeControl* gridCtrl = Grid();
    CColorGrid* grid = (CColorGrid*)gridCtrl;

    grid->ItemDrawer()->FormattedCellData()->SetIconArray(theIcons);
    grid->Model()->SetItemTextArray(iconArrays);
    CleanupStack::Pop(); // iconArrays
    CleanupStack::Pop(); // theIcons

    SetLineNonFocusing(EColourGridPopup);
    if ( iNoneBox && iNoneBox->IsLegacyMode() )
        {
        SetLineNonFocusing(EColourGridPopupNone);
        }

    grid->ItemDrawer()->FormattedCellData()->SetSkinEnabledL(ETrue);
    
    CCoeControl *popupHeadingCtrl = ControlOrNull(EColourGridPopup);
    if (popupHeadingCtrl)
        {
        STATIC_CAST(CAknPopupHeadingPane*, popupHeadingCtrl)->SetLayout(CAknPopupHeadingPane::EColourSelectionGridHeadingPane);
        }
    _AKNTRACE_FUNC_EXIT;
    }

// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::SetSizeAndPosition()
// 
// -----------------------------------------------------------------------------
//
void CAknColourSelectionGrid::SetSizeAndPosition( const TSize& aSize )
    {
    _AKNTRACE_FUNC_ENTER;
    // Set skin id 
    MAknsControlContext *cc = AknsDrawUtils::ControlContext(this);
    if (cc)
        {
        const TAknsItemID *frameCenterId = &KAknsIIDQsnFrPopupCenter;
        
        CAknsBasicBackgroundControlContext *bcc = 
            (CAknsBasicBackgroundControlContext*) cc;
        bcc->SetBitmap( *frameCenterId );
        }
        
    if ( AknLayoutUtils::PenEnabled() )
        {
        CAknDialog::SetSizeAndPosition( aSize );
        }
    else
        {
        TRect applicationRect = iAvkonAppUi->ApplicationRect();    
        TRect colourSelectionDialogRect(ColourSelectionDialogRect());
    
        CCoeControl *gridCtrl = ControlOrNull(ECtrlGridType);
        if (gridCtrl) 
            {
            CAknColorSelectionGridControl *ctrl = 
                (CAknColorSelectionGridControl*)gridCtrl;
            ctrl->SetParentRects(applicationRect, colourSelectionDialogRect);
            }
        SetRect(colourSelectionDialogRect);
        }
    _AKNTRACE_FUNC_EXIT;
    }

// ----------------------------------------------------------------------------
// CAknColourSelectionGrid::ExecuteLD()
// 
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CAknColourSelectionGrid::ExecuteLD()
    {
    return(CAknDialog::ExecuteLD(iNoneExist ? R_COLOUR_SELECTION_GRID_WITH_NONE_FIELD : R_COLOUR_SELECTION_GRID_WITHOUT_NONE_FIELD));
    }

// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::OkToExitL()
// 
// -----------------------------------------------------------------------------
//
TBool CAknColourSelectionGrid::OkToExitL(TInt aButton) 
    {
	_AKNTRACE_FUNC_ENTER;
    // close the color grid: 
    // if the NGA effects are off, use “pop-up”.
    // If NGA effects are on, use “pop-up closed”.
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        if( AknLayoutUtils::PenEnabled() )
            {
            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                {
                feedback->InstantFeedback( ETouchFeedbackPopupClose );
                }
            else
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }
            }
        }

    switch (aButton)
        {
        case EAknSoftkeyInsert:
        case EEikBidOk:
            {
            TInt index = iGrid->CurrentItemIndex();

            if (iNoneBox)
                {
                *iNoneChosen = iNoneBox->IsFocused();
                }
            else
                {
                *iNoneChosen = EFalse;
                }
            *iColourChosen = iColours->At(index);
            break;
            }
        default:
            {
            break;
            }
        }
    _AKNTRACE_FUNC_EXIT;
    return ETrue;
    }

// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::PostLayoutDynInitL()
// 
// -----------------------------------------------------------------------------
//
void CAknColourSelectionGrid::PostLayoutDynInitL()
    {
    _AKNTRACE_FUNC_ENTER;
    CCoeControl* gridCtrl = Grid();
    if (gridCtrl)
        {
        CColorGrid* grid = (CColorGrid*)gridCtrl;
        grid->ItemDrawer()->FormattedCellData()->SetRespectFocus(ETrue);
        if (*iNoneChosen==EFalse)
            {
            for (TInt i=0;i<iColours->Count();i++)
                {
                if (iColours->At(i) == *iColourChosen)
                    {
                    TBool redrawDisabled = grid->GridView()->RedrawDisabled();
                    grid->GridView()->SetDisableRedraw(ETrue);                    
                    grid->SetCurrentDataIndex(i);                                        
                    grid->GridView()->SetDisableRedraw(redrawDisabled);
                    
                    break;
                    }
                }
            grid->SetFocus(ETrue);                
            }
        else
            {
            if (iNoneBox)
                {                
                iNoneBox->SetFocus(ETrue);        
                }
            else
                {
                grid->SetFocus(ETrue);                
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::CreateCustomControlL()
// 
// -----------------------------------------------------------------------------
//
SEikControlInfo CAknColourSelectionGrid::CreateCustomControlL( 
    TInt aControlType )
    {
	_AKNTRACE_FUNC_ENTER;
    // open the color grid: 
    // if the NGA effects are off, use “pop-up”.
    // If NGA effects are on, use “increasing long touch”.
    MTouchFeedback* feedback = MTouchFeedback::Instance();
    if ( feedback )
        {
        if( AknLayoutUtils::PenEnabled() )
            {
            if ( CAknTransitionUtils::TransitionsEnabled( AknTransEffect::EComponentTransitionsOff ) )
                {
                feedback->InstantFeedback( ETouchFeedbackPopupOpen );
                }
            else
                {
                feedback->InstantFeedback( ETouchFeedbackPopUp );
                }
            }
        }

    // Create the grid control. CAknDialog will CreateFromResourceL() it
    SEikControlInfo control = {NULL, 0, 0};    
    if( iNoneExist && !iNoneBox)
        {        
        iNoneBox = new (ELeave) CNoneField( 
            iAvkonAppUi->IsSingleClickCompatible() );
        iNoneBox->SetPressDownEffect( EFalse );
        if ( AknLayoutUtils::PenEnabled() )     
            {
            // Nonefield will inform selecting it with stylus via this observer interface  
            iNoneBox->SetNoneFieldObserver( this );
            }
 
        if (aControlType == EAknCtColourSelectionDialogNoneField)
            {
            // Legacy none field.
            iNoneBox->SetLegacyMode(ETrue);
            control.iControl = iNoneBox;
            control.iTrailerTextId = 0;
            control.iFlags = 0;          
            _AKNTRACE_FUNC_EXIT;
            return control;
            }
        }
    CColorGrid* grid = new (ELeave) CColorGrid;
    CCoeControl* colorSelectionGridControl;
    CleanupStack::PushL(grid);
    colorSelectionGridControl = new (ELeave) CAknColorSelectionGridControl(
        grid, iNoneBox, iAvkonAppUi->IsSingleClickCompatible() );
    CleanupStack::Pop();
    iGrid = grid;
    iGrid->SetNoneExist(iNoneExist);
    if (aControlType == EAknCtColourSelectionDialogGrid)
        {
        grid->SetLegacyMode(ETrue);
        }

    if ( AknLayoutUtils::PenEnabled() )
        {
        // ListBox informs us selectioning via this observer interface.   
        iGrid->SetListBoxObserver( this );
        }

    control.iControl = colorSelectionGridControl;
    control.iTrailerTextId = 0;
    control.iFlags = 0;          
    _AKNTRACE_FUNC_EXIT;
    return control;
    }





// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::OfferKeyEventL()
// 
// -----------------------------------------------------------------------------
//
TKeyResponse CAknColourSelectionGrid::OfferKeyEventL(
    const TKeyEvent& aKeyEvent,
    TEventCode aType) 
    {
    _AKNTRACE_FUNC_ENTER;
    if ( IsFocused() ||
        (aType == EEventKey && aKeyEvent.iCode == EKeyEscape)
        )
        {
        _AKNTRACE_FUNC_EXIT;
        return (CEikDialog::OfferKeyEventL(aKeyEvent, aType));
        }
    else
    	{
    	_AKNTRACE_FUNC_EXIT;
    	return EKeyWasNotConsumed;
    	} 
    }

// -----------------------------------------------------------------------------
// CAknColourSelectionGrid::Grid()
// 
// -----------------------------------------------------------------------------
//
CAknGrid *CAknColourSelectionGrid::Grid() const
    {
    CCoeControl *gridCtrl = ControlOrNull(ECtrlGridType);
    if (!gridCtrl) 
        {
        return NULL;
        }
    CAknColorSelectionGridControl *ctrl = (CAknColorSelectionGridControl*)gridCtrl;
    CAknGrid *grid = ctrl->Grid();
    return grid;
    }


// ---------------------------------------------------------------------------
// CAknColourSelectionGrid::ActivateL()
// ---------------------------------------------------------------------------
//
void CAknColourSelectionGrid::ActivateL()
    {
    CCoeControl::ActivateL();
    }


// ---------------------------------------------------------------------------
// CAknColourSelectionGrid::HandleListBoxEventL()
// Handles list box events.
// ---------------------------------------------------------------------------
//
void CAknColourSelectionGrid::HandleListBoxEventL( CEikListBox*  aListBox,
                                                   TListBoxEvent aEventType )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknColourSelectionGridExtension;
        }

    if ( AknLayoutUtils::PenEnabled() )
        {
        switch ( aEventType )
            {
            case MEikListBoxObserver::EEventItemClicked:
            // This event will be sent when single click is enabled    
            case MEikListBoxObserver::EEventItemSingleClicked:
                {
                _AKNTRACE( "[%s] EEventItemClicked or EEventItemSingleClicked", 
                		   __FUNCTION__ );
                if ( aListBox == iGrid && !iExtension->iIsDragged )
                    {
                    iExtension->iFlags |= ECSelGridCloseAfterDPageClicked;
                    }
                break;
                }
            case MEikListBoxObserver::EEventItemDraggingActioned:
                {
                _AKNTRACE( "[%s] EEventItemDraggingActioned",
                		   __FUNCTION__ );
                iExtension->iIsDragged = ETrue;  
                iGrid->CleanPressedDownState();
                iExtension->iFlags &= ~ECSelGridCloseAfterDPageClicked; 
                break;
                }
            case MEikListBoxObserver::EEventPenDownOnItem:
                {
                _AKNTRACE( "[%s] EEventPenDownOnItem", 
                		   __FUNCTION__ );
                iExtension->iIsDragged = EFalse;
                iGrid->SetPressedDownState();
                break;
                }
            default:
                {
                break;
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Handles pointer events
// ---------------------------------------------------------------------------
//
EXPORT_C void CAknColourSelectionGrid::HandlePointerEventL(
    const TPointerEvent& aPointerEvent )
    {
    _AKNTRACE_FUNC_ENTER;
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknColourSelectionGridExtension;
        }

    if ( !Rect().Contains( aPointerEvent.iPosition ) )
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            TryExitL( EAknSoftkeyCancel );
            _AKNTRACE_FUNC_EXIT;
            return;
            }

        if ( aPointerEvent.iType == TPointerEvent::EDrag )
            {
            iExtension->iIsDragged = ETrue;
            }
        }
    else
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
            {
            iExtension->iIsDragged = EFalse;
            }

        CAknDialog::HandlePointerEventL( aPointerEvent );
        }
    _AKNTRACE_FUNC_EXIT;
    }


// ---------------------------------------------------------------------------
// Handles tap event to the CNoneField.
// ---------------------------------------------------------------------------
//
void CAknColourSelectionGrid::HandleControlEventL( CCoeControl* aControl,
                                                   TCoeEvent aEventType )
    { 
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( iExtension &&
             aControl == iNoneBox &&
             aEventType == EEventRequestExit &&
             !iExtension->iIsDragged )
            {   
            iExtension->iFlags |= ECSelGridCloseAfterDPageClicked; 
            }  
        }
    }


// ---------------------------------------------------------------------------
// Handles closing the colour selection grid dialog after selection
// has been done by tapping. 
// ---------------------------------------------------------------------------
//
void CAknColourSelectionGrid::HandleDialogPageEventL( TInt aEventID )
    {  
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( iExtension && 
            aEventID == MEikDialogPageObserver::EDialogPageTapped && 
            iExtension->iFlags & ECSelGridCloseAfterDPageClicked )
            {        
            iExtension->iFlags = 0;
            // Exit requested, exit with ok. 
            TryExitL( EAknSoftkeyOk );
            }   
        }
    
    }
    
// End of File
