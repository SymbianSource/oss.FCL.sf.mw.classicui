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
* Description:  test akntransparentcamerasettingpage.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <s32file.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <akntransparentcamerasettingpage.h>
#include <avkon.mbg>
#include <coemain.h>

#include <testdomsetpage.rsg>
#include "testdomsetpage.h"
#include "testdomsetpageext.h"

// CONSTANTS
const TInt KDesLength = 24;

_LIT( KTitle, "title" );


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMSetPage::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestDefaultConstruct", CTestDOMSetPage::TestDefaultConstructL ),
        ENTRY( "TestConstructWithTDesC", CTestDOMSetPage::TestConstructWithTDesCL ),
        ENTRY( "TestConstructL", CTestDOMSetPage::TestConstructL ),
        ENTRY( "TestListBoxControl", CTestDOMSetPage::TestListBoxControlL ),
        ENTRY( "TestExecuteLD", CTestDOMSetPage::TestExecuteLDL ),
        ENTRY( "TestHandleListBoxEventL", CTestDOMSetPage::TestHandleListBoxEventL ),
        ENTRY( "TestSetItemArrayAndSelectionL", CTestDOMSetPage::TestSetItemArrayAndSelectionL ),
        ENTRY( "TestChangeBackground", CTestDOMSetPage::TestChangeBackgroundL ),
        ENTRY( "TestSetBitmapPositionAndClipRect", CTestDOMSetPage::TestSetBitmapPositionAndClipRectL ),
        ENTRY( "TestHandleResourceChange", CTestDOMSetPage::TestHandleResourceChangeL ),
        ENTRY( "TestSetBitmapPositionAndClipRectWithBool", CTestDOMSetPage::TestSetBitmapPositionAndClipRectWithBoolL ),
        ENTRY( "TestUpdateSettingL", CTestDOMSetPage::TestUpdateSettingL ),
        ENTRY( "TestDynamicInitL", CTestDOMSetPage::TestDynamicInitL ),
        ENTRY( "TestSelectCurrentItemL", CTestDOMSetPage::TestSelectCurrentItemL ),
        ENTRY( "TestHandleControlEventL", CTestDOMSetPage::TestHandleControlEventL ),
        ENTRY( "TestProcessCommandL", CTestDOMSetPage::TestProcessCommandL ),
        ENTRY( "TestOfferKeyEventL", CTestDOMSetPage::TestOfferKeyEventL ),
        ENTRY( "TestWriteInternalStateL", CTestDOMSetPage::TestWriteInternalStateL ),
        ENTRY( "TestSizeChanged", CTestDOMSetPage::TestSizeChangedL ),
        ENTRY( "TestDraw", CTestDOMSetPage::TestDrawL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestDefaultConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestDefaultConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestDefaultConstruct, "In TestDefaultConstruct" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestDefaultConstruct );
    // Print to log file
    iLog->Log( KTestDefaultConstruct );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    STIF_ASSERT_NOT_NULL( setPage );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestConstructWithTDesCL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestConstructWithTDesCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestConstructWithTDesC, "In TestConstructWithTDesC" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestConstructWithTDesC );
    // Print to log file
    iLog->Log( KTestConstructWithTDesC );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( &KTitle, 0, 0, 0,
                        R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    STIF_ASSERT_NOT_NULL( setPage );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestConstructL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestConstructL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestConstructL, "In TestConstructL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestConstructL );
    // Print to log file
    iLog->Log( KTestConstructL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    _LIT( KTitle, "title" );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( &KTitle, 0, 0, 0,
                        R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );

    setPage->ConstructL();

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestListBoxControlL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestListBoxControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestListBoxControl, "In TestListBoxControl" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestListBoxControl );
    // Print to log file
    iLog->Log( KTestListBoxControl );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( &KTitle, 0, 0, 0,
                        R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    CAknSetStyleListBox* listBox = setPage->ListBoxControl();
    STIF_ASSERT_NOT_NULL( listBox );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestExecuteLDL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestExecuteLDL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestExecuteLD, "In TestExecuteLD" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestExecuteLD );
    // Print to log file
    iLog->Log( KTestExecuteLD );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    TBool execute = setPage->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted );
    STIF_ASSERT_TRUE( execute );

    CleanupStack::Pop( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestHandleListBoxEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestHandleListBoxEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestHandleListBoxEventL, "In TestHandleListBoxEventL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestHandleListBoxEventL );
    // Print to log file
    iLog->Log( KTestHandleListBoxEventL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    CEikListBox* listBox = new ( ELeave ) CEikListBox;
    CleanupStack::PushL( listBox );
    setPage->HandleListBoxEventL( listBox,
            MEikListBoxObserver::EEventEnterKeyPressed );

    CleanupStack::PopAndDestroy( listBox );
    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestSetItemArrayAndSelectionL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestSetItemArrayAndSelectionL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestSetItemArrayAndSelectionL, "In TestSetItemArrayAndSelectionL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestSetItemArrayAndSelectionL );
    // Print to log file
    iLog->Log( KTestSetItemArrayAndSelectionL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    setPage->SetItemArrayAndSelectionL( array, 0 );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestChangeBackgroundL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestChangeBackgroundL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestChangeBackground, "In TestChangeBackground" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestChangeBackground );
    // Print to log file
    iLog->Log( KTestChangeBackground );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    CFbsBitmap* bmp = NULL;
    bmp = AknIconUtils::CreateIconL( AknIconUtils::AvkonIconFileName(), 
        EMbmAvkonQgn_prop_nrtyp_note );
    CleanupStack::PushL( bmp );
    setPage->ChangeBackground( bmp );

    CleanupStack::PopAndDestroy( bmp );
    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestSetBitmapPositionAndClipRectL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestSetBitmapPositionAndClipRectL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestSetBitmapPositionAndClipRect, "In TestSetBitmapPositionAndClipRect" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestSetBitmapPositionAndClipRect );
    // Print to log file
    iLog->Log( KTestSetBitmapPositionAndClipRect );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    setPage->SetBitmapPositionAndClipRect( TPoint(), TRect() );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestHandleResourceChange, "In TestHandleResourceChange" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestHandleResourceChange );
    // Print to log file
    iLog->Log( KTestHandleResourceChange );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    setPage->HandleResourceChange( 0 );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestSetBitmapPositionAndClipRectWithBoolL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestSetBitmapPositionAndClipRectWithBoolL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestSetBitmapPositionAndClipRectWithBool, "In TestSetBitmapPositionAndClipRectWithBool" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestSetBitmapPositionAndClipRectWithBool );
    // Print to log file
    iLog->Log( KTestSetBitmapPositionAndClipRectWithBool );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    setPage->SetBitmapPositionAndClipRect( TPoint(), TRect(), ETrue );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestUpdateSettingL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestUpdateSettingL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestUpdateSettingL, "In TestUpdateSettingL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestUpdateSettingL );
    // Print to log file
    iLog->Log( KTestUpdateSettingL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoUpdateSettingL();

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestDynamicInitL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestDynamicInitL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestDynamicInitL, "In TestDynamicInitL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestDynamicInitL );
    // Print to log file
    iLog->Log( KTestDynamicInitL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoDynamicInitL();

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestSelectCurrentItemL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestSelectCurrentItemL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestSelectCurrentItemL, "In TestSelectCurrentItemL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestSelectCurrentItemL );
    // Print to log file
    iLog->Log( KTestSelectCurrentItemL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoSelectCurrentItemL();

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestHandleControlEventL, "In TestHandleControlEventL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestHandleControlEventL );
    // Print to log file
    iLog->Log( KTestHandleControlEventL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoHandleControlEventL( NULL,
            MCoeControlObserver::EEventRequestCancel );

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestProcessCommandL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestProcessCommandL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestProcessCommandL, "In TestProcessCommandL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestProcessCommandL );
    // Print to log file
    iLog->Log( KTestProcessCommandL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    CCoeEnv::Static()->AppUi()->AddToStackL( setPageExt );
    setPageExt->DoProcessCommandL( EAknSoftkeyHide );
    CCoeEnv::Static()->AppUi()->RemoveFromStack( setPageExt );

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestOfferKeyEventL, "In TestOfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestOfferKeyEventL );
    // Print to log file
    iLog->Log( KTestOfferKeyEventL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPage* setPage = new ( ELeave )
            CAknTransparentCameraSettingPage( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPage );
    setPage->ConstructL();

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = setPage->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_EQUALS( EKeyWasNotConsumed, keyResponse );

    CleanupStack::PopAndDestroy( setPage );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestWriteInternalStateL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestWriteInternalStateL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestWriteInternalStateL, "In TestWriteInternalStateL" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestWriteInternalStateL );
    // Print to log file
    iLog->Log( KTestWriteInternalStateL );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    RFs fs;
    CleanupClosePushL( fs );
    TInt err = fs.Connect();
    if ( err != KErrNone )
        {
        return err;
        }

    RFileWriteStream writeStream;
    CleanupClosePushL( writeStream );
    _LIT( KFileName, "c:\\setpage.dat" );
    writeStream.Replace( fs, KFileName, EFileWrite );
    setPageExt->DoWriteInternalStateL( writeStream );

    CleanupStack::PopAndDestroy( &writeStream );
    CleanupStack::PopAndDestroy( &fs );
    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestSizeChanged, "In TestSizeChanged" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestSizeChanged );
    // Print to log file
    iLog->Log( KTestSizeChanged );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoSizeChanged();

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMSetPage::TestDrawL
// -----------------------------------------------------------------------------
//
TInt CTestDOMSetPage::TestDrawL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestDOMSetPage, "testdomsetpage" );
    _LIT( KTestDraw, "In TestDraw" );
    TestModuleIf().Printf( 0, KTestDOMSetPage, KTestDraw );
    // Print to log file
    iLog->Log( KTestDraw );

    TInt index = 0;
    CPtrCArray* array = new ( ELeave ) CPtrCArray( 1 );
    CleanupStack::PushL( array );
    TBuf<KDesLength> txt( KTitle );
    array->AppendL( txt );
    

    CAknTransparentCameraSettingPageExt* setPageExt = new ( ELeave )
            CAknTransparentCameraSettingPageExt( R_SETTING_PAGE, index, array );
    CleanupStack::PushL( setPageExt );
    setPageExt->ConstructL();

    setPageExt->DoDraw( TRect() );

    CleanupStack::PopAndDestroy( setPageExt );
    CleanupStack::PopAndDestroy( array );
    return KErrNone;

    }


//  [End of File]
