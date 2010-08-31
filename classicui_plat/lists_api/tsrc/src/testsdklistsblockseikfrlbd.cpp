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
* Description:  Test eikfrlbd.h
*
*/


// [INCLUDE FILES]
#include <e32base.h>
#include <eikfrlbd.h>
#include <testsdklists.rsg>
#include <barsread.h>
#include <stringloader.h>
#include <bitstd.h>
#include <aknlists.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslbabdrawer.h"
#include "testsdklistsfclbdata.h"


// CONSTANTS
const TInt KCellNum = 0;
const TInt KSetNum = 1;
const TInt KTen = 10;
_LIT( KDrawFormatted, "Draw Formatted" );


// ============================ MEMBER FUNCTIONS ===============================

// ===========================CFormattedCellListBoxData=========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDTColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDTColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDTColorsL, "In TestFCLBDTColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDTColorsL );
    // Print to log file
    iLog->Log( KTestFCLBDTColorsL );

    CFormattedCellListBoxData::TColors* color =
        new( ELeave ) CFormattedCellListBoxData::TColors();
    CleanupStack::PushL( color );
    STIF_ASSERT_NOT_NULL( color );
    CleanupStack::PopAndDestroy( color );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDNewL, "In TestFCLBDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDNewL );
    // Print to log file
    iLog->Log( KTestFCLBDNewL );

    CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDDestructorL, "In TestFCLBDDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDDestructorL );
    // Print to log file
    iLog->Log( KTestFCLBDDestructorL );

    CFormattedCellListBoxData* data = CFormattedCellListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::Pop( data );

    delete data;
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellColorsL, "In TestFCLBDSubCellColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellColorsL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellColorsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );
    
    data->SubCellColors( KCellNum );
    
    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellColorsL, "In TestFCLBDSetSubCellColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellColorsL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellColorsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );
    
    CFormattedCellListBoxData::TColors color;  
    data->SetSubCellColorsL( KCellNum , color );
    
    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellBaselinePosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellBaselinePosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellBaselinePosL, "In TestFCLBDSubCellBaselinePosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellBaselinePosL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellBaselinePosL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TInt linePos = data->SubCellBaselinePos( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellBaselinePosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellBaselinePosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellBaselinePosL, "In TestFCLBDSetSubCellBaselinePosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellBaselinePosL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellBaselinePosL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetSubCellBaselinePosL( 0 , KSetNum );
    TInt linePos = data->SubCellBaselinePos( 0 );
    STIF_ASSERT_EQUALS( KSetNum, linePos );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellSizeL, "In TestFCLBDSubCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellSizeL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellSizeL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TSize size = data->SubCellSize( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellSizeL, "In TestFCLBDSetSubCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellSizeL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellSizeL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TSize cellSize( 1, 1 );
    data->SetSubCellSizeL( 0 , cellSize );
    TSize size = data->SubCellSize( 0 );
    STIF_ASSERT_EQUALS( cellSize, size );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellPositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellPositionL, "In TestFCLBDSubCellPositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellPositionL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellPositionL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TPoint point = data->SubCellPosition( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellPositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellPositionL, "In TestFCLBDSetSubCellPositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellPositionL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellPositionL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );
    
    TPoint cellPoint( 0 , 0 );
    data->SetSubCellPositionL( 0, cellPoint );
    TPoint point = data->SubCellPosition( 0 );
    STIF_ASSERT_EQUALS( cellPoint, point );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellIsTransparentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellIsTransparentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellIsTransparentL, "In TestFCLBDSubCellIsTransparentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellIsTransparentL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellIsTransparentL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBool isTransparent = data->SubCellIsTransparent( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetTransparentSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetTransparentSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetTransparentSubCellL, "In TestFCLBDSetTransparentSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetTransparentSubCellL );
    // Print to log file
    iLog->Log( KTestFCLBDSetTransparentSubCellL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetTransparentSubCellL( 0, ETrue );
    TBool isTransparent = data->SubCellIsTransparent( 0 );
    STIF_ASSERT_TRUE( isTransparent );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellIsNotAlwaysDrawnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellIsNotAlwaysDrawnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellIsTransparentL, "In TestFCLBDSubCellIsNotAlwaysDrawnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellIsTransparentL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellIsTransparentL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBool isNotAlwaysDrawn = data->SubCellIsNotAlwaysDrawn( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetNotAlwaysDrawnSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetNotAlwaysDrawnSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetTransparentSubCellL, "In TestFCLBDSetNotAlwaysDrawnSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetTransparentSubCellL );
    // Print to log file
    iLog->Log( KTestFCLBDSetTransparentSubCellL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetNotAlwaysDrawnSubCellL( 0, ETrue );
    TBool isNotAlwaysDrawn = data->SubCellIsNotAlwaysDrawn( 0 );
    STIF_ASSERT_TRUE( isNotAlwaysDrawn );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellMarginsL, "In TestFCLBDSubCellMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellMarginsL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellMarginsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellMargins( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellMarginsL, "In TestFCLBDSetSubCellMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellMarginsL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellMarginsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TMargins setMargins;
    setMargins.iBottom = 1;
    setMargins.iLeft = 1;
    setMargins.iRight = 1;
    setMargins.iTop = 1;
    data->SetSubCellMarginsL( 0, setMargins );
    TMargins margins = data->SubCellMargins( 0 );
    STIF_ASSERT_EQUALS( setMargins, margins );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellFontL, "In TestFCLBDSubCellFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellFontL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellFontL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellFont( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellFontL, "In TestFCLBDSetSubCellFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellFontL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellFontL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    const CFont* setFont = CCoeEnv::Static()->NormalFont();
    data->SetSubCellFontL( 0, setFont );
    const CFont* font = data->SubCellFont( 0 );
    STIF_ASSERT_EQUALS( setFont, font );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellAlignmentL, "In TestFCLBDSubCellAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellAlignmentL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellAlignmentL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellAlignment( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetSubCellAlignmentL, "In TestFCLBDSetSubCellAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetSubCellAlignmentL );
    // Print to log file
    iLog->Log( KTestFCLBDSetSubCellAlignmentL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CGraphicsContext::TTextAlign setAlign = CGraphicsContext::ELeft;
    data->SetSubCellAlignmentL( 0, setAlign );
    CGraphicsContext::TTextAlign align = data->SubCellAlignment( 0 );
    STIF_ASSERT_EQUALS( setAlign, align );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellIsGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellIsGraphicsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSubCellIsGraphicsL, "In TestFCLBDSubCellIsGraphicsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSubCellIsGraphicsL );
    // Print to log file
    iLog->Log( KTestFCLBDSubCellIsGraphicsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellIsGraphics( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetGraphicsSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetGraphicsSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBDSetGraphicsSubCellL, "In TestFCLBDSetGraphicsSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBDSetGraphicsSubCellL );
    // Print to log file
    iLog->Log( KTestFCLBDSetGraphicsSubCellL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetGraphicsSubCellL( 0, ETrue );
    TBool isGraphics = data->SubCellIsGraphics( 0 );
    STIF_ASSERT_TRUE( isGraphics );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellRightSeparatorStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellRightSeparatorStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSubCellRightSeparatorStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellRightSeparatorStyle( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellRightSeparatorStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellRightSeparatorStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSubCellRightSeparatorStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CGraphicsContext::TPenStyle setStyle = CGraphicsContext::ENullPen;
    data->SetSubCellRightSeparatorStyleL( 0, setStyle );
    CGraphicsContext::TPenStyle style = data->SubCellRightSeparatorStyle( 0 );
    STIF_ASSERT_EQUALS( setStyle, style );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellTextClipGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellTextClipGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSubCellTextClipGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellTextClipGap( 0 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellTextClipGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellTextClipGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSubCellTextClipGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetSubCellTextClipGapL( 0, KCellNum );
    TInt gap = data->SubCellTextClipGap( 0 );
    STIF_ASSERT_EQUALS( KCellNum, gap );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSkinEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSkinEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSkinEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SkinEnabled();

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetSkinEnabledL( ETrue );
    TBool flag = data->SkinEnabled();
    STIF_ASSERT_TRUE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSubCellIsNumberCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSubCellIsNumberCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSubCellIsNumberCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SubCellIsNumberCell( KCellNum );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetNumberCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetNumberCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetNumberCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetNumberCellL( 0, ETrue );
    TBool flag = data->SubCellIsNumberCell( KCellNum );
    STIF_ASSERT_TRUE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->IconArray();

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetIconArrayLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetIconArrayLL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetIconArrayLL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>( KTen );
    CleanupStack::PushL( icons );
    data->SetIconArrayL( icons );
    CArrayPtr<CGulIcon>* getIcons = data->IconArray();
    STIF_ASSERT_TRUE( icons == getIcons );

    CleanupStack::Pop( icons );
    CleanupStack::PopAndDestroy( 2 );
    icons = NULL;
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>( KTen );
    CleanupStack::PushL( icons );
    data->SetIconArray( icons );
    CArrayPtr<CGulIcon>* getIcons = data->IconArray();
    STIF_ASSERT_TRUE( icons == getIcons );

    CleanupStack::Pop( icons );
    CleanupStack::PopAndDestroy( 2 );
    icons = NULL;
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    const CFont* setFont = CCoeEnv::Static()->NormalFont();
    data->SetSubCellFontL( 0, setFont );
    TListItemProperties* property = new( ELeave ) TListItemProperties();
    CleanupStack::PushL( property );
    CFont* font = data->Font( *property, 0 );
    STIF_ASSERT_NOT_NULL( font );

    CleanupStack::PopAndDestroy( 3 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TListItemProperties* property = new( ELeave ) TListItemProperties();
    CleanupStack::PushL( property );
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    gc.UseFont( CCoeEnv::Static()->NormalFont() );
    HBufC* buf = StringLoader::LoadLC( R_TESTLIST_DRAWBUFF );
    TRect rect = listBox->Rect();
    TBool highlight = ETrue;
    CFormattedCellListBoxData::TColors color;

    data->Draw( *property, gc, buf, rect, highlight, color );

    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 4 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDUseSubCellColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDUseSubCellColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDUseSubCellColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBool flag = data->UseSubCellColors( 0 );
    STIF_ASSERT_FALSE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CCoeControl* control = data->Control();
    STIF_ASSERT_NOT_NULL( control );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetControl( NULL );
    CCoeControl* control = data->Control();
    STIF_ASSERT_NULL( control );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSkinBackgroundContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSkinBackgroundContextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSkinBackgroundContextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetSkinEnabledL( ETrue );
    MAknsControlContext* context = data->SkinBackgroundContext();
    STIF_ASSERT_NOT_NULL( context );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetBackgroundSkinStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetBackgroundSkinStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetBackgroundSkinStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = listBox->Rect();
    data->SetBackgroundSkinStyle( &itemID, rect );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = listBox->Rect();
    data->SetSkinStyle( &itemID, rect );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinParentPosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinParentPosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinParentPosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TPoint point( KTen, KTen );
    data->SetSkinParentPos( point );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetListEndSkinStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetListEndSkinStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetListEndSkinStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = listBox->Rect();
    data->SetListEndSkinStyle( &itemID, rect );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDRespectFocusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDRespectFocusL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDRespectFocusL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->RespectFocus();

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetRespectFocusL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetRespectFocusL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetRespectFocusL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetRespectFocus( ETrue );
    TBool flag = data->RespectFocus();
    STIF_ASSERT_TRUE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinHighlightFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinHighlightFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinHighlightFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    data->SetSkinHighlightFrame( &itemID, &itemID );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinPopupFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinPopupFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinPopupFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    data->SetSkinPopupFrame( &itemID, &itemID );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSkinPopupFramePositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSkinPopupFramePositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSkinPopupFramePositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TRect rect = listBox->Rect();
    data->SetSkinPopupFramePosition( rect, rect );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDUseLogicalToVisualConversionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDUseLogicalToVisualConversionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDUseLogicalToVisualConversionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->UseLogicalToVisualConversion( EFalse );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDEnableMarqueeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDEnableMarqueeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDEnableMarqueeLL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->EnableMarqueeL( EFalse );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDIsMarqueeOnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDIsMarqueeOnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDIsMarqueeOnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->EnableMarqueeL( EFalse );
    TBool flag = data->IsMarqueeOn();
    STIF_ASSERT_FALSE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    const CAknsEffectAnim* anim = data->HighlightAnim();
    STIF_ASSERT_NULL( anim );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDAboutToDrawHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDAboutToDrawHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDAboutToDrawHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->AboutToDrawHighlightAnim();

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetHighlightAnimBackgroundDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetHighlightAnimBackgroundDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetHighlightAnimBackgroundDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CTestSDKListsLBABDrawer* animDrawer = new( ELeave ) CTestSDKListsLBABDrawer();
    CleanupStack::PushL( animDrawer );
    data->SetHighlightAnimBackgroundDrawer( animDrawer );

    CleanupStack::PopAndDestroy( 3 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetItemCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetItemCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetItemCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TSize size( 0, 0 );
    data->SetItemCellSize( size );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDHasHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDHasHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDHasHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBool flag = data->HasHighlightAnim();
    STIF_ASSERT_FALSE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDDrawHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDDrawHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDDrawHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TRect rect = listBox->Rect();
    CFbsBitGc* bitGc = CFbsBitGc ::NewL();
    CleanupStack::PushL( bitGc );
    TBool flag = data->DrawHighlightAnim( *bitGc, rect );
    STIF_ASSERT_FALSE( flag );

    CleanupStack::PopAndDestroy( 3 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellFontForRowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellFontForRowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSubCellFontForRowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->SetSubCellFontForRowL( KCellNum, KCellNum, font );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDRowAndSubCellFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDRowAndSubCellFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDRowAndSubCellFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    const CFont* font = CCoeEnv::Static()->NormalFont();
    data->SetSubCellFontForRowL( KCellNum, KCellNum, font );
    const CFont* getFont = data->RowAndSubCellFont( KCellNum, KCellNum );
    STIF_ASSERT_TRUE( font == getFont );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetDrawBackgroundL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetDrawBackgroundL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetDrawBackgroundL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetDrawBackground( ETrue );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSeparatorLinePositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSeparatorLinePositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSeparatorLinePositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetSeparatorLinePosition( ENoLine );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSeparatorLinePositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSeparatorLinePositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSeparatorLinePositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TAknSeparatorLinePosition position = ENoLine;
    data->SetSeparatorLinePosition( position );
    TAknSeparatorLinePosition getPosition = data->SeparatorLinePosition();
    STIF_ASSERT_EQUALS( position, getPosition );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDLayoutDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDLayoutDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDLayoutDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    CAknLayoutData* layoutData = data->LayoutData();
    STIF_ASSERT_NULL( layoutData );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDLayoutInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDLayoutInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDLayoutInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBool flag = data->LayoutInit();
    STIF_ASSERT_FALSE( flag );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetLayoutInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetLayoutInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetLayoutInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetLayoutInit( ETrue );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubcellUnderlinedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubcellUnderlinedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSubcellUnderlinedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TBitFlags32 flags;
    data->SetSubcellUnderlined( flags );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetMarqueeParamsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetMarqueeParamsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetMarqueeParamsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->SetMarqueeParams( 1, 6, 1000000, 100000 );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDCurrentItemTextWasClippedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDCurrentItemTextWasClippedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDCurrentItemTextWasClippedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    data->CurrentItemTextWasClipped();

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDSetSubCellIconSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDSetSubCellIconSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDSetSubCellIconSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CFormattedCellListBoxData* data = listBox->ItemDrawer()->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );

    TSize size( 1, 1 );
    data->SetSubCellIconSize( KCellNum, size );

    CleanupStack::PopAndDestroy( 2 );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CTestSDKListsFCLBData* data = new( ELeave ) CTestSDKListsFCLBData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDConstructLDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDConstructLDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDConstructLDL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CTestSDKListsFCLBData* data = new( ELeave ) CTestSDKListsFCLBData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    TInt err = KErrNone;
    TRAP( err, data->ConstructLD() );
    CleanupStack::Pop( data );
    if ( err == KErrNone )
        {
        delete data;
        }
    data = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDConstructLDWithParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDConstructLDWithParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDConstructLDWithParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CTestSDKListsFCLBData* data = new( ELeave ) CTestSDKListsFCLBData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TInt err = KErrNone;
    TRAP( err, data->ConstructLD( itemID ) );
    CleanupStack::Pop( data );
    if ( err == KErrNone )
        {
        delete data;
        }
    data = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBDDrawFormattedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBDDrawFormattedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCLBD, "In TestFCLBDDrawFormattedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBD );
    // Print to log file
    iLog->Log( KTestFCLBD );

    CTestSDKListsFCLBData* data = new( ELeave ) CTestSDKListsFCLBData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TInt err = KErrNone;
    TRAP( err, data->ConstructLD( itemID ) );
    if ( err != KErrNone )
        {
        CleanupStack::Pop( data );
        data = NULL;
        return err;
        }

    TListItemProperties property;
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    CFormattedCellListBoxData::TColors color;

    data->DrawFormatted( property, gc, &KDrawFormatted, rect, ETrue, color );
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// =========================CSettingItemEditingListBoxData======================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestSIELBDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSIELBDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestSIELBDNewL, "In TestSIELBDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSIELBDNewL );
    // Print to log file
    iLog->Log( KTestSIELBDNewL );

    CSettingItemEditingListBoxData* data = CSettingItemEditingListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestSIELBDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestSIELBDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestSIELBDDrawL, "In TestSIELBDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestSIELBDDrawL );
    // Print to log file
    iLog->Log( KTestSIELBDDrawL );

    CAknSetStyleListBox* listBox = new( ELeave ) CAknSetStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    CSettingItemEditingListBoxData* data =
        static_cast<CSettingItemEditingListBoxData*> ( listBox->ItemDrawer()->ColumnData() );
    STIF_ASSERT_NOT_NULL( data );

    TListItemProperties property;
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    CFormattedCellListBoxData::TColors color;

    data->Draw( property, gc, &KDrawFormatted, rect, ETrue, color );
    iContainer->DeactivateGc();
    data = NULL;

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// ============================CFormGraphicListBoxData==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGLBDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGLBDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFGLBDNewL, "In TestFGLBDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFGLBDNewL );
    // Print to log file
    iLog->Log( KTestFGLBDNewL );

    CFormGraphicListBoxData* data = CFormGraphicListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFGLBDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFGLBDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFGLBDDrawL, "In TestFGLBDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFGLBDDrawL );
    // Print to log file
    iLog->Log( KTestFGLBDDrawL );

    CAknFormGraphicStyleListBox* listBox = new( ELeave ) CAknFormGraphicStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    CFormGraphicListBoxData* data = 
        static_cast<CFormGraphicListBoxData*> ( listBox->ItemDrawer()->ColumnData() );
    STIF_ASSERT_NOT_NULL( data );

    TListItemProperties property;
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    CFormattedCellListBoxData::TColors color;

    data->Draw( property, gc, &KDrawFormatted, rect, ETrue, color );
    iContainer->DeactivateGc();
    data = NULL;

    CleanupStack::PopAndDestroy( 2 );


    return KErrNone;
    }

// ===========================CPopupFormattedListBoxData========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestPFLBDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestPFLBDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestPFLBDNewL, "In TestPFLBDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestPFLBDNewL );
    // Print to log file
    iLog->Log( KTestPFLBDNewL );

    CPopupFormattedListBoxData* data = CPopupFormattedListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestPFLBDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestPFLBDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestPFLBDDrawL, "In TestPFLBDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestPFLBDDrawL );
    // Print to log file
    iLog->Log( KTestPFLBDDrawL );

    CAknDoublePopupMenuStyleListBox* listBox =
        new ( ELeave ) CAknDoublePopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    listBox->ConstructFromResourceL( reader );

    CPopupFormattedListBoxData* data =
        static_cast<CPopupFormattedListBoxData*> ( listBox->ItemDrawer()->ColumnData() );
    STIF_ASSERT_NOT_NULL( data );
    
    TListItemProperties property;
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    CFormattedCellListBoxData::TColors color;
    data->Draw( property, gc, &KDrawFormatted, rect, ETrue, color );
    iContainer->DeactivateGc();

    CleanupStack::PopAndDestroy( 2 );
    
    return KErrNone;
    }
// ==============================CFormattedCellGridData=========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCGDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCGDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCGDNewL, "In TestFCGDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCGDNewL );
    // Print to log file
    iLog->Log( KTestFCGDNewL );

    CFormattedCellGridData* data = CFormattedCellGridData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCGDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCGDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBDTestModule" );
    _LIT( KTestFCGDDrawL, "In TestFCGDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCGDDrawL );
    // Print to log file
    iLog->Log( KTestFCGDDrawL );

    CAknGrid* grid = new ( ELeave ) CAknGrid;
    CleanupStack::PushL( grid );
    grid->ConstructL( iContainer, 0 );
    
    CFormattedCellGridData* data =
        static_cast<CFormattedCellGridData*> ( grid->ItemDrawer()->ColumnData() );
    STIF_ASSERT_NOT_NULL( data );

    TListItemProperties property;
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    CFormattedCellListBoxData::TColors color;

    data->Draw( property, gc, &KDrawFormatted, rect, ETrue, color );
    iContainer->DeactivateGc();
    
    CleanupStack::PopAndDestroy( grid );

    return KErrNone;
    }
