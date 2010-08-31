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
* Description:  This is a concrete class for the handling of a grid.
*                The class handles a rectangular grid arrangement of items
*                held in any linear ordering i.e. cells ordered top to
*                bottom and left, left to right and down etc.
*
*/


#include <AknGrid.h>
#include <avkon.hrh>
#include <avkon.rsg>

#include <barsread.h>

#include <AknGridView.h>
#include <AknGridM.h>
#include <eiklbm.h>
#include <eiklbi.h>
#include <eiklbx.h>

#include <eikenv.h>
#include <eiklbx.pan>
#include <eikkeys.h>

#include <AknsUtils.h>

//formatted listbox
#include <eikfrlbd.h>
#include <eikfrlb.h>

#include <AknDef.h>
#include <aknlayoutscalable_avkon.cdl.h>
#include <AknsControlContext.h>
#include "layoutmetadata.cdl.h"
#include <aknphysics.h>

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
    #include <aknlistloadertfx.h>
    #include <aknlistboxtfxinternal.h>
#endif //RD_UI_TRANSITION_EFFECTS_LIST

#include <touchfeedback.h>
#include "akntrace.h"

const TInt KDefaultLineHeightForHorizontalGrid = 10;

const TInt KEikListBoxPointerRepeatInterval = 100000;  // 0.1 seconds in micro seconds

const TInt KEikListBoxInvalidIndex = -1;

enum TGridOrientation
    {
    EGridOrientationHorizontal,
    EGridOrientationVertical
    };
enum TGridHorizontal
    {
    EGridHorizontalRightToLeft,
    EGridHorizontalLeftToRight,
    EGridHorizontalWritingDirection,
    EGridHorizontalAntiWritingDirection
    };
enum TGridVertical
    {
    EGridVerticalBottomToTop,
    EGridVerticalTopToBottom
    };


/**
* Local Panic Function and Panic Codes 
*/
enum TAknGridPanicCodes
    {
    EAknPanicGridGeneralPanic,
    EAknPanicGridModelAlreadyExists,
    EAknPanicGridInvalidNumberOfPrimaryItems,
    EAknPanicGridNoView
    };
    

enum TAknGridStateFlags
    {
    EAknGridStateButton1DownInGrid = 0x01
    };

// ================= Extension class ========================
NONSHARABLE_CLASS(CAknGridExtension) : public CBase
    {
    public:
        CAknGridExtension();
        ~CAknGridExtension();
    TInt GetScrollingSpeed( TBool aIsOverItem, TInt aItemIndex, CAknGridView& aView, 
                            const TPoint& aPoint ) const;
    

    public: // data 
        TInt iFlags;
        // EMMA-7A8B9F.Ugly hack. Prevent MopSupplyObject being invoked 
        // from CEikListBox::MopGetObject()
        TBool iIsFromBaseClass;
        TPoint iLastPoint;
        TBool iKineticScrolling;
        TBool iSingleClickEnabled;
    };

CAknGridExtension::CAknGridExtension() 
    : 
    iFlags(0), 
    iIsFromBaseClass( EFalse ),
    iLastPoint( 0, 0 ), 
    iKineticScrolling( CAknPhysics::FeatureEnabled() ),
    iSingleClickEnabled( iAvkonAppUi->IsSingleClickCompatible() )
    {
    }

CAknGridExtension::~CAknGridExtension()
    {
    }
    
TInt CAknGridExtension::GetScrollingSpeed( TBool aIsOverItem, TInt aItemIndex, 
                                           CAknGridView& aView, const TPoint& aPoint ) const
    {
    TInt itemCountInRow = aView.NumberOfColsInView();
    TInt speed = 0;
    TInt y = aPoint.iY - iLastPoint.iY;
    if ( aIsOverItem )
        {
        if ( aView.BottomItemIndex() - aItemIndex < itemCountInRow 
            &&  y> 0 )
            {
            speed = 1;
            }
        else if ( aItemIndex - aView.TopItemIndex() < itemCountInRow 
            && y < 0 )
            {
            speed = -1;
            }
        }
    else
        {
        speed = 0;
        }
    return speed;
    }
    
    
// ================= CAknGrid class ========================

GLDEF_C void Panic(TAknGridPanicCodes aPanic)
    {
    _LIT(KPanicCat,"AknGrid");
    User::Panic(KPanicCat, aPanic);
    }


EXPORT_C CAknGrid::CAknGrid()
    {
    }

EXPORT_C CAknGrid::~CAknGrid()
    {
    delete iExtension;
    }

/**
* This function must only be called before ConstructL()
*/
EXPORT_C void CAknGrid::SetModel(CAknGridM* aModel)
    {
    __ASSERT_ALWAYS(!iModel, Panic(EAknPanicGridModelAlreadyExists));
    iModel = aModel;
    }

