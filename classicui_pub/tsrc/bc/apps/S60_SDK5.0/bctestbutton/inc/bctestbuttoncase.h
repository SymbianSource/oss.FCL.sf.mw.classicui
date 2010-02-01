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









#ifndef C_BCTEST_BUTTONCASE_H
#define C_BCTEST_BUTTONCASE_H

#include "bctestcase.h"
#include <aknbutton.h>

class CBCTestButtonContainer;
class CCoeControl;
class CAknButtonStateEx;
class CAknButtonEx;

/**
* test case for various list classes
*/
class CBCTestButtonCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
    * Symbian 2nd static constructor
    */
    static CBCTestButtonCase* NewL( CBCTestButtonContainer* aContainer );

    /**
    * Destructor
    */
    virtual ~CBCTestButtonCase();

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
     * Test AknButtonState functions
     */
    void TestAknButtonStateL();

    /**
     * Test AknButton functions
     */
    void TestAknButtonL();
    void TestAknButtonExtL();
    void TestAknButtonProL();
    void TestAknButtonUtiL();

    CGulIcon* CreateIconL();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestButtonCase( CBCTestButtonContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestButtonContainer* iContainer;
    CEikonEnv *eikEnv;

    };


#endif // C_BCTEST_BUTTONCASE_H
