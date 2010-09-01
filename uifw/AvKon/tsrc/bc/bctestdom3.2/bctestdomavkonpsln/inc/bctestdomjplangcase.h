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
* Description:  declaration of test case
*
*/


#ifndef C_BCTESTDOMJPLANGCASE_H
#define C_BCTESTDOMJPLANGCASE_H

#include "bctestcase.h"

class CBCTestDomAvkonPslnContainer;
class CCoeControl;

/**
* test case for various classes
*/
class CBCTestDomJPLangCase: public CBCTestCase
    {
    
public: 
// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomJPLangCase* NewL( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomJPLangCase();
    
// from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: 
// new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * TestJPLangUtilL()
     */
    void TestJPLangUtilL();
    
    /**
     * TestNumberGroupL()
     */
    void TestNumberGroupL();
    
    /**
     * TestGenericParamConsumerL()
     */
    void TestGenericParamConsumerL();
        
private: 
// constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomJPLangCase( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomAvkonPslnContainer* iContainer;
    
    };

#endif // C_BCTESTDOMTEMPLATECASE_H
