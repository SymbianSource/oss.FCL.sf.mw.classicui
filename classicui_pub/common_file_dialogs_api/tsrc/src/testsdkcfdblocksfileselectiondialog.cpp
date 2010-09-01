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
* Description:  Test CAknFileSelectionDialog.h
 *
*/


// [INCLUDE FILES]
#include <maknfileselectionobserver.h>
#include <maknfilefilter.h>

#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDNewL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDNewL( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDNewL, "In TestFSDNewL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDNewL );
    // Print to log file
    iLog->Log( KTestFSDNewL );

    TCommonDialogType iDlgType = ECFDDialogTypeSelect;
    TInt err = KErrNone;
    TRAP( err, iFDlg = CAknFileSelectionDialog::NewL( iDlgType ) );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDNewLWithResL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDNewLWithResL( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( FDlgNewWithResL, "In FDlgNewWithResL" );
    TestModuleIf().Printf( 0, KCFDTestModule, FDlgNewWithResL );
    // Print to log file
    iLog->Log( FDlgNewWithResL );

    TCommonDialogType iDlgType = ECFDDialogTypeSelect;
    TInt err = KErrNone;
    TRAP( err, iFDlg = CAknFileSelectionDialog::NewL( iDlgType, 0 ) );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDExecuteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDExecuteL( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KFDlgExecuteL, "In FDlgExecuteL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KFDlgExecuteL );
    // Print to log file
    iLog->Log( KFDlgExecuteL );

    _LIT( KRootPath, "C:\\TestFramework\\" );
    TFileName rootFileName( KRootPath );
    TInt err = KErrNone;
    TRAP( err, iFDlg->ExecuteL( rootFileName ) );
 
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDRunDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDRunDlgLD( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( FDlgQuickCreateL, "In FDlgQuickCreateL" );
    TestModuleIf().Printf( 0, KCFDTestModule, FDlgQuickCreateL );
    // Print to log file
    iLog->Log( FDlgQuickCreateL );

    TFileName filename(_L("C:\\data\\"));
    TFileName folder(_L("C:\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileSelectionDialog::RunDlgLD( filename, folder ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDRunDlgLDWithTitleLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDRunDlgLDWithTitleLD( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( FDlgQuickCreateWithTitleL, "In FDlgQuickCreateWithTitleL" );
    TestModuleIf().Printf( 0, KCFDTestModule, FDlgQuickCreateWithTitleL );
    // Print to log file
    iLog->Log( FDlgQuickCreateWithTitleL );

    TFileName filename;
    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileSelectionDialog::RunDlgLD( filename, folder, _L( "a title" ) ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDRunDlgLDWithResLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDRunDlgLDWithResLD( CStifItemParser& /*aItem*/)
    {

    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( FDlgQuickCreateWithResL, "In FDlgQuickCreateWithResL" );
    TestModuleIf().Printf( 0, KCFDTestModule, FDlgQuickCreateWithResL );
    // Print to log file
    iLog->Log( FDlgQuickCreateWithResL );

    TFileName filename;
    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileSelectionDialog::RunDlgLD( filename, folder, 0 ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDDelete
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDDelete( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KFDlgDeleteL, "In FDlgDeleteL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KFDlgDeleteL );
    // Print to log file
    iLog->Log( KFDlgDeleteL );

    if( iFDlg )
        {
        delete iFDlg;
        iFDlg = NULL;
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetDefaultFolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetDefaultFolderL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetDefaultFolderL, "In TestFSDSetDefaultFolderL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetDefaultFolderL );
    // Print to log file
    iLog->Log( KTestFSDSetDefaultFolderL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetDefaultFolderL(_L("Data\\") ) );

    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetTitleL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetTitleL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetTitleL, "In TestFSDSetTitleL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetTitleL );
    // Print to log file
    iLog->Log( KTestFSDSetTitleL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetTitleL( _L("a title") ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetLeftSoftkeyFileL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetLeftSoftkeyFileL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetLeftSoftkeyFileL, "In TestFSDSetLeftSoftkeyFileL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetLeftSoftkeyFileL );
    // Print to log file
    iLog->Log( KTestFSDSetLeftSoftkeyFileL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetLeftSoftkeyFileL( _L("left fkey") ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetLeftSoftkeyFolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetLeftSoftkeyFolderL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetLeftSoftkeyFolderL, "In TestFSDSetLeftSoftkeyFolderL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetLeftSoftkeyFolderL );
    // Print to log file
    iLog->Log( KTestFSDSetLeftSoftkeyFolderL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetLeftSoftkeyFolderL( _L( "left dkey" ) ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetRightSoftkeyRootFolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetRightSoftkeyRootFolderL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetRightSoftkeyRootFolderL, "In TestFSDSetRightSoftkeyRootFolderL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetRightSoftkeyRootFolderL );
    // Print to log file
    iLog->Log( KTestFSDSetRightSoftkeyRootFolderL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetRightSoftkeyRootFolderL( _L( "right root" ) ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetRightSoftkeySubfolderL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetRightSoftkeySubfolderL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetRightSoftkeySubfolderL, "In TestFSDSetRightSoftkeySubfolderL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetRightSoftkeySubfolderL );
    // Print to log file
    iLog->Log( KTestFSDSetRightSoftkeySubfolderL );

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetRightSoftkeySubfolderL( _L( "right sdir" ) ) );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDSetObserverL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDSetObserverL, "In TestFSDSetObserverL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDSetObserverL );
    // Print to log file
    iLog->Log( KTestFSDSetObserverL );

    struct MonkObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        } monkObserver;

    TInt err = KErrNone;

    TRAP( err, iFDlg->SetObserver( &monkObserver ) );

    TFileName folder( _L( "C:\\Data\\" ) );
    iFDlg->ExecuteL( folder );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFSDAddFilterL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFSDAddFilterL( CStifItemParser& /*aItem*/)
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFSDAddFilterL, "In TestFSDAddFilterL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFSDAddFilterL );
    // Print to log file
    iLog->Log( KTestFSDAddFilterL );

    struct MonkFilter : public MAknFileFilter
        {
        TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/) const
            {
            return ETrue;
            }
        };

    TInt err = KErrNone;

    TRAP( err, iFDlg->AddFilterL( new (ELeave) MonkFilter ) );//problems, should be push into stack

    return err;
    }

//  [End of File]
