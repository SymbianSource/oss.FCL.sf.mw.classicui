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
* Description:         Declares test bc for popup testcase.
*
*/









#ifndef C_CBCTESTPOPUPCASE_H
#define C_CBCTESTPOPUPCASE_H

#include "bctestcase.h"

class CBCTestPopupsContainer;
class CCoeControl;

/**
 * test case for various popups classes
 */
class CBCTestPopupCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestPopupCase* NewL( CBCTestPopupsContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestPopupCase();

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
     * TestPopupL  function
     */
    void TestPopupL();

    /**
     * TestProtectedFunctionsL  function
     */    
    void TestProtectedFunctionsL();
    
    /**
     * TestTAknPopupFaderFunctionsL  function
     */   
    void TestTAknPopupFaderFunctionsL();   
        
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestPopupCase( CBCTestPopupsContainer* aContainer );

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

    };

#endif // C_CBCTESTPOPUPCASE_H
