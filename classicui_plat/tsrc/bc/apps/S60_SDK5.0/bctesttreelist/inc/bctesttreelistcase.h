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









#ifndef BCTEST_TEMPLATECASE_H
#define BCTEST_TEMPLATECASE_H

#include "bctestcase.h"

class CBCTestTreeListContainer;
class CCoeControl;
class CAknSingleStyleTreeList;

/**
* test case for various list classes
*/
class CBCTestTreeListCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
    * Symbian 2nd static constructor
    */
    static CBCTestTreeListCase* NewL( CBCTestTreeListContainer* aContainer );

    /**
    * Destructor
    */
    virtual ~CBCTestTreeListCase();

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
     * Test CAknTreeList functions
     */
    void TestTreeList();

    /**
     * Test CAknSingleStyleTreeList functions
     */    
    void TestSingleStyleTreeList();

    /**
     * Test CAknSingleColumnStyleTreeList functions
     */
    void TestSingleColumnStyleTreeList();

    /**
     * Test ScrollBar functions
     */
     void TestScrollBar();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestTreeListCase( CBCTestTreeListContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestTreeListContainer* iContainer;

    };
    

#endif // BCTEST_TEMPLATECASE_H
