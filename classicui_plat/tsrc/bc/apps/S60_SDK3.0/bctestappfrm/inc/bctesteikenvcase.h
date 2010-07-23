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








#ifndef C_TESTEIKENV_H
#define C_TESTEIKENV_H

#include "bctestcase.h"

class CBCTestAppFrmContainer;

/**
* test case for testing volume setting page.
*/
class CBCTestEikenv: public CBCTestCase
    { 
public:
    /** 
    * symbian NewL
    * @param aView, pointer to the active view
    */
    static CBCTestEikenv* NewL( CBCTestAppFrmContainer* aContainer );

    /** dtor */
    virtual ~CBCTestEikenv();
    
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
    CBCTestEikenv( CBCTestAppFrmContainer* aContainer );

    /** symbian 2nd phase ctor */
    void ConstructL();

    /** build the necessary test scripts */
    void BuildScriptL();

    /** perform test */
    void TestL();
    
private:
    CEikonEnv* iEikenv;
    CBCTestAppFrmContainer* iContainer;    
    };

#endif // C_TESTEIKENV_H
