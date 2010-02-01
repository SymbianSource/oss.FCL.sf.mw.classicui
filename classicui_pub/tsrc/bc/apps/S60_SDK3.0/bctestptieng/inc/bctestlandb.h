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









#ifndef BCTEST_PTIENG_LAN_DB_H
#define BCTEST_PTIENG_LAN_DB_H

#include "bctestcase.h"

class CPtiLanguageDatabase;

/**
* test case for various list classes
*/
class CBCTestLanDB: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestLanDB* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestLanDB();
    
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
    CBCTestLanDB();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

    void SetupL();
    void Teardown();
    void TestDBInfoL();
    void TestImplL();
    void TestOthersL();

//data
    CPtiLanguageDatabase* iDB;
    };

#endif // BCTEST_PTIENG_LAN_DB_H