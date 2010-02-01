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
// The test code exercises uikon classes: CEikEnv, CEikDocument, CEikAppUi.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/

#include <eikenv.h>
#include "teikenv.hrh"
#include "teikenv.h"
#include <teikenv.rsg>
#include "apgtask.h"
#include <ecom/ecom.h>
#include "tbitmap.h"
#include <eikrutil.h>	
#include <gulicon.h>
#include <prnsetup.h>
#include "eiksrvc.h"

_LIT(KFileName, "c:\\dummy.doc");
_LIT(KTEikEnvResourceFilePath, "z:\\system\\test\\teikenv\\teikenv.rsc");
_LIT(KParameter,"Event");
_LIT(KInfo, "Info Msg");
const TInt KErrTestHandle=(10);

const TUid KTestPictureType={5711};
const TUid KTestPictureType1={5712};
const TUid KTestPictureTypeUnused={5713};
const TUid KMessageUid1={KUidApaMessageSwitchOpenFileValue};
const TUid KMessageUid2={KUidApaMessageSwitchCreateFileValue};
const TUid KMessageUid3={NULL};

/**
   Auxiliary Function For all Test Cases
   
   Creates a new document. Called by the application DLL framework to create a
   new instance of the document associated with the application.
   
 */
CApaDocument*	CTEikEnvApplication::CreateDocumentL()
	{
	CApaDocument*	theDocument = new (ELeave) CTEikEnvDocument(*this);
	return theDocument;
	}

CTEikEnvApplication	theApplication;
CTEikEnvDocument *theDocument;

//
// class CTEikEnvAppUi
//
CTEikEnvAppUi::CTEikEnvAppUi(CTmsTestStep* aStep) :
	CTestAppUi(aStep, KTEikEnvResourceFilePath)
/**
   Constructor
 */
	{
	}

/**
   Auxiliary Fn for all Test Cases
  
   The method creates application’s user interface and prepares it for running
   tests in auto mode.
  
 */
void CTEikEnvAppUi::ConstructL()
    {
    CTestAppUi::ConstructL();

	AutoTestManager().StartAutoTest();
    }

CTEikEnvAppUi::~CTEikEnvAppUi()
/**
   Destructor
 */
    {
    RemoveFromStack(iParentControl);
	delete iParentControl;
    }
    
/**
   Auxiliary Fn for all Test Cases
  
   The method is an override from CTestAppUi. The method initiates all tests
   to be performed on uikon classes CEikEnv, CEikDocument, CEikAppUi.
   
 */
void CTEikEnvAppUi::RunTestStepL(TInt aNumStep)
 	{
	User::After(TTimeIntervalMicroSeconds32(500000));
 	switch(aNumStep)
 		{
	case 1:
		SetTestStepID(_L("UIF-teikenv-TestEikonEnv"));
		TestEikonEnv();
		RecordTestResultL();
		break;
	case 2:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestEikonEnvPictureFactoryL"));
 		TRAPD(err, TestEikonEnvPictureFactoryL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
	case 3:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestPopUpMenuL"));
 		TRAPD(err, TestPopUpMenuL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
	case 4:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestEikonAppUiL"));
 		TRAPD(err, TestEikonAppUiL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
	case 5:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestCreateBitmapL"));
 		TRAPD(err, TestCreateBitmapL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
	case 6:
 		{
 		SetTestStepID(_L("UIF-UIKTEST-0002"));
 		TRAPD(err,TestREikAppUiSessionApiL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}	
	case 7:
 		{
 		SetTestStepID(_L("UIF-UIKTEST-0001"));
 		TRAPD(err,TestMessageApiL());
		TEST(err == KErrNone);
		RecordTestResultL();
 		break;
 		}
 	case 8:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestAddDialogLikeControlToStackL"));
 		TRAPD(err,TestAddDialogLikeControlToStackL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
 	case 9:
 		{
 		SetTestStepID(_L("UIF-teikenv-TestAddAlertDialogLikeControlToStackL"));
 		TRAPD(err,TestAddAlertDialogLikeControlToStackL());
 		TEST(err == KErrNone);
 		RecordTestResultL();
 		break;
 		}
	case 10:
		{
		SetTestStepID(_L("UIF-teikenv-TestUpdateNameL"));
		TRAPD(err,TestUpdateNameL());
		TEST(err == KErrNone);
		RecordTestResultL();
		break;	
		}
	case 11:
		{
		SetTestStepID(_L("UIF-teikenv-TestFocusL"));
		TRAPD(err,TestFocusL());
		TEST(err == KErrNone);
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;	
		}
	case 12:
	 	{
		INFO_PRINTF1(_L("Tests completed.\n"));
		delete theDocument; 
 		AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
 		break; 		
 		}
	default:
 		break;
 		}
 	}


/**
   @SYMTestCaseID UIF-teikenv-TestCreateBitmapL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikonEnv::CreateBitmapL(const TDesC &aFileName, TInt aId)
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikonEnv::Static() to get the instance of CEikonEnv.
   It then tests CreateBitmapL() (by passing wildcharacter ("*") as the filename) in TBITMAP.exe application.
     
   @SYMTestExpectedResults The method should return application default bitmap if wild character("*")
   is passed as the filename to CEikonEnv::CreateBitmapL(const TDesC &aFileName, TInt aId);
 */

void CTEikEnvAppUi::TestCreateBitmapL()
	{
	_LIT(KBitMapAppFileName,"z:\\sys\\bin\\TBITMAP.exe");

	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();	
	RProcess bitmapProc;
	TInt ret = bitmapProc.Create(KBitMapAppFileName,KNullDesC);
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(bitmapProc);

	INFO_PRINTF1(_L("Create Bitmap Process"));

	//attach commandline to Bitmap process
	TRAP(ret,cmdLine->SetProcessEnvironmentL(bitmapProc));
	TEST(ret == KErrNone);

	TRequestStatus trs;
	bitmapProc.Logon(trs);
	bitmapProc.Resume();
	User::WaitForRequest(trs);

	// check exit values
	TEST(bitmapProc.ExitReason() == KErrNone);	// specifically, it must be different to KErrBitMapDoesNotMatch
	TEST(bitmapProc.ExitType() == EExitKill);

	CleanupStack::PopAndDestroy(&bitmapProc);
	CleanupStack::PopAndDestroy(cmdLine);
	}
	
	/**
   @SYMTestCaseID		UIF-UIKTEST-0001

   @SYMPREQ	
  
   @SYMTestCaseDesc 	Testing the Apis which give messages to the user
  
   @SYMTestPriority 	High
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions  	The apis are called which handle messages,errors and give out
   						messages to the user.Also some other miscellaneous  apis are 
   						verified from classes CEikDocument,CEikAppUi
   
   @SYMTestExpectedResults Test should complete without any leave, panic or error.
   
 */

void CTEikEnvAppUi::TestMessageApiL()
	{
	INFO_PRINTF1(_L("Test step MessageApiL started"));
	TFileName noFile;
	TBool exist=CEikAppUi::ProcessCommandParametersL(EApaCommandCreate,noFile);
	TEST(!exist);
		
	TBuf8<128>	buf;
	buf.Copy(KFileName);
	TMessageResponse response;
	response=CEikAppUi::HandleMessageL(1,KMessageUid1,buf);
	TEST(response==EMessageHandled);
	response=CEikAppUi::HandleMessageL(1,KMessageUid2,buf);
	TEST(response==EMessageHandled);
	response=CEikAppUi::HandleMessageL(1,KMessageUid3,buf);
	TEST(response==EMessageNotHandled);
	
	TBool empty=theDocument->IsEmpty();
	TEST(empty);
		
	CEikonEnv* theEnv = CEikonEnv::Static();
	
	TRAPD(err,theEnv->UpdateSystemFontsL());
	TEST(err==KErrNone);
	
	TBufC<16> bufc2(KParameter);
	TPtr ptr = bufc2.Des();	
	theEnv->SendEventToEikonServer(-16,&ptr,16);
	bufc2=KNullDesC;
	theEnv->SendEventToEikonServer(1,&ptr,16);
		
   	// the following tests are tested through display of required info
	TBufC<10> msg(KInfo);
	theEnv->SetVerboseInfoReporting(ETrue);
	theEnv->VerboseInfoMsg(msg);
	

	theEnv->DisplayTaskList();
	User::After(1000000);
	theEnv->DismissTaskList();//if the tasklist is displayed , it will be closed by this api....hence tested
	
	theEnv->WservAllocInfoMsg();
	User::After(1000000);
	theEnv->AllocInfoMsg();
	User::After(1000000);	
	theEnv->FservAllocInfoMsg();
	User::After(1000000);

	theEnv->HandleErrorWithContext(KErrTestHandle,R_EIKENV_APP_ERR_HANDLE);
	// display tests over
	INFO_PRINTF1(_L("Test step MessageApiL completed!"));
	}

/**
   @SYMTestCaseID UIF-teikenv-TestAddDialogLikeControlToStackL
  
   @SYMPREQ PDEF098453
  
   @SYMTestCaseDesc Test CEikonEnv::AddDialogLikeControlToStackL(CCoeControl* aControl)
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikonEnv::Static() to get the instance of CEikonEnv.
   It then tests AddDialogLikeControlToStackL() method with the following scenarios.
   1) Creates a control with "ECoeStackPrioritySoftkey" priority and displays on the screen
   and then invokes AddDialogLikeControlToStackL().
   2) Creates a control with "ECoeStackPrioritySoftkey-1" priority and displays on the screen
   and then invokes AddDialogLikeControlToStackL().
 
   @SYMTestExpectedResults 
   1) Should return KErrNone
   2) Should return KLeaveWithoutAlert
   
 */

void CTEikEnvAppUi::TestAddDialogLikeControlToStackL()
	{
	TInt res=0;
	CEikonEnv* theEnv = CEikonEnv::Static();
	CTestControl* control1 = CTestControl::NewL();
	AddToStackL(control1,ECoeStackPrioritySoftkey);
	INFO_PRINTF1(_L("Control with softkey priority is added to Control Stack"));
	control1->DrawNow();
	CTestControl* control2 = CTestControl::NewL();
	TRAP(res,theEnv->AddDialogLikeControlToStackL(control2));
	TEST(res==KErrNone);
	INFO_PRINTF1(_L("Control with dialog priority is added to the Control Stack"));
	control2->DrawNow();
	theEnv->RemoveFromStack(control1);
	theEnv->RemoveFromStack(control2);
	
	AddToStackL(control1,ECoeStackPrioritySoftkey-1);
	INFO_PRINTF1(_L("Control with ECoeStackPrioritySoftkey-1 priority is added to Control Stack"));
	control1->DrawNow();
	TRAP(res,theEnv->AddDialogLikeControlToStackL(control2));
	TEST(res==KLeaveWithoutAlert);
	INFO_PRINTF1(_L("Control with dialog priority is not added to the Control Stack"));
	theEnv->RemoveFromStack(control1);
				
	delete control1;
	delete control2;
	}

/**
   @SYMTestCaseID UIF-teikenv-TestFocusL
  
   @SYMDEF 105102
  
   @SYMTestCaseDesc Test CCoeAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination)
  
   @SYMTestPriority Critical
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method tests a particular scenario which is as follows.
   The defect is reproduced when a focus event is called on a control which doesn't exist in the stack.
   To simulate the scenario the following steps are carried and executed with and without fix.
   1) Create control 1(parent) with default settings.
      Add to control stack with 'ECoeStackPrioritySoftkey' priority. Activate parent.
   2) Create control 2(child) with default settings.
      Add to control stack with 'ECoeStackPriorityEnvironmentFilter' (higher than parent) priority.
      Activate child.	
   3) Raise focus lost event (EEventFocusLost). Call HandleWsEventL on child.
   4) When HandleWsEventL is called the overridden HandleForeGroundEventL is called internally.
   5) It deletes the child control which has the current focus.
      This should cause a KERN:EXEC 3 panic which is fixed by making changes in
   	  CCoeAppUi::HandleWsEventL(const TWsEvent& aEvent,CCoeControl* aDestination).	
 
   @SYMTestExpectedResults 
   1) Should not panic.
 
 */
	
void CTEikEnvAppUi::TestFocusL()
	{
	iParentControl = CTestControl::NewL();
	AddToStackL(iParentControl,ECoeStackPrioritySoftkey);
	INFO_PRINTF1(_L("Create parent control and add to control stack with ECoeStackPrioritySoftkey priority."));

	iChildControl = CTestControl::NewL();
	iChildControl->SetContainerWindowL(*iParentControl);
	AddToStackL(iChildControl,ECoeStackPriorityEnvironmentFilter);
	INFO_PRINTF1(_L("Create Child control and add to control stack with  priority more than parent."));

	TWsEvent event;
	event.SetType(EEventFocusLost);
	INFO_PRINTF1(_L("Raise 'EEventFocusLost' event and call HandleWsEventL "));

	HandleWsEventL(event,iChildControl);
	}
	
/**
   @SYMTestCaseID UIF-teikenv-TestAddAlertDialogLikeControlToStackL
  
   @SYMPREQ PDEF098453 
  
   @SYMTestCaseDesc Test CEikonEnv::AddAlertDialogLikeControlToStackL(CCoeControl* aControl)
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikonEnv::Static() to get the instance of CEikonEnv.
   It then tests AddAlertDialogLikeControlToStackL() method with the following scenarios.
   1) Creates a control with "ECoeStackPrioritySoftkey" priority and displays on the screen
   and then invokes AddAlertDialogLikeControlToStackL().
   2) Creates a control with "ECoeStackPrioritySoftkey-1" priority and displays on the screen
   and then invokes AddAlertDialogLikeControlToStackL().
     
   @SYMTestExpectedResults 
   1) Should return KErrNone
   2) Should return KLeaveWithoutAlert
   
 */

void CTEikEnvAppUi::TestAddAlertDialogLikeControlToStackL()
	{
	TInt res=0;
	CEikonEnv* theEnv = CEikonEnv::Static();
	CTestControl* control1 = CTestControl::NewL();
	AddToStackL(control1,ECoeStackPrioritySoftkey);
	INFO_PRINTF1(_L("Control with softkey priority is added to Control Stack"));
	control1->DrawNow();
	CTestControl* control2 = CTestControl::NewL();
	TRAP(res,theEnv->AddAlertDialogLikeControlToStackL(control2));
	TEST(res==KErrNone);
	INFO_PRINTF1(_L("Control with alert priority is added to the Control Stack"));
	control2->DrawNow();
	theEnv->RemoveFromStack(control1);
	theEnv->RemoveFromStack(control2);
	
	AddToStackL(control1,ECoeStackPrioritySoftkey-1);
	INFO_PRINTF1(_L("Control with ECoeStackPrioritySoftkey-1 priority is added to Control Stack"));
	control1->DrawNow();
	TRAP(res,theEnv->AddAlertDialogLikeControlToStackL(control2));
	TEST(res==KLeaveWithoutAlert);
	INFO_PRINTF1(_L("Control with alert priority is not added to the Control Stack"));
	theEnv->RemoveFromStack(control1);
				
	delete control1;
	delete control2;
	}
/**
   @SYMTestCaseID UIF-teikenv-TestEikonEnv
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests CEikonEnv APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions This method invokes CEikonEnv::Static() to get the instance
   of CEikonEnv.\n
   The following setter APIs are then tested for values ETrue and EFalse. 
   1. CEikonEnv::SetBusy()\n
   2. CEikonEnv::SetSystem()\n
   3. CEikonEnv::SetDocNameIsAFile()\n
   4. CEikonEnv::SetRespondsToShutdownEvent()\n
   5. CEikonEnv::SetRespondsToSwitchFilesEvent()\n
   It also tests APIs
   6. CEikonEnv::Version()
   7. CEikonEnv::GetErrorText()
   8. CEikonEnv::LeaveWithInfoMsg()
  
   @SYMTestExpectedResults The method verifies results against expected results. The
   setter APIs are verified by checking results produced by their getter method
   against expected results. 
   
 */
void CTEikEnvAppUi::TestEikonEnv()
	{
	CEikonEnv* theEnv = CEikonEnv::Static();

	theEnv->SetBusy(ETrue);
	INFO_PRINTF1(_L("Set env to busy"));
	TBool theRes = theEnv->IsBusy();
	TEST(theRes);
	theEnv->SetBusy(EFalse);
	INFO_PRINTF1(_L("Set env to free"));
	theRes = theEnv->IsBusy();
	TEST(!theRes);
	
	INFO_PRINTF1(_L("Check the version number"));
	TVersion theVersion = theEnv->Version();
	TEST(theVersion.iMajor >= 0);
	TEST(theVersion.iMinor <= 99);
	TEST(theVersion.iMinor >= 0);
	TEST(theVersion.iMinor < theVersion.iMajor);
	TEST(theVersion.iBuild >= 0);

// Check a system attribute
	INFO_PRINTF1(_L("Set system attribute"));
	theEnv->SetSystem(ETrue);
	theRes = theEnv->IsSystem();
	TEST(theRes);

	theEnv->SetSystem(EFalse);
	theRes = theEnv->IsSystem();
	TEST(!theRes);
//

	TBuf<256>	buf;
	theEnv->GetErrorText(buf, -1);
	TEST(buf==_L("Not found"));
	theEnv->GetErrorText(buf, 2);
	TEST(buf==_L("Unknown error"));
	theEnv->GetErrorText(buf, 2, KNullUid);
	TEST(buf==_L("Unknown error"));

//
	TRAPD(res1, theEnv->LeaveWithInfoMsg(R_EIKENV_APP_ERR_TEXT));
	TEST(res1 != KErrNone);
	TEST(res1==KLeaveWithoutAlert);

//
	theEnv->SetDocNameIsAFile(EFalse);
	TBool res = theEnv->DocNameIsAFile();
	TEST(!res);

	theEnv->SetDocNameIsAFile(ETrue);
	res = theEnv->DocNameIsAFile();
	TEST(res);

//
	INFO_PRINTF1(_L("Test responds to shutdown event"));
	theEnv->SetRespondsToShutdownEvent(EFalse);
	res = theEnv->RespondsToShutdownEvent();
	TEST(!res);

	theEnv->SetRespondsToShutdownEvent(ETrue);
	res = theEnv->RespondsToShutdownEvent();
	TEST(res);

	theEnv->SetRespondsToSwitchFilesEvent(EFalse);
	res = theEnv->RespondsToSwitchFilesEvent();
	TEST(!res);

	theEnv->SetRespondsToSwitchFilesEvent(ETrue);
	res = theEnv->RespondsToSwitchFilesEvent();
	TEST(res);
	}

	/**
   @SYMTestCaseID		UIF-UIKTEST-0002
  
   @SYMPREQ	
  
   @SYMTestCaseDesc 	Testing the Apis 
  
   @SYMTestPriority 	Low
  
   @SYMTestStatus 		Implemented
   
   @SYMTestActions  	The APIs from REikAppUiSession classes of 
   						UIKON are called and verified.  
   						 
   
   @SYMTestExpectedResults Test should complete without any leave, panic or error.
   
 */

void CTEikEnvAppUi::TestREikAppUiSessionApiL()
{
	INFO_PRINTF1(_L("Test step REikAppUiSessionApiL started"));
	_LIT(KResolveError,"ResolveError");
	TInt ret;
	REikAppUiSession uiSession;

	TEST(uiSession.Connect()==KErrNone);
	CleanupClosePushL(uiSession);
	
	TSecurityInfo info;
	info.Set(RProcess());
	uiSession.BlankScreen();//BlankScreen is seen 
	User::After(1000000);
	uiSession.UnblankScreen();//Screen is seen Again, hence tested
	
	ret=uiSession.EnableTaskList();
	TEST(ret==KErrNone);//on successful return	

	CEikonEnv::TErrorValidity errValid;
	TInt error=-90;
	TUid appUid={0x10004c6A};
	TBuf<250> buffer(KResolveError);
	errValid=uiSession.ResolveError(buffer,error,appUid);
	TEST(errValid==CEikonEnv::EErrorNumValid);
	INFO_PRINTF2(_L("The errorValid is %d"),errValid);
	
	uiSession.Close();
	CleanupStack::PopAndDestroy(&uiSession);

	}

/**
   @SYMTestCaseID UIF-teikenv-TestPopUpMenuL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test loading menu from resource.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method invokes CEikonEnv::Static() to get the instance of
   CEikonEnv.It then calls auxiliary method LaunchPopupMenuL() which loads
   menu from resource file. The method then simulates the enter key event
   by invoking CEikonEnv::SimulateKeyEventL() close the menu.
  
   @SYMTestExpectedResults The method should load the menu and close the menu
   with the simulated enter key event.
   
 */
void CTEikEnvAppUi::TestPopUpMenuL()
	{
	CEikonEnv* theEnv = CEikonEnv::Static();

	LaunchPopupMenuL();
	
	TKeyEvent theKeyEvent;
	theKeyEvent.iCode = EKeyEnter;
	theKeyEvent.iScanCode = EStdKeyEnter;
	theKeyEvent.iModifiers = 0;
	theKeyEvent.iRepeats = 0;
	theEnv->SimulateKeyEventL(theKeyEvent,EEventKey);
	}

/**
   @SYMTestCaseID UIF-teikenv-TestEikonEnvPictureFactoryL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test adding/retrieving picture factory to/from Eikon environment.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
  
   @SYMTestActions The method creates two Picture factory objects and invokes 
   CEikonEnv::AddPictureFactoryL() to add them to the Eikon environment. It then
   invokes CEikonEnv::ExtendedPictureFactory() to retrieve these Picture factory
   objects. The test checks CEikonEnv::ExtendedPictureFactory() by using valid &
   invalid picture factory identifers. It tests CEikonEnv::RemovePictureFactory()
   to remove a specified picture factory object.
  
   @SYMTestExpectedResults Each of these tests verify the results against expected
   results.
  
 */
void CTEikEnvAppUi::TestEikonEnvPictureFactoryL()
	{
	CEikonEnv* theEnv = CEikonEnv::Static();

	RFs theFs;
	theFs.Connect(); 
	CTPictureFactory* theFactory = new (ELeave) CTPictureFactory(theFs, KTestPictureType);
	CTPictureFactory* theFactory1 = new (ELeave) CTPictureFactory(theFs, KTestPictureType1);

	CleanupStack::PushL(theFactory);
	CleanupStack::PushL(theFactory1);
	
	TUid Id = theFactory -> Id();
	theEnv->AddPictureFactoryL(*theFactory);

	theEnv->AddPictureFactoryL(*theFactory1);


	MEikPictureFactory* thePictureFactury = theEnv->ExtendedPictureFactory(KTestPictureTypeUnused);
	TEST(thePictureFactury == NULL);

	thePictureFactury = theEnv->ExtendedPictureFactory(KTestPictureType1);
	TEST(thePictureFactury == theFactory1);
	
	theEnv->RemovePictureFactory(Id);
	thePictureFactury = theEnv->ExtendedPictureFactory(KTestPictureType);
	TEST(thePictureFactury == NULL);
	
    CleanupStack::PopAndDestroy(2, theFactory);

	theFs.Close();
	}

/**
   Auxiliary Fn for teikenv-TestPopUpMenuL
  
   The method invokes CEikonEnv::LaunchPopupMenuL() to launch the pop up menu
   identified by the resource id R_EIKENV_MENU. It also test that no leave
   occurs in the process.
  
 */
void CTEikEnvAppUi::LaunchPopupMenuL()
	{
	CEikonEnv* theEnv = CEikonEnv::Static();
	TPoint	theTargetPos(0, 0);
	TInt theResourceId = R_EIKENV_MENU;
	TRAPD(res, theEnv->LaunchPopupMenuL(theResourceId, theTargetPos));

	TEST(!res);
	}

/**
   @SYMTestCaseID UIF-teikenv-TestEikonAppUiL
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test CEikAppUi APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method checks whether CEikAppUi::ProcessMessageL() method,
   invokes overloaded methods of CEikAppUi::OpenFileL() and
   CEikAppUi::CreateFileL() when message UIDs KUidApaMessageSwitchOpenFile16
   and KUidApaMessageSwitchCreateFile16. It then tests whether 
   CEikonEnv::ClosePopup() closes the pop up menu launched by LaunchPopupMenuL()
   method. The method then invokes CEikonEnv::CreateHotKeyControlL() to create 
   hot key control specified by resource id R_TEST_ENV_HOTKEYS. The hot key
   combination is simulated to verify. Finally the method tests 
   CEikAppUi::HandleError() and CEikDocument::SetChanged() APIs.
  
   @SYMTestExpectedResults All test results are verified against expected results.
   
 */
void CTEikEnvAppUi::TestEikonAppUiL()
	{
	TBuf8<128>	buf;
	buf.Copy(KFileName);
	ProcessMessageL(KUidApaMessageSwitchOpenFile16, buf);

	ProcessMessageL(KUidApaMessageSwitchCreateFile16, buf);
//
	LaunchPopupMenuL();

	ClosePopup();
//
	INFO_PRINTF1(_L("Create a hot key control from resource file"));
	iResponseForHotKey = EFalse;
	CreateHotKeyControlL(R_TEST_ENV_HOTKEYS);

	TKeyEvent theKeyEvent;
	theKeyEvent.iCode = 2;
	theKeyEvent.iScanCode = 66; // for 'b'
	theKeyEvent.iModifiers = EModifierLeftCtrl | EModifierCtrl | EModifierAutorepeatable;
	theKeyEvent.iRepeats = 0;

	CEikonEnv* theEnv = CEikonEnv::Static();
	theEnv->SimulateKeyEventL(theKeyEvent, EEventKey);

	User::After(2000000);

	TEST(iResponseForHotKey);
//
	User::After(2000000);

	theEnv->HandleError(KErrPathNotFound);

//
	TInt res = theDocument->HasChanged();
	TEST(!res);

	theDocument->SetChanged(ETrue);
	res = theDocument->HasChanged();
	TEST(res);
	}


/**
   Auxiliary Fn for teikenv-TestEikonAppUiL
  
   The method is overloaded from CEikAppUi class. It is used to test
   ProcessMessageL() when KUidApaMessageSwitchOpenFile16 message uid
   is passed to it as parameter.
  
 */
void CTEikEnvAppUi::OpenFileL(const TDesC& aFileName)
	{
	TPtrC8 ptrc(((TText8*)aFileName.Ptr()),aFileName.Length() * sizeof(TText));

	TBuf8<128> buf;
	buf.Copy(KFileName);
	
	TInt res = ptrc.CompareC(buf);
	TEST(res==0);
	}

/**
   Auxiliary Fn for teikenv-TestEikonAppUiL
  
   The method is overloaded from CEikAppUi class. It is used to verify
   the ProcessMessageL() when KUidApaMessageSwitchCreateFile16 message uid is
   passed to it as parameter.
  
 */
void CTEikEnvAppUi::CreateFileL(const TDesC& aFileName)
	{
	TPtrC8 ptrc(((TText8*)aFileName.Ptr()),aFileName.Length() * sizeof(TText));

	TBuf8<128> buf;
	buf.Copy(KFileName);
	
	TInt res = ptrc.CompareC(buf);
	TEST(res==0);
	}
/**
   Auxiliary Fn for teikenv-TestEikonAppUiL
  
   The method is overloaded from CEikAppUi class. It is used to test
   the simulated hot key event created by CEikonEnv::CreateHotKeyControlL().
  
 */
void CTEikEnvAppUi::HandleCommandL(TInt aCommand)
	{
	switch(aCommand)
		{
		case ETestUiCmd1:
			iResponseForHotKey = ETrue;
			break;
		case ETestUiCmd2:
			iResponseForHotKey = ETrue;
			break;
		}
	}

/**
   Auxiliary Fn for teikenv-TestEikonAppUiL
  
   The method is overloaded from CEikAppUi class. It is used to test
   the simulated behaviour of CEikAppUi::HandleError() when 
   KErrPathNotFound is to be handled.
  
 */
TErrorHandlerResponse CTEikEnvAppUi::HandleError(TInt aError, const SExtendedError& ,
		TDes& aErrorText, TDes& aContextText)
	{
	if(aError == KErrPathNotFound)
		{
		aErrorText.Copy(_L("Path Not Found"));
		aContextText.Copy(_L("File input/output operation"));
		return EInfoDisplay;
		}
	 else if(aError==KErrTestHandle)
		{
		aErrorText.Copy(_L("error handled"));	
		aContextText.Copy(_L("testing api"));
		return EInfoDisplay;
		}
	   
	return EErrorNotHandled;
	}

/**
   @SYMTestCaseID 	UIF-teikenv-TestUpdateNameL
  
   @SYMDEF			DEF119031
  
   @SYMTestCaseDesc Test the caption of a process is valid to rename this process or thread.
  
   @SYMTestPriority High
  
   @SYMTestStatus 	Implemented
   
   @SYMTestActions 	The method creates a process whose caption(in .rss file)is invalid
   					with more than 80 characters and with special symbols included. The API
   					CEikonEnv::UpdateTaskNameL() will verify this caption and update it accordingly. 
  
   @SYMTestExpectedResults 	Eventhough this test process caption is invalid, it will modified with 
   							suitable caption and RenameThread() and RenameProcess() in CEikonEnv::UpdateTaskNameL()
   							will successfully invoked.  
 */ 
void CTEikEnvAppUi::TestUpdateNameL()
	{
	INFO_PRINTF1(_L("Create Caption test Process"));
	_LIT(KNameTestAppFileName,"z:\\sys\\bin\\tnametest1.exe");
	
	RProcess nameProc;
	TInt ret = nameProc.Create(KNameTestAppFileName,KNullDesC);
	TEST(ret == KErrNone);
	User::LeaveIfError(ret);
	CleanupClosePushL(nameProc);
	nameProc.Resume();
	
	//Time for the nametest process to launch itself
	User::After(500000);
	TEST(nameProc.ExitReason() == KErrNone);
	
	// This LIT is the anticipated modified form of that specified in tcaptiontest_reg.rss,
	// to which the test process should be renamed.
	// Note the wild-card to accomodate kernel decorations.
	_LIT( KCheckUpdateProcName, "CheckforValidASCIICharactersBetween-=(32)and~(126)_RemoveIllegalCh*");
	TFindProcess findProc( KCheckUpdateProcName );
	TFullName fullName;
	TEST( KErrNone == findProc.Next(fullName) );
	
	CleanupStack::PopAndDestroy(&nameProc);
	}

/** 
   This method is part of Two - phase construction. It creates a test control.
 */
CTestControl* CTestControl::NewL()
	{ // static
	CTestControl* control=new(ELeave) CTestControl;
	CleanupStack::PushL(control);
	control->ConstructL();
	CleanupStack::Pop(control);
	return control;
	}

CTestControl::~CTestControl()
/**
   Destructor
 */
	{
	}

CTestControl::CTestControl()
/**
   Constructor
 */
	{
	}

/**
  Second phase constructor for the CTestControl.\n
  Creates a control window, sets the control's extent and activates the control.\n
 */
void CTestControl::ConstructL()
	{
	RWsSession& windowServerSession=iCoeEnv->WsSession();
	windowServerSession.SetAutoFlush(ETrue);
	CreateWindowL();
	CWsScreenDevice& screenDevice=*iCoeEnv->ScreenDevice();
	const TSize screenSize(screenDevice.SizeInPixels());
	SetExtent(TPoint(50, 50), TSize(screenSize.iWidth-100, screenSize.iHeight-100));
	ActivateL(); 
	}
	
void CTEikEnvAppUi::HandleForegroundEventL(TBool /*aBool*/)
	{
	if (iChildControl)
		{
		INFO_PRINTF1(_L("Remove Child control from Stack "));
		RemoveFromStack(iChildControl);
		delete iChildControl;
		iChildControl=NULL;
		}
	}
/**
	This method is an override from CCoeControl.It draws the control.
 */
void CTestControl::Draw(const TRect&) const
	{
	CWindowGc& graphicsContext=SystemGc();
	graphicsContext.SetPenStyle(CGraphicsContext::ESolidPen);
	graphicsContext.SetPenColor(KRgbRed);
	graphicsContext.SetBrushStyle(CGraphicsContext::ESolidBrush);
	graphicsContext.SetBrushColor(KRgbGray);
	TRect rectangle(TPoint(0, 0), Rect().Size());
	graphicsContext.DrawRect(rectangle);
	}

/**
   Auxiliary Function for all Test Cases
  
   The method creates a document for the application,prepares the document for
   editing & sets UI which manipulates this document’s data as application's UI.
   
 */
void CEikEnvStep::ConstructAppL(CEikonEnv* aEikEnv)
	{ // runs inside a TRAP harness
	aEikEnv->ConstructL();
 	
	// goes out of scope when function leaves and private members are destroyed. App Architecture handles 
	// CEikAppUI destruction
	theDocument = (CTEikEnvDocument *) (theApplication.CreateDocumentL());
	theDocument->iStep = this;
	theDocument->PrepareToEditL();
	aEikEnv->SetAppUi(theDocument->AppUi());
    }

CEikEnvStep::~CEikEnvStep()
/**
   Destructor
 */
	{
	}

CEikEnvStep::CEikEnvStep()
/**
   Constructor
 */
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KEikEnvStep);
	}



/**
   The method creates & sets the application's user interface object to
   launch the application to initiate the tests.
 */
TVerdict CEikEnvStep::doTestStepL()
	{
	INFO_PRINTF1(_L("Test Started"));
 	PreallocateHALBuffer();
    __UHEAP_MARK;
 
 	CEikonEnv* eikEnv=new CEikonEnv;
 	if (eikEnv==NULL)
		{
		INFO_PRINTF1(_L("Failed to create Eikon Environment due to lack of Memory"));
		SetTestStepResult(EFail);
 		return TestStepResult();
		}
 	TRAPD(err,ConstructAppL(eikEnv));
 	if (err!=KErrNone)
		{
 		SetTestStepResult(EFail);
		delete eikEnv;
		INFO_PRINTF2(_L("Failed to construct Eikon Environment, error %d"), err);
		}
 	else
 		eikEnv->ExecuteD();
 	
 	REComSession::FinalClose();	
	 
 	__UHEAP_MARKEND;
 
	INFO_PRINTF1(_L("Test Finished"));
	return TestStepResult();
    }

//----------------


/**
   The method is an overrride from MEikPictureFactory. It enables editing
   viewing of an Picture Factory object.
 */
void CTPictureFactory::EditL(const TPictureHeader&  ,TBool  )
	{
	}

/**
   This method is an override from MEikPictureFactory.It checks if the factory
   supports the specified picture type aPictureType.
 */
TBool CTPictureFactory::SupportsPictureType(TUid aPictureType) const
	{
	return aPictureType == iPictureType;
	}

/**
   This method is an override from MEikPictureFactory. It returns a pointer to
   the picture factory object.
 */
const MPictureFactory* CTPictureFactory::PictureFactory(TUid aPictureType) const
	{
	if(aPictureType == iPictureType)
		{
		return this;
		}
	return NULL;
	}

/**
   This method is an override from MEikPictureFactory. It returns TPictureHeader
   object.
 */
TPictureHeader CTPictureFactory::InsertL(TUid aPictureType,CBase* )
	{
	TPictureHeader header;
	if (aPictureType==iPictureType)
		{
		}
	return header;

	}

/**
   This method is an override from MEikPictureFactory.
 */
void CTPictureFactory::NewPictureL(TPictureHeader&  ,const CStreamStore&  )const
	{
	}
