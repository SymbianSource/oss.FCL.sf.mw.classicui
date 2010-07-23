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









#ifndef C_BCTESRUTILITIESCASE_H
#define C_BCTESRUTILITIESCASE_H

#include <coecobs.h>

#include "bctestcase.h"

class CBCTestUtilitiesContainer;
class CCoeControl;
class CEikFormattedCellListBox;
class CEikColumnListBox;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestUtilitiesCase: public CBCTestCase
    {
public: 

// constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestUtilitiesCase* NewL( CBCTestUtilitiesContainer* aContainer );
    
    /**
     * Destructor
     */
    virtual ~CBCTestUtilitiesCase();
    
// from CBCTestUtilitiesCase
    
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
    
// test functions of AknUtils
    
     void TestTextUtilsL();
     
     void TestSelectionServiceL();
     
     void TestAknFindL();
     
     void TestAknEditUtilsL();
     
     void TestOtherAknUtilsL();
     
     void TestFilterModelAndItemL();
     
     void TestAknLayoutUtilsL();
          
     void TestAknDrawL();
     
// test function of AknBidiTextUtils

     void TestAknBidiTextUtilsL();
     
// test functions of CAknEnv

    void TestAknEnvL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestUtilitiesCase( CBCTestUtilitiesContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data

    /**
     * Pointer to container.
     * not own
     */     
    CBCTestUtilitiesContainer* iContainer;
    
    /**
     * Pointer to formatted cell list box.
     * Own
     */
    CEikFormattedCellListBox* iFormatList;
    
    /**
     * Pointer to column list box.
     * Own
     */
    CEikColumnListBox* iColumnList;
    
    /**
     * Pointer to CEikonEnv.
     * Not own
     */
    CEikonEnv* iEnv;
    
    };
    
/** 
 * Test class implement MCoeControlObserver
 */
class TBCTestControlObserver: public MCoeControlObserver
    {
public:
    
    void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    
    };

#endif // C_BCTESRUTILITIESCASE_H