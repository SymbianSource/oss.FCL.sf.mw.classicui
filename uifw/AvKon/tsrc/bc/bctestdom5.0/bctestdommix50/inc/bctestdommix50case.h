/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  declaration of test case
*
*/


#ifndef C_BCTESTDOMMIX50CASE_H
#define C_BCTESTDOMMIX50CASE_H

#include "bctestcase.h"

class CBCTestDomMix50Container;
class CCoeControl;

/**
 * test case for various classes
 */
class CBCTestDomMix50Case: public CBCTestCase
    {

public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestDomMix50Case* NewL( CBCTestDomMix50Container* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestDomMix50Case();

public:
// from base class CBCTestCase

    /**
     * from base class CBCTestCase
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
     * Test for CAknPopupForm
     */
    void TestCAknPopupFormCaseL();

    /**
     * Test for CAknCharMap
     */
    void TestCAknCharMapCaseL();

    /**
     * Test for CAknCharMapDialog
     */
    void TestCAknCharMapDialogCaseL();

    /**
     * Test for CAknVolumePopup
     */
     void TestCAknVolumePopupCaseL();

    /**
     * Test for CAknTransparentCameraSettingPage
     */
     void TestCAknTransparentCameraSettingPageCaseL();

    /**
     * Test for CAknSingle2GraphicStyleListBox
     */
    void TestCAknSingle2GraphicStyleListBoxCaseL();

    /**
     * Test for CAknExtendedInputCapabilities
     */
    void TestCAknExtendedInputCapabilitiesCaseL();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestDomMix50Case( CBCTestDomMix50Container* aContainer );

    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

private: // memeber data

    /**
     * Pointer to CEikonEnv
     * own
     */    
    CEikonEnv* iEnv;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomMix50Container* iContainer;

    };

#endif // C_BCTESTDOMMIX50CASE_H
