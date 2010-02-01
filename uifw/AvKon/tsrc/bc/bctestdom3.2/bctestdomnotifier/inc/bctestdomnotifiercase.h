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


#ifndef C_BCDOMIANTESTNOTIFIERCASE_H
#define C_BCDOMIANTESTNOTIFIERCASE_H

#include <aknsignal.h>
#include <AknNotiferAppServerApplication.h>
#include <AknNotifierAppServer.h>
#include <AknMediatorFacade.h>
#include <AknNotifierWrapper.h>

#include "bctestcase.h"
#include "bctestdomnotifierapp.h"

class CBCDomainTestNotifierContainer;
class CCoeControl;
class TAknTextComponentLayout;
class MAknNotifierCustomSecurityCheck;
/**
* CBCNotifierAppServer class.
*/

class CBCNotifierAppServer: public CAknNotifierAppServerApplication
    {
public:
//FROM CAknNotierAppServerApplication
    TUid AppDllUid() const
    {
        return KUidBCDomainTestNotifier;
    }    
    };

/**
* CBCSecurityCheck class.
*/

class CBCSecurityCheck : public MAknNotifierCustomSecurityCheck
    {	
public:
//from MAknNotifierCustomSecurityCheck
    void Release()
    {
    }
    
    void CustomSecurityCheckL(const RMessagePtr2&)
    {    	
    }
    };

class CBCserverAppExitObserver: public MAknServerAppExitObserver
    {
	void HandleServerAppExit( TInt )
	{		
	}
    };

/**
* CBCNotiAppServerUi class.
*/

class CBCNotiAppServerUi: public CAknNotifierAppServerAppUi
    {
    friend class CBCDomainTestNotifierCase;
public:
/**
* default Constructor
*/
    CBCNotiAppServerUi():
    CAknNotifierAppServerAppUi()
    {      
    }
    
    void ConstructL()
    {
        CAknNotifierAppServerAppUi::ConstructL();
    }
     
    ~CBCNotiAppServerUi()
    {
        CAknNotifierAppServerAppUi::~CAknNotifierAppServerAppUi();
    }
    };

/**
* CBCSignalPane class.
*/ 
class CBCSignalPane:public CAknSignalPane
    {
    friend class CBCDomainTestNotifierCase;
public:
    void HandlePointerEventL( TPointerEvent const&)
    {    
    }
    
    };
/**
* test case for various classes
*/
class CBCDomainTestNotifierCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCDomainTestNotifierCase* NewL( CBCDomainTestNotifierContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCDomainTestNotifierCase();
    
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
     * Test FunctionL
     */
    void TestFunctionL();
    
    /**
     * Test TestSignalL
     */
    void TestSignalL();
    
    /**
     * Test TestOtherL
     */
    void TestOtherL();
    
    /**
     * Test TestPhoneL
     */
    void TestPhoneL();
    
    /**
     * Test TestFormatL
     */
    void TestFormatL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCDomainTestNotifierCase( CBCDomainTestNotifierContainer* aContainer );
    
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
    CBCDomainTestNotifierContainer* iContainer;
    
    };

#endif // C_BCDomainTestNotifierCASE_H 

