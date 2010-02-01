/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:         declaration of test case
*
*/









#ifndef C_BCTESTMIX50CASE_H
#define C_BCTESTMIX50CASE_H

#include "bctestcase.h"

class CBCTestMix50Container;
class CCoeControl;

/**
 * test case for various classes
 */
class CBCTestMix50Case: public CBCTestCase
    {

public: // constructor and destructor

    /**
     * Symbian 2nd static constructor
     */
    static CBCTestMix50Case* NewL( CBCTestMix50Container* aContainer );

    /**
     * Destructor
     */
    virtual ~CBCTestMix50Case();

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
     * Test for CFormattedCellListBoxData
     */
    void TestCFormattedCellListBoxDataCaseL();

    /**
     * Test for CAknSearchField
     */
    void TestCAknSearchFieldCaseL();

    /**
     * Test for CAknPopupList
     */
    void TestCAknPopupListCaseL();

    /**
     * Test for CAknMessageQueryControl
     */
    void TestCAknMessageQueryControlCaseL();

    /**
     * Test for CAknPopupHeadingPane
     */
    void TestCAknPopupHeadingPaneCaseL();

    /**
     * Test for CEikButtonGroupContainer
     */
    void TestCEikButtonGroupContainerCaseL();
    
    /**
     * Test for CEikCba
     */
    void TestCEikCbaCaseL();

    /**
     * Test for CEikEdwin
     */
    void TestCEikEdwinCaseL();

    /**
     * Test for CAknSlider
     */
    void TestCAknSliderCaseL();

    /**
     * Test for CEikDialog
     */
    void TestCEikDialogCaseL();

    /**
     * Test for CEikCaptionedControl
     */
    void TestCEikCaptionedControlCaseL();

    /**
     * Test for CAknVolumeControl
     */
     void TestCAknVolumeControlCaseL();

    /**
     * Test for CAknSettingPage
     */
    void TestCAknSettingPageCaseL();

    /**
     * Test for CEikListBox
     */
     void TestCEikListBoxCaseL();

    /**
     * Test for CAknEdwinState
     */
     void TestCAknEdwinStateCaseL();

    /**
     * Test for CEikMenuPane
     */
     void TestCEikMenuPaneCaseL();

    /**
     * Test for CAknGrid
     */
    void TestCAknGridCaseL();

    /**
     * Test for CColumnListBoxItemDrawer
     */
    void TestCColumnListBoxItemDrawerCaseL();

    /**
     * Test for CAknLocationEditor
     */
    void TestCAknLocationEditorCaseL();

    /**
     * Test for CEikMfne
     */
    void TestCEikMfneCaseL();

    /**
     * Test for CAknUnitEditor
     */
    void TestCAknUnitEditorCaseL();

    /**
     * Test for CColumnListBoxData
     */
    void TestCColumnListBoxDataCaseL();
    /**
     * Test for MTouchFeedback
     */    
    void TestTouchFeedback() ;   
    /**
     * Test for CAknchoicelist
     */
    void TestCAknchoicelist();
    
    /**
     * Test for CAknButton
     */
    //komala void TestCAknButton();

private: // constructor

    /**
     * C++ default constructor
     */
    CBCTestMix50Case( CBCTestMix50Container* aContainer );

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
    CBCTestMix50Container* iContainer;

    };

#endif // C_BCTESTMIX50CASE_H
