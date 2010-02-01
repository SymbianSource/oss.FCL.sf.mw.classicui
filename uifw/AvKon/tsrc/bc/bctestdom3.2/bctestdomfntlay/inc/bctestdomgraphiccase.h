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


#ifndef C_CBCTESTDOMGRAPHICCASE_H
#define C_CBCTESTDOMGRAPHICCASE_H

#include <aknlayout2scalabledatadef.h>

#include "bctestcase.h"
/**
* test case for various list classes
*/
class CBCTestDomGraphicCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomGraphicCase* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomGraphicCase();
    
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
    CBCTestDomGraphicCase();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
    * Test Layout2ScalableDataDef
    */
    void TestLayout2ScalableDataDefL();
    
    /**
    * Test iconconfig
    */
    void TestIconconfigL();
    
private: // data
      
    
    };

#endif // C_CBCTESTDOMGRAPHICCASE_H
