/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  view test case
*
*/


#ifndef C_BCTESTMIX50PATCHVIEWCASE_H
#define C_BCTESTMIX50PATCHVIEWCASE_H

#include "bctestcase.h"

class CBCTestMix50Container;
class CBCTestMix50View;
class CCoeControl;

/**
* test case for various classes
*/
class CBCTestMix50PatchViewCase: public CBCTestCase,
						   public MAknAliasKeyCodeResolver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestMix50PatchViewCase* NewL( 
            CBCTestMix50Container* aContainer,
            CBCTestMix50View* aView );
    
    /**
    * Destructor
    */
    virtual ~CBCTestMix50PatchViewCase();
    
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
     * Test the akn view
     */
    void TestAknViewL();
   
    /**
     * Test appui
     */
    void TestAknAppUiL();

    /**
     * Test app ui base
     */
    void TestAknAppUiBaseL();
    
    /**
     * Test app service base
     */
    void TestAknAppServiceBaseL();
    
    /**
    * Resolves keyboard layout dependent keycode for the given event 
    *
    * @since S60 3.1
    * @param aCode reference to variable to contain new keycode 
    * @param aKeyEvent reference to original, complete, event
    * @param aType indicating original event type
    * @return KErrNone on success, otherwise system wide error codes
    */
    inline TInt GetAliasKeyCode(TUint& /* aCode */, 
    		const TKeyEvent& /* aKeyEvent */,TEventCode /* aType */ )
    	{
    	return 0;
    	}
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestMix50PatchViewCase( CBCTestMix50Container* aContainer, 
            CBCTestMix50View* aView );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
    
    /**
     * Pointer to view
     * own
     */
	CBCTestMix50View* iView;
    /**
        * Pointer to view
        * own
        */
    CCoeControl* iControl;
    /**
     * Pointer to container.
     * not own
     */
    CBCTestMix50Container* iContainer;
    };

#endif /*C_BCTESTMIX50PATCHVIEWCASE_H*/
