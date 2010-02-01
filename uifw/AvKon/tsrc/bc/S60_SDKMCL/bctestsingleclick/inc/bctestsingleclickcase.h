/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Test case class for bctestsingleclick.
*
*/

#ifndef C_BCTESTSINGLECLICKCASE_H
#define C_BCTESTSINGLECLICKCASE_H

#include "bctestcase.h"
#include <akncollection.h>

class CBCTESTSingleClickContainer;
class CCoeControl;
class MAknCollection;

/**
* test case for various classes
*/
class CBCTESTSingleClickCase: public CBCTestCase, public MAknCollection
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTESTSingleClickCase* 
        NewL( CBCTESTSingleClickContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTESTSingleClickCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );

//From MAknCollection
  /**
     * Returns the collection state. The state is combination of
     * flags defined in @c TStateFlag. 
     *
     * @return  Collection state.
     */
    virtual TUint CollectionState() const;

    /**
     * Notifies that item action menu (@c CAknItemActionMenu)
     * was closed. 
     */
    virtual void ItemActionMenuClosed();

    /** 
     * Extension function.
     *
     * @param  aExtensionId  Extension id. 
     * @param  a0            First extension method parameter.
     * @param  a1            Second extension method parameter.
     */    
    virtual TInt CollectionExtension(
            TUint aExtensionId, TAny*& a0, TAny* a1 );	
    
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
     * Test single click apis
     */
    void TestSingleClickL();

    /**
     * Test listbox api(s)
     */
    void TestListBoxL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTESTSingleClickCase( CBCTESTSingleClickContainer* aContainer );
    
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
    CBCTESTSingleClickContainer* iContainer;
    
    };

#endif // C_BCTESTSINGLECLICKCASE_H
