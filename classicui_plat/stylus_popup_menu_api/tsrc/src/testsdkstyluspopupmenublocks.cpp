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
* Description:  test aknstyluspopupmenu.h
*
*/



// [INCLUDE FILES]
#include <e32svr.h>
#include <stifparser.h>
#include <stiftestinterface.h>
#include <aknstyluspopupmenu.h>
#include <coemain.h>
#include <coeaui.h>
#include <akndef.h>
#include <barsread.h>
#include <testsdkstyluspopupmenu.rsg>

#include "testsdkstyluspopupmenu.h"
#include "testsdkmenuobserver.h"
#include "testsdkstyluspopupmenu.hrh"

const TInt KPoint = 10;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::RunMethodL( CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "TestSPMNewTL", CTestSDKStylusPopupMenu::TestSPMNewTL ),
        ENTRY( "TestSPMNewL", CTestSDKStylusPopupMenu::TestSPMNewL ),
        ENTRY( "TestSPMNewLC", CTestSDKStylusPopupMenu::TestSPMNewLC ),
        ENTRY( "TestSPMAddMenuItemL", CTestSDKStylusPopupMenu::TestSPMAddMenuItemL ),
        ENTRY( "TestSPMRemoveMenuItemL", CTestSDKStylusPopupMenu::TestSPMRemoveMenuItemL ),
        ENTRY( "TestSPMSetItemDimmedL", CTestSDKStylusPopupMenu::TestSPMSetItemDimmedL ),
        ENTRY( "TestSPMShowMenuL", CTestSDKStylusPopupMenu::TestSPMShowMenuL ),
        ENTRY( "TestSPMSetPositionL", CTestSDKStylusPopupMenu::TestSPMSetPositionL ),
        ENTRY( "TestSPMSetPositionTL", CTestSDKStylusPopupMenu::TestSPMSetPositionTL ),
        ENTRY( "TestSPMConstructFromResourceL", CTestSDKStylusPopupMenu::TestSPMConstructFromResourceL ),
        ENTRY( "TestSPMHandleControlEventL", CTestSDKStylusPopupMenu::TestSPMHandleControlEventL ),
        };

    const TInt count = sizeof( KFunctions ) / sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMNewTL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMNewTL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewL( observer, point, NULL );
    CleanupStack::PushL( menu );
    STIF_ASSERT_NOT_NULL( menu );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMNewL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewL( observer, point );
    CleanupStack::PushL( menu );
    STIF_ASSERT_NOT_NULL( menu );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMNewLC
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMNewLC( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMAddMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMAddMenuItemL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    _LIT( KItem, "item1" );
    menu->AddMenuItemL( KItem, ETESTSDKMENUITEM1 );
    menu->RemoveMenuItem( ETESTSDKMENUITEM1 );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMRemoveMenuItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMRemoveMenuItemL( CStifItemParser& aItem )
    {
    return TestSPMAddMenuItemL( aItem );
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMSetItemDimmedL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMSetItemDimmedL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    _LIT( KItem, "item1" );
    menu->AddMenuItemL( KItem, ETESTSDKMENUITEM1 );
    menu->SetItemDimmed( ETESTSDKMENUITEM1, ETrue );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMShowMenuL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMShowMenuL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    _LIT( KItem, "item1" );
    menu->AddMenuItemL( KItem, ETESTSDKMENUITEM1 );
    menu->SetItemDimmed( ETESTSDKMENUITEM1, ETrue );
    
    menu->ShowMenu();
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMSetPositionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMSetPositionL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    TPoint pointSet( KPoint, KPoint );
    menu->SetPosition( pointSet );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMSetPositionTL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMSetPositionTL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );
    
    TPoint pointSet( KPoint, KPoint );
    menu->SetPosition( pointSet, CAknStylusPopUpMenu::EPositionTypeRightTop );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMConstructFromResourceL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMConstructFromResourceL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MENU );
    menu->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }

// -----------------------------------------------------------------------------
// CTestSDKStylusPopupMenu::TestSPMHandleControlEventL
// -----------------------------------------------------------------------------
//
TInt CTestSDKStylusPopupMenu::TestSPMHandleControlEventL( CStifItemParser& /*aItem*/ )
    {
    CTestSDKMenuObserver* observer = CTestSDKMenuObserver::NewL();
    CleanupStack::PushL( observer );
    STIF_ASSERT_NOT_NULL( observer );
    
    TPoint point;
    CAknStylusPopUpMenu* menu = CAknStylusPopUpMenu::NewLC( observer, point, NULL );
    STIF_ASSERT_NOT_NULL( menu );

    TResourceReader reader;
    CCoeEnv::Static()->CreateResourceReaderLC( reader, R_TESTSDK_MENU );
    menu->ConstructFromResourceL( reader );
    CleanupStack::PopAndDestroy();
    
    menu->HandleControlEventL( observer, MCoeControlObserver::EEventRequestExit );
    
    CleanupStack::PopAndDestroy( menu );
    CleanupStack::PopAndDestroy( observer );
    
    return KErrNone;
    
    }
//  [End of File]
