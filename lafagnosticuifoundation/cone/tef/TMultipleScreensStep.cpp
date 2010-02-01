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
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code 
*/

#include "TMultipleScreensStep.h"
#include "../src/coepanic.h"
#include <apacmdln.h> 

const TInt KFstScreenNo = 0;
const TInt KSndScreenNo = 1;
const TInt KX = 0;
const TInt KY = 0;
/*Controls*/

CTImageControl::CTImageControl(CFbsBitmap& aBitmap)
	:iBitmap(aBitmap)
	{
	}

CTImageControl::~CTImageControl()
	{
	}

CTImageControl* CTImageControl::NewL(RWindowGroup& aWindow,CFbsBitmap& aBitmap)
	{
	CTImageControl* self = new(ELeave)CTImageControl(aBitmap);
	CleanupStack::PushL(self);
	self->ConstructL(aWindow);
	CleanupStack::Pop();
	return self;
	}

void CTImageControl::ConstructL(RWindowGroup& aWindow)
	{	
   	CreateWindowL(aWindow);
   	SetExtentToWholeScreen();
    SetFocus(ETrue);
	ActivateL();
	}

void CTImageControl::Draw(const TRect& /*aRect*/) const
	{
    CWindowGc& gc=SystemGc();
	TRect rct(0, 0, iBitmap.SizeInPixels().iWidth, iBitmap.SizeInPixels().iHeight);
	gc.Clear();
	gc.DrawBitmap(rct,&iBitmap);
	}

/*AppUI*/
CTMultipleScreensAppUi::CTMultipleScreensAppUi(CTmsTestStep* aStep) :
	CTestCoeAppUi(aStep),
	iNumScreens(0)
	{
	}

void CTMultipleScreensAppUi::ConstructL()
	{
	CTestCoeAppUi::ConstructL();
	iBitmap=new(ELeave) CFbsBitmap();
	iBitmap->Load(KImagePath);
	AutoTestManager().StartAutoTest();
	}

CTMultipleScreensAppUi::~CTMultipleScreensAppUi()
	{
	if(iSndControl)
		{
		RemoveFromStack(iSndControl);
		delete iSndControl;
		}

	RemoveFromStack(iFstControl);
	delete iFstControl;
	delete iBitmap;
	}
	

void CTMultipleScreensAppUi::CompareL(TInt aScreenNumber)
	{
	INFO_PRINTF1(_L("Compare bitmaps..."));
	CWsScreenDevice* screenDevice = STATIC_CAST(CWsScreenDevice*,iCoeEnv->SystemGc().Device());
	TEST(screenDevice->GetScreenNumber()==aScreenNumber);
	TInt bitmapHeight = iBitmap->SizeInPixels().iHeight;
	TInt bitmapWidth = iBitmap->SizeInPixels().iWidth;
	TDisplayMode screenDisplayMode = screenDevice->DisplayMode();
	
	TRect rct(KX, KY, bitmapWidth, bitmapHeight);
	 
	INFO_PRINTF1(_L("Capture screen content."));
	CFbsBitmap* screenBitmap = new(ELeave) CFbsBitmap();
	CleanupStack::PushL(screenBitmap);
	User::LeaveIfError(screenBitmap->Create(iBitmap->SizeInPixels(), screenDisplayMode));
	User::LeaveIfError(screenDevice->CopyScreenToBitmap(screenBitmap,rct));

	INFO_PRINTF1(_L("Compare the displayed bitmap against the expected one."));
	TInt lineLength=iBitmap->ScanLineLength(bitmapWidth, screenDisplayMode);
	HBufC8* compareLineBuf=HBufC8::NewLC(lineLength);
	TPtr8 compareLinePtr(compareLineBuf->Des());
	HBufC8* screenLineBuf=HBufC8::NewLC(lineLength);
	TPtr8 screenLinePtr(screenLineBuf->Des());
	for (TInt index=0; index<bitmapHeight; index++)
		{
		iBitmap->GetScanLine(compareLinePtr, TPoint(KX,index), bitmapWidth, screenDisplayMode);
		screenBitmap->GetScanLine(screenLinePtr, TPoint(KX,index),bitmapWidth, screenDisplayMode);
		INFO_PRINTF2(_L("Scanline: %d"),index);
		TEST(compareLinePtr.Compare(screenLinePtr)==KErrNone);
		}
	CleanupStack::PopAndDestroy(3,screenBitmap);
	}


/**
   @SYMTestCaseID          UIF-CONE-0001

   @SYMPREQ                PREQ1227

   @SYMREQ                 REQ5544

   @SYMTestCaseDesc        Get the number of screens supported by the system

   @SYMTestPriority        High

   @SYMTestStatus          Implemented

   @SYMTestActions         Call NumberOfScreens() to find the number of screens that are supported by the system.
                           API Calls:\n
						   TInt CCoeEnv::NumberOfScreens() const

   @SYMTestExpectedResults This test case gets the number of screens supported by the system.
*/
void CTMultipleScreensAppUi::TestNumberOfScreens()
	{
   	INFO_PRINTF1(_L("Starting TestNumberOfScreens..."));
	iNumScreens = iCoeEnv->WsSession().NumberOfScreens();
   	INFO_PRINTF2(_L("The number of screens supported on this device is %d"),iNumScreens);	
	}

/**
   @SYMTestCaseID          UIF-CONE-0002

   @SYMPREQ                PREQ1227

   @SYMREQ                 REQ5544
   
   @SYMTestCaseDesc        Display image on the first screen.

   @SYMTestPriority        High

   @SYMTestStatus          Implemented

   @SYMTestActions         Pass the second window group as parameter to CreateWindowL of the Control.
   						   Test that the graphics context was last activated on the first screen device. 
                           API Calls:\n
						   CWsScreenDevice* CCoeEnv::ScreenDevice(TInt aScreenNumber) const
						   RWindowGroup* CCoeEnv::RootWin(TInt aScreenNumber) const
						   CGraphicsDevice* CWindowGc::Device() const

   @SYMTestExpectedResults An image is observed on the first screen.
*/
void CTMultipleScreensAppUi::TestDrawOnFirstScreenL()
	{
   	INFO_PRINTF1(_L("Start draw bitmap on first screen..."));
	iFstControl=CTImageControl::NewL(*iCoeEnv->RootWin(KFstScreenNo),*iBitmap); 
   	AddToStackL(iFstControl);
   	iFstControl->DrawNow();
	CompareL(KFstScreenNo);
   	CWsScreenDevice* fstDev = STATIC_CAST(CWsScreenDevice*,iFstControl->SystemGc().Device());
	TEST(fstDev==iCoeEnv->ScreenDevice(KFstScreenNo));
	}

/**
   @SYMTestCaseID          UIF-CONE-0003

   @SYMPREQ                PREQ1227

   @SYMREQ                 REQ5544

   @SYMTestCaseDesc        Display image on the second screen.

   @SYMTestPriority        High

   @SYMTestStatus          Implemented

   @SYMTestActions         Pass the second window group as parameter to CreateWindowL of the Control.
   						   Test that the graphics context was last activated on the second screen device. 
                           API Calls:\n
						   CWsScreenDevice* CCoeEnv::ScreenDevice(TInt aScreenNumber) const
						   RWindowGroup* CCoeEnv::RootWin(TInt aScreenNumber) const
						   CGraphicsDevice* CWindowGc::Device() const

   @SYMTestExpectedResults An image is observed on the first screen.
*/
void CTMultipleScreensAppUi::TestDrawOnSecondScreenL()
	{
	INFO_PRINTF1(_L("Start draw bitmap on second screen..."));
 	if(KSndScreenNo<iNumScreens) 
 		{
	   	iSndControl = CTImageControl::NewL(*iCoeEnv->RootWin(KSndScreenNo),*iBitmap); 
 		AddToStackL(iSndControl);
 		iSndControl->DrawNow();
		CompareL(KSndScreenNo);
 		CWsScreenDevice* sndDev = STATIC_CAST(CWsScreenDevice*, CCoeEnv::Static()->SystemGc().Device());		
		TEST(sndDev==iCoeEnv->ScreenDevice(KSndScreenNo));
 		}
	}
		
/**
   @SYMTestCaseID          UIF-CONE-0004

   @SYMPREQ                PREQ1227

   @SYMREQ                 REQ5544

   @SYMTestCaseDesc        Tests for an invalid screen number.

   @SYMTestPriority        High

   @SYMTestStatus          Implemented
   
   @SYMTestActions         TMulScreensApp is launched.Negative tests are carried out on the APIs listed below, by passing an invalid screen number to them.
                           API Calls:\n
						   CWsScreenDevice* CCoeEnv::ScreenDevice(TInt aScreenNumber) const;
						   RWindowGroup* CCoeEnv::RootWin(TInt aScreenNumber) const;
   
   @SYMTestExpectedResults Application panics and exits with reason number ECoePanicInvalidScreenNumber.
*/
void CTMultipleScreensAppUi::TestInvalidScreenNumberL()
	{
	INFO_PRINTF1(_L("Start Test TestInvalidScreenNumberL ..."));
	_LIT8(KScreenDevice,"ScreenDevice");
	StartProcessL(KScreenDevice);	
	_LIT8(KWindowGroup,"WindowGroup");
	StartProcessL(KWindowGroup);	
	// Closes the panic windows created by this test case.
	// DEF107910 Caused regression in one of the uikon test cases due to this panic dialog box. 
	CloseAllPanicWindowsL();	
	}

void CTMultipleScreensAppUi::StartProcessL(const TDesC8& aTailEnd)
	{
 	CApaCommandLine* cmdLine=CApaCommandLine::NewLC();
	RProcess process; 
	User::LeaveIfError(process.Create(KExeName, KNullDesC));
	CleanupClosePushL(process);
	TRAPD(ret,
		{ 
		cmdLine->SetExecutableNameL(KExeName);
		cmdLine->SetTailEndL(aTailEnd);
		cmdLine->SetProcessEnvironmentL(process);
		})
	TEST(ret==KErrNone);	
	TRequestStatus status = KRequestPending;
	process.Logon(status);

	//Prevent emulator closing when a panic occurs
	User::SetJustInTime(EFalse);

	process.Resume();
	User::WaitForRequest(status); 	

	TEST(process.ExitType()==EExitPanic); 
	TEST(process.ExitReason()==ECoePanicInvalidScreenNumber);

	User::SetJustInTime(ETrue);
	CleanupStack::PopAndDestroy(2, cmdLine);
	}
	
void CTMultipleScreensAppUi::RunTestStepL(TInt aStepNum)
	{
	switch(aStepNum)
		{	
		case 1:
			SetTestStepID(_L("UIF-CONE-0001"));
			TestNumberOfScreens();
			RecordTestResultL();
			break;	
		case 2:
			SetTestStepID(_L("UIF-CONE-0002"));
			TRAPD(err,TestDrawOnFirstScreenL());
			TEST(err==KErrNone);
			RecordTestResultL();
			break;
		case 3:
			SetTestStepID(_L("UIF-CONE-0003"));
			TRAP(err,TestDrawOnSecondScreenL());
			TEST(err==KErrNone);
			RecordTestResultL();
			break;
		case 4:
			SetTestStepID(_L("UIF-CONE-0004"));
			TRAP(err,TestInvalidScreenNumberL());
			TEST(err==KErrNone);
			RecordTestResultL();
			CloseTMSGraphicsStep();
			break;
		case 5:
			INFO_PRINTF1(_L("All tests completed.\n"));
			AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);	
			break;
		default:
			INFO_PRINTF1(_L("CTMultipleScreensAppUi::RunTestStepL default case\n"));
			break;	
		}
	}

/*Test step*/
CTMultipleScreensStep::CTMultipleScreensStep()
	{
	SetTestStepName(KTMultipleScreensStep);
	}

CTMultipleScreensStep::~CTMultipleScreensStep()
	{
	}

void CTMultipleScreensStep::ConstructAppL(CCoeEnv* aCoe)
	{
	aCoe->ConstructL();
	CTMultipleScreensAppUi* appUi=new(ELeave) CTMultipleScreensAppUi(this);
	aCoe->SetAppUi(appUi);
	appUi->ConstructL();	
	}

TVerdict CTMultipleScreensStep::doTestStepL() // main function called by E32
	{
	INFO_PRINTF1(_L("TMultipleScreens Test Started"));
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







