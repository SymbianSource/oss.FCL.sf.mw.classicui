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









#ifndef BCTEST_BUTTONSCASE_H
#define BCTEST_BUTTONSCASE_H

#include <eikcmbut.h>
#include <eiklbbut.h>
#include <eikmnbut.h>

#include "bctestcase.h"

class CBCTestButtonsContainer;
class CCoeControl;
class CEikLabeledButton;
class CEikTwoPictureCommandButton;
class CBCTestCmdBtnBase;

/**
* test case for various list classes
*/
class CBCTestButtonsCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestButtonsCase* NewL( CBCTestButtonsContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestButtonsCase();
    
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
     * Test TestEikBgftyAndEikBtgpcL
     */
    void TestEikBgftyAndEikBtgpcL();
    /**
     * Test TestEIKBTGPCL
     */
    void TestEikButbAndEikCbaL();
    /**
     * Test TestCEikCommandButton
     */
    void TestCEikCommandButtonL();
    /**
     * Test TestCEikTwoPictureCmd
     */
    void TestCEikTwoPictureCmdL();
    /**
     * Test TestCEikInverterCmdL
     */
    void TestCEikInverterCmdL();
     /**
     * Test TestCEikTextBtnL
     */
    void TestCEikTextBtnL();
    /**
     * Test TestCEikBitmapBtnL
     */
    void TestCEikBitmapBtnL();
    /**
     * Test TestEikCmbutAndEikLbbutL
     */
    void TestCEikLabeledBtnL();
    /**
     * Test TestMnbutAndBtgpsAndBtgrpL
     */
    void TestMnbutAndBtgpsAndBtgrpL();
    
    /**
     * Test TestCbaButtonL
     */
    void TestCbaButtonL();
    
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestButtonsCase( CBCTestButtonsContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();

	CEikCommandButton* SetupCommandBtnL();
	void TeardownCommandBtnL(CEikCommandButton* aBtn);
	void TestSetBtnLayoutL();
	void TestExcessSpace();
	void TestStuff();
	void TestImgBtnL();
	void TestStackRelatedL();
	void TestCommandButtonBaseL();
	void TestButtonBaseL();
	
	CEikTwoPictureCommandButton* SetupTwoPictureCmdL();
	void TestSetTwoPicturesL();
	void TeardownTwoPictureCmdL( CEikTwoPictureCommandButton* aBtn );
    
    CEikInverterCommandButton* SetupInverterCmdL();
    void TeardownInverterCmdL( CEikInverterCommandButton* aBtn );
    
    CEikTextButton* SetupTextBtnL();
    void TeardownTextBtnL( CEikTextButton* aBtn );
    
    CEikBitmapButton* SetupBitmapBtnL();
    void TeardownBitmapBtnL( CEikBitmapButton* aBtn );
    
    CEikLabeledButton* SetupLabeledBtnLC();
    void TeardownLabeledBtnL( CEikLabeledButton* aBtn );
    
private: // data
    
    CBCTestCmdBtnBase* iCmdBtnBase;//own

    /**
     * Pointer to container.
     * not own
     */
    CBCTestButtonsContainer* iContainer;
    
    CEikonEnv* iEnv;
    
    };
/**
*  For MEikCommandObserver classes test
*/
class TBCTestCommandObserver: public MEikCommandObserver
    {
    void ProcessCommandL( TInt aCommandId ); 
    };
/**
*  For MEikMenuObserver classes test
*/
class TBCTestMenuObserver: public MEikMenuObserver
    {
    void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    
    void ProcessCommandL( TInt aCommandId );
    };
/**
*  For CEikLabeledButton classes test 
*/
class CBCTestLabeledButton: public CEikLabeledButton
    {
    friend class CBCTestButtonsCase;
    };
/**
*  For CEikTwoPictureCommandButton classes test 
*/

class CBCTestTwoPicture: public CEikTwoPictureCommandButton
    {
    friend class CBCTestButtonsCase;
    };

/**
*  For CEikCommandButtonBase classes test 
*/

class CBCTestCmdBtnBase: public CEikCommandButtonBase
    {
    friend class CBCTestButtonsCase;
    };
/**
*  For CEikButtonBase classes test 
*/

class CBCTestBtnBase: public CEikButtonBase
    {
    friend class CBCTestButtonsCase;
    };

/**
 * For CEikInverterCommandButton classes test
 */
class CBCTestInverterCmdButton: public CEikInverterCommandButton
    {
    friend class CBCTestButtonsCase;
    };

/**
 * For CEikMenuButton classes test
 */
class CBCTestMenuButton: public CEikMenuButton
    {
    friend class CBCTestButtonsCase;
    }; 

#endif // BCTEST_BUTTONSCASE_H