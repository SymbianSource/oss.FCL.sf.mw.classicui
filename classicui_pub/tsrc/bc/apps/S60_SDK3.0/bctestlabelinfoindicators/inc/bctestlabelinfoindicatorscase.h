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
* Description:         Declares test bc for labelinfoindicators testcase.
*
*/









#ifndef C_CBCTESTLABELINFOINDICATORSCASE_H
#define C_CBCTESTLABELINFOINDICATORSCASE_H

#include "bctestcase.h"

class CBCTestLabelInfoIndicatorsContainer;
class CCoeControl;

/**
 * test case for various labelinfoindicators classes
 */
class CBCTestLabelInfoIndicatorsCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestLabelInfoIndicatorsCase* NewL( 
        CBCTestLabelInfoIndicatorsContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestLabelInfoIndicatorsCase();

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
     * TestFunctionsForFileNameLabelL  function
     */
    void TestFunctionsForFileNameLabelL();
    
    /**
     * TestFunctionsForEikLabelL  function
     */
    void TestFunctionsForEikLabelL();
    
    /**
     * TestFunctionsForIndicatorsL  function
     */    
    void TestFunctionsForIndicatorsL();

    /**
     * TestFunctionsForIndicatorsOverLoadL  function
     */    
    void TestFunctionsForIndicatorsOverLoadL();
    
    /**
     * TestFunctionsForInfoPopupNoteL  function
     */     
    void TestFunctionsForInfoPopupNoteL();
    
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestLabelInfoIndicatorsCase( 
        CBCTestLabelInfoIndicatorsContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

   /**
     * Pointer to container.
     * not own
     */
    CBCTestLabelInfoIndicatorsContainer* iContainer;
    
   /**
     * Pointer to CEikonEnv.
     * not own
     */
    CEikonEnv* iEikEnv;    
    
    };

#endif // C_CBCTESTLABELINFOINDICATORSCASE_H
