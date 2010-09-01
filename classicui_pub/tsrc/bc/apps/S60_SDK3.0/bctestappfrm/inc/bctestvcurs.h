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
* Description:         test bc for the volume control API(s)
*
*/








#ifndef C_TESTVCURS_H
#define C_TESTVCURS_H

#include "bctestcase.h"

/**
* test case for testing volume setting page.
*/
class CBCTestVCursor: public CBCTestCase
    {
public:
    /** 
    * symbian NewL
    * @param aView, pointer to the active view
    */
    static CBCTestVCursor* NewL();

    /** dtor */
    virtual ~CBCTestVCursor();
    
    /**
    * from CBCTestCase
    */
    virtual void RunL(int aCmd);
    
protected: // new
    /** do necessary setup things. */
    virtual void SetupL();

    /** do necessary teardown things. */
    virtual void TearDownL();
    
    /** ctor */
    CBCTestVCursor();

    /** symbian 2nd phase ctor */
    void ConstructL();

    /** build the necessary test scripts */
    void BuildScriptL();

    /** perform test */
    void TestL();
    
private:
    };

#endif // C_TESTVCURS_H
