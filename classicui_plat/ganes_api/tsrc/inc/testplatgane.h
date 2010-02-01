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
* Description:  ganes_api
*
*/


#ifndef C_TESTPLATGANE_H
#define C_TESTPLATGANE_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>

#include <ganes\HgDoubleGraphicList.h>
#include <ganes\HgDoubleGraphicListFlat.h>
#include <ganes\HgDoubleTextList.h>
#include <ganes\HgGrid.h>
#include <ganes\HgItem.h>
#include <ganes\HgScroller.h>
#include <ganes\HgScrollerWithTitle.h>
#include <ganes\HgSingleGraphicList.h>
#include <ganes\HgSingleLargeList.h>
#include <ganes\HgSingleTextList.h>
#include <ganes\HgVgMediaWall.h>
#include <ganes\HgVgItem.h>
#include <ganes\HgScrollBufferObserverIface.h>
#include <ganes\HgSelectionObserverIface.h>
#include <ganes\HgMarkingObserverIface.h>
#include <ganes\HgSingleTextListWithIcon.h>

// MACROS
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KTestPlatGaneLogPath, "\\logs\\testframework\\testplatgane\\" ); 
// Log file
_LIT( KTestPlatGaneLogFile, "testplatgane.txt" ); 
_LIT( KTestPlatGaneLogFileWithTitle, "testplatgane_[%S].txt" );

// const variable
const int KTest = 5;
const int KStringSize = 20;

// Dummy observer for testing some methods.
class TDummyObserver : public MHgScrollBufferObserver, public MHgSelectionObserver, public MHgMarkingObserver
    {
    public:
       void Request(TInt /*aRequestStart*/, TInt /*aRequestEnd*/, THgScrollDirection /*aDirection*/) {}       
       void Release(TInt /*aReleaseStart*/, TInt /*aReleaseEnd*/) { }       
       void HandleOpenL(TInt /*aIndex*/) { }
       void HandleSelectL(TInt /*aIndex*/) { }
       void HandleMarkingL( TInt /*aIndex*/, TBool /*aMarked*/ ) {}
    };



/**
*  CTestPlatGane test class for STIF Test Framework TestScripter.
*  @since S60 5.0
*/
NONSHARABLE_CLASS( CTestPlatGane ) : public CScriptBase
    {
public:  // Constructors and destructor

    /**
    * Two-phased constructor.
    */
    static CTestPlatGane* NewL( CTestModuleIf& aTestModuleIf );

    /**
    * Destructor.
    */
    virtual ~CTestPlatGane();

public: // Functions from base classes

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
    CTestPlatGane( CTestModuleIf& aTestModuleIf );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();
    
    /**
     * Method used to log version of test class
     */
    void SendTestClassVersion();
    
        /**
     * Turn off ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void TurnOffScreenSaver();

    /**
     * Restore ScreenSaver
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    void RestoreScreenSaver();

private: // [TestMethods]
    /**
     * TestCHgDoubleGraphicListL test  of CHgDoubleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleGraphicListL( CStifItemParser& aItem );

    /**
     * TestCHgDoubleGraphicListPreferredImageSize test PreferredImageSize of CHgDoubleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleGraphicListPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgDoubleGraphicListL test  of CHgDoubleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleGraphicListFlatL( CStifItemParser& aItem );

    /**
     * TestCHgDoubleGraphicListPreferredImageSize test PreferredImageSize of CHgDoubleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleGraphicListFlatPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgDoubleTextListL test  of CHgDoubleTextList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleTextListL( CStifItemParser& aItem );

    /**
     * TestCHgDoubleTextListPreferredImageSize test PreferredImageSize of CHgDoubleTextList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgDoubleTextListPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgGridNewL test NewL of CHgGrid
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgGridNewL( CStifItemParser& aItem );

    /**
     * TestCHgGridPreferredImageSize test PreferredImageSize of CHgGrid
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgGridPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgGridSetLandscapeScrollingSupport test SetLandscapeScrollingSupport of CHgGrid
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgGridSetLandscapeScrollingSupport( CStifItemParser& aItem );

    /**
     * TestCHgItemNewL test NewL of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemNewL( CStifItemParser& aItem );

    /**
     * TestCHgItemNewLCL test NewLC of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemNewLCL( CStifItemParser& aItem );

    /**
     * TestCHgItemIconL test Icon of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemIconL( CStifItemParser& aItem );

    /**
     * TestCHgItemTitleL test Title of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemTitleL( CStifItemParser& aItem );

    /**
     * TestCHgItemTextL test Text of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemTextL( CStifItemParser& aItem );

    /**
     * TestCHgItemTimeL test Time of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemTimeL( CStifItemParser& aItem );

    /**
     * TestCHgItemSetIconL test SetIcon of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemSetIconL( CStifItemParser& aItem );

    /**
     * TestCHgItemSetTitleL test SetTitleL of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemSetTitleL( CStifItemParser& aItem );

    /**
     * TestCHgItemSetTextL test SetTextL of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemSetTextL( CStifItemParser& aItem );

    /**
     * TestCHgItemSetTimeL test SetTime of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemSetTimeL( CStifItemParser& aItem );

    /**
     * TestCHgItemFlagsL test Flags of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgItemSetFlagsL test SetFlags of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemSetFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgItemClearFlagsL test ClearFlags of CHgItem
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgItemClearFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerInitScreenL1 test InitScreenL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerInitScreenL1( CStifItemParser& aItem );

    /**
     * TestCHgScrollerInitScreenL2L test InitScreenL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerInitScreenL2L( CStifItemParser& aItem );

    /**
     * TestCHgScrollerRefreshScreenL test RefreshScreen of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerRefreshScreenL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerFirstIndexOnScreenL test FirstIndexOnScreen of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerFirstIndexOnScreenL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerItemsOnScreenL test ItemsOnScreen of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerItemsOnScreenL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerItemL test ItemL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetItemL test SetItem of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerAddItemL test AddItem of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerAddItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerInsertItemL test InsertItem of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerInsertItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerRemoveItemL test RemoveItem of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerRemoveItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSelectedIndexL test SelectedIndex of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSelectedIndexL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetSelectedIndexL test SetSelectedIndex of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetSelectedIndexL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerMarkL test Mark of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerMarkL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerUnMarkL test UnMark of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerUnMarkL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerMarkAllL test MarkAll of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerMarkAllL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerUnMarkAllL test UnMarkAll of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerUnMarkAllL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerGetMarkedItemsL test GetMarkedItemsL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerGetMarkedItemsL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerEnableScrollBufferL test EnableScrollBufferL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerEnableScrollBufferL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetSelectionObserver test SetSelectionObserver of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetSelectionObserver( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetMarkingObserver test SetMarkingObserver of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetMarkingObserver( CStifItemParser& aItem );

    /**
     * TestCHgScrollerResetL test Reset of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerResetL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerResizeL test ResizeL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerResizeL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetEmptyTextL test SetEmptyTextL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetEmptyTextL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerItemCountL test ItemCount of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerItemCountL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetScrollBarTypeL test SetScrollBarTypeL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetScrollBarTypeL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetFlagsL test SetFlags of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerClearFlagsL test ClearFlags of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerClearFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerFlagsL test Flags of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerFlagsL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerHightlightItemL test HightlightItem of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerHightlightItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerSetDefaultIconL test SetDefaultIconL of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerSetDefaultIconL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerDisableScrollBufferL test DisableScrollBuffer of CHgScroller
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerDisableScrollBufferL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerWithTitleNewL test NewL of CHgScrollerWithTitle
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerWithTitleNewL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerWithTitleInitScreenL test InitScreenL of CHgScrollerWithTitle
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerWithTitleInitScreenL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerWithTitleScrollerL test Scroller of CHgScrollerWithTitle
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerWithTitleScrollerL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerWithTitleTitleItemL test TitleItem of CHgScrollerWithTitle
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerWithTitleTitleItemL( CStifItemParser& aItem );

    /**
     * TestCHgScrollerWithTitlePreferredImageSize test PreferredImageSize of CHgScrollerWithTitle
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgScrollerWithTitlePreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgSingleGraphicListNewL test NewL of CHgSingleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgSingleGraphicListNewL( CStifItemParser& aItem );

    /**
     * TestCHgSingleGraphicListPreferredImageSize test PreferredImageSize of CHgSingleGraphicList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgSingleGraphicListPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgSingleLargeListNewL test NewL of CHgSingleLargeList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgSingleLargeListNewL( CStifItemParser& aItem );

    /**
     * TestCHgSingleLargeListPreferredImageSize test PreferredImageSize of CHgSingleLargeList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgSingleLargeListPreferredImageSize( CStifItemParser& aItem );

    /**
     * TestCHgSingleTextListL test  of CHgSingleTextList
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgSingleTextListL( CStifItemParser& aItem );

    /**
     * TestCHgVgMediaWallNewL test NewL of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallNewL( CStifItemParser& aItem );
    
    /**
     * TestCHgVgMediaWallInitScreenL test InitScreenL of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallInitScreenL( CStifItemParser& aItem );


    /**
     * TestCHgVgMediaWallRefreshScreen test RefreshScreen of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallRefreshScreen( CStifItemParser& aItem );
    

    /**
     * TestCHgVgMediaWallFirstIndexOnScreen test FirstIndexOnScreen of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallFirstIndexOnScreen( CStifItemParser& aItem );

    /**
     * TestCHgVgMediaWallItemsOnScreen test ItemsOnScreen of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallItemsOnScreen( CStifItemParser& aItem );

    /**
     * TestCHgVgMediaWallItemL test ItemL of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallItemL( CStifItemParser& aItem );
        
    /**
     * TestCHgVgMediaWallSetItem test SetItem of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallSetItem( CStifItemParser& aItem );
    
    /**
     * TestCHgVgMediaWallAddItem test AddItem of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallAddItem( CStifItemParser& aItem );
    
    /**
     * TestCHgVgMediaWallInsertItem test InsertItem of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallInsertItem( CStifItemParser& aItem );

    /**
     * TestCHgVgMediaWallRemoveItem test InsertItem of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallRemoveItem( CStifItemParser& aItem );
    
    
    /**
     * TestCHgVgMediaWallSelectedIndex test SelectedIndex of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallSelectedIndex( CStifItemParser& aItem );


    /**
     * TestCHgVgMediaWallSetSelectedIndex test SetSelectedIndex of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallSetSelectedIndex( CStifItemParser& aItem );


    /**
     * TestCHgVgMediaWallEnableScrollBufferL test EnableScrollBufferL of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallEnableScrollBufferL( CStifItemParser& aItem );


    /**
     * TestCHgVgMediaWallSetSelectionObserver test SetSelectionObserver of CHgVgMediaWall
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCHgVgMediaWallSetSelectionObserver( CStifItemParser& aItem );
    
    /**
    * TestCHgVgMediaWallSetSelectionReset test Reset of CHgVgMediaWall
    * @since S60 5.0
    * @param aItem never used
    * @return Symbian OS error code.
    */
   virtual TInt TestCHgVgMediaWallReset( CStifItemParser& aItem );
        
   /**
   * TestCHgVgMediaWallSetSelectionResizeL test ResizeL of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallResizeL( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallSetEmptyTextL test SetEmptyTextL of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallSetEmptyTextL( CStifItemParser& aItem );
   

   /**
   * TestCHgVgMediaWallItemCount test ItemCount of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallItemCount( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallSetDefaultIconL test SetDefaultIconL of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallSetDefaultIconL( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallDisableScrollBuffer test DisableScrollBuffer of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallDisableScrollBuffer( CStifItemParser& aItem );


   /**
   * TestCHgVgMediaWallChangeStyleL test ChangeStyleL of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallChangeStyleL( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallSetObserver test SetObserver of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallSetObserver( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallSetOpeningAnimationType test SetOpeningAnimationType of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallSetOpeningAnimationType( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallStyle test Style of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallStyle( CStifItemParser& aItem );

   /**
   * TestCHgVgMediaWallOpeningAnimationType test OpeningAnimationType of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallOpeningAnimationType( CStifItemParser& aItem );
      
   /**
   * TestCHgVgMediaWallStartOpeningAnimationL test StartOpeningAnimationL of CHgVgMediaWall
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgMediaWallStartOpeningAnimationL( CStifItemParser& aItem );

   /**
   * TestCHgVgItemNewL test NewL of CHgVgItem
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgItemNewL( CStifItemParser& aItem );
   
   /**
   * TestCHgVgItemNewLC test NewLC of CHgVgItem
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgItemNewLC( CStifItemParser& aItem );

   /**
   * TestCHgVgItemSetIcon test SetIcon of CHgVgItem
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgVgItemSetIcon( CStifItemParser& aItem );
   
   /**
   * TestCHgSingleTextListWithIconNewL test NewL of CHgSingleTextListWithIcon
   * @since S60 5.0
   * @param aItem never used
   * @return Symbian OS error code.
   */
   virtual TInt TestCHgSingleTextListWithIconNewL( CStifItemParser& aItem );
   
   
private:    // Data
    
    /**
     * ScreenSaver Property
     */
    TInt iOldScreenSaverProperty;

    };

#endif      // C_TESTPLATGANE_H

// End of File

