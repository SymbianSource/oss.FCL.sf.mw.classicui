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
* Description:         Declares test bc for eik progress info testcase.
*
*/









#ifndef C_CBCTESTEIKPROGRESSINFOCASE_H
#define C_CBCTESTEIKPROGRESSINFOCASE_H

#include "bctestcase.h"

class CBCTestNoteContainer;
class CCoeControl;
class CEikProgressInfo;

/**
 * test case for various note classes
 */
class CBCTestEikProgressInfoCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestEikProgressInfoCase* NewL( 
        CBCTestNoteContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestEikProgressInfoCase();

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
     * TestPublicFunctionsL  function
     */
    void TestPublicFunctionsL();
    
    /**
     * TestProtectedFunctionsL  function
     */
    void TestProtectedFunctionsL();    

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestEikProgressInfoCase( CBCTestNoteContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestNoteContainer* iContainer;

    /**
     * Pointer to eikprogressinfo.
     * own
     */    
    CEikProgressInfo* iEikProgressInfo;
    
    };

#endif // C_CBCTESTEIKPROGRESSINFOCASE_H
