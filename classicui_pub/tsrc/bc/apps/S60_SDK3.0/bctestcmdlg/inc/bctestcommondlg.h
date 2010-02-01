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









#ifndef BCTEST_COMMON_DLG_H
#define BCTEST_COMMON_DLG_H

#include "bctestcase.h"

class MAknFileFilter;

/**
* test case for various list classes
*/
class CBCTestCommonDlg: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestCommonDlg* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestCommonDlg();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    
    /**
     * Release resource used in test
     */
    void Teardown();
    
    /**
     * Test functions
     */
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestCommonDlg();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    void RunCopyL(TInt aCmd);
    void RunSaveL(TInt aCmd);
    void RunMoveL(TInt aCmd);
    void RunSelectL(TInt aCmd);

    void BuildCopyScriptL(int i);
    void BuildSaveScriptL(int i);
    void BuildMoveScriptL(int i);
    void BuildSelectScriptL(int i);

    void SetupL();
    void AddCancelL();
    void AddOKL();
    
    void TestSelectL();
    void TestSelectL(const TDesC& aTitle);
    void TestSelectL(MAknFileFilter* aFilter);
    void TestSelectL(TInt aFileSelResID);
    void TestSelectL(const TDesC& aStartFolder, TInt aMemSelResID);
    void TestSelectL(const TDesC& aStartFolder, MAknFileFilter* aFilter);
    void TestSelectL(const TDesC& aStartFolder, TInt aMemSelResID, TInt aFileSelResID);
    void TestSelectL(const TDesC& aStartFolder, const TDesC& aTitle);

    void TestMoveL(TInt aFileSelResID);
    void TestMoveL(MAknFileFilter* aFilter);
    void TestMoveL(const TDesC& aTitle);
    void TestMoveL();

    void TestSaveL(TBool aDirFlag, TInt aMemSelResID, const TDesC& aPrompt);
    void TestSaveL(TBool aDirFlag, TInt aMemSelResID);
    void TestSaveL(TInt aFileSelResID, const TDesC& aPrompt);
    void TestSaveL(TInt aFileSelResID);
    void TestSaveL(const TDesC& aFileTitle, const TDesC& aPromptTitle);
    void TestSaveL(MAknFileFilter* aFilter);
    void TestSaveL();

    void TestCopyL(TInt aFileSelResID);
    void TestCopyL(MAknFileFilter* aFilter);
    void TestCopyL();
    };

#endif // BCTEST_COMMON_DLG_H