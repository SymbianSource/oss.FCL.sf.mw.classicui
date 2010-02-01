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
* Description:         test case for query value classes
*
*/








#ifndef C_CBCTESTQUERYVALUE_H
#define C_CBCTESTQUERYVALUE_H

#include "bctestcase.h"

class CEikonEnv;
class CBCTestQueryContainer;

/**
* test case for various list classes
*/
class CBCTestQueryValue: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestQueryValue* NewL( CBCTestQueryContainer* aContainer, 
        CEikonEnv* aEnv );
    
    /**
     * Destructor
     */
    virtual ~CBCTestQueryValue();
    
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
    void TestQueryValueDateL();
    
    void TestQueryValueDurationL();
    
    void TestQueryValueNumberL();
    
    void TestQueryValuePhoneL();
    
    void TestQueryValueTextL(); 
    
    void TestQueryValueTimeL();
            
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestQueryValue(  CBCTestQueryContainer* aContainer,
        CEikonEnv* aEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    /**
     * Not Own
     */
    CBCTestQueryContainer* iContainer;
    
    /**
     * Not Own
     */
    CEikonEnv* iEnv;
        
    };

#endif // C_CBCTESTQUERYVALUE_H