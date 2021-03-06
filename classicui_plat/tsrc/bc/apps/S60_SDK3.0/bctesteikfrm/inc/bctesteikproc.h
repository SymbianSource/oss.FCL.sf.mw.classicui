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









#ifndef BCTEST_EIK_PROC_H
#define BCTEST_EIK_PROC_H

#include "bctestcase.h"

/**
* test case for various list classes
*/
class CBCTestEikProc: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestEikProc* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestEikProc();
    
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
    
    /**
     * Test functions
     */
    void TestFunctionL();

	void TestFileL();

	void TestOpsL();

	void HandleErrL(TInt err);

        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestEikProc();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    };

#endif // BCTEST_EIK_PROC_H