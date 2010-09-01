/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of test case
*
*/


#ifndef C_BCTESTMIXMCLCASE_H
#define C_BCTESTMIXMCLCASE_H

#include "bctestcase.h"

class CEikonEnv;
class CBCTestMixMCLContainer;
class CCoeControl;
class CBCTestHWRMHapticsHelperActiveObject;

/**
 * test case for various classes
 * @since S60 v5.0
 */
class CBCTestMixMCLCase: public CBCTestCase
    {

public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     * @param aContainer  a point of Container 
     */
    static CBCTestMixMCLCase* NewL( CBCTestMixMCLContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestMixMCLCase();

public:
// from base class CBCTestCase

    /**
     * from base class CBCTestCase
     * Execute corresponding test functions for UI command
     * @param aCmd, UI command
     */
    void RunL( TInt aCmd );

private: // new functions

    /**
     * Build autotest script
     */
    void BuildScriptL();

    /**
     * Test for Haptics Apis
     */
    void TestHapticsL();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestMixMCLCase( CBCTestMixMCLContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // memeber data

    /**
     * Pointer to CEikonEnv
     * not own
     */    
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestMixMCLContainer* iContainer;
    
    /**
     * Pointer to haptics helper AO.
     * owned
     */
    CBCTestHWRMHapticsHelperActiveObject* iHapticsHelper;
    };

#endif // C_BCTESTMIXMCLCASE_H
