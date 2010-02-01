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
* Description:         Declares test bc for eik console control testcase.
*
*/









#ifndef C_CBCTESTEIKCONSOLECONTROLCASE_H
#define C_CBCTESTEIKCONSOLECONTROLCASE_H

#include "bctestcase.h"

class CBCTestMiscControlContainer;
class CCoeControl;

/**
 * test case for various misc control classes
 */
class CBCTestEikConsoleControlCase: public CBCTestCase
    {

public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestEikConsoleControlCase* 
        NewL( CBCTestMiscControlContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestEikConsoleControlCase();

// from CBCTestCase

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
     * TestFunctionsForEikConsoleControlL function
     */
    void TestFunctionsForEikConsoleControlL();
    
    /**
     * TestProtectedFunctionsForEikConsoleControlL function
     */
    void TestProtectedFunctionsForEikConsoleControlL();   

    /**
     * TestFunctionsForEikConsoleScreenL function
     */
    void TestFunctionsForEikConsoleScreenL();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestEikConsoleControlCase( CBCTestMiscControlContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data
    
   /**
     * Pointer to container.
     * not own
     */
    CBCTestMiscControlContainer* iContainer;
  
    };
    
#endif // C_CBCTESTEIKCONSOLECONTROLCASE_H
