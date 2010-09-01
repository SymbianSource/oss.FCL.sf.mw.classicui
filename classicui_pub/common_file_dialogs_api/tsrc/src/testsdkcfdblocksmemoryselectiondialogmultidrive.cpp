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
* Description:  Test CAknMemorySelectionDialogMultiDrive.h
 *
*/


// [INCLUDE FILES]
#include <caknmemoryselectiondialogmultidrive.h> 
#include <cakncommondialogsbase.h>

#include "testsdkcfd.h"


const TInt KRootPathLength = 16;
const TInt KDefaultFolderLength = 512;
const TInt KItemDiscriptor = 512;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDNewL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDNewL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall, "Test MemorySelectionDialogMultiDrive::TestMSDMDNewL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDNewWithResourceL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDNewWithResourceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall, "Test MemorySelectionDialogMultiDrive::TestMSDMDNewWithResourceL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, 0, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDNewWithMediaL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDNewWithMediaL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall, "Test MemorySelectionDialogMultiDrive::TestMSDMDNewWithMediaL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );
    TInt media = 1;
    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, 0, ETrue,
        media );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDSetTitleL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDSetTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall, "Test MemorySelectionDialogMultiDrive::SetTitleL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KDialogTitle, "Hello Dialog!" );
    TDesC dialogTitle(KDialogTitle);
    memorySelectionDialog->SetTitleL( dialogTitle );

    CleanupStack::PopAndDestroy( memorySelectionDialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDSetLeftSoftkeyL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDSetLeftSoftkeyL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::SetLeftSoftkeyL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KLeftKey, "Enter" );
    TDesC dialogLeftKey( KLeftKey );

    memorySelectionDialog->SetLeftSoftkeyL( dialogLeftKey );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDSetRightSoftkeyL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDSetRightSoftkeyL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::SetRightSoftkeyL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KRightKey, "Enter" );
    TDesC dialogRightKey( KRightKey );

    memorySelectionDialog->SetRightSoftkeyL( dialogRightKey );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDExecuteL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDExecuteL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::ExecuteL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KCallExecuteL1True, "MemorySelectionDialogMultiDrive::ExecuteL Return ETrue" );
    _LIT( KCallExecuteL1False, "MemorySelectionDialogMultiDrive::ExecuteL Return EFalse" );

    TDriveNumber selectedDrive = EDriveC;
    CAknCommonDialogsBase::TReturnKey returnKey;

    returnKey = memorySelectionDialog->ExecuteL( selectedDrive );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    if ( returnKey )
        {
        iLog->Log( KCallExecuteL1True );
        }
    else
        {
        iLog->Log( KCallExecuteL1False );
        }

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDExecuteLDefaultFolderL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDExecuteLDefaultFolderL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDExecuteLDefaultFolderL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    _LIT( KCallExecuteL1True, "MemorySelectionDialogMultiDrive::ExecuteL Return ETrue" );
    _LIT( KCallExecuteL1False, "MemorySelectionDialogMultiDrive::ExecuteL Return EFalse" );
    
    TDriveNumber selectedDrive = EDriveC;
    _LIT( KRootPath, "C:\\" );
    _LIT( KDefaultFolder, " " );
    TBuf<KRootPathLength> rootBuf( KRootPath );
    TBuf<KDefaultFolderLength> defaultBuf( KDefaultFolder );

    CAknCommonDialogsBase::TReturnKey returnKey;
    returnKey = memorySelectionDialog->ExecuteL( selectedDrive, &rootBuf,
        &defaultBuf );
    
    if ( returnKey )
        {
        iLog->Log( KCallExecuteL1True );
        }
    else
        {
        iLog->Log( KCallExecuteL1False );
        }
    
    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }
// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDRunDlgLD
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDRunDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::NewL1" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );
    
    TDriveNumber selectedDrive = EDriveC;
    CAknMemorySelectionDialogMultiDrive::RunDlgLD( selectedDrive );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDRunDlgLDTitleL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDRunDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDRunDlgLDTitleL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    _LIT( KDialogTitle, "Hello Dialog!" );
    TBuf<KMaxFileName> dialogTitle( KDialogTitle );
    
    TDriveNumber selectedDrive = EDriveC;

    CAknMemorySelectionDialogMultiDrive::RunDlgLD( selectedDrive, dialogTitle );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDRunDlgLDResourceL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDRunDlgLDResourceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDRunDlgLDResourceL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    TDriveNumber selectedDrive = EDriveC;

    _LIT( KRootPath, "C:\\" );
    _LIT( KDefaultFolder, " " );

    TBuf<KRootPathLength> rootBuf( KRootPath );
    TBuf<KDefaultFolderLength> defaultBuf( KDefaultFolder );
    CAknMemorySelectionDialogMultiDrive::RunDlgLD( selectedDrive, 0, &rootBuf,
        &defaultBuf );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDGetItemL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDGetItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDGetItemL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    TInt index = 0;
    TBuf<KItemDiscriptor> itemdes;
    memorySelectionDialog->GetItem( index, itemdes );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDAddDrivePathsL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDAddDrivePathsL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDAddDrivePathsL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KRootPath, "C:\\Data" );
    _LIT( KDefaultFolder, "Others" );
    TBuf<KRootPathLength> rootBuf(KRootPath);
    TBuf<KDefaultFolderLength> defaultBuf(KDefaultFolder);
    memorySelectionDialog->AddDrivePathsL( rootBuf, defaultBuf );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDMDFindIndexByDriveL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDMDFindIndexByDriveL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialogMultiDrive>" );
    _LIT( KCall1, "Test MemorySelectionDialogMultiDrive::TestMSDMDFindIndexByDriveL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialogMultiDrive* memorySelectionDialog =
        CAknMemorySelectionDialogMultiDrive::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    TDriveNumber drive = EDriveC;
    memorySelectionDialog->FindIndexByDrive( drive );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

//  [End of File]
