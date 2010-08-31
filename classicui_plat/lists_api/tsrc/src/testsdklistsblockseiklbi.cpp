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
* Description:  Test eiklbi.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <coemain.h>
#include <coeaui.h>
#include <eiklbi.h>
#include <barsread.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistslistitemdrawer.h"
#include "testsdkliststlitemdrawer.h"

const TInt KZero = 0;
const TInt KTen = 10;
_LIT( KTextItemDrawerMatchText, "Add Items" );
// ============================ MEMBER FUNCTIONS ===============================

// ===========================class CListItemDrawer=============================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDrawItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDrawItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDrawItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    TPoint pos( 1, 1 );
    drawer->CListItemDrawer::DrawItem( 0, pos, ETrue, ETrue, EFalse, EFalse );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDClearRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDClearRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDClearRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    TRect rect = iContainer->Rect();
    drawer->CListItemDrawer::ClearRect( rect );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDItemWidthInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDItemWidthInPixelsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDItemWidthInPixelsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::ItemWidthInPixels( 0 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMinimumCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMinimumCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMinimumCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::MinimumCellSize();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetGcL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetGcL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    drawer->CListItemDrawer::SetGc( &gc );
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDGcL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDGcL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    iContainer->ActivateGc();
    CWindowGc* gc = &( iContainer->SystemGc() );
    drawer->CListItemDrawer::SetGc( gc );
    CWindowGc* getGc = drawer->CListItemDrawer::Gc();
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetMarkColumnWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetMarkColumnWidthL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetMarkColumnWidthL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetMarkColumnWidth( KTen );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetMarkGutterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetMarkGutterL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetMarkGutterL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetMarkGutter( KTen );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMarkColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMarkColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMarkColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetMarkColumnWidth( KTen );
    TInt width = drawer->CListItemDrawer::MarkColumn();
    STIF_ASSERT_EQUALS( KTen, width );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMarkGutterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMarkGutterL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMarkGutterL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetMarkGutter( KTen );
    TInt width = drawer->CListItemDrawer::MarkGutter();
    STIF_ASSERT_EQUALS( KTen, width );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetItemCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetItemCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetItemCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    TSize size( KTen, KTen );
    drawer->CListItemDrawer::SetItemCellSize( size );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDItemCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDItemCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDItemCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    TSize size( KTen, KTen );
    drawer->CListItemDrawer::SetItemCellSize( size );
    TSize getSize = drawer->CListItemDrawer::ItemCellSize();
    STIF_ASSERT_EQUALS( size, getSize );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetViewRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetViewRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetViewRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    TRect rect = listBox->Rect();
    drawer->CListItemDrawer::SetViewRect( rect );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetDrawMarkL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetDrawMarkL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetDrawMarkL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetDrawMark( ETrue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMatcherCursorRectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMatcherCursorRectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMatcherCursorRectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::MatcherCursorRect( KMatchableText, 0, 0, 0 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMatcherCursorAscentL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMatcherCursorAscentL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMatcherCursorAscentL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::MatcherCursorAscent( 0 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDrawItemMarkL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDrawItemMarkL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDrawItemMarkL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::DrawItemMark( ETrue, EFalse, TPoint( 0, 0 ) );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetSymbolFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetSymbolFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetSymbolFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    const CFont* font = iEikonEnvPointer->NormalFont();
    drawer->CListItemDrawer::SetSymbolFont( font );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetVerticalInterItemGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetVerticalInterItemGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetVerticalInterItemGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetVerticalInterItemGap( KTen );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    CListBoxData* data = new( ELeave ) CListBoxData();
    CleanupStack::PushL( data );
    drawer->CListItemDrawer::SetData( data );
    CleanupStack::Pop( data );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDFontL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDFontL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDFontL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::Font( 0 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::Properties( 0 );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDrawFrameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDrawFrameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDrawFrameL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    TRect rect = iContainer->Rect();
    drawer->CListItemDrawer::DrawFrame( gc, rect, ETrue );
    iContainer->DeactivateGc();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetTextColor( KRgbBlue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetBackColor( KRgbBlue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetHighlightedTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetHighlightedTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetHighlightedTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetHighlightedTextColor( KRgbBlue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetHighlightedBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetHighlightedBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetHighlightedBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetHighlightedBackColor( KRgbMagenta );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetDimmedTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetDimmedTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetDimmedTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetDimmedTextColor( KRgbMagenta );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetDimmedBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetDimmedBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetDimmedBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetDimmedBackColor( KRgbMagenta );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetTextColor( KRgbBlue );
    TRgb color = drawer->CListItemDrawer::TextColor();
    STIF_ASSERT_EQUALS( KRgbBlue, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetBackColor( KRgbBlue );
    TRgb color = drawer->CListItemDrawer::BackColor();
    STIF_ASSERT_EQUALS( KRgbBlue, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDHighlightedTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDHighlightedTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDHighlightedTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetHighlightedTextColor( KRgbBlue );
    TRgb color = drawer->CListItemDrawer::HighlightedTextColor();
    STIF_ASSERT_EQUALS( KRgbBlue, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDHighlightedBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDHighlightedBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDHighlightedBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetHighlightedBackColor( KRgbMagenta );
    TRgb color = drawer->CListItemDrawer::HighlightedBackColor();
    STIF_ASSERT_EQUALS( KRgbMagenta, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDimmedTextColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDimmedTextColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDimmedTextColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetDimmedTextColor( KRgbMagenta );
    TRgb color = drawer->CListItemDrawer::DimmedTextColor();
    STIF_ASSERT_EQUALS( KRgbMagenta, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDimmedBackColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDimmedBackColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDimmedBackColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetDimmedBackColor( KRgbMagenta );
    TRgb color = drawer->CListItemDrawer::DimmedBackColor();
    STIF_ASSERT_EQUALS( KRgbMagenta, color );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::Flags();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetFlags( KTen );
    TInt flag = drawer->CListItemDrawer::Flags();
    STIF_ASSERT_EQUALS( KTen, flag );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDClearFlagsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDClearFlagsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDClearFlagsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::ClearFlags( KZero );
    TInt flag = drawer->CListItemDrawer::Flags();
    STIF_ASSERT_EQUALS( KZero, flag );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSkinBackgroundControlContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSkinBackgroundControlContextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSkinBackgroundControlContextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SkinBackgroundControlContext();
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetSkinEnabledL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetSkinEnabledL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetSkinEnabledL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListItemDrawer* drawer = listBox->ItemDrawer();

    drawer->CListItemDrawer::SetSkinEnabledL( ETrue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );
    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );
    CleanupStack::Pop( drawer );
    delete drawer;
    drawer = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDResetGcL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDResetGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDResetGcL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    drawer->SetGc( &gc );

    drawer->ResetGc();
    CleanupStack::PopAndDestroy( drawer );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDMarkColorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDMarkColorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDMarkColorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    drawer->MarkColor();

    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDVerticalInterItemGapL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDVerticalInterItemGapL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDVerticalInterItemGapL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    drawer->VerticalInterItemGap();

    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIDSetupGcL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIDSetupGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIDSetupGcL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CTestSDKListsListItemDrawer* drawer = new( ELeave ) CTestSDKListsListItemDrawer();
    CleanupStack::PushL( drawer );
    STIF_ASSERT_NOT_NULL( drawer );

    drawer->SetupGc( 0 );

    CleanupStack::PopAndDestroy( drawer );

    return KErrNone;
    }

// =========================class CTextListItemDrawer===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDConstructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer = new( ELeave ) CTextListItemDrawer();
    STIF_ASSERT_NOT_NULL( iTLIDrawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    delete iTLIDrawer;
    iTLIDrawer = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDConstructorWithParaL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDConstructorWithParaL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDConstructorWithParaL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();
    iTLIDrawer = new( ELeave ) CTextListItemDrawer( iTLBModel, font );
    STIF_ASSERT_NOT_NULL( iTLIDrawer );
    CleanupStack::Pop( textArray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    const CFont* font = iEikonEnvPointer->NormalFont();
    iTLIDrawer->ConstructL( font );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDDrawActualItem
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDDrawActualItem( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDDrawActualItem" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    iTLIDrawer->SetGc( &gc );
    TSize size = iTLIDrawer->ItemCellSize();
    TRect rect( TPoint( 0, 0 ), size ); 
    iTLIDrawer->DrawActualItem( 0, rect, ETrue, EFalse, EFalse, EFalse );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDItemWidthInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDItemWidthInPixels( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDItemWidthInPixels" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->ItemWidthInPixels( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDMinimumCellSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDMinimumCellSize( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDMinimumCellSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->MinimumCellSize();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetGc
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetGc( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDMinimumCellSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    iTLIDrawer->SetGc( &gc );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetCellWidthInChars
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetCellWidthInChars( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetCellWidthInChars" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->SetCellWidthInChars( KTen );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDMatcherCursorRect
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDMatcherCursorRect( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDMatcherCursorRect" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->MatcherCursorRect( KTextItemDrawerMatchText, 0, 0, 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDMatcherCursorAscent
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDMatcherCursorAscent( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDMatcherCursorAscent" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->MatcherCursorRect( KTextItemDrawerMatchText, 0, 0, 0 );
    iTLIDrawer->SetVerticalInterItemGap( KTen );
    iTLIDrawer->MatcherCursorAscent( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetFont
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetFont( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetFont" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    const CFont* font = iEikonEnvPointer->NormalFont();
    iTLIDrawer->SetFont( font );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetSearchStringL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetSearchStringL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetSearchStringL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    TPtrC ptr( KTextItemDrawerMatchText );
    iTLIDrawer->SetSearchStringL( &ptr );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDFont
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDFont( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDFont" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    const CFont* font = iEikonEnvPointer->NormalFont();
    iTLIDrawer->SetFont( font );
    const CFont* getFont = iTLIDrawer->Font( 0 );
    STIF_ASSERT_TRUE( font == getFont );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetItemMarkPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetItemMarkPosition( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetItemMarkPosition" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->SetItemMarkPosition( KTen );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDItemMarkPosition
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDItemMarkPosition( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDFont" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->SetItemMarkPosition( KTen );
    TInt pos = iTLIDrawer->ItemMarkPosition();
    STIF_ASSERT_EQUALS( KTen, pos );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetItemMarkReplacement
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetItemMarkReplacement( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetItemMarkReplacement" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    TPtrC ptr( KTextItemDrawerMatchText );    
    iTLIDrawer->SetItemMarkReplacement( ptr );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDItemMarkReplacement
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDItemMarkReplacement( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDItemMarkReplacement" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    TPtrC ptr( KTextItemDrawerMatchText );
    iTLIDrawer->SetItemMarkReplacement( ptr );
    TPtrC getPtr = iTLIDrawer->ItemMarkReplacement();
    TInt compare = ptr.Compare( getPtr );
    STIF_ASSERT_EQUALS( KZero, compare );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDSetItemMarkReverse
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDSetItemMarkReverse( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDSetItemMarkReverse" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->SetItemMarkReverse( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDItemMarkReverse
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDItemMarkReverse( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDItemMarkReverse" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iTLIDrawer->SetItemMarkReverse( ETrue );
    TBool flag = iTLIDrawer->ItemMarkReverse();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDDoDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDDoDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDDoDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTestSDKListsTLItemDrawer* drawer = new( ELeave ) CTestSDKListsTLItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    TPtrC ptr( KTextItemDrawerMatchText );
    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    gc.UseFont( font );
    drawer->SetGc( &gc );
    TSize size = drawer->ItemCellSize();
    TRect rect( TPoint( 0, 0 ), size ); 

    drawer->DoDrawItemText( ptr, rect, ETrue, EFalse, EFalse, 0 );
    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( textArray );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTestSDKListsTLItemDrawer* drawer = new( ELeave ) CTestSDKListsTLItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    drawer->SetGc( &gc );
    TSize size = drawer->ItemCellSize();
    TRect rect( TPoint( 0, 0 ), size ); 

    drawer->DrawItemText( 0, rect, ETrue, EFalse, EFalse );
    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( textArray );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestTLIDResetGcL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestTLIDResetGcL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestTLIDResetGcL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    CDesCArray* textArray = iEikonEnvPointer->ReadDesCArrayResourceL( 
            R_TESTLIST_ITEM_ARRAY_AGAIN );
    CleanupStack::PushL( textArray );
    iTLBModel = new( ELeave ) CTextListBoxModel();
    iTLBModel->ConstructL( textArray );

    const CFont* font = iEikonEnvPointer->NormalFont();

    CTestSDKListsTLItemDrawer* drawer = new( ELeave ) CTestSDKListsTLItemDrawer( iTLBModel, font );
    CleanupStack::PushL( drawer );

    iContainer->ActivateGc();
    CWindowGc& gc = iContainer->SystemGc();
    drawer->SetGc( &gc );

    drawer->ResetGc();
    CleanupStack::PopAndDestroy( drawer );
    CleanupStack::Pop( textArray );
    iContainer->DeactivateGc();

    return KErrNone;
    }

// =========================class TListItemProperties===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    TListItemProperties* property = new( ELeave ) TListItemProperties();
    CleanupStack::PushL( property );
    STIF_ASSERT_NOT_NULL( property );
    CleanupStack::PopAndDestroy( property );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetBold
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetBold( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetBoldL" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetBold( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsBold
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsBold( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsBold" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetBold( ETrue );
    TBool flag = iPropery.IsBold();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetItalics
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetItalics( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetItalics" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetItalics( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsItalics
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsItalics( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsItalics" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetItalics( ETrue );
    TBool flag = iPropery.IsItalics();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetUnderlined
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetUnderlined( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetUnderlined" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetUnderlined( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsUnderlined
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsUnderlined( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsUnderlined" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetUnderlined( ETrue );
    TBool flag = iPropery.IsUnderlined();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetDimmed
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetDimmed( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetDimmed" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetDimmed( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsDimmed
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsDimmed( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsDimmed" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetDimmed( ETrue );
    TBool flag = iPropery.IsDimmed();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetColor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetColor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetColor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetColor( KRgbGray );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPColor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPColor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPColor" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetColor( KRgbGray );
    TRgb color = iPropery.Color();
    STIF_ASSERT_EQUALS( KRgbGray, color );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetSeparatorAfter
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetSeparatorAfter( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetSeparatorAfter" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetSeparatorAfter( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsSeparatorAfter
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsSeparatorAfter( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsSeparatorAfter" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetSeparatorAfter( ETrue );
    TBool flag = iPropery.IsSeparatorAfter();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPSetHiddenSelection
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPSetHiddenSelection( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPSetHiddenSelection" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetHiddenSelection( ETrue );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestLIPIsSelectionHidden
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestLIPIsSelectionHidden( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKLBEDTestModule" );
    _LIT( KTestEIKLBED, "In TestLIPIsSelectionHidden" );
    TestModuleIf().Printf( 0, KTestModule, KTestEIKLBED );
    // Print to log file
    iLog->Log( KTestEIKLBED );

    iPropery.SetHiddenSelection( ETrue );
    TBool flag = iPropery.IsSelectionHidden();
    STIF_ASSERT_TRUE( flag );

    return KErrNone;
    }
