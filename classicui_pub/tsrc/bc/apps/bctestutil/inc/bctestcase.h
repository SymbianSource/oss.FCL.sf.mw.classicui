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
* Description:         Test case class, user will create own test case class by 
*                deriving from the class.
*
*/









#ifndef C_CBCTESTCASE_H
#define C_CBCTESTCASE_H

#include "bctestassert.h"
#include "AutotestCommands.h"

const TInt KNameLength = 50;

/**
 *  Test case class, user will derive own test case from the class
 */
class CBCTestCase : public CBCTestAssert
    {
public:
    
// declaration

    /**
     * Test case type 
     * EEndCase means the case is an instance of CBCTestEndCase
     */
    enum TTestCaseType
        {
        ENormalCase,
        EEndCase
        };

// constructor
    
    /**
     * C++ default constructor
     */ 
    IMPORT_C CBCTestCase();
    
    /**
     * Destructor
     */
    IMPORT_C virtual ~CBCTestCase();
    
// exported new functions
    
    /**
     * Add script commands to the test case.
     * @param aCmd, script command
     */
    IMPORT_C void AddTestL( TInt aCmd, ... );
    
    /**
     * Add a series of commands defined in a TInt array to the test case
     * @param aCmdArray, an array stored script commands
     * @param aCmdCount, the count of script commands stored in aCmdArray.
     */
    IMPORT_C void AddTestScriptL( const TInt* aCmdArray, TInt aCmdCount );    
    
// exported virtual functions
    
    /**
     * Do actual test work specified by parameter, here the functions is not
     * implemented. User have to override it.
     * @param, a value to a test command.
     */
    IMPORT_C virtual void RunL( TInt );
    
// new functions

    /**
     * Return iTestScripts.
     */
    TInt* TestScripts();
    
    /**
     * Return the count of script commands stored in the test case.
     */
    TInt ScriptCount();
    
    /**
     * Set name of test case 
     */
    void SetName( const TDesC& aName );
    
    /**
     * Get name of test case
     */
    TDesC& Name();
    
    /**
     * Set type of test case.
     */
    void SetType( TInt aType );
    
    /**
     * Get type of test case.
     */
    TInt Type();

protected: 

// new functions
    
    /**
     * Add a TInt to iTestScripts, and dynamically expand the array 
     * when necessary.
     * @param aCmd, a script command.
     */
    void AppendL( TInt aCmd );
    
private: // data
    
    /**
     * Array to store script commands. Use TInt* for combining several 
     * TInt array together easily. And copying memory is not needed by 
     * the way.
     * Own.
     */
    TInt* iTestScripts;
    
    /**
     * Record the count of script commands stored in iTestScripts.
     */
    TInt  iScriptCount;
    
    /**
     * Record the maximum size of iTestScripts.
     */
    TInt  iMaxSize;
    
    /**
     * The name of test case.
     */
    TBuf<KNameLength> iName;
    
    /**
     * The type of test case, using the value ETestCaseType.
     */
    TInt iType;
    
    };

#endif // C_CBCTESTCASE_H
