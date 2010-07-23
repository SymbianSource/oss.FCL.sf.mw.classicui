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
* Description:  Test eikclbd.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <eikclb.h>
#include <eikclbd.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <aknlists.h>
#include <barsread.h>
#include <eikdialg.h>
#include <gdi.h>
#include <stringloader.h>
#include <avkon.hrh>
#include <aknslistboxbackgroundcontrolcontext.h>
#include <aknlayout2scalabledef.h>
#include <aknsconstants.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistsclbdata.h"

const TInt KColumn = 1;
const TInt KTen = 10;
_LIT( KColumnDataText, "Test text for DrawText" );
_LIT( KClippedText, "Test text" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDTColorsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDTColorsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDTColorsL, "In TestCLBDTColorsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDTColorsL );
    // Print to log file
    iLog->Log( KTestCLBDTColorsL );

    CColumnListBoxData::TColors* color = new( ELeave ) CColumnListBoxData::TColors();
    CleanupStack::PushL( color );
    STIF_ASSERT_NOT_NULL( color );
    CleanupStack::PopAndDestroy( color );
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDNewL, "In TestCLBDNewL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDNewL );
    // Print to log file
    iLog->Log( KTestCLBDNewL );

    CColumnListBoxData* data = CColumnListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDDestructorL, "In TestCLBDDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDDestructorL );
    // Print to log file
    iLog->Log( KTestCLBDDestructorL );

    CColumnListBoxData* data = CColumnListBoxData::NewL();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::Pop( data );
    delete data;
    data = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDLastColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDLastColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDLastColumnL, "In TestCLBDLastColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDLastColumnL );
    // Print to log file
    iLog->Log( KTestCLBDLastColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    STIF_ASSERT_NOT_NULL( data );
    TInt column = data->LastColumn();
    STIF_ASSERT_TRUE( column > 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnWidthPixelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnWidthPixelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnWidthPixelL, "In TestCLBDColumnWidthPixelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnWidthPixelL );
    // Print to log file
    iLog->Log( KTestCLBDColumnWidthPixelL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnWidthPixel( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnWidthPixelLL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnWidthPixelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDLastColumnL, "In TestCLBDLastColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDLastColumnL );
    // Print to log file
    iLog->Log( KTestCLBDLastColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetColumnWidthPixelL( KColumn, 1 );
    TInt column = data->ColumnWidthPixel( 1 );
    STIF_ASSERT_EQUALS( KColumn, column );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnHorizontalGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnHorizontalGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnHorizontalGapL, "In TestCLBDColumnHorizontalGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnHorizontalGapL );
    // Print to log file
    iLog->Log( KTestCLBDColumnHorizontalGapL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnHorizontalGap( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnHorizontalGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnHorizontalGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnHorizontalGapL, "In TestCLBDSetColumnHorizontalGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnHorizontalGapL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnHorizontalGapL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetColumnHorizontalGapL( 0, KColumn );
    TInt gap = data->ColumnHorizontalGap( 0 );
    STIF_ASSERT_EQUALS( KColumn, gap );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnBaselinePosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnBaselinePosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnBaselinePosL, "In TestCLBDColumnBaselinePosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnBaselinePosL );
    // Print to log file
    iLog->Log( KTestCLBDColumnBaselinePosL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnBaselinePos( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnBaselinePosL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnBaselinePosL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnBaselinePosL, "In TestCLBDSetColumnBaselinePosL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnBaselinePosL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnBaselinePosL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetColumnBaselinePosL( 0 , KColumn );
    TInt pos = data->ColumnBaselinePos( 0 );
    STIF_ASSERT_EQUALS( KColumn, pos );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnMarginsL, "In TestCLBDColumnMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnMarginsL );
    // Print to log file
    iLog->Log( KTestCLBDColumnMarginsL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnMargins( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnMarginsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnMarginsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnMarginsL, "In TestCLBDSetColumnMarginsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnMarginsL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnMarginsL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TMargins setMargins;
    setMargins.iBottom = 1;
    setMargins.iLeft = 1;
    setMargins.iRight = 1;
    setMargins.iTop = 1;
    data->SetColumnMarginsL( 0, setMargins );
    TMargins margins = data->ColumnMargins( 0 );
    STIF_ASSERT_TRUE( setMargins == margins );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnFontL, "In TestCLBDColumnFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnFontL );
    // Print to log file
    iLog->Log( KTestCLBDColumnFontL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnFont( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnFontL, "In TestCLBDSetColumnFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnFontL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnFontL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    const CFont* setFont = CCoeEnv::Static()->NormalFont();
    data->SetColumnFontL( 0, setFont );
    const CFont* font = data->ColumnFont( 0 );
    STIF_ASSERT_TRUE( setFont == font );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnAlignmentL, "In TestCLBDColumnAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnAlignmentL );
    // Print to log file
    iLog->Log( KTestCLBDColumnAlignmentL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnAlignment( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnAlignmentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnAlignmentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnAlignmentL, "In TestCLBDSetColumnAlignmentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnAlignmentL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnAlignmentL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    CGraphicsContext::TTextAlign setAlign = CGraphicsContext::ELeft;
    data->SetColumnAlignmentL( 0, setAlign );
    CGraphicsContext::TTextAlign align = data->ColumnAlignment( 0 );
    STIF_ASSERT_TRUE( setAlign == align );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnSeparatorStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnSeparatorStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnSeparatorStyleL, "In TestCLBDColumnSeparatorStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnSeparatorStyleL );
    // Print to log file
    iLog->Log( KTestCLBDColumnSeparatorStyleL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnSeparatorStyle( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnSeparatorStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnSeparatorStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnSeparatorStyleL, "In TestCLBDSetColumnSeparatorStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnSeparatorStyleL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnSeparatorStyleL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    CGraphicsContext::TPenStyle setPenStyle = CGraphicsContext::ENullPen;
    data->SetColumnSeparatorStyleL( 0, setPenStyle );
    CGraphicsContext::TPenStyle penStyle = data->ColumnSeparatorStyle( 0 );
    STIF_ASSERT_TRUE( setPenStyle == penStyle );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnIsOptionalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnIsOptionalL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnIsOptionalL, "In TestCLBDColumnIsOptionalL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnIsOptionalL );
    // Print to log file
    iLog->Log( KTestCLBDColumnIsOptionalL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnIsOptional( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetOptionalColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetOptionalColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetOptionalColumnL, "In TestCLBDSetOptionalColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetOptionalColumnL );
    // Print to log file
    iLog->Log( KTestCLBDSetOptionalColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TBool optional = ETrue;
    data->SetOptionalColumnL( 0, optional );
    TBool isOptional = data->ColumnIsOptional( 0 );
    STIF_ASSERT_TRUE( optional == isOptional );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnIsGraphicsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnIsGraphicsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnIsGraphicsL, "In TestCLBDColumnIsGraphicsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnIsGraphicsL );
    // Print to log file
    iLog->Log( KTestCLBDColumnIsGraphicsL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnIsGraphics( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetGraphicsColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetGraphicsColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetGraphicsColumnL, "In TestCLBDSetGraphicsColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetGraphicsColumnL );
    // Print to log file
    iLog->Log( KTestCLBDSetGraphicsColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TBool graphics = ETrue;
    data->SetGraphicsColumnL( 0, graphics );
    TBool isGraphics = data->ColumnIsGraphics( 0 );
    STIF_ASSERT_TRUE( graphics == isGraphics );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnIsNumberL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnIsNumberL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnIsNumberL, "In TestCLBDColumnIsNumberL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnIsNumberL );
    // Print to log file
    iLog->Log( KTestCLBDColumnIsNumberL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnIsNumber( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetNumberColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetNumberColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetNumberColumnL, "In TestCLBDSetNumberColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetNumberColumnL );
    // Print to log file
    iLog->Log( KTestCLBDSetNumberColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TInt setIsNumber = ETrue;
    data->SetNumberColumnL( 0, setIsNumber );
    TInt isNumber = data->ColumnIsNumber( 0 );
    STIF_ASSERT_TRUE( setIsNumber == isNumber );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDIconArrayL, "In TestCLBDIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDIconArrayL );
    // Print to log file
    iLog->Log( KTestCLBDIconArrayL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->IconArray();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetIconArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetIconArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetIconArrayL, "In TestCLBDSetIconArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetIconArrayL );
    // Print to log file
    iLog->Log( KTestCLBDSetIconArrayL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    CArrayPtr<CGulIcon>* icons = new( ELeave ) CArrayPtrFlat<CGulIcon>( KTen );
    CleanupStack::PushL( icons );
    data->SetIconArray( icons );
    CArrayPtr<CGulIcon>* getIcons = data->IconArray();
    STIF_ASSERT_TRUE( icons == getIcons );

    iContainer->ResetControl();
    CleanupStack::Pop( icons );
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    icons = NULL;
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDColumnTextClipGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDColumnTextClipGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDColumnTextClipGapL, "In TestCLBDColumnTextClipGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDColumnTextClipGapL );
    // Print to log file
    iLog->Log( KTestCLBDColumnTextClipGapL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->ColumnTextClipGap( 0 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnTextClipGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnTextClipGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnTextClipGapL, "In TestCLBDSetColumnTextClipGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnTextClipGapL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnTextClipGapL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetColumnTextClipGapL( 0, KColumn );
    TInt textClipGap = data->ColumnTextClipGap( 0 );
    STIF_ASSERT_EQUALS( KColumn, textClipGap );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDFontL, "In TestCLBDFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDFontL );
    // Print to log file
    iLog->Log( KTestCLBDFontL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    const CFont* setFont = CCoeEnv::Static()->NormalFont();
    data->SetColumnFontL( 0, setFont );
    TListItemProperties* property = new( ELeave ) TListItemProperties();
    CleanupStack::PushL( property );
    CFont* font = data->Font( *property, 0 );
    STIF_ASSERT_NOT_NULL( font );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDMakeColumnRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDMakeColumnRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDMakeColumnRectL, "In TestCLBDMakeColumnRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDMakeColumnRectL );
    // Print to log file
    iLog->Log( KTestCLBDMakeColumnRectL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TRect rect = colListBox->Rect();
    TBool flag = data->MakeColumnRect( 0, rect );
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDDrawL, "In TestCLBDDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDDrawL );
    // Print to log file
    iLog->Log( KTestCLBDDrawL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TListItemProperties* property = new( ELeave ) TListItemProperties();
    CleanupStack::PushL( property );
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    gc.UseFont( CCoeEnv::Static()->NormalFont() );
    HBufC* buf = StringLoader::LoadLC( R_TESTLIST_DRAWBUFF );
    TRect rect = colListBox->Rect();
    TBool highlight = ETrue;
    CColumnListBoxData::TColors color;

    data->Draw( *property, gc, buf, rect, highlight, color );

    iContainer->ResetControl();
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 3 );
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetSeparatorLinePositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetSeparatorLinePositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetSeparatorLinePositionL, "In TestCLBDSetSeparatorLinePositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetSeparatorLinePositionL );
    // Print to log file
    iLog->Log( KTestCLBDSetSeparatorLinePositionL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetSeparatorLinePosition( ENoLine );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSeparatorLinePositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSeparatorLinePositionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSeparatorLinePositionL, "In TestCLBDSeparatorLinePositionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSeparatorLinePositionL );
    // Print to log file
    iLog->Log( KTestCLBDSeparatorLinePositionL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetSeparatorLinePosition( ENoLine );
    TAknSeparatorLinePosition linePos = data->SeparatorLinePosition();
    STIF_ASSERT_EQUALS( linePos, ENoLine );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDLayoutDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDLayoutDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDLayoutDataL, "In TestCLBDLayoutDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDLayoutDataL );
    // Print to log file
    iLog->Log( KTestCLBDLayoutDataL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    CAknLayoutData* layout = data->LayoutData();
    STIF_ASSERT_NULL( layout );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDLayoutInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDLayoutInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDLayoutInitL, "In TestCLBDLayoutInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDLayoutInitL );
    // Print to log file
    iLog->Log( KTestCLBDLayoutInitL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetLayoutInit( ETrue );
    TBool flag = data->LayoutInit();
    STIF_ASSERT_FALSE( flag );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetLayoutInitL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetLayoutInitL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetLayoutInitL, "In TestCLBDSetLayoutInitL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetLayoutInitL );
    // Print to log file
    iLog->Log( KTestCLBDSetLayoutInitL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    data->SetLayoutInit( ETrue );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnUnderlinedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnUnderlinedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnUnderlinedL, "In TestCLBDSetColumnUnderlinedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnUnderlinedL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnUnderlinedL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();
    TBitFlags32 flags;
    data->SetColumnUnderlined( flags );
    iContainer->ResetControl();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDControlL, "In TestCLBDControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDControlL );
    // Print to log file
    iLog->Log( KTestCLBDControlL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    data->SetControl( listBox );
    CCoeControl* control = data->Control();
    STIF_ASSERT_TRUE( listBox == control );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetControlL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetControlL, "In TestCLBDSetControlL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetControlL );
    // Print to log file
    iLog->Log( KTestCLBDSetControlL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    data->SetControl( listBox );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSkinBackgroundContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSkinBackgroundContextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSkinBackgroundContextL, "In TestCLBDSkinBackgroundContextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSkinBackgroundContextL );
    // Print to log file
    iLog->Log( KTestCLBDSkinBackgroundContextL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SetSkinEnabledL( ETrue );
    MAknsControlContext* context = data->SkinBackgroundContext();
    STIF_ASSERT_NOT_NULL( context );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetSkinStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetSkinStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetSkinStyleL, "In TestCLBDSetSkinStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetSkinStyleL );
    // Print to log file
    iLog->Log( KTestCLBDSetSkinStyleL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = colListBox->Rect();
    data->SetSkinStyle( &itemID, rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetListEndSkinStyleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetListEndSkinStyleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetListEndSkinStyleL, "In TestCLBDSetListEndSkinStyleL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetListEndSkinStyleL );
    // Print to log file
    iLog->Log( KTestCLBDSetListEndSkinStyleL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = colListBox->Rect();
    data->SetListEndSkinStyle( &itemID, rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetSkinHighlightFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetSkinHighlightFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetSkinHighlightFrameL, "In TestCLBDSetSkinHighlightFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetSkinHighlightFrameL );
    // Print to log file
    iLog->Log( KTestCLBDSetSkinHighlightFrameL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRect rect = colListBox->Rect();
    data->SetSkinHighlightFrame( &itemID, &itemID );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetSkinEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetSkinEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetSkinEnabledL, "In TestCLBDSetSkinEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetSkinEnabledL );
    // Print to log file
    iLog->Log( KTestCLBDSetSkinEnabledL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SetSkinEnabledL( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDEnableMarqueeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDEnableMarqueeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDEnableMarqueeL, "In TestCLBDEnableMarqueeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDEnableMarqueeL );
    // Print to log file
    iLog->Log( KTestCLBDEnableMarqueeL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->EnableMarqueeL( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetColumnFontForRowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetColumnFontForRowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetColumnFontForRowL, "In TestCLBDSetColumnFontForRowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetColumnFontForRowL );
    // Print to log file
    iLog->Log( KTestCLBDSetColumnFontForRowL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SetColumnFontForRowL( 0, 0, CCoeEnv::Static()->NormalFont() );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDRowAndColumnFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDRowAndColumnFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDRowAndColumnFontL, "In TestCLBDRowAndColumnFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDRowAndColumnFontL );
    // Print to log file
    iLog->Log( KTestCLBDRowAndColumnFontL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    const CFont* setFont = CCoeEnv::Static()->NormalFont();
    data->SetColumnFontForRowL( 0, 0, setFont );
    const CFont* font = data->RowAndColumnFont( 0, 0 );
    STIF_ASSERT_TRUE( setFont == font );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetSubCellIconSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetSubCellIconSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetSubCellIconSizeL, "In TestCLBDSetSubCellIconSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetSubCellIconSizeL );
    // Print to log file
    iLog->Log( KTestCLBDSetSubCellIconSizeL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TSize size;
    size.iHeight = 1;
    size.iWidth = 1;
    data->SetSubCellIconSize( 0, size );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDHighlightAnimL, "In TestCLBDHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDHighlightAnimL );
    // Print to log file
    iLog->Log( KTestCLBDHighlightAnimL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->HighlightAnim();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDAboutToDrawHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDAboutToDrawHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDAboutToDrawHighlightAnimL, "In TestCLBDAboutToDrawHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDAboutToDrawHighlightAnimL );
    // Print to log file
    iLog->Log( KTestCLBDAboutToDrawHighlightAnimL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->AboutToDrawHighlightAnim();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetHighlightAnimBackgroundDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetHighlightAnimBackgroundDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetHighlightAnimBackgroundDrawerL, "In TestCLBDSetHighlightAnimBackgroundDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetHighlightAnimBackgroundDrawerL );
    // Print to log file
    iLog->Log( KTestCLBDSetHighlightAnimBackgroundDrawerL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TTestListBoxAnimBgDrawer drawer;
    data->SetHighlightAnimBackgroundDrawer( &drawer );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetItemCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetItemCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetItemCellSizeL, "In TestCLBDSetItemCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetItemCellSizeL );
    // Print to log file
    iLog->Log( KTestCLBDSetItemCellSizeL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TSize sizeInPixels;
    sizeInPixels.SetSize( 1, 1 );
    data->SetItemCellSize( sizeInPixels );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDHasHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDHasHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDHasHighlightAnimL, "In TestCLBDHasHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDHasHighlightAnimL );
    // Print to log file
    iLog->Log( KTestCLBDHasHighlightAnimL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->HasHighlightAnim();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDDrawHighlightAnimL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDDrawHighlightAnimL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDDrawHighlightAnimL, "In TestCLBDDrawHighlightAnimL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDDrawHighlightAnimL );
    // Print to log file
    iLog->Log( KTestCLBDDrawHighlightAnimL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TRect rect = colListBox->Rect();
    CFbsBitGc* bitGc = CFbsBitGc ::NewL();
    CleanupStack::PushL( bitGc );
    data->DrawHighlightAnim( *bitGc, rect );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy( 2 );
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetGraphicSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetGraphicSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetGraphicSubCellL, "In TestCLBDSetGraphicSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetGraphicSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDSetGraphicSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TInt err = KErrNone;
    TAknWindowLineLayout layout;
    TRAP( err, data->SetGraphicSubCellL( 0, layout ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetTextSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetTextSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetTextSubCellL, "In TestCLBDSetTextSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetTextSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDSetTextSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TInt err = KErrNone;
    TAknTextLineLayout layout;
    TRAP( err, data->SetTextSubCellL( 0, layout ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetConditionalSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetConditionalSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetConditionalSubCellL, "In TestCLBDSetConditionalSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetConditionalSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDSetConditionalSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TInt err = KErrNone;
    TAknTextLineLayout layout;
    TRAP( err, data->SetConditionalSubCellL( 0, layout, 0 ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSubCellsMightIntersectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSubCellsMightIntersectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSubCellsMightIntersectL, "In TestCLBDSubCellsMightIntersectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSubCellsMightIntersectL );
    // Print to log file
    iLog->Log( KTestCLBDSubCellsMightIntersectL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SubCellsMightIntersect( ETrue );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetStretchableGraphicSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetStretchableGraphicSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetStretchableGraphicSubCellL, "In TestCLBDSetStretchableGraphicSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetStretchableGraphicSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDSetStretchableGraphicSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknWindowComponentLayout comLayout;
    TInt err = KErrNone;
    TRAP( err, data->SetStretchableGraphicSubCellL( 0, comLayout, comLayout ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDResetSLSubCellArrayL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDResetSLSubCellArrayL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDResetSLSubCellArrayL, "In TestCLBDResetSLSubCellArrayL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDResetSLSubCellArrayL );
    // Print to log file
    iLog->Log( KTestCLBDResetSLSubCellArrayL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->ResetSLSubCellArray();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDStretchingEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDStretchingEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDStretchingEnabledL, "In TestCLBDStretchingEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDStretchingEnabledL );
    // Print to log file
    iLog->Log( KTestCLBDStretchingEnabledL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TBool flag = data->StretchingEnabled();
    STIF_ASSERT_TRUE( flag );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetMarqueeParamsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetMarqueeParamsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetMarqueeParamsL, "In TestCLBDSetMarqueeParamsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetMarqueeParamsL );
    // Print to log file
    iLog->Log( KTestCLBDSetMarqueeParamsL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SetMarqueeParams( 1, 6, 1000000 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetMarqueeParamsWithIntervalL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetMarqueeParamsWithIntervalL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetMarqueeParamsWithIntervalL, "In TestCLBDSetMarqueeParamsWithIntervalL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetMarqueeParamsWithIntervalL );
    // Print to log file
    iLog->Log( KTestCLBDSetMarqueeParamsWithIntervalL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->SetMarqueeParams( 2, 8, 1000000, 100000 );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDCurrentItemTextWasClippedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDCurrentItemTextWasClippedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDCurrentItemTextWasClippedL, "In TestCLBDCurrentItemTextWasClippedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDCurrentItemTextWasClippedL );
    // Print to log file
    iLog->Log( KTestCLBDCurrentItemTextWasClippedL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    data->CurrentItemTextWasClipped();

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetStretchableTextSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetStretchableTextSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDSetStretchableTextSubCellL, "In TestCLBDSetStretchableTextSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDSetStretchableTextSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDSetStretchableTextSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknTextComponentLayout comLayout;
    TInt err = KErrNone;
    TRAP( err, data->SetStretchableTextSubCellL( 0, comLayout, comLayout ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDSetStretchableConditionalSubCellL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDSetStretchableConditionalSubCellL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDConditionalSubCellL, "In TestCLBDSetStretchableConditionalSubCellL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDConditionalSubCellL );
    // Print to log file
    iLog->Log( KTestCLBDConditionalSubCellL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( colListBox );
    CColumnListBoxData* data = colListBox->ItemDrawer()->ColumnData();

    TAknTextComponentLayout comLayout;
    TInt err = KErrNone;
    TRAP( err, data->SetStretchableConditionalSubCellL( 0, comLayout, comLayout, 0, 0 ) );

    iContainer->ResetControl();
    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDConstructorL, "In TestCLBDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDConstructorL );
    // Print to log file
    iLog->Log( KTestCLBDConstructorL );

    CTestSDKColumnListBoxData* data = new( ELeave ) CTestSDKColumnListBoxData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    CleanupStack::PopAndDestroy( data );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDConstructLDL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDConstructLDL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDConstructLDL, "In TestCLBDConstructLDL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDConstructLDL );
    // Print to log file
    iLog->Log( KTestCLBDConstructLDL );

    CTestSDKColumnListBoxData* data = new( ELeave ) CTestSDKColumnListBoxData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    TInt err = KErrNone;
    TRAP( err, data->ConstructLD() );
    if ( err == KErrNone )
        {
        CleanupStack::PopAndDestroy( data );
        }
    else
        {
        CleanupStack::Pop( data );
        data = NULL;
        }

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDConstructLDWithParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDConstructLDWithParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDConstructLDWithParaL, "In TestCLBDConstructLDWithParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDConstructLDWithParaL );
    // Print to log file
    iLog->Log( KTestCLBDConstructLDWithParaL );

    CTestSDKColumnListBoxData* data = new( ELeave ) CTestSDKColumnListBoxData();
    CleanupStack::PushL( data );
    STIF_ASSERT_NOT_NULL( data );
    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TInt err = KErrNone;
    TRAP( err, data->ConstructLD( itemID ) );
    if ( err == KErrNone )
        {
        CleanupStack::PopAndDestroy( data );
        }
    else
        {
        CleanupStack::Pop( data );
        data = NULL;
        }

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBDDrawTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBDDrawTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBDDrawTextL, "In TestCLBDDrawTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBDDrawTextL );
    // Print to log file
    iLog->Log( KTestCLBDDrawTextL );

    CEikColumnListBox* colListBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_SINGLE_STYLE );
    colListBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();

    iContainer->SetControlL( colListBox );

    CTestSDKColumnListBoxData* data = new( ELeave ) CTestSDKColumnListBoxData();
    CleanupStack::PushL( data );
    TInt err = KErrNone;
    TAknsItemID itemID;
    itemID.Set( 0x2001CB80, 1 );
    TRAP( err, data->ConstructLD( itemID ) );
    if ( err != KErrNone )
        {
        CleanupStack::Pop( data );
        data = NULL;
        return err;
        }

    CColumnListBoxData* listBoxData = colListBox->ItemDrawer()->ColumnData();
    STIF_ASSERT_NOT_NULL( listBoxData );
    delete listBoxData;
    listBoxData = NULL;
    colListBox->ItemDrawer()->SetData( data );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    gc.UseFont( CCoeEnv::Static()->NormalFont() );
    TRect rect = iContainer->Rect();
    rect.iBr.iX = rect.iTl.iX + 
        colListBox->ItemDrawer()->ItemCellSize().iWidth;
    rect.iBr.iY = rect.iTl.iY + 
        colListBox->ItemDrawer()->ItemCellSize().iHeight;

    data->DrawText( gc, rect,  KColumnDataText, KClippedText, 
            0, CGraphicsContext::ELeft, *CCoeEnv::Static()->NormalFont(), ETrue, EFalse ); 
    iContainer->ResetControl();
    iContainer->DeactivateGc();
    CleanupStack::Pop( data );
    data = NULL;
    CleanupStack::Pop( colListBox );
    colListBox = NULL;

    return KErrNone;
    }
