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
* Description:         Test suite.
*
*/








#ifndef C_CBCTESTSUITE_H
#define C_CBCTESTSUITE_H

#include <e32base.h>
#include "bctestutil.h"

class CEikonEnv;
class CBCTestCase;
class CBCTestLogger;
//class TApaAppCaption

enum TBCTestEvent
    {
    ETestCaseStart,
    ETestCaseEnd,
    ETestCaseNoScript,
    ETestCaseUnbalancedIf   
    };

/**
* Test suite class.
*/
class CBCTestSuite : public CBase
    {
public: 

// constructor
    /**
     * C++ default constructor.
     * @param aLogger, pointer to log project
     */
    CBCTestSuite( CBCTestLogger* aLogger );
    
    /**
     * Destructor.
     */
	virtual ~CBCTestSuite();

// new functions
    
    /**
     * Execute a test work specified by aCmd
     * @param aCmd, a value to test command.
     */    
    void RunL(int aCmd);
    
    /**
     * Add a test case and the name of it.
     * @param aTestCase, pointer to a test case, test suite will own it.
     * @param aName, name of the test case.
     */
    void AddTestCaseL(CBCTestCase* aTestCase, const TDesC& aName );
    
    /**
     * Build a parameter for automatic test process.
     * @param aAutoTest, structure storing automatic test information, out.
     */
    void BuildScriptsL(SAutoTest* aAutoTest);
    
    /**
     * Handke test event, such as case start, case end, ...
     * @param aEvent, enum for event type
     * @param aPrarm, index to relative test case.
     */
    void HandleTestEventL( TBCTestEvent aEvent, TInt aParam );
    
protected: 

// new functions
    
    /**
     * Creates test case start and end separators to log file
     * @param aScriptIndex, script index
     * @param aStart, whether start a test case.
     */
    void WriteTestCaseLogL( TInt aScriptIndex, TBool aStart );
    
    /**
     * When start auto test, write some general information
     */
    void WriteStartLogL();
    
    /**
     * When all test completed, write summary information.
     */
    void WriteSummaryLogL();

private: // data
    
    /**
     * An array storing pointer to test case.
     */
    RArray<CBCTestCase*> iTestCases;
    
    /**
     * write log
     * Not own
     */
    CBCTestLogger* iLogger;
    
    };

#endif // C_CBCTESTSUITE_H
