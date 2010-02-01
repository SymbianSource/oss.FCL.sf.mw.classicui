/*
* Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         test case
*
*/









#include <w32std.h>
#include <coecntrl.h>
#include <akncommondialogs.h>
//#include <AknCommonDialogsDynMem.h>

#include <MAknFileSelectionObserver.h>
#include <MaknFileFilter.h>
#include <bctestcmdlg.rsg>

#include "BCTestCommonDlg.h"
#include "BCTestCmDlg.hrh"
#include "streamlogger.h"

//helper class

struct MonkFilter: public MAknFileFilter{
    TBool Accept( const TDesC& /*aDriveAndPath*/, const TEntry& /*aEntry*/ ) const{
        return ETrue;
    }
};

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Symbian 2nd static Constructor
// ---------------------------------------------------------------------------
//
CBCTestCommonDlg* CBCTestCommonDlg::NewL()
    {
    CBCTestCommonDlg* self = new( ELeave ) CBCTestCommonDlg();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------------------------
//
CBCTestCommonDlg::CBCTestCommonDlg()
    {    
    }
    
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CBCTestCommonDlg::~CBCTestCommonDlg()
    {  
    }
    
// ---------------------------------------------------------------------------
// Symbian 2nd Constructor
// ---------------------------------------------------------------------------
//
void CBCTestCommonDlg::ConstructL()
    {    
    BuildScriptL();    
    }

void CBCTestCommonDlg::SetupL()
    {
    }

// ---------------------------------------------------------------------------
// CBCTestCommonDlg::BuildScriptL
// ---------------------------------------------------------------------------
//
void CBCTestCommonDlg::BuildScriptL()
    { 
    AddTestL( DELAY(1), TEND);

    // Add script as your need.   
    for(int i=0; i<EBCTestCmdCommonDlgEnd - EBCTestCmdCommonDlgBegin -1; ++i)
        {
        AddTestL( LeftCBA, REP(Down, 4), Right, TEND ); //navigate to common dialog menu

        for(int j=0; j<i; ++j)
            AddTestL( Down, TEND);  // navigate to each sub menu item
        AddTestL( LeftCBA, TEND );  // trigger the menu item.

        BuildSelectScriptL(i);
        BuildMoveScriptL(i);
        BuildSaveScriptL(i);
        BuildCopyScriptL(i);
        }
    }

void CBCTestCommonDlg::BuildSelectScriptL(int i)
    {
    AddCancelL();       //OK may enter a folder and ask user to select more.
    
    // some sepcial cases
    if( i >= (EBCTestCmdCommonDlgSelect5 - EBCTestCmdCommonDlgBegin -1) &&
        i <= (EBCTestCmdCommonDlgSelect8 - EBCTestCmdCommonDlgBegin -1))
        AddCancelL();   //first back, 2nd cancel.
    
    if( i == (EBCTestCmdCommonDlgSelect8 - EBCTestCmdCommonDlgBegin -1))
        AddCancelL();   //first back, then back again, finally cancel.
    }

void CBCTestCommonDlg::BuildMoveScriptL( int )
    {
    }

void CBCTestCommonDlg::BuildSaveScriptL( int )
    {
    }

void CBCTestCommonDlg::BuildCopyScriptL( int )
    {
    }
    
void CBCTestCommonDlg::AddOKL()
    {
    // add dlg response sciprts
    for(int i=0; i<1; ++i)
        AddTestL( WAIT(5), KeyOK, TEND);
    }

void CBCTestCommonDlg::AddCancelL()
    {
    // add dlg response sciprts
    for(int i=0; i<1; ++i)
        AddTestL( WAIT(5), RightCBA, TEND);
    }

// ---------------------------------------------------------------------------
// CBCTestCommonDlg::RunL
// ---------------------------------------------------------------------------
//
void CBCTestCommonDlg::RunL( TInt aCmd )
    {
    SetupL();
    RunSelectL(aCmd);
    RunMoveL(aCmd);
    RunSaveL(aCmd);
    RunCopyL(aCmd);
    Teardown();
    }

void CBCTestCommonDlg::RunSelectL(TInt aCmd)
    {
    switch(aCmd)
        {
        case EBCTestCmdCommonDlgSelect1:
            TestSelectL();
            break;
        case EBCTestCmdCommonDlgSelect2:
            TestSelectL(_L("a title"));
            break;
        case EBCTestCmdCommonDlgSelect3:
            {
            MonkFilter filter;
            TestSelectL(&filter);
            break;
            }
        case EBCTestCmdCommonDlgSelect4:
            TestSelectL(R_BCTEST_FILE_SELECTION_ALL);
            break;
        case EBCTestCmdCommonDlgSelect5:
            TestSelectL(_L("C:\\Data"), R_BCTEST_MEMORY_SELECTION_LOCATIONS);
            break;
        case EBCTestCmdCommonDlgSelect6:
            {
            MonkFilter filter;
            TestSelectL(_L("C:\\Data"), &filter);
            break;
            }
        case EBCTestCmdCommonDlgSelect7:
            TestSelectL(_L("C:\\Data"), _L("a title"));
            break;
        case EBCTestCmdCommonDlgSelect8:
            TestSelectL(_L("C:\\Data"), R_BCTEST_MEMORY_SELECTION_LOCATIONS, R_BCTEST_FILE_SELECTION_ALL);
            break;
        default:
            break;
        }
    }

void CBCTestCommonDlg::RunMoveL(TInt aCmd)
    {
    switch(aCmd)
        {
        case EBCTestCmdCommonDlgMove1:
            TestMoveL();
            break;
        case EBCTestCmdCommonDlgMove2:
            TestMoveL(_L("a title"));
            break;
        case EBCTestCmdCommonDlgMove3:
            {
            MonkFilter filter;
            TestMoveL(&filter);
            break;
            }
        case EBCTestCmdCommonDlgMove4:
            TestMoveL(R_BCTEST_FILE_SELECTION_ALL);
            break;
        default:
            break;
        }
    }

void CBCTestCommonDlg::RunSaveL(TInt aCmd)
    {
    switch(aCmd)
        {
        case EBCTestCmdCommonDlgSave1:
            TestSaveL();
            break;
        case EBCTestCmdCommonDlgSave2:
            TestSaveL(_L("a sel title"), _L("a name prompt"));
            break;
        case EBCTestCmdCommonDlgSave3:
            {
            MonkFilter filter;
            TestSaveL(&filter);
            break;
            }
        case EBCTestCmdCommonDlgSave4:
            TestSaveL(R_BCTEST_FILE_SELECTION_ALL);
            break;
        case EBCTestCmdCommonDlgSave5:
            TestSaveL(R_BCTEST_FILE_SELECTION_ALL, _L("a prompt"));
            break;
        case EBCTestCmdCommonDlgSave6:
            TestSaveL(EFalse, R_BCTEST_MEMORY_SELECTION_LOCATIONS);
            break;
        case EBCTestCmdCommonDlgSave7:
            TestSaveL(EFalse, R_BCTEST_MEMORY_SELECTION_LOCATIONS, _L("a prompt"));
            break;
        default:
            break;
        }
    }

void CBCTestCommonDlg::RunCopyL(TInt aCmd)
    {
    switch(aCmd)
        {
        case EBCTestCmdCommonDlgCopy1:
            TestCopyL();
            break;
        case EBCTestCmdCommonDlgCopy2:
            TestCopyL(R_BCTEST_FILE_SELECTION_ALL);
            break;
        case EBCTestCmdCommonDlgCopy3:
            {
            MonkFilter filter;
            TestCopyL(&filter);
            break;
            }
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBCTestCommonDlg::ReleaseCaseL
// ---------------------------------------------------------------------------
//   
void CBCTestCommonDlg::Teardown()
    {
    }

void CBCTestCommonDlg::TestSelectL()
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS );
    AssertTrueL(ETrue, _L("Select with Res ID"));
    }

void CBCTestCommonDlg::TestSelectL(const TDesC &aTitle)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aTitle);
    AssertTrueL(ETrue, _L("Select with Res ID and Title"));
    }

