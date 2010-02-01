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
* Description:  Test AknCommonDialogs.h
 *
*/


// [INCLUDE FILES]
#include <caknmemoryselectiondialog.h> 
#include <cakncommondialogsbase.h>

#include "testsdkcfd.h"
#include "testsdkcfdmaknmemoryselectionobserver.h"


const TInt KRootPathLength = 16;
const TInt KDefaultFolderLength = 512;
const TInt KItemDiscriptor = 512;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDNewL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDNewL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall, "Test MemorySelectionDialog::TestMSDNewL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDNewWithResourceL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDNewWithResourceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall, "Test MemorySelectionDialog::TestMSDNewWithResourceL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, 0, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDNewWithMediaL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDNewWithMediaL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall, "Test MemorySelectionDialog::TestMSDNewWithMediaL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );
    TInt media = 1;
    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, 0, ETrue,
        media );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDSetTitleL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDSetTitleL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall, "Test MemorySelectionDialog::SetTitleL" );

    iLog->Log( KTitle );
    iLog->Log( KCall );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KDialogTitle, "Hello Dialog!" );
    TDesC dialogTitle(KDialogTitle);
    memorySelectionDialog->SetTitleL( dialogTitle );

    CleanupStack::PopAndDestroy( memorySelectionDialog );
    
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDSetLeftSoftkeyL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDSetLeftSoftkeyL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::SetLeftSoftkeyL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KLeftKey, "Enter" );
    TDesC dialogLeftKey( KLeftKey );

    memorySelectionDialog->SetLeftSoftkeyL( dialogLeftKey );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDSetRightSoftkeyL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDSetRightSoftkeyL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::SetRightSoftkeyL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KRightKey, "Enter" );
    TDesC dialogRightKey( KRightKey );

    memorySelectionDialog->SetRightSoftkeyL( dialogRightKey );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDSetObserverL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDSetObserverL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::SetObserver" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CTestSDKCFDMAknMemorySelectionOberver* msobserver=
        CTestSDKCFDMAknMemorySelectionOberver::NewL( );
    CleanupStack::PushL( msobserver );
    STIF_ASSERT_NOT_NULL( msobserver );

    memorySelectionDialog->SetObserver( msobserver );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDExecuteL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDExecuteL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::ExecuteL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KCallExecuteL1True, "MemorySelectionDialog::ExecuteL Return ETrue" );
    _LIT( KCallExecuteL1False, "MemorySelectionDialog::ExecuteL Return EFalse" );

    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;
    CAknCommonDialogsBase::TReturnKey returnKey;

    returnKey = memorySelectionDialog->ExecuteL( memType );

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
// CTestSDKCFD::TestMSDExecuteLDefaultFolderL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDExecuteLDefaultFolderL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::TestMSDExecuteLDefaultFolderL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );
    
    _LIT( KCallExecuteL1True, "MemorySelectionDialog::ExecuteL Return ETrue" );
    _LIT( KCallExecuteL1False, "MemorySelectionDialog::ExecuteL Return EFalse" );
    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;
    _LIT( KRootPath, "C:\\" );
    _LIT( KDefaultFolder, " " );
    TBuf<KRootPathLength> rootBuf( KRootPath );
    TBuf<KDefaultFolderLength> defaultBuf( KDefaultFolder );

    CAknCommonDialogsBase::TReturnKey returnKey;
    returnKey = memorySelectionDialog->ExecuteL( memType, &rootBuf,
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
// CTestSDKCFD::TestMSDRunDlgLD
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDRunDlgLD( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::NewL1" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );
    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CTestSDKCFDMAknMemorySelectionOberver* msobserver=
        CTestSDKCFDMAknMemorySelectionOberver::NewL( );
    CleanupStack::PushL( msobserver );
    STIF_ASSERT_NOT_NULL( msobserver );
    
    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;
    CAknMemorySelectionDialog::RunDlgLD( memType, msobserver );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestNewMemorySelectionDialog
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDRunDlgLDTitleL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::TestMSDRunDlgLDTitleL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    _LIT( KDialogTitle, "Hello Dialog!" );
    TBuf<KMaxFileName> dialogTitle( KDialogTitle );

    CTestSDKCFDMAknMemorySelectionOberver* msobserver =
        CTestSDKCFDMAknMemorySelectionOberver::NewL( );
    CleanupStack::PushL( msobserver );
    STIF_ASSERT_NOT_NULL( msobserver );
    
    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;

    CAknMemorySelectionDialog::RunDlgLD( memType, dialogTitle, msobserver );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestNewMemorySelectionDialog
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDRunDlgLDResourceL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::TestMSDRunDlgLDResourceL" );
    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CTestSDKCFDMAknMemorySelectionOberver* msobserver=
        CTestSDKCFDMAknMemorySelectionOberver::NewL( );
    CleanupStack::PushL( msobserver );
    STIF_ASSERT_NOT_NULL( msobserver );

    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;

    _LIT( KRootPath, "C:\\" );
    _LIT( KDefaultFolder, " " );

    TBuf<KRootPathLength> rootBuf( KRootPath );
    TBuf<KDefaultFolderLength> defaultBuf( KDefaultFolder );
    CAknMemorySelectionDialog::RunDlgLD( memType, 0, &rootBuf,
        &defaultBuf, msobserver );

    CleanupStack::PopAndDestroy( 2 );

    return KErrNone;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDGetItemL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDGetItemL( CStifItemParser& /*aItem*/ )
    {
    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::TestMSDGetItemL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    TInt index = 0;
    TBuf<KItemDiscriptor> itemdes;
    memorySelectionDialog->GetItem( index, itemdes );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestMSDGetMemoriesL
// -----------------------------------------------------------------------------
TInt CTestSDKCFD::TestMSDGetMemoriesL( CStifItemParser& /*aItem*/ )
    {

    _LIT( KTitle, "Class <MemorySelectionDialog>" );
    _LIT( KCall1, "Test MemorySelectionDialog::TestMSDGetMemoriesL" );

    iLog->Log( KTitle );
    iLog->Log( KCall1 );

    CAknMemorySelectionDialog* memorySelectionDialog =
        CAknMemorySelectionDialog::NewL( ECFDDialogTypeNormal, ETrue );
    CleanupStack::PushL( memorySelectionDialog );
    STIF_ASSERT_NOT_NULL( memorySelectionDialog );

    CAknMemorySelectionDialog::TMemory memType =
        CAknMemorySelectionDialog::EPhoneMemory;

    _LIT( KRootPath, "C:\\" );
    _LIT( KDefaultFolder, "" );
    TBuf<KRootPathLength> rootBuf(KRootPath);
    TBuf<KDefaultFolderLength> defaultBuf(KDefaultFolder);
    memorySelectionDialog->GetMemories( memType, &rootBuf, &defaultBuf );

    CleanupStack::PopAndDestroy( memorySelectionDialog );

    return KErrNone;
    }

//  [End of File]
