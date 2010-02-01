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









#ifndef C_CBCTESTTOUCHPANECASE_H
#define C_CBCTESTTOUCHPANECASE_H

//#include <aknfeppensupportinterface.h>
#include <akntouchpane.h>

#include "bctestcase.h"

class CBCTestTouchPaneContainer;
class CCoeControl;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestTouchPaneCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestTouchPaneCase* NewL( CBCTestTouchPaneContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestTouchPaneCase();
    
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
    CBCTestTouchPaneCase( CBCTestTouchPaneContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
   
    /**
     * TestAknTouchPaneL
     */
    void TestAknTouchPaneL();
    
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
    CBCTestTouchPaneContainer* iContainer;
    
    };

/**
 *  BCTestObserver class
 */
class CBCTestObserver: public CBase, public MAknTouchPaneObserver
    { 
    void HandleTouchPaneSizeChange();
    };

#if 0 //SDK API using Domain API Class
/**
 *  CBCTestFepPen class
 */

class CBCTestFepPen: public CBase, public MAknFepPenSupportInterface
    {
    void ActivatePenInputL();
    void DeactivatePenInputL();
    };
#endif
#endif // C_CBCTESTTOUCHPANECASE_H