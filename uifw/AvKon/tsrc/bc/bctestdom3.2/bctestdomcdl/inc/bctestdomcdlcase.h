/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef C_CBCTESTDOMCDLCASE_H
#define C_CBCTESTDOMCDLCASE_H

#include "bctestcase.h"

class CBCTestDomCdlContainer;
class CCoeControl;

/** 
* test case for various list classes
*/
class CBCTestDomCdlCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomCdlCase* NewL( CBCTestDomCdlContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomCdlCase();
    
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
     * Test TestFunctionL
     */
    void TestFunctionL();
    
    /**
     * Test TestCdlRefsL
     */
    void TestCdlRefsL();
    
    /**
     * Test TestCdlInstanceL
     */
    void TestCdlInstanceL();

    /**
     * Test TestCdlUidsL
     */
    void TestCdlUidsL();
    
    /**
     * Test TestCdlNamesL
     */
    void TestCdlNamesL();
     
    /**
     * Test TestMCdlChangeObserverL
     */
    void TestMCdlChangeObserverL();
    
    /**
     * Test TestCdlEngineL
     */
    void TestCdlEngineL(); 
    
    /**
     * Test TestCdlExplorerUtilsL
     */
    void TestCdlExplorerUtilsL();
    
    /**
     * Test TestCCdlInstanceExplorerBaseL
     */
    void TestCCdlInstanceExplorerBaseL();
    
    /**
     * Test TestCCdlUserPackageExplorerL
     */
    void TestCCdlUserPackageExplorerL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomCdlCase( CBCTestDomCdlContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
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
    CBCTestDomCdlContainer* iContainer;
    
    };

#endif 
