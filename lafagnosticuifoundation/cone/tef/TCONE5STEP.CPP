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
// Tests for control layout manager support.\n
// 
//

/**
 @file
 @internalComponent - Internal Symbian test code
 @file
 @internalComponent
*/

#include <e32std.h>
#include <coeaui.h>
#include "TCone5Step.h"

//! Horizontal border for the control.\n
const TUint KHorizontalBorder = 25;
//! Vertical border for the control.\n
const TUint KVerticalBorder = 25;
//! Max number of component controls.\n
const TUint KNumControls = 10;
//! Minimum size of the Control.\n
#define KMinSize TSize(10, 10)
//! Total Size of the Window in which controls are spaced.\n
#define KViewRect TRect(TPoint(0,0), TPoint(400,200))


/**
  Constructor for CCone5TestAppUi class.\n 
  Sets the Test step Name.\n
*/
CCone5TestAppUi::CCone5TestAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep)
    {
    }
/**
  Destructor for CCone5TestAppUi class.\n
*/
CCone5TestAppUi::~CCone5TestAppUi()
    {
    delete iTestAppView;
    }
/**
  Second phase constructor for the CCone5TestAppUi class.\n
  Invokes the base class CTestCoeAppUi ConstructL function.\n
  Instantiates a layout manager object handles the layout of the components
  of the attached compound controls.\n
  It also calculates the attached compound controls' minimum size.\n
  Starts the asynchronous execution of tests using Auto test manager.\n
*/       
void CCone5TestAppUi::ConstructL()
    {
    CTestCoeAppUi::ConstructL();
    CLayoutTest* layoutMan = new(ELeave) CLayoutTest;
    // CLayoutTest derives from CObject, so push it on the cleanup stack using CleanupClosePushL()
    // this will call close on the object if a leave occurs decrementing the internal reference count
    // and deleting the object when the reference count gets to zero
	CleanupClosePushL(*layoutMan);
    iTestAppView = CLayoutTestAppView::NewL(layoutMan, KViewRect);
 	// layout manager takes over ownership of itself   
    CleanupStack::Pop(layoutMan);
    layoutMan->Close();
    iLayoutMan = layoutMan;
	AutoTestManager().StartAutoTest();
    }
/**
   @SYMTestCaseID UIF-TCone5Step-DoTestsL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests MCoeLayOutManager APIs.\n
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Gets the layout manager for the application initially using LayoutManager() API \n
   Sets the layout manager for the application using SetLayoutManager() API. \n
   The setting of layout manager is verified using the Get Function.\n
   The layouts performed by the layout manager are obtained using LayoutsPerformed() API. \n
   A relayout of the components of the application is requested using RequestReLayout() API.\n
   Change of component control sizes is tested.\n
  
   @SYMTestExpectedResults The application should be started without any error.\n
  
   @SYMTestType : CIT 
 */
void CCone5TestAppUi::DoTestsL()
    {
    INFO_PRINTF1(_L("Testing Setting the Layout Manager"));
    MCoeLayoutManager* layout = NULL;
    layout = iTestAppView->LayoutManager();
	TEST(layout == NULL);
	iTestAppView->SetLayoutManagerL(iLayoutMan);
	layout = iTestAppView->LayoutManager();
	TEST(layout == iLayoutMan);
	iTestAppView->SetLayoutManagerL(NULL);
	layout = iTestAppView->LayoutManager();
	TEST(layout == NULL);
	// set the layout manager in preparation for next test
	iTestAppView->SetLayoutManagerL(iLayoutMan);
	
	
	INFO_PRINTF1(_L("Testing CanAttach()"));
	layout = iTestAppView->LayoutManager();
	TEST(layout->CanAttach() != EFalse);
	
	INFO_PRINTF1(_L("Testing Request Relayout"));
	TUint layoutsPerformed = iLayoutMan->LayoutsPerformed();
	iTestAppView->RequestRelayout(iTestAppView);
	// this should have caused a layout to be performed
	++layoutsPerformed;
	TEST(iLayoutMan->LayoutsPerformed() == layoutsPerformed);	
	const RPointerArray<CTest5Control>& ctrlArray = iTestAppView->CtrlArray();
	TInt numCtrls = ctrlArray.Count();
	layoutsPerformed = iLayoutMan->LayoutsPerformed();
	TInt ctrlCount = 0;
	for (ctrlCount = 0; ctrlCount < numCtrls; ctrlCount++)
		{
		ctrlArray[ctrlCount]->RequestRelayout(iTestAppView);
		++layoutsPerformed;
		TEST(iLayoutMan->LayoutsPerformed() == layoutsPerformed);
		}
	
	
	INFO_PRINTF1(_L("Testing Changing Control Size"));	
	// every time a controls size is changed a layout will be performed
	layoutsPerformed = iLayoutMan->LayoutsPerformed();
	iTestAppView->SetRect(KViewRect);
	++layoutsPerformed;
	TEST(iLayoutMan->LayoutsPerformed() == layoutsPerformed);
	numCtrls = ctrlArray.Count();
	for (ctrlCount = 0; ctrlCount < numCtrls; ctrlCount++)
		{
		ctrlArray[ctrlCount]->SetRect(KMinSize);
		layoutsPerformed++;
		TEST(iLayoutMan->LayoutsPerformed() == layoutsPerformed);
		}
	
	INFO_PRINTF1(_L("Testing Calculating mimimum size"));
	TEST (iTestAppView->MinimumSize() == KMinSize);

	INFO_PRINTF1(_L("Testing baseline offset calculation"));
	TSize testSize(400, 400);

	// See implementation of CalcTextBaselineOffset - if the
	// width > 200, it returns height/4, else it returns 3*height/4
	// ctrlArray[0] only porvided as dummy because fct requires it
	TInt baseOffset = iLayoutMan->CalcTextBaselineOffset(*ctrlArray[0], testSize);
	INFO_PRINTF2(_L("Width 400, offset = %d"), baseOffset);
	TEST (baseOffset < 200);

	testSize.iWidth = 100;
	baseOffset = iLayoutMan->CalcTextBaselineOffset(*ctrlArray[0], testSize);
	INFO_PRINTF2(_L("Width 100, offset = %d"), baseOffset);
	TEST (baseOffset > 200);
	}
    
/**
  Auxilliary Function for all test cases.\n
  This function is iteratively called by the RunL function of the Autotestmanager
  asynchronously.\n
  Calls the following function\n
  1. DoTestsL()
*/
void CCone5TestAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{	 
		case 1:
			SetTestStepID(_L("UIF-TCone5Step-DoTestsL"));			
			TRAPD(err, DoTestsL());
			TEST(err == KErrNone);
			RecordTestResultL();	
			CloseTMSGraphicsStep();
			break;
		case 2:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CCone5TestAppUi class which serves as a AppUi class.\n
  Sets the CCone5TestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTCone5Step::ConstructCone5AppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone5TestAppUi* appUi=new(ELeave) CCone5TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTCone5Step class.\n
  Sets the test step name.\n
*/

CTCone5Step::CTCone5Step()
	{
	SetTestStepName(KTCone5Step);
	}
/**
  Destructor for CTCone5Step class.\n
*/
CTCone5Step::~CTCone5Step()
{}

/**
  Entry function for CTCone5 Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTCone5 Test application.\n
*/
TVerdict CTCone5Step::doTestStepL()
	{
    INFO_PRINTF1(_L("Test Started"));
	CCoeEnv* coe=new(ELeave) CCoeEnv;
    TRAPD(err,ConstructCone5AppL(coe));
    if (!err)
        coe->ExecuteD();
	else
		{
		SetTestStepResult(EFail);
		coe->PrepareToExit();
		coe->DestroyEnvironment();
		delete coe;
		}

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


//
//
// CTest5Control
//
//
/**
  Constructor for CTest5Control class.\n
*/
CTest5Control::CTest5Control()
	{
	}
/**
  Static function used for CTest5Control class instantiation.\n
  The function instantiates an CTest5Control object.\n
  Invokes second phase constructor of CTest5Control class passing pointers to
  Layout manager, container object as arguments.\n
*/
CTest5Control* CTest5Control::NewL(CLayoutTest* aLayoutMan, 
	CCoeControl& aContainer, const TRect& aRect)
	{
	CTest5Control* self = new(ELeave) CTest5Control();
	CleanupStack::PushL(self);
	self->ConstructL(aLayoutMan, aContainer, aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for CTest5Control class.\n
*/
CTest5Control::~CTest5Control()
	{
	}
/**
  Second phase constructor for CTest5Control class.\n
  Sets the component control's container window to aContainer.\n
  Sets the parent control also to aContainer object.\n
  Sets the control's extent i.e; the dimensions to aRect.\n
  Sets the layout manager of the component to aLayoutMan object.\n
  Activate the control.\n
*/
void CTest5Control::ConstructL(CLayoutTest* aLayoutMan, 
	CCoeControl& aContainer, const TRect& aRect)
    {
	SetContainerWindowL(aContainer);
	SetParent(&aContainer);
	SetRect(aRect);
	SetLayoutManagerL(aLayoutMan);
	ActivateL();
	}
/**
  Draws the CTest5Control object.\n
  Gets a pointer to the Windows Graphic context.
  Sets the pen colour,pen style and brush style settings.\n
  Draws the control using DrawRect function of the Graphics context.\n
*/
void CTest5Control::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenColor(KRgbSymbianBlue);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
 	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	}



//
//
// CLayoutTestAppView
//
//
/**
  Constructor for CLayoutTestAppView Class.\n
*/
CLayoutTestAppView::CLayoutTestAppView()
	{
	}
/**
  Static entry function for CLayoutTestAppView class.\n
  Instantiates the CLayoutTestAppView object.\n
  Invokes the second phase constructor passing Layout manager as argument.\n
*/
CLayoutTestAppView* CLayoutTestAppView::NewL(CLayoutTest* aLayoutMan, 
											 const TRect& aRect)
	{
	CLayoutTestAppView* self = new(ELeave) CLayoutTestAppView();
	CleanupStack::PushL(self);
	self->ConstructL(aLayoutMan, aRect);
	CleanupStack::Pop();
	return self;
	}
/**
  Destructor for CLayoutTestAppView class.\n
  Destroys the Control array.\n
*/
CLayoutTestAppView::~CLayoutTestAppView()
	{
	iCtrlArray.ResetAndDestroy();
	iCtrlArray.Close();
	}
/**
  Second phase constructor for CLayoutTestAppView class.\n
  Creates a control's window. The created window is the child of the application's window group.\n
  Sets the view's extent i.e dimenstions.\n
  Instantiates Component controls each of CTest5Control class.\n
  Each component control is appended to a control array.\n
  The AppView object is added as the container control for all the component controls.\n
  The Appview is activated.\n
*/
void CLayoutTestAppView::ConstructL(CLayoutTest* aLayoutMan, const TRect& aRect)
    {
	CreateWindowL();
	SetRect(aRect);
	TRect ctrlRect(10, 10, 20, 20);
	for (TInt ctrlCount = 0; ctrlCount < KNumControls; ctrlCount++)
		{
		CTest5Control* testCtrl = CTest5Control::NewL(aLayoutMan, *this, ctrlRect);
		iCtrlArray.Append(testCtrl);
		testCtrl->SetContainerWindowL(*this);
		TPoint offset(20, 0);
		ctrlRect.iTl += offset;
		ctrlRect.iBr += offset;
		}	
	ActivateL();
	TRect rect(TPoint(0,0), aRect.iBr - TPoint(1,1));
 	SetRect(rect);
	}
/**
   Gets the component control's at the index (aIndex) in the Control array.\n
*/	
CCoeControl* CLayoutTestAppView::ComponentControl(TInt aIndex) const
	{
	return iCtrlArray[aIndex];
	}
/**
  Gets the number of component controls contained by the App View .\n
*/	
TInt CLayoutTestAppView::CountComponentControls() const
	{
	return iCtrlArray.Count();
	}

/**
  Function to Draw the App View .\n
  Gets a pointer to the Windows Graphic context.
  Sets the pen colour,pen style and brush style settings.\n
  Draws the control using DrawRect function of the Graphics context.\n
*/
void CLayoutTestAppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
 	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	}

/**
  Requests the  relayout of the App View.\n
  Instantiates the layout manager.\n
  Invokes the PerformLayout function of Layout Manager.\n
*/
TBool CLayoutTestAppView::RequestRelayout(const CCoeControl* /* aChildControl */)
	{
	MCoeLayoutManager* layoutMan = LayoutManager();
	layoutMan->PerformLayout();
	return ETrue;
	}

/**
  Returns the iCtrlArray member object.\n
*/
const RPointerArray<CTest5Control>& CLayoutTestAppView::CtrlArray() const
	{
	return iCtrlArray;
	}

/**
  Destructor for CLayoutTest Class.\n
  Closes the control array (iCtrlArray) frees all memory allocated to it.\n
*/
CLayoutTest::~CLayoutTest()
	{
	iCtrlArray.Close();	
	}
	
	/** Determines if it is possible to attach another control to the layout manager.
		@return <code>ETrue</code> if possible, otherwise <code>EFalse</code>
	*/
TBool CLayoutTest::CanAttach() const 
		{
		return ETrue;
		}
	
	/** Attaches <code>aCompoundControl</code> to the layout manager.
		Is normally not called manually since <code>CCoeControl::SetLayoutManagerL()</code>
		calls this function.
		Once a compound control is attached to a layout manager, the layout manager owns itself.
		@see Detach
		@see CCoeControl::SetLayoutManagerL
		@param aCompoundControl The compound control.
		@leave KErrOverflow
	*/
void CLayoutTest::AttachL(CCoeControl& aCompoundControl)
	{
	Open();
	iCtrlArray.Append(&aCompoundControl);
	}
	
	
	/** Detaches <code>aCompoundControl</code> from the layout manager.
		Is normally not called manually since <code>CCoeControl::SetLayoutManagerL()</code>
		calls this function when you switch layout managers on a control. It is also called
		from <code>CCoeControl::~CCoeControl</code>
		When the last attached compound control detaches, the layout manager deletes itself.
		@see CCoeControl::SetLayoutManagerL
		@param aCompoundControl The compound control.
	*/
void CLayoutTest::Detach(CCoeControl& aCompoundControl)
	{
	TInt index = iCtrlArray.Find(&aCompoundControl);
	if (index != KErrNotFound)
		{
		iCtrlArray.Remove(index);
		}
	Close();
	}

	/** Calculates the minimum size of <code>aCompoundControl</code>
		Is normally not called manually since <code>CCoeControl::MinimumSize()</code>
		calls this function in the default implementation on controls with layout managers.
	
		To calculate the minimum size is almost as time consuming as performing an actual layout
		and should be used with caution. The minimum size depends on <code>aCompoundControl</code>'s
		maximum width.
		@see CCoeControl::MaximumWidth
		@param aCompoundControl The compound control
		@return The minimum size
	*/	
TSize CLayoutTest::CalcMinimumSize(const CCoeControl& /* aCompoundControl*/) const
	{

	TSize size = KMinSize;
	return size;		
	}
	
	/** Performs the layout of the attached controls
		Is normally not called manually since <code>CCoeControl::SizeChanged()</code>
		calls this function in the default implementation on controls with layout managers.
	
		The layout is generally performed by calling the component controls' 
		<code>SetMaximumWidth()</code>, followed by <code>MinimumSize()</code>, and then the
		layout manager tries to place the component controls according the their minimum
		sizes and the settings.
	
		If the layout manager is suspended it won't perform the actual layout until it
		gets activated.
		@see CCoeControl::SetMaximumWidth
		@see CCoeControl::MinimumSize
		@see SetSuspended
	*/

void CLayoutTest::PerformLayout()
	{
	if (!iLayoutInProgress)
		{	
		iLayoutsPerformed++;
		iLayoutInProgress = ETrue;
		iControlsCompleted = 0;
		// find the total rectangle we have to play with by finding the window owning control
		FindRectangle();
		TInt curCtrlIndex = 0;
		while ((curCtrlIndex < iCtrlArray.Count()) && (curCtrlIndex != KErrTooBig))
			{
			LayoutRow(curCtrlIndex);	
			}
		// set all controls that haven't been layed out to invisible
		for ( ; iControlsCompleted < iCtrlArray.Count(); iControlsCompleted++)
			{
			// make sure we aren't setting the window owning control to invisible, else the
			// application will disappear
			if (!iCtrlArray[iControlsCompleted]->OwnsWindow())
				{
				iCtrlArray[iControlsCompleted]->MakeVisible(EFalse);
				}
			}
		iCtrlArray[iWinOwningCtrlIndex]->DrawNow();
		iLayoutInProgress = EFalse;
		}
	}

/**
	@SYMPREQ PREQ527
	Testing of function CalcTextBaselineOffset introduced by PREQ527
	The switchover width, 1/4 and 3/4 values are purely arbitrary for
	the purpose of the test.
	@param CCoeControl& - reference to CCoeControl
	@param TSize& - rectangle size
	@return - The offset of the baseline to the top of the control
*/
	
TInt CLayoutTest::CalcTextBaselineOffset(const CCoeControl& /*aCompoundControl*/, const TSize& aSize) const
	{
	// Simulate a text control changing position dependent on the width of the
	// rect given. If the width is greater than a certain value, the text is
	// plced near the top of the rectangle, otherwise it's placed nearer the
	// bottom.
	const TInt KBaselineSwitchoverWidth = 200;

	TInt baseline = aSize.iHeight/4;		// 1/4 of the way down.

	if (aSize.iWidth < KBaselineSwitchoverWidth)
		baseline *= 3;						// 3/4 of the way down.

	return baseline;
	}

/**
	@SYMPREQ PREQ527
	Empty definition of SetTextBaselineSpacing introduced by PREQ527
	@param TInt - the desired baseline spacing
	@return - none
*/
void CLayoutTest::SetTextBaselineSpacing(TInt /*aBaselineSpacing*/)
	{
	}

TInt CLayoutTest::TextBaselineSpacing() const
	{
	return 0;
	}

void CLayoutTest::HandleAddedControlL(const CCoeControl& /*aCompoundControl*/, const CCoeControl& /*aAddedControl*/)
	{
	}
	
void CLayoutTest::HandleRemovedControl(const CCoeControl& /*aCompoundControl*/, const CCoeControl& /*aRemovedControl*/)
	{
	}
	
TInt CLayoutTest::HandleControlReplaced(const CCoeControl& /*aOldControl*/, const CCoeControl& /*aNewControl*/)
	{
	return KErrNone;
	}

void CLayoutTest::LayoutRow(TInt& aCurCtrlIndex)
	{
	iSizeUsed.iWidth = 0;
	TUint maxHeightOfRow = 0;
	// while theres space for another control
	while (SpaceForControl(maxHeightOfRow) && (aCurCtrlIndex < iCtrlArray.Count())) 
		{
		if (aCurCtrlIndex == iWinOwningCtrlIndex)
			{
			aCurCtrlIndex++;
			iControlsCompleted++;
			continue;
			}
		TSize ctrlSize = iCtrlArray[aCurCtrlIndex]->Size();
		// if we can layout the control, do it and move to the next one
		if (LayoutControl(aCurCtrlIndex, ctrlSize) != KErrNone)
			{
			break;
			}
		aCurCtrlIndex++;
		// check the max height of the current row, if this is more than the height left
		// return an error
		if (maxHeightOfRow < ctrlSize.iHeight)
			{
			maxHeightOfRow = ctrlSize.iHeight;
			}
		iSizeUsed.iWidth += (ctrlSize.iWidth + KHorizontalBorder);
		}
	iSizeUsed.iHeight += (maxHeightOfRow + KVerticalBorder);
	if (iSizeUsed.iHeight > iLayoutRect.Height())
		{
		aCurCtrlIndex = KErrTooBig;
		}		
	}
	
/**
  Auxilliary Function performing the layout for a control.\n
  Checks if the used up width and height are less that than the available width and height respectively.\n
  If yes, initializes the top left and bottom right coordinates of the control 
  and assigns the same to the control's extent.\n
  
  @return KErrNone if successful else KErrTooBig
*/
TInt CLayoutTest::LayoutControl(TUint aCurCtrlIndex, TSize aCtrlSize)
	{
	TInt layoutSuccess = KErrNone;
	// check that we haven't used all the space left on the screen
	if (((iSizeUsed.iWidth + aCtrlSize.iWidth + KHorizontalBorder) <= iLayoutRect.Width()) &&
		((iSizeUsed.iHeight + aCtrlSize.iHeight + KVerticalBorder) <= iLayoutRect.Height()))
		{
		TPoint topLeft(iSizeUsed.iWidth + KHorizontalBorder, iSizeUsed.iHeight + KVerticalBorder);
		TPoint bottomRight(iSizeUsed.iWidth + aCtrlSize.iWidth + KHorizontalBorder, 
						   iSizeUsed.iHeight + aCtrlSize.iHeight + KVerticalBorder);
		TRect ctrlRect(topLeft, bottomRight);
		CCoeControl* ctrl = iCtrlArray[aCurCtrlIndex];
		ctrl->SetRect(ctrlRect);
		iControlsCompleted++;
		}
	else
		{
		layoutSuccess = KErrTooBig;
		}
	return layoutSuccess;
	}
	
	
/**
  Checks whether there is any space for the component control on the container.\n
  Calculates the already used width and height are less than that allocated for the layout rectangle.\n
 
  @return Boolean,True if there is any space available.\n
*/	
TBool CLayoutTest::SpaceForControl(TUint aMaxHeight)
	{
	 if (((iSizeUsed.iWidth + KHorizontalBorder) < iLayoutRect.Width()) ||
	 	((iSizeUsed.iHeight + aMaxHeight + KVerticalBorder) < iLayoutRect.Height()))
	 	{
	 	return ETrue;
	 	}
	 return EFalse;
	}
/**
  Finds the rectange belonging to the window owning control.\n
  Iterates through the control array and finds the window owning control.\n
  Initializes the iLayoutRect member with the window owning control's extent.\n
*/	
void  CLayoutTest::FindRectangle()
	{
	for (TInt index = 0; index < iCtrlArray.Count(); index++)
		{
		if (iCtrlArray[index]->OwnsWindow())
			{
			iWinOwningCtrlIndex = index;
			iLayoutRect = iCtrlArray[iWinOwningCtrlIndex]->Rect();
			break;
			}
		}
	}
	
/** 
  @return Returns the number of layouts performed by the Layout Manager.\n
  
  The number of layouts performed is stored in iLayoutsPerformed member variable of CLayoutTest object.\n
*/
TUint CLayoutTest::LayoutsPerformed() const
	{
	return iLayoutsPerformed;
	}