void CBCTestCommonDlg::TestSelectL(MAknFileFilter* aFilter)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFilter);
    AssertTrueL(ETrue, _L("Select with Res ID and Filter"));
    }

void CBCTestCommonDlg::TestSelectL(TInt aFileSelResID)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFileSelResID);
    AssertTrueL(ETrue, _L("Select with Res ID and File Selection Res ID"));
    }

void CBCTestCommonDlg::TestSelectL(const TDesC& aStartFolder, TInt aMemSelResID)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        aStartFolder,
        aMemSelResID);
    AssertTrueL(ETrue, _L("Select with start folder"));
    }


void CBCTestCommonDlg::TestSelectL(const TDesC& aStartFolder, MAknFileFilter* aFilter)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        aStartFolder,
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFilter);
    AssertTrueL(ETrue, _L("Select with start folder and filter"));
    }

void CBCTestCommonDlg::TestSelectL(const TDesC &aStartFolder, const TDesC &aTitle)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        aStartFolder, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS, 
        aTitle);
    AssertTrueL(ETrue, _L("Select with start folder and title"));
    }

void CBCTestCommonDlg::TestSelectL(const TDesC &aStartFolder, TInt aMemSelResID, TInt aFileSelResID)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunSelectDlgLD( emptyFileName, 
        aStartFolder, 
        aMemSelResID, 
        aFileSelResID);
    AssertTrueL(ETrue, _L("Select with start folder and file selection res ID"));
    }

