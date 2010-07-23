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
* Description:  Test eikclb.H
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

#include "testsdklists.h"
#include "testsdkcontainer.h"
#include "testsdklistscolumnlistbox.h"
#include "testsdklistscolumnlistboxeditor.h"

const TInt KExpectedCol = 1;
const TInt KColumn = 1;
const TInt KMaxLength= 20;
const TInt KGranularity = 4;
const TInt KTen = 10;
const TInt KThirty = 30;
// ============================ MEMBER FUNCTIONS ===============================

//========================= CColumnListBoxItemDrawer ===========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDConstructorL, "In TestCLBIDConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDConstructorL );
    // Print to log file
    iLog->Log( KTestCLBIDConstructorL );

    iItemDrawer = new( ELeave ) CColumnListBoxItemDrawer();
    STIF_ASSERT_NOT_NULL( iItemDrawer );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDConstructorWithParameterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDConstructorWithParameterL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDConstructorWithParameterL, "In TestCLBIDConstructorWithParameterL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDConstructorWithParameterL );
    // Print to log file
    iLog->Log( KTestCLBIDConstructorWithParameterL );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );

    listBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    MTextListBoxModel* model = listBox->Model();
    const CFont* font = CCoeEnv::Static()->NormalFont();
    CColumnListBoxData* data = CColumnListBoxData::NewL();
    CleanupStack::PushL( data );

    iItemDrawer = new( ELeave ) CColumnListBoxItemDrawer( model, font, data );
    STIF_ASSERT_NOT_NULL( iItemDrawer );

    CleanupStack::Pop( data );
    CleanupStack::PopAndDestroy();
    iListBox = STATIC_CAST( CEikListBox*, listBox );
    CleanupStack::Pop( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDDestructor
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDDestructor( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDDestructor, "In TestCLBIDDestructor" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDDestructor );
    // Print to log file
    iLog->Log( KTestCLBIDDestructor );

    delete iItemDrawer;
    iItemDrawer = NULL;
    iLog->Log( _L("delete iItemDrawer") );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDColumnData
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDColumnData( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDColumnData, "In TestCLBIDColumnData" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDColumnData );
    // Print to log file
    iLog->Log( KTestCLBIDColumnData );

    CColumnListBoxData* data = iItemDrawer->ColumnData();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDClearAllPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDClearAllPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDClearAllPropertiesL, "In TestCLBIDClearAllPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDClearAllPropertiesL );
    // Print to log file
    iLog->Log( KTestCLBIDClearAllPropertiesL );

    TInt err = KErrNone;
    TRAP( err, iItemDrawer->ClearAllPropertiesL() );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDSetPropertiesL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDSetPropertiesL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDSetPropertiesL, "In TestCLBIDSetPropertiesL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDSetPropertiesL );
    // Print to log file
    iLog->Log( KTestCLBIDSetPropertiesL );

    TInt err = KErrNone;
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue ); 
    TRAP( err, iItemDrawer->SetPropertiesL( 0, itemProp ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDProperties
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDProperties( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDProperties, "In TestCLBIDProperties" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDProperties );
    // Print to log file
    iLog->Log( KTestCLBIDProperties );

    TInt err = KErrNone;
    TListItemProperties itemProp;
    itemProp.SetBold( ETrue );
    itemProp.SetItalics( ETrue );
    itemProp.SetUnderlined( ETrue );
    itemProp.SetDimmed( ETrue );
    itemProp.SetColor( KRgbGray );
    itemProp.SetSeparatorAfter( ETrue ); 
    TRAP( err, iItemDrawer->SetPropertiesL( 0, itemProp ) );

    iItemDrawer->Properties( 0 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDDrawItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDDrawItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDDrawItemTextL, "In TestCLBIDDrawItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDDrawItemTextL );
    // Print to log file
    iLog->Log( KTestCLBIDDrawItemTextL );

    CEikColumnListBox* listBox = new( ELeave ) CAknSingleStyleListBox();
    CleanupStack::PushL( listBox );
    listBox->SetContainerWindowL( *iContainer );        
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    listBox->ConstructFromResourceL( reader );

    listBox->ItemDrawer()->DrawItemText( 0, listBox->Rect(), ETrue, ETrue, ETrue );

    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy( listBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDDrawItemMark
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDDrawItemMark( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDDrawItemText, "In TestCLBIDDrawItemText" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDDrawItemText );
    // Print to log file
    iLog->Log( KTestCLBIDDrawItemText );

    TPoint point( 0, 0 );
    iItemDrawer->DrawItemMark( ETrue, EFalse, point );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDMinimumCellSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDMinimumCellSize( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDMinimumCellSize, "In TestCLBIDMinimumCellSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDMinimumCellSize );
    // Print to log file
    iLog->Log( KTestCLBIDMinimumCellSize );

    TSize size = iItemDrawer->MinimumCellSize();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDItemWidthInPixels
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDItemWidthInPixels( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDItemWidthInPixels, "In TestCLBIDItemWidthInPixels" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDItemWidthInPixels );
    // Print to log file
    iLog->Log( KTestCLBIDItemWidthInPixels );

    TInt width = iItemDrawer->ItemWidthInPixels( 0 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBIDSetItemCellSize
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBIDSetItemCellSize( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBIDSetItemCellSize, "In TestCLBIDSetItemCellSize" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBIDSetItemCellSize );
    // Print to log file
    iLog->Log( KTestCLBIDSetItemCellSize );

    TSize size = iItemDrawer->MinimumCellSize();
    iItemDrawer->SetItemCellSize( size );

    return KErrNone;
    }

// ========================== class  CEikColumnListBox==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBConstructorL, "In TestCLBConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBConstructorL );
    // Print to log file
    iLog->Log( KTestCLBConstructorL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();

    CleanupStack::PushL( colListBox );
    STIF_ASSERT_NOT_NULL( colListBox );
    CleanupStack::PopAndDestroy( colListBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBConstructFromResourceL, "In TestCLBConstructFromResourceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBConstructFromResourceL );
    // Print to log file
    iLog->Log( KTestCLBConstructFromResourceL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBConstructL, "In TestCLBConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBConstructL );
    // Print to log file
    iLog->Log( KTestCLBConstructL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->ConstructL( iContainer, 0 );

    CleanupStack::PopAndDestroy( colListBox );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEditItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEditItemL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEditItemL, "In TestCLBEditItemL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEditItemL );
    // Print to log file
    iLog->Log( KTestCLBEditItemL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    colListBox->EditItemL( KColumn, KMaxLength );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBModelL, "In TestCLBModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBModelL );
    // Print to log file
    iLog->Log( KTestCLBModelL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CTextListBoxModel* model = colListBox->Model();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBItemDrawerL, "In TestCLBItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBItemDrawerL );
    // Print to log file
    iLog->Log( KTestCLBItemDrawerL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CColumnListBoxItemDrawer* itemDrawer = colListBox->ItemDrawer();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEnableExtendedDrawingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEnableExtendedDrawingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEnableExtendedDrawingL, "In TestCLBEnableExtendedDrawingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEnableExtendedDrawingL );
    // Print to log file
    iLog->Log( KTestCLBEnableExtendedDrawingL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TRAP( err, colListBox->EnableExtendedDrawingL() );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEnableStretchingL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEnableStretchingL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEnableStretchingL, "In TestCLBEnableStretchingL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEnableStretchingL );
    // Print to log file
    iLog->Log( KTestCLBEnableStretchingL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    colListBox->EnableStretching( ETrue );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBMakeViewClassInstanceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBMakeViewClassInstanceL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBMakeViewClassInstanceL, "In TestCLBMakeViewClassInstanceL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBMakeViewClassInstanceL );
    // Print to log file
    iLog->Log( KTestCLBMakeViewClassInstanceL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CListBoxView* view = colListBox->MakeViewClassInstanceL();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBFocusChangedL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBFocusChangedL, "In TestCLBFocusChangedL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBFocusChangedL );
    // Print to log file
    iLog->Log( KTestCLBFocusChangedL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    colListBox->FocusChanged( EDrawNow );
    colListBox->FocusChanged( ENoDrawNow );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBGetColorUseListL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBGetColorUseListL, "In TestCLBGetColorUseListL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBGetColorUseListL );
    // Print to log file
    iLog->Log( KTestCLBGetColorUseListL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CArrayFixFlat<TCoeColorUse>* colorUseList = new( ELeave ) 
        CArrayFixFlat<TCoeColorUse>( KGranularity );
    CleanupStack::PushL( colorUseList );

    TInt err = KErrNone;
    TRAP( err, colListBox->GetColorUseListL( *colorUseList ) );

    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBHandleResourceChangeL, "In TestCLBHandleResourceChangeL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBHandleResourceChangeL );
    // Print to log file
    iLog->Log( KTestCLBHandleResourceChangeL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    colListBox->HandleResourceChange( KAknsMessageSkinChange );    
    colListBox->HandleResourceChange( KEikDynamicLayoutVariantSwitch );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBMopSupplyObjectL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBMopSupplyObjectL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBMopSupplyObjectL, "In TestCLBMopSupplyObjectL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBMopSupplyObjectL );
    // Print to log file
    iLog->Log( KTestCLBMopSupplyObjectL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    TTypeUid::Ptr ptr = TTypeUid::Null();
    ptr = colListBox->MopSupplyObject( CEikDialog::ETypeId );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBHandlePointerEventL, "In TestCLBHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestCLBHandlePointerEventL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KTen, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, colListBox->HandlePointerEventL( event ) );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBCreateItemDrawerL, "In TestCLBCreateItemDrawerL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBCreateItemDrawerL );
    // Print to log file
    iLog->Log( KTestCLBCreateItemDrawerL );

    CTestSDKListsColumnListBox* colListBox = new( ELeave ) CTestSDKListsColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TRAP( err, colListBox->CreateItemDrawerL() );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBCreateModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBCreateModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBCreateModelL, "In TestCLBCreateModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBCreateModelL );
    // Print to log file
    iLog->Log( KTestCLBCreateModelL );

    CTestSDKListsColumnListBox* colListBox = new( ELeave ) CTestSDKListsColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    TInt err = KErrNone;
    TRAP( err, colListBox->CreateModelL() );

    CleanupStack::PopAndDestroy( 2 );

    return err;
    }

// ========================class CEikColumnListBoxEditor =======================

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEConstructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEConstructorL, "In TestCLBEConstructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEConstructorL );
    // Print to log file
    iLog->Log( KTestCLBEConstructorL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );
    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );
    STIF_ASSERT_NOT_NULL( colListBoxEditor );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEDestructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEDestructorL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEDestructorL, "In TestCLBEDestructorL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEDestructorL );
    // Print to log file
    iLog->Log( KTestCLBEDestructorL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );
    STIF_ASSERT_NOT_NULL( colListBoxEditor );
    CleanupStack::Pop( colListBoxEditor );

    delete colListBoxEditor;
    colListBoxEditor = NULL;

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEConstructL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEConstructL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEConstructL, "In TestCLBEConstructL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEConstructL );
    // Print to log file
    iLog->Log( KTestCLBEConstructL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );

    colListBoxEditor->ConstructL( 0 );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEItemTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEItemTextL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEItemTextL, "In TestCLBEItemTextL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEItemTextL );
    // Print to log file
    iLog->Log( KTestCLBEItemTextL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );

    TPtrC text = colListBoxEditor->ItemText();

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEUpdateModelL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEUpdateModelL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEUpdateModelL, "In TestCLBEUpdateModelL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEUpdateModelL );
    // Print to log file
    iLog->Log( KTestCLBEUpdateModelL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );

    TBool update = colListBoxEditor->UpdateModelL();

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEHandlePointerEventL, "In TestCLBEHandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEHandlePointerEventL );
    // Print to log file
    iLog->Log( KTestCLBEHandlePointerEventL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CEikColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CEikColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );
    
    TInt err = KErrNone;
    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KTen, KThirty );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;
    TRAP( err, colListBoxEditor->HandlePointerEventL( event ) );

    CleanupStack::PopAndDestroy( 3 );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBEColumnL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBEColumnL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBEColumnL, "In TestCLBEColumnL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBEColumnL );
    // Print to log file
    iLog->Log( KTestCLBEColumnL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CTestSDKListsColumnListBoxEditor* colListBoxEditor = 
        new ( ELeave ) CTestSDKListsColumnListBoxEditor( colListBox->Model() );
    CleanupStack::PushL( colListBoxEditor );

    colListBoxEditor->ConstructL( 1 );
    TInt column = colListBoxEditor->Column();
    STIF_ASSERT_EQUALS( KExpectedCol, column );

    CleanupStack::PopAndDestroy( 3 );

    return KErrNone;
    }

// ========================= class CColumnListBoxView ==========================
// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBVDrawL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBVDrawL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBVDrawL, "In TestCLBVDrawL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBVDrawL );
    // Print to log file
    iLog->Log( KTestCLBVDrawL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CColumnListBoxView* colLBViewr =
        static_cast<CColumnListBoxView*> ( colListBox->View() );
    STIF_ASSERT_NOT_NULL( colLBViewr );
    
    colLBViewr->Draw( NULL );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKLists::TestCLBVCalcBottomItemIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKLists::TestCLBVCalcBottomItemIndexL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KTestModule, "EIKCLBTestModule" );
    _LIT( KTestCLBVCalcBottomItemIndexL, "In TestCLBVCalcBottomItemIndexL" );
    TestModuleIf().Printf( 0, KTestModule, KTestCLBVCalcBottomItemIndexL );
    // Print to log file
    iLog->Log( KTestCLBVCalcBottomItemIndexL );

    CEikColumnListBox* colListBox = new( ELeave ) CEikColumnListBox();
    CleanupStack::PushL( colListBox );

    colListBox->SetContainerWindowL( *iContainer );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTLIST_LISTBOX );
    colListBox->ConstructFromResourceL( reader );

    CColumnListBoxView* colLBViewr =
        static_cast<CColumnListBoxView*> ( colListBox->View() );
    STIF_ASSERT_NOT_NULL( colLBViewr );
    
    colLBViewr->CalcBottomItemIndex();

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }
