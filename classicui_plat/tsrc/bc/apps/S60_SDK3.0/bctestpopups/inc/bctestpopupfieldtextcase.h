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
* Description:         Declares test bc for popup field text testcase.
*
*/









#ifndef C_CBCTESTPOPUPFIELDTEXTCASE_H
#define C_CBCTESTPOPUPFIELDTEXTCASE_H

#include "bctestcase.h"

class CBCTestPopupsContainer;
class CCoeControl;
class CAknForm;

/**
 * test case for various popups classes
 */
class CBCTestPopupFieldTextCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestPopupFieldTextCase* 
        NewL( CBCTestPopupsContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestPopupFieldTextCase();

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
     * TestPopupFieldTextL  function
     */
    void TestPopupFieldTextL();
    
    /**
     * TestPopupFieldL  function
     */
    void TestPopupFieldL(); 
    
     /**
     * TestProtectedFunctionsL  function
     */
    void TestProtectedFunctionsL();  
        
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestPopupFieldTextCase( CBCTestPopupsContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPopupsContainer* iContainer;

    /**
     * Pointer to BaseDialog.
     * own
     */    
    CAknForm* iBaseDialog;
    };

#endif // C_CBCTESTPOPUPFIELDTEXTCASE_H
