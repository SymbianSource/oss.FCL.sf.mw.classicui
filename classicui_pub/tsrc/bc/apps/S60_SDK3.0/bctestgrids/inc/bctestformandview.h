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









#ifndef C_CBCTESTGRIDSCASE_H
#define C_CBCTESTGRIDSCASE_H

#include "bctestcase.h"

class CBCTestGridsContainer;
class CCoeControl;
class CEikonEnv;

/**
 * test case for various list classes
 */
class CBCTestForMAndView: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestForMAndView* NewL( CBCTestGridsContainer* aContainer );
    
    /**
     * Destructor
     */
    virtual ~CBCTestForMAndView();
    
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
    
    void TestForAknGridML();
     
    /**
     * Test TestForAknGridViewL
     */
     void TestForAknGridViewL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestForMAndView( CBCTestGridsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestGridsContainer* iContainer;
    
    };

class CBCTestForGridView: public CAknGridView
    {
    friend class CBCTestForMAndView;
    };

#endif // BCTESTGRIDSCASE_H