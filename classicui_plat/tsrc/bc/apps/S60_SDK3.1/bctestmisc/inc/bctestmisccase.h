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









#ifndef C_CBCTESTMISCCASE_H
#define C_CBCTESTMISCCASE_H

#include "bctestcase.h"

class CBCTestMiscContainer;
class CCoeControl;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestMiscCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMiscCase* NewL( CBCTestMiscContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMiscCase();
    
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
      
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestMiscCase( CBCTestMiscContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
     * TestAknScreenModesL
     */
    void TestAknScreenModesL();

private: // data
    
    /**
     * Pointer to CEikonEnv
     * Not own
     */    
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestMiscContainer* iContainer;
    
    };

#endif // C_CBCTEST_MISCCASE_H