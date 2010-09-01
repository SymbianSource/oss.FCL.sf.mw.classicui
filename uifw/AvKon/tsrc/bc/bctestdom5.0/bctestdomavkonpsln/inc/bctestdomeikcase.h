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


#ifndef C_BCTESTDOMEIKCASE_H
#define C_BCTESTDOMEIKCASE_H

#include "bctestcase.h"

class CBCTestDomAvkonPslnContainer;
class CCoeControl;

/**
* test case for various classes
*/
class CBCTestDomEikCase: public CBCTestCase
    {
    
public: 
// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomEikCase* NewL( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomEikCase();
    
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
     * TestAlarmControlL
     */    
    void TestAlarmControlL();
    
    /**
     * TestSettingsListBoxDataL
     */    
    void TestSettingsListBoxDataL();
    
    /**
     * TestSettingsListBoxDataL
     */
    void TestEikSoftkeyImageL();
    
    /**
     * TestServAppUiBaseL
     */    
    void TestServAppUiBaseL();

private: 
// constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomEikCase( CBCTestDomAvkonPslnContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: 
// data

    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomAvkonPslnContainer* iContainer;
    
    };

#endif // C_BCTESTDOMTEMPLATECASE_H
