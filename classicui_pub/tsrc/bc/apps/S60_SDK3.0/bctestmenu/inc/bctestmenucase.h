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









#ifndef BCTEST_MENUCASE_H
#define BCTEST_MENUCASE_H

#include <eikmenub.h>
#include <eikmenup.h>
#include <eikenv.h>

#include "bctestcase.h"

class CBCTestMenuContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestMenuCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMenuCase* NewL( CBCTestMenuContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMenuCase();
    
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
    void TestEikMenuBarL();
    void TestEikMenuPaneL(); 
    void TestEikMenuBarTitleL();
    void TestEikMenuPaneTitleL();
    void TestEikMenuPaneItemL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestMenuCase( CBCTestMenuContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
    void DestroyMenuPaneL();
    void CreateMenuPaneL();

private: // data

    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;
    CEikMenuBar* iEikMenuBar;
    CEikMenuPane* iEikMenuPane;
    CEikMenuBarTitle* iEikMenuBarTitle;
    CEikMenuPaneTitle* iEikMenuPaneTitle;
    CEikMenuPaneItem* iEikMenuPaneItem;
    /**
     * Pointer to container.
     * not own
     */
    CBCTestMenuContainer* iContainer;
    
    CEikonEnv* iEikEnv;
    
    };

#endif // BCTEST_MenuCASE_H