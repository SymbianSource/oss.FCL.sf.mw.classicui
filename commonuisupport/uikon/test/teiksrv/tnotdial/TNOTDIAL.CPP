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
// 1. What is the test code testing?
// TNotdial has been designed to exercise the API of the extended notifier 
// framework. The extended notifier framework has 
// support for priorities, channels, and plugin-in implementation modules --- see the 
// tplugin.* files.
// When the notifier framework is started for the first time Connect is called on
// a RNotifier object. The manager is created and Register is called and the plug-in 
// dll implementing the MEikSrvNotifierbase2 classes:
// CMyPhoneNotifierSubject 
// CMyLEDPhoneNotifierSubject
// CMyLEDLowBatteryNotifierSubject
// CMyLowBatteryNotifierSubject
// CMyAgendaNotifierSubject 
// CMyLEDAgendaNotifierSubject
// is created and registered in the list of notifiers owned by the manager class. 
// The basic tests performed are starting notifiers, updating notifiers and cancelling
// notifiers. Notifiers for phone, agenda and low battery can be requested. Each notifier
// has two channels visually displayed as a busy message and dialog in the middle of the
// screen. Updates are displayed along the bottom of the screen as info messages.
// Messages when starting agenda notifier asynchronously are displayed as info messages
// along the top of the screen. The notifiers have been assigned priorities with Low 
// Battery having the highest and Agenda the lowest. When a notifier is already displayed,
// and another request is called on a notifier with a higher notifier priority on the same 
// channel, the high priority notifier has focus, and the low priority notifier remains
// in the background where it can be updated. When a notifier is alreday displayed, and
// another request is called on a notifier with a lower priority on the same channel, 
// nothing happens until the high priority notifier is in an idle state.
// 2. The APIs:
// ------ class RNotifier
// TInt Connect()
// Creates a session to the extended notifier server, if the server isn't started already,
// it will be started, and the plug-in dll(s) will be loaded. Returns an error code.
// Tint StartNotifier(TUid aNotifierUid, const TDesC8& aBuffer,TDes8& aResponse)
// When started the two channels for a notifier appear as a busy message and dialog, 
// horizontally, in the middle of the display. The busy message on the left displays
// the contents of aBuffer.
// TInt CancelNotifier(TUid aNotifierUid)
// This removes the two channels from the screen
// TInt UpdateNotifier(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)
// When a notifier is already displayed and another request is called on a notifier with a higher priority
// on the same channel, the high priority notifier has focus and the low priority notifier
// remains in updated in the background. Updates are displayed as info messages along the
// bottom of the screen ---  an info message on the left displays the content of aBuffer
// and an info message on the right displays the content of aResponse. If an update is not
// possible because the notifier has not been started, then a suitable info message is
// displayed in the bottom right hand corner.
// void StartNotifierAndGetResponse(TRequestStatus& aRs,TUid aNotifierUid,
// const TDesC8& aBuffer,TDes8& aResponse)
// This function is only implemented for Agenda. Calling results in Agenda channels 
// displayed in the middle of screen as expected and an info message at the top left
// hand corner of the screen. If the call completes and returns, an info message displays
// aResponse at the top right hand corner of the screen.
// ------ class MEikSrvNotifierBase
// This is a mixin class and the following pure virtual functions from (eiknotapi.h) are
// implemented in the plug-in, (see tplugin.* files), for the notifiers
// virtual void Release()
// Called when all resources allocated by notifiers should be freed.
// TNotifierInfo RegisterL()
// Called when a notifier is first loaded to allow any initial construction 
// that is required.
// TNotifierInfo Info() const
// Packages the notifier info, contains public members:
// TUid iUid - The notifier's own uid (e.g KPhoneNotifierUid)
// TUid iChannel - a Uid specifying which channel the notifier uses
// TNotifierPriority iPriority - the priority channel
// TPtrC8 StartL(const TDesC8& aBuffer)
// Will be called by the manager to start the notifier, the contents of the 
// buffer are passed unchanged from RNotifier call (and in the test code displayed
// in the busy message representing the LED channel).
// void StartL(const TDesC8& aBuffer, const TAny* aReturnVal, RMessage aMessage)
// Same as above but asynchronous version. Response is returned to
// void StartNotifierAndGetResponse(TRequestStatus& aRs,TUid aNotifierUid,
// const TDesC8& aBuffer,TDes8& aResponse)
// by calling
// aMessage.WriteL(aReturnVal,descriptor).
// The test code calls
// StartL(const TDesC8& aBuffer), and then aMessage.WriteL(aReturnVal,descriptor),
// successful completion is noted by calling 
// aMessage.Complete(EEikNotExtRequestCompleted); 
// void Cancel()
// Will be called by the manager to stop the notifier. Nothing hapens when a call to
// cancel is made on a notifier that hasn't started. Calling cancel in the test code
// cancels the busy message and dialog channels.
// TPtrC8 UpdateL(const TDesC8& aBuffer)
// Will be called by the manager to update an already started notifier, the contents
// of aBuffer are passed unchanged from the RNotifier call and can be used by the notifier
// implementation. In the test code aBuffer is displayed as an info message at the
// bottom left hand corner of the screen. A response is returned to:
// TInt UpdateNotifier(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)
// 3. The test code does not check the error codes returned by StartNotifier, UpdateNotifier
// and CancelNotifier. Also code and checks for the responses from
// StartL(const TDesC8& aBuffer) are not implemented. Only three of the 5 priority levels
// a notifier can have are implemented.
// 
//

/**
 @file
 @test
 @internalComponent - Internal Symbian test code
*/



#include <basched.h>
#include <eikenv.h>

#include  "tnotdial.h"

#include "tpluginV2.h"
#include "tnotify2v2.h"
#include <techview/eikmenup.h>
#include <e32test.h>
#include "w32std.h"
#include <ecom/ecom.h>


// globals 
_LIT(KTNOTDIALResourceFilePath, "z:\\system\\test\\tnotdial\\tnotdial.rsc");


//
// Models
//

/**
   This method creates an empty control which provides the background for
   the test step.
 */
void CEmptyControl::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	SetRect(aRect);
	SetBlank();
	ActivateL();
	}

//
// class CTNotdialAppUi
//

CTNotdialAppUi::CTNotdialAppUi(CTmsTestStep* aTestStep) :
	CTestAppUi(aTestStep, KTNOTDIALResourceFilePath, R_TNOT_HOTKEYS, R_TDLG_MENUBAR, R_TDLG_TOOLBAR)
	{
	}

/**
   This method copies notifiers along with its resource file from ROM to RAM
   and connects to the extended notifier server. The method also creates an
   empty control and a periodic timer. Once all the construction is completed
   it prepares to execute the test step.
 */
void CTNotdialAppUi::ConstructL()
	{
	INFO_PRINTF1(_L("CTNotdialAppUi::ConstructL"));
	
	CTestAppUi::ConstructL();
	
	iEmptyControl=new(ELeave) CEmptyControl;
	iEmptyControl->ConstructL(ClientRect());

	INFO_PRINTF1(_L("iNotifier Connect"));
	User::LeaveIfError(iNotifier.Connect());
	iColor[0]=KRgbBlack;
	iColor[1]=KRgbBlack;
	iBattTimer = CPeriodic::NewL(CActive::EPriorityIdle);

	INFO_PRINTF1(_L("Start Auto Test"));

	iMyPhoneNotifierUid = KMyNewPhoneNotifierUid ;
	iMySmsNotifierUid = KMyNewSmsNotifierUid ;
	iMyEmailNotifierUid = KMyNewEmailNotifierUid;
	iMyLowBatteryNotifierUid =KMyNewLowBatteryNotifierUid ;
	iMyAgendaAlarmUid =KMyNewAgendaAlarmUid ;

	AutoTestManager().StartAutoTest();
	}

