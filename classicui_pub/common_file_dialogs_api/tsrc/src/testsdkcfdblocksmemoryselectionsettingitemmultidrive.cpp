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
* Description:  Test CAknMemorySelectionSettingItemMultidrive.h
 *
*/


// [INCLUDE FILES]
#include <aknsettingitemlist.h> 
#include <testsdkcfd.rsg>

#include "testsdkcfd.h"
#include "testsdkcfdsettingitemmultidrive.h"
#include "testsdkcfd.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiConstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiConstructorL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiConstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    TDriveNumber selectedDrive = EDriveC;
    CTestSettingItemMultiDrive* settingitem =
        new ( ELeave ) CTestSettingItemMultiDrive( ETestSettingItem, selectedDrive );
    STIF_ASSERT_NOT_NULL( settingitem );
    CleanupStack::PushL( settingitem );
    CleanupStack::PopAndDestroy( settingitem );
    
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiDeconstructorL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiDeconstructorL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiDeconstructorL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiCompleteConstructionL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiCompleteConstructionL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiCompleteConstructionL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    
    TDriveNumber selectedDrive = EDriveC;
    CTestSettingItemMultiDrive* settingitem =
        new ( ELeave ) CTestSettingItemMultiDrive( ETestSettingItem, selectedDrive );
    CleanupStack::PushL( settingitem );
    settingitem->CompleteConstructionL();
    CAknMemorySelectionSettingItemExtension* temp= NULL;
    temp = settingitem->GetExtensionPointer();
    STIF_ASSERT_NOT_NULL( temp );
    temp = NULL;
    CleanupStack::PopAndDestroy( settingitem );
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiEditItemL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiEditItemL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiEditItemL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);
    
    iSettingItemListMulti = new ( ELeave ) CTestSettingItemListMultiDrive;
    iSettingItemListMulti->ConstructL();
    iSettingItemListMulti->EditItemL( 0, ETrue );
    delete iSettingItemListMulti;
    iSettingItemListMulti = NULL;
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiLoadL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiLoadL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiLoadL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    TDriveNumber selectedDrive = EDriveC;
    CTestSettingItemMultiDrive* settingitem =
        new ( ELeave ) CTestSettingItemMultiDrive( ETestSettingItem, selectedDrive );
    CleanupStack::PushL( settingitem );
    settingitem->CompleteConstructionL();
    settingitem->LoadL();
    CleanupStack::PopAndDestroy( settingitem );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiStoreL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiStoreL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiStoreL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    TDriveNumber selectedDrive = EDriveC;
    CTestSettingItemMultiDrive* settingitem =
        new ( ELeave ) CTestSettingItemMultiDrive( ETestSettingItem, selectedDrive );
    CleanupStack::PushL( settingitem );
    settingitem->CompleteConstructionL();
    settingitem->StoreL();
    CleanupStack::PopAndDestroy( settingitem );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestSettingItemMultiSettingTextL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestSettingItemMultiSettingTextL(CStifItemParser& /*aItem*/)
    {
    _LIT( Ktestsdkcfd, "testsdkcfd" );
    _LIT( KExample, "In TestSettingItemMultiSettingTextL" );
    TestModuleIf().Printf( 0, Ktestsdkcfd, KExample );
    iLog->Log(KExample);

    TDriveNumber selectedDrive = EDriveC;
    CTestSettingItemMultiDrive* settingitem =
        new ( ELeave ) CTestSettingItemMultiDrive( ETestSettingItem, selectedDrive );
    CleanupStack::PushL( settingitem );
    settingitem->CompleteConstructionL();
    settingitem->SettingTextL();
    CleanupStack::PopAndDestroy( settingitem );
    
    return KErrNone;
    }

// End of File
