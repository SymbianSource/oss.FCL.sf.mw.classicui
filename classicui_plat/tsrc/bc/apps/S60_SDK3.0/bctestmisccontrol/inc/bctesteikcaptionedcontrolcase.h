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
* Description:         Declares test bc for eik captioned control testcase.
*
*/









#ifndef C_CBCTESTEIKCAPTIONEDCONTROLCASE_H
#define C_CBCTESTEIKCAPTIONEDCONTROLCASE_H

#include "bctestcase.h"

class CBCTestMiscControlContainer;
class CCoeControl;
class CBCTestSubEikCaptionedControl;
class CBCTestSubAknForm;
class CEikCaptionedControl;

/**
 * test case for various misc control classes
 */
class CBCTestEikCaptionedControlCase: public CBCTestCase
    {

public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestEikCaptionedControlCase* 
        NewL( CBCTestMiscControlContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestEikCaptionedControlCase();

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
     * TestPublicFunctionsL function
     */
    void TestPublicFunctionsL();
    
    /**
     * TestProtectedFunctionsL function
     */
    void TestProtectedFunctionsL();
    
    /**
     * TestFunctionsOfEikCapCArrayL function
     */
    void TestFunctionsOfEikCapCArrayL();    
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestEikCaptionedControlCase( CBCTestMiscControlContainer* aContainer );

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
    
   /**
     * Pointer to form.
     * own
     */
    CBCTestSubAknForm* iForm;

   /**
     * Pointer to EikCaptionedControl.
     * not own
     */    
    CEikCaptionedControl* iCapControl; 
    
   /**
     * Pointer to SubEikCaptionedControl.
     * not own
     */  
    CBCTestSubEikCaptionedControl* iSubCapControl;   
    
    };
    
#endif // C_CBCTESTEIKCAPTIONEDCONTROLCASE_H