CTNotdialAppUi::~CTNotdialAppUi()
	{
	delete iEmptyControl;
	iNotifier.Close();
	if(iBattTimer->IsActive())
		{
		iBattTimer->Cancel();
		}
	delete iBattTimer;
	}

/**
   The method is an override from CTestAppUi. The method initiates tests on
   public APIs of RNotifier and  MEikSrvNotifierBase.
 */
void CTNotdialAppUi::RunTestStepL(TInt aNextStep)
	{
	switch(aNextStep)
		{
	case 1:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep01L"));
		TestStep01L();
		RecordTestResultL();
		break;
	case 2:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep02L"));
		TestStep02L();
		RecordTestResultL();
		break;
	case 3:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep03L"));
		TestStep03L();
		RecordTestResultL();
		break;
	case 4:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep04L"));
		TestStep04L();
		RecordTestResultL();
		break;
	case 5:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep05L"));
		TestStep05L();
		RecordTestResultL();
		break;
	case 6:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep06L"));
		TestStep06L();
		RecordTestResultL();
		break;
	case 7:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep07L"));
		TestStep07L();
		RecordTestResultL();
		break;
	case 8:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep08L"));
		TestStep08L();
		RecordTestResultL();
		break;
	case 9:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep09L"));
		TestStep09L();
		RecordTestResultL();
		break;
	case 10:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep10L"));
		TestStep10L();
		RecordTestResultL();
		break;
	case 11:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep11L"));
		TestStep11L();
		RecordTestResultL();
		break;
	case 12:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep12L"));
		TestStep12L();
		RecordTestResultL();
		break;
	case 13:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep13L"));
		TestStep13L();
		RecordTestResultL();
		break;
	case 14:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep14L"));
		TestStep14L();
		RecordTestResultL();
		break;
	case 15:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep15L"));
		TestStep15L();
		RecordTestResultL();
		break;
	case 16:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep16L"));
		TestStep16L();
		RecordTestResultL();
		break;
	case 17:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep17L"));
		TestStep17L();
		RecordTestResultL();
		break;
	case 18:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep18L"));
		TestStep18L();
		RecordTestResultL();
		break;
	case 19:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep19L"));
		TestStep19L();
		RecordTestResultL();
		break;
	case 20:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep20L"));
		TestStep20L();
		RecordTestResultL();
		break;
	case 21:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep21L"));
		TestStep21L();
		RecordTestResultL();
		break;
	case 22:
		TestStep22L();
		break;
	case 23:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep23L"));
		TestStep23L();
		RecordTestResultL();
		break;
	case 24:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep24L"));
		TestStep24L();
		RecordTestResultL();
		break;
	case 25:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep25L"));
		TestStep25L();
		RecordTestResultL();
		break;
	case 26:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep26L"));
		TestStep26L();
		RecordTestResultL();
		break;
	case 27:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep27L"));
		TestStep27L();
		RecordTestResultL();
		break;
	case 28:
		SetTestStepID(_L("UIF-TNotdialStep-TestStep28L"));
		TestStep28L();
		RecordTestResultL();
		break;
	case 29:
		SetTestStepID(_L("UIF-NotdialStep-TestStep29L"));
		TestStep29L();
		RecordTestResultL();
		break;
	case 30:
		SetTestStepID(_L("UIF-NotdialStep-TestStep30L"));
		TestStep30L();
		RecordTestResultL();
		break;
	case 31:
		SetTestStepID(_L("UIF-NotdialStep-TestStep31L"));
		TestStep31L();
		RecordTestResultL();
		break;
	case 32:
		SetTestStepID(_L("UIF-NotdialStep-TestStep32L"));
		TestStep32L();
		RecordTestResultL();
		CloseTMSGraphicsStep();
		break;
	case 33:
		{
		INFO_PRINTF1(_L("Last test case reached -> finishing!"));
		CTestAppUi::AutoTestManager().FinishAllTestCases(CAutoTestManager::EPass);
		}
	default:
		break;
		}
		
	INFO_PRINTF1(_L("Test case completed\n"));
	}

/**
  @SYMTestCaseID UIF-TNotdialStep-TestStep01L
  
  @SYMPREQ
  
  @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
  APIs.
  
  @SYMTestPriority High
  
  @SYMTestStatus Implemented
  
  @SYMTestActions The method calls CTNotdialAppUi::HandleCommandL() to test
  StartNotifier() & CancelNotifier() APIs for the following plug-in notifiers:
  (a) Phone Ring Notifier.
  (b) Low Battery Notifier.
  (c) Agenda Alarm Notifier.
  
  @SYMTestExpectedResults The test verifies whether StartNotifier() &
  CancelNotifier() method returns KErrNone on successful completion of
  function call.
  
 */
void CTNotdialAppUi::TestStep01L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 1:"));
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);
	
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep02L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test cancelling the plug-in notifiers via dialog.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the plug-in notifier by calling
   CTNotdialAppUi::HandleCommandL(). The test then connects to Windows Server
   and simulates an ENTER key event on the notifier dialog to cancel. This test
   is carried out for the following plug-in notifiers:
   (a) Phone Ring Notifier.
   (b) Low Battery Notifier.
   (c) Agenda Alarm Notifier.
   
   @SYMTestExpectedResults The tests should be able to simulate the ENTER Key
   for the notifier dialog and cancel the notifier.
   
 */
void CTNotdialAppUi::TestStep02L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 2:"));
	RWsSession ws;
	TKeyEvent event;

	//Set up key event "enter" to simulate key enter to replace clicking "ok" on dialog.
	event.iCode=event.iScanCode=EKeyEnter;
	event.iModifiers=event.iRepeats=0;

	//Connect to Window Server Session
	TEST(ws.Connect()==KErrNone);

	//Start Notifier
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);
	
	//Cancel Notifier using dialog
	INFO_PRINTF1(_L("Cancel Phone Ring Notifier via dialog"));
	
	// Simulate key entry and flush the buffer to send event to windows server session.
	ws.SimulateKeyEvent(event);
	ws.Flush();
	
	//Low battery notifier
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);
	INFO_PRINTF1(_L("Cancel Low Battery Notifier via dialog"));
	
	ws.SimulateKeyEvent(event);
	ws.Flush();		

	//Agenda alarm notifier
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier via dialog"));

	ws.SimulateKeyEvent(event);
	ws.Flush();
	ws.Close();
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep03L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::UpdateNotifier() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the plug-in notifier by calling
   RNotifier::StartNotifier(). It then calls CTNotdialAppUi::AppUpdate()
   method which calls RNotifier::UpdateNotifier() to update the plug-in
   notifier identified by the specified UID. The test then cancels the
   notifier. The test is carried out for the following plug-in notifiers:
   (a) Phone Ring Notifier.
   (b) Low Battery Notifier.
   (c) Agenda Alarm Notifier.
   
   @SYMTestExpectedResults The response received from RNotifier::UpdateNotifier()
   is verified and displayed.
   
  */
void CTNotdialAppUi::TestStep03L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 3:"));

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Start Low Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Update Agenda Alarm Notifier"));
	HandleCommandL(EAppUpdateAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep04L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::UpdateNotifier() API without starting the
   plug-in notifier.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls CTNotdialAppUi::AddUpdate() which invokes
   RNotifier::UpdateNotifier() to update the Low Battery Notifier without
   starting the plug-in notifier.
   
   @SYMTestExpectedResults The response received from RNotifier::UpdateNotifier()
   is verified and displayed.
   
 */
void CTNotdialAppUi::TestStep04L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 4:"));
	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep05L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start
   (i) Low Battery (ii) Ringing Phone & (iii) Agenda Alarm Notifiers one after
   the other without cancelling any plug-in notifier. The test then cancels
   them one after the other in the same order.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep05L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 5:"));
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep06L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start notifiers
   in the order (i) Low Battery (ii) Agenda Alarm & (iii) Ringing Phone
   Notifier one after the other without cancelling any plug-in notifier. The
   test then cancels them so that Low Battery notifier is first cancelled
   followed by Ringing Phone and Agenda Alarm notifier.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep06L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 6:"));
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep07L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start notifiers
   in the order (i) Ringing Phone (ii) Low Battery & (iii) Alarm Agenda Notifier
   one after the other without cancelling any plug-in notifier. The test then
   cancels them so that Low Battery notifier is first cancelled followed by
   Ringing Phone and Agenda Alarm notifier.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep07L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 7:"));
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep08L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start notifiers
   in the order (i) Ringing Phone (ii) Alarm Agenda & (iii) Low Battery 
   Notifiers one after the other without cancelling any plug-in notifier. The
   test then cancels them so that Low Battery notifier is first cancelled
   followed by Ringing Phone and Agenda Alarm notifier.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep08L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 8:"));
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);
	
	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep09L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start notifiers
   in the order (i) Alarm Agenda (ii) Ringing Phone & (iii) Low Battery 
   Notifier one after the other without cancelling any plug-in notifier. The
   test then cancels them so that Low Battery notifier is first cancelled
   followed by Ringing Phone and Agenda Alarm notifier.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep09L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 9:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);
	
	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep10L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() & RNotifier::CancelNotifier()
   API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start notifiers
   in the order (i) Alarm Agenda (ii) Low Battery & (iii) Ringing Phone   
   Notifiers one after the other without cancelling any plug-in notifier. The
   test then cancels them so that Low Battery notifier is first cancelled
   followed by Ringing Phone and Agenda Alarm notifier.
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep10L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 10:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep11L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() ,RNotifier::CancelNotifier()
   & RNotifier::UpdateNotifier() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start Low
   Battery notifier followed by Phone Ringing Notifier without cancelling any
   plug-in notifier. The test then calls UpdateNotifier() to update them so
   that Low Battery notifier is first updated followed by Ringing Phone 
   updation.In the same order these notifiers are cancelled.
   
   @SYMTestExpectedResults The message from RNotifier::UpdateNotifer() is verified
   and recorded. RNotifier::Cancel() should return KErrNone & only cancel the
   plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep11L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 11:"));
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);
	
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);
	
	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);
	
	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);
	
	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);
	
	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep12L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() ,RNotifier::CancelNotifier()
   & RNotifier::UpdateNotifier() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start Phone
   Ringing notifier followed by Low Battery notifier without cancelling any
   plug-in notifier. The test then calls UpdateNotifier() to update them so
   that Low Battery notifier is first updated followed by Phone Ringing
   updation.Now the Low Battery notifier is cancelled followed by Phone 
   Ringing notifier cancellation.
   
   @SYMTestExpectedResults The message from RNotifier::UpdateNotifer() is verified
   and recorded. RNotifier::Cancel() should return KErrNone & only cancel the
   plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep12L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 12:"));
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);

	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep13L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() ,RNotifier::CancelNotifier()
   & RNotifier::UpdateNotifier() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start Alarm
   Agenda notifier followed by Low Battery notifier which is followed by 
   Phone Ringing notifier without cancelling any plug-in notifier. The test
   then calls UpdateNotifier() to update them so that Phone Ringing notifier
   is first updated followed by Low Battery notifier updation which is followed
   by Alarm Agenda notifier updation.The Low Battery notifier is cancelled first,
   followed by Phone Ringing notifier and Alarm Agenda notifier cancellation.
   
   @SYMTestExpectedResults The message from RNotifier::UpdateNotifer() is verified
   and recorded. RNotifier::Cancel() should return KErrNone & only cancel the
   plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep13L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 13:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);

	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);

	INFO_PRINTF1(_L("Update Agenda Alarm Notifier"));
	HandleCommandL(EAppUpdateAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep14L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() ,RNotifier::CancelNotifier()
   & RNotifier::UpdateNotifier() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start Phone
   Ringing notifier followed by Alarm Agenda notifier and Low Battery
   notifier started without cancelling any plug-in notifier. The test then
   calls UpdateNotifier() to update them so that Low Battery notifier is first
   updated followed by Phone Ringing notifier and Alarm Agenda notifier
   updation. Then the Low Battery notifier is cancelled first followed by Phone 
   Ringing notifier and Alarm Agenda notifier cancellation.
   
   @SYMTestExpectedResults The message from RNotifier::UpdateNotifer() is verified
   and recorded. RNotifier::Cancel() should return KErrNone & only cancel the
   plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep14L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 14:"));
	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);
	
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);

	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);

	INFO_PRINTF1(_L("Update Agenda Alarm Notifier"));
	HandleCommandL(EAppUpdateAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep15L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() ,RNotifier::CancelNotifier()
   & RNotifier::UpdateNotifier() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifier() to start Low Battery
   notifier followed by Phone Ringing notifier and Alarm Agenda notifier
   without cancelling any plug-in notifier. The test then calls
   UpdateNotifier() to update them so that Low Battery notifier is first
   updated followed by Phone Ringing notifier and Alarm Agenda notifier
   updation.Then the Low Battery notifier is cancelled first followed by Phone 
   Ringing notifier and Alarm Agenda notifier cancellation.
   
   @SYMTestExpectedResults The message from RNotifier::UpdateNotifer() is verified
   and recorded. RNotifier::Cancel() should return KErrNone & only cancel the
   plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep15L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 15:"));
	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);
	
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Update Low Battery Notifier"));
	HandleCommandL(EAppUpdateLowBattery);

	INFO_PRINTF1(_L("Update Phone Ring Notifier."));
	HandleCommandL(EAppUpdateRingPhone);

	INFO_PRINTF1(_L("Update Agenda Alarm Notifier"));
	HandleCommandL(EAppUpdateAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep16L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifierAndGetResponse() &
   RNotifier:: CancelNotifier() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method connects to the extended notifier server and makes
   an asynchronous requests to start the Alarm Agenda plug-in notifier by
   calling RNotifier::StartNotifierAndGetResponse(). While the request is
   outstanding the test attempts to cancel the Low Battery plug-in notifier
   by calling RNotifier::CanelNotifier(). The response from CancelNotifier()
   & response message on completion of asynchronous request
   StartNotifierAndGetResponse() is observed.
   
   @SYMTestExpectedResults Test verifies that CancelNotifier returns KErrNone
   even though the notifier is not started. It also verifies and displays the
   response message on completion of asynchronous request
   StartNotifierAndGetResponse()
   
 */
void CTNotdialAppUi::TestStep16L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 16:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier Status"));
	HandleCommandL(EAppStartAgendaAlarmStatus);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep17L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test cancelling plug-in notifier started by 
   RNotifier::StartNotifierAndGetResponse() request.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method connects to the extended notifier server and makes
   an asynchronous requests to start the Alarm Agenda plug-in notifier by
   calling RNotifier::StartNotifierAndGetResponse(). Now the Low Battery
   plug-in notifier is started by calling RNotifier::StartNotifier(). The test
   now cancels the Alarm Agenda notifier followed by Low Battery notifier by
   calling RNotifier::CancelNotifier().
   
   @SYMTestExpectedResults Test verifies that RNotifier::CancelNotifier returns
   KErrNone and cancels the notifier started by asynchronous method
   RNotifier::StartNotifierAndGetResponse(). 
  
 */
void CTNotdialAppUi::TestStep17L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 17:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier Status"));
	HandleCommandL(EAppStartAgendaAlarmStatus);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep18L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test StartNotifier(), CancelNotifier() &
   StartNotifierAndGetResponse() APIs.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method initially Starts & Cancels Low Battery plug-in
   notifier. Now it starts Alarm Agenda notifer by calling
   RNotifier::StartNotifierAndGetResponse(). Now Phone Ringing notifier is
   started by calling RNotifier::StartNotifier(). Then the Alarm Agenda
   notifier is cancelled followed by cancellation of Phone Ringing notifier.
   
   @SYMTestExpectedResults Test verifies that RNotifier::CancelNotifier returns
   KErrNone and cancels the notifier started by asynchronous method
   RNotifier::StartNotifierAndGetResponse(). 
  
 */
void CTNotdialAppUi::TestStep18L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 18:"));

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);
		
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier Status"));
	HandleCommandL(EAppStartAgendaAlarmStatus);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep19L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifierAndGetResponse(), RNotifier::StartNotifier()
   & RNotifier::CancelNotifier() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::StartNotifierAndGetResponse() to
   start the Alarm Agenda notifier asynchronously. This is followed by calls
   to RNotifier::StartNotifier() to start Low Battery & Phone Ringing Notifiers
   one after the other without cancelling any plug-in notifier. The test then
   cancels them one after the other in the same order by calling
   RNotifier::CancelNotifier().
   
   @SYMTestExpectedResults RNotifier::Cancel() should return KErrNone & only
   cancel the plug-in notifier specifed by the UID.
   
 */
void CTNotdialAppUi::TestStep19L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 19:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier Status"));
	HandleCommandL(EAppStartAgendaAlarmStatus);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Start Phone Ring Notifier"));
	HandleCommandL(EAppRingPhone);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);

	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);

	INFO_PRINTF1(_L("Cancel Phone Ring Notifier"));
	HandleCommandL(EAppCancelRingPhone);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep20L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test Starting & Cancelling the SMS plug-in notifier.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test invokes RNotifier::StartNotifier() by specifying the
   UID for SMS plug-in notifier to start the notifier. Then the test cancels
   SMS notifier by invoking RNotifier::CancelNotifier().
   
   @SYMTestExpectedResults The test verifies that StartNotifier() &
   CancelNotifier() returns KErrNone on successful completion.
   
 */
void CTNotdialAppUi::TestStep20L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 20:"));
	INFO_PRINTF1(_L("Start SMS Notifier"));
	HandleCommandL(EAppNewSms);

	INFO_PRINTF1(_L("Cancel SMS Notifier"));
	HandleCommandL(EAppCancelSms);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep21L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test cancelling the SMS plug-in notifier via dialog.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the SMS plug-in notifier by calling
   RNotifier::StartNotifier. The test then connects to Windows Server
   and simulates an ENTER key event on the notifier dialog to cancel the SMS
   plug-in notifier.
   
   @SYMTestExpectedResults The simulated ENTER Key on the notifier dialog should
   cancel the SMS notifier.
  
 */
void CTNotdialAppUi::TestStep21L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 21:"));
	RWsSession ws;
	TKeyEvent event;

	INFO_PRINTF1(_L("Start SMS Notifier"));
	HandleCommandL(EAppNewSms);

	//Set up key event "enter" to simulate key enter to replace  clicking "ok" on dialog.
	event.iCode=event.iScanCode=EKeyEnter;
	event.iModifiers=event.iRepeats=0;

	//Connect to Window Server Session
	TEST(ws.Connect()==KErrNone);

	// Simulate key entry and flush the buffer to send event to windows server session.
	ws.SimulateKeyEvent(event);
	ws.Flush();
	INFO_PRINTF1(_L("Cancel SMS Notifier via dialog"));
	ws.Close();
	}

 
void CTNotdialAppUi::TestStep22L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 22:"));
	INFO_PRINTF1(_L("Start Email Notifier"));
	HandleCommandL(EAppNewEmail);

	INFO_PRINTF1(_L("Cancel Email Notifier"));
	HandleCommandL(EAppCancelEmail);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep23L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test cancelling the Email plug-in notifier via dialog.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the Email plug-in notifier by calling
   RNotifier::StartNotifier. The test then connects to Windows Server
   and simulates an ENTER key event on the notifier dialog to cancel the Email
   plug-in notifier.
   
   @SYMTestExpectedResults The simulated ENTER Key on the notifier dialog should
   cancel the Email notifier.
   
 */
void CTNotdialAppUi::TestStep23L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 23:"));
	RWsSession ws;
	TKeyEvent event;

	INFO_PRINTF1(_L("Start Email Notifier"));
	HandleCommandL(EAppNewEmail);

	//Set up key event "enter" to simulate key enter to replace  clicking "ok" on dialog.
	event.iCode=event.iScanCode=EKeyEnter;
	event.iModifiers=event.iRepeats=0;

	//Connect to Window Server Session
	TEST(ws.Connect()==KErrNone);

	// Simulate key entry and flush the buffer to send event to windows server session.
	ws.SimulateKeyEvent(event);
	ws.Flush();
	INFO_PRINTF1(_L("Cancel Email Notifier via dialog"));
	ws.Close();
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep24L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test updating the SMS notifier.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the SMS plug-in notifier by invoking
   RNotifier::StartNotifier() specifying the UID for SMS plug-in notifier.
   It then calls CTNotdialAppUi::AppUpdate() method which calls
   RNotifier::UpdateNotifier() to update the SMS plug-in notifier identified
   by its UID. The test then cancels the notifier.
   
   @SYMTestExpectedResults The response received from RNotifier::UpdateNotifier()
   is verified and displayed.
   
 */
void CTNotdialAppUi::TestStep24L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 24:"));
	INFO_PRINTF1(_L("Start SMS Notifier"));
	HandleCommandL(EAppNewSms);

	INFO_PRINTF1(_L("Update SMS Notifier."));
	HandleCommandL(EAppUpdateSms);

	INFO_PRINTF1(_L("Cancel SMS Notifier"));
	HandleCommandL(EAppCancelSms);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep25L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test updating the Email notifier.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test method starts the Email plug-in notifier by invoking
   RNotifier::StartNotifier() specifying the UID for Email plug-in notifier.
   It then calls CTNotdialAppUi::AppUpdate() method which calls
   RNotifier::UpdateNotifier() to update the Email plug-in notifier identified
   by its UID. The test then cancels the notifier.
   
   @SYMTestExpectedResults The response received from RNotifier::UpdateNotifier()
   is verified and displayed.
   
 */
void CTNotdialAppUi::TestStep25L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 25:"));
	INFO_PRINTF1(_L("Start Email Notifier"));
	HandleCommandL(EAppNewEmail);

	INFO_PRINTF1(_L("Update Email Notifier."));
	HandleCommandL(EAppUpdateEmail);

	INFO_PRINTF1(_L("Cancel Email Notifier"));
	HandleCommandL(EAppCancelEmail);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep26L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::StartNotifier() to start a plug-in notifier
   which is invalid.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test calls RNotifier::StartNotifier() by specifying an
   invalid uid for the notifier.
   
   @SYMTestExpectedResults RNotifier::StartNotifier() should return KErrNotFound
   if the UID of notifier is invalid.
   
 */
void CTNotdialAppUi::TestStep26L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 26."));
	INFO_PRINTF1(_L("Test Checking Error Code"));
	HandleCommandL(EAppCheckErrorCode);
	}

/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep27L
 
   @SYMPREQ
  
   @SYMTestCaseDesc Test to start a Low Battery Notifier using a CPeriodic Timer.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The test starts a CPeriodic Timer which invokes callback
   method KickOffBatteryNotifierL(). This callback method starts Low Battery
   notifier by calling RNotifier::StartNotifier(). 
   
   @SYMTestExpectedResults The response message from StartNotifier() is verified
   & displayed.
   
 */
	void CTNotdialAppUi::TestStep27L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 27."));
	INFO_PRINTF1(_L("Test Checking Battery On Timer Notifier "));
	HandleCommandL(EAppBatteryNotifiyOnTimer);
	}


/**
   @SYMTestCaseID UIF-TNotdialStep-TestStep28L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Test RNotifier::Notify() API.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions The method calls RNotifier::Notify() to asynchronously
   display a dialog. Then it connects to the Windows server and
   simulates an ENTER key event for the dialog to cancel it.
   
   @SYMTestExpectedResults RNotifier::Notify() should display a dialog and the
   simulated key event should cancel the dialog.
   
 */
void CTNotdialAppUi::TestStep28L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 28:"));
	RNotifier n;
	n.Connect();
	_LIT(KLine1,"Line1 - Select Button2");
	_LIT(KLine2,"Line2 - or press enter");
	_LIT(KButton1,"Button1");
	_LIT(KButton2,"Button2");
	TInt button=-1;
	TRequestStatus stat;
	INFO_PRINTF1(_L("Testing RNotifier::Notify:"));
	n.Notify(KLine1,KLine2,KButton1,KButton2,button,stat);
	// Wait for a time to allow the Notifier server to process this
	// request and display a dialog before we simulate sending an enter key press
	User::After(100000);

	RWsSession ws;
	TKeyEvent event;
	//Set up key event "enter" to simulate key enter to replace  clicking "ok" on dialog.
	event.iCode=event.iScanCode=EKeyEnter;
	event.iModifiers=event.iRepeats=0;
	TEST(ws.Connect()==KErrNone);

	// Simulate key entry and flush the buffer to send
	// event to windows server session.
	ws.SimulateKeyEvent(event);
	ws.Flush();
	INFO_PRINTF1(_L("Cancel Notifier dialog by simulating pressing the enter key"));
	ws.Close();

	// Don't test the button until we know the server has completed the request
	User::WaitForRequest(stat);
	INFO_PRINTF1(_L("Testing the enter key was pressed:"));
	TEST(button==1);
	n.Close();
	}

/**
   @SYMTestCaseID UIF-NotdialStep-TestStep29L
  
   @SYMPREQ
  
   @SYMTestCaseDesc Tests RNotifer::Notify and notification messages of different threads.
  
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions  
   To create five threads,with a time gap of 5 seconds between creation of the next thread and
   to test whether the notification messages of all the five threads are displayed
   API Calls:		
   RNotifer::Notify(const TDesC& aLine1,const TDesC& aLine2,const TDesC& aBut1,
  			const TDesC& aBut2,TInt& aButtonVal,TRequestStatus& aStatus)
   RThread::TInt Create(const TDesC& aName,TThreadFunction aFunction,
  			TInt aStackSize,RHeap* aHeap,TAny* aPtr,TOwnerType aType=EOwnerProcess)
   RThread::Resume() const
   RThread::Heap()
   RThread::Close()
   User::After(TTimeIntervalMicroSeconds32 anInterval)
  
   @SYMTestExpectedResults The notification messages of all the five threads to be displayed.
   
 */
void CTNotdialAppUi::TestStep29L()
	{
	iNotifierCounter=0;
	iMessageCounter=0;
	INFO_PRINTF1(_L(" ------------------------- Test Case 29:"));
	INFO_PRINTF1(_L("Testing Display of Queued Error Notes"));
	_LIT(KMessage1, "Note 1");
	_LIT(KMessage2, "Note 2");
	_LIT(KMessage3, "Note 3");
	_LIT(KMessage4, "Note 4");
	_LIT(KMessage5, "Note 5");
	
	iNotifierMessage[0].Set(KMessage1);
	iNotifierMessage[1].Set(KMessage2);
	iNotifierMessage[2].Set(KMessage3);
	iNotifierMessage[3].Set(KMessage4);
	iNotifierMessage[4].Set(KMessage5);
	
	// Launch a thread to pop up an error note
	RThread one;
	one.Create(KMessage1,NotifyFunc, 4096, NULL, (void*) this);
	one.Resume();
	one.Close();
	// Wait for a bit (5 secs)
	User::After(1000000);
	// Launch another thread to pop up an error note
	RThread two;
	two.Create(KMessage2,NotifyFunc, 4096, NULL, (void*) this);
	two.Resume();
	two.Close();
	// Wait for a bit more (5 secs)
	User::After(1000000);
	// Launch another thread to pop up an error note
	RThread three;
	three.Create(KMessage3,NotifyFunc, 4096, NULL, (void*) this);
	three.Resume();
	three.Close();
	// Wait for a bit more (5 secs)
	User::After(1000000);
	// Launch another thread to pop up an error note
	RThread four;
	four.Create(KMessage4, NotifyFunc, 4096, NULL, (void*) this);
	four.Resume();
	four.Close();
	// Wait for a bit more (5 secs)
	User::After(1000000);
	// Launch another thread to pop up an error note
	RThread five;
	five.Create(KMessage5, NotifyFunc, 4096, NULL, (void*) this);
	five.Resume();
	five.Close();
	// Wait for a bit more (5 secs)
	User::After(1000000);
	while(iNotifierCounter<5)
		{
		User::After(2000000);
		}
	}
	
/**
   @SYMTestCaseID UIF-NotdialStep-TestStep30L
  
   @SYMPREQ INC079968
  
   @SYMTestCaseDesc Tests activation and cancellation of Agenda Alarm, Low Battery notifier.
   					
      
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions  
   Activate the agenda alarm and low battery notifiers.
   Update then cancel the agenda alarm and low battery notifiers..
   
   
   @SYMTestExpectedResults Both notifiers are activated and cancelled susccessfully.
   						     
 */

void CTNotdialAppUi::TestStep30L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 30:"));
	INFO_PRINTF1(_L("Start Agenda Alarm Notifier"));
	HandleCommandL(EAppAgendaAlarm);

	INFO_PRINTF1(_L("Start Low Battery Notifier"));
	HandleCommandL(EAppLowBattery);

	INFO_PRINTF1(_L("Update Agenda Alarm Notifier Status"));
	HandleCommandL(EAppUpdateAgendaAlarmStatus);

	INFO_PRINTF1(_L("Cancel Agenda Alarm Notifier"));
	HandleCommandL(EAppCancelAgendaAlarm);
	
	INFO_PRINTF1(_L("Cancel Low Battery Notifier"));
	HandleCommandL(EAppCancelLowBattery);
	}

	
	/**
   @SYMTestCaseID UIF-NotdialStep-TestStep31L
  
   @SYMDEF INC079968
  
   @SYMTestCaseDesc Verifies that messages are completed if the corresponding notifier is inactive.
      
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions  
   Attempt to send a message to the inactive agenda alarm notifier. 
   Observe that the message completes i.e. the test step continues. 
  
   @SYMTestExpectedResults Messages sent to inactive notifiers complete.  
 */
void CTNotdialAppUi::TestStep31L()
	{	
	INFO_PRINTF1(_L(" ------------------------- Test Case 31:"));
	INFO_PRINTF1(_L("Update Agenda Alarm Notifier Status after it was cancelled"));
	HandleCommandL(EAppUpdateAgendaAlarmStatus);
	
	}

	/**
   @SYMTestCaseID UIF-NotdialStep-TestStep32L
  
   @SYMDEF DEF113741
  
   @SYMTestCaseDesc Verifies that attempting to cancel a notifier that doesn't exist returns the required error code
      
   @SYMTestPriority High
  
   @SYMTestStatus Implemented
   
   @SYMTestActions  
   Call RNotifier::CancelNotifier() with the UID of a notifier that hasn't been started.

  
   @SYMTestExpectedResults RNotifier::CancelNotifier() returns KErrNotFound.  
 */
void CTNotdialAppUi::TestStep32L()
	{
	INFO_PRINTF1(_L(" ------------------------- Test Case 32:"));
	INFO_PRINTF1(_L("Cancelling a notifier that hasn't been started.\n"));
	const TUid KNotifierNotExistUid = {0x1fffffff}; 
	TInt err = iNotifier.CancelNotifier(KNotifierNotExistUid);
	INFO_PRINTF4(_L("RNotifier::Cancel(%x) returned '%D', expected '%D'"), KNotifierNotExistUid.iUid, err, KErrNotFound);
	TEST(KErrNotFound == err);
	}

/**
   The method creates a session with Notifier server for each of the five threads.
   The notification message for each thread is displayed after a simulated lapse
   of 10 seconds
 */
TInt CTNotdialAppUi::NotifyFunc(TAny *aPtr)
	{
	CTNotdialAppUi* notdialAppUi=(CTNotdialAppUi*)aPtr;
	_LIT(KLine2,"Line2 - or press enter");
	_LIT(KButton1,"Button1");
	_LIT(KButton2,"Button2");
	TRequestStatus status;
	TInt response;
	RNotifier session;
	session.Connect();
	session.Notify(notdialAppUi->iNotifierMessage[notdialAppUi->iMessageCounter++], KLine2, KButton1, KButton2, response, status);
	//wait for 10 seconds and then dismiss the first queued message to check whether
	//the other queued message in the notifier server are popped up. 
	User::After(10000000);
	RWsSession ws;
	TKeyEvent event;
	//Set up key event "enter" to simulate key enter to replace  clicking "ok" on dialog.
	event.iCode=event.iScanCode=EKeyEnter;
	event.iModifiers = event.iRepeats = 0;
	
	TInt err = ws.Connect();
	if(err==KErrNone)
		{
		// Simulate key entry and flush the buffer to send event to windows server session.
		ws.SimulateKeyEvent(event);
		ws.Flush();
		ws.Close();
		}
	User::WaitForRequest(status);
	notdialAppUi->iNotifierCounter++;
	session.Close();
	return err;
	}

/**
   This method is an oveerride from CCoeAppUi. It is used to handle key events.
 */
TKeyResponse CTNotdialAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
	{
	return  EKeyWasNotConsumed;
	}

/**
   This is an override from CEikAppUi. It is used to handle user commands.
 */
void CTNotdialAppUi::HandleCommandL(TInt aCommand)
	{
	TInt ret=KErrNotFound;
	TBuf8<256> response;
	response.SetMax();

	User::After(TTimeIntervalMicroSeconds32(100000));

	CEikonEnv* eikEnv=CEikonEnv::Static();

	if (iNotifier.Handle()==KNullHandle)
		{
		User::LeaveIfError(iNotifier.Connect());
		}

	_LIT8(KMessagePhone, "Phone Ringing");
	_LIT8(KMessageBattery, "Low Battery");
	_LIT8(KMessageAgenda, "Agenda Alarm");
	_LIT8(KMessageSms, "New Sms");
	_LIT8(KMessageEmail, "New Email");

	const TUid KRubbishUid={0x11111234};

	switch (aCommand)
		{
	case EAppRingPhone:	
		ret=iNotifier.StartNotifier(iMyPhoneNotifierUid,KMessagePhone);
		INFO_PRINTF3(_L("Start Phone Notifier returned :%d MyPhoneNotifierUid[%x]"), ret, iMyPhoneNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppNewSms:
		ret=iNotifier.StartNotifier(iMySmsNotifierUid,KMessageSms,response);
		INFO_PRINTF3(_L("Start SMS Notifier returned: %d MySmsNotifierUid[%x]"), ret, iMySmsNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppNewEmail:
		ret=iNotifier.StartNotifier(iMyEmailNotifierUid,KMessageEmail,response);
		INFO_PRINTF3(_L("Start Email Notifier returned: %d MyEmailNotifierUid[%x]"), ret, iMyEmailNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppLowBattery:
		ret=iNotifier.StartNotifier(iMyLowBatteryNotifierUid,KMessageBattery,response);
		INFO_PRINTF3(_L("Start Low Battery Notifier returned: %d MyLowBatteryNotifierUid[%x]"), ret,iMyLowBatteryNotifierUid.iUid);
		TEST (ret==KErrNone);	
		break;
	case EAppAgendaAlarm:
		ret=iNotifier.StartNotifier(iMyAgendaAlarmUid,KMessageAgenda,response);
		INFO_PRINTF3(_L("Start Agenda Alarm Notifier returned: %d MyAgendaAlarmUid[%x]"), ret,iMyAgendaAlarmUid.iUid);
		TEST (ret==KErrNone);	
		break;
	case EAppCancelRingPhone:
		ret=iNotifier.CancelNotifier(iMyPhoneNotifierUid);
		INFO_PRINTF3(_L("Cancel Phone Notifier returned: %d MyPhoneNotifierUid[%x]"), ret,iMyPhoneNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppCancelSms:
		ret=iNotifier.CancelNotifier(iMySmsNotifierUid);
		INFO_PRINTF3(_L("Cancel SMS Notifier returned: %d MySmsNotifierUid[%x]"), ret,iMySmsNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppCancelEmail:
		ret=iNotifier.CancelNotifier(iMyEmailNotifierUid);
		INFO_PRINTF3(_L("Cancel Email Notifier returned: %d MyEmailNotifierUid[%x]"), ret,iMyEmailNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppCancelLowBattery:
		ret=iNotifier.CancelNotifier(iMyLowBatteryNotifierUid);
		INFO_PRINTF3(_L("Cancel Low Battery Notifier returned: %d MyLowBatteryNotifierUid[%x]"), ret,iMyLowBatteryNotifierUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppCancelAgendaAlarm:
		ret=iNotifier.CancelNotifier(iMyAgendaAlarmUid);
		INFO_PRINTF3(_L("Cancel Agenda Notifier returned: %d MyAgendaAlarmUid[%x]"), ret,iMyAgendaAlarmUid.iUid);
		TEST (ret==KErrNone);
		break;
	case EAppUpdateRingPhone:
		{
		INFO_PRINTF2(_L("Calling Phone Update MyPhoneNotifierUid[%x]"),iMyPhoneNotifierUid.iUid);
		_LIT8(KMessage, "Calling Sms Update");
		AppUpdate(iMyPhoneNotifierUid,KMessage(),eikEnv,response);
		}
		break;
	case EAppUpdateSms:
		{
		INFO_PRINTF2(_L("Calling Sms Update MySmsNotifierUid[%x]"),iMySmsNotifierUid.iUid);
		_LIT8(KMessage, "Calling Sms Update");
		AppUpdate(iMySmsNotifierUid,KMessage(),eikEnv,response);
		}
		break;
	case EAppUpdateEmail:
		{
		INFO_PRINTF2(_L("Calling Email Update MyEmailNotifierUid[%x]"),iMyEmailNotifierUid.iUid);
		_LIT8(KMessage, "Calling Email Update");
		AppUpdate(iMyEmailNotifierUid,KMessage(),eikEnv,response);
		}
		break;
	case EAppUpdateLowBattery:
		{
		INFO_PRINTF2(_L("Calling Low Battery Update MyLowBatteryNotifierUid[%x]"),iMyLowBatteryNotifierUid.iUid);
		_LIT8(KMessage, "Calling Low Battery Update");
		AppUpdate(iMyLowBatteryNotifierUid,KMessage(),eikEnv,response);
		}
		break;
	case EAppUpdateAgendaAlarm:
		{
		INFO_PRINTF2(_L("Calling Agenda Update MyAgendaAlarmUid[%x]"),iMyAgendaAlarmUid.iUid);
		_LIT8(KMessage, "Calling Agenda Update");
		AppUpdate(iMyAgendaAlarmUid,KMessage(),eikEnv,response);

		}
		break;
	case EAppStartAgendaAlarmStatus:
		{
		if (iNotifier.Handle()==KNullHandle)
			{
			User::LeaveIfError(iNotifier.Connect());
			}
		_LIT(KMessage,"Agenda:Status Request");
		_LIT(KRequestQMsg,"Agenda Alarm:Request Queued");
		_LIT(KNotifExists,"Agenda Alarm Already Exists");
		_LIT(KNotifNotFound,"Agenda Alarm notifier not found");

		TRequestStatus status=KRequestPending;
		INFO_PRINTF2(_L("StartNotifierAndGetResponse for MyAgendaAlarmUid [%x]"),iMyAgendaAlarmUid.iUid );
		
		iNotifier.StartNotifierAndGetResponse(status,iMyAgendaAlarmUid,KMessageAgenda,response);

		INFO_PRINTF2(_L(">>call cancel low battery notifier MyLowBatteryNotifierUid[%x]"),iMyLowBatteryNotifierUid.iUid);
		
		//issue new call while request pending
		TInt error=iNotifier.CancelNotifier(iMyLowBatteryNotifierUid);
		TGulAlignment messageAlignment=EHLeftVTop;
		eikEnv->InfoMsgWithAlignment(messageAlignment,KMessage);
		INFO_PRINTF3(_L("cancel low battery notifier MyLowBatteryNotifierUid[%x] returned[%d]"),iMyLowBatteryNotifierUid.iUid,error);
		User::WaitForRequest(status);
		messageAlignment=EHRightVTop;
		if (status.Int() == (TInt)EEikNotExtRequestQueued)
			{
			INFO_PRINTF1(_L(">>request queued"));
			eikEnv->InfoMsgWithAlignment(messageAlignment,KRequestQMsg);
			}
		else if (status.Int() == (TInt)KErrAlreadyExists)
			{
			INFO_PRINTF1(_L(">>notifier exists"));
			eikEnv->InfoMsgWithAlignment(messageAlignment,KNotifExists);
			}
		else if(status.Int() == (TInt)KErrNone)
			{
			INFO_PRINTF1(_L(">>request completed successfully"));
			TBuf<256> buffer;
			buffer.Copy(response);
			INFO_PRINTF1(buffer);
			eikEnv->InfoMsgWithAlignment(messageAlignment,buffer);
			}
		else if(status.Int() == (TInt)KErrNotFound)
			{
			INFO_PRINTF1(KNotifNotFound);
			}
		else
			{
			INFO_PRINTF2(_L("************ request completed with an error: %d"), status.Int());
			}
		}
		break;
	case EAppUpdateAgendaAlarmStatus:
		{
		_LIT(KNotifNotFound,"Agenda Alarm notifier not found");
		_LIT(KRequestQMsg,"Agenda Alarm:Request Queued");
		_LIT(KMessage,"Agenda:Status Request");
		_LIT(KNotifNotReady,"Agenda Alarm notifier not ready");

		TRequestStatus status=KRequestPending;
		INFO_PRINTF2(_L("UpdateNotifierAndGetResponse for MyAgendaAlarmUid [%x]"),iMyAgendaAlarmUid.iUid);
		iNotifier.UpdateNotifierAndGetResponse(status,iMyAgendaAlarmUid,KMessageAgenda,response);
		TGulAlignment messageAlignment=EHLeftVTop;
		eikEnv->InfoMsgWithAlignment(messageAlignment, KMessage);
		
		INFO_PRINTF1(_L("Update Low Battery Notifier"));
		HandleCommandL(EAppUpdateLowBattery); 

		User::WaitForRequest(status);
		if(status.Int() == (TInt)EEikNotExtRequestQueued)
			{
			INFO_PRINTF1(_L(">>request queued"));
			eikEnv->InfoMsgWithAlignment(messageAlignment, KRequestQMsg);
			}
		else if (status.Int() == (TInt) KErrNone)
			{
			INFO_PRINTF1(_L(">>request completed successfully"));
			TBuf<256> buffer;
			buffer.Copy(response);
			INFO_PRINTF1(buffer);
			eikEnv->InfoMsgWithAlignment(messageAlignment, buffer);
			}
		else if (status.Int() == (TInt) KErrNotFound)
			{
			INFO_PRINTF1(KNotifNotFound);
			}
		else if(status.Int() == (TInt)KErrNotReady)
			{
			INFO_PRINTF1(KNotifNotReady);
			}
		else
			{
			INFO_PRINTF2(_L("************ request completed with an error: %d"), status.Int());
			}
		}
		break;
	case EAppStartEmailStatus:
		{
		if (iNotifier.Handle()==KNullHandle)
			{
			User::LeaveIfError(iNotifier.Connect());
			}
		_LIT(KEmailMessage,"Email:Status Request");
		_LIT(KEmailRequestQMsg,"Email :Request Queued");
		_LIT(KEmailNotifExists,"Email  Already Exists");
		_LIT(KEmailNotFound,"Email Notifier not found");
		
		TRequestStatus status=KRequestPending;

		INFO_PRINTF2(_L("StartNotifierAndGetResponse for MyEmailNotifierUid [%x]"),iMyEmailNotifierUid.iUid );
		iNotifier.StartNotifierAndGetResponse(status,iMyEmailNotifierUid,KMessageEmail,response);
		
		INFO_PRINTF2(_L(">>call cancel low battery notifier MyLowBatteryNotifierUid[%x]"),iMyLowBatteryNotifierUid.iUid);
		
		//issue new call while request pending
		TInt error = iNotifier.CancelNotifier(iMyLowBatteryNotifierUid);
		TGulAlignment messageAlignment=EHLeftVTop;
		eikEnv->InfoMsgWithAlignment(messageAlignment,KEmailMessage);
		INFO_PRINTF3(_L(">>call cancel low battery notifier MyLowBatteryNotifierUid[%x]"),iMyLowBatteryNotifierUid.iUid,error);

		RWsSession ws;
		TKeyEvent event;

		//Set up key event "enter" to simulate key enter to replace 
		//clicking "ok" on dialog.
		event.iCode=event.iScanCode=EKeyEnter;
		event.iModifiers=event.iRepeats=0;

		//Connect to Window Server Session
		TEST(ws.Connect()==KErrNone);

		// Simulate key entry and flush the buffer to send event to windows server session.
		ws.SimulateKeyEvent(event);
		ws.Flush();
		INFO_PRINTF1(_L("Cancelled Email Status Notifier via dialog"));
		ws.Close();

		messageAlignment=EHRightVTop;
		TInt statusValue=status.Int();
		if (statusValue == (TInt)EEikNotExtRequestQueued)
			{
			INFO_PRINTF1(_L(">>request queued"));
			eikEnv->InfoMsgWithAlignment(messageAlignment,KEmailRequestQMsg);
			}
		else if (statusValue == (TInt)KErrAlreadyExists)
			{
			INFO_PRINTF1(_L(">>notifier exits"));
			eikEnv->InfoMsgWithAlignment(messageAlignment,KEmailNotifExists);
			}
		else if(statusValue == (TInt)KErrNone) 
			{
			INFO_PRINTF1(_L(">>request completed successfully"));
			TBuf<256> buffer;
			buffer.Copy(response);
			INFO_PRINTF1(buffer);
			eikEnv->InfoMsgWithAlignment(messageAlignment,buffer);
			}
		else if(statusValue == (TInt)KErrNotFound)
			{
			INFO_PRINTF1(KEmailNotFound);
			}
		else  
			{
			INFO_PRINTF2(_L("************ request completed with an error: %d"),statusValue);
			}
			
		}
		
		break;
	case EAppUpdateEmailStatus:
		{
		_LIT(KNotifNotFound,"Email notifier not found");
		_LIT(KRequestQMsg,"Email:Request Queued");
		_LIT(KMessage,"Email:Status Request");

		TRequestStatus status=KRequestPending;
		INFO_PRINTF2(_L("UpdateNotifierAndGetResponse for MyEmailUid [%x]"),iMyEmailNotifierUid.iUid);
		iNotifier.UpdateNotifierAndGetResponse(status,iMyEmailNotifierUid,KMessageEmail,response);
		TGulAlignment messageAlignment=EHLeftVTop;
		eikEnv->InfoMsgWithAlignment(messageAlignment, KMessage);

		INFO_PRINTF1(_L("Update Low Battery Notifier"));
		HandleCommandL(EAppUpdateLowBattery);

		User::WaitForRequest(status);
		if(status.Int() == (TInt)EEikNotExtRequestQueued)
			{
			INFO_PRINTF1(_L(">>request queued"));
			eikEnv->InfoMsgWithAlignment(messageAlignment, KRequestQMsg);
			}
		else if (status.Int() == (TInt) KErrNone)
			{
			INFO_PRINTF1(_L(">>request completed successfully"));
			TBuf<256> buffer;
			buffer.Copy(response);
			INFO_PRINTF1(buffer);
			eikEnv->InfoMsgWithAlignment(messageAlignment, buffer);
			}
		else if (status.Int() == (TInt) KErrNotFound)
			{
			INFO_PRINTF1(KNotifNotFound);
			}
		else
			{
			INFO_PRINTF2(_L("************ request completed with an error: %d"), status.Int());
			}
		}
		break;
	case EAppBatteryNotifiyOnTimer:
		{
		TTimeIntervalMicroSeconds32 delay(3000000);
		TTimeIntervalMicroSeconds32 repeat(0);
		if (!iBattTimer->IsActive())
			iBattTimer->Start(delay,repeat,(TCallBack(&KickOffBatteryNotifierL,this)));
		}
		break;
	case EAppCheckErrorCode:
		{
		// Specific test for DEF022326 - RNotifier can start a notifier that doesn't exist
		if (iNotifier.StartNotifier(KRubbishUid,KMessagePhone,response)==KErrNotFound)
			{
			INFO_PRINTF1(_L("Rubbish Notifer Not Found"));
			}
		}
		break;
		}
	}

/**
   This is a callback method for CPeriodic Timer, iBattTimer. The method
   invokes RNotifier::StartNotifier() to start Low Battery plug-in notifier.
 */
TInt CTNotdialAppUi::KickOffBatteryNotifierL(TAny* aSimpleAppUi)
	{
	CTNotdialAppUi* appUi=STATIC_CAST(CTNotdialAppUi*,aSimpleAppUi);
	TBuf8<256> response;
	response.SetMax();
	_LIT8(KMessageBattery, "Low Battery on Timer");
	if (appUi->iNotifier.Handle()==KNullHandle)
		{
		User::LeaveIfError(appUi->iNotifier.Connect());
		}
	appUi->iNotifier.StartNotifier(appUi->iMyLowBatteryNotifierUid,KMessageBattery,response);
	appUi->iBattTimer->Cancel();
	return 0;
	}


/**
   The method updates a plug-in notifier specified by UID aNotifierUid with
   message aMessage by calling RNotifier::UpdateNotifier(). The method then
   verifies the response aResponse and displays it.
 */
void CTNotdialAppUi::AppUpdate(TUid aNotifierUid, const TDesC8& aMessage, CEikonEnv* aEikEnv, TDes8& aResponse)
	{
	_LIT8(KPluginResponse, "Response:");
	_LIT(KNoPluginUpdate,"No Update from Plugin");

	iNotifier.UpdateNotifier(aNotifierUid,aMessage,aResponse);
	if (aResponse.Find(KPluginResponse)!=0)
		{
		aEikEnv->InfoMsgWithAlignment(EHRightVBottom, KNoPluginUpdate);
		}
	else
		{
		TBuf<256> buffer;
		buffer.Copy(aResponse);
		INFO_PRINTF1(buffer);
		aEikEnv->InfoMsgWithAlignment(EHRightVBottom, buffer);
		}
	}

/**
   The method creates & sets the application's user interface object.
 */
void CTNotdialStep::ConstructAppL(CEikonEnv* aEikEnv)
    { // runs inside a TRAP harness
	INFO_PRINTF1(_L("CTNotdialStep::ConstructAppL"));
	aEikEnv->ConstructL();
	CTNotdialAppUi* appUi=new(ELeave) CTNotdialAppUi(this);
	INFO_PRINTF1(_L("SetAppUi"));
	aEikEnv->SetAppUi(appUi);
	appUi->ConstructL();
    }

CTNotdialStep::CTNotdialStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTNotdialStep);
	}

CTNotdialStep::~CTNotdialStep()
	{
	}

TVerdict CTNotdialStep::doTestStepPreambleL()
	{
	SetTestStepResult(EPass);
	return TestStepResult();
	}

TVerdict CTNotdialStep::doTestStepPostambleL()
	{
	return TestStepResult();
	}

TVerdict CTNotdialStep::doTestStepL()
	{
	PreallocateHALBuffer();

	__UHEAP_MARK;
	INFO_PRINTF1(_L("Start TNotdial test cases (TESTING V2 NOTIFIERS)...."));
	CEikonEnv* eikEnv=new(ELeave) CEikonEnv;
	TRAPD(err,ConstructAppL(eikEnv));
	if (!err)
		{
		eikEnv->ExecuteD();
		}
	else
		{
		SetTestStepResult(EFail);
		User::Leave(err);
		}	
	
	REComSession::FinalClose();	
	__UHEAP_MARKEND;
	
	INFO_PRINTF1(_L("...TNotdial test completed!"));
	return TestStepResult();
	}
