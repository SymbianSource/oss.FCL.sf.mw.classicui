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









#ifndef BCTEST_FORSLIDER_H
#define BCTEST_FORSLIDER_H

#include "bctestcase.h"

class CBCTestSliderAndIconsContainer;
class CCoeControl;
class CEikonEnv;

/**
* test case for various list classes
*/
class CBCTestForSlider: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestForSlider* NewL( CBCTestSliderAndIconsContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestForSlider();
    
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
     * Test TestSliderL
     */
    void TestSliderL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestForSlider( CBCTestSliderAndIconsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to CEikonEnv
     * own
     */    
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestSliderAndIconsContainer* iContainer;
    
    };

#endif // BCTEST_FORSLIDER_H