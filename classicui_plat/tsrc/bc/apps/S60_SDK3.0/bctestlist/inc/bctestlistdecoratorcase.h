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
* Description:         test case for aknlistboxlayoutdecorator
*
*/








#ifndef C_CBCTESTLISTDECORATORCASE_H
#define C_CBCTESTLISTDECORATORCASE_H

#include "bctestlistbasecase.h"

class CEikonEnv;
class CEikTextListBox;
class CBCTestListContainer;
class CColumnListBoxItemDrawer;

/**
* test case for various list classes
*/
class CBCTestListDecoratorCase: public CBCTestListBaseCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListDecoratorCase* NewL( 
        CBCTestListContainer* aContainer, CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListDecoratorCase();
    
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
    * Release resource used in test
    */
    void ReleaseCase();
    
    /**
    * Test functions
    */
    void TestLayoutDecoratorL();
        
private: // constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListDecoratorCase( CBCTestListContainer* aContainer, 
        CEikonEnv* aEikEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
private: // data
    
    /**
     * Own
     */
    CEikTextListBox* iListBox;
    
    };

#endif // C_CBCTESTLISTDECORATORCASE_H