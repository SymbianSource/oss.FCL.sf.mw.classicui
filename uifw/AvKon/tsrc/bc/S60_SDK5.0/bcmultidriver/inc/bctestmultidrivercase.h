/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef C_MultiDriverCASE_H
#define C_MultiDriverCASE_H

#include "bctestcase.h"

class CMultiDriverContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CMultiDriverCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CMultiDriverCase* NewL( CMultiDriverContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CMultiDriverCase();
    
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
     * Test functions
     */
    void TestFunctionL();
    
    void TestFunction2L();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CMultiDriverCase( CMultiDriverContainer* aContainer );
    
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
    CMultiDriverContainer* iContainer;
    
    };

#endif // C_MultiDriverCASE_H