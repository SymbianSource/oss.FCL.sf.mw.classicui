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


#include "T_FocusStep.h"

/**
   Destructor
 */
CSimpleFocusControl::~CSimpleFocusControl()
	{
	}


/**
   Auxiliary function for all Test Cases
  
   This method creates the user interface control on which tests are carried
   out.
   
 */
void CSimpleFocusControl::ConstructL()
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
TKeyResponse CSimpleFocusControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode aType)
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
void CSimpleFocusAppUi::ConstructL()
    {
    //BaseConstructL(ENoAppResourceFile);
	CTestCoeAppUi::ConstructL();
    
	iSimpleFocusControl=new(ELeave) CSimpleFocusControl;
    iSimpleFocusControl->ConstructL();
    AddToStackL(iSimpleFocusControl);
 
	AutoTestManager().StartAutoTest();
   }

CSimpleFocusAppUi::~CSimpleFocusAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iSimpleFocusControl);
    delete iSimpleFocusControl;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates border
   drawing tests.
   
 */
void CSimpleFocusAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
		case 1:	
			{
			INFO_PRINTF1(_L("Test focus"));
			TBool isNonFocusing = iSimpleFocusControl->IsNonFocusing();
			TEST(!isNonFocusing);
			if (isNonFocusing)
				{
				INFO_PRINTF1(_L("IsNonFocusing() returned ETrue, EFalse expected"));
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

//----------

CTestFocusStep::CTestFocusStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestFocusStep);
	}
	
	

CTestFocusStep::~CTestFocusStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestFocusStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CSimpleFocusAppUi* appUi= new (ELeave) CSimpleFocusAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the test step's user interface object and
   launches the test step.
   
 */
TVerdict CTestFocusStep::doTestStepL() // main function called by E32
	{
	PreallocateHALBuffer();
	__UHEAP_MARK;

	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();

	REComSession::FinalClose();	
	__UHEAP_MARKEND;

	return TestStepResult();
	}





