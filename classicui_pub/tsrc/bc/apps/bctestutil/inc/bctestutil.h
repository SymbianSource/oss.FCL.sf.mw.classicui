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
* Description:         Test utility, an interface of BCTest framework.
*
*/








#ifndef C_CBCTESTUTIL_H
#define C_CBCTESTUTIL_H

#include <e32std.h>
#include <e32base.h>
#include <f32file.h>

class CEikonEnv;
class CBCTestKeyFeeder;
class CBCTestCase;
class CBCTestSuite;
class CBCTestLogger;

// Struct to be used as parameter passing
struct SAutoTest
    {
    TInt** scripts; 
    TInt* countArray;    
    RArray<TDesC> nameArray;
    TInt scriptCount;
    };
    
// Panics
_LIT( KBCTestUtilPanicText, "BCTestUtilDLL" );

enum TBCTestUtilPanics
    {
    EBCTestUtilNoSuchVariant = 1,
    EBCTestUtilUnbalacedIfOrEndif,
    EBCTestUtilNestedIf,
    EBCTestUtilTooManyEndifs
    };

/**
 * Test utility class.
 */
class CBCTestUtil: public CBase
    {
public: 

// constructor and destructor
    
    /**
     * Symbian 2nd phase constructor.
     */
    IMPORT_C static CBCTestUtil* NewL();
    
    /**
     * Destructor.
     */
    IMPORT_C virtual ~CBCTestUtil();    

// new functions
    
    /**
     * start the runner engine, test scripts will be feed to the
     * application continuously.
     */
    IMPORT_C void RunL();

    /**
     * run according to the specified UI event, this will invoke a mapping 
     * from UI-event to test cases in test suite
     * @param aCmd, a test command.
     */
 	IMPORT_C void RunL( TInt aCmd );
 	
 	/**
     * Add test case to test suite. It will call CTestSuite::AddTestCaseL 
     * directly. A interface for user.
     * @param aTestCase, pointer to a test case.
     * @param aName, name of the test case.
     */
 	IMPORT_C void AddTestCaseL( CBCTestCase* aTestCase, const TDesC& aName );

private: // constructor
    
    /**
     * C++ default constructor.
     */
    CBCTestUtil();
    
    /**
     * Symbian 2nd constructor.
     */
    void ConstructL();

private: // data
    
    /** 
     * A parameter for automatic test 
     */   
    SAutoTest iAutoTest;

    /** 
     * Own 
     */
    CBCTestLogger* iLogger;
    
    /** 
     * Not own 
     */
    CEikonEnv* iEikEnv;
    
    /**
     * Own 
     */
    CBCTestSuite* iTestSuite;
    
    /**
     * Own 
     */
    CBCTestKeyFeeder* iKeyFeeder;
    
    };
    
#endif // C_CBCTESTUTIL_H
