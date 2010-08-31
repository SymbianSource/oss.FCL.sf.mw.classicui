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









#ifndef C_CBCTESTAPPFRMAKNVIEWCASE_H
#define C_CBCTESTAPPFRMAKNVIEWCASE_H

#include "bctestcase.h"
#include "aknview.h"
#include "bctestappfrmview.h"

class CBCTestAppFrmContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestAppFrmAknViewCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestAppFrmAknViewCase* NewL( CBCTestAppFrmContainer* aContainer ,CAknView* aView);
    
    /**
    * Destructor
    */
    virtual ~CBCTestAppFrmAknViewCase();
    
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
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void TestFunction();
  
    void TestPublicFunction();
    
    void TestProtectedFunction();         
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestAppFrmAknViewCase( CBCTestAppFrmContainer* aContainer ,CAknView* aView);
    
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
    CBCTestAppFrmContainer* iContainer;
    
    CAknView* iView;
    
    };

#endif // C_CBCTESTAPPFRMAKNVIEWCASE_H