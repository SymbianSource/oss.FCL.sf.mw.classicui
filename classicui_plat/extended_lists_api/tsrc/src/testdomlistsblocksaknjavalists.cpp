/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test aknjavalists.h
*
*/


#include <aknjavalists.h>

#include "testdomlists.h"
#include "testdomlistscontainer.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestDOMLists::TestLargeListDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestLargeListDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestLargeListDefCon, "In LargeListDefCon" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestLargeListDefCon );
    // Print to log file
    iLog->Log( KTestLargeListDefCon );

    CAknDouble2GraphicLargeStyleListBox* largeList = new ( ELeave )
            CAknDouble2GraphicLargeStyleListBox;
    CleanupStack::PushL( largeList );
    STIF_ASSERT_NOT_NULL( largeList );

    CleanupStack::PopAndDestroy( largeList );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestLargeListSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestLargeListSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestLargeListSizeChanged, "In LargeListSizeChanged" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestLargeListSizeChanged );
    // Print to log file
    iLog->Log( KTestLargeListSizeChanged );

    CAknDouble2GraphicLargeStyleListBox* largeList = new ( ELeave )
            CAknDouble2GraphicLargeStyleListBox;
    CleanupStack::PushL( largeList );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    largeList->ConstructL( container, EAknListBoxSelectionList );

    largeList->SizeChanged();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( largeList );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestLargeListMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestLargeListMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestLargeListMinimumSize, "In LargeListMinimumSize" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestLargeListMinimumSize );
    // Print to log file
    iLog->Log( KTestLargeListMinimumSize );

    CAknDouble2GraphicLargeStyleListBox* largeList = new ( ELeave )
            CAknDouble2GraphicLargeStyleListBox;
    CleanupStack::PushL( largeList );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    largeList->ConstructL( container, EAknListBoxSelectionList );

    TSize miniSize( largeList->MinimumSize() );
    STIF_ASSERT_TRUE( ( miniSize.iWidth >= 0 ) && ( miniSize.iHeight >= 0 ) );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( largeList );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestLargeListCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestLargeListCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestLargeListCreateItemDrawerL, "In LargeListCreateItemDrawerL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestLargeListCreateItemDrawerL );
    // Print to log file
    iLog->Log( KTestLargeListCreateItemDrawerL );

    CAknDouble2GraphicLargeStyleListBox* largeList = new ( ELeave )
            CAknDouble2GraphicLargeStyleListBox;
    CleanupStack::PushL( largeList );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    largeList->ConstructL( container, EAknListBoxSelectionList );

    largeList->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( largeList );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestListDefConL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestListDefConL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestListDefCon, "In ListDefCon" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestListDefCon );
    // Print to log file
    iLog->Log( KTestListDefCon );

    CAknSingle2GraphicStyleListBox* listBox = new ( ELeave )
            CAknSingle2GraphicStyleListBox;
    CleanupStack::PushL( listBox );
    STIF_ASSERT_NOT_NULL( listBox );

    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestListSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestListSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestListSizeChanged, "In ListSizeChanged" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestListSizeChanged );
    // Print to log file
    iLog->Log( KTestListSizeChanged );

    CAknSingle2GraphicStyleListBox* listBox = new ( ELeave )
            CAknSingle2GraphicStyleListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxSelectionList );

    listBox->SizeChanged();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestListMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestListMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestListMinimumSize, "In ListMinimumSize" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestListMinimumSize );
    // Print to log file
    iLog->Log( KTestListMinimumSize );

    CAknSingle2GraphicStyleListBox* listBox = new ( ELeave )
            CAknSingle2GraphicStyleListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxSelectionList );

    TSize miniSize( listBox->MinimumSize() );
    STIF_ASSERT_TRUE( ( miniSize.iWidth >= 0 ) && ( miniSize.iHeight >= 0 ) );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestListUseEmptyIconSpaceL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestListUseEmptyIconSpaceL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestListUseEmptyIconSpace, "In ListUseEmptyIconSpace" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestListUseEmptyIconSpace );
    // Print to log file
    iLog->Log( KTestListUseEmptyIconSpace );

    CAknSingle2GraphicStyleListBox* listBox = new ( ELeave )
            CAknSingle2GraphicStyleListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxSelectionList );

    listBox->UseEmptyIconSpace( ETrue );

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestDOMLists::TestListCreateItemDrawerL
// -----------------------------------------------------------------------------
//
TInt CTestDOMLists::TestListCreateItemDrawerL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( Ktestdomlists, "testdomlists" );
    _LIT( KTestListCreateItemDrawerL, "In ListCreateItemDrawerL" );
    TestModuleIf().Printf( 0, Ktestdomlists, KTestListCreateItemDrawerL );
    // Print to log file
    iLog->Log( KTestListCreateItemDrawerL );

    CAknSingle2GraphicStyleListBox* listBox = new ( ELeave )
            CAknSingle2GraphicStyleListBox;
    CleanupStack::PushL( listBox );
    CTestListsContainer* container = CTestListsContainer::NewL();
    CleanupStack::PushL( container );
    listBox->ConstructL( container, EAknListBoxSelectionList );

    listBox->CreateItemDrawerL();

    CleanupStack::PopAndDestroy( container );
    CleanupStack::PopAndDestroy( listBox );
    return KErrNone;

    }


