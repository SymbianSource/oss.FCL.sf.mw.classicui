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

#include <apgcli.h>
#include "TCone7Step.h"
#include "twindowposition.h"

CCone7TestAppUi::CCone7TestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}

CCone7TestAppUi::~CCone7TestAppUi()
	{
	}


void CCone7TestAppUi::ConstructL()
	{
	INFO_PRINTF1(_L("App UI ConstructL"));
	
	CTestCoeAppUi::ConstructL();
	AutoTestManager().StartAutoTest();
	}

	
TKeyResponse CCone7TestAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	TKeyResponse ret=EKeyWasNotConsumed;
    	if (aType==EEventKey && aKeyEvent.iCode==CTRL('e'))
		{
		CBaActiveScheduler::Exit();
		ret=EKeyWasConsumed;
		}
	return ret;
	}


/**
Ensure the text-drawer is propagated from container to component control
test case PREQ641.1
*/
TBool CCone7TestAppUi::TestTextDrawer_1L()
	{
	CCtlContainer641* testContainer = new (ELeave)CCtlContainer641();
	CleanupStack::PushL(testContainer);
	testContainer->ConstructL( _L("Container") );
	testContainer->SetExtent( TPoint(20,20),TSize(600,200) );
	testContainer->ActivateL();
	testContainer->DrawNow();
	
	const TInt err = testContainer->iContainee->TestContainerTextDrawer();
	User::After( TTimeIntervalMicroSeconds32(2000000) );
	
	CleanupStack::PopAndDestroy(testContainer);
	return err;
	}



/**
Ensure the text-drawer is propagated from the super-container, 
via the sub-container to the component control	
test case PREQ641.2
*/
TBool CCone7TestAppUi::TestTextDrawer_2L()
	{
	CCtlSuperContainer641* testSuperContainer = new (ELeave)CCtlSuperContainer641;
	CleanupStack::PushL(testSuperContainer);
	testSuperContainer->ConstructL( _L("SuperContainer") );
	testSuperContainer->SetExtent( TPoint(20,20),TSize(600,200) );			
	testSuperContainer->ActivateL();
	testSuperContainer->DrawNow();
	
	const TInt err = testSuperContainer->iSubContainer->iContainee->TestContainerTextDrawer();
	User::After( TTimeIntervalMicroSeconds32(2000000) );
	
	CleanupStack::PopAndDestroy(testSuperContainer);
	return err;
	}


class MyDummyMopObject
	{
public:
	enum { ETypeId = 0x1234 };
	MyDummyMopObject() {}
	~MyDummyMopObject() {}
public:
	TInt iDummy;
	};

/**  Ensure the text-drawer the MopSupplyObject function is working properly. */

TBool CCone7TestAppUi::TestTextDrawer_3L()
	{
	CCoePlainTextDrawer* drawer = CCoePlainTextDrawer::New(KRgbRed);
	if (!drawer)
		return EFalse;
		
	XCoeTextDrawer xdrawer(*drawer);
	
	const CCoePlainTextDrawer* drawer2 = xdrawer->MopGetObject(drawer2);
	if (!drawer2 || (drawer2->TextColor() != KRgbRed))
		return EFalse;
		
	const MyDummyMopObject* dummy3 = xdrawer->MopGetObject(dummy3);
	if (dummy3)
		return EFalse;
	
	return ETrue;
	}

/**
This test will verify that left and right text alignment is swapped when the
application language is set to a RightToLeft script, unless the alignment is
set to be absolute. This will be done in 9 steps, drawing a four line text
clockwise from topLeft, via topCenter, topRight, bottomRight, bottomCenter, 
bottomLeft, topLeft, topCenter, to topRight.

Visual verification is required.
*/
TBool CCone7TestAppUi::TestTextDrawer_4L()
	{
	CCtlTestTextDrawer* testTextDrawer = new(ELeave) CCtlTestTextDrawer();
	CleanupStack::PushL(testTextDrawer);
	testTextDrawer->ConstructL();
	testTextDrawer->SetExtent(TPoint(20,20),TSize(600,200));
	testTextDrawer->ActivateL();
	testTextDrawer->DrawNow();
	
	const TInt noOfLines = TCoeTextTypeAdaptor(KMultipleLineText).NumberOfLines();
	TEST(noOfLines == 4);
	INFO_PRINTF2(_L("Number of lines in the text separated by new line character are : %d"), noOfLines);

	TOpenFontFaceAttrib openFontFaceAttrib;
	((CFbsFont&)(testTextDrawer->FontUsed())).GetFaceAttrib(openFontFaceAttrib);
	TBuf<25> buf(openFontFaceAttrib.FullName());
	INFO_PRINTF2(_L("CCtlTestTextDrawer : Typeface being used is %S"), &buf);
	
	CWsScreenDevice* screenDevice = iCoeEnv->ScreenDevice();
	TSize sizeInPixels = screenDevice->SizeInPixels();
	TSize sizeInTwips = screenDevice->SizeInTwips();
	TInt xPixel = sizeInPixels.iWidth;
	TInt xTwips = sizeInTwips.iWidth;
	TInt yPixel = sizeInPixels.iHeight;
	TInt yTwips = sizeInTwips.iHeight;
	
	TInt KLineWidthsInPixels[4];
	
	//Line width in pixels on H4
	if(xPixel == 320 && xTwips == 4463 && yPixel == 240 && yTwips == 3041)
		{
		KLineWidthsInPixels[0] = 80;
		KLineWidthsInPixels[1] = 51;
		KLineWidthsInPixels[2] = 110;
		KLineWidthsInPixels[3] = 100;
		}
	//Line width in pixels on H6 QVGA
	else if(xPixel == 240 && xTwips == 3685 && yPixel == 320 && yTwips ==5056)
		{
		KLineWidthsInPixels[0] = 64;
		KLineWidthsInPixels[1] = 41;
		KLineWidthsInPixels[2] = 88;
		KLineWidthsInPixels[3] = 80;
		}
	//Line width in pixels on H6 VGA
	else if(xPixel == 480 && xTwips == 3685 && yPixel == 640 && yTwips ==5056)
		{
		KLineWidthsInPixels[0] = 128;
		KLineWidthsInPixels[1] = 81;
		KLineWidthsInPixels[2] = 176;
		KLineWidthsInPixels[3] = 160;
		}
	//Line width in pixels on emulator
	else if(xPixel == 640 && xTwips == 7620 && yPixel == 240 && yTwips == 2858)
		{
		KLineWidthsInPixels[0] = 80;
		KLineWidthsInPixels[1] = 51;
		KLineWidthsInPixels[2] = 110;
		KLineWidthsInPixels[3] = 100;
		}
	//Line width in pixels on NaviEngine
	else if(xPixel == 800 && xTwips == 9520 && yPixel == 480 && yTwips == 5712)
		{
		KLineWidthsInPixels[0] = 80;
		KLineWidthsInPixels[1] = 51;
		KLineWidthsInPixels[2] = 110;
		KLineWidthsInPixels[3] = 100;
		}
	//Line width in pixels on NaviEngine without integrated screen
	else if(xPixel == 640 && xTwips == 7616 && yPixel == 480 && yTwips == 5712)
		{
		KLineWidthsInPixels[0] = 80;
		KLineWidthsInPixels[1] = 51;
		KLineWidthsInPixels[2] = 110;
		KLineWidthsInPixels[3] = 100;
		}
	else
		{
		INFO_PRINTF1(_L("This might be a new hardware, need to calculate line widths in pixels again."));
		INFO_PRINTF5(_L("xPixel=%d, xTwips=%d, yPixel=%d, yTwips=%d"),xPixel,xTwips,yPixel,yTwips);
		CleanupStack::PopAndDestroy(testTextDrawer);
		return EFalse;
		}
    
	TInt widthInPixels = 0;
	for (TInt line = 0; line < noOfLines; line++)
		{
		testTextDrawer->WidthOfText(line, widthInPixels);
		TInt testWidth = KLineWidthsInPixels[line];
		// Allow a tolerance of 1 pixel difference less than KLineWidthsInPixels
		TEST(Rng(testWidth-1, widthInPixels, testWidth));
		INFO_PRINTF3(_L("Width for line %d in pixels : %d"), line, widthInPixels);
		}
		
	for(TInt testIndex = 0; testIndex <= 8; testIndex++)
		{
		testTextDrawer->TestTextDrawer(testIndex, ETrue);
		User::After( TTimeIntervalMicroSeconds32(1000000) );
		}

	CleanupStack::PopAndDestroy(testTextDrawer);		
	return ETrue;
	}

/**
This text case will verify that vertical text drawing of XCoeTextDrawer class is correct and 
consistent with horizontal drawing of the same alignment. Clip area will also be set to check that 
drawing will not happen outside this area. The text will consist of a few lines.

defect INC122592  
Visual verification is required.
*/
TBool CCone7TestAppUi::TestTextDrawer_5L()
	{
	CCtlTestTextDrawer* testTextDrawer = new(ELeave) CCtlTestTextDrawer();
	CleanupStack::PushL(testTextDrawer);
	testTextDrawer->ConstructL();
	testTextDrawer->SetExtent(TPoint(20,20),TSize(600,200));
	testTextDrawer->ActivateL();
	testTextDrawer->DrawNow();
	
	const TInt noOfLines = TCoeTextTypeAdaptor(KMultipleLineText1).NumberOfLines();

	TOpenFontFaceAttrib openFontFaceAttrib;
	((CFbsFont&)(testTextDrawer->FontUsed())).GetFaceAttrib(openFontFaceAttrib);
	TBuf<25> buf(openFontFaceAttrib.FullName());
	INFO_PRINTF2(_L("CCtlTestTextDrawer : Typeface being used is %S"), &buf);
	
	//testing with clip area
	TRect clipRect = testTextDrawer->Rect();
	clipRect.Shrink(40, 40);
	TRgb nonClippedText = KRgbRed;
	
	//drawing vertical text, up direction
	for(TInt testIndex = 0; testIndex <= 8; testIndex++)
		{
		testTextDrawer->TestTextDrawer(testIndex, ETrue, NULL, &nonClippedText);
		testTextDrawer->TestTextDrawer(testIndex, ETrue, &clipRect, NULL, EFalse);
		User::After( TTimeIntervalMicroSeconds32(1000000) );

		testTextDrawer->TestTextDrawer(testIndex, EFalse, NULL, &nonClippedText);
		testTextDrawer->TestTextDrawer(testIndex, EFalse, &clipRect, NULL, EFalse);
		User::After( TTimeIntervalMicroSeconds32(1000000) );
		}

	//drawing vertical text, up direction
	for(TInt testIndex = 0; testIndex <= 8; testIndex++)
		{
		testTextDrawer->TestTextDrawer(testIndex, ETrue, NULL, &nonClippedText);
		testTextDrawer->TestTextDrawer(testIndex, ETrue, &clipRect, NULL, EFalse);
		User::After( TTimeIntervalMicroSeconds32(1000000) );

		testTextDrawer->TestTextDrawer(testIndex, EFalse, NULL,     &nonClippedText, ETrue, EFalse);
		testTextDrawer->TestTextDrawer(testIndex, EFalse, &clipRect, NULL,         EFalse, EFalse);
		User::After( TTimeIntervalMicroSeconds32(1000000) );
		}
	
	CleanupStack::PopAndDestroy(testTextDrawer);		
	return ETrue;
	}

/**
   @SYMTestCaseID UIF-TCone7Step-TestWindowPositionL
  
   @SYMDEF PDEF109812: Draw optimization assumes children's position are relative to parent's 
  
   @SYMTestCaseDesc Launches the twindowposition application.
	The application test for position of the non window owning control being drawn.
	
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Launches an test application as follows.
	Instantiates a CApaCommandLine object. Creates the application KAppFileName using RProcess object
	and sets the process environment. Resumes the process and tests for application's exit reason. 
	The test application draw the controls such that when the child has a parent window and is not 
	relative to the the parent control's window.
	  
   @SYMTestExpectedResults The test application should be started without any error. 
	The test application exit with KErrNone if the position of the child window being drawn matches 
	with co-ordinate space of the parent control. Otherwise it exit with KErrWindowPosDoesNotMatch.

   @SYMTestType : CIT 
 */
TBool CCone7TestAppUi::TestWindowPositionL()
	{
	_LIT(KAppFileName,"z:\\sys\\bin\\twindowposition.exe");
	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();	
	RProcess windowPos;
	TInt ret = windowPos.Create(KAppFileName,KNullDesC);
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(windowPos);
	INFO_PRINTF1(_L("Create twindowposition process."));
	
	//attach commandline to twindowposition process
	TRAP(ret,cmdLine->SetProcessEnvironmentL(windowPos));
	TEST(ret == KErrNone);
	windowPos.Resume();
	//Time for the twindowposition process to launch itself
	User::After(3000000);
	TEST(windowPos.ExitReason() != KErrWindowPosDoesNotMatch);
	CleanupStack::PopAndDestroy(&windowPos);
	CleanupStack::PopAndDestroy(cmdLine);
	return ETrue;
	}


/**
   @SYMTestCaseID UIF-TCone7Step-TestExtentNotSetL
  
   @SYMDEF DEF123521 - Fix for PDEF116704 has been removed 
  
   @SYMTestCaseDesc Tests fix for PDEF116704 has not regressed.
	
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Creates a CCoeControl and a RWindow. Sets the RWindow as the container
    window for the CCoeControl.
	  
   @SYMTestExpectedResults The RWindow's position and size should not change.

   @SYMTestType : CIT 
 */
TBool CCone7TestAppUi::TestExtentNotSetL()
	{
	
	// Create a window
	RWindow window(iCoeEnv->WsSession());
	TEST(window.Construct((RWindowTreeNode&)iCoeEnv->RootWin(), TUint32(this))==KErrNone);
	
	// Create a control
	CCoeControl* ctrl = new (ELeave) CCoeControl;
	CleanupStack::PushL(ctrl);
	ctrl->SetExtent(TPoint(20,20), TSize(40,40));

	// Get extent of window
	TPoint position1 = window.Position();
	TSize size1 = window.Size();

	// Set control's container window
	ctrl->SetContainerWindowL(window);

	// Check extent not changed
	TPoint position2 = window.Position();
	TSize size2 = window.Size();

	TEST((size1==size2)&&(position1==position2)); 

	// Cleanup

	CleanupStack::PopAndDestroy(ctrl);
	window.Close();

	return ETrue;
	}


/**
   @SYMTestCaseID UIF-TCone7Step-TestBackedUpExtentNotSetL
  
   @SYMDEF DEF123521 - Fix for PDEF116704 has been removed 
  
   @SYMTestCaseDesc Tests fix for PDEF116704 has not regressed.
	
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions : Creates a CCoeControl and a RBackedUpWindow. Sets the RBackupWindow as the container
    window for the CCoeControl.
	  
   @SYMTestExpectedResults The RBackedUpWindow's position and size should not change.

   @SYMTestType : CIT 
 */
TBool CCone7TestAppUi::TestBackedUpExtentNotSetL()
	{
	
	// Create a window
	RBackedUpWindow window(iCoeEnv->WsSession());
	TEST(window.Construct((RWindowTreeNode&)iCoeEnv->RootWin(), EGray4, TUint32(this))==KErrNone);
	
	// Create a control
	CCoeControl* ctrl = new (ELeave) CCoeControl;
	CleanupStack::PushL(ctrl);
	ctrl->SetExtent(TPoint(20,20), TSize(40,40));

	// Get extent of window
	TPoint position1 = window.Position();
	TSize size1 = window.Size();

	// Set control's container window
	ctrl->SetContainerWindowL(window);

	// Check extent not changed
	TPoint position2 = window.Position();
	TSize size2 = window.Size();

	TEST((size1==size2)&&(position1==position2)); 

	// Cleanup
	CleanupStack::PopAndDestroy(ctrl);
	window.Close();

	return ETrue;
	} 

void CCone7TestAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{
		case 0 :
		case 1 :
			TEST(TestTextDrawer_1L());
			break;
		case 2 :
			TEST(TestTextDrawer_2L());	
			break;
		case 3 :
			TEST(TestTextDrawer_3L());
			break;		
		case 4:
			TEST(TestTextDrawer_4L());
			break;
		case 5:
			TEST(TestTextDrawer_5L());
			break;
		case 6:
			SetTestStepID(_L("UIF-TCone7Step-TestWindowPositionL"));
			TEST(TestWindowPositionL());
			RecordTestResultL();
			break;
		case 7:
			SetTestStepID(_L("UIF-TCone7Step-TestExtentNotSetL"));
			TEST(TestExtentNotSetL());
			RecordTestResultL();
			break;
		case 8:
			SetTestStepID(_L("UIF-TCone7Step-TestBackedUpExtentNotSetL"));
			TEST(TestBackedUpExtentNotSetL());
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}



//----------
void CTCone7Step::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CCone7TestAppUi* appUi= new (ELeave) CCone7TestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}

CTCone7Step::CTCone7Step()
	{
	SetTestStepName(KTCone7Step);
	}

CTCone7Step::~CTCone7Step()
	{}


TVerdict CTCone7Step::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test 7 Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;

	TRAPD(err,ConstructAppL(coe));

	if (!err)
		{
		coe->ExecuteD();
		}
	else
		{
		SetTestStepResult(EFail);
		delete coe;
		}

	REComSession::FinalClose();	

	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
	}


