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









#ifndef BCTEST_PTICORE_H
#define BCTEST_PTICORE_H

#include "bctestcase.h"

class CPtiCore;

/**
* test case for various list classes
*/
class CBCTestPtiCore: public CBCTestCase
    {
public: // constructor and destructor

    /**
    * Symbian 2nd static constructor
    */
    static CBCTestPtiCore* NewL();

    /**
    * Destructor
    */
    virtual ~CBCTestPtiCore();

public: // from CBCTestCase

    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

//new funcs

    /**
    * @return the 1st core UID in core list
    */
    static TInt TestListCoreL();

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
        void TestJapaneseL();
        void TestChineseL();
        void TestUserDictL();
        void TestPredictiveLatinL();
    void TestGeneralL();

    /**
     * C++ default constructor
     */
    CBCTestPtiCore();

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

    void SetupL();
    void Teardown();

//data
    CPtiCore* iCore;
    };

#endif // BCTEST_PTICORE_H