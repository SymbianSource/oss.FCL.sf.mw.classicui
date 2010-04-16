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
* Description:  Test Common File Dialogs
 *
*/


#ifndef C_TESTSDKCFD_H
#define C_TESTSDKCFD_H

//  INCLUDES
#include <stiflogger.h>
#include <testscripterinternal.h>
#include <stiftestmodule.h>
#include <testclassassert.h>
#include <coemain.h>
#include <coeaui.h>
#include <caknmemoryselectionsettingpage.h>
#include <caknfilenamepromptdialog.h>
#include <maknfileselectionobserver.h>
#include <caknfileselectiondialog.h> 

#include "testsdkcfdcontrol.h"
#include "testsdkcfdsettingitem.h"
#include "testsdkcfdsettingitemmultidrive.h"

// Logging path
_LIT( KtestsdkcfdLogPath, "\\logs\\testframework\\testsdkcfd\\" );
// Log file
_LIT( KtestsdkcfdLogFile, "testsdkcfd.txt" );
_LIT( KtestsdkcfdLogFileWithTitle, "testsdkcfd_[%S].txt" );

// FORWARD DECLARATIONS
class CTestSDKCFD;
class AknCommonDialogs;
class AknCommonDialogsDynMem;

/**
 *  CTestSDKCFD test class for STIF Test Framework TestScripter.
 *  @since S60 5.0
 */
NONSHARABLE_CLASS(CTestSDKCFD) : public CScriptBase
    {
public: // Constructors and destructor

    /**
     * Two-phased constructor.
     */
    static CTestSDKCFD* NewL( CTestModuleIf& aTestModuleIf );

    /**
     * Destructor.
     */
    virtual ~CTestSDKCFD();

public: // Functions from base classes

    /**
     * From CScriptBase Runs a script line.
     * @since ?Series60_version
     * @param aItem Script line containing method name and parameters
     * @return Symbian OS error code
     */
    virtual TInt RunMethodL( CStifItemParser& aItem );

private:

    /**
     * C++ default constructor.
     */
    CTestSDKCFD( CTestModuleIf& aTestModuleIf );

    /**
     * By default Symbian 2nd phase constructor is private.
     */
    void ConstructL();

    /**
     * Frees all resources allocated from test methods.
     * @since ?Series60_version
     */
    void Delete();

private: // Test CAknMemorySelectionDialog.h
    /**
     * TestMSDNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDNewL(CStifItemParser& aItem);
    /**
     * TestMSDNewWithResourceL test function for testing the NewL function with Resource
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDNewWithResourceL(CStifItemParser& aItem);
    /**
     * TestMSDNewWithMediaL test function for testing the NewL function with Medias
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDNewWithMediaL(CStifItemParser& aItem);
    /**
     * TestMSDSetTitleL test function for testing the SetSetTitleL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDSetTitleL(CStifItemParser& aItem);
    /**
     * TestMSDSetLeftSoftkeyL test function for testing the LeftSoftkeyL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDSetLeftSoftkeyL(CStifItemParser& aItem);
    /**
     * TestMSDSetRightSoftkeyL test function for testing the SetRightSoftkeyL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDSetRightSoftkeyL(CStifItemParser& aItem);
    /**
     * TestMSDSetObserverL test function for testing the SetObserverL function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDSetObserverL(CStifItemParser& aItem);
    /**
     * TestMSDExecuteL test function for testing the ExecuteL  function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDExecuteL(CStifItemParser& aItem);
    /**
     * TestMSDExecuteLDefaultFolderL test function for testing the ExecuteL  function with a default folder
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDExecuteLDefaultFolderL(CStifItemParser& aItem);
    /**
     * TestMSDRunDlgLD test function for testing the RunDlgLD  function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDRunDlgLD(CStifItemParser& aItem);
    /**
     * TestMSDRunDlgLD test function for testing the RunDlgLD  function with a title
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDRunDlgLDTitleL(CStifItemParser& aItem);
    /**
     * TestMSDRunDlgLD test function for testing the RunDlgLD  function with a resource
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDRunDlgLDResourceL(CStifItemParser& aItem);
    /**
     * TestMSDGetItemL test function for testing the GetItemL  function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDGetItemL(CStifItemParser& aItem);
    /**
     * TestMSDGetMemoriesL test function for testing the GetMemories function 
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestMSDGetMemoriesL(CStifItemParser& aItem);

private: // Test AknCommonDialogs.h

    /**
     * TestCDRunSelectDlgLD test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLD( CStifItemParser& /*aItem*/ );

    /**
     * TestCDRunSelectDlgLDFilter test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFilterL( CStifItemParser& /*aItem*/ );

    /**
     * TestCDRunSelectDlgLDTitleL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDTitleL( CStifItemParser& /*aItem*/ );

    /**
     * TestCDRunSelectDlgLDFileIdL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunMoveDlgLD test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunMoveDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunMoveDlgLDFilterL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunMoveDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunMoveDlgLDTitleL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunMoveDlgLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunMoveDlgLDFileIdL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunMoveDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLD test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLDFilterL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLDTitleL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLDFileIdL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLDIdTitleL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLDIdTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgNoDirectorySelectionLD test function for testing the RunSaveDlgNoDirectorySelectionLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgNoDirectorySelectionLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgNoDirectorySelectionLDTitleL test function for testing the RunSaveDlgNoDirectorySelectionLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgNoDirectorySelectionLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunCopyDlgLD test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunCopyDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunCopyDlgLDFilterL test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunCopyDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunCopyDlgLDFileIdL test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunCopyDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSelectDlgLDFolderL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFolderL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSelectDlgLDFolderFilterL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFolderFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSelectDlgLDFolderTitleL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFolderTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSelectDlgLDFolderFileIDL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFolderFileIDL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSelectDlgLDFolderTitleFilterL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSelectDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunSaveDlgLDFolderTitleFilterL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunSaveDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDRunFolderSelectDlgLD test function for testing the RunFolderSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDRunFolderSelectDlgLD( CStifItemParser& /*aItem*/ );
    
