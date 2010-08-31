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
* Description:  test akntabgrp.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>

#include <coecntrl.h>
#include <barsread.h>
#include <fbs.h>
#include <aknconsts.h>
#include <coedef.h>
#include <coecobs.h>
#include <aknnavide.h> 
#include <akniconutils.h> 

#include <testsdktabgrp.rsg>
#include "testsdktabgrp.h"
#include "testsdktabgrp.hrh"
#include "testsdktabgrpcontrol.h"

// CONSTANTS
const TInt KNum = 1;
const TInt KPointX = 10;
const TInt KPointY = 30;
const TInt KWidth = 100;
const TInt KHeight = 100;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTestSDKTabGroup::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNewL", CTestSDKTabGroup::TestTabGroupNewL ),
        ENTRY( "TestNewLC", CTestSDKTabGroup::TestTabGroupNewLCL ),
        ENTRY( "TestAddTabL", CTestSDKTabGroup::TestTabGroupAddTabL ),
        ENTRY( "TestReplaceTabL", CTestSDKTabGroup::TestTabGroupReplaceTabL ),
        ENTRY( "TestReplaceTabTextL",
                CTestSDKTabGroup::TestTabGroupReplaceTabTextL ),
        ENTRY( "TestDeleteTabL", CTestSDKTabGroup::TestTabGroupDeleteTabL ),
        ENTRY( "TestSetActiveTabById",
                CTestSDKTabGroup::TestTabGroupSetActiveTabByIdL ),
        ENTRY( "TestSetActiveTabByIndex",
                CTestSDKTabGroup::TestTabGroupSetActiveTabByIndexL ),
        ENTRY( "TestActiveTabId", CTestSDKTabGroup::TestTabGroupActiveTabIdL ),
        ENTRY( "TestActiveTabIndex",
                CTestSDKTabGroup::TestTabGroupActiveTabIndexL ),
        ENTRY( "TestSetTabFixedWidthL",
                CTestSDKTabGroup::TestTabGroupSetTabFixedWidthL ),
        ENTRY( "TestDimTab", CTestSDKTabGroup::TestTabGroupDimTabL ),
        ENTRY( "TestIsTabDimmed", CTestSDKTabGroup::TestTabGroupIsTabDimmedL ),
        ENTRY( "TestTabIndexFromId",
                CTestSDKTabGroup::TestTabGroupTabIndexFromIdL ),
        ENTRY( "TestTabIdFromIndex",
                CTestSDKTabGroup::TestTabGroupTabIdFromIndexL ),
        ENTRY( "TestTabCount", CTestSDKTabGroup::TestTabGroupTabCountL ),
        ENTRY( "TestSetObserver", CTestSDKTabGroup::TestTabGroupSetObserverL ),
        ENTRY( "TestMinimumSize", CTestSDKTabGroup::TestTabGroupMinimumSizeL ),
        ENTRY( "TestOfferKeyEventL",
                CTestSDKTabGroup::TestTabGroupOfferKeyEventL ),
        ENTRY( "TestGetColorUseListL",
                CTestSDKTabGroup::TestTabGroupGetColorUseListL ),
        ENTRY( "TestHandleResourceChange",
                CTestSDKTabGroup::TestTabGroupHandleResourceChangeL ),
        ENTRY( "TestHandlePointerEventL",
                CTestSDKTabGroup::TestTabGroupHandlePointerEventL ),
        ENTRY( "TestHandleControlEventL",
                CTestSDKTabGroup::TestTabGroupHandleControlEventL ),
        ENTRY( "TestPrepareContext",
                CTestSDKTabGroup::TestTabGroupPrepareContextL ),
        ENTRY( "TestHandleNaviDecoratorEventL",
                CTestSDKTabGroup::TestTabGroupHandleNaviDecoratorEventL ),
        ENTRY( "TestSizeChanged",
                CTestSDKTabGroup::TestTabGroupSizeChangedL ),
        ENTRY( "TestCountComponentControls",
                CTestSDKTabGroup::TestTabGroupCountComponentControlsL ),
        ENTRY( "TestComponentControl",
                CTestSDKTabGroup::TestTabGroupComponentControlL ),
        ENTRY( "TestFocusChanged",
                CTestSDKTabGroup::TestTabGroupFocusChangedL ),
        ENTRY( "TestSetTabMultiColorMode",
                CTestSDKTabGroup::TestTabGroupSetTabMultiColorModeL ),

        // [test cases entries]

        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupNewL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KNewL, "In NewL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KNewL );
    // Print to log file
    iLog->Log( KNewL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );
    STIF_ASSERT_NOT_NULL( tabGroup );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupNewLCL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupNewLCL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KNewLC, "In NewLC" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KNewLC );
    // Print to log file
    iLog->Log( KNewLC );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewLC( *testControl );
    STIF_ASSERT_NOT_NULL( tabGroup );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupAddTabL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupAddTabL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KAddTabL, "In AddTabL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KAddTabL );
    // Print to log file
    iLog->Log( KAddTabL );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    _LIT( KText, "AddNewTab" );
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile,
            EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );

    switch( num )
        {
        case 1:
            {
            TResourceReader reader;
            iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
            
            TInt id = ETab;
            TInt tabId = tabGroup->AddTabL( reader );
            STIF_ASSERT_EQUALS( id, tabId );
            
            CleanupStack::PopAndDestroy();
            break;
            }
        case 2:
            {
            tabGroup->AddTabL( ETab, KText );
            break;
            }
        case 3:
            {
            tabGroup->AddTabL( ETab, KText, bitmap, mask );
            break;
            }
        case 4:
            {
            tabGroup->AddTabL( ETab, bitmap, mask );
            break;
            }
        default:
            CleanupStack::Pop( mask );
            CleanupStack::Pop( bitmap );
            CleanupStack::PopAndDestroy( tabGroup );
            CleanupStack::PopAndDestroy( testControl );
            return KErrNotSupported;
        }

    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupReplaceTabL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupReplaceTabL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KReplaceTabL, "In ReplaceTabL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KReplaceTabL );
    // Print to log file
    iLog->Log( KReplaceTabL );

    TInt num = 0;
    TInt err = aItem.GetNextInt( num );
    if ( err != KErrNone )
        {
        return err;
        }

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    _LIT( KReplaceText, "ReplaceTab" );
    _LIT( KBitmapFile, "z:\\resource\\apps\\avkon2.mbm" );
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;
    AknIconUtils::CreateIconL( bitmap, mask, KBitmapFile,
            EMbmAvkonQgn_indi_mic, EMbmAvkonQgn_indi_mic_mask );
    CleanupStack::PushL( bitmap );
    CleanupStack::PushL( mask );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    switch( num )
        {
        case 1:
            {
            iEikonEnvPointer->CreateResourceReaderLC( reader, R_REPLACETAB );
            tabGroup->ReplaceTabL( reader );
            
            CleanupStack::PopAndDestroy();
            break;
            }
        case 2:
            {
            tabGroup->ReplaceTabL( ETab, KReplaceText );
            break;
            }
        case 3:
            {
            tabGroup->ReplaceTabL( ETab, KReplaceText, bitmap, mask );
            break;
            }
        case 4:
            {
            tabGroup->ReplaceTabL( ETab, bitmap, mask );
            break;
            }
        default:
            CleanupStack::Pop( mask );
            CleanupStack::Pop( bitmap );
            CleanupStack::PopAndDestroy( tabGroup );
            CleanupStack::PopAndDestroy( testControl );
            return KErrNotSupported;
        }

    CleanupStack::Pop( mask );
    CleanupStack::Pop( bitmap );
    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupReplaceTabTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupReplaceTabTextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KReplaceTabTextL, "In ReplaceTabTextL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KReplaceTabTextL );
    // Print to log file
    iLog->Log( KReplaceTabTextL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    _LIT( KReplaceText, "ReplaceTab" );
    tabGroup->ReplaceTabTextL( tabId, KReplaceText );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupDeleteTabL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupDeleteTabL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KDeleteTabL, "In DeleteTabL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KDeleteTabL );
    // Print to log file
    iLog->Log( KDeleteTabL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->DeleteTabL( tabId );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSetActiveTabByIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSetActiveTabByIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSetActiveTabById, "In SetActiveTabById" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSetActiveTabById );
    // Print to log file
    iLog->Log( KSetActiveTabById );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->SetActiveTabById( tabId );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSetActiveTabByIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSetActiveTabByIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSetActiveTabByIndex, "In SetActiveTabByIndex" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSetActiveTabByIndex );
    // Print to log file
    iLog->Log( KSetActiveTabByIndex );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    TInt tabIndex = 0;
    tabGroup->SetActiveTabByIndex( tabIndex );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupActiveTabIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupActiveTabIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KActiveTabId, "In ActiveTabId" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KActiveTabId );
    // Print to log file
    iLog->Log( KActiveTabId );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->SetActiveTabById( tabId );
    TInt tabActiveId = tabGroup->ActiveTabId();
    STIF_ASSERT_EQUALS( tabId, tabActiveId );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupActiveTabIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupActiveTabIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KActiveTabIndex, "In ActiveTabIndex" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KActiveTabIndex );
    // Print to log file
    iLog->Log( KActiveTabIndex );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    TInt tabIndex = 0;
    tabGroup->SetActiveTabByIndex( tabIndex );
    TInt tabActiveIndex = tabGroup->ActiveTabIndex();
    STIF_ASSERT_EQUALS( tabIndex, tabActiveIndex );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSetTabFixedWidthL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSetTabFixedWidthL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSetTabFixedWidthL, "In SetTabFixedWidthL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSetTabFixedWidthL );
    // Print to log file
    iLog->Log( KSetTabFixedWidthL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->SetTabFixedWidthL( KTabWidthWithOneTab );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupDimTabL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupDimTabL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KDimTab, "In DimTab" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KDimTab );
    // Print to log file
    iLog->Log( KDimTab );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->DimTab( tabId, ETrue );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupIsTabDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupIsTabDimmedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KIsTabDimmed, "In IsTabDimmed" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KIsTabDimmed );
    // Print to log file
    iLog->Log( KIsTabDimmed );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->DimTab( tabId, ETrue );
    TBool isDimmed = tabGroup->IsTabDimmed( tabId );
    STIF_ASSERT_TRUE( isDimmed );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupTabIndexFromIdL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupTabIndexFromIdL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KTabIndexFromId, "In TabIndexFromId" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KTabIndexFromId );
    // Print to log file
    iLog->Log( KTabIndexFromId );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    TInt tabIndex = tabGroup->TabIndexFromId( tabId );
    TInt tabExpectedIndex = 0;
    STIF_ASSERT_EQUALS( tabExpectedIndex, tabIndex );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupTabIdFromIndexL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupTabIdFromIndexL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KTabIdFromIndex, "In TabIdFromIndex" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KTabIdFromIndex );
    // Print to log file
    iLog->Log( KTabIdFromIndex );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    TInt tabIndex = 0;
    TInt tabActualId = tabGroup->TabIdFromIndex( tabIndex );
    STIF_ASSERT_EQUALS( tabId, tabActualId );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupTabCountL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupTabCountL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KTabCount, "In TabCount" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KTabCount );
    // Print to log file
    iLog->Log( KTabCount );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    TInt tabCounts = tabGroup->TabCount();
    TInt tabExpectedCounts = 1;
    STIF_ASSERT_EQUALS( tabExpectedCounts, tabCounts );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSetObserverL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSetObserver, "In SetObserver" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSetObserver );
    // Print to log file
    iLog->Log( KSetObserver );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    tabGroup->SetObserver( testControl );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupMinimumSizeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupMinimumSizeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KMinimumSize, "In MinimumSize" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KMinimumSize );
    // Print to log file
    iLog->Log( KMinimumSize );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TSize minSize = tabGroup->MinimumSize();
    TInt zero = 0;
    STIF_ASSERT_TRUE( ( minSize.iHeight > zero ) && ( minSize.iWidth > zero ) );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupOfferKeyEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupOfferKeyEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KOfferKeyEventL, "In OfferKeyEventL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KOfferKeyEventL );
    // Print to log file
    iLog->Log( KOfferKeyEventL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TKeyEvent keyEvent;
    keyEvent.iScanCode = EStdKeyEnter;
    TKeyResponse keyResponse = tabGroup->OfferKeyEventL( keyEvent, EEventKey );
    STIF_ASSERT_TRUE( keyResponse == EKeyWasNotConsumed );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupGetColorUseListL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupGetColorUseListL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KGetColorUseListL, "In GetColorUseListL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KGetColorUseListL );
    // Print to log file
    iLog->Log( KGetColorUseListL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    CArrayFix<TCoeColorUse>* colorUseList = new (ELeave) CArrayFixFlat<TCoeColorUse> ( KNum );
    CleanupStack::PushL( colorUseList );
    tabGroup->GetColorUseListL( *colorUseList );
    STIF_ASSERT_NOT_NULL( colorUseList );

    CleanupStack::PopAndDestroy( colorUseList );
    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupHandleResourceChangeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupHandleResourceChangeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KHandleResourceChange, "In HandleResourceChange" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KHandleResourceChange );
    // Print to log file
    iLog->Log( KHandleResourceChange );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    tabGroup->HandleResourceChange( KAknsMessageSkinChange );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupHandlePointerEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupHandlePointerEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KHandlePointerEventL, "In HandlePointerEventL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KHandlePointerEventL );
    // Print to log file
    iLog->Log( KHandlePointerEventL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TPointerEvent event;
    event.iType = TPointerEvent::EButton1Down;
    event.iModifiers = 0;
    TPoint eventPos( KPointX, KPointY );
    event.iPosition = eventPos;
    event.iParentPosition = eventPos;

    tabGroup->HandlePointerEventL( event );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupHandleControlEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KHandleControlEventL, "In HandleControlEventL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KHandleControlEventL );
    // Print to log file
    iLog->Log( KHandleControlEventL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    MCoeControlObserver::TCoeEvent eventType = MCoeControlObserver::EEventStateChanged;
    
    tabGroup->HandleControlEventL( testControl, eventType );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupPrepareContextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupPrepareContextL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KPrepareContext, "In PrepareContext" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KPrepareContext );
    // Print to log file
    iLog->Log( KPrepareContext );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    CWindowGc& gc = CCoeEnv::Static()->SystemGc();
    tabGroup->PrepareContext( gc );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupHandleNaviDecoratorEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupHandleNaviDecoratorEventL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KHandleNaviDecoratorEventL, "In HandleNaviDecoratorEventL" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KHandleNaviDecoratorEventL );
    // Print to log file
    iLog->Log( KHandleNaviDecoratorEventL );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TInt layoutType = CAknNavigationDecorator::ENaviControlLayoutNormal;
    tabGroup->HandleNaviDecoratorEventL( layoutType );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSizeChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSizeChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSizeChanged, "In SizeChanged" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSizeChanged );
    // Print to log file
    iLog->Log( KSizeChanged );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TSize size( KWidth, KHeight );
    tabGroup->SetSize( size );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupCountComponentControlsL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupCountComponentControlsL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KCountComponentControls, "In CountComponentControls" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KCountComponentControls );
    // Print to log file
    iLog->Log( KCountComponentControls );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    tabGroup->DrawNow();

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupComponentControlL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupComponentControlL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KComponentControl, "In ComponentControl" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KComponentControl );
    // Print to log file
    iLog->Log( KComponentControl );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    tabGroup->DrawNow();

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupFocusChangedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupFocusChangedL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KFocusChanged, "In FocusChanged" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KFocusChanged );
    // Print to log file
    iLog->Log( KFocusChanged );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    tabGroup->SetFocus( EFalse, EDrawNow );
    tabGroup->SetFocus( ETrue, EDrawNow );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKTabGroup::TestTabGroupSetTabMultiColorModeL
// -----------------------------------------------------------------------------
//
TInt CTestSDKTabGroup::TestTabGroupSetTabMultiColorModeL( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    _LIT( KTestSDKTabGroup, "testsdktabgrp" );
    _LIT( KSetTabMultiColorMode, "In SetTabMultiColorMode" );
    TestModuleIf().Printf( 0, KTestSDKTabGroup, KSetTabMultiColorMode );
    // Print to log file
    iLog->Log( KSetTabMultiColorMode );

    CTestTabsControl* testControl = CTestTabsControl::NewL();
    CleanupStack::PushL( testControl );
    CAknTabGroup* tabGroup = CAknTabGroup::NewL( *testControl );
    CleanupStack::PushL( tabGroup );

    TResourceReader reader;
    iEikonEnvPointer->CreateResourceReaderLC( reader, R_ADDTAB );
    TInt tabId = tabGroup->AddTabL( reader );
    CleanupStack::PopAndDestroy();

    tabGroup->SetTabMultiColorMode( tabId, ETrue );

    CleanupStack::PopAndDestroy( tabGroup );
    CleanupStack::PopAndDestroy( testControl );
    return KErrNone;

    }


//  [End of File]
