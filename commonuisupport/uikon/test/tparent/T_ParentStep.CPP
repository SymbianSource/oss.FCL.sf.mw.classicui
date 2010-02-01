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


#include "T_ParentStep.h"
#include "appfwk_test_utils.h"

//! Total Size of the Window in which controls are spaced.\n
#define KViewRect TRect(TPoint(0,0), TPoint(400,200))

/**
   Destructor
 */
CSimpleParentControl::~CSimpleParentControl()
	{
	}

/**
  Static function used for CSimpleParentControl class instantiation.\n
  The function instantiates an CSimpleParentControl object.\n
  Invokes second phase constructor of CSimpleParentControl class passing pointers to
  Layout manager, container object as arguments.\n
*/
CSimpleParentControl* CSimpleParentControl::NewL(CCoeControl& aContainer, const TRect& /*aRect*/)
	{
	CSimpleParentControl* self = new(ELeave) CSimpleParentControl();
	CleanupStack::PushL(self);
	self->ConstructL(aContainer);
	CleanupStack::Pop();
	return self;
	}
	
/**
   Auxiliary function for all Test Cases
  
   This method creates the user interface control on which tests are carried
   out.
   
 */
void CSimpleParentControl::ConstructL(CCoeControl& aContainer)
    {
    CreateWindowL();
    SetExtentToWholeScreen();
    SetContainerWindowL(aContainer);
    ActivateL();
	}


/**
   Auxilliary function for all Test Cases
  
   This method is an override from CCoeControl. It is used to handle key
   events for the control.
  
 */
TKeyResponse CSimpleParentControl::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode aType)
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
void CSimpleParentAppUi::ConstructL()
    {
	CTestCoeAppUi::ConstructL();

    iParentAppView = CParentTestAppView::NewL(KViewRect);
	AutoTestManager().StartAutoTest();
   }

CSimpleParentAppUi::~CSimpleParentAppUi()
/**
   Destructor
 */
	{
  	delete iParentAppView;
	}

/**
   Auxiliary function for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates border
   drawing tests.
   
 */
void CSimpleParentAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
		case 1:	
			{
			INFO_PRINTF1(_L("Test Parent - does the control have the view as its parent?"));
			
			// Get the control on the appview
			CCoeControl *control = iParentAppView->GetControl();
			
			if (control == NULL)
				{
				TEST(control != NULL); // generates a fail automatically
				INFO_PRINTF1(_L("Could not get control from appview - test failed"));
				break;
				}
				
			// Get the parent of that control
			CCoeControl *parent = control->Parent();
			
			// Check that there is a parent to begin with
			if (parent==NULL)
				{
				TEST(parent != NULL); // generates a fail automatically
				INFO_PRINTF1(_L("Control does not have a parent - test failed"));
				break;
				}
				
			// Check that the parent is the same as the view
			TEST(parent == iParentAppView);
				
			if (parent != iParentAppView)
				{
				INFO_PRINTF1(_L("View is not parent of Control - test failed"));
				}
				else
				{
				INFO_PRINTF1(_L("View is parent of Control - test PASSED"));
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

CTestParentStep::CTestParentStep()
/**
   Constructor
 */
	{
	SetTestStepName(KTestParentStep);
	}
	
	

CTestParentStep::~CTestParentStep()
/**
   Destructor
 */
	{
	}

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the application's user interface object.
   
 */
void CTestParentStep::ConstructAppL(CEikonEnv* aCoe)
    { // runs inside a TRAP harness
	aCoe->ConstructL();

	CSimpleParentAppUi* appUi= new (ELeave) CSimpleParentAppUi(this);
    aCoe->SetAppUi(appUi);
    appUi->ConstructL();
    }

/**
   Auxiliary function for all Test Cases
  
   The method creates & sets the test step's user interface object and
   launches the test step.
   
   @SYMTestCaseID UIF-TPARENT-doTestStepL
  
   @SYMDEF
  
   @SYMTestCaseDesc This test aims to test that the parent of a control created
                    in a container has the view as its parent.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The view creates a control, and sets the container window
                   for the control to be itself 
  
   @SYMTestExpectedResults The control is queried to confirm that its parent
                           is the view.
   
 
 */
TVerdict CTestParentStep::doTestStepL() // main function called by E32
	{
  	PreallocateHALBuffer();
	__UHEAP_MARK;
	SetTestStepID(_L("UIF-TPARENT-doTestStepL"));
	// Before creating the CEikonEnv we must create C:\parent.txt.
	// The presence of this file will modify the behaviour of 
	// staticsettingsinit
	RSmlTestUtils utils;
	User::LeaveIfError(utils.Connect());
	CleanupClosePushL(utils);
	_LIT(KFile, "c:\\parent.txt");
	utils.CreateFileL(KFile);
	    
	CEikonEnv* coe=new CEikonEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
	
	utils.DeleteFileL(KFile);
	CleanupStack::PopAndDestroy(&utils);

	REComSession::FinalClose();
	
	RecordTestResultL();
	CloseTMSGraphicsStep();
	__UHEAP_MARKEND;
	

	return TestStepResult();
	}

//
//
// CParentTestAppView
//
//
/**
  Constructor for CParentTestAppView Class.\n
*/
CParentTestAppView::CParentTestAppView()
	{
	}
/**
  Static entry function for CParentTestAppView class.\n
  Instantiates the CParentTestAppView object.\n
  Invokes the second phase constructor passing Layout manager as argument.\n
*/
CParentTestAppView* CParentTestAppView::NewL( const TRect& aRect)
	{
	CParentTestAppView* self = new(ELeave) CParentTestAppView();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for CParentTestAppView class.\n
  Destroys the Control array.\n
*/
CParentTestAppView::~CParentTestAppView()
	{
	delete iSimpleParentControl;
	}
/**
  Second phase constructor for CParentTestAppView class.\n
  Creates a control's window. The created window is the child of the application's window group.\n
  Sets the view's extent i.e dimensions.\n
  Instantiates a component control of CSimpleParentControl class.\n
  The AppView object is added as the container control for the component control.\n
*/
void CParentTestAppView::ConstructL(const TRect& aRect)
    {
	CreateWindowL();
	SetRect(aRect);
	TRect ctrlRect(10, 10, 20, 20);
	
	iSimpleParentControl = CSimpleParentControl::NewL(*this, ctrlRect);
	iSimpleParentControl->SetContainerWindowL(*this);
		
	}
/**
   Gets the component control's at the index (aIndex) in the Control array.\n
*/	
CCoeControl* CParentTestAppView::ComponentControl(TInt /*aIndex*/) const
	{
	return iSimpleParentControl;
	}
/**
  Gets the number of component controls contained by the App View .\n
*/	
TInt CParentTestAppView::CountComponentControls() const
	{
	return 1;
	}

/**
  Function to Draw the App View .\n
  Gets a pointer to the Windows Graphic context.
  Sets the pen colour,pen style and brush style settings.\n
  Draws the control using DrawRect function of the Graphics context.\n
*/
void CParentTestAppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
 	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	}






