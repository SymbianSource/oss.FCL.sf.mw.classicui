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


#ifndef C_CBCTESTDOMLAYOUTSYSTEMCASE_H
#define C_CBCTESTDOMLAYOUTSYSTEMCASE_H

#include "bctestcase.h"

/**
* test case for various list classes
*/
class CBCTestDomLayoutSystemCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomLayoutSystemCase* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomLayoutSystemCase();
    
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
    CBCTestDomLayoutSystemCase();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    /**
    * Test Layout2AdaptationDataDef
    */
    void TestLayout2AdaptationDataDefL();
    
    /**
    * Test Layout2DataDef
    */
    void TestLayout2DataDefL();
    
    /**
    * Test Layout2Hierarchy
    */
    void TestLayout2HierarchyL();
    
    /**
    * Test Layout2HierarchyDef
    */
    void TestLayout2HierarchyDefL();
    
    };

#endif // C_CBCTESTDOMLAYOUTSYSTEMCASE_H
