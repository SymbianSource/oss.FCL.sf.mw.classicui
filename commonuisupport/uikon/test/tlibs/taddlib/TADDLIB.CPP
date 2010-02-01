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
// Test adds a control factory function and resource file to the application.\n  
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
*/

#include <basched.h>
#include <eikenv.h>
#include <eikappui.h>
#include <techview/eikon.hrh>
#include <eikapp.h>
#include <eikdoc.h>
#include <techview/eiklabel.h>
#include <eikfctry.h>
#include <coecntrl.h>
#include <barsread.h>
#include "TADDLIB.HRH"
#include <external.rsg>
#include <techview/eiktbar.h>
#include <techview/eikmenub.h>
#include <eikspane.h>
#include <ecom/ecom.h>


_LIT(KTAddLibResourceFilePath, "");

#include "Taddlib.h"

/**
   Auxiliary function for refreshing Label
  
   This method is an override from CEikLabel. It draws the label control.
   
 */ 
void CTestLabel::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	gc.SetPenColor(KRgbBlack);
	CEikLabel::Draw(aRect);
	}


CTestContainer::CTestContainer(CTestAppUi* aAppUi)
	: iResourceFile(_L("z:\\system\\test\\taddlib\\external.rsc")),
	iAppUi(aAppUi)
/**
   Constructor
 */
	{
	}

void CTestContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	Window().SetBackgroundColor(KRgbWhite);
 	SetRect(aRect);

	ActivateL();
    }

/**
   @SYMTestCaseID UIF-AddLib-AddLibraryL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikonEnv::AddLibraryL() method.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test case tests whether the specified control factory
   function and resource file are added to their respective lists by
   CEikonEnv::AddLibraryL(). The method verifies this by checking whether
   CEikonEnv::AddLibraryL() returns a non-zero value for the resource file
   offset indicating successful addition.\n
   API Calls:\n	
   TInt CEikonEnv::AddLibraryL(TCreateByTypeFunction aControlFactory, TFileName* aResourceFile)\n
  
   @SYMTestExpectedResults On successful addition of the specified control
   factory function and resource file, CEikonEnv::AddLibraryL() should
   return a non-zero value.
   
 */
void CTestContainer::AddLibraryL()
    {
	if(iResFileOffset)
		{
		iEikonEnv->InfoMsg(_L("Library already added!"));
		return;
		}
	iAppUi->INFO_PRINTF1(_L("ADD LOCAL CONTROL FACTORY AND RESOURCE FILE TO THE EIKON ENVIRONMENT"));
	iResFileOffset = iEikonEnv->AddLibraryL(CreateByTypeL, &iResourceFile);
	iAppUi->TEST(iResFileOffset >= 0);
	iEikonEnv->InfoMsg(_L("Library added."));
    }
    
    
/**
   @SYMTestCaseID UIF-AddLib_RemoveLibrary
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikonEnv::RemoveLibrary() method.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test case tests whether the specified control factory
   function and the resource file identified by the resource file offset
   specified as parameters are removed from their respective lists by
   CEikonEnv::RemoveLibrary().\n
   API Calls:\n	
   void CEikonEnv::RemoveLibrary(TCreateByTypeFunction aControlFactory, TInt aResourceFileOffset)\n
  
   @SYMTestExpectedResults The test removes the control factory function
   and the resource file which was previously added.
   
 */
void CTestContainer::RemoveLibrary()
    {
	if(!iResFileOffset)
		{
		iEikonEnv->InfoMsg(_L("No library to remove."));
		return;
		}
	iAppUi->INFO_PRINTF1(_L("FREE UP THE CONTROL FACTORY AND RESOURCE FILE MEMORY FROM EIKENV"));
	iEikonEnv->RemoveLibrary(CreateByTypeL, iResFileOffset);
	delete iLabel;
	iLabel = NULL;
	iResFileOffset = 0;
	iEikonEnv->InfoMsg(_L("Library removed."));
	DrawNow();
    }

/**
   Auxiliary function for TestCaseID T-AddLib-RunL
  
   This method is used by CTestContainer::RunL() to create the applications
   control. This method calls the control factory function
   CTestContainer::CreateByTypeL() to create the control. The method then uses
   Cone to construct the control by reading information from the resource
   file that was added.
   
 */
TBool CTestContainer::CreateControlL()
	{
	TBool ret = EFalse;
	if(!iLabel)
		{
		iAppUi->INFO_PRINTF1(_L("ASK THE EIKON CONTROL FACTORY TO CREATE THIS APPLICATION'S CONTROL\n"));
		SEikControlInfo controlInfo = EikControlFactory::CreateByTypeL(ECtTestLabel);
		if(controlInfo.iControl)
			{
			iAppUi->INFO_PRINTF1(_L("Control successfully created\n"));
			iLabel = STATIC_CAST(CTestLabel*, controlInfo.iControl);
			iAppUi -> TEST(iLabel != NULL);

			iLabel->SetContainerWindowL(*this);
			iLabel->SetControlContext(iLabel);
			
			iAppUi->INFO_PRINTF1(_L("ASK CONE TO CONSTRUCT THIS APPLICATION'S CONTROL FROM THE LOCAL RESOURCE FILE\n"));

			TResourceReader reader;
			iCoeEnv->CreateResourceReaderLC(reader,R_TESTADDLIB_LABEL);
			iLabel->ConstructFromResourceL(reader);
			CleanupStack::PopAndDestroy();
			iLabel->SetRect(TRect(TPoint(260,110),iLabel->MinimumSize()));
			iLabel->ActivateL();
			ret = ETrue;
			}
		}
	// Control already created
	else ret = ETrue;
	
	return ret;
	}

/**
   @SYMTestCaseID UIF-AddLib-RunL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests Creation of Applications Control.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test initiates creation of applications control and
   draws it on the container. \n
   
   @SYMTestExpectedResults The test should create controls by reading
   information from the resource file and should display them.
  
 */
void CTestContainer::RunL()
    {
	if(CreateControlL())
		DrawNow();
	else iEikonEnv->InfoMsg(_L("Must add library first!"));
    }


CTestContainer::~CTestContainer()
/**
   Destructor
 */
    {
	delete iLabel;
    }

/**
   Auxiliary function for TestCaseID T-AddLib-RunL
  
   This method is an override from CCoeControl. It returns the number of
   controls contained in a compound control.
   
 */
TInt CTestContainer::CountComponentControls() const
    {
	if(iLabel)
		return 1;
	else
		return 0;
    }

/**
   Auxiliary function for TestCaseID T-AddLib-RunL
  
   This method is an override from CCoeControl. It returns the label component
   from the container control. 
   
 */  
CCoeControl* CTestContainer::ComponentControl(TInt aIndex) const
    {			 
	switch (aIndex)
		{
		case 0:
		default:
			return iLabel;
		}
	}

/**
   Auxiliary function for refreshing Container
  
   This method is an override from CCoeControl. It draws the container control.
   
 */ 
void CTestContainer::Draw(const TRect& aRect) const
    {
   	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbGray);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbWhite);
	gc.DrawRect(aRect);
    }

/**
   Auxiliary function for TestCaseID T-AddLib-RunL
  
   This method is the control factory function for this Application.
   It is called by CTestContainer::CreateControlL() to create label control.
   The method returns the structure SEikControlInfo which contains the
   control information for the control.
   
 */  
SEikControlInfo CTestContainer::CreateByTypeL(TInt aControlType)
	{	
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case ECtTestLabel:
		controlInfo.iControl = new(ELeave) CTestLabel;
		break;
		}
	return controlInfo;
	}



CTestAddLibraryAppUi::CTestAddLibraryAppUi(CTmsTestStep*		aStep, const TDesC& aRes) :
	CTestAppUi(	aStep, aRes)
/**
   Constructor
 */
	{
	}


CTestAddLibraryAppUi::~CTestAddLibraryAppUi()
/**
   Destructor
 */
	{
	RemoveFromStack(iContainer);
	delete iContainer;
	
	}


/**
   Auxiliary function for all Test Cases
   
   The method creates a container and sets active object with lowest
   priority for running test in auto mode.
  
 */
void CTestAddLibraryAppUi::ConstructL()
	{
	CTestAppUi::ConstructL();
	
	TRect boundingRect=ClientRect(); // make toolband stretch to the screen width by default
    iContainer=new(ELeave) CTestContainer(this);
	
	ReduceRect(boundingRect);
	iContainer->ConstructL(boundingRect);
    AddToStackL(iContainer);

	AutoTestManager().StartAutoTest();
	}


/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   to be performed by calling CTestAddLibraryAppUi::HandleCommandL().
   
 */
void CTestAddLibraryAppUi::RunTestStepL(TInt aStep)
	{
	TInt theProgramState = 0;

//#ifdef FORCE_AUTO
	User::After(TTimeIntervalMicroSeconds32(1000000));
//#endif	
	switch (aStep)
		{
	case 1:
		INFO_PRINTF1(_L("Adding library\n"));
		SetTestStepID(_L("UIF-AddLib-AddLibraryL"));
		theProgramState = ECmdAddLibrary;
		RecordTestResultL();
		break;
	case 2:
		INFO_PRINTF1(_L("Run library\n"));
		SetTestStepID(_L("UIF-AddLib-RunL"));
		theProgramState = ECmdRun;
		RecordTestResultL();
		break;
	case 3:
		INFO_PRINTF1(_L("Removing library\n"));
		SetTestStepID(_L("UIF-AddLib_RemoveLibrary"));
		theProgramState = ECmdRemoveLibrary;
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	case 5:
		theProgramState = EEikCmdExit;
		break;
		}
	HandleCommandL(theProgramState);							
	}



/**
   Auxiliary function for all Test Cases
  
   This method is called by CTestAddLibraryAppUi::RunTestStepL() to initiate
   the tests.
   
 */
void CTestAddLibraryAppUi::HandleCommandL(TInt aCommand)
	{

	switch (aCommand)
		{
	case ECmdAddLibrary:
		if(iContainer)
			{
			iContainer->AddLibraryL();
			}
		break;
	case ECmdRemoveLibrary:
		if(iContainer)
			{
			iContainer->RemoveLibrary();
			}
		break;
	case ECmdRun:
		if(iContainer)
			{
			iContainer->RunL();
			}
		break;
	case EEikCmdExit:
		if(iContainer)
			{
			iContainer->RemoveLibrary();
			iCoeEnv->Flush();
			}
		Exit();
		break;
		}
	}


//----------

CTestAddLibraryStep::CTestAddLibraryStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestAddLibraryStep);
	}

CTestAddLibraryStep::~CTestAddLibraryStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestAddLibraryStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CTestAppUi* appUi= new (ELeave) CTestAddLibraryAppUi(this,KTAddLibResourceFilePath);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object to
   launch the application which will initiate the tests.
   
 */
TVerdict CTestAddLibraryStep::doTestStepL() // main function called by E32
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

