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



#ifndef C_TESTSDKGRIDS_H
#define C_TESTSDKGRIDS_H

/*
 *   INCLUDES
 */
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>


#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0


_LIT( KtestsdkgridsLogPath, "\\logs\\testframework\\testsdkgrids\\" ); 

_LIT( KtestsdkgridsLogFile, "testsdkgrids.txt" ); 
_LIT( KtestsdkgridsLogFileWithTitle, "testsdkgrids_[%S].txt" );

class CTestSDKGridsView;
class CTestSDKGridsContainer;
class CAknColourSelectionGrid;
class CAknGMSStyleGrid;
class CAknGrid;
/**
*  Ctestsdkgrids test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS(CTestSDKGrids) : public CScriptBase
    {
public: 

    /**
    * Two-phased constructor.
    */
    static CTestSDKGrids* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestSDKGrids();

public: 

    /**
    * From CScriptBase Runs a script line.
    * @since S60 5.0
    * @param aItem Script line containing method name and parameters
    * @return Symbian OS error code
    */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
    * C++ default constructor.
    */
    CTestSDKGrids( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    /**
    * Frees all resources allocated from test methods.
    * @since S60 5.0
    */
    void Delete();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();

    //[TestMethods]
private:
    //akncolourselectiongrid.h
    /**
     * TestGridsCCSGNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    
    virtual TInt TestGridsCCSGNewL( CStifItemParser& aItem );
    /**
     * TestGridsCCSGExecuteLD test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    
    virtual TInt TestGridsCCSGExecuteLD( CStifItemParser& aItem );
    /**
     * TestGridsCCSGDelete test function for testing the Destruct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsCCSGDelete( CStifItemParser& aItem );
    
    /**
     * TestGridsCCSGHandlePointerEventL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsCCSGHandlePointerEventL( CStifItemParser& aItem );
    
private:
    //AknGMSStyleGrid.h------class CAknGMSStyleGridView
    /**
     * TestGridsGMSSGVConstuctionL test function for testing the construction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGVConstuctionL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGVDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGVDrawL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGVSetupLayoutL test function for testing the SetupLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGVSetupLayoutL( CStifItemParser& aItem );
    
    //AknGMSStyleGrid.h------class CAknGMSStyleGrid
    /**
     * TestGridsGMSSGNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGNewL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGConstructionL test function for testing the Construction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGConstructionL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGConstructionWithTBoolL test function for testing the CAknGMSStyleGrid(TBool aIsPopup) function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGConstructionWithTBoolL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGConstructL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGDelete test function for testing the Destruct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGDelete( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGSetupLayout test function for testing the SetupLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGSetupLayout( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGHandlePointerEventL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGHandlePointerEventL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGSizeChanged test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGSizeChanged( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGMinimumSize test function for testing the MinimumSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGMinimumSize( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGOfferKeyEventL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGDraw test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGDraw( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSSGMakeViewClassInstanceL test function for testing the MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSSGMakeViewClassInstanceL( CStifItemParser& aItem );
    
    // AknGMSStyleGrid.h------class CAknGMSPopupGrid
    /**
     * TestGridsGMSPGNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGNewL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSPGSetupWindowLayoutL test function for testing the SetupWindowLayout function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGSetupWindowLayoutL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSPGCalcPopupGridLargeGraphicWindowL test function for testing the CalcPopupGridLargeGraphicWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGCalcPopupGridLargeGraphicWindowL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSPGSetupPopupGridLargeGraphicWindowL test function for testing the SetupPopupGridLargeGraphicWindow function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGSetupPopupGridLargeGraphicWindowL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSPGPopupGridLargeGraphicGraphicsL test function for testing the PopupGridLargeGraphicGraphics function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGPopupGridLargeGraphicGraphicsL( CStifItemParser& aItem );
    
    /**
     * TestGridsGMSPGHandlePointerEventL test function for testing the HandlePointerEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGMSPGHandlePointerEventL( CStifItemParser& aItem );
    
private:
    //akngrid.h
    /**
     * TestGridsGridConstructionL test function for testing the construction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridConstructionL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridDelete test function for testing the destruct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridDelete( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetModelL test function for testing the SetModel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetModelL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridConstructL test function for testing the ConstructL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridConstructL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridConstructFromResourceL test function for testing the ConstructFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridConstructFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetLayoutL test function for testing the SetLayoutL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetLayoutL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetLayoutFromResourceL test function for testing the SetLayoutFromResourceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetLayoutFromResourceL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetPrimaryScrollingType test function for testing the SetPrimaryScrollingType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetPrimaryScrollingType( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetSecondaryScrollingType test function for testing the SetSecondaryScrollingType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetSecondaryScrollingType( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetStartPositionL test function for testing the SetStartPositionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetStartPositionL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridCurrentDataIndex test function for testing the CurrentDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridCurrentDataIndex( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetCurrentDataIndex test function for testing the SetCurrentDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetCurrentDataIndex( CStifItemParser& aItem );
    
    /**
     * TestGridsGridIndexOfPosition test function for testing the IndexOfPosition function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridIndexOfPosition( CStifItemParser& aItem );
    
    /**
     * TestGridsGridPositionAtIndex test function for testing the PositionAtIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridPositionAtIndex( CStifItemParser& aItem );
    
    /**
     * TestGridsGridItemDrawer test function for testing the ItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridItemDrawer( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetEmptyGridTextL test function for testing the SetEmptyGridTextL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetEmptyGridTextL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridEmptyGridText test function for testing the EmptyGridText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridEmptyGridText( CStifItemParser& aItem );
    
    /**
     * TestGridsGridMakeViewClassInstanceL test function for testing the MakeViewClassInstanceL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridMakeViewClassInstanceL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetColumnWidth test function for testing the SetColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetColumnWidth( CStifItemParser& aItem );
    
    /**
     * TestGridsGridColumnWidth test function for testing the ColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridColumnWidth( CStifItemParser& aItem );
    
    /**
     * TestGridsGridUpdateScrollBarsL test function for testing the UpdateScrollBarsL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridUpdateScrollBarsL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridHandleItemAdditionL test function for testing the HandleItemAdditionL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleItemAdditionL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridHandleItemRemovalL test function for testing the HandleItemRemovalL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleItemRemovalL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridOfferKeyEventL test function for testing the OfferKeyEventL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridOfferKeyEventL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetItemHeightL test function for testing the SetItemHeightL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetItemHeightL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSizeChanged test function for testing the SizeChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSizeChanged( CStifItemParser& aItem );
    
    /**
     * TestGridsGridModel test function for testing the Model function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridModel( CStifItemParser& aItem );
    
    /**
     * TestGridsGridSetRect test function for testing the SetRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetRectL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridHandleViewRectSizeChangeL test function for testing the HandleViewRectSizeChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleViewRectSizeChangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridSetTopItemIndexL test function for testing the SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridSetTopItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridHandleResourceChangeL test function for testing the HandleResourceChange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleResourceChangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridFocusChangedL test function for testing the FocusChanged function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridFocusChangedL( CStifItemParser& /*aItem*/ );
    
    /*
     * Follow are protected funciont in CAknGrid
     */
    /**
     * TestGridsGridHorizontalNudgeValueL test function for testing the HorizontalNudgeValue function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHorizontalNudgeValueL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridHorizScrollGranularityInPixels test function for testing the HorizScrollGranularityInPixel function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHorizScrollGranularityInPixelsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridAdjustTopItemIndex test function for testing the AdjustTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridAdjustTopItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridHandleDragEventL test function for testing the HandleDragEvent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleDragEventL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridRestoreClientRectFromViewRectL test function for testing the RestoreClientRectFromViewRect function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridRestoreClientRectFromViewRectL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridAdjustRectHeightToWholeNumberOfItemsL test function for testing the AdjustRectHeightToWholeNumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridUpdateScrollBarThumbsL test function for testing the UpdateScrollBarThumbs function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridUpdateScrollBarThumbsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridCountComponentControlsL test function for testing the CountComponentControls function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridCountComponentControlsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridMoveToNextOrPreviousItemL test function for testing the MoveToNextOrPreviousItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridMoveToNextOrPreviousItemL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridCalcGridSizeL test function for testing the CalcGridSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridCalcGridSizeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridCreateItemDrawerL test function for testing the CreateItemDrawer function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridCreateItemDrawerL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridHandleScrollEventL test function for testing the HandleScrollEvent function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridHandleScrollEventL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridMopSupplyObjectL test function for testing the MopSupplyObject function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridMopSupplyObjectL( CStifItemParser& /*aItem*/ );
    