private: // Test AknCommonDialogsDynMem.h

    /**
     * TestCDDMRunSelectDlgLD test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLD( CStifItemParser& /*aItem*/ );

    /**
     * TestCDDMRunSelectDlgLDFilter test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFilterL( CStifItemParser& /*aItem*/ );

    /**
     * TestCDDMRunSelectDlgLDTitleL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDTitleL( CStifItemParser& /*aItem*/ );

    /**
     * TestCDDMRunSelectDlgLDFileIdL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunMoveDlgLD test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunMoveDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunMoveDlgLDFilterL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunMoveDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunMoveDlgLDTitleL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunMoveDlgLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunMoveDlgLDFileIdL test function for testing the RunMoveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunMoveDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLD test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLDFilterL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLDTitleL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLDFileIdL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLDIdTitleL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLDIdTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgNoDirectorySelectionLD test function for testing the RunSaveDlgNoDirectorySelectionLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgNoDirectorySelectionLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgNoDirectorySelectionLDTitleL test function for testing the RunSaveDlgNoDirectorySelectionLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgNoDirectorySelectionLDTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunCopyDlgLD test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunCopyDlgLD( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunCopyDlgLDFilterL test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunCopyDlgLDFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunCopyDlgLDFileIdL test function for testing the RunCopyDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunCopyDlgLDFileIdL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSelectDlgLDFolderL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFolderL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSelectDlgLDFolderFilterL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFolderFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSelectDlgLDFolderTitleL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFolderTitleL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSelectDlgLDFolderFileIDL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFolderFileIDL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSelectDlgLDFolderTitleFilterL test function for testing the RunSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSelectDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunSaveDlgLDFolderTitleFilterL test function for testing the RunSaveDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunSaveDlgLDFolderTitleFilterL( CStifItemParser& /*aItem*/ );
    
    /**
     * TestCDDMRunFolderSelectDlgLD test function for testing the RunFolderSelectDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestCDDMRunFolderSelectDlgLD( CStifItemParser& /*aItem*/ );

