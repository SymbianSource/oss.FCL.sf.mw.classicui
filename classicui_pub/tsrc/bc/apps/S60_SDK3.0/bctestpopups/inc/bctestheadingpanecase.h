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
* Description:         Declares test bc for heading pane testcase.
*
*/









#ifndef C_CBCTESTHEADINGPANECASE_H
#define C_CBCTESTHEADINGPANECASE_H

#include "bctestcase.h"

class CBCTestPopupsContainer;
class CCoeControl;

/**
 * test case for various popups classes
 */
class CBCTestHeadingPaneCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestHeadingPaneCase* NewL( CBCTestPopupsContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestHeadingPaneCase();

// from CBCTestCase

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
     * TestHeadingPaneL  function
     */
    void TestHeadingPaneL();
        
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestHeadingPaneCase( CBCTestPopupsContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPopupsContainer* iContainer;

    };

#endif // C_CBCTESTHEADINGPANECASE_H