private:
    /**
     * TestGridsGridmConstructorAndDestructorL test function for testing the ConstructorAndDestructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
	virtual TInt TestGridsGridmConstructorAndDestructorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridmNumberOfItemsL test function for testing the NumberOfItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmNumberOfItemsL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmIndexContainsDataL test function for testing the IndexContainsData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmIndexContainsDataL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmNumberOfDataL test function for testing the NumberOfData function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmNumberOfDataL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmSetStartCellsL test function for testing the SetStartCells function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmSetStartCellsL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmIndexOfFirstDataItemL test function for testing the IndexOfFirstDataItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmIndexOfFirstDataItemL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmIndexOfLastDataItemL test function for testing the IndexOfLastDataItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridmIndexOfLastDataItemL( CStifItemParser& /*aItem*/ );

    /**
     * TestGridsGridmItemTextL test function for testing the ItemText function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
	virtual TInt TestGridsGridmItemTextL( CStifItemParser& /*aItem*/ );
	
private:
    /**
     * TestGridsGridviewDestructorAndDestructorL test function for testing the DestructorAndDestructor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDestructorAndDestructorL( CStifItemParser& /*aItem*/ );
	
    /**
     * TestGridsGridviewActualDataIndexL test function for testing the ActualDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewActualDataIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewListBoxIndexL test function for testing the ListBoxIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewListBoxIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCurrentDataIndexL test function for testing the CurrentDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCurrentDataIndexL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewSetCurrentDataIndexL test function for testing the SetCurrentDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetCurrentDataIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewSetPrimaryScrollingTypeL test function for testing the SetPrimaryScrollingType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetPrimaryScrollingTypeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewSetSecondaryScrollingTypeL test function for testing the SetSecondaryScrollingType function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetSecondaryScrollingTypeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewSetGridCellDimensionsL test function for testing the SetGridCellDimensions function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetGridCellDimensionsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewGridCellDimensions test function for testing the GridCellDimensions function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewGridCellDimensionsL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewSetSpacesBetweenItemsL test function for testing the SetSpacesBetweenItems function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetSpacesBetweenItemsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewIsPrimaryVerticalL test function for testing the IsPrimaryVertical function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewIsPrimaryVerticalL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDataIndexFromLogicalPosL test function for testing the DataIndexFromLogicalPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDataIndexFromLogicalPosL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewLogicalPosFromDataIndexL test function for testing the LogicalPosFromDataIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewLogicalPosFromDataIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewListBoxIndexFromLogicalPosL test function for testing the ListBoxIndexFromLogicalPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewListBoxIndexFromLogicalPosL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewLogicalPosFromListBoxIndexL test function for testing the LogicalPosFromListBoxIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewLogicalPosFromListBoxIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDrawEmptyListL test function for testing the DrawEmptyList function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawEmptyListL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewSetGridDetailsL test function for testing the SetGridDetails function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetGridDetailsL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewMoveToItemIndexLL test function for testing the MoveToItemIndexL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewMoveToItemIndexLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewNumberOfColsInViewL test function for testing the viewNumberOfColsInView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewNumberOfColsInViewL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewNumberOfRowsInViewL test function for testing the NumberOfRowsInView function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewNumberOfRowsInViewL( CStifItemParser& /*aIetm*/ );
    
    /**
     * TestGridsGridviewDrawMatcherCursorL test function for testing the DrawMatcherCursor function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawMatcherCursorL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCurrentItemIndexL test function for testing the CurrentItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCurrentItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewItemExistsL test function for testing the ItemExists function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewItemExistsL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewSetColumnWidthL test function for testing the SetColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetColumnWidthL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewMoveCursorLL test function for testing the MoveCursorL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewMoveCursorLL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDrawL test function for testing the Draw function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDrawItemL test function for testing the DrawItem function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawItemL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewItemPosL test function for testing the ItemPos function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewItemPosL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCalcBottomItemIndexL test function for testing the CalcBottomItemIndexL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalcBottomItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL test function for testing the CalcNewTopItemIndexSoItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalcNewTopItemIndexSoItemIsVisibleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDrawItemRangeL test function for testing the DrawItemRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawItemRangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewColumnWidthL test function for testing the ColumnWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewColumnWidthL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewSetTopItemIndexL test function for testing the SetTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetTopItemIndexL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewSetItemHeightL test function for testing the SetItemHeight function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewSetItemHeightL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewXYPosToItemIndexL test function for testing the XYPosToItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewXYPosToItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCalcDataWidthL test function for testing the CalcDataWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalcDataWidthL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewVisibleWidthL test function for testing the VisibleWidth function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewVisibleWidthL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewScrollToMakeItemVisibleL test function for testing the ScrollToMakeItemVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewScrollToMakeItemVisibleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL test function for testing the CalculateHScrollOffsetSoItemIsVisible function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalculateHScrollOffsetSoItemIsVisibleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewItemSizeL test function for testing the ItemSize function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewItemSizeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewCalcRowAndColIndexesFromItemIndexL test function for testing the CalcRowAndColIndexesFromItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalcRowAndColIndexesFromItemIndexL( CStifItemParser& aItem );
    
    /**
     * TestGridsGridviewCalcItemIndexFromRowAndColIndexesL test function for testing the CalcItemIndexFromRowAndColIndexes function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewCalcItemIndexFromRowAndColIndexesL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDrawColumnRangeL test function for testing the DrawColumnRange function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDrawColumnRangeL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewClearUnusedItemSpaceL test function for testing the ClearUnusedItemSpace function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewClearUnusedItemSpaceL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL test function for testing the UpdateHScrollOffsetBasedOnTopItemIndex function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewUpdateHScrollOffsetBasedOnTopItemIndexL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestGridsGridviewDoMoveLL test function for testing the DoMoveL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestGridsGridviewDoMoveLL( CStifItemParser& /*aItem*/ );

private:
    /*
     * This member variable is for test other function
     */
    CTestSDKGridsView* iView;
    /*
     * This member variable is for test other function
     */
    CTestSDKGridsContainer* iContainer;
    /*
     * This member variable is for test other function
     */
    CAknColourSelectionGrid* iCCSGrid;
    /*
     * This member variable is for test other function
     */
    CAknGMSStyleGrid* iStyleGrid;
    /*
     * This member variable is for test other function
     */
    CAknGrid* iGrid;
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif 

/*
 * End of File
 */