void CBCTestCommonDlg::TestMoveL()
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunMoveDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS );
    AssertTrueL(ETrue, _L("Move"));
    }

void CBCTestCommonDlg::TestMoveL(const TDesC &aTitle)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunMoveDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aTitle);
    AssertTrueL(ETrue, _L("Move with title"));
    }

void CBCTestCommonDlg::TestMoveL(MAknFileFilter *aFilter)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunMoveDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFilter);
    AssertTrueL(ETrue, _L("Move with filter"));
    }

void CBCTestCommonDlg::TestMoveL(TInt aFileSelResID)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunMoveDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFileSelResID);
    AssertTrueL(ETrue, _L("Move with file selection Res ID"));
    }

void CBCTestCommonDlg::TestSaveL()
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS );
    AssertTrueL(ETrue, _L("Save"));
    }

void CBCTestCommonDlg::TestSaveL(MAknFileFilter *aFilter)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFilter);
    AssertTrueL(ETrue, _L("Save with filter"));
    }

void CBCTestCommonDlg::TestSaveL(const TDesC &aFileTitle, const TDesC &aPromptTitle)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFileTitle,
        aPromptTitle);
    AssertTrueL(ETrue, _L("Save with title"));
    }

void CBCTestCommonDlg::TestSaveL(TInt aFileSelResID)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFileSelResID);
    AssertTrueL(ETrue, _L("Save with file selection res ID"));
    }

void CBCTestCommonDlg::TestSaveL(TInt aFileSelResID, const TDesC &aPrompt)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgLD( defaultFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS,
        aFileSelResID,
        aPrompt);
    AssertTrueL(ETrue, _L("Save with file selection res ID and Prompt"));
    }

void CBCTestCommonDlg::TestSaveL(TBool /*aDirFlag*/, TInt aMemSelResID)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD( defaultFileName, 
        aMemSelResID);
    AssertTrueL(ETrue, _L("Save without dir selection"));
    }

void CBCTestCommonDlg::TestSaveL(TBool /*aDirFlag*/, TInt aMemSelResID, const TDesC& aPrompt)
    {
    TFileName defaultFileName(_L("foo.jpg"));
    TInt returnValue = AknCommonDialogs::RunSaveDlgNoDirectorySelectionLD( defaultFileName, 
        aMemSelResID, aPrompt);
    AssertTrueL(ETrue, _L("Save without dir selection but with a prompt"));
    }

void CBCTestCommonDlg::TestCopyL()
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunCopyDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS);
    AssertTrueL(ETrue, _L("Copy"));
    }

void CBCTestCommonDlg::TestCopyL(MAknFileFilter *aFilter)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunCopyDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS, aFilter);
    AssertTrueL(ETrue, _L("Copy with filter"));
    }

void CBCTestCommonDlg::TestCopyL(TInt aFileSelResID)
    {
    TFileName emptyFileName;
    TInt returnValue = AknCommonDialogs::RunCopyDlgLD( emptyFileName, 
        R_BCTEST_MEMORY_SELECTION_LOCATIONS, aFileSelResID);
    AssertTrueL(ETrue, _L("Copy with file selection res ID"));
    }

// EOF
