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


#ifndef C_CBCTESTDOMAKNRCLASSCASE_H
#define C_CBCTESTDOMAKNRCLASSCASE_H

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
class CBCTestDomAknRClassCase: 
    public CBCTestCase
    ,public MEikMenuObserver
    {
public: // constructor and destructor
    
    /**
     * Symbian 2nd static constructor
     */
    static CBCTestDomAknRClassCase* NewL( 
        CBCTestDomAiwAknContainer* aContainer );
    
    /**
     * Destructor
     */
    virtual ~CBCTestDomAknRClassCase();
    
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
     *  themselves when they are displayed, and de-emphasise themselves when
     *  they stop displaying.
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
     * for testing APIs in AknAsyncDemoNotify.h .  
     * Callback function for the CPeriodic. Calculates the current frame, 
     * keeps the background light from turning off and orders the CBillboard 
     * to do the rendering for each frame.
     *
     * @since S60 v5.0         
     *@param aInstance Pointer to this instance of CBillboardContainer.
     */
     static TInt AknAsyncDemoNotifyCallBack( TAny* aInstance );
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */
    void TestAknAsyncDemoNotify();

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknAnimation();     

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */  
    void TestAknBattery();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknCapServerClient();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknCharMap();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknCustomCursorSupport();

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknDateFormatUtils();  

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknEcsDetector(); 
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknEdwinFormAccessor();  
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknEikSrvc();  

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknExtendedInputCapabilities() ;
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknFileFilterFactory();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknFontIdLayoutFont(); 
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknGlobalPopupPriorityController();

    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknIncallBubbleNotify();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknIndicator();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknInputBlock();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknJapaneseReading();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknKeyRotator();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknLaunchAppService();  
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestAknLayoutConfig();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestCAknLibrary();
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestListBox();  
    
    /**
     * Test functions
     *
     * @since S60 v5.0            
     */    
    void TestTAknLineBreaker();            

    
    
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestDomAknRClassCase( CBCTestDomAiwAknContainer* aContainer );
    
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
    CBCTestDomAiwAknContainer* iContainer;    
  
    };

#endif // C_CBCTESTDOMAKNRCLASSCASE_H