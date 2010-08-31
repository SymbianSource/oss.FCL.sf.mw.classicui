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
* Description:         test case for setting list box classes
*
*/








#ifndef C_CBCTESTLISTSETTINGCASE_H
#define C_CBCTESTLISTSETTINGCASE_H

#include <akncheckboxsettingpage.h>

#include "bctestlistbasecase.h"

class CEikSettingsListBox;
class CBCTestListContainer;

/**
* test case for various list classes
*/
class CBCTestListSettingCase: public CBCTestListBaseCase
    {
public: 

// constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestListSettingCase* NewL( CBCTestListContainer* aContainer,
        CEikonEnv* aEikEnv );
    
    /**
    * Destructor
    */
    virtual ~CBCTestListSettingCase();
    
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
    * Prepare necessary resource for test case
    * @param aCmd, UI command
    */
    void PrepareCaseL( TInt aCmd );
    
    /**
    * Release resource used by test case
    */
    void ReleaseCase();
    
    /**
    * test functions
    */
    void TestSettingListL( TInt aCmd );
    
private: 

// constructor
    
    /**
    * C++ default constructor
    */
    CBCTestListSettingCase( CBCTestListContainer* aContainer,
        CEikonEnv* aEikEnv );
    
    /**
    * Symbian 2nd constructor
    */
    void ConstructL();
    
// from CBCTestListBaseCase
    
    /**
    * Appends graphics data.
    * @param Pointer of icon using graphics for listbox.
    */
    virtual void GraphicIconL( CArrayPtr<CGulIcon>* aIcons );
    
private: // data
    
    CEikSettingsListBox* iListBox; // own
       
    };

/**
 * class for testing protected API of CAknListSettingPage
 */    
class CBCTestCheckSettingPage: public CAknCheckBoxSettingPage
    {
    friend class CBCTestListSettingCase;
    
public:

    CBCTestCheckSettingPage(TInt aResourceID, 
        CSelectionItemList* aItemArray );
    
    };

#endif // C_CBCTESTLISTSETTINGCASE_H