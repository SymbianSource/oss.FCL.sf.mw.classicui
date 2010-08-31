/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test grids_api
*
*/


/*
 *  [INCLUDE FILES]
 */
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include "testsdkgrids.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctestsdkgrids::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKGrids::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctestsdkgrids::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKGrids::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  

        /*
         * akncolourselectiongrid.h
         */
        ENTRY( "TestGridsCCSGNewL", CTestSDKGrids::TestGridsCCSGNewL ),
        ENTRY( "TestGridsCCSGExecuteLD", CTestSDKGrids::TestGridsCCSGExecuteLD ),
        ENTRY( "TestGridsCCSGDelete", CTestSDKGrids::TestGridsCCSGDelete ),
        ENTRY( "TestGridsCCSGHandlePointerEventL",
            CTestSDKGrids::TestGridsCCSGHandlePointerEventL ),

        /*
         * AknGMSStlyeGrid.h 
         *class CAknGMSStyleGridView
         */
        ENTRY( "TestGridsGMSSGVConstuctionL", CTestSDKGrids::TestGridsGMSSGVConstuctionL ),
        ENTRY( "TestGridsGMSSGVDrawL", CTestSDKGrids::TestGridsGMSSGVDrawL ),
        ENTRY( "TestGridsGMSSGVSetupLayoutL", CTestSDKGrids::TestGridsGMSSGVSetupLayoutL ),
        /*
         * class CAknGMSStyleGrid
         */
        ENTRY( "TestGridsGMSSGNewL", CTestSDKGrids::TestGridsGMSSGNewL ),
        ENTRY( "TestGridsGMSSGConstructionL", CTestSDKGrids::TestGridsGMSSGConstructionL ),
        ENTRY( "TestGridsGMSSGConstructionWithTBoolL",
            CTestSDKGrids::TestGridsGMSSGConstructionWithTBoolL ),
        ENTRY( "TestGridsGMSSGConstructL", CTestSDKGrids::TestGridsGMSSGConstructL ),
        ENTRY( "TestGridsGMSSGDelete", CTestSDKGrids::TestGridsGMSSGDelete ),
        ENTRY( "TestGridsGMSSGSetupLayout", CTestSDKGrids::TestGridsGMSSGSetupLayout ),
        ENTRY( "TestGridsGMSSGHandlePointerEventL",
            CTestSDKGrids::TestGridsGMSSGHandlePointerEventL ),
        ENTRY( "TestGridsGMSSGSizeChanged", CTestSDKGrids::TestGridsGMSSGSizeChanged ),
        ENTRY( "TestGridsGMSSGMinimumSize", CTestSDKGrids::TestGridsGMSSGMinimumSize ),
        ENTRY( "TestGridsGMSSGOfferKeyEventL", CTestSDKGrids::TestGridsGMSSGOfferKeyEventL ),
        ENTRY( "TestGridsGMSSGDraw", CTestSDKGrids::TestGridsGMSSGDraw ),
        ENTRY( "TestGridsGMSSGMakeViewClassInstanceL",
            CTestSDKGrids::TestGridsGMSSGMakeViewClassInstanceL ),
        /*
         * class CAknGMSPopupGrid
         */
        ENTRY( "TestGridsGMSPGNewL", CTestSDKGrids::TestGridsGMSPGNewL ),
        ENTRY( "TestGridsGMSPGSetupWindowLayoutL", CTestSDKGrids::TestGridsGMSPGSetupWindowLayoutL ),
        ENTRY( "TestGridsGMSPGCalcPopupGridLargeGraphicWindowL",
            CTestSDKGrids::TestGridsGMSPGCalcPopupGridLargeGraphicWindowL ),
        ENTRY( "TestGridsGMSPGSetupPopupGridLargeGraphicWindowL",
            CTestSDKGrids::TestGridsGMSPGSetupPopupGridLargeGraphicWindowL ),
        ENTRY( "TestGridsGMSPGPopupGridLargeGraphicGraphicsL",
            CTestSDKGrids::TestGridsGMSPGPopupGridLargeGraphicGraphicsL ),
        ENTRY( "TestGridsGMSPGHandlePointerEventL", CTestSDKGrids::TestGridsGMSPGHandlePointerEventL ),
        
        /*
         * akngrid.h
         */
        ENTRY( "TestGridsGridConstructionL", CTestSDKGrids::TestGridsGridConstructionL ),
        ENTRY( "TestGridsGridDelete", CTestSDKGrids::TestGridsGridDelete ),
        ENTRY( "TestGridsGridSetModelL", CTestSDKGrids::TestGridsGridSetModelL ),
        ENTRY( "TestGridsGridConstructL", CTestSDKGrids::TestGridsGridConstructL ),
        ENTRY( "TestGridsGridConstructFromResourceL",
            CTestSDKGrids::TestGridsGridConstructFromResourceL ),
        ENTRY( "TestGridsGridSetLayoutL", CTestSDKGrids::TestGridsGridSetLayoutL ),
        ENTRY( "TestGridsGridSetLayoutFromResourceL",
            CTestSDKGrids::TestGridsGridSetLayoutFromResourceL ),
        ENTRY( "TestGridsGridSetPrimaryScrollingType",
            CTestSDKGrids::TestGridsGridSetPrimaryScrollingType ),
        ENTRY( "TestGridsGridSetSecondaryScrollingType",
            CTestSDKGrids::TestGridsGridSetSecondaryScrollingType ),
        ENTRY( "TestGridsGridSetStartPositionL", CTestSDKGrids::TestGridsGridSetStartPositionL ),
        ENTRY( "TestGridsGridCurrentDataIndex", CTestSDKGrids::TestGridsGridCurrentDataIndex ),
        ENTRY( "TestGridsGridSetCurrentDataIndex", CTestSDKGrids::TestGridsGridSetCurrentDataIndex ),
        ENTRY( "TestGridsGridIndexOfPosition", CTestSDKGrids::TestGridsGridIndexOfPosition ),
        ENTRY( "TestGridsGridPositionAtIndex", CTestSDKGrids::TestGridsGridPositionAtIndex ),
        ENTRY( "TestGridsGridItemDrawer", CTestSDKGrids::TestGridsGridItemDrawer ),
        ENTRY( "TestGridsGridSetEmptyGridTextL", CTestSDKGrids::TestGridsGridSetEmptyGridTextL ),
        ENTRY( "TestGridsGridEmptyGridText", CTestSDKGrids::TestGridsGridEmptyGridText ),
        ENTRY( "TestGridsGridMakeViewClassInstanceL",
            CTestSDKGrids::TestGridsGridMakeViewClassInstanceL ),
        ENTRY( "TestGridsGridSetColumnWidth", CTestSDKGrids::TestGridsGridSetColumnWidth ),
        ENTRY( "TestGridsGridColumnWidth", CTestSDKGrids::TestGridsGridColumnWidth ),
        ENTRY( "TestGridsGridUpdateScrollBarsL", CTestSDKGrids::TestGridsGridUpdateScrollBarsL ),
        ENTRY( "TestGridsGridHandleItemAdditionL", CTestSDKGrids::TestGridsGridHandleItemAdditionL ),
        ENTRY( "TestGridsGridHandleItemRemovalL", CTestSDKGrids::TestGridsGridHandleItemRemovalL ),
        ENTRY( "TestGridsGridOfferKeyEventL", CTestSDKGrids::TestGridsGridOfferKeyEventL ),
        ENTRY( "TestGridsGridSetItemHeightL", CTestSDKGrids::TestGridsGridSetItemHeightL ),
        ENTRY( "TestGridsGridSizeChanged", CTestSDKGrids::TestGridsGridSizeChanged ),
        ENTRY( "TestGridsGridModel", CTestSDKGrids::TestGridsGridModel ),
        ENTRY( "TestGridsGridSetRectL", CTestSDKGrids::TestGridsGridSetRectL ),
        ENTRY( "TestGridsGridHandleViewRectSizeChangeL", CTestSDKGrids::TestGridsGridHandleViewRectSizeChangeL ),
        ENTRY( "TestGridsGridSetTopItemIndexL", CTestSDKGrids::TestGridsGridSetTopItemIndexL ),
        ENTRY( "TestGridsGridHandleResourceChangeL", CTestSDKGrids::TestGridsGridHandleResourceChangeL ),
        ENTRY( "TestGridsGridFocusChangedL", CTestSDKGrids::TestGridsGridFocusChangedL ),
        ENTRY( "TestGridsGridHorizontalNudgeValueL", CTestSDKGrids::TestGridsGridHorizontalNudgeValueL ),
        ENTRY( "TestGridsGridHorizScrollGranularityInPixelsL", CTestSDKGrids::TestGridsGridHorizScrollGranularityInPixelsL ),
        ENTRY( "TestGridsGridAdjustTopItemIndexL", CTestSDKGrids::TestGridsGridAdjustTopItemIndexL ),
        ENTRY( "TestGridsGridHandleDragEventL", CTestSDKGrids::TestGridsGridHandleDragEventL ),
        ENTRY( "TestGridsGridRestoreClientRectFromViewRectL", CTestSDKGrids::TestGridsGridRestoreClientRectFromViewRectL ),
        ENTRY( "TestGridsGridAdjustRectHeightToWholeNumberOfItemsL", CTestSDKGrids::TestGridsGridAdjustRectHeightToWholeNumberOfItemsL ),
        ENTRY( "TestGridsGridUpdateScrollBarThumbsL", CTestSDKGrids::TestGridsGridUpdateScrollBarThumbsL ),
        ENTRY( "TestGridsGridCountComponentControlsL", CTestSDKGrids::TestGridsGridCountComponentControlsL ),
        ENTRY( "TestGridsGridMoveToNextOrPreviousItemL", CTestSDKGrids::TestGridsGridMoveToNextOrPreviousItemL ),
        ENTRY( "TestGridsGridCalcGridSizeL", CTestSDKGrids::TestGridsGridCalcGridSizeL ),
        ENTRY( "TestGridsGridCreateItemDrawerL", CTestSDKGrids::TestGridsGridCreateItemDrawerL ),
        ENTRY( "TestGridsGridHandleScrollEventL", CTestSDKGrids::TestGridsGridHandleScrollEventL ),
        ENTRY( "TestGridsGridMopSupplyObjectL", CTestSDKGrids::TestGridsGridMopSupplyObjectL ),
        /*
         * akngridm.h
         */
        ENTRY( "TestGridsGridmConstructorAndDestructorL", TestGridsGridmConstructorAndDestructorL ),
        ENTRY( "TestGridsGridmNumberOfItemsL", CTestSDKGrids::TestGridsGridmNumberOfItemsL ),
        ENTRY( "TestGridsGridmIndexContainsDataL", CTestSDKGrids::TestGridsGridmIndexContainsDataL ),
        ENTRY( "TestGridsGridmNumberOfDataL", CTestSDKGrids::TestGridsGridmNumberOfDataL ),
        ENTRY( "TestGridsGridmSetStartCellsL", CTestSDKGrids::TestGridsGridmSetStartCellsL ),
        ENTRY( "TestGridsGridmIndexOfFirstDataItemL", CTestSDKGrids::TestGridsGridmIndexOfFirstDataItemL ),
        ENTRY( "TestGridsGridmIndexOfLastDataItemL", CTestSDKGrids::TestGridsGridmIndexOfLastDataItemL ),
        ENTRY( "TestGridsGridmItemTextL", CTestSDKGrids::TestGridsGridmItemTextL ),
        /*
         * akngridview.h
         */
        ENTRY( "TestGridsGridviewDestructorAndDestructorL", CTestSDKGrids::TestGridsGridviewDestructorAndDestructorL ),
        ENTRY( "TestGridsGridviewActualDataIndexL", CTestSDKGrids::TestGridsGridviewActualDataIndexL ),
        ENTRY( "TestGridsGridviewListBoxIndexL", CTestSDKGrids::TestGridsGridviewListBoxIndexL ),
        ENTRY( "TestGridsGridviewCurrentDataIndexL", CTestSDKGrids::TestGridsGridviewCurrentDataIndexL ),
        ENTRY( "TestGridsGridviewSetCurrentDataIndexL", CTestSDKGrids::TestGridsGridviewSetCurrentDataIndexL ),
        ENTRY( "TestGridsGridviewSetPrimaryScrollingTypeL", CTestSDKGrids::TestGridsGridviewSetPrimaryScrollingTypeL ),
        ENTRY( "TestGridsGridviewSetSecondaryScrollingTypeL", CTestSDKGrids::TestGridsGridviewSetSecondaryScrollingTypeL ),
        ENTRY( "TestGridsGridviewSetGridCellDimensionsL", CTestSDKGrids::TestGridsGridviewSetGridCellDimensionsL ),
        ENTRY( "TestGridsGridviewGridCellDimensionsL", CTestSDKGrids::TestGridsGridviewGridCellDimensionsL ),
        ENTRY( "TestGridsGridviewSetSpacesBetweenItemsL", CTestSDKGrids::TestGridsGridviewSetSpacesBetweenItemsL ),
        ENTRY( "TestGridsGridviewIsPrimaryVerticalL", CTestSDKGrids::TestGridsGridviewIsPrimaryVerticalL ),
        ENTRY( "TestGridsGridviewDataIndexFromLogicalPosL", CTestSDKGrids::TestGridsGridviewDataIndexFromLogicalPosL ),
        ENTRY( "TestGridsGridviewLogicalPosFromDataIndexL", CTestSDKGrids::TestGridsGridviewLogicalPosFromDataIndexL ),
        ENTRY( "TestGridsGridviewListBoxIndexFromLogicalPosL", CTestSDKGrids::TestGridsGridviewListBoxIndexFromLogicalPosL ),
        ENTRY( "TestGridsGridviewLogicalPosFromListBoxIndexL", CTestSDKGrids::TestGridsGridviewLogicalPosFromListBoxIndexL ),
        ENTRY( "TestGridsGridviewDrawEmptyListL", CTestSDKGrids::TestGridsGridviewDrawEmptyListL ),
        ENTRY( "TestGridsGridviewSetGridDetailsL", CTestSDKGrids::TestGridsGridviewSetGridDetailsL ),
        ENTRY( "TestGridsGridviewMoveToItemIndexLL", CTestSDKGrids::TestGridsGridviewMoveToItemIndexLL ),
        ENTRY( "TestGridsGridviewNumberOfColsInViewL", CTestSDKGrids::TestGridsGridviewNumberOfColsInViewL ),
        ENTRY( "TestGridsGridviewNumberOfRowsInViewL", CTestSDKGrids::TestGridsGridviewNumberOfRowsInViewL ),
        ENTRY( "TestGridsGridviewDrawMatcherCursorL", CTestSDKGrids::TestGridsGridviewDrawMatcherCursorL ),
        ENTRY( "TestGridsGridviewCurrentItemIndexL", CTestSDKGrids::TestGridsGridviewCurrentItemIndexL ),
        ENTRY( "TestGridsGridviewItemExistsL", CTestSDKGrids::TestGridsGridviewItemExistsL ),
        ENTRY( "TestGridsGridviewSetColumnWidthL", CTestSDKGrids::TestGridsGridviewSetColumnWidthL ),
        ENTRY( "TestGridsGridviewMoveCursorLL", CTestSDKGrids::TestGridsGridviewMoveCursorLL ),
        ENTRY( "TestGridsGridviewDrawL", CTestSDKGrids::TestGridsGridviewDrawL ),
        ENTRY( "TestGridsGridviewDrawItemL", CTestSDKGrids::TestGridsGridviewDrawItemL ),
        ENTRY( "TestGridsGridviewItemPosL", CTestSDKGrids::TestGridsGridviewItemPosL ),
        ENTRY( "TestGridsGridviewCalcBottomItemIndexL", CTestSDKGrids::TestGridsGridviewCalcBottomItemIndexL ),
        ENTRY( "TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL", CTestSDKGrids::TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL ),
        ENTRY( "TestGridsGridviewDrawItemRangeL", CTestSDKGrids::TestGridsGridviewDrawItemRangeL ),
        ENTRY( "TestGridsGridviewColumnWidthL", CTestSDKGrids::TestGridsGridviewColumnWidthL ),
        ENTRY( "TestGridsGridviewSetTopItemIndexL", CTestSDKGrids::TestGridsGridviewSetTopItemIndexL ),
        ENTRY( "TestGridsGridviewSetItemHeightL", CTestSDKGrids::TestGridsGridviewSetItemHeightL ),
        ENTRY( "TestGridsGridviewXYPosToItemIndexL", CTestSDKGrids::TestGridsGridviewXYPosToItemIndexL ),
        ENTRY( "TestGridsGridviewCalcDataWidthL", CTestSDKGrids::TestGridsGridviewCalcDataWidthL ),
        ENTRY( "TestGridsGridviewVisibleWidthL", CTestSDKGrids::TestGridsGridviewVisibleWidthL ),
        ENTRY( "TestGridsGridviewScrollToMakeItemVisibleL", CTestSDKGrids::TestGridsGridviewScrollToMakeItemVisibleL ),
        ENTRY( "TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL", CTestSDKGrids::TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL ),
        ENTRY( "TestGridsGridviewItemSizeL", CTestSDKGrids::TestGridsGridviewItemSizeL ),
        ENTRY( "TestGridsGridviewCalcRowAndColIndexesFromItemIndexL", CTestSDKGrids::TestGridsGridviewCalcRowAndColIndexesFromItemIndexL ),
        ENTRY( "TestGridsGridviewCalcItemIndexFromRowAndColIndexesL", CTestSDKGrids::TestGridsGridviewCalcItemIndexFromRowAndColIndexesL ),
        ENTRY( "TestGridsGridviewDrawColumnRangeL", CTestSDKGrids::TestGridsGridviewDrawColumnRangeL ),
        ENTRY( "TestGridsGridviewClearUnusedItemSpaceL", CTestSDKGrids::TestGridsGridviewClearUnusedItemSpaceL ),
        ENTRY( "TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL", CTestSDKGrids::TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL ),
        ENTRY( "TestGridsGridviewDoMoveLL", CTestSDKGrids::TestGridsGridviewDoMoveLL ),

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


/*
 *  [End of File]
 */
