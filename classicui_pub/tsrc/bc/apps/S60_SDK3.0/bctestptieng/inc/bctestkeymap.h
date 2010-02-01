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









#ifndef BCTEST_PTIENG_KEYMAP_H
#define BCTEST_PTIENG_KEYMAP_H

#include "bctestcase.h"

class CPtiKeyMappings;
class MPtiKeyMappings;

/**
* test case for various list classes
*/
class CBCTestKeymap: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestKeymap* NewL();
    
    /**
    * Destructor
    */
    virtual ~CBCTestKeymap();
    
// from CBCTestCase
	
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

// new funcs

	static MPtiKeyMappings* CreateKeyMapL();

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
    CBCTestKeymap();
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

	void TestKeyData();
	void TestReverseMapping();
	void TestReplaceMappingL();
	void TestNextKey();
	void TestStartMapping();
	void TestMapping();
	void TestCreateL();
	void SetupL();
	void Teardown();

//data
	CPtiKeyMappings* iMap;
    };

#endif // BCTEST_PTIENG_KEYMAP_H