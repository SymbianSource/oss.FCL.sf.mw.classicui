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









#ifndef BCTEST_eikbctrlCASE_H
#define BCTEST_eikbctrlCASE_H

#include "bctestcase.h"

class CBCTesteikbctrlContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTesteikbctrlCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTesteikbctrlCase* NewL( CBCTesteikbctrlContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTesteikbctrlCase();
    
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


private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTesteikbctrlCase( CBCTesteikbctrlContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTesteikbctrlContainer* iContainer;
    
    };

#endif // BCTEST_eikbctrlCASE_H