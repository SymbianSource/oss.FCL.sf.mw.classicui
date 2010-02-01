// Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Tests border drawing using border colour & style.\n
// 
//

/**
 @file 
 @internalComponent - Internal Symbian test code
*/
#include <e32keys.h>
#include <basched.h>
#include <gdi.h>
#include <gulutil.h>
#include <gulbordr.h>
#include <coecntrl.h>
#include <coeutils.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdef.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <ecom/ecom.h>

#include "appfwk_test_utils.h"
#include "T_NonFocusStep.h"

/**
   Destructor
 */
CSimpleNonFocusControl::~CSimpleNonFocusControl()
	{
	}


/**
   Auxiliary function for all Test Cases
  
   This method creates the user interface control on which tests are carried
   out.
   
 */
void CSimpleNonFocusControl::ConstructL()
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    ActivateL();
	}


/**
   Auxilliary function for all Test Cases
  
   This method is an override from CCoeControl. It is used to handle key
   events for the control.
  
 */
TKeyResponse CSimpleNonFocusControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode aType)
    {
    if (aType!=EEventKey)
        return(EKeyWasNotConsumed);
        
    return(EKeyWasConsumed);
    }

/**
   Auxiliary function for all Test Cases
  
   This method prepares the test step's user interface and prepares it
   to start the tests. As part of user interface it creates a control
   on which the tests are carried out.
   
 */
void CSimpleNonFocusAppUi::ConstructL()
    {
    //BaseConstructL(ENoAppResourceFile);
	CTestCoeAppUi::ConstructL();
    
	iSimpleNonFocusControl=new(ELeave) CSimpleNonFocusControl;
    iSimpleNonFocusControl->ConstructL();
    AddToStackL(iSimpleNonFocusControl);
 
	AutoTestManager().StartAutoTest();
   }

CSimpleNonFocusAppUi::~CSimpleNonFocusAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iSimpleNonFocusControl);
    delete iSimpleNonFocusControl;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates border
   drawing tests.
   
 */
void CSimpleNonFocusAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
		case 1:
			{
			INFO_PRINTF1(_L("Test non focus"));
			TBool isNonFocusing = iSimpleNonFocusControl->IsNonFocusing();
			TEST(isNonFocusing);
			if (!isNonFocusing)
				{
				INFO_PRINTF1(_L("IsNonFocusing() returned EFalse, ETrue expected"));
				}			
			}
			break;
		case 2:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		default:
			break;
		}
	}

/**
   Constructor
 */
CTestNonFocusStep::CTestNonFocusStep()
	{  
	SetTestStepName(KTestNonFocusStep);	
	}

/**
   Destructor
 */	
CTestNonFocusStep::~CTestNonFocusStep()
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestNonFocusStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CSimpleNonFocusAppUi* appUi= new (ELeave) CSimpleNonFocusAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
  Auxiliary function for all Test Cases
  
  The method creates & sets the test step's user interface object and
  launches the test step.
  
 */
TVerdict CTestNonFocusStep::doTestStepL() // main function called by E32
	{
  	PreallocateHALBuffer();
	__UHEAP_MARK;
	
	// Before creating the CEikonEnv we must create C:\focus.txt.
	// The presence of this file will modify the behaviour of 
	// staticsettingsinit
	RSmlTestUtils utils;
	User::LeaveIfError(utils.Connect());
	CleanupClosePushL(utils);
	_LIT(KFile, "c:\\focus.txt");
	utils.CreateFileL(KFile);
	    
	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	
	utils.DeleteFileL(KFile);
	CleanupStack::PopAndDestroy(&utils);

	REComSession::FinalClose();
	
		
	__UHEAP_MARKEND;
	

	return TestStepResult();
	}





