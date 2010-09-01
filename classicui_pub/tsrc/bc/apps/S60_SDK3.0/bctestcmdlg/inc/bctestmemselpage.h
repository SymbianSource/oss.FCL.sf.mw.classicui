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









#ifndef BCTEST_MEM_SEL_SETTING_PAGE_H
#define BCTEST_MEM_SEL_SETTING_PAGE_H

#include <caknmemoryselectionsettingpage.h>
#include "bctestcase.h"

class CBCTestCmDlgContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestMemSelSettingPage: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMemSelSettingPage* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestMemSelSettingPage();
    
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
    CBCTestMemSelSettingPage();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
	    void TestQuickCreateL(TInt aResID);
	    void TestQuickCreateL(const TDesC& aTitle);
	    void TestCreateL(TInt aResID);
	    void SetupL();
	    void AddCancelL();
	    void AddOKL();
	    void TestQuickCreateL();
	    void TestCreateL();
    
	CAknMemorySelectionSettingPage* iDlg;
	CAknMemorySelectionDialog::TMemory iMemory;
    };

#endif // BCTEST_MEM_SEL_SETTING_PAGE_H