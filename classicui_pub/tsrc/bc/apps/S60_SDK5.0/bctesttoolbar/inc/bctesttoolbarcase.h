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









#ifndef C_BCTESTTOOLBARCASE_H
#define C_BCTESTTOOLBARCASE_H

#include <akntoolbarobserver.h>

#include "bctestcase.h"

class CBCTestToolBarContainer;
class CCoeControl;

/**
* test case for various list classes
*/
class CBCTestToolBarCase: public CBCTestCase,
						   public MAknToolbarObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestToolBarCase* NewL( CBCTestToolBarContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestToolBarCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

public: // from MAknToolbarObserver
    
    /**
    * Should be used to set the properties of some toolbar components 
    * before it is drawn.
    * @param aResourceId The resource ID for particular toolbar
    * @param aToolbar The toolbar object pointer
    */
    void DynInitToolbarL( TInt aResourceId, CAknToolbar* aToolbar );
    
	/**
	* Handles toolbar events for a certain toolbar item.
	* @param aCommand The command ID of some toolbar item.
	*/
    void OfferToolbarEventL( TInt aCommand );

protected: // new functions
    
    /**
    * Build autotest script
    */
    void BuildScriptL();
    
    /**
     * Test functions
     */
    void TestFunctionL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestToolBarCase( CBCTestToolBarContainer* aContainer );
    
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
    CBCTestToolBarContainer* iContainer;
    
    };

class CBCTestToolBarObserver : public CBase, public MAknToolbarObserver
{
	public: // from MAknToolbarObserver
    
    /**
    * Should be used to set the properties of some toolbar components 
    * before it is drawn.
    * @param aResourceId The resource ID for particular toolbar
    * @param aToolbar The toolbar object pointer
    */
    //void DynInitToolbarL( TInt aResourceId, CAknToolbar* aToolbar );
    
	/**
	* Handles toolbar events for a certain toolbar item.
	* @param aCommand The command ID of some toolbar item.
	*/
    void OfferToolbarEventL( TInt aCommand );
    //void Call();

};	
#endif // C_BCTESTTOOLBARCASE_H