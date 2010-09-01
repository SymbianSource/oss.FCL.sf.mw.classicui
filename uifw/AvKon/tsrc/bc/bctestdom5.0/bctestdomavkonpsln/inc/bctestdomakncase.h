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


#ifndef C_BCTESTDOMAKNDOMAINCASE_H
#define C_BCTESTDOMAKNDOMAINCASE_H

#include "bctestcase.h"

class CBCTestDomAvkonPslnContainer;
class CCoeControl;

/**
* test case for various classes
*/
class CBCTestDomAknCase: public CBCTestCase
    {
    
public: 
// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomAknCase* NewL( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomAknCase();
    
// from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

protected: 
// new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * TestAknSkinnableClockL
     */
    void TestSkinnableClockL();
    
    /**
     * TestAknSmallIndicatorL
     */
    void TestSmallIndicatorL();
        
    /**
     * TestAknSoftNotifierL
     */
    void TestSoftNotifierL();
    
    /**
     * TestAknStatuspaneUtils
     */
    void TestStatuspaneUtilsL();
    
    /**
     * TestAknPopupContentL
     */
    void TestPopupContentL();
    
    /**
     * TestSyncDrawL
     */
    void TestSyncDrawL();
    
    /**
     * TestAknTaskListL
     */
    void TestTaskListL();
    
    /**
     * TestAknTransitionUtilsL
     */
    void TestTransitionL();
    
    /**
     * TestCameraSettingPageL
     */
    void TestCameraSettingPageL();
    
    /**
     * TestAknVolumePopupL
     */    
     void TestAknVolumePopupL();
     
    /**
     * TestLafSystemFontL
     */    
     void TestLafSystemFontL();
    
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomAknCase( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomAvkonPslnContainer* iContainer;
    
    };

#endif // C_BCTESTDOMAVKONPSLNCASE_H
