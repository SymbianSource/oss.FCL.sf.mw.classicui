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
* Description:         Declares test bc for wait note wrapper testcase.
*
*/









#ifndef C_CBCTESTWAITNOTEWRAPPERCASE_H
#define C_CBCTESTWAITNOTEWRAPPERCASE_H

#include "bctestcase.h"

class CBCTestNoteContainer;
class CCoeControl;
class CAknWaitNoteWrapper;
class CBCTestSubWaitNoteWrapper;

/**
 * test case for various note classes
 */
class CBCTestWaitNoteWrapperCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestWaitNoteWrapperCase* 
        NewL( CBCTestNoteContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestWaitNoteWrapperCase();

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
     * TestWaitNoteWrapperL function
     */
    void TestWaitNoteWrapperL();
    
    /**
     * TestOtherFunctionsL function
     */
    void TestOtherFunctionsL();    

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestWaitNoteWrapperCase( CBCTestNoteContainer* aContainer );

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
     * Pointer to waitnotewrapper.
     * own
     */    
    CAknWaitNoteWrapper* iWaitNoteWrapper;

    /**
     * Pointer to subwaitnotewrapper.
     * own
     */     
    CBCTestSubWaitNoteWrapper* iSubWaitNoteWrapper;
    
    };

#endif // C_CBCTESTWAITNOTEWRAPPERCASE_H