private: // Test CAknFileSelectionDialog.h

    /**
     * TestFSDNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDNewL( CStifItemParser& aItem );

    /**
     * TestFSDNewLWithResL test function for testing the NewL function with ResourceID
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDNewLWithResL( CStifItemParser& aItem );

    /**
     * TestFSDExecuteL test function for testing the ExecuteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDExecuteL( CStifItemParser& aItem );

    /**
     * TestFSDRunDlgLD test function for testing the RunDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDRunDlgLD( CStifItemParser& aItem );

    /**
     * TestFSDRunDlgLDWithTitleLD test function for testing the RunDlgLD function
     with the title parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDRunDlgLDWithTitleLD( CStifItemParser& aItem );

    /**
     * TestFSDRunDlgLDWithResLD test function for testing the RunDlgLD function
     with the resouceID parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDRunDlgLDWithResLD( CStifItemParser& aItem );

    /**
     * TestFSDDelete test function for testing the destruction function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDDelete( CStifItemParser& aItem );

    /**
     * TestFSDSetDefaultFolderL test function for testing the SetDefaultFolderL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetDefaultFolderL( CStifItemParser& aItem );

    /**
     * TestFSDSetTitleL test function for testing the SetTitleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetTitleL( CStifItemParser& aItem );

    /**
     * TestFSDSetLeftSoftkeyFileL test function for testing the 
     SetLeftSoftkeyFileL  function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetLeftSoftkeyFileL( CStifItemParser& aItem );

    /**
     * TestFSDSetLeftSoftkeyFolderL test function for testing the 
     SetLeftSoftkeyFolderL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetLeftSoftkeyFolderL( CStifItemParser& aItem );

    /**
     * TestFSDSetRightSoftkeyRootFolderL test function for testing the 
     SetRightSoftkeyRootFolderL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetRightSoftkeyRootFolderL( CStifItemParser& aItem );

    /**
     * TestFSDSetRightSoftkeySubfolderL test function for testing the 
     SetRightSoftkeySubfolderL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetRightSoftkeySubfolderL( CStifItemParser& aItem );

    /**
     * TestFSDSetObserverL test function for testing the SetObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDSetObserverL( CStifItemParser& aItem );

    /**
     * TestFSDAddFilterL test function for testing the AddFilterL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFSDAddFilterL( CStifItemParser& aItem );
    
private: //Test CAknFileNamePromptDialog.h
    
    /**
     * TestFNPDNewL test function for testing the NewL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDNewL( CStifItemParser& aItem );
    /**
     * TestFNPDNewLWithResL test function for testing the NewL function with ResourceID
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDNewLWithResL( CStifItemParser& aItem );
    /**
     * TestFNPDSetPathL test function for testing the SetPathL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDSetPathL( CStifItemParser& aItem );
    /**
     * TestFNPDExecuteL test function for testing the ExecuteL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDExecuteL( CStifItemParser& aItem );
    /**
     * TestFNPDRunDlgLD test function for testing the RunDlgLD function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDRunDlgLD( CStifItemParser& aItem );
    /**
     * TestFNPDRunDlgLDWithTitleLD test function for testing the RunDlgLD
       function with the title parameter
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDRunDlgLDWithTitleLD( CStifItemParser& aItem );
    /**
     * TestFNPDRunDlgLDWithResLD test function for testing the RunDlgLD 
         function with the resourceID
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDRunDlgLDWithResLD( CStifItemParser& aItem );   
    /**
     * TestFNPDDeleteL test function for testing the deconstruct function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */     
    virtual TInt TestFNPDDeleteL( CStifItemParser& aItem );
    /**
     * TestFNPDSetObserverL test function for testing the SetObserverL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDSetObserverL( CStifItemParser& aItem );
    /**
     * TestFNPDSetTitleL test function for testing the SetTitleL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDSetTitleL( CStifItemParser& aItem );
    /**
     * TestFNPDSetLeftSoftkeyL test function for testing the SetLeftSoftkeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDSetLeftSoftkeyL( CStifItemParser& aItem );
    /**
     * TestFNPDSetRightSoftkeyL test function for testing the SetRightSoftkeyL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDSetRightSoftkeyL( CStifItemParser& aItem );
    /**
     * TestFNPDRenameL test function for testing the RenameL function
     * @since S60 5.0
     * @param aItem never used
     * @return Symbian OS error code.
     */
    virtual TInt TestFNPDRenameL( CStifItemParser& aItem );

private:
    /**
     * TestFSDSetDefaultFolderL test function for testing the SetDefaultFolderL function
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageNewLNoParaL( CStifItemParser& aItem );

    /**
     * Test NewL function with parameter of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageNewL( CStifItemParser& aItem );

    /**
     * Test ExecuteL with Only Memory Type parameter of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @param aItem number for softkey
     *      1 LeftKey pressed
     *      2 RightKey pressed
     *      3 SelectKey pressed
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageExecuteLOnlyMemoryTypeL( CStifItemParser& aItem );

    /**
     * Test destructor of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageDeconstructorL( CStifItemParser& aItem );

    /**
     * Test RunDlgLD of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageRunDlgLDTwoParaL( CStifItemParser& aItem );

    /**
     * Test RunDlgLD of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageRunDlgLDThreeParaL( CStifItemParser& aItem );

    /**
     * Test RunDlgLD of CAknMemorySelectionSettingPage
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingPage.h
    virtual TInt TestSettingPageRunDlgLDFiveParaL( CStifItemParser& aItem );
    
private:
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemConstructorL( CStifItemParser& aItem );
    /**
     * Test deconstructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemDeconstructorL( CStifItemParser& aItem );
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemCompleteConstructionL( CStifItemParser& aItem );
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemEditItemL( CStifItemParser& aItem );
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemLoadL( CStifItemParser& aItem );
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemStoreL( CStifItemParser& aItem );
    /**
     * Test constructor of CAknMemorySelectionSettingItem
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItem.h
    virtual TInt TestSettingItemSettingTextL( CStifItemParser& aItem );

private:
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiConstructorL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiDeconstructorL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiCompleteConstructionL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiEditItemL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiLoadL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiStoreL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionSettingItemMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionSettingItemMultiDrive.h
    virtual TInt TestSettingItemMultiSettingTextL( CStifItemParser& aItem );

private:
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDNewL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDNewWithResourceL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDNewWithMediaL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDSetTitleL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDSetLeftSoftkeyL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDSetRightSoftkeyL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDExecuteL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDExecuteLDefaultFolderL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDRunDlgLD( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDRunDlgLDTitleL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDRunDlgLDResourceL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDGetItemL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDAddDrivePathsL( CStifItemParser& aItem );
    /**
     * Test function of CAknMemorySelectionDialogMultiDrive
     * @since S60 5.0
     * @return Symbian OS error code.
     */
    //function for function in CAknMemorySelectionDialogMultiDrive.h
    virtual TInt TestMSDMDFindIndexByDriveL( CStifItemParser& aItem );

private: // Data
    
    enum TSwitchId
    {
    ECaseOne = 1,
    ECaseTwo = 2,
    ECaseThree = 3
    };
    
    //Own : test functions in CAknFileSelectionDialog.h
    CAknFileSelectionDialog* iFDlg;

    //Own : test functions in CAknFileSelectionDialog.h
    CAknFileNamePromptDialog* iFNPDialog;
    
    // Own : test functions in CAknMemorySelectionSettingPage.h
    CAknMemorySelectionSettingPage* iSettingPage;
    
    //Own : test functions in CAknMemorySelectionSettingItem.h
    CTestSettingItemList* iSettingItemList;

    //Own : test functions in CAknMemorySelectionSettingItemMultiDrive.h
    CTestSettingItemListMultiDrive* iSettingItemListMulti;

    // ScreenSaver Property
    TInt iOldScreenSaverProperty;

    // Resource file offset
    TInt iOffset;
    };

#endif      // C_TESTSDKCFD_H
// End of File
