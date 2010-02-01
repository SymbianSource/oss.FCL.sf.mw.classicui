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









#ifndef BCTEST_CMDLG_CASE_H
#define BCTEST_CMDLG_CASE_H

#include <caknmemoryselectiondialog.h>
#include "bctestcase.h"

class CBCTestCmDlgContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestCmDlgCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestCmDlgCase* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestCmDlgCase();
    
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
    CBCTestCmDlgCase();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    void TestSettingsL();
    void TestQuickCreateL(TInt aResID);
    void TestQuickCreateL(const TDesC& aTitle);
    void TestWithRootL();
    void TestCreateL(TInt aResID);
    void SetupL();
    void AddCancelL();
    void AddOKL();
    void TestQuickCreateL();
    void TestCreateL();

	CAknMemorySelectionDialog* iDlg;
	CAknMemorySelectionDialog::TMemory iMemory;
    };

#endif // BCTEST_CMDLG_CASE_H