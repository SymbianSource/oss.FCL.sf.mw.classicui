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









#ifndef BCTEST_PTIENG_DICT_H
#define BCTEST_PTIENG_DICT_H

#include "bctestcase.h"

class CBCTestPtiEngContainer;
class CCoeControl;
class CPtiUserDictionary;

/**
* test case for various list classes
*/
class CBCTestUserDict: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestUserDict* NewL( CBCTestPtiEngContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestUserDict();
    
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
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void TestFunctionL();

private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestUserDict( CBCTestPtiEngContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

	/**
	* added detailed tests
	*/
	void TestCreateL();

	void TestSetDataL();

	void TestSaveDataL();

	void TestReloadL();

	void Reset();
    
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPtiEngContainer* iContainer;

	/**
	* pointer to a user dict, own
	*/
	CPtiUserDictionary* iDict;
    
    };

#endif // BCTEST_PTIENG_DICT_H
