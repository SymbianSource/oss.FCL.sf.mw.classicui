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
* Description: 
*
*/

#ifndef C_CBCTESTDOMAKNNOCTRLCASE_H
#define C_CBCTESTDOMAKNNOCTRLCASE_H

#include "bctestcase.h"
 
 
class CBCTestDomAiwAknContainer;
class CCoeControl;
class CEikonEnv;
 
/**
 *  test case for various classes
 *  
 *
 *  @code
 *    
 *  @endcode
 *
 *  @lib   
 *  @since S60 v5.0
 */  
class CBCTestDomAknNoCtrlCase: 
    public CBCTestCase
    ,public MEikMenuObserver
    {
    
public:  
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestDomAknNoCtrlCase* NewL( 
        CBCTestDomAiwAknContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestDomAknNoCtrlCase();
    
public: 

// from base class CBCTestCase  
 
    /**
     * From CBCTestCase.  
     * Execute corresponding test functions for UI command.
     *
     * @since S60 v5.0  
     * @param aCmd, UI command
     */
    void RunL( TInt aCmd );


// from base class MEikMenuObserver  
 
	/**
	 * From MEikMenuObserver.  
	 * Processes user commands.
	 *
	 * Derived classes must provide an implementation of this function which 
	 * responds to user commands appropriately based on a user-defined ID for
	 * the command.
	 *
     * @since S60 v5.0  	 
	 * @param aCommandId ID of the command to respond to. 
	 */
	virtual void ProcessCommandL(TInt aCommandId) ;    
	
	/** 
	 * From MEikMenuObserver.  
     * Called by the Uikon framework to handle the emphasising or 
     * de-emphasising of a menu window. 
     *
     *  CEikMenuBar objects call this on their observer to emphasise 
     *  themselves when they are displayed, and de-emphasise themselves
     *  when they stop displaying.
     *
     * @since S60 v5.0       
     * @param aMenuControl The menu control.
     * @param aEmphasis ETrue to emphasize the menu, EFalse otherwise. 
  	 */
	virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
	
	
protected: 
    
     
    /**
     * Build autotest script
     *
     * @since S60 v5.0       
     */
    void BuildScriptL();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */
    void TestAknDateFormatUtils(); //Not Ctrl 
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */                 
    void TestAknEcsDetector();    //Not Ctrl              
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */
    void TestAknEdwinFormAccessor(); //Not Ctrl   
            
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */
    void TestAknExtendedInputCapabilities(); //Not Ctrl               
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknFontIdLayoutFont();  //Not Ctrl              
               
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */               
    void TestAknJapaneseReading();//Not Ctrl

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknKeyRotator();   //Not Ctrl 
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknLaunchAppService();//Not Ctrl 

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknLayoutConfig();  //Not Ctrl         

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestCAknLibrary();      //Not Ctrl  
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestTAknLineBreaker();//Not Ctrl    
    
    
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomAknNoCtrlCase( CBCTestDomAiwAknContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
   
    /**
     * Pointer to container.
     * not own
     */
    CBCTestDomAiwAknContainer* iContainer;    
  
    };

#endif // C_CBCTESTDOMAKNNOCTRLCASE_H