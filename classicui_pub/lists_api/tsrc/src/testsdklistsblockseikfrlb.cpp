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
* Description:  Test eikfrlb.h
*
*/

// [INCLUDE FILES]
#include <e32base.h>
#include <eikfrlb.h>
#include <aknlists.h>
#include <testsdklists.rsg>
#include <avkon.hrh>
#include <barsread.h>

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistsformattedcelllistbox.h"

const TInt KNum = 0;
const TInt KGranularity = 4;
const TInt KTen = 10;
const TInt KThirty = 30;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDConstructor, "In TestFCLBIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDConstructor );
    // Print to log file
    iLog->Log( KTestFCLBIDConstructor );

    CFormattedCellListBoxItemDrawer* formattedDrawer =
        new( ELeave ) CFormattedCellListBoxItemDrawer( NULL,
                CCoeEnv::Static()->NormalFont(), NULL );
    CleanupStack::PushL( formattedDrawer );
    STIF_ASSERT_NOT_NULL( formattedDrawer );
    CleanupStack::PopAndDestroy( formattedDrawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDDestructor, "In TestFCLBIDDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDDestructor );
    // Print to log file
    iLog->Log( KTestFCLBIDDestructor );

    CFormattedCellListBoxItemDrawer* formattedDrawer =
        new( ELeave ) CFormattedCellListBoxItemDrawer( NULL, CCoeEnv::Static()->NormalFont(), NULL );
    CleanupStack::PushL( formattedDrawer );
    STIF_ASSERT_NOT_NULL( formattedDrawer );
    CleanupStack::Pop( formattedDrawer );
    delete formattedDrawer;
    formattedDrawer = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDFormattedCellDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDFormattedCellDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDFormattedCellData, "In TestFCLBIDFormattedCellDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDFormattedCellData );
    // Print to log file
    iLog->Log( KTestFCLBIDFormattedCellData );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    CFormattedCellListBoxData* data = drawer->FormattedCellData();
    STIF_ASSERT_NOT_NULL( data );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDColumnDataL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDColumnDataL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDColumnData, "In TestFCLBIDColumnDataL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDColumnData );
    // Print to log file
    iLog->Log( KTestFCLBIDColumnData );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    CFormattedCellListBoxData* data = drawer->ColumnData();
    STIF_ASSERT_NOT_NULL( data );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDDrawEmptyItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDDrawEmptyItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDDrawEmptyItem, "In TestFCLBIDDrawEmptyItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDDrawEmptyItem );
    // Print to log file
    iLog->Log( KTestFCLBIDDrawEmptyItem );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TPoint pt( 0, 0 );
    drawer->DrawEmptyItem( KNum , pt, ETrue );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDSetTopItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDSetTopItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDSetTopItemIndex, "In TestFCLBIDSetTopItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDSetTopItemIndex );
    // Print to log file
    iLog->Log( KTestFCLBIDSetTopItemIndex );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TPoint pt( 0, 0 );
    drawer->SetTopItemIndex( KNum );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDClearAllPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDClearAllPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDClearAllPropertiesL, "In TestFCLBIDClearAllPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDClearAllPropertiesL );
    // Print to log file
    iLog->Log( KTestFCLBIDClearAllPropertiesL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TInt err = KErrNone;
    TRAP( err, drawer->ClearAllPropertiesL() );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDSetPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDSetPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDSetPropertiesL, "In TestFCLBIDSetPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDSetPropertiesL );
    // Print to log file
    iLog->Log( KTestFCLBIDSetPropertiesL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TInt err = KErrNone;
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue ); 
    TRAP( err, drawer->SetPropertiesL( KNum, itemProp ) );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDProperties, "In TestFCLBIDPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDProperties );
    // Print to log file
    iLog->Log( KTestFCLBIDProperties );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TListItemProperties getItemProp = drawer->Properties( KNum );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDDrawItemText, "In TestFCLBIDDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDDrawItemText );
    // Print to log file
    iLog->Log( KTestFCLBIDDrawItemText );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TRect rect = listBox->Rect();
    drawer->DrawItemText( KNum, rect, ETrue, ETrue, ETrue );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDDrawItemMarkL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDDrawItemMarkL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDDrawItemMarkL, "In TestFCLBIDDrawItemMarkL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDDrawItemMarkL );
    // Print to log file
    iLog->Log( KTestFCLBIDDrawItemMarkL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TPoint pt( 0, 0 );
    drawer->DrawItemMark( ETrue, EFalse, pt );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDMinimumCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDMinimumCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDMinimumCellSizeL, "In TestFCLBIDMinimumCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDMinimumCellSizeL );
    // Print to log file
    iLog->Log( KTestFCLBIDMinimumCellSizeL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TSize size = drawer->MinimumCellSize();
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDItemWidthInPixelsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDItemWidthInPixelsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDItemWidthInPixelsL, "In TestFCLBIDItemWidthInPixelsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDItemWidthInPixelsL );
    // Print to log file
    iLog->Log( KTestFCLBIDItemWidthInPixelsL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TInt pix = drawer->ItemWidthInPixels( KNum );
    STIF_ASSERT_NOT_EQUALS( KNum, pix );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBIDSetItemCellSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBIDSetItemCellSizeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBIDSetItemCellSizeL, "In TestFCLBIDSetItemCellSizeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBIDSetItemCellSizeL );
    // Print to log file
    iLog->Log( KTestFCLBIDSetItemCellSizeL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    CDesCArray* textArray = CCoeEnv::Static()->ReadDesCArrayResourceL( R_TESTLIST_ITEM_ARRAY );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    listBox->Model()->SetItemTextArray( textArray );
    listBox->Model()->SetOwnershipType( ELbmOwnsItemArray );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxItemDrawer* drawer = listBox->ItemDrawer();

    TSize size( 1, 1 );
    drawer->SetItemCellSize( size );
    iContainer->ResetControl();
    CleanupStack::Pop( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBConstructorL, "In TestFCLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBConstructorL );
    // Print to log file
    iLog->Log( KTestFCLBConstructorL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBConstructFromResourceL, "In TestFCLBConstructFromResourceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestFCLBConstructFromResourceL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBConstructL, "In TestFCLBConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBConstructL );
    // Print to log file
    iLog->Log( KTestFCLBConstructL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CAknDoubleStyle2ListBox();
    CleanupStack::PushL( listBox );
    listBox->ConstructL( iContainer, EAknListBoxSelectionList );
    CleanupStack::PopAndDestroy( listBox );
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBModelL, "In TestFCLBModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBModelL );
    // Print to log file
    iLog->Log( KTestFCLBModelL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    CTextListBoxModel* model = listBox->Model();
    STIF_ASSERT_NOT_NULL( model );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBItemDrawerL, "In TestFCLBItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBItemDrawerL );
    // Print to log file
    iLog->Log( KTestFCLBItemDrawerL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CFormattedCellListBoxItemDrawer* itemDrawer = listBox->ItemDrawer();
    STIF_ASSERT_NOT_NULL( itemDrawer );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBUseLogicalToVisualConversionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBUseLogicalToVisualConversionL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBItemDrawerL, "In TestFCLBUseLogicalToVisualConversionL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBItemDrawerL );
    // Print to log file
    iLog->Log( KTestFCLBItemDrawerL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    listBox->UseLogicalToVisualConversion( ETrue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBEnableExtendedDrawingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBEnableExtendedDrawingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBItemDrawerL, "In TestFCLBEnableExtendedDrawingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBItemDrawerL );
    // Print to log file
    iLog->Log( KTestFCLBItemDrawerL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    TInt err = KErrNone;
    TRAP( err, listBox->EnableExtendedDrawingL() );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBEnableStretchingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBEnableStretchingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBEnableStretchingL, "In TestFCLBEnableStretchingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBEnableStretchingL );
    // Print to log file
    iLog->Log( KTestFCLBEnableStretchingL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    listBox->EnableStretching( ETrue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBHideSecondRowL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBHideSecondRowL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBHideSecondRowL, "In TestFCLBHideSecondRowL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBHideSecondRowL );
    // Print to log file
    iLog->Log( KTestFCLBHideSecondRowL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    listBox->HideSecondRow( ETrue );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBMakeViewClassInstanceL, "In TestFCLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBMakeViewClassInstanceL );
    // Print to log file
    iLog->Log( KTestFCLBMakeViewClassInstanceL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CListBoxView* view = listBox->MakeViewClassInstanceL();
    STIF_ASSERT_NOT_NULL( view );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBFocusChangedL, "In TestFCLBFocusChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBFocusChangedL );
    // Print to log file
    iLog->Log( KTestFCLBFocusChangedL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    listBox->FocusChanged( EDrawNow );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBGetColorUseListL, "In TestFCLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBGetColorUseListL );
    // Print to log file
    iLog->Log( KTestFCLBGetColorUseListL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KGranularity );
    CleanupStack::PushL( colorUseList );
    TInt err = KErrNone;
    TRAP( err, listBox->GetColorUseListL( *colorUseList ) );
    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBHandleResourceChangeL, "In TestFCLBHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestFCLBHandleResourceChangeL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );
    listBox->HandleResourceChange( KAknsMessageSkinChange );
    listBox->HandleResourceChange( KEikDynamicLayoutVariantSwitch );
    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBHandlePointerEventL, "In TestFCLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestFCLBHandlePointerEventL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KTen, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, listBox->HandlePointerEventL( event ) );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBCreateItemDrawerL, "In TestFCLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBCreateItemDrawerL );
    // Print to log file
    iLog->Log( KTestFCLBCreateItemDrawerL );

    CTestSDKListsFormattedCellListBox* listBox =
            new( ELeave ) CTestSDKListsFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TRAP( err, listBox->CreateItemDrawerL() );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBAdjustRectHeightToWholeNumberOfItemsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBAdjustRectHeightToWholeNumberOfItemsL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBCreateItemDrawerL, "In TestFCLBAdjustRectHeightToWholeNumberOfItemsL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBCreateItemDrawerL );
    // Print to log file
    iLog->Log( KTestFCLBCreateItemDrawerL );

    CTestSDKListsFormattedCellListBox* listBox =
            new( ELeave ) CTestSDKListsFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TRect rect = listBox->Rect();
    TInt number = listBox->AdjustRectHeightToWholeNumberOfItems( rect );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBMopSupplyObjectL, "In TestFCLBMopSupplyObjectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBMopSupplyObjectL );
    // Print to log file
    iLog->Log( KTestFCLBMopSupplyObjectL );

    CTestSDKListsFormattedCellListBox* listBox =
            new( ELeave ) CTestSDKListsFormattedCellListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    TTypeUid uid = 0x000000;
    listBox->MopSupplyObject( uid );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBVDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBVDrawL, "In TestFCLBVDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBVDrawL );
    // Print to log file
    iLog->Log( KTestFCLBVDrawL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxView* view =
        static_cast<CFormattedCellListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    TRect viewRect = listBox->Rect();
    view->Draw( &viewRect );

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );
    iContainer->ResetControl();
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBVDrawEmptyListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBVDrawEmptyListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBVDrawEmptyListL, "In TestFCLBVDrawEmptyListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBVDrawEmptyListL );
    // Print to log file
    iLog->Log( KTestFCLBVDrawEmptyListL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxView* view =
        static_cast<CFormattedCellListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    TRect viewRect = listBox->Rect();
    view->DrawEmptyList( viewRect );

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );
    iContainer->ResetControl();
    listBox = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestFCLBVCalcBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestFCLBVCalcBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKFRLBTestModule" );
    _LIT( KTestFCLBVDrawEmptyListL, "In TestFCLBVCalcBottomItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestFCLBVDrawEmptyListL );
    // Print to log file
    iLog->Log( KTestFCLBVDrawEmptyListL );

    CEikFormattedCellListBox* listBox = new( ELeave ) CEikFormattedCellListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    iContainer->SetControlL( listBox );
    CFormattedCellListBoxView* view =
        static_cast<CFormattedCellListBoxView*> ( listBox->View() );
    STIF_ASSERT_NOT_NULL( view );

    view->CalcBottomItemIndex();

    CleanupStack::PopAndDestroy();
    CleanupStack::Pop( listBox );
    iContainer->ResetControl();
    listBox = NULL;

    return KErrNone;
    }
