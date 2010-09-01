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


#ifndef C_CBCTESTDOMLAYOUTDATACASE_H
#define C_CBCTESTDOMLAYOUTDATACASE_H

#include "bctestcase.h"

/**
* test case for various list classes
*/
class CBCTestDomLayoutDataCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomLayoutDataCase* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomLayoutDataCase();
    
    // from CBCTestDomCase
    
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
    CBCTestDomLayoutDataCase();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
    * Test Layout2Def
    */
    void TestLayout2DefL();
    
    /**
    * Test Layout2ScalableDef
    */
    void TestLayout2ScalableDefL();
    
    /**
    * Test Layout2ScalableDef, because a lot of APIs 
    */
    void TestLayout2ScalableDef2L();
    
    
    };

#endif // C_CBCTESTDOMLAYOUTDATACASE_H
