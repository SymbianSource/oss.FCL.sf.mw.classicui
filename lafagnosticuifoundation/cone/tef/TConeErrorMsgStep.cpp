// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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
 @test
 @internalComponent - Internal Symbian test code 
*/

#include <coemain.h>
#include <bautils.h>
#include <apacmdln.h> 
#include <fbs.h>
#include <imageconversion.h>
#include <bitmaptransforms.h>
#include "TConeErrorMsgStep.h"

/**
  Single Argument Constructor for CConeErrorMsgTestAppUi class.\n
*/
CConeErrorMsgTestAppUi::CConeErrorMsgTestAppUi(CTmsTestStep* aStep) :
CTestCoeAppUi(aStep)
{}
/**
  Destructor for CConeErrorMsgTestAppUi class.\n
*/
CConeErrorMsgTestAppUi::~CConeErrorMsgTestAppUi()
{}

/**
  Second phase Constructor for CConeErrorMsgTestAppUi class.\n
  Invokes the base class CTestCoeAppUi second phase constructor.\n
  Executes the test cases asynchronously using Autotest Manager.\n
*/
void CConeErrorMsgTestAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	
	AutoTestManager().StartAutoTest();
	}

void CConeErrorMsgTestAppUi::TestLeaveWithErrorTextL(const TDesC& aErrorText, const TDesC* aContextErrorText, const TBool& aExceedMaxDesc)
	{
	RBuf testMsg;
	testMsg.CreateL(aErrorText);
	testMsg.CleanupClosePushL();
	
	TInt err=KErrNone;
	
	if (aContextErrorText)
		{
		RBuf testConMsg;
		testConMsg.CreateL(*aContextErrorText);
		testConMsg.CleanupClosePushL();
		TRAP(err,iCoeEnv->LeaveWithErrorText(testMsg, &testConMsg));
	
		TDes& errConRxText = static_cast<CTestCoeEnv*>(iCoeEnv)->TestErrorContextText();
		RBuf errConMsg;
		errConMsg.CreateL(errConRxText);
		errConMsg.CleanupClosePushL();
		INFO_PRINTF3(_L("Err Cntxt Msg Tx: %S, Err Cntxt Msg Rx: %S"), &testConMsg, &errConMsg);
		if (aExceedMaxDesc)
			{
			TEST(testConMsg!=errConMsg);
			TEST(errConMsg.Length()==80); // KErrorContextTextLength
			TEST(errConMsg[79]==KBaflCharTruncation);
			testConMsg.Delete(80, 1); // remove the last char
			testConMsg[79]=KBaflCharTruncation; // set the last char to the truncation char
			TEST(testConMsg==errConMsg);
			}
		else
			{
			TEST(testConMsg==errConMsg);
			}
		
		CleanupStack::PopAndDestroy(2);
		}
	else
		{
		TRAP(err,iCoeEnv->LeaveWithErrorText(testMsg));
		
		TDes& errConText = static_cast<CTestCoeEnv*>(iCoeEnv)->TestErrorContextText();
		INFO_PRINTF3(_L("Actual Context Length: %d, Expected Context Length: %d"), errConText.Length(), 0);			
		TEST(errConText.Length()==0);
		}

	INFO_PRINTF3(_L("Actual Leave Code: %d, Expected Leave Code: %d"), err, KErrExtendedWithText);
	TEST(err==KErrExtendedWithText);
	
	TDes& errRxText = ((CTestCoeEnv *)iCoeEnv)->TestErrorText();
	RBuf errMsg;
	errMsg.CreateL(errRxText);
	errMsg.CleanupClosePushL();
	INFO_PRINTF3(_L("Err Msg Tx: %S, Err Msg Rx: %S"), &testMsg, &errMsg);
	if (aExceedMaxDesc)
		{
		TEST(testMsg!=errMsg);
		TEST(errMsg.Length()==80); // KErrorTextLength
		TEST(errMsg[79]==KBaflCharTruncation);
		testMsg.Delete(80, 1); // remove the last char
		testMsg[79]=KBaflCharTruncation; // set the last char to the truncation char
		TEST(testMsg==errMsg);
		}
	else
		{
		TEST(testMsg==errMsg);
		}

	CleanupStack::PopAndDestroy(2);
	}

/**
 Utility to close the dialogs once the screen has been compared
 with a previous capture of an expected display.
 */	
void CConeErrorMsgTestAppUi::CloseDialogsL()
	{	
	User::LeaveIfError(iWs.Connect());
	TInt wgFocus = iWs.GetFocusWindowGroup();

	const TUint32 ENullWsHandle = 0xFFFFFFFF;	// Events delivered to this handle are thrown away
	RWindowGroup wg = RWindowGroup(iWs);

	wg.Construct(ENullWsHandle);
	TInt wgId = wg.Identifier();

	TWsEvent event;
	event.SetType(EEventKey);
	TKeyEvent *keyEvent = event.Key();
	keyEvent->iCode = EKeyEscape;
	keyEvent->iScanCode = EStdKeyEscape;
	keyEvent->iModifiers = 0;

	TInt limit = 0;
	for(limit = 0; wgFocus != wgId && (limit < 50); limit++)
		{
		iWs.SendEventToAllWindowGroups(event);
		wgFocus = iWs.GetFocusWindowGroup();
		RDebug::Print(_L("CloseAllPanicWindowsL() - EKeyEscape sent to Windows Group"));
		}

	wg.Close();
	iWs.Close();
	}

/**
 Utility for creating a easily readable bmp from a CFbsBitmap
 */

void CConeErrorMsgTestAppUi::ConvertToBmpL(const CFbsBitmap* aBitmap, const TDesC* aFileName)
	{
	CImageEncoder * imageEncoder = CImageEncoder::FileNewL(iFs,*aFileName,CImageEncoder::EOptionAlwaysThread ,KImageTypeBMPUid);
	CleanupStack::PushL(imageEncoder);
	TRequestStatus status;
	imageEncoder->Convert(&status,*aBitmap);
	User::WaitForRequest(status);
	CleanupStack::PopAndDestroy(imageEncoder);
	}

/**
   @SYMTestCaseID		    UIF-CONE-0008

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to 'Test Error Message'
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to 'Test Error Message'
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to 'Test Error Message'
   							CCoeEnv::iErrorContextText is zero'd
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase01L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0008 - test case start"));
	_LIT(KTestErrMsg, "Test Error Message");
	TBuf<20> errText(KTestErrMsg);
	TestLeaveWithErrorTextL(errText);
	INFO_PRINTF1(_L("UIF-CONE-0008 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0009

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to 'Test Error Message'
   							and error context text to 'Test Context Error Message'
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to 'Test Error Message'
   							and error context text to 'Test Context Error Message'
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to 'Test Error Message'
   							CCoeEnv::iErrorContextText is set to 'Test Context Error Message'
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase02L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0009 - test case start"));
	_LIT(KTestErrMsg, "Test Error Message");
	TBuf<20> errText(KTestErrMsg);
	_LIT(KTestErrConMsg, "Test Context Error Message");
	TBuf<40> errConText(KTestErrConMsg);
	TestLeaveWithErrorTextL(errText, &errConText);
	INFO_PRINTF1(_L("UIF-CONE-0009 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0010

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to ''
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to ''
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to ''
   							CCoeEnv::iErrorContextText is zero'd
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase03L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0010 - test case start"));
	_LIT(KTestErrMsg, "");
	TBuf<20> errText(KTestErrMsg);
	TestLeaveWithErrorTextL(errText);
	INFO_PRINTF1(_L("UIF-CONE-0010 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0011

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to ''
   							and error context text to ''
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to ''
   							and error context text to ''
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to ''
   							CCoeEnv::iErrorContextText is set to ''
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase04L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0011 - test case start"));
	_LIT(KTestErrMsg, "");
	TBuf<20> errText(KTestErrMsg);
	_LIT(KTestErrConMsg, "");
	TBuf<40> errConText(KTestErrConMsg);
	TestLeaveWithErrorTextL(errText, &errConText);
	INFO_PRINTF1(_L("UIF-CONE-0011 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0012

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to 'Test Max Error Message'
   							plus, filled to max length of 80 chars.
   							and error context text to 'Test Max Error Message' 
   							plus, filled to max length of 80 chars.
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to 'Test Max Error Message'
   							plus, filled to max length of 80 chars.
   							and error context text to 'Test Max Error Message'
   							plus, filled to max length of 80 chars.
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to 'Test Max Error Message34567890...'
   							CCoeEnv::iErrorContextText is set to 'Test Max Error Message34567...'
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase05L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0012 - test case start"));
	_LIT(KTestErrMsg, "Test Max Error Message3456789012345678901234567890123456789012345678901234567890"); // 80 chars
	TBuf<80> errText(KTestErrMsg);
	_LIT(KTestErrConMsg, "Test Max Error Message3456789012345678901234567890123456789012345678901234567890"); // 80 chars
	TBuf<80> errConText(KTestErrConMsg);
	TestLeaveWithErrorTextL(errText, &errConText);
	INFO_PRINTF1(_L("UIF-CONE-0012 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0013

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to set error text to 'Test Max Error Message'
   							plus, filled to exceed max length of 80 chars, i.e. 81 chars
   							and error context text to 'Test Max Error Message' 
   							plus, filled to exceed max length of 80 chars, i.e. 81 chars
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Call CCoeEnv::LeaveWithErrorText() to set error text to 'Test Max Error Message'
   							plus, filled to exceed max length of 80 chars, i.e. 81 chars
   							and error context text to 'Test Max Error Message'
   							plus, filled to exceed max length of 80 chars, i.e. 81 chars
   
   @SYMTestExpectedResults  CCoeEnv::iErrorText is set to 'Test Max Error Message34567890...' 
   							and terminated by KBaflCharTruncation at the 80th char
   							CCoeEnv::iErrorContextText is set to 'Test Max Error Message34567...' 
   							and terminated by KBaflCharTruncation at the 80th char
   							Function leaves with KErrExtendedWithText
 */
void CConeErrorMsgTestAppUi::TestCase06L()
	{
	INFO_PRINTF1(_L("UIF-CONE-0013 - test case start"));
	_LIT(KTestErrMsg, "Test Max Error Message34567890123456789012345678901234567890123456789012345678901"); // 81 chars
	TBuf<81> errText(KTestErrMsg);
	_LIT(KTestErrConMsg, "Test Max Error Message34567890123456789012345678901234567890123456789012345678901"); // 81 chars
	TBuf<81> errConText(KTestErrConMsg);
	TestLeaveWithErrorTextL(errText, &errConText, ETrue);
	INFO_PRINTF1(_L("UIF-CONE-0013 - test case end"));
	}


TSize CConeErrorMsgTestAppUi::CalculateScreenSize()
	{
	User::LeaveIfError(iWs.Connect());
	CWsScreenDevice *screen;
	screen=new(ELeave) CWsScreenDevice(iWs);
	CleanupStack::PushL(screen);
	User::LeaveIfError(screen->Construct(0));
	TSize screenSize=screen->SizeInPixels();
	CleanupStack::PopAndDestroy(screen);
	iWs.Close();
    return screenSize;
	}


/**
   @SYMTestCaseID		    UIF-CONE-0014

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to display a dialog with error text of 
   							'Test Error Message' and error context text of 'Test Context Error Message' 
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Start the TErrMsgApp, which takes the TailEnd set to "TestCase07", that
   							then sets up the Error Text and Context Error Text before calling
   							CCoeEnv::LeaveWithErrorText() to result in the display of the dialog.
   
   @SYMTestExpectedResults  Dialog with 'Test Context Error Message' and 'Test Error Message' displayed.
   							NOTE: Context error message is on line 1, with Test Error Message below.
   							
   @SYMTestCaseDependencies TErrMsgApp.exe (see TErrMsgApp.cpp)
 */
void CConeErrorMsgTestAppUi::TestCase07()
	{
	INFO_PRINTF1(_L("UIF-CONE-0014 - test case start"));
	INFO_PRINTF1(_L("ErrAndConMsg Dialog"));
	_LIT8(KTestCaseName,"UIF-CONE-0014 ErrAndConMsg");
	_LIT(KDbgBmp,          "c:\\test\\appfwk\\cone\\errandconmsg.bmp");
	_LIT(KDbgConvBmp,      "c:\\test\\appfwk\\cone\\errandconmsg_conv_act.bmp");
	_LIT(KDbgConvCompBmp,  "c:\\test\\appfwk\\cone\\errandconmsg_conv_exp.bmp");
	_LIT(KDbgMbm,          "c:\\test\\appfwk\\cone\\errandconmsg.mbm");
	_LIT(KTestCompareMbm,  "z:\\conetest\\errandconmsg.mbm");
	_LIT(KTestCompareMbmh6,  "z:\\conetest\\errandconmsgh6.mbm");
	_LIT(KTestCompareMbmh6vga,  "z:\\conetest\\errandconmsgh6vga.mbm");
	_LIT(KTestCompareMbmNavi,  "z:\\conetest\\errandconmsgnavi.mbm");
	
	TSize screenSize = CalculateScreenSize();
	TInt err;
	
	//test on h4 or emulator
	if((screenSize.iHeight == 240 && screenSize.iWidth == 320) || (screenSize.iHeight == 240 && screenSize.iWidth == 640))
		{
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbm,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));
		}
	//test on h6 QVGA
	else if(screenSize.iHeight == 320 && screenSize.iWidth == 240)
		{
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbmh6,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));
		}
	//test on h6 VGA
	else if(screenSize.iHeight == 640 && screenSize.iWidth == 480)
	    {
        TRAP(err,TestErrorDialogL(  KTestCaseName, 
                                    KTestCompareMbmh6vga,
                                    &KDbgBmp, 
                                    &KDbgConvBmp, 
                                    &KDbgConvCompBmp,
                                    &KDbgMbm));
        }   
	//test on NaviEngine
	else if(screenSize.iHeight == 480 && screenSize.iWidth == 640)
		{
		
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbmNavi,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));
		
		}
	//It might be a new platform or unknown hardware
	else
		{
		err = KErrNotFound;
		ERR_PRINTF1(_L("UIF-CONE-0014 - Test case ERROR - Unknown Screen size"));
		}
	TEST(err==KErrNone);	
	INFO_PRINTF1(_L("UIF-CONE-0014 - test case end"));
	}

/**
   @SYMTestCaseID		    UIF-CONE-0015

   @SYMTestCaseDesc 	    Check use of CCoeEnv::LeaveWithErrorText() to display a dialog with error text of 
   							'Test Error Message' 
  
   @SYMTestPriority   	    Critical
   
   @SYMTestType				Component Integration Test
  
   @SYMTestStatus 	  	    Implemented
    
   @SYMTestActions  	    Start the TErrMsgApp, which takes the TailEnd set to "TestCase08", that
   							then sets up the Error Text before calling
   							CCoeEnv::LeaveWithErrorText() to result in the display of the dialog.
   
   @SYMTestExpectedResults  Dialog with 'Test Error Message' displayed.
   							NOTE: No Context error message
   							
   @SYMTestCaseDependencies TErrMsgApp.exe (see TErrMsgApp.cpp)
 */
void CConeErrorMsgTestAppUi::TestCase08()
	{
	INFO_PRINTF1(_L("UIF-CONE-0015 - test case start"));
	INFO_PRINTF1(_L("ErrMsg Dialog"));
	_LIT8(KTestCaseName,   "UIF-CONE-0015 ErrMsg");
	_LIT(KDbgBmp,          "c:\\test\\appfwk\\cone\\errmsg.bmp");
	_LIT(KDbgConvBmp,      "c:\\test\\appfwk\\cone\\errmsg_conv_act.bmp");
	_LIT(KDbgConvCompBmp,  "c:\\test\\appfwk\\cone\\errmsg_conv_exp.bmp");
	_LIT(KDbgMbm,          "c:\\test\\appfwk\\cone\\errmsg.mbm");
	_LIT(KTestCompareMbm,  "z:\\conetest\\errmsg.mbm");
	_LIT(KTestCompareMbmh6,  "z:\\conetest\\errmsgh6.mbm");
	_LIT(KTestCompareMbmh6vga,  "z:\\conetest\\errmsgh6vga.mbm");
	_LIT(KTestCompareMbmNavi, "z:\\conetest\\errmsgnavi.mbm");
	
	TSize screenSize = CalculateScreenSize();
	TInt err;
	//test on h4 or emulator
	if((screenSize.iHeight == 240 && screenSize.iWidth == 320) || (screenSize.iHeight == 240 && screenSize.iWidth ==640))
		{
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbm,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));
		}
	//test on h6 QVGA
	else if(screenSize.iHeight == 320 && screenSize.iWidth == 240)
		{
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbmh6,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));	
		}
	//test on h6 VGA
    else if(screenSize.iHeight == 640 && screenSize.iWidth == 480)
        {
        TRAP(err,TestErrorDialogL(  KTestCaseName, 
                                    KTestCompareMbmh6vga,
                                    &KDbgBmp,
                                    &KDbgConvBmp, 
                                    &KDbgConvCompBmp,
                                    &KDbgMbm));
        }
	//test on NaviEngine
	else if(screenSize.iHeight == 480 && screenSize.iWidth == 640)
		{
				
		TRAP(err,TestErrorDialogL(	KTestCaseName, 
									KTestCompareMbmNavi,
									&KDbgBmp, 
									&KDbgConvBmp, 
									&KDbgConvCompBmp,
									&KDbgMbm));	
		}

	//It might be a new platform or unknown hardware
	else
		{
		err = KErrNotFound;
		ERR_PRINTF1(_L("UIF-CONE-0015 - Test case ERROR - Unknown Screen size"));
		}
	TEST(err==KErrNone);	
	INFO_PRINTF1(_L("UIF-CONE-0015 - test case end"));
	}	

/**
	Utility function to setup and start TErrMsgApp for the display of the 
	error dialogs when the App leaves due to a call to CCoeEnv::LeaveWithErrorText()
 */
void CConeErrorMsgTestAppUi::TestErrorDialogL(const TDesC8& aTestCaseName,
			const TDesC& aTestCompareMbm,
			const TDesC* aDbgBmp,
			const TDesC* aDbgConvBmp,
			const TDesC* aDbgConvCompBmp,
			const TDesC* aDbgMbm)
	{
	_LIT(KExeName,"z:\\sys\\bin\\TErrMsgApp.EXE");
	RProcess process; 
	TRequestStatus status;
	TPtrC8 tailEnd;
	tailEnd.Set(aTestCaseName); 
	
	// create and configure command line, with test case name in
	// the tail end to be used by TErrMsgApp to determine what
	// information is displayed in the error dialog
 	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
	User::LeaveIfError(process.Create(KExeName, KNullDesC));
	CleanupClosePushL(process);
	cmdLine->SetExecutableNameL(KExeName);
	cmdLine->SetTailEndL(tailEnd);
	cmdLine->SetProcessEnvironmentL(process);
	status =  KRequestPending;
	process.Logon(status);
	process.Resume();
	
	// allow the host process to start and display a dialog
	User::After(1000000);
	
	// screen capture
	CFbsBitmap* screenBitmap=new(ELeave) CFbsBitmap();
	CleanupStack::PushL(screenBitmap);
	User::LeaveIfError(iWs.Connect());
	CWsScreenDevice *actualScreen;
	actualScreen=new(ELeave) CWsScreenDevice(iWs);
	CleanupStack::PushL(actualScreen);
	User::LeaveIfError(actualScreen->Construct(0));
	TSize screenSize=actualScreen->SizeInPixels();
	TDisplayMode screenDisplayMode = actualScreen->DisplayMode();
	User::LeaveIfError(screenBitmap->Create(screenSize, screenDisplayMode));
	User::LeaveIfError(actualScreen->CopyScreenToBitmap(screenBitmap));
	screenBitmap->Save(_L("c:\\screen.mbm"));

	// load in expected bmp for comparison
	CFbsBitmap* compareBitmap=new(ELeave) CFbsBitmap();
	CleanupStack::PushL(compareBitmap);
	TInt loadErr = compareBitmap->Load(aTestCompareMbm);
	INFO_PRINTF3(_L("Load Error: %d Expected Error: %d"), loadErr, KErrNone);
	TEST(loadErr==KErrNone);
		
	// compare expected and actual bitmaps
	TInt lengthInBytes=screenBitmap->ScanLineLength(screenSize.iWidth, screenDisplayMode);
	HBufC8* lineBufBitmap=HBufC8::NewLC(lengthInBytes);
	TPtr8 lineBufBitmapPtr(lineBufBitmap->Des());
	HBufC8* lineBufScreenBitmap=HBufC8::NewLC(lengthInBytes);
	TPtr8 lineBufScreenBitmapPtr(lineBufScreenBitmap->Des());

	// in the case of the emulator the colour palette used by
	// windows can differ and therefore causes false failures to
	// be reported. e.g. although the dialog is displayed it is
	// subtly different shade of blue (techview), hence for 
	// emulator test runs we purposely do not run a comparison
	// of the screen.
#ifndef __WINS__
	INFO_PRINTF1(_L("Comparing expected vs actual screen bitmap"));
	for (TInt index=0; index<screenSize.iHeight; index++)
		{
		compareBitmap->GetScanLine(lineBufBitmapPtr, TPoint(0,index), screenSize.iWidth, screenDisplayMode);
		screenBitmap->GetScanLine(lineBufScreenBitmapPtr, TPoint(0,index), screenSize.iWidth, screenDisplayMode);
		INFO_PRINTF2(_L("Scanline: %d"),index);
		TEST(lineBufBitmapPtr.Compare(lineBufScreenBitmapPtr)==0);
		}
#endif

	if (aDbgMbm)
		{
		// for debug purposes store the screen capture
		// in c:\appfwk\test\cone\...
		User::LeaveIfError(iFs.Connect());
		iFs.MkDirAll(*aDbgBmp);
		screenBitmap->Save(*aDbgBmp);
		const TDesC* bmpArray[1];
		bmpArray[0] = aDbgBmp;
		TInt32 bmpIds[1];
		bmpIds[0]=0;
		CFbsBitmap::StoreL(*aDbgMbm,1,bmpArray,bmpIds);
		// convert CFbsBitmap of screen capture to standard bmp to ease debug
		ConvertToBmpL(screenBitmap, aDbgConvBmp);
		// convert CFbsBitmap of expected bmp to standard bmp to ease debug
		ConvertToBmpL(compareBitmap, aDbgConvCompBmp);
		iFs.Close();
		}
	
	// terminate the host process
	process.Terminate(KErrNone);
	
	CleanupStack::PopAndDestroy(7);
	iWs.Close();
	
	// send signal to close a dialog
	CloseDialogsL();
	// wait the host process for a termination
	User::WaitForRequest(status);
	
	}

/**
   Auxiliary Function for all Test Cases.\n
  
   The method is an override from CTestCoeAppUi.\n
   This function is called asynchronously by RunL function of the
   AutotestManager after previous test case is executed.\n
   Generates the KeyDown event and KeyUp Events alternatively.\n
 */
 
void CConeErrorMsgTestAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{
		case 1:
			{
			SetTestStepID(_L("UIF-CONE-0008"));
			TRAPD(err,TestCase01L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 2:
			{
			SetTestStepID(_L("UIF-CONE-0009"));
			TRAPD(err,TestCase02L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 3:
			{
			SetTestStepID(_L("UIF-CONE-0010"));
			TRAPD(err,TestCase03L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 4:
			{
			SetTestStepID(_L("UIF-CONE-0011"));
			TRAPD(err,TestCase04L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 5:
			{
			SetTestStepID(_L("UIF-CONE-0012"));
			TRAPD(err,TestCase05L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 6:
			{
			SetTestStepID(_L("UIF-CONE-0013"));
			TRAPD(err,TestCase06L());
			TEST(err==KErrNone);	
			RecordTestResultL();
			break;
			}
		case 7:
			SetTestStepID(_L("UIF-CONE-0014"));
			TestCase07();
			RecordTestResultL();
			break;
		case 8:
			SetTestStepID(_L("UIF-CONE-0015"));
			TestCase08();
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		default:
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
			break;
		}
	}

/**
  Completes the construction of the Control Environment(CCoeEnv object).\n
  Instantiates the CConeErrorMsgTestAppUi class which serves as a AppUi class.\n
  Sets the CConeErrorMsgTestAppUi object as the application's user interface object.\n
  Invokes the second phase constructor of the application's UI.\n
*/
void CTConeErrorMsgStep::ConstructAppL(CCoeEnv* aCoe)
	{ // runs inside a TRAP harness
	aCoe->ConstructL();
	CConeErrorMsgTestAppUi* appUi= new (ELeave) CConeErrorMsgTestAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();
	}
/**
  Constructor for CTConeErrorMsgStep class.\n
  Sets the test step name.\n
*/
CTConeErrorMsgStep::CTConeErrorMsgStep()
	{
	SetTestStepName(KTConeErrorMsgStep);
	}
/**
  Destructor for CTConeErrorMsgStep class.\n
*/
CTConeErrorMsgStep::~CTConeErrorMsgStep()
{}

/**
  Entry function for CTConeErrorMsgStep Test Step.\n
  Sets up the control environment.\n
  Constructs and Launches the CTConeErrorMsgStep Test application.\n
 
*/
TVerdict CTConeErrorMsgStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("Test Started"));
	
	PreallocateHALBuffer();

	__UHEAP_MARK;

	CCoeEnv* coe=new(ELeave) CCoeEnv;
	TRAPD(err,ConstructAppL(coe));

	if (!err)
		coe->ExecuteD();
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


