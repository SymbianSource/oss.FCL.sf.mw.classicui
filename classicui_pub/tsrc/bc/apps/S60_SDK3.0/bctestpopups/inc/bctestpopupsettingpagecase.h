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
* Description:         Declares test bc for popup setting page testcase.
*
*/









#ifndef C_CBCTESTPOPUPSETTINGPAGECASE_H
#define C_CBCTESTPOPUPSETTINGPAGECASE_H

#include <aknpopupsettingpage.h>
#include <aknpopup.h>

#include "bctestcase.h"
#include "bctestpopupsettingpage.h"

class CBCTestPopupsContainer;
class CCoeControl;
class CEikonEnv;
    
/**
 * test case for various popups classes
 */
class CBCTestPopupSettingPageCase: public CBCTestCase
    {
public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestPopupSettingPageCase* 
        NewL( CBCTestPopupsContainer* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestPopupSettingPageCase();

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
     * Test functions for CAknPopupSettingPage
     */
    void TestFunctionsForSettingPageL();
    
    /**
     * Test functions for CAknPopupSettingList
     */
    void TestFunctionsForSettingListL( 
        CAknPopupSettingList* aPopSettingList, 
        MAknQueryValue* aQueryValueText );
 
    /**
     * Test functions for AknPopupLayouts
     */   
    void TestFunctionForPopLayoutsL();
            
private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestPopupSettingPageCase( CBCTestPopupsContainer* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestPopupsContainer* iContainer;
    
    /**
     * Pointer to CEikonEnv.
     * not own
     */
    CEikonEnv* iEikEnv;  

    /**
     * Pointer to CBCTestPopupSettingPage.
     * own
     */    
    CBCTestPopupSettingPage* iSettingPage;

    };

#endif // C_CBCTESTPOPUPSETTINGPAGECASE_H
