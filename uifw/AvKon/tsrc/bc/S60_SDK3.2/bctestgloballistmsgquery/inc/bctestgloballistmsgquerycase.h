/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test cases declaration for BCTestGlobalListMsgQuery.
*
*/

#ifndef BCTESTGLOBALLISTMSGQUERYCASE_H
#define BCTESTGLOBALLISTMSGQUERYCASE_H

#include "bctestcase.h"

class CBCTestGlobalListMsgQueryContainer;
class CCoeControl;
class CBCTestActiveEngine;

/**
* Test cases for global list message query.
*/
class CBCTestGlobalListMsgQueryCase: public CBCTestCase
    {
public: // constructor and destructor
    /**
    * Symbian static constructor.
    */
    static CBCTestGlobalListMsgQueryCase* NewL( CBCTestGlobalListMsgQueryContainer* aContainer );

    /**
    * Destructor.
    */
    virtual ~CBCTestGlobalListMsgQueryCase();

public: // from CBCTestCase
    /**
    * Execute corresponding test functions for UI command.
    Ä
    * @param aCmd UI command.
    */
    void RunL( TInt aCmd );

protected: // new functions
    /**
    * Build autotest script.
    */
    void BuildScriptL();

    /**
     * Create control or allocate resource for test.
     *
     * @param aCmd UI command, maybe you need to do some work for different outline.
     */
    void PrepareCaseL( TInt aCmd );

    /**
     * Release resource used in test.
     */
    void ReleaseCaseL();

    /**
     * Test functions
     */
    void TestAllL();
    void TestGlobalListMsgQueryL();

private: // constructor
    /**
     * C++ default constructor.
     */
    CBCTestGlobalListMsgQueryCase( CBCTestGlobalListMsgQueryContainer* aContainer );

    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();

private: // data
    /**
     * Pointer to a control, maybe you need one in your test.
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestGlobalListMsgQueryContainer* iContainer;
    
    /**
     * Pointer to active engine helper class.
     * own
     */
    CBCTestActiveEngine* iActiveEngine;
    };

#endif

// End of file
