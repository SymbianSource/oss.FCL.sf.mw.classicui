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









#ifndef BCTEST_SERVERAPPCASE_H
#define BCTEST_SERVERAPPCASE_H

#include "bctestcase.h"
#include <aknserverapp.h>
#include <aknwseventobserver.h>

//TUid Kmysimpleserver = { 0x06C22C0C	};

class CBCTestServerappContainer;
class CCoeControl;
class MAknWsEventObserver;

class CSubMonitor: public CBase,
			 	    public MAknWsEventObserver
  {
   public:
  	static CSubMonitor* NewL();

    ~CSubMonitor();

    /**
    * Two-phased constructor.
    */
	void ConstructL();

   IMPORT_C void HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination);
  };

/**
* test case for various list classes
*/
class CBCTestServerappCase: public CBCTestCase
    {
public: // constructor and destructor
    
    /**
    * Symbian 2nd static constructor
    */
    static CBCTestServerappCase* NewL( CBCTestServerappContainer* aContainer );
    
    /**
    * Destructor
    */
    virtual ~CBCTestServerappCase();
    
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
     * Test functions
     */
    void TestFunctionL();
    void TestFunctionOneL();
    void TestFunctionTwoL();
    void TestFunctionThreeL();
    void TestFunctionFourL();
        
private: // constructor
    
    /**
     * C++ default constructor
     */
    CBCTestServerappCase( CBCTestServerappContainer* aContainer );
    
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
    CBCTestServerappContainer* iContainer;
    
    };
    
class CAknAppServiceDrv:public CAknAppServiceBase, MAknServerAppExitObserver
	{
public:
    CAknAppServiceDrv()
    {
    	
    }
    ~CAknAppServiceDrv()
    {
    	
    }
    void CreateL();
    void ServiceL(const RMessage2& aMessage);
    void ServiceError(const RMessage2& aMessage,TInt aError);
    void HandleServerAppExit(TInt aReason);
	};

/*class CMySimpleServer:public CAknAppServer
{
public:
	CApaAppServiceBase* CreateServiceL(TUid aServiceType) const
	{
		if (aServiceType == Kmysimpleserver )
		{
			return new(ELeave)CAknAppServiceDrv();
		}
		else
		{
			return CAknAppServer::CreateServiceL(aServiceType);
		}
	}
};

class REmbedderClient:public RAknAppServiceBase
{
public:
	TUid ServiceUid() const
	{
		return Kmysimpleserver;
	}
	virtual ~REmbedderClient()
	{
		Close();
	}
};*/

#endif // BCTEST_SERVERAPPCASE_H