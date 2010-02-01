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
#include "TLOADDLL.H"
#include <external.rsg>
#include <techview/eiktbar.h>
#include <techview/eikmenub.h>
#include <ecom/ecom.h>


#include "Tautolib.h"


_LIT(KTAutoLibResourceFilePath, "");


//#define FORCE_AUTO


//!  A CTestAutoContainer  test control class. 
/**
 The class represents the test Container control.
*/
class CTestAutoContainer : public CCoeControl
    {
public:
	CTestAutoContainer(CTestAppUi*				aApp);
    ~CTestAutoContainer();
    void ConstructL(const TRect& aRect);
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
private: 
    void Draw(const TRect& aRect) const;
private:
	CTestEikDllLoadedLabel* iLabel2;
	CTestAppUi*				iApp;
    };

CTestAutoContainer::CTestAutoContainer(CTestAppUi*	aApp) :
		iApp(aApp)
/**
   Constructor
 */
	{

	}

/**
   Auxiliary function for Container
  
   This method is the second phase constructor for CTestAutoContainer.
   It is used to create the applications control. This method calls the control
   factory function to create the control. The method then uses Cone to
   construct the control by reading information from the resource file that was
   added.
   
 */
void CTestAutoContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	Window().SetBackgroundColor(KRgbWhite);
	iApp->INFO_PRINTF1(_L("ASKING THE EIKON CONTROL FACTORY TO CREATE THIS APPLICATION'S CONTROL"));	

	
	// For ECom Plugin DLL
	iApp->INFO_PRINTF1(_L("Creating control from ECom plugin DLL"));	
	SEikControlInfo control2Info = EikControlFactory::CreateByTypeL(CTestEikDllLoadedLabel::ECtTestEikEComDllLoadedLabel);
	iLabel2 = STATIC_CAST(CTestEikDllLoadedLabel*, control2Info.iControl);
	iApp->TEST(iLabel2 != NULL);
	if (iLabel2)
		{
		iLabel2->SetContainerWindowL(*this);
		iLabel2->SetControlContext(iLabel2);

		iApp->INFO_PRINTF1(_L("ASKING CONE TO CONSTRUCT THIS APPLICATION'S CONTROL FROM THE LOCAL RESOURCE FILE"));	
		TResourceReader reader2;
		iCoeEnv->CreateResourceReaderLC(reader2,R_TESTAUTOLIB_LABEL);
		iLabel2->ConstructFromResourceL(reader2);
		CleanupStack::PopAndDestroy();// resource readers
		iLabel2->SetRect(TRect(TPoint(260,130),iLabel2->MinimumSize()));
		iLabel2->ActivateL();
		}
	else
		{
		iApp->INFO_PRINTF1(_L("Error may be related to binaries in TLOADDLLV2.MMP"));
		}
	
	if (iLabel2)
		{
		SetRect(aRect);
    	ActivateL();
		}
	}

CTestAutoContainer::~CTestAutoContainer()
/**
   Destructor
 */
    {
	delete iLabel2;
    }

/**
   Auxiliary function for Container
  
   This method is an override from CCoeControl. It returns the number of
   controls contained in a compound control.
   
 */
TInt CTestAutoContainer::CountComponentControls() const
    {
	return(1);
    }

/**
   Auxiliary function for Container
  
   This method is an override from CCoeControl. It returns the label component
   from the container control. 
   
 */
CCoeControl* CTestAutoContainer::ComponentControl(TInt aIndex) const
    {			 
	switch (aIndex)
		{
		case 0:
		default:
			{
			return iLabel2;
			}
		}
	}


/**
   Auxiliary function for refreshing Container
  
   This method is an override from CCoeControl. It draws the container control.
   
 */
void CTestAutoContainer::Draw(const TRect& aRect) const
    {
	CWindowGc& gc=SystemGc();
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(KRgbWhite);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(KRgbWhite);
	gc.DrawRect(aRect);
    }


//!  A CTestAutoAddLibraryAppUi test class. 
/**
 The class handles work with resources.
*/
class CTestAutoAddLibraryAppUi : public CTestAppUi
	{
public:
	CTestAutoAddLibraryAppUi(CTmsTestStep*		aStep) :
	  CTestAppUi(aStep, KTAutoLibResourceFilePath) {} //, TESTAUTOLIB_HOT_KEYS, TESTAUTOLIB_MENU_BAR){}
	~CTestAutoAddLibraryAppUi();
	void ConstructL();
	virtual void HandleCommandL(TInt aCommand);

	//from CCoeAppUi
	void PrepareToExit();
	
private:
	void RunTestStepL(TInt aNumStep);

	CTestAutoContainer* iContainer;
	};


CTestAutoAddLibraryAppUi::~CTestAutoAddLibraryAppUi()
/**
   Destructor
 */
	{
	}

void CTestAutoAddLibraryAppUi::PrepareToExit()
	{
	// Need to delete iContainer here rather than in the destructor because iContainer 
	// owns a control (CTestEikDllLoadedLabel) which is defined in an ECom DLL. 
	// Because this app is the only user of that Ecom DLL, it will be expunged from RAM
	// (when run from an On-Demand-Paging ROM) before the AppUi is deleted.
	// See DEF112572
	RemoveFromStack(iContainer);
	delete iContainer;
	}


/**
   Auxiliary function for all Test Cases
  
   The method creates a container and sets active object with lowest
   priority for running test in auto mode.
  
 */
void CTestAutoAddLibraryAppUi::ConstructL()
	{
	//BaseConstructL();
    CTestAppUi::ConstructL();

	TRect boundingRect=ClientRect(); // make toolband stretch to the screen width by default
	//menu
	iContainer=new(ELeave) CTestAutoContainer(this);
	ReduceRect(boundingRect);
    iContainer->ConstructL(boundingRect);
    AddToStackL(iContainer);

	AutoTestManager().StartAutoTest();

	}
	

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   to be performed.
   
 */
void CTestAutoAddLibraryAppUi::RunTestStepL(TInt aNumStep)
	{
	
	User::After(TTimeIntervalMicroSeconds32(1000000));
		switch(aNumStep)
			{
			case 1:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
			}
	}


/**
   Auxiliary function for all Test Cases
  
   This method is called by CTestAutoAddLibraryAppUi::RunTestStepL() to initiate
   the tests.
   
 */
void CTestAutoAddLibraryAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case EEikCmdExit:
		iCoeEnv->Flush();
		Exit();
		break;
		}
	}



//----------

CTestAutoLibStep::CTestAutoLibStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestAutoLibStep);
	}

CTestAutoLibStep::~CTestAutoLibStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestAutoLibStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CTestAppUi* appUi= new (ELeave) CTestAutoAddLibraryAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object to
   launch the application which will initiate the tests.
   
 */
TVerdict CTestAutoLibStep::doTestStepL() // main function called by E32
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




