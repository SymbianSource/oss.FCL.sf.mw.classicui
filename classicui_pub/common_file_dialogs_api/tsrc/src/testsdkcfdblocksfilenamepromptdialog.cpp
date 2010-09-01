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
* Description:  Test CAknFileNamePromptDialog.h
 *
*/


// [INCLUDE FILES]
#include "testsdkcfd.h"

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDNewL
// -----------------------------------------------------------------------------
//

TInt CTestSDKCFD::TestFNPDNewL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDNewL, "In TestFNPDNewL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDNewL );
    // Print to log file
    iLog->Log( KTestFNPDNewL );

    TInt err = KErrNone;
    TRAP( err, iFNPDialog = CAknFileNamePromptDialog::NewL(); );
    return err;

    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDNewLWithResL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDNewLWithResL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDNewL, "In TestFNPDNewL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDNewL );
    // Print to log file
    iLog->Log( KTestFNPDNewL );

    TInt err = KErrNone;
    TRAP( err, iFNPDialog = CAknFileNamePromptDialog::NewL(0); );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDSetPathL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDSetPathL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDSetPathL, "In TestFNPDSetPathL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDSetPathL );
    // Print to log file
    iLog->Log( KTestFNPDSetPathL );

    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;
    TRAP( err, iFNPDialog->SetPathL(folder); );
    return err;
    }
// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDExecuteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDExecuteL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDExecuteL, "In TestFNPDExecuteL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDExecuteL );
    // Print to log file
    iLog->Log( KTestFNPDExecuteL );

    TFileName filename(_L("C:\\"));

    TInt err = KErrNone;
    TRAP( err, iFNPDialog->ExecuteL(filename); );
    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDRunDlgLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDRunDlgLD( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDRunDlgLD, "In TestFNPDRunDlgLD" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDRunDlgLD );
    // Print to log file
    iLog->Log( KTestFNPDRunDlgLD );

    TFileName filename(_L("C:\\"));
    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileNamePromptDialog::RunDlgLD(filename, folder); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDRunDlgLDWithTitleLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDRunDlgLDWithTitleLD( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDRunDlgLD, "In TestFNPDRunDlgLD" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDRunDlgLD );
    // Print to log file
    iLog->Log( KTestFNPDRunDlgLD );

    TFileName filename(_L("C:\\"));
    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileNamePromptDialog::RunDlgLD(filename, folder, _L("a title")); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDRunDlgLDWithResLD
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDRunDlgLDWithResLD( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDRunDlgLD, "In TestFNPDRunDlgLD" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDRunDlgLD );
    // Print to log file
    iLog->Log( KTestFNPDRunDlgLD );

    TFileName filename(_L("C:\\"));
    TFileName folder(_L("C:\\Data\\"));
    TInt err = KErrNone;

    TRAP( err, CAknFileNamePromptDialog::RunDlgLD(filename, folder, 0); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDDeleteL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDDeleteL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDDeleteL, "In TestFNPDDeleteL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDDeleteL );
    // Print to log file
    iLog->Log( KTestFNPDDeleteL );

    delete iFNPDialog;
    iFNPDialog = NULL;

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDSetObserverL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDSetObserverL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDSetObserverL, "In TestFNPDSetObserverL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDSetObserverL );
    // Print to log file
    iLog->Log( KTestFNPDSetObserverL );

    struct MonkObserver : public MAknFileSelectionObserver
        {
        TBool OkToExitL( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/)
            {
            return ETrue;
            }
        } monkObserver;

    TInt err = KErrNone;

    TRAP( err, iFNPDialog->SetObserver(&monkObserver); );

    TFileName filename(_L("C:\\Data\\"));
    iFNPDialog->ExecuteL( filename );

    return err;
    }

TInt CTestSDKCFD::TestFNPDSetTitleL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDSetTitleL, "In TestFNPDSetTitleL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDSetTitleL );
    // Print to log file
    iLog->Log( KTestFNPDSetTitleL );

    TInt err = KErrNone;

    TRAP( err, iFNPDialog->SetTitleL(_L("FNPD Title")); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDSetLeftSoftkeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDSetLeftSoftkeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDSetLeftSoftkeyL, "In TestFNPDSetLeftSoftkeyL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDSetLeftSoftkeyL );
    // Print to log file
    iLog->Log( KTestFNPDSetLeftSoftkeyL );

    TInt err = KErrNone;

    TRAP( err, iFNPDialog->SetLeftSoftkeyL(_L("FNPD LSoftkey")); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDSetRightSoftkeyL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDSetRightSoftkeyL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDSetRightSoftkeyL, "In TestFNPDSetRightSoftkeyL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDSetRightSoftkeyL );
    // Print to log file
    iLog->Log( KTestFNPDSetRightSoftkeyL );

    TInt err = KErrNone;

    TRAP( err, iFNPDialog->SetRightSoftkeyL(_L("FNPD RSoftkey")); );

    return err;
    }

// -----------------------------------------------------------------------------
// CTestSDKCFD::TestFNPDRenameL
// -----------------------------------------------------------------------------
//
TInt CTestSDKCFD::TestFNPDRenameL( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    _LIT( KCFDTestModule, "CFDTestModule" );
    _LIT( KTestFNPDRenameL, "In TestFNPDRenameL" );
    TestModuleIf().Printf( 0, KCFDTestModule, KTestFNPDRenameL );
    // Print to log file
    iLog->Log( KTestFNPDRenameL );

    TInt err = KErrNone;
    TFileName filename;

    TRAP( err, iFNPDialog->RenameL(filename); );

    return err;
    }

//  [End of File]
