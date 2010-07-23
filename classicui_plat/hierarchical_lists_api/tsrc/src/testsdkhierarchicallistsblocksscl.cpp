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
* Description:  test aknsinglecolumnstyletreelist.h 
*
*/

#include <aknsinglecolumnstyletreelist.h>

#include "testsdkhierarchicallists.h"
#include "testsdkhierarchicallistscontrol.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLNewL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLNewL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewL();
    CleanupStack::PushL( treeList );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLCNewL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLCNewL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewL( *control );
    CleanupStack::PushL( treeList );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLNewLC
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLCNewLC
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLCNewLC( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLAddSimpleDataRowL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLAddSimpleDataRowL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "SimpleData" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSimpleDataRowL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    _LIT( KSecondColumn, "SecondColumn" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, KFirstColumn, KSecondColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowCL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLAddCoreDataRowCL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    _LIT( KSecondColumn, "SecondColumn" );
    _LIT( KThirdColumn, "ThirdColumn" );
    
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, KFirstColumn, KSecondColumn, KThirdColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLAddSubtitleRowL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLAddSubtitleRowL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddSubtitleRow" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSubtitleRowL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLTextL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLTextL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "SimpleData" );
    TBuf<KLength> text( KText );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSimpleDataRowL( KAknTreeIIDRoot, text, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    TBuf<KLength> textGet = treeList->Text( id );
    STIF_ASSERT_EQUALS( 0, textGet.Compare( text ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLTextCIL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLTextCIL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    TBuf<KLength> firstColumn( KFirstColumn );
    _LIT( KSecondColumn, "SecondColumn" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, firstColumn, KSecondColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    TBuf<KLength> firstColumnGet = treeList->Text( id, 0 );
    STIF_ASSERT_EQUALS( 0, firstColumnGet.Compare( firstColumn ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLSetTextL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLSetTextL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "SimpleData" );
    TBuf<KLength> text( KText );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSimpleDataRowL( KAknTreeIIDRoot, text, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    _LIT( KTextSet, "Change" );
    TBuf<KLength> textSet( KTextSet );
    treeList->SetTextL( id, textSet, ETrue );
    
    TBuf<KLength> textGet = treeList->Text( id );
    STIF_ASSERT_EQUALS( 0, textGet.Compare( textSet ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLSetTextCIL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLSetTextCIL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    TBuf<KLength> firstColumn( KFirstColumn );
    _LIT( KSecondColumn, "SecondColumn" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, firstColumn, KSecondColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    _LIT( KFirstColumnSet, "Change" );
    TBuf<KLength> textSet( KFirstColumnSet );
    treeList->SetTextL( id, textSet, 0, ETrue );
    
    TBuf<KLength> firstColumnGet = treeList->Text( id, 0 );
    STIF_ASSERT_EQUALS( 0, firstColumnGet.Compare( textSet ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLIsEmphasisedL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLIsEmphasisedL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    _LIT( KSecondColumn, "SecondColumn" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, KFirstColumn, KSecondColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    treeList->SetEmphasis( id, EFalse, ETrue );
    STIF_ASSERT_FALSE( treeList->IsEmphasised( id ) );
    
    treeList->SetEmphasis( id, ETrue, ETrue );
    STIF_ASSERT_TRUE( treeList->IsEmphasised( id ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLSetEmphasisL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLSetEmphasisL( CStifItemParser& aItem )
    {
    return TestHLSCLIsEmphasisedL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLIsThirdColumnEnabledL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLIsThirdColumnEnabledL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KFirstColumn, "FirstColumn" );
    _LIT( KSecondColumn, "SecondColumn" );
    _LIT( KThirdColumn, "ThirdColumn" );
    
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddCoreDataRowL( KAknTreeIIDRoot, KFirstColumn, KSecondColumn, KThirdColumn, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    treeList->EnableThirdColumn( id, ETrue, ETrue );
    STIF_ASSERT_TRUE( treeList->IsThirdColumnEnabled( id ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLEnableThirdColumnL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLEnableThirdColumnL( CStifItemParser& aItem )
    {
    return TestHLSCLIsThirdColumnEnabledL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLIconL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "SimpleData" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSimpleDataRowL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    treeList->SetIcon( id, CAknSingleColumnStyleTreeList::ELeaf, 1, ETrue );
    STIF_ASSERT_EQUALS( 1, treeList->Icon( id, CAknSingleColumnStyleTreeList::ELeaf ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLSetIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLSetIconL( CStifItemParser& aItem )
    {
    return TestHLSCLIconL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSCLItemTypeL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSCLItemTypeL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleColumnStyleTreeList* treeList = CAknSingleColumnStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "SimpleData" );
    TUint32 flags = CAknSingleColumnStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddSimpleDataRowL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    STIF_ASSERT_TRUE( CAknSingleColumnStyleTreeList::ESimpleDataRow == treeList->ItemType( id ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }
