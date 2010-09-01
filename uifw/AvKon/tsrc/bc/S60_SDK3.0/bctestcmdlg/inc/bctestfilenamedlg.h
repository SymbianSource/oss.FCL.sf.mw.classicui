/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  test case
*
*/


#ifndef BCTEST_FILE_NAME_DLG_H
#define BCTEST_FILE_NAME_DLG_H

#include "bctestcase.h"

class CAknFileNamePromptDialog;

/**
* test case for various list classes
*/
class CBCTestFileNameDlg: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestFileNameDlg* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestFileNameDlg();
    
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
    CBCTestFileNameDlg();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
	    void TestSettingsL();
	    void TestQuickCreateL(TInt aResID);
	    void TestQuickCreateL(const TDesC& aTitle);
	    void TestCreateL(TInt aResID);
	    void SetupL();
	    void AddCancelL();
	    void AddOKL();
	    void TestQuickCreateL();
	    void TestCreateL();
    
	CAknFileNamePromptDialog* iDlg;
    };

#endif // BCTEST_FILE_NAME_DLG_H