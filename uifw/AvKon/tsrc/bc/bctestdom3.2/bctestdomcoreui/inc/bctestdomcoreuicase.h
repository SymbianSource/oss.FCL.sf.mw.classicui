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
* Description:  test case
*
*/


#ifndef C_CBCTESTDOMCOREUICASE_H
#define C_CBCTESTDOMCOREUICASE_H

#include "bctestcase.h"

class CBCTestDomCoreUiContainer; 
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestDomCoreUiCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomCoreUiCase* NewL( CBCTestDomCoreUiContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomCoreUiCase();
    
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
     * Create control or allocate resource for test
     * @param aCmd UI command, maybe you need to do some work 
     * for different outline
     */
    void PrepareCaseL( TInt aCmd );
    
    /**
     * Release resource used in test
     */
    void ReleaseCaseL();
    
    /**
     * Test functions
     */
    void TestFunctionL();
    
    /**
     * Test TestMenuSATInterfaceL
     */
    void TestMenuSATInterfaceL();
    
    /**
     * Test TestAddVoiceTagDialogL
     */
    void TestAddVoiceTagDialogL();
    
    /**
     * Test TestChangeVoiceTagDialogL
     */
    void TestChangeVoiceTagDialogL();
    
    /**
    * Test TestEraseVoiceTagDialogL
    */
    void TestEraseVoiceTagDialogL();
    
    /**
    * Test TestVoiceDialerL
    */
    void TestVoiceDialerL();
    
    /**
     * Test TestVoiceTagContactL
     */
    void TestVoiceTagContactL();
    
    /**
     * Test TestVoiceTagFieldL
     */
    void TestVoiceTagFieldL();
    
    /**
     * Test TestVoiceRecogL
     */
    void TestVoiceRecogL();
    
    /**
     * Test TestVoiceRecognitionDialogL
     */
    void TestVoiceRecognitionDialogL();
    
    void TestPlaybackVoiceTagDialogL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomCoreUiCase( CBCTestDomCoreUiContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to a control, maybe you need one in your test
     * own
     */
    CCoeControl* iControl;

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomCoreUiContainer* iContainer;
    
    };

#endif 
