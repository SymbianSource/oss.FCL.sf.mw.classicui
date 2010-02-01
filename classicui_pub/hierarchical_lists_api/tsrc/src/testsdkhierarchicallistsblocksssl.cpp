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
* Description:  test aknsinglestyletreelist.h 
*
*/

#include <aknsinglestyletreelist.h>

#include "testsdkhierarchicallists.h"
#include "testsdkhierarchicallistscontrol.h"

const TInt KLength = 20;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLNewL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLNewL( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewL();
    CleanupStack::PushL( treeList );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLCNewL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLCNewL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewL( *control );
    CleanupStack::PushL( treeList );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLNewLC
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLNewLC( CStifItemParser& /*aItem*/ )
    {
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC();
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLCNewLC
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLCNewLC( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLAddLeafL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLAddLeafL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddLeaf" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddLeafL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLAddNodeL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLAddNodeL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddNode" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddNodeL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLSortL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLSortL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddLeaf" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddLeafL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    treeList->SortL( CAknSingleStyleTreeList::EAscendingAlphabeticalOrdering, ETrue );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLSetTextL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLSetTextL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddLeaf" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddLeafL( KAknTreeIIDRoot, KText, flags, ETrue );
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
// CTestSDKHierarchicalLists::TestHLSSLTextL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLTextL( CStifItemParser& aItem )
    {
    return TestHLSSLSetTextL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLSetIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLSetIconL( CStifItemParser& /*aItem*/ )
    {
    CTestControl* control = CTestControl::NewL();
    CleanupStack::PushL( control );
    STIF_ASSERT_NOT_NULL( control );
    
    CAknSingleStyleTreeList* treeList = CAknSingleStyleTreeList::NewLC( *control );
    STIF_ASSERT_NOT_NULL( treeList );
    
    _LIT( KText, "AddLeaf" );
    TUint32 flags = CAknSingleStyleTreeList::EPersistent;
    TAknTreeItemID id = treeList->AddLeafL( KAknTreeIIDRoot, KText, flags, ETrue );
    STIF_ASSERT_NOT_EQUALS( 0, id );
    
    treeList->SetIcon( id, CAknSingleStyleTreeList::ELeaf, 1, ETrue );
    STIF_ASSERT_EQUALS( 1, treeList->Icon( id, CAknSingleStyleTreeList::ELeaf ) );
    
    CleanupStack::PopAndDestroy( treeList );
    CleanupStack::PopAndDestroy( control );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKHierarchicalLists::TestHLSSLIconL
// -----------------------------------------------------------------------------
TInt CTestSDKHierarchicalLists::TestHLSSLIconL( CStifItemParser& aItem )
    {
    return TestHLSSLSetIconL( aItem );
    
    }
