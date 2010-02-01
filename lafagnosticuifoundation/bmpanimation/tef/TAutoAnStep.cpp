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
// Extended existing test for UIKON GT0143 Typhoon Work Series 60 Changes
// UIKON GT0143 Typhoon Work Series 60 Changes
// REQ815.1: Add a new op-code EBitmapAnimCommandStartAnimationAndKeepLastFrame
// Added a new class RTestBitmapAnim, which inherits from RBitmapAnim and
// calls CommandReply with the new op-code
// Added a new test BmpAnimTest::TestStartAnimationAndKeepLastFrameL to 
// use RTestBitmapAnim
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <s32mem.h>
#include <w32std.h>
#include <fbs.h>
#include <tautoan.mbg>

#include <bmpansrv.h>
#include "bmpanpan.h"
#include "TAutoAnStep.h"

TInt PanicTestThread(TAny* aOption);

enum TPanicOption
	{
	EFirst,
	ENegativeFrameInterval,
	EUnknownPanicOption,	
	ELast
	};

_LIT(KDefaultBitmapPath,"z:\\resource\\apps\\Tautoan\\Tautoan.mbm");

const TInt KValueForSixFrames = 600;//Total time for 6 frames

const TInt KNegativeFrameInterval = -100;

//
// CWsClient
//

CWsClient::CWsClient()
	{
	}

void CWsClient::ConstructL()
	{
	User::LeaveIfError(iWs.Connect());
	iGroup=RWindowGroup(iWs);
	User::LeaveIfError(iGroup.Construct(2));
	}

CWsClient::~CWsClient()
	{
	iGroup.Close();
	iWs.Close();
	}

//
// RTestBitmapAnim
//
RTestBitmapAnim::RTestBitmapAnim(RAnimDll& aAnimDll)
	:RBitmapAnim(aAnimDll)
	{
	}

void RTestBitmapAnim::StartAndKeepLastFrameL()
	{
	CommandReply(EBitmapAnimCommandStartAnimationAndKeepLastFrame);
	}

//
// BmpAnimTest
//

CBitmapAnimClientData* CTAutoAnStep::CreateClientDataL()
	{
	CBitmapAnimClientData* clientData = CBitmapAnimClientData::NewL();
	CleanupStack::PushL(clientData);

	CFbsBitmap* bitmap=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Load(KDefaultBitmapPath, EMbmTautoanTextured));
	CFbsBitmap* mask = NULL;
	
	CBitmapFrameData* frameData = CBitmapFrameData::NewL(bitmap, mask);
	CleanupStack::Pop();	// backgroundbitmap


	clientData->SetBackgroundFrame(frameData);
	
	TPoint position(10, 10);
	TInt milliSeconds = 100;
	TInt count = 6;
	for(TInt index=0; index<count; index++)
		{
		 bitmap=new(ELeave) CFbsBitmap;
		 CleanupStack::PushL(bitmap);
		 User::LeaveIfError(bitmap->Load(KDefaultBitmapPath, EMbmTautoanRedball));
		 mask=new(ELeave) CFbsBitmap;
		 CleanupStack::PushL(mask);
		 User::LeaveIfError(mask->Load(KDefaultBitmapPath, EMbmTautoanRedballm));

		 frameData = CBitmapFrameData::NewL(bitmap, mask, milliSeconds, position);
		 frameData->SetBitmapsOwnedExternally(EFalse);
		 CleanupStack::PushL(frameData);
		 CleanupStack::Pop(2);	// bitmap, mask
		 clientData->AppendFrameL(frameData);
		 CleanupStack::Pop();
		}
	CleanupStack::Pop();
	return clientData;
	}

void CTAutoAnStep::Test1L(CTestingData* aTestingData)
	{
	__UHEAP_MARK;
	RWindow window = aTestingData->iWindow;
	RBitmapAnim animation = aTestingData->iAnimation;
	CBitmapAnimClientData* clientData = NULL;

	TRAPD(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	clientData->SetPlayMode(CBitmapAnimClientData::EPlay);
	clientData->SetFrameInterval(0);
	clientData->SetFlash(EFalse);
	TestWindowConstructL(animation,window,clientData);

	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	clientData->ResetFrameArray();
	TestWindowConstructL(animation,window,clientData);
		
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	TInt count = clientData->FrameArray().Count();
	TInt index=0;
	for(index=0; index<count; index++)
		{
		  CBitmapFrameData* frameData = clientData->FrameArray().At(index);
		  frameData->SetInterval(-1);
		}
	TestWindowConstructL(animation,window,clientData);

	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	count = clientData->FrameArray().Count();
	CBitmapFrameData* frameData = NULL;
	for(index=0; index<count; index++)
		{
		  frameData = clientData->FrameArray().At(index);
		  frameData->SetPosition(TPoint(0, 0));
		}
	TestWindowConstructL(animation,window,clientData);

	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	clientData->SetBackgroundFrame(NULL);
	TestWindowConstructL(animation,window,clientData);

	//testing setbitmapOwnedExternally()	
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	frameData->SetBitmapsOwnedExternally(EFalse);
	TBool val = frameData->BitmapsOwnedExternally();
	TEST(val == EFalse);
	INFO_PRINTF1(_L("Test BitmapOwnedExternally Passed"));
	TestWindowConstructL(animation,window,clientData);

	//testing ResetFrameArray()
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	count = clientData->FrameArray().Count();
	for(index=0; index<count; index++)
		{
		  CBitmapFrameData* frameData = clientData->FrameArray().At(index);
		  frameData->SetInterval(-1);
		}
	clientData->ResetFrameArray();
	val = clientData->FrameArray().Count();
	TEST(val == 0);
	TestWindowConstructL(animation,window,clientData);
	
	//TESTING SetPositionL() -greater than screen size//
	TSize area = window.Size();
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	TRAP(error,animation.SetPositionL(TPoint(area.iWidth+10,area.iHeight+10)));
	TEST(error == KErrNone);
	TestWindowConstructL(animation,window,clientData);
	
	//SetPositionL() - negative value
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	TRAP(error, animation.SetPositionL(TPoint(-10,-10)));
	TEST(error == KErrNone);
	TestWindowConstructL(animation,window,clientData);
		
	//DurationInMilliSeconds()...6 frames...100ms each
	TRAP(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	TInt timeinmillisec = clientData->DurationInMilliSeconds();
	TEST(timeinmillisec == KValueForSixFrames);
	TestWindowConstructL(animation,window,clientData);
	
	RFbsSession::Disconnect();
	__UHEAP_MARKEND;
	RFbsSession::Connect();
	}


void CTAutoAnStep::TestWindowConstructL(RBitmapAnim& animation,RWindow& window,CBitmapAnimClientData* clientData)
	{
	TRAPD(error, animation.ConstructL(window));
	TEST(error == KErrNone);
	TRAP(error, animation.SetBitmapAnimDataL(*clientData));
	TEST(error == KErrNone);
	TRAP(error, animation.StartL());
	TEST(error == KErrNone);
	User::After(1000000);
	TRAP(error, animation.StopL());
	TEST(error == KErrNone);
	delete clientData;	
	}


void CTAutoAnStep::Test2L(CTestingData* aTestingData)
	{
	__UHEAP_MARK;
	RWindow window = aTestingData->iWindow;
	RBitmapAnim animation = aTestingData->iAnimation;

	CBitmapAnimClientData* clientData = NULL;
	TRAPD(error, clientData = CTAutoAnStep::CreateClientDataL());
	TEST(error == KErrNone);
	TRAP(error, animation.ConstructL(window));
	TEST(error == KErrNone);		
	TRAP(error, animation.StartL());
	TEST(error == KErrNone);
	User::After(1000000);
	TRAP(error, animation.StopL());
	TEST(error == KErrNone);
	INFO_PRINTF1(_L("Executing Test2L"));

	TRAP(error, animation.SetBitmapAnimDataL(*clientData));
	TEST(error == KErrNone);
	
	TRAP(error, animation.DisplayFrameL(3));
	TEST(error == KErrNone);
	
	TRAP(error, animation.SetFrameIntervalL(200000));
	TEST(error == KErrNone);
		
	TRAP(error, animation.SetNumberOfCyclesL(1));
	TEST(error == KErrNone);
	
	TRAP(error, animation.SetPlayModeL(CBitmapAnimClientData::ECycle));
	TEST(error == KErrNone);
		
	TRAP(error, animation.SetPositionL(TPoint(20,20)));
	TEST(error == KErrNone);

	TRAP(error, animation.SetNumberOfCyclesL(-1));
	TEST(error == KErrNone);
			
	TRAP(error, animation.SetPlayModeL(CBitmapAnimClientData::EBounce));
	TRAP(error, animation.SetNumberOfCyclesL(1));
	TEST(error == KErrNone);
		
	TRAP(error,animation.DisplayFrameL(-1));
	TEST(error == KErrOverflow);
	
	
	delete clientData;
	RFbsSession::Disconnect();
	__UHEAP_MARKEND;
	RFbsSession::Connect();
	
	}


void CTAutoAnStep::CreatedAndCloseAnimationsL(CTestingData* aTestingData)
	{
	__UHEAP_MARK;
	RAnimDll animDll = aTestingData->iAnimDll;
	RWindow window = aTestingData->iWindow;
	RBitmapAnim animation = aTestingData->iAnimation;
	animation.ConstructL(window);

	RBitmapAnim tempAnimation(animDll);
	tempAnimation.Close();
	RBitmapAnim tempAnimation1(animDll);
	RBitmapAnim tempAnimation2(animDll);
	tempAnimation2.ConstructL(window);

	RBitmapAnim tempAnimation3(animDll);
	tempAnimation3.ConstructL(window);

	RBitmapAnim tempAnimation4(animDll);
	tempAnimation4.ConstructL(window);

	RBitmapAnim tempAnimation5(animDll);
	tempAnimation5.ConstructL(window);

	tempAnimation2.StartL();

	tempAnimation2.Close();
	tempAnimation1.Close();
	tempAnimation3.Close();
	tempAnimation4.Close();
	tempAnimation5.Close();
	__UHEAP_MARKEND;
	}

/**
   @SYMTestCaseID		UIF-BMPANIM-0001
   @SYMDEF				DEF085516
   @SYMTestCaseDesc 	It tests the behaviour of the API SetFrameInterval( ) for negative time.   				
   @SYMTestPriority 	High
   @SYMTestStatus 		Implemented
   @SYMTestActions 		Set time to the frames present in the clientData,through the SetFrameInterval() API of CBitmapAnimClientData.
   						Pass a negative value as parameter to the API.
   @SYMTestExpectedResults  	It should  panic in debug mode with Panic EAnimationClientPanicFrameIntervalNegative and in release mode it should not panic.
  
 */

void CTAutoAnStep::TestNegativeFrameIntervalL()
	{
#ifdef _DEBUG//only in debug mode, the following code is used
	RThread thrd;
	TRequestStatus stat;
	TInt ret=thrd.Create(_L("ptt"),PanicTestThread,KDefaultStackSize,0x2000,0x20000,(TAny*)ENegativeFrameInterval);
	User::LeaveIfError(ret);
	thrd.SetPriority(EPriorityMuchMore);
	thrd.Logon(stat);
	User::SetJustInTime(EFalse);
	thrd.Resume();
	User::WaitForRequest(stat);
	TEST(thrd.ExitType()==EExitPanic); 
	TEST(thrd.ExitReason()==EAnimationClientPanicFrameIntervalNegative);
	INFO_PRINTF2(_L("TestNegativeFrameIntervalL panic=%d"), thrd.ExitReason());
	thrd.Close();
	User::SetJustInTime(ETrue);
	INFO_PRINTF1(_L("TestNegativeFrameIntervalL test case finished in udeb mode"));
#else//only in urel mode , the following code is called
	CBitmapAnimClientData* clientData = CBitmapAnimClientData::NewL();
	CleanupStack::PushL(clientData);

	CFbsBitmap* bitmap=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Load(KDefaultBitmapPath, EMbmTautoanTextured));
	CFbsBitmap* mask = NULL;
	
	CBitmapFrameData* frameData = CBitmapFrameData::NewL(bitmap, mask);
	CleanupStack::Pop();	// backgroundbitmap

	clientData->SetBackgroundFrame(frameData);
	clientData->SetFrameInterval(KNegativeFrameInterval);
	TInt count = 3;
	for(TInt index=0; index<count; index++)
		{
		bitmap=new(ELeave) CFbsBitmap;
		CleanupStack::PushL(bitmap);
		User::LeaveIfError(bitmap->Load(KDefaultBitmapPath, EMbmTautoanRedball));
		mask=new(ELeave) CFbsBitmap;
		CleanupStack::PushL(mask);
		User::LeaveIfError(mask->Load(KDefaultBitmapPath, EMbmTautoanRedballm));

		frameData = CBitmapFrameData::NewL(bitmap, mask);
		frameData->SetBitmapsOwnedExternally(EFalse);
		CleanupStack::PushL(frameData);
		CleanupStack::Pop(2);	// bitmap, mask
		clientData->AppendFrameL(frameData);
		CleanupStack::Pop();
		}
	CleanupStack::Pop();
	TEST(clientData->FrameIntervalInMilliSeconds() == KNegativeFrameInterval);
	delete clientData;	
	INFO_PRINTF1(_L("TestNegativeFrameIntervalL test case finished in urel mode"));
#endif	
	}
	
//The following thread should panic under debug mode
TInt PanicTestThread(TAny* aOption)
	{
	CTrapCleanup::New();
	RFbsSession::Connect();
	
	const TInt option = TInt(aOption);
	switch (option)
		{
		case ENegativeFrameInterval:
			{
			CBitmapAnimClientData* clientData=NULL;
			TRAPD(ret,clientData=CBitmapAnimClientData::NewL());
			if(ret!=KErrNone)
				User::Panic(_L(" TAutoAnStep Failed"),ret);
			clientData->SetFrameInterval(KNegativeFrameInterval);	//The negative time is the reason for panic
			delete clientData;
			}
		default:
			User::Panic(_L("TAutoAnStep error"), EUnknownPanicOption);
		}
	
	return KErrNone;
	}


	
void CTAutoAnStep::TestStartAnimationAndKeepLastFrameL(CTestingData* aTestingData)
	{
	__UHEAP_MARK;
	RWindow window = aTestingData->iWindow;
	RTestBitmapAnim animation(aTestingData->iAnimDll);
	animation.ConstructL(window);
	animation.StartAndKeepLastFrameL();
	animation.StopL();
	animation.Close();
	__UHEAP_MARKEND;
	}

void CTAutoAnStep::ExcuteTestCodeL()
	{
	__UHEAP_MARK;
// Make Ws client
	INFO_PRINTF1(_L("Connecting to Windows Server"));
	CWsClient* client = new (ELeave) CWsClient;	// allocate new client
	CleanupStack::PushL(client);				// push, just in case
	client->ConstructL();						// construct and run
	CleanupStack::Pop();						// client

//
// Creates and deletes to bitmaps in order to allocate KDefaultBitmapPath in the cache for FBserv
// This is necessary to check for memory leaks.
	CFbsBitmap* bitmap = new(ELeave) CFbsBitmap;
	INFO_PRINTF1(_L("Trying to Load Bitmap"));
	User::LeaveIfError(bitmap->Load(KDefaultBitmapPath, EMbmTautoanRedball));
	CFbsBitmap* mask = new(ELeave) CFbsBitmap;
	User::LeaveIfError(mask->Load(KDefaultBitmapPath, EMbmTautoanRedballm));
	delete bitmap;
	delete mask;
//

// Create an animation.
	RWsSession wsSession = client->WindowSession();
	RAnimDll animDll(wsSession);
	User::LeaveIfError(animDll.Load(_L("BmpAnSrv.DLL")));

	RWindow window(wsSession);
	RWindowGroup windowGroup = client->WindowGroup();
	window.Construct(windowGroup, 123);

	RBitmapAnim animation(animDll);

// Create the packaging object
	CTestingData testingData(animDll, animation, window);

// Start tests

	INFO_PRINTF1(_L("Test 1: Create/Run/Stop an animation."));
	TRAPD(err,CTAutoAnStep::Test1L(&testingData));
	TEST(err==KErrNone);

	INFO_PRINTF1(_L("Test 2: Changes Attribute when running"));
	TRAP(err,CTAutoAnStep::Test2L(&testingData));
	TEST(err==KErrNone);

	INFO_PRINTF1(_L("Test 3: Create/Close many animations"));
	TRAP(err,CTAutoAnStep::CreatedAndCloseAnimationsL(&testingData));
	TEST(err==KErrNone);
	
	SetTestStepID(_L("UIF-BMPANIM-0001"));
	INFO_PRINTF1(_L("Test 4: Set Negative frameinterval"));
	TRAP(err,CTAutoAnStep::TestNegativeFrameIntervalL());
	TEST(err==KErrNone);
	RecordTestResultL();
	CloseTMSGraphicsStep();

	// Series60 Specific Test
	INFO_PRINTF1(_L("Test 5: Start Animation and Keep Last Frame"));
	TRAP(err,CTAutoAnStep::TestStartAnimationAndKeepLastFrameL(&testingData));
	TEST(err==KErrNone);

	animation.Close();
	animDll.Close();
	delete client;
	__UHEAP_MARKEND;
	}

CTAutoAnStep::~CTAutoAnStep()
/**
   Destructor
 */
	{
	}

CTAutoAnStep::CTAutoAnStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTAutoAnStep);
	}


TVerdict CTAutoAnStep::doTestStepL()
	{
	 INFO_PRINTF1(_L("Test Started"));

     __UHEAP_MARK;
	 TRAPD(error, ExcuteTestCodeL());				// more initialization, then excute test
     __ASSERT_ALWAYS(!error, User::Panic(_L("TAUTOAN"), error));
     __UHEAP_MARKEND;
	
	 INFO_PRINTF1(_L("Test Finished"));

	 return TestStepResult();
	}
	
