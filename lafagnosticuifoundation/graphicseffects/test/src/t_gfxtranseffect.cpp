// Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// t_gfxtransdefect.cpp
// Test code for defect INC109405: Problem with sequential Gfxtranseffect registrations
// 
//

/**
 @file 
 @test
 @internalComponent - Internal Symbian test code
*/

#include <coecntrl.h>
#include <coeutils.h>
#include <eikenv.h>
#include <eikappui.h>
#include <eikdef.h>
#include <eikdoc.h>
#include <eikapp.h>
#include <gfxtranseffect/gfxtranseffect.h>

#include "t_gfxtranseffect.h"

/**
 *  Destructor
 */
CSimpleGfxTransControl::~CSimpleGfxTransControl()
	{
	// Empty
	}


/**
 * Auxiliary function for all Test Cases
 *
 * This method creates the user interface control on which tests are carried
 * out. 
 */
void CSimpleGfxTransControl::ConstructL()
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    ActivateL();
	}


/**
 * Auxilliary function for all Test Cases
 * 
 * This method is an override from CCoeControl. It is used to handle key
 * events for the control. 
 */
TKeyResponse CSimpleGfxTransControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode aType)
    {
    if (aType!=EEventKey)
        return(EKeyWasNotConsumed);
        
    return(EKeyWasConsumed);
    }

/**
 * Auxiliary function for all Test Cases
 * 
 * This method prepares the test step's user interface and prepares it
 * to start the tests. 
 */
void CSimpleGfxTransAppUi::ConstructL()
    {
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
   }

/**
 *  Destructor
 */
CSimpleGfxTransAppUi::~CSimpleGfxTransAppUi()
	{
    //Empty
	}

/**
@SYMTestCaseID UIF-gfxtranseffect-RunTestStepL

@SYMDEF INC109405: Problem with sequential Gfxtranseffect registrations

@SYMTestCaseDesc Testing for Register / Deregister method implementation  to check
				whether ,an object to appear deregistered even though register would've just
				been called for it.

@SYMTestPriority	Normal

@SYMTestStatus	Implemented

@SYMTestActions	This tests GfxTransEffect features.
				The sequence is as follows:
					1.- Create a control to perform transition on.
					2.- Register this control with UID set to 0.
					3.- Check if control is registered within transition.
					4.- Prepare transition for currect control bystarting a transition which runs endlessly.
					5.- While performing a transition deregister the control and check its status.
					6.-	Register this control once again and test its status.

@SYMTestExpectedResults  isRegistered value set to ETrue
*/

void CSimpleGfxTransAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
		case 1:
			{
			/**
			@SYMDEF DEF133206 DEF135332
			
			@SYMTestCaseID	UIF-APPFWK-GFXTRANSEFFECT-0001
			
			@SYMTestCaseDesc Testing Deregister does not create transeffects
							
			@SYMTestPriority	Normal
			
			@SYMTestStatus	Implemented
			
			@SYMTestActions	Get allocated heap size
							Call Deregister
							Get new allocated heap size
			
			@SYMTestExpectedResults  
					After a deregister there should be the same or less memory
					allocated on the heap.
					NOTE: This test must be run first otherwise it cannot pick up 
					a regression.
			*/
			SetTestStepID(_L("UIF-APPFWK-GFXTRANSEFFECT-0001"));
			CSimpleGfxTransControl* control1 = new(ELeave) CSimpleGfxTransControl;
			if (!control1)
				{
				TEST(EFalse);
				break;
				}
			CleanupStack::PushL(control1);
			control1->ConstructL();
			
			//must be first GfxTransEffect calls in test suite otherwise memory will already 
			//have been allocated.
			//Deregister
			TInt heapSizeBefore = 0;
			TInt cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::Deregister(control1);	
			TInt heapSizeAfter = 0;
			TInt cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			//IsRegistered
			cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::IsRegistered(control1);	//must be first GfxTransEffect calls in test suite.
			cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			//Abort
			cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::Abort(control1);	//must be first GfxTransEffect calls in test suite.
			cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			//GetHints
			cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::GetHints(control1);	//must be first GfxTransEffect calls in test suite.
			cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			//Disable
			cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::Disable();	//must be first GfxTransEffect calls in test suite.
			cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			//AbortFullScreen
			cellsBefore = User::AllocSize(heapSizeBefore);
			GfxTransEffect::AbortFullScreen();	//must be first GfxTransEffect calls in test suite.
			cellsAfter = User::AllocSize(heapSizeAfter);
			TEST(heapSizeBefore >= heapSizeAfter);
			TEST(cellsBefore >= cellsAfter);
			
			CleanupStack::PopAndDestroy(control1);
			RecordTestResultL();
			}
			break;
        case 2:
            {
			/**
			@SYMDEF INC109405: Problem with sequential Gfxtranseffect registrations
			
			@SYMTestCaseID	UIF-APPFWK-GFXTRANSEFFECT-0002
			
			@SYMTestCaseDesc Testing for Register / Deregister method implementation  to check 
						whether ,an object to appear deregistered even though register would've just
						been called for it.
						
			@SYMTestPriority	Normal
			
			@SYMTestStatus	Implemented
			
			@SYMTestActions	This tests GfxTransEffect features.
						The sequence is as follows:
							1.- Create a control to perform transition on.
							2.- Register this control with UID set to 0.
							3.- Check if control is registered within transition.
							4.- Prepare transition for currect control bystarting a transition which runs endlessly. 
							5.- While performing a transition deregister the control and check its status.
							6.-	Register this control once again and test its status.
			
			@SYMTestExpectedResults  isRegistered value set to ETrue
			*/
            SetTestStepID(_L("UIF-APPFWK-GFXTRANSEFFECT-0002"));
			CSimpleGfxTransControl* control2 = new(ELeave) CSimpleGfxTransControl;
			if (!control2)
				{
				TEST(EFalse);
				break;
				}
			CleanupStack::PushL(control2);
			control2->ConstructL();		 
			TUid id = {0};
			
			GfxTransEffect::Register(control2, id); 
			TBool isRegistered = GfxTransEffect::IsRegistered(control2);
			TEST(isRegistered);
			 
			GfxTransEffect::Begin(control2, GfxTransEffect::ELoseFocus);
			GfxTransEffect::End(control2); 
			 
			GfxTransEffect::Deregister(control2);
			isRegistered = GfxTransEffect::IsRegistered(control2);
			TEST(!isRegistered);
			
			GfxTransEffect::Register(control2, id);
			isRegistered = GfxTransEffect::IsRegistered(control2);
			TEST(isRegistered);
			
			CleanupStack::PopAndDestroy(control2);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			}
			break;
		case 3:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		default:
			break;
		}
	}

/**
 *  Constructor
 */
CTestGfxTransEffect::CTestGfxTransEffect()
	{
	SetTestStepName(KTestGfxTransEffect);
	}
	
/**
 *  Destructor
 */
CTestGfxTransEffect::~CTestGfxTransEffect()
	{
	//Empty
	}

/**
 *  Auxiliary function for all Test Cases
 * 
 *  The method creates & sets the application's user interface object.
 *  
 */
void CTestGfxTransEffect::ConstructAppL(CEikonEnv* aCoe)
    {
	aCoe->ConstructL();

	CSimpleGfxTransAppUi* appUi= new (ELeave) CSimpleGfxTransAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
 *  Auxiliary function for all Test Cases
 * 
 *  The method creates & sets the test step's user interface object and
 *  launches the test step.
 *  
 */
TVerdict CTestGfxTransEffect::doTestStepL() // main function called by E32
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