EXPORT_C void CAknGrid::ConstructL(const CCoeControl* aParent, TInt aFlags)
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iModel)
        {
        iModel = new(ELeave) CAknGridM;
        }
    
    GridModel()->ConstructL();

    CreateItemDrawerL();
    ItemDrawer()->FormattedCellData()->SetControl(this);
    CEikListBox::ConstructL(aParent, aFlags);
    
    if ( !iExtension )
        {
        iExtension = new (ELeave) CAknGridExtension;    
        }

    // the default scrolling method is follows items
    SetPrimaryScrollingType( CAknGridView::EScrollFollowsItemsAndLoops );
    SetSecondaryScrollingType( CAknGridView::EScrollFollowsItemsAndLoops );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknGrid::ConstructFromResourceL(TResourceReader& aReader)
    {
    _AKNTRACE_FUNC_ENTER;
    RestoreCommonListBoxPropertiesL(aReader);        
    TInt requiredCellCharWidth=aReader.ReadInt16();
 
    if (!iModel)
        iModel = new(ELeave) CAknGridM;

    TInt items=aReader.ReadInt32();
    if (!items)
        {
        STATIC_CAST(CAknGridM*,iModel)->ConstructL();
        }
    else
        {
        CDesCArray* desArray=iCoeEnv->ReadDesCArrayResourceL(items);
        CleanupStack::PushL(desArray);

        STATIC_CAST(CAknGridM*,iModel)->ConstructL(desArray);
        CleanupStack::Pop( desArray );
        }
 
    CreateItemDrawerL();
    iItemDrawer->SetDrawMark(EFalse);
    ItemDrawer()->FormattedCellData()->SetControl(this);
    STATIC_CAST(CFormattedCellListBoxItemDrawer*,iItemDrawer)->SetCellWidthInChars(requiredCellCharWidth);
    CreateViewL();

    // empty text
    HBufC* emptyGridText = aReader.ReadHBufCL();
    if (emptyGridText)
        {
        CleanupStack::PushL(emptyGridText);
        SetEmptyGridTextL(*emptyGridText);
        CleanupStack::PopAndDestroy( emptyGridText );
        }

    TInt gridStyle=aReader.ReadInt32();

    TResourceReader reader;
    if (!gridStyle)
        {
        iEikonEnv->CreateResourceReaderLC(reader,R_AVKON_GRID_STYLE_DEFAULT);
        }
    else
        {
        iEikonEnv->CreateResourceReaderLC(reader,gridStyle);
        }

    SetLayoutFromResourceL(reader);
    CleanupStack::PopAndDestroy(); // reader
    
    if ( !iExtension )
        {        
        iExtension = new (ELeave) CAknGridExtension;  
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
* This routine assumes that SetLayoutL has been called to set
* up the grid.
*/
EXPORT_C void CAknGrid::SizeChanged()
    {
    _AKNTRACE_FUNC_ENTER;
    TRect clientRect = iBorder.InnerRect(Rect());

    TInt currentDataIndex = 0;
    CAknGridView* gridView = GridView();

    // reset item offset
    gridView->SetItemOffsetInPixels( 0 );

    if (iCurrentIsValid) // appshell does not call HandleItemAddition!
        {                // so this is never called. See CAknAppStyleGrid::SizeChanged()
        // remember current position
        currentDataIndex = gridView->CurrentDataIndex();
        }

    TRect rect(clientRect);
    rect.SetRect(rect.iTl.iX + ListBoxMargins().iLeft, rect.iTl.iY + ListBoxMargins().iTop,
                 rect.iBr.iX - ListBoxMargins().iRight, rect.iBr.iY - ListBoxMargins().iBottom);
    iView->SetViewRect(rect);
    _AKNTRACE( "The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   rect.iTl.iX, rect.iTl.iY, 
    		   rect.iBr.iX, rect.iBr.iY );
    TRAPD(err1, HandleViewRectSizeChangeL());
    if (err1)
        {
        if (iSBFrameOwned == ENotOwnedExternally)
            {
            delete iSBFrame;
            iSBFrame = 0;
            }
        }

    // check grid orientated to show current focus (item height
    // change may have moved the focus to a new page)
    if (iCurrentIsValid)
        {
        gridView->SetCurrentDataIndex(currentDataIndex);
        }

    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    TRgb color;
    
    TInt error = AknsUtils::GetCachedColor( skin,
                                            color,
                                            KAknsIIDQsnTextColors,
                                            EAknsCIQsnTextColorsCG11 );
    if (!error)
        {
        ItemDrawer()->SetHighlightedTextColor( color );
        }
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Protected routine used by functions to check/alter the dimensions
* of the grid as data items are added or removed or the
* size of the items are altered.
* This routine assumes that SetLayoutL has been called.
* This will not leave if scrollbars have both been turned off.
*/
EXPORT_C void CAknGrid::CalcGridSizeL()
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;

    CAknGridView* gridView = GridView();
    TSize gridSize = gridView->GridCellDimensions();

    TInt definedItems = GridModel()->IndexOfLastDataItem() + 1;

    if (definedItems > 0)
        {
        // item height determines iHeight
        if (iItemHeight < 1)
            {
            // item height must exist - so set to default value
            // for now
            CEikListBox::SetItemHeightL(KDefaultLineHeightForHorizontalGrid);
            }

        if(iOrientationFlags.IsSet(EGridOrientationVertical))
            {
            gridSize.iHeight = iNumOfRowsInView;
            gridSize.iWidth = definedItems / gridSize.iHeight; 
            if (definedItems % gridSize.iHeight)
                gridSize.iWidth++;
            }
        else
            {
            gridSize.iWidth = iNumOfColsInView;
            gridSize.iHeight = definedItems / gridSize.iWidth; 
            if (definedItems % gridSize.iWidth)
                gridSize.iHeight++;
            }
        }
    else
        {
        //no defined items so grid empty
        gridSize.iWidth = 1;
        gridSize.iHeight = 1;
        if (iOrientationFlags.IsSet(EGridOrientationVertical))
            gridSize.iHeight = iNumOfRowsInView;
        else
            gridSize.iWidth = iNumOfColsInView;
        }
    // set number of cells in grid
    gridView->SetGridCellDimensions(gridSize);
    _AKNTRACE_FUNC_EXIT;
    }


/**
* Creates a formatted list item drawer.
*/
EXPORT_C void CAknGrid::CreateItemDrawerL()
    {
    CFormattedCellListBoxData* data=CFormattedCellGridData::NewL();
    CleanupStack::PushL(data);

    data->SetControl( this );
    data->CreatePictographInterfaceL();

    iItemDrawer=new(ELeave) CFormattedCellListBoxItemDrawer(Model(), iEikonEnv->NormalFont(), data);
    CleanupStack::Pop( data );
    }

/**
* Gives the formatted list item drawer being used by the grid.
*/
EXPORT_C CFormattedCellListBoxItemDrawer* CAknGrid::ItemDrawer() const
    {
    return STATIC_CAST(CFormattedCellListBoxItemDrawer*,iItemDrawer);
    }

/**
* Informs the grid that the data in the model has altered.
* It is assumed that the grid has been initialised by a call to SetLayoutL
* before this function is called for the first time.
*/
EXPORT_C void CAknGrid::HandleItemAdditionL()
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;

    if (GridModel()->NumberOfData() <= 0)
        return;

    TInt currentDataIndex = 0;

    CAknGridView* gridView = GridView();

    if (iCurrentIsValid)
        {
        // remember current position
        currentDataIndex = gridView->CurrentDataIndex();
        }

    CalcGridSizeL();

    CEikListBox::HandleItemAdditionL();

    // check the current marker is set to the first item in the 
    // grid if it hasn't been set yet otherwise ensure current marker still
    // on cell item before new items were added. 
    if (!iCurrentIsValid)
        SetStartPositionL(PositionAtIndex(0));
    else
        gridView->SetCurrentDataIndex(currentDataIndex);

    iCurrentIsValid = ETrue;

    // redraw everything visible since all/most will have been affected
    DrawNow();
    UpdateScrollBarsL();
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Informs the  grid that the data in the model has altered.
* It is assumed that the grid has been initialised by a call to SetLayoutL
* before this function is called for the first time.
*/
EXPORT_C void CAknGrid::HandleItemRemovalL()
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;

    if (!iCurrentIsValid)
        return;

    CAknGridView* gridView = GridView();

    TInt currentDataIndex = gridView->CurrentDataIndex();

    CalcGridSizeL();

    CEikListBox::HandleItemRemovalL();

    // check if need to reposition current index since may have been
    // on one of those just deleted.
    CAknGridM* gridModel = GridModel();
    if (!gridModel->IndexContainsData(currentDataIndex))
        currentDataIndex = gridModel->IndexOfLastDataItem();

    gridView->SetCurrentDataIndex(currentDataIndex);

    // redraw everything visible since all/most will have been affected
    DrawNow();
    UpdateScrollBarsL();
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Sets the orientation of the grid, either vertical or horizontal, the
* ordering of the data and the size of the primary dimension of the
* grid.
* Note: The value for the parameter aNumOfItemsInPrimaryOrient must be
* greater than zero since this determines the number of items (be it rows
* or columns) in the primary orientation of the grid.
*/
EXPORT_C void CAknGrid::SetLayoutL(TBool aVerticalOrientation,
                                   TBool aLeftToRight,
                                   TBool aTopToBottom,
                                   TInt aNumOfItemsInPrimaryOrient,
                                   TInt aNumOfItemsInSecondaryOrient,
                                   TSize aSizeOfItems,
                                   TInt aWidthOfSpaceBetweenItems,
                                   TInt aHeightOfSpaceBetweenItems)
    {
    _AKNTRACE_FUNC_ENTER;
    TGridOrientation gridOrientation = EGridOrientationHorizontal;
    if (aVerticalOrientation)
        gridOrientation = EGridOrientationVertical;

    TGridHorizontal gridHorizontal = EGridHorizontalWritingDirection;
    if (aLeftToRight)
        gridHorizontal = EGridHorizontalLeftToRight;
    else
        gridHorizontal = EGridHorizontalRightToLeft;

    TGridVertical gridVertical = EGridVerticalBottomToTop;
    if (aTopToBottom)
        gridVertical = EGridVerticalTopToBottom;
    
    DoSetLayoutL(gridOrientation,
                 gridHorizontal,
                 gridVertical,
                 aNumOfItemsInPrimaryOrient,
                 aNumOfItemsInSecondaryOrient,
                 aSizeOfItems,
                 aWidthOfSpaceBetweenItems,
                 aHeightOfSpaceBetweenItems);
    _AKNTRACE_FUNC_EXIT;

    }

void CAknGrid::DoSetLayoutL(TInt aOrientation,
                            TInt aHorizontal,
                            TInt aVertical,
                            TInt aNumOfItemsInPrimaryOrient,
                            TInt aNumOfItemsInSecondaryOrient,
                            TSize aSizeOfItems,
                            TInt aWidthOfSpaceBetweenItems,
                            TInt aHeightOfSpaceBetweenItems)
    {
    _AKNTRACE_FUNC_ENTER;
    // this must be the first method called after the construction of
    // the grid
    __TEST_INVARIANT;

    // number of primary items must be > 0
    __ASSERT_ALWAYS((aNumOfItemsInPrimaryOrient > 0), Panic(EAknPanicGridInvalidNumberOfPrimaryItems));

    // store number of items in primary in case of SizeChange
    // never used iNumOfItemsInPrimaryOrient = aNumOfItemsInPrimaryOrient;

    iSpaceBetweenItems.iWidth = aWidthOfSpaceBetweenItems;
    iSpaceBetweenItems.iHeight = aHeightOfSpaceBetweenItems;

    iOrientationFlags.ClearAll(); 
    iHorizontalFlags.ClearAll();
    iVerticalFlags.ClearAll();
    TInt gridFlags = 0;

    switch(aOrientation)
        {
        case EGridOrientationHorizontal:
            iOrientationFlags.Set(EGridOrientationHorizontal);
            iNumOfRowsInView = aNumOfItemsInSecondaryOrient;
            iNumOfColsInView = aNumOfItemsInPrimaryOrient;
            break;
        case EGridOrientationVertical: // drop through to default
        default: // use default to keep BC with old code
            iOrientationFlags.Set(EGridOrientationVertical);
            gridFlags |= CAknGridView::EPrimaryIsVertical;
            iNumOfRowsInView = aNumOfItemsInPrimaryOrient;
            iNumOfColsInView = aNumOfItemsInSecondaryOrient;
            break;
        }

    switch(aHorizontal)
        {
        case EGridHorizontalRightToLeft:      // drop through
        case EGridHorizontalLeftToRight:      // drop through
        case EGridHorizontalWritingDirection: // drop through
        case EGridHorizontalAntiWritingDirection:
            iHorizontalFlags.Set(aHorizontal);
            break;
        default: // use default to keep BC with old code
            iHorizontalFlags.Set(EGridHorizontalWritingDirection);
            break;
        }

    TBool isMirrored = AknLayoutUtils::LayoutMirrored();
    if (isMirrored)
        {
        if (iHorizontalFlags.IsSet(EGridHorizontalAntiWritingDirection)
            || iHorizontalFlags.IsSet(EGridHorizontalLeftToRight))
            gridFlags |= CAknGridView::ELeftToRight;
        }
    else
        {
        if (iHorizontalFlags.IsSet(EGridHorizontalWritingDirection)
            || iHorizontalFlags.IsSet(EGridHorizontalLeftToRight))
            gridFlags |= CAknGridView::ELeftToRight;
        }

    switch(aVertical)
        {
        case EGridVerticalBottomToTop:
            iVerticalFlags.Set(EGridVerticalBottomToTop);
            break;
        case EGridVerticalTopToBottom: // drop through to default
        default: // use default to keep BC with old code
            iVerticalFlags.Set(EGridVerticalTopToBottom);
            gridFlags |= CAknGridView::ETopToBottom;
            break;
        }
        
    CAknGridView* gridView = GridView();

    gridView->SetSpacesBetweenItems(iSpaceBetweenItems);
    CAknGridView::SGrid gridDetails;
    // define a single cell grid size to start with - the grid will only become
    // real after we've added some data and called HandleItemAdditionL. Because
    // this method is being called when dynamic layout switch is handled we
    // cannot set gridDetails.iGridDimensions = TSize(1,1). Instead, we use the
    // grid view's value -> a fully populated grid no longer loses its
    // dimension information. Default value TSize(1,1) is now set in grid
    // view's constructor.
    gridDetails.iGridDimensions = gridView->GridCellDimensions();
    gridDetails.iGridFlags = gridFlags;
    gridDetails.iPageSize = iNumOfColsInView*iNumOfRowsInView;
    gridDetails.iColsInView = iNumOfColsInView;
    gridDetails.iRowsInView = iNumOfRowsInView;
    gridDetails.iSizeBetweenItems = iSpaceBetweenItems;
    gridDetails.iSizeOfItems = aSizeOfItems;
    CalcGridSizeL();
    gridView->SetGridDetails(gridDetails);

    gridView->SetColumnWidth(aSizeOfItems.iWidth);
    SetItemHeightL(aSizeOfItems.iHeight);
    SetItemsInSingleLine(gridDetails.iColsInView);

    // Create the scroll bars
    _AKNTRACE( "Create scroll bar" );
    CreateScrollBarFrameL(ETrue, EFalse, ETrue);
    ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
    UpdateScrollBarsL();
    _AKNTRACE_FUNC_EXIT;
    }
    
EXPORT_C void CAknGrid::HandlePointerEventL(const TPointerEvent& aPointerEvent) 
    {     
    _AKNTRACE_FUNC_ENTER;
    if ( AknLayoutUtils::PenEnabled() ) 
        {
        // Scroll bar
        // Do not use iSBFrame->VerticalScrollBar()->Rect() to test, 
        // because of iSBFrame->VerticalScrollBar owning window.
        if( iSBFrame && TRect(iSBFrame->VerticalScrollBar()->Position(), 
            iSBFrame->VerticalScrollBar()->Size()).Contains ( aPointerEvent.iPosition ))
            {
            if ( !ScrollingDisabled()
                && iExtension->iFlags & EAknGridStateButton1DownInGrid )
                {
                if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
                    {
                    iExtension->iFlags &= ~EAknGridStateButton1DownInGrid;
                    }
                CEikListBox::HandlePointerEventL( aPointerEvent );
                }
            else
                {
                CCoeControl::HandlePointerEventL( aPointerEvent );
                }
            return;
            }
        else
            {
            CAknGridView* gridView = GridView();
            TInt itemIndex = 0;
            
            TRect visibleItemsRect(gridView->ViewRect().iTl, 
                TSize(gridView->ItemSize(itemIndex).iWidth * iNumOfColsInView, 
                gridView->ItemSize(itemIndex).iHeight * iNumOfRowsInView));
        
        // switch pointer event type and set button 1 down in grid flag on and off depending where event happened.
            switch (aPointerEvent.iType)
                {
                case TPointerEvent::EButton1Down:
                    iExtension->iLastPoint = aPointerEvent.iPosition;
                    if ( visibleItemsRect.Contains(aPointerEvent.iPosition) )
                        {
                        iExtension->iFlags |= EAknGridStateButton1DownInGrid;                
                        }
                    _AKNTRACE( "TPointerEvent::EButton1Down" );
                    break;

                case TPointerEvent::EButton1Up:
                    {
                    iExtension->iFlags &= ~EAknGridStateButton1DownInGrid;
                    _AKNTRACE( "TPointerEvent::EButton1Up" );
                    break;
                    }

                default:
                    {
                    break;
                    }
                }

            CEikListBox::HandlePointerEventL( aPointerEvent ); // eventually will call CAknGrid::HandleDragEventL if dragged
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void* CAknGrid::ExtensionInterface( TUid /*aInterface*/ ) 
    { 
    return NULL;
    }

/**
* Sets the layout from a resource. Layout includes orientation 
* (either vertical or horizontal), horizontal and vertical direction 
* of numbering, the number of items in the primary and secondary
* orientation, and the primary and secondary scrolling types.
*/
EXPORT_C void CAknGrid::SetLayoutFromResourceL(TResourceReader& aReader)
    {
    _AKNTRACE_FUNC_ENTER;
    TInt layoutFlags = aReader.ReadInt16();
    TInt primaryScroll=aReader.ReadInt16();
    TInt secondaryScroll=aReader.ReadInt16();
    TInt numItemsInPrimaryOrient=aReader.ReadInt16();
    TInt numItemsInSecondaryOrient=aReader.ReadInt16();
    TInt height = aReader.ReadInt16();
    TInt width = aReader.ReadInt16();
    TInt gapWidth = aReader.ReadInt16();
    TInt gapHeight = aReader.ReadInt16();

    TGridOrientation gridOrientation = EGridOrientationHorizontal;
    if (layoutFlags & EAknGridVerticalOrientation)
        gridOrientation = EGridOrientationVertical;

    TGridHorizontal gridHorizontal = EGridHorizontalWritingDirection;
    if (layoutFlags & EAknGridLeftToRight)
        gridHorizontal = EGridHorizontalLeftToRight;
    else if (layoutFlags & EAknGridRightToLeft)
        gridHorizontal = EGridHorizontalRightToLeft;
//        else if (layoutFlags & EAknGridHorizontalAntiWritingDirection)
//                gridHorizontal = EGridHorizontalAntiWritingDirection;
    else if (layoutFlags & EAknGridLanguageSpecificHorizontalDirection)
        gridHorizontal = EGridHorizontalWritingDirection;

    TGridVertical gridVertical = EGridVerticalTopToBottom;
    if (layoutFlags & EAknGridBottomToTop)
        gridVertical = EGridVerticalBottomToTop;

    CAknGridView::TScrollingType prime = CAknGridView::EScrollFollowsItemsAndLoops;
    CAknGridView::TScrollingType second = CAknGridView::EScrollFollowsItemsAndLoops;

    switch(primaryScroll)
        {
        case EAknGridFollowsItemsAndStops:
            prime = CAknGridView::EScrollFollowsItemsAndStops;
            break;
        case EAknGridFollowsItemsAndLoops:
            prime = CAknGridView::EScrollFollowsItemsAndLoops;
            break;
        case EAknGridFollowsGrid:
            prime = CAknGridView::EScrollFollowsGrid;
            break;
        case EAknGridStops:
            prime = CAknGridView::EScrollStops;
            break;
        case EAknGridIncrementLineAndStops:
            prime = CAknGridView::EScrollIncrementLineAndStops;
            break;
        case EAknGridIncrementLineAndLoops:
            prime = CAknGridView::EScrollIncrementLineAndLoops;
            break;
        default:
            break;
        }

    switch(secondaryScroll)
        {
        case EAknGridFollowsItemsAndStops:
            second = CAknGridView::EScrollFollowsItemsAndStops;
            break;
        case EAknGridFollowsItemsAndLoops:
            second = CAknGridView::EScrollFollowsItemsAndLoops;
            break;
        case EAknGridFollowsGrid:
            second = CAknGridView::EScrollFollowsGrid;
            break;
        case EAknGridStops:
            second = CAknGridView::EScrollStops;
            break;
        case EAknGridIncrementLineAndStops:
            second = CAknGridView::EScrollIncrementLineAndStops;
            break;
        case EAknGridIncrementLineAndLoops:
            second = CAknGridView::EScrollIncrementLineAndLoops;
            break;
        default:
            break;
        }
    TSize itemSize(width,height);
    DoSetLayoutL(gridOrientation, gridHorizontal, gridVertical, numItemsInPrimaryOrient, numItemsInSecondaryOrient, itemSize, gapWidth, gapHeight);
    SetPrimaryScrollingType(prime);
    SetSecondaryScrollingType(second);
    _AKNTRACE_FUNC_EXIT;
    }


/**
* Sets the movement of the cursor with respect to scrolling when the
* end item in the current row or column, whichever is the primary
* orientation of the data items, is encountered. The movement maybe
* either stop, loop back to same row or column or move onto the
* next logical data item in the sequence.
*/
EXPORT_C void CAknGrid::SetPrimaryScrollingType(CAknGridView::TScrollingType aScrollingType)
    {
    __TEST_INVARIANT;
    GridView()->SetPrimaryScrollingType(aScrollingType);
    }

/**
* Sets the movement of the cursor with respect to scrolling when the
* end item in the secondary dimension of the grid is encountered.
* The movement maybe either stop, loop back back to same row or column
* or move onto the next logical data item in the sequence.
*/
EXPORT_C void CAknGrid::SetSecondaryScrollingType(CAknGridView::TScrollingType aSecondaryScrolling)
    {
    __TEST_INVARIANT;
    GridView()->SetSecondaryScrollingType(aSecondaryScrolling);
    }

/**
* Returns the current grid data index.
* Returns -1 if the grid is empty.
*/
EXPORT_C TInt CAknGrid::CurrentDataIndex() const
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;
    if (GridModel()->NumberOfData() < 1)
    	{
    	_AKNTRACE( "no data in model, return -1" );
    	_AKNTRACE_FUNC_EXIT;
        return -1;
    	}
    TInt startOffset = GridModel()->IndexOfFirstDataItem();
    _AKNTRACE_FUNC_EXIT;
    return (GridView()->CurrentDataIndex() - startOffset);
    }

/**
* Moves the cursor to the required grid data index.
*/
EXPORT_C void CAknGrid::SetCurrentDataIndex(TInt aDataIndex)
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;
    _AKNTRACE( "[%s] aDataIndex = %d", 
    		   __FUNCTION__, aDataIndex );
    TInt startOffset = GridModel()->IndexOfFirstDataItem();

    if (startOffset == -1)
    	{
    	_AKNTRACE_FUNC_EXIT;
        return; // there is no data yet
    	}
    TInt newIndex = aDataIndex + startOffset;

    GridView()->SetCurrentDataIndex(newIndex);
    UpdateScrollBarThumbs();
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Sets the starting position of the data within the grid.
* <p>
* Note: a blank page cannot be accessed (since cannot move into empty cells)
* so a totally blank page is the same as if the page never existed since
* the user cannot scroll into it. For this reason it is suggested that
* the start position be no more than one page into the grid.
*/
EXPORT_C void CAknGrid::SetStartPositionL(TPoint aGridStartPosition)
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;

    TInt dataIndex;
    CAknGridView* gridView = GridView();
    gridView->DataIndexFromLogicalPos(dataIndex,aGridStartPosition.iY,aGridStartPosition.iX);

    // set the number of blank start cells
    GridModel()->SetStartCells(dataIndex);

    // need to check grid size
    CalcGridSizeL();

    // check current item position
    gridView->SetCurrentDataIndex(dataIndex);
    iCurrentIsValid = ETrue;
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Gives the data index at the grid position given.
* The position must be given with respect to the top left corner
* of the grid.
* An index value of -1 is given if the grid position given is
* invalid.
*/
EXPORT_C TInt CAknGrid::IndexOfPosition(TPoint aGridPosition) const
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;

    TInt indexValue = -1;


    CAknGridView* gridView = GridView();
    TSize gridSize = gridView->GridCellDimensions();

    if ((aGridPosition.iY >= 0)&&
        (aGridPosition.iX >= 0)&&
        (aGridPosition.iX < gridSize.iWidth)&&
        (aGridPosition.iY < gridSize.iHeight))
        {
        // grid position is valid
        gridView->DataIndexFromLogicalPos(indexValue, aGridPosition.iY, aGridPosition.iX);

        indexValue -= GridModel()->IndexOfFirstDataItem();
        }
        
    _AKNTRACE_FUNC_EXIT;    
    return indexValue;
    }

/**
* Gives the position of the data item required.
* The logical position is given with respect to the top left 
* hand corner of the grid.
* A position of (-1,-1) is given if the data item is not valid.
*/
EXPORT_C TPoint CAknGrid::PositionAtIndex(TInt aItemIndex) const
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;
    _AKNTRACE(" [%s] aItemIndex = %d", 
        		  __FUNCTION__, aItemIndex );
    
    TPoint gridPosition(-1,-1);

    CAknGridM* gridModel = GridModel();

    TInt startOffset = gridModel->IndexOfFirstDataItem();
    TInt newIndex = aItemIndex + startOffset;

    if (ItemExists(newIndex))
        {
        if (gridModel->IndexContainsData(newIndex))
            {
            GridView()->
                LogicalPosFromDataIndex(newIndex, gridPosition.iY, gridPosition.iX);
            }
        }

    _AKNTRACE_FUNC_EXIT;
    return gridPosition;
    }


EXPORT_C CListBoxView* CAknGrid::MakeViewClassInstanceL() 
    {
    return (new(ELeave) CAknGridView);
    }

/**
* Sets the column width of the grid.
* Column width cannot be set in a horizontal grid since the number
* of columns in the grid is defined by the initialising call to
* SetLayoutL.
* The column width cannot be larger than the width of the viewing
* rectangle.
*/
EXPORT_C void CAknGrid::SetColumnWidth(TInt aColumnWidth)
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;
    _AKNTRACE(" [%s] aColumnWidth = %d", 
    		  __FUNCTION__, aColumnWidth );
    
    if (aColumnWidth < 1)
        return;

    TInt currentDataIndex = 0;

    CAknGridView* gridView = GridView();
    if (iCurrentIsValid)
        {
        // remember current position
        currentDataIndex = gridView->CurrentDataIndex();
        }

    // hold the users value in case needed in the method
    // HandleItemAdditionL
    iMinColWidth = aColumnWidth;

    gridView->SetColumnWidth(aColumnWidth);

    // check grid orientated to show current focus (item height
    // change may have moved the focus to a new page)
    if (iCurrentIsValid)
        gridView->SetCurrentDataIndex(currentDataIndex);
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Sets the row height of the grid.
* Row height cannot be set in a vertical grid since the number
* of rows in the grid is defined by the initialising call to
* SetLayoutL.
* The row height cannot be larger than the height of the viewing
* rectangle.
*/
EXPORT_C void CAknGrid::SetItemHeightL(TInt aHeight)
    {
    _AKNTRACE_FUNC_ENTER;
    __TEST_INVARIANT;
    _AKNTRACE(" [%s] aHeight = %d", 
    		  __FUNCTION__, aHeight );

    if (aHeight < 1)
        return;

    TInt currentDataIndex = 0;

    CAknGridView* gridView = GridView();
    if (iCurrentIsValid)
        {
        // remember current position
        currentDataIndex = gridView->CurrentDataIndex();
        }

    // this ensures that if user changes the item height then the
    // grid details will change in line as well
    iItemHeight = aHeight;

    gridView->SetItemHeight(aHeight);

    CalcGridSizeL();

    // check grid orientated to show current focus (item height
    // change may have moved the focus to a new page)
    if (iCurrentIsValid)
        gridView->SetCurrentDataIndex(currentDataIndex);
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Processes the user key events or passes them onto the underlying
* listbox code.
*/
EXPORT_C TKeyResponse CAknGrid::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    _AKNTRACE_FUNC_ENTER;
    // SERIES60 LAF
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
        
    // With single click first key event enables highlight
    if ( iExtension->iSingleClickEnabled
            && ItemDrawer()->Flags()
            &  CListItemDrawer::ESingleClickDisabledHighlight )
        {
        if ( aKeyEvent.iCode == EKeyUpArrow || 
             aKeyEvent.iCode == EKeyDownArrow ||
             aKeyEvent.iCode == EKeyLeftArrow || 
             aKeyEvent.iCode == EKeyRightArrow ||   
             aKeyEvent.iCode == EKeyEnter || 
             aKeyEvent.iCode == EKeyOK )
            {
            _AKNTRACE_FUNC_EXIT;
            return CEikListBox::OfferKeyEventL( aKeyEvent, aType );
            }
        }
    
    switch (aKeyEvent.iCode)
        {
        case EKeyUpArrow:
            iView->MoveCursorL(CListBoxView::ECursorPreviousItem, selectionMode);
            ClearMatchBuffer();
            _AKNTRACE( "EKeyUpArrow" );
            break;
        case EKeyDownArrow:
            iView->MoveCursorL(CListBoxView::ECursorNextItem, selectionMode);
            ClearMatchBuffer();
            _AKNTRACE( "EKeyDownArrow" );
            break;

        case EKeyPrevious:
            {
            const TBool disableRedraw = aKeyEvent.iRepeats;
            TBool redrawDisabled = iView->RedrawDisabled();
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(ETrue);
                }
            
            ((CAknGridView*)iView)->
                MoveCursorWithRepeatsL( EFalse, selectionMode, 1 + aKeyEvent.iRepeats );
            ClearMatchBuffer();
                
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(redrawDisabled);
                if ( !redrawDisabled )
                    {
                    DrawNow();
                    }
                }
            }
            _AKNTRACE( "EKeyPrevious" );
            break;

        case EKeyLeftArrow:
            iView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
            ClearMatchBuffer();
            _AKNTRACE( "EKeyLeftArrow" );
            break;
            
        case EKeyNext:
            {
            const TBool disableRedraw = aKeyEvent.iRepeats;
            TBool redrawDisabled = iView->RedrawDisabled();
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(ETrue);
                }

            ((CAknGridView*)iView)->
                MoveCursorWithRepeatsL( ETrue, selectionMode, 1 + aKeyEvent.iRepeats );
            ClearMatchBuffer();
                
            if ( disableRedraw )
                {
                iView->SetDisableRedraw(redrawDisabled);
                if ( !redrawDisabled )
                    {
                    DrawNow();
                    }
                }
            }
            _AKNTRACE( "EKeyNext" );
            break;

        case EKeyRightArrow:
            iView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
            ClearMatchBuffer();
            _AKNTRACE( "EKeyRightArrow" );
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

    UpdateScrollBarThumbs();

    // matcher cursor code maybe needed here if matcher cursors
    // supported in future versions, refer to CEikListBox::OfferKeyEventL

    if (iListBoxFlags & EStateChanged)
        {
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        iListBoxFlags &= (~EStateChanged);
        }

    _AKNTRACE_FUNC_EXIT;
    return EKeyWasConsumed;
    }
/**
* @return Model
*/
EXPORT_C CTextListBoxModel* CAknGrid::Model() const
    {
    return STATIC_CAST(CTextListBoxModel*,iModel);
    }

/**
* Sets the viewable rect
*/
EXPORT_C void CAknGrid::SetRect(const TRect& aRect)
    {
    _AKNTRACE_FUNC_ENTER;
    
    CCoeControl::SetRect(aRect);
        
    TRect rect(aRect);
    rect.SetRect(rect.iTl.iX + ListBoxMargins().iLeft, rect.iTl.iY + ListBoxMargins().iTop,
                 rect.iBr.iX - ListBoxMargins().iRight, rect.iBr.iY - ListBoxMargins().iBottom);
    _AKNTRACE( "The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   rect.iTl.iX, rect.iTl.iY, 
    		   rect.iBr.iX, rect.iBr.iY );
    iView->SetViewRect(rect);

    // basically, this is redundant call, but leaving it out breaks at
    // least camcorder's colorburstgrid, because SizeChanged() trusts
    // margin values
    TRAP_IGNORE( HandleViewRectSizeChangeL() );  
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Called when the view rect changes size
*/
EXPORT_C void CAknGrid::HandleViewRectSizeChangeL()
    {
    _AKNTRACE_FUNC_ENTER;
    iView->CalcBottomItemIndex();
    TInt oldTopItemIndex = TopItemIndex();// store old top item index
    TInt newTopItemIndex = oldTopItemIndex;// set new same as old

    TInt currentItemIndex = CurrentItemIndex();// get the current item index

    if (currentItemIndex < 0)// check valid
    	{
    	_AKNTRACE_FUNC_EXIT;
        return;
    	}

    iNumOfRowsInView = Max(1, iNumOfRowsInView);// make iNumOfRowsInView > 1
    iNumOfColsInView = Max(1, iNumOfColsInView);// make iNumOfColsInView > 1

    if ( iOrientationFlags.IsClear( EGridOrientationVertical )&&
         ( AknLayoutUtils::LayoutMirrored()
           ? iHorizontalFlags.IsClear( EGridHorizontalLeftToRight )
           : iHorizontalFlags.IsSet(   EGridHorizontalLeftToRight ) ) &&
         iVerticalFlags.IsSet(EGridVerticalTopToBottom) )
        {
        // CAknAppStyleGrid uses this combination of flags
        AdjustTopItemIndex();
        }
    else
        {
        // this version is likely to contain bugs.
        if (currentItemIndex != oldTopItemIndex)
            {
            TInt colIndexOfTargetItem = currentItemIndex / iNumOfRowsInView;// iNumOfRowsInView != 0
            TInt adjustment = newTopItemIndex % iNumOfRowsInView;// iNumOfRowsInView != 0
            if (adjustment != 0)
                {
                // adjust newTopItemIndex till it refers to the index of an item at the top of a column
                newTopItemIndex -= adjustment;
                }
            TInt newBottomItemIndex = newTopItemIndex + (iNumOfColsInView * iNumOfRowsInView) - 1;
            if (currentItemIndex < newTopItemIndex)
                newTopItemIndex = colIndexOfTargetItem * iNumOfRowsInView;
            else if (currentItemIndex > newBottomItemIndex)
                {
                TInt colIndexOfNewBottomItem = colIndexOfTargetItem;
                TInt colIndexOfNewTopItem = colIndexOfNewBottomItem - (iNumOfColsInView - 1);
                newTopItemIndex = colIndexOfNewTopItem * iNumOfRowsInView;
                }
            }
        else if ((newTopItemIndex != 0) && (iNumOfRowsInView != 0))
            {
            TInt adjustment = newTopItemIndex % iNumOfRowsInView;// iNumOfRowsInView != 0
            if (adjustment != 0)
                {// adjust newTopItemIndex till it refers to the index of an item at the top of a column
                newTopItemIndex -= adjustment;
                }
            }
        SetTopItemIndex(newTopItemIndex);
        }
    
    iView->CalcDataWidth();
    UpdateScrollBarsL();
    iView->CalcBottomItemIndex();
    _AKNTRACE_FUNC_EXIT;
    }

/**
* Set the empty grid text
*/
EXPORT_C void CAknGrid::SetEmptyGridTextL(const TDesC& aText)
    {
    GridView()->SetListEmptyTextL(aText);
    }

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

EXPORT_C void CAknGrid::SetTopItemIndex(TInt aItemIndex) const
    {
    __ASSERT_DEBUG(iView, Panic(EAknPanicGridNoView));
    iView->SetTopItemIndex(aItemIndex);
    }

EXPORT_C void CAknGrid::HandleResourceChange(TInt aType)
    {
    _AKNTRACE_FUNC_ENTER;
    // Need to do this to set up the scroll bar model
    TRAP_IGNORE( UpdateScrollBarsL() );
    
    if (aType==KEikDynamicLayoutVariantSwitch)
        {
        CAknGridView* gridView = GridView();
        
        gridView->SetItemOffsetInPixels( 0 );
        
        TSize sizeOfItems;
        sizeOfItems.iWidth = ( Rect().iBr.iX - Rect().iTl.iX ) / iNumOfColsInView;
        sizeOfItems.iHeight = ( Rect().iBr.iY - Rect().iTl.iY ) / iNumOfRowsInView;
        
        CAknGridView::SGrid gridDetails;
        gridDetails.iGridDimensions = gridView->GridCellDimensions();
        gridDetails.iPageSize = iNumOfColsInView*iNumOfRowsInView;

        gridDetails.iColsInView = iNumOfColsInView;
        gridDetails.iRowsInView = iNumOfRowsInView;
        gridDetails.iSizeBetweenItems = iSpaceBetweenItems;
        //gridDetails.iSizeOfItems = gridView->ItemSize();
        gridDetails.iSizeOfItems = sizeOfItems;
        
        gridView->SetColumnWidth(gridDetails.iSizeOfItems.iWidth);
        TRAP_IGNORE( SetItemHeightL(gridDetails.iSizeOfItems.iHeight) );

        gridDetails.iGridFlags = 0;
        if (iOrientationFlags.IsSet(EGridOrientationVertical))
            gridDetails.iGridFlags |= CAknGridView::EPrimaryIsVertical;
        if (iVerticalFlags.IsSet(EGridVerticalTopToBottom))
            gridDetails.iGridFlags |= CAknGridView::ETopToBottom;
        
        TBool isMirrored = AknLayoutUtils::LayoutMirrored();
        if (isMirrored)
            {
            if (iHorizontalFlags.IsSet(EGridHorizontalAntiWritingDirection)
                || iHorizontalFlags.IsSet(EGridHorizontalLeftToRight))
                gridDetails.iGridFlags |= CAknGridView::ELeftToRight;
            }
        else
            {
            if (iHorizontalFlags.IsSet(EGridHorizontalWritingDirection)
                || iHorizontalFlags.IsSet(EGridHorizontalLeftToRight))
                gridDetails.iGridFlags |= CAknGridView::ELeftToRight;
            }
        gridView->SetGridDetails(gridDetails);
              
        SetItemsInSingleLine( gridDetails.iColsInView );
        }
    
    CEikListBox::HandleResourceChange(aType);
    
    TRAP_IGNORE( ItemDrawer()->FormattedCellData()->SetupSkinContextL());
    // Data extension has animations which will change when skin changes.
    ItemDrawer()->FormattedCellData()->HandleResourceChange( aType );

    // Need to do this to set up the scroll bar model
    TRAP_IGNORE( UpdateScrollBarsL() );
    _AKNTRACE_FUNC_EXIT;
    }


EXPORT_C void CAknGrid::FocusChanged( TDrawNow aDrawNow )
    {
    _AKNTRACE_FUNC_ENTER;
    CEikListBox::FocusChanged( aDrawNow );

    // Grid data needs focus change information to control animations.
    if( IsFocused() )
        {
        ItemDrawer()->FormattedCellData()->FocusGained();
        }
    else
        {
        ItemDrawer()->FormattedCellData()->FocusLost();
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CAknGrid::ColumnWidth() const
    {
    __ASSERT_DEBUG(iView, Panic(EAknPanicGridNoView));
    return ((CAknGridView*)iView)->ColumnWidth();
    }

EXPORT_C TInt CAknGrid::HorizontalNudgeValue() const
    {
    return 1;        // scroll horizontal by one column when the left/right scroll arrows (i.e. the nudge buttons) are tapped
    }

EXPORT_C TInt CAknGrid::HorizScrollGranularityInPixels() const
    {
    return ColumnWidth(); // horiz scrollbar model set in columns for snaking list box
    }

EXPORT_C void CAknGrid::AdjustTopItemIndex() const
    {

    _AKNTRACE_FUNC_ENTER;
    /*
    * make sure, that topitemindex points to topmost leftmost visible item
    * This hackish solution is only valid for appstyle grid & similar grids
    */
     if ( iOrientationFlags.IsClear( EGridOrientationVertical )&&
          ( AknLayoutUtils::LayoutMirrored()
            ? iHorizontalFlags.IsClear( EGridHorizontalLeftToRight )
            : iHorizontalFlags.IsSet(   EGridHorizontalLeftToRight ) ) &&
         iVerticalFlags.IsSet(EGridVerticalTopToBottom) )
        {
        if ( !iNumOfColsInView )
            {  // just in case
            _AKNTRACE_FUNC_EXIT;
            return;
            }

        TPoint topIndexPoint = iView->ItemPos( TopItemIndex() );
        TInt bottomOrdinate = topIndexPoint.iY + iItemHeight;
        if ( TopItemIndex() % iNumOfColsInView == 0 
             && ( bottomOrdinate > 0
             && bottomOrdinate <= ( iView->ViewRect().iTl.iY + iItemHeight ) )
             && iView->ViewRect().Contains( iView->ItemPos( CurrentItemIndex() ) ) )
        {
        _AKNTRACE_FUNC_EXIT;
        return;
        }

        // get row of topmost item relative to the whole grid - 0 based indexing
        TInt topRow = TopItemIndex() / iNumOfColsInView;

        // get row of current item relative to the whole grid - 0 based indexing
        TInt currRow = CurrentItemIndex() / iNumOfColsInView;
        
        // top item will be col 0 in topmost row - find out new top item's row
        TInt newTopRow( topRow );  // prefer minimum adjustment
        TInt reminder = iView->ViewRect().Height() % ( iItemHeight + iSpaceBetweenItems.iHeight );
        TInt rowsFitInView = iNumOfRowsInView;
        if ( reminder > 0 )
            {
            rowsFitInView ++;
            }
        newTopRow = currRow - rowsFitInView + 1; 
        newTopRow = Max( 0, newTopRow );
        
        // and calculate new top item index
        TInt topItemIndex = newTopRow * iNumOfColsInView ;
        iView->SetItemOffsetInPixels(0);
        SetTopItemIndex(topItemIndex);
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknGrid::HandleDragEventL(TPoint aPointerPos)
    {
    _AKNTRACE_FUNC_ENTER;
    // No drag event handling if kinetic scrolling is enabled
    if ( !ScrollingDisabled() )
        {
        _AKNTRACE_FUNC_EXIT;
        return;     
        }
    
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( !(iExtension->iFlags & EAknGridStateButton1DownInGrid) )
            {
            _AKNTRACE_FUNC_EXIT;
            return;
            }

        CAknGridView* gridView = GridView();
        TRect maxRect(TPoint( KMinTInt, KMinTInt ), TPoint(KMaxTInt, KMaxTInt));
        TRect ignoreDragRect;
        TRect viewRect(gridView->ViewRect());
        TInt itemIndex = KEikListBoxInvalidIndex ;
        TBool pointerIsOverAnItem = gridView->XYPosToItemIndex(aPointerPos, itemIndex);
        // SERIES60 LAF
        CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
        //        CListBoxView::TSelectionMode selectionMode = (iListBoxFlags & EMultipleSelection) ? CListBoxView::EContiguousSelection : CListBoxView::ESingleSelection;
        // END OF SERIES60 LAF
        TInt speed = iExtension->GetScrollingSpeed( pointerIsOverAnItem, itemIndex, 
                                                    *gridView, aPointerPos );
        
        TInt oldCurrentItemIndex = CurrentItemIndex();
        TRect currentItemRect(gridView->ItemPos(oldCurrentItemIndex), gridView->ItemSize(oldCurrentItemIndex));       
        TInt numOfRows =  Max(GridView()->GridCellDimensions().iHeight,1);
        const TInt placesInGrid = numOfRows * iNumOfColsInView;   
        TBool currItemIsInLastRow = ((placesInGrid - iNumOfColsInView) <= itemIndex) && (placesInGrid > itemIndex); 
        TBool currItemIsInFirstRow = itemIndex >= iNumOfColsInView;
            
        TRect visibleItemsRect(viewRect.iTl, 
                               TPoint(gridView->ItemSize(itemIndex).iWidth * iNumOfColsInView, 
                                      gridView->ItemSize(itemIndex).iHeight * iNumOfRowsInView));   

        if ( speed != 0 )
            {
            TInt itemCountInRow = iNumOfColsInView;
            TInt dest = itemIndex + speed * itemCountInRow;
            TInt offset = 0;
            TInt newTopIndex = dest / itemCountInRow * itemCountInRow;
            TInt upperBound = iModel->NumberOfItems() - 1;
            
            if ( speed > 0 )
                {

                if ( gridView->ActualDataIndex( dest ) <= upperBound )
                    {
                    offset = -itemCountInRow;
                    }
                else
                    {
                    dest = gridView->ListBoxIndex( upperBound );
                    offset = itemIndex - dest; // Don't make focus jump.
                    }
                newTopIndex -= ( iNumOfRowsInView - 1) * itemCountInRow ;
                }
            else if ( speed < 0 )
                {
                if ( dest > 0 )
                    {
                    offset = itemCountInRow;
                    }
                else
                    {
                    offset = itemIndex - dest;
                    newTopIndex = 0;
                    }
                }

            if ((iListBoxFlags & ES60StyleMarkable) && 
                ( (EventModifiers() & EModifierShift) ||
                  (EventModifiers() & EModifierCtrl) ))
                {
                selectionMode = CListBoxView::EPenMultiselection;
                iListBoxFlags |= EStateChanged;
                }
            TInt oldtop = gridView->TopItemIndex();
            if ( !gridView->ItemIsVisible( dest ))
                {
                gridView->VScrollTo( newTopIndex );
                UpdateScrollBarThumbs();
                if ( pointerIsOverAnItem )
                    {
                    Window().RequestPointerRepeatEvent( 
                        KEikListBoxPointerRepeatInterval, viewRect );
                    }
                }
            itemIndex = dest + offset;
            }
                
                              
        // if pointer is over some new item. 
        if ( pointerIsOverAnItem )
            {
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
            MAknListBoxTfxInternal* transApi = CAknListLoader::TfxApiInternal(
                                                iView->ItemDrawer()->Gc() );
            if ( transApi && !transApi->EffectsDisabled() )
                {
                transApi->SetMoveType( itemIndex < oldCurrentItemIndex ?
                                       MAknListBoxTfxInternal::EListMoveUp :
                                       MAknListBoxTfxInternal::EListMoveDown );
                }
#endif
            if ((iListBoxFlags & ES60StyleMarkable) && 
                    ( (EventModifiers() & EModifierShift) ||
                    (EventModifiers() & EModifierCtrl) ))
                {
                selectionMode = CListBoxView::EPenMultiselection;
                iListBoxFlags |= EStateChanged;
                }            
            
            gridView->MoveToItemIndexL(itemIndex, selectionMode);
            }     
        else if ((aPointerPos.iY < visibleItemsRect.iTl.iY) && 
                    (aPointerPos.iX > visibleItemsRect.iTl.iX) && 
                    (aPointerPos.iX < visibleItemsRect.iBr.iX) &&
                     !currItemIsInFirstRow) // Dragged upwards from the grid.               
            {
            ignoreDragRect = TRect(maxRect.iTl, TPoint(maxRect.iBr.iX, visibleItemsRect.iTl.iY));

            MoveToNextOrPreviousItemL(aPointerPos);                 
            
            if ( (iListBoxFlags & ES60StyleMarkable) && 
                ( (EventModifiers() & EModifierShift) ||
                  (EventModifiers() & EModifierCtrl) ))
                {
                iView->UpdateSelectionL(CListBoxView::EPenMultiselection);          
                iListBoxFlags |= EStateChanged;
                }  
                            
            UpdateScrollBarThumbs();
            
            Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
            }     
        else if (aPointerPos.iY > visibleItemsRect.iBr.iY && 
                    (aPointerPos.iX > visibleItemsRect.iTl.iX) && 
                    (aPointerPos.iX < visibleItemsRect.iBr.iX) &&
                     !currItemIsInLastRow) // Dragged downwards from the grid.         
            {        
            ignoreDragRect = TRect(TPoint( maxRect.iTl.iX, visibleItemsRect.iBr.iY), maxRect.iBr );

            MoveToNextOrPreviousItemL(aPointerPos);                
            
            if ( (iListBoxFlags & ES60StyleMarkable) && 
                    ( (EventModifiers() & EModifierShift) ||
                      (EventModifiers() & EModifierCtrl) ))
                {
                iView->UpdateSelectionL(CListBoxView::EPenMultiselection);          
                iListBoxFlags |= EStateChanged;
                }
                
            UpdateScrollBarThumbs();
            
            Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
            }       
            
        if (CurrentItemIndex() != oldCurrentItemIndex)
            {
            ReportListBoxEventL(MEikListBoxObserver::EEventItemDraggingActioned);
            iListBoxFlags |= EStateChanged;
            if (IsMatchBuffer())
                {
                ClearMatchBuffer();
                DrawMatcherCursor();
                }
            }
        }
    else
        {
        if (!(iListBoxFlags & ELeftDownInViewRect))
        	{
        	_AKNTRACE_FUNC_EXIT;
            return;
        	}

        CAknGridView* gridView = GridView();
        const TInt clickableBorder = 20; // distance in pixels of area around grid that can see pointer events.
        TRect ignoreDragRect(TPoint(aPointerPos.iX-clickableBorder, aPointerPos.iY-clickableBorder), TPoint(aPointerPos.iX+clickableBorder, aPointerPos.iY+clickableBorder));
        TRect viewRect(gridView->ViewRect());
        TInt itemIndex;
        TBool pointerIsOverAnItem = gridView->XYPosToItemIndex(aPointerPos, itemIndex);
        // SERIES60 LAF
        CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
    //        CListBoxView::TSelectionMode selectionMode = (iListBoxFlags & EMultipleSelection) ? CListBoxView::EContiguousSelection : CListBoxView::ESingleSelection;
        // END OF SERIES60 LAF

        TInt oldCurrentItemIndex = CurrentItemIndex();
        TRect currentItemRect(gridView->ItemPos(oldCurrentItemIndex), gridView->ItemSize(oldCurrentItemIndex));
        if (pointerIsOverAnItem)
            {
            gridView->MoveToItemIndexL(itemIndex, selectionMode);
            }
        else if ((aPointerPos.iX < viewRect.iTl.iX) || (aPointerPos.iX > viewRect.iBr.iX))
            {
            // drag event occurred outside the listbox's viewRect
            if (aPointerPos.iX < viewRect.iTl.iX)
                gridView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
            else if (aPointerPos.iX > viewRect.iBr.iX)
                gridView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
            MoveToNextOrPreviousItemL(aPointerPos);                
            UpdateScrollBarThumbs();
            Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
            }
        else
            {
            // find item nearest to the pointer pos and make that the current item
            if (viewRect.Contains(aPointerPos))
                {
                }
            else
                {
                if (aPointerPos.iX > currentItemRect.iBr.iX)
                    gridView->MoveCursorL(CListBoxView::ECursorNextColumn, selectionMode);
                else if (aPointerPos.iX < currentItemRect.iTl.iX)
                    gridView->MoveCursorL(CListBoxView::ECursorPreviousColumn, selectionMode);
                MoveToNextOrPreviousItemL(aPointerPos);
                UpdateScrollBarThumbs();
                Window().RequestPointerRepeatEvent(KEikListBoxPointerRepeatInterval, ignoreDragRect);
                }
            }
        if (CurrentItemIndex() != oldCurrentItemIndex)
            {
            iListBoxFlags |= EStateChanged;
            if (IsMatchBuffer())
                {
                ClearMatchBuffer();
                DrawMatcherCursor();
                }
            }
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknGrid::RestoreClientRectFromViewRect(TRect& aClientRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    aClientRect=iView->ViewRect();
    aClientRect.SetRect(aClientRect.iTl.iX - ListBoxMargins().iLeft, aClientRect.iTl.iY - ListBoxMargins().iTop,
                        aClientRect.iBr.iX + ListBoxMargins().iRight, aClientRect.iBr.iY + ListBoxMargins().iBottom);
    if (!ViewRectHeightAdjustment())
    	{
    	_AKNTRACE_FUNC_EXIT;
        return;
    	}
    aClientRect.iBr.iY += ViewRectHeightAdjustment();
    _AKNTRACE( "The rect of grid are ( %d, %d ) ( %d, %d )", 
    		   aClientRect.iTl.iX, aClientRect.iTl.iY, 
    		   aClientRect.iBr.iX, aClientRect.iBr.iY );
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CAknGrid::AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const
    {
    _AKNTRACE_FUNC_ENTER;
    TInt remainder = aRect.Height() % (iItemHeight + iSpaceBetweenItems.iHeight);
    if (remainder >= iItemHeight)
        remainder -= iItemHeight;
    if (remainder != 0) 
        aRect.iBr.iY -= remainder;
    _AKNTRACE_FUNC_EXIT;
    return remainder;
    }

EXPORT_C void CAknGrid::MoveToNextOrPreviousItemL(TPoint aPointerPos)
    {
    _AKNTRACE_FUNC_ENTER;
    // SERIES60 LAF
    CListBoxView::TSelectionMode selectionMode = CListBoxView::ENoSelection;
//        CListBoxView::TSelectionMode selectionMode = (iListBoxFlags & EMultipleSelection) ? CListBoxView::EContiguousSelection : CListBoxView::ESingleSelection;
    // END OF SERIES60 LAF

    TInt cix = CurrentItemIndex();
    TRect currentItemRect(iView->ItemPos(cix), iView->ItemSize(cix));
    TInt numOfRows =  Max(GridView()->GridCellDimensions().iHeight,1);
    
    TBool currItemIsInLastRow;
    TBool currItemIsInFirstRow;
    
    if ( AknLayoutUtils::PenEnabled() )  
        {
        const TInt placesInGrid = numOfRows * iNumOfColsInView;    
    
        // calculate is the item in first or last row. 
        currItemIsInLastRow = ((placesInGrid - iNumOfColsInView) <= cix) && (placesInGrid > cix);    
        currItemIsInFirstRow = (cix >= 0 && cix < iNumOfColsInView);
        }
    else
        {
        currItemIsInLastRow = ((cix % numOfRows) == (numOfRows-1));
        currItemIsInFirstRow = ((cix % numOfRows) == 0);
        }

    TBool currItemIsLastItem = (cix == (iModel->NumberOfItems()-1));

    if ((aPointerPos.iY > currentItemRect.iBr.iY) && (! (currItemIsInLastRow || currItemIsLastItem)))
        {
        iView->MoveCursorL(CListBoxView::ECursorNextItem, selectionMode);
        }
    else if ((aPointerPos.iY < currentItemRect.iTl.iY) && (! currItemIsInFirstRow))
        {
        iView->MoveCursorL(CListBoxView::ECursorPreviousItem, selectionMode);
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknGrid::UpdateScrollBarsL()
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iSBFrame)
    	{
    	_AKNTRACE_FUNC_EXIT;
        return;
    	}
    TEikScrollBarModel hSbarModel;
    TEikScrollBarModel vSbarModel;
    CAknGridView* gridView = GridView();
    TRect rect=gridView->ViewRect();
    if (!(iListBoxFlags & EScrollBarSizeExcluded))
        {
        // Ignore scrollbars presence to set the model, Scrollbar Frame will change it as required
        rect = iBorder.InnerRect(Rect());
        rect.SetRect(rect.iTl.iX + ListBoxMargins().iLeft, rect.iTl.iY + ListBoxMargins().iTop,
                     rect.iBr.iX - ListBoxMargins().iRight, rect.iBr.iY - ListBoxMargins().iBottom);
        AdjustRectHeightToWholeNumberOfItems(rect);
        // rect is now viewRect when ignoring scrollbars
        }
    if (iSBFrame->VScrollBarVisibility()!=CEikScrollBarFrame::EOff)
        {
        TInt currentIndex = CurrentItemIndex();
        if (currentIndex < 0)
        	{
        	_AKNTRACE_FUNC_EXIT;
            return; // current item is not defined
        	}
        TInt row = 0;
        TInt col = 0;
        gridView->LogicalPosFromListBoxIndex(currentIndex, row, col);
        row *= iView->ItemHeight();
        row -= iView->ItemOffsetInPixels();

        TSize gridSize = gridView->GridCellDimensions();
        gridSize.iHeight = Max(gridSize.iHeight,1);//check gridSize != 0

        vSbarModel.iThumbPosition = row;
        // EHXA-7AQ8N4. Only set it to 0 can make scrollbar empty.
        vSbarModel.iScrollSpan = GridModel()->NumberOfItems() >0 ? 
            gridSize.iHeight : 0;
        vSbarModel.iThumbSpan = gridView->NumberOfRowsInView();
        vSbarModel.iScrollSpan = GridModel()->NumberOfItems() >0 ? 
            gridSize.iHeight*iView->ItemHeight() : 0;
        vSbarModel.iThumbSpan = rect.Height();

        if (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
            {
            TInt topRow = 0;
            TInt topCol = 0;
            gridView->LogicalPosFromListBoxIndex(TopItemIndex(), topRow, topCol);
            topRow *= iView->ItemHeight();
            topRow -= iView->ItemOffsetInPixels();
            vSbarModel.iThumbPosition = topRow;
            }
        if (vSbarModel.iScrollSpan-vSbarModel.iThumbPosition<vSbarModel.iThumbSpan)
            {
            vSbarModel.iThumbPosition=Max(0,vSbarModel.iScrollSpan-vSbarModel.iThumbSpan);
            gridView->MoveToItemIndexL(currentIndex,CListBoxView::ENoSelection); // force a scroll if neccessary
            }
        }
    if (iSBFrame->ScrollBarVisibility(CEikScrollBar::EHorizontal)!=CEikScrollBarFrame::EOff)
        {
        GridView()->CalcDataWidth();
        hSbarModel.iThumbPosition = gridView->HScrollOffset();
        hSbarModel.iScrollSpan = gridView->DataWidth();
        }
    
    if (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EDoubleSpan)
        {
        //same scrollbar data within landscape & portraid
        TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation() ? 1: 0;
        TAknWindowComponentLayout layout = TAknWindowComponentLayout::Compose( 
            AknLayoutScalable_Avkon::listscroll_app_pane(0),  
            AknLayoutScalable_Avkon::scroll_pane_cp15(varietyIndex));
            
        CEikAppUi* appUi = iEikonEnv->EikAppUi();
        TRect clientRect = appUi->ClientRect();      
        TRect mainPaneRect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, mainPaneRect);

        TRect scrollBarParent = TRect( TPoint(0, 0), mainPaneRect.Size());
        AknLayoutUtils::LayoutVerticalScrollBar(iSBFrame, scrollBarParent, layout.LayoutLine());
        

        TRect inclusiveRect=Rect();
        
        TEikScrollBarFrameLayout layoutSB;
        layoutSB.SetClientMargin(0);
        layoutSB.SetInclusiveMargin(0);
        layoutSB.iTilingMode=TEikScrollBarFrameLayout::EInclusiveRectConstant;
        
        iSBFrame->Tile(&hSbarModel, &vSbarModel );
        }
    else
        {
        TRect clientRect;
        RestoreClientRectFromViewRect(clientRect);
        TRect inclusiveRect=Rect();
        TEikScrollBarFrameLayout layout;
        CreateScrollBarFrameLayout(layout);
        TBool sizeChanged=iSBFrame->TileL(&hSbarModel, &vSbarModel, clientRect, inclusiveRect, layout);
        if (!sizeChanged)
        	{
        	_AKNTRACE_FUNC_EXIT;
            return;
        	}
        // else size of client/inclusive rect has changed
        if (layout.iTilingMode==TEikScrollBarFrameLayout::EClientRectConstant)
            SetSizeWithoutNotification(inclusiveRect.Size());
        else
            {
            SetViewRectFromClientRect(clientRect);
            ClearMargins();
            }        
        }
    AdjustTopItemIndex();
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C void CAknGrid::UpdateScrollBarThumbs() const
    {
    _AKNTRACE_FUNC_ENTER;
    if (!iSBFrame)
    	{
    	_AKNTRACE_FUNC_EXIT;
        return;
    	}
    CAknGridView* gridView = GridView();
    TInt currentDataIndex = gridView->CurrentDataIndex();
    TInt row = 0;
    TInt col = 0;
    gridView->LogicalPosFromDataIndex(currentDataIndex, row, col);
    iSBFrame->MoveHorizThumbTo(col);
    if (iSBFrame->TypeOfVScrollBar() == CEikScrollBarFrame::EArrowHead)
        {
        iSBFrame->MoveVertThumbTo(row);
        iSBFrame->DrawScrollBarsNow(); 
        }
    else
        {
        TInt topRow = 0;
        TInt topCol = 0;
        gridView->LogicalPosFromListBoxIndex(TopItemIndex(), topRow, topCol);
        topRow *= iView->ItemHeight();
        topRow -= iView->ItemOffsetInPixels();
        iSBFrame->MoveVertThumbTo(topRow);
        }
    _AKNTRACE_FUNC_EXIT;
    }

EXPORT_C TInt CAknGrid::CountComponentControls() const
    {
    if (GridModel()->NumberOfItems()<=0) return 0;
    return CEikListBox::CountComponentControls();
    }


// debug only invariant function
EXPORT_C void CAknGrid::__DbgTestInvariant() const          
    {
#if defined(_DEBUG)
    TBool invalid = EFalse;

    if ( !iModel )
        {
        invalid = ETrue;
        }

    if ( !iView )
        {
        invalid = ETrue;
        }

    if ( invalid )
        {
        User::Invariant();
        }
#endif
    }

EXPORT_C TAny*  CAknGrid::MListBoxModel_Reserved() 
    {
    return NULL;
    }


//----------------------------------------------------------------------------
// Handles scroll events received from the scroll bar.
// Function reads thumb position from model and updates view by these values.
// One thumb step is actually one row in list, not item in list. 
//----------------------------------------------------------------------------
//
EXPORT_C void CAknGrid::HandleScrollEventL( CEikScrollBar* aScrollBar,
                                            TEikScrollEvent aEventType ) 
    {
    _AKNTRACE_FUNC_ENTER;
    if ( AknLayoutUtils::PenEnabled() )
        {
        // Read values from model.
        TInt oldThumbPos = iView->TopItemIndex() / iNumOfColsInView * iView->ItemHeight() - iView->ItemOffsetInPixels();
        TInt newThumbPos = aScrollBar->ThumbPosition();
        TInt pageSize = aScrollBar->Model()->iThumbSpan;
        TInt maxThumbPos = aScrollBar->Model()->MaxThumbPos();
        TBool update = EFalse;

        switch ( aEventType & KEikScrollEventBarMask )
            { 
            case KEikScrollEventFromHBar:
                {
                switch ( aEventType )
                    {
                    case EEikScrollLeft:
                        {
                        newThumbPos -= HorizontalNudgeValue();
                        break;
                        }
                        
                    case EEikScrollRight:
                        {
                        newThumbPos += HorizontalNudgeValue();
                        break;
                        }
                        
                    case EEikScrollPageLeft:
                        {
                        newThumbPos -= pageSize;
                        break;
                        }
                        
                    case EEikScrollPageRight:
                        {
                        newThumbPos += pageSize;
                        break;
                        }
                        
                    case EEikScrollThumbDragVert:
                        {
                        // In the case of drag events, the scrollbar
                        // automatically updates its thumb pos...
                        SuspendEffects( ETrue );
                        break;
                        }
                        
                    case EEikScrollThumbReleaseVert:
                        {
                        // In the case of drag events, the scrollbar
                        // automatically updates its thumb pos...
                        SuspendEffects( EFalse );
                        break;
                        }
                        
                    default:
                        {
                        // Do nothing
                        break;
                        }
                    }
                    
                newThumbPos = Max( 0, Min( newThumbPos, maxThumbPos ) );
                
                if ( aEventType != EEikScrollThumbDragHoriz )
                    {               
                    iView->HScroll( newThumbPos - oldThumbPos );
                    aScrollBar->SetModelThumbPosition( iView->HScrollOffset() );
                    }
                break;
                }
                
            case KEikScrollEventFromVBar:
                {
                switch ( aEventType )
                    {
                    case EEikScrollUp:
                        {
                        if ( oldThumbPos == 0 && (iListBoxFlags & ELoopScrolling) )
                            {
                            // move thumb to downmost site if current is upmost
                            newThumbPos = maxThumbPos;
                            update = ETrue;
                            }
                        break;
                        }
                        
                    case EEikScrollDown:
                        {
                        if ( oldThumbPos == maxThumbPos && (iListBoxFlags & ELoopScrolling) )
                            {
                            // move thumb to upmost site if current is downmost
                            newThumbPos = 0;
                            update = ETrue;
                            }
                        break;
                        }
                        
                    case EEikScrollThumbDragVert:
                        {
                        SuspendEffects( ETrue );
                        break;
                        }
                        
                    case EEikScrollThumbReleaseVert:
                        {
                        SuspendEffects( EFalse );
                        break;
                        }
                        
                    default:
                        {
                        // Do nothing
                        break;
                        }
                    }
                    
#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                MAknListBoxTfxInternal* transApi =
                    CAknListLoader::TfxApiInternal(
                        iView->ItemDrawer()->Gc() );
                TBool effects = newThumbPos != oldThumbPos &&
                                    transApi && !transApi->EffectsDisabled();
                if ( effects )
                    {
                    transApi->SetMoveType( newThumbPos < oldThumbPos ?
                                    MAknListBoxTfxInternal::EListScrollUp :
                                    MAknListBoxTfxInternal::EListScrollDown );
                    }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
 
                if ( iExtension && !ScrollingDisabled() )
                    {
                    HandlePhysicsScrollEventL( newThumbPos - oldThumbPos );
                    }
                else
                    {
                    // Do normal scrolling if physics are not enabled.
                    iView->VScrollTo( newThumbPos/iView->ItemHeight() * iNumOfColsInView );
                    }

#ifdef RD_UI_TRANSITION_EFFECTS_LIST
                if ( effects )
                    {
                    transApi->Draw( Rect() );
                    }
#endif // RD_UI_TRANSITION_EFFECTS_LIST
                
                // If event has changed thumb position to different than in
                // model do by default, then update scroll bar to
                // correct values. 
                if ( update )
                    {               
                    aScrollBar->SetModelThumbPosition(
                        iView->TopItemIndex() / iNumOfColsInView*iView->ItemHeight() - iView->ItemOffsetInPixels() );
                    
                    UpdateScrollBarThumbs();
                    }
                else
                    {
                    aScrollBar->DrawNow();                      
                    }
                }
            
            default:
                {
                // Do nothing
                break;
                }
            }
        }
    else
        {
        CEikListBox::HandleScrollEventL( aScrollBar, aEventType );
        }   
    _AKNTRACE_FUNC_EXIT;
    } 


EXPORT_C TTypeUid::Ptr CAknGrid::MopSupplyObject(TTypeUid aId)
    {
    if ( iExtension && iExtension->iIsFromBaseClass )
        {
        iExtension->iIsFromBaseClass = EFalse;
        return CEikListBox::MopSupplyObject( aId );
        }

    if (  iExtension && aId.iUid == MAknsControlContext::ETypeId )
        {
        MAknsControlContext* cc = NULL;
        iExtension->iIsFromBaseClass = ETrue;
        if ( !CEikListBox::MopGetObject( cc ))
            {
            cc = ItemDrawer()->FormattedCellData()->SkinBackgroundContext();
            }
        return MAknsControlContext::SupplyMopObject( aId, cc);
        }
    return CEikListBox::MopSupplyObject( aId );
    } 
