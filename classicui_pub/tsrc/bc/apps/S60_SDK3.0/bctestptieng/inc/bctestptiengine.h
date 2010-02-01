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









#ifndef BCTEST_PTIENGINE_H
#define BCTEST_PTIENGINE_H

#include "bctestcase.h"

class CPtiEngine;

/**
* test case for various list classes
*/
class CBCTestPtiEngine: public CBCTestCase
    {
public: // constructor and destructor

    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPtiEngine* NewL();

    /**
    * Destructor
    */
    virtual ~CBCTestPtiEngine();

public: // from CBCTestCase

    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

//new funcs

    /**
	* @return the 1st core UID in core list
	*/

protected: // new functions

    /**
    * Build autotest script
    */
    void BuildScriptL();

    /**
     * Test functions
     */
    void TestFunctionL();

private: // constructor
	    void TestJapaneseInputL();
		void TestOtherL();
	    void TestSpellL();
	    void TestChineseInputL();
	    void TestReorderingL();
	    void TestNavigationL();
	    void TestLastKeyL();
	    void TestDictL();
	    void TestInputModeL();
	    void TestPredictL();
	    void TestMultitappingL();
	    void TestInputL();
	    void TestInfoL();
	    void TestCoreL();
	    void TestLanguageL();
	CPtiEngine* TestCreateL();

	/**
     * C++ default constructor
     */
    CBCTestPtiEngine();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

	void SetupL();
	void TeardownL();

//data
	CPtiEngine* iEngine;
    };

#endif // BCTEST_PTIENGINE_H