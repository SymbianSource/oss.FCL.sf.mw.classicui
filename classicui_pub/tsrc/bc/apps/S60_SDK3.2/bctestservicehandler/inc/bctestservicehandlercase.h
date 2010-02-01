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









#ifndef BCTEST_SERVICEHANDLERCASE_H
#define BCTEST_SERVICEHANDLERCASE_H

#include "bctestcase.h"
#include <aiwcommon.h>
#include <eikmobs.h>    // MEikMenuObserver

class CBCTestServiceHandlerContainer;
class CBCTestServiceHandlerAppUi;
class CAiwServiceHandler;

/**
* test case for various list classes
*/
class CBCTestServiceHandlerCase: public CBCTestCase, public MAiwNotifyCallback,
                                 public MEikMenuObserver
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestServiceHandlerCase* NewL( CBCTestServiceHandlerContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestServiceHandlerCase();
    
public: // from CBCTestCase
    
    /**
    * Execute corresponding test functions for UI command
    * @param aCmd, UI command
    */
    void RunL( TInt aCmd );
    
public: // from MAiwNotifyCallback

    /**
     * Handles notifications caused by an asynchronous ExecuteCmdL call.
     * @param aCmdId The service command associated to the event.
     * @param aEventId Occured event, see AiwCommon.hrh.
     * @param aEvenParamList Event parameters, if any, as defined per
     *        related HandleCommandL.
     * @return Error code for the callback.
     */
    TInt HandleNotifyL( TInt aCmdId,
                        TInt aEventId,
                        CAiwGenericParamList& aEventParamList,
                        const CAiwGenericParamList& aInParamList );
                        
public: // from MEikMenuObserver
     
   /**
    * Called by the Uikon framework to handle the emphasising or de-emphasising of 
	* a menu window. 
	*
	* CEikMenuBar objects call this on their observer to emphasise 
	* themselves when they are displayed, and de-emphasise themselves when they 
	* stop displaying.
	*
	* @param aMenuControl The menu control.
	* @param aEmphasis ETrue to emphasize the menu, EFalse otherwise.
	*/
	void SetEmphasis( CCoeControl* aMenuControl, TBool aEmphasis ); 
	
public: // from MEikCommandObserver

   /**
    * Processes user commands.
	*
	* Derived classes must provide an implementation of this function which responds 
	* to user commands appropriately based on a user-defined ID for the command.
	*
	* @param aCommandId ID of the command to respond to.
	*/
	void ProcessCommandL( TInt aCommandId );
	
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
     * Tests the functions in CAiwServiceHandler class.
     */
    void TestServiceHandlerFunctions();
    
    /**
     * Tests the functions in CAiwCriteriaItem class.
     */
    void TestCriteriaItemFunctions();
    
    /**
     * Tests the functions in TAiwGenericParam class.
     */
    void TestGenericParamFunctions();
    
    /**
     * Tests the functions in CAiwGenericParamList class.
     */
    void TestGenericParamListFunctions();
    
    /**
     * Tests the functions in TAiwVariant class.
     */
    void TestVariantFunctions();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestServiceHandlerCase( CBCTestServiceHandlerContainer* aContainer );
    
    /**
     * Symbian 2nd constructor
     */
    void ConstructL();
    
private: // data
   
    /**
     * Pointer to container.
     * Not owned
     */
    CBCTestServiceHandlerContainer* iContainer;
        
    /**
     * Pointer to an AIW criteria item instance.
     * Owned
     */
    CAiwCriteriaItem* iCriteria;
    };

#endif // BCTEST_SERVICEHANDLERCASE_H