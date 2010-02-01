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

#include <asaltdefs.h>
#include "ASAltClientSession.h"

#include "TMultipleAlarmStep.h"

//
//


static TBool CompareAlarm(TInt aOffset, TInt aLength, const TDesC8& aDesc, const TDesC8& aSubDesc)
	{
	for (TInt i = 0; i < aLength; ++i)
		{
		if (aDesc[i + aOffset] != aSubDesc[i])
			{
			return EFalse;
			}
		}
		
	return ETrue;
	}

//
//


CTMultipleAlarmStep::~CTMultipleAlarmStep()
	{
	iDataArray.Close();
	}

CTMultipleAlarmStep::CTMultipleAlarmStep()
	{
	// Call base class method to set up the human readable name for logging
	SetTestStepName(KTMultipleAlarm);
	}

TVerdict CTMultipleAlarmStep::doTestStepPreambleL()
	{
	SetTestStepResult(EPass);
	return TestStepResult();
	}

TVerdict CTMultipleAlarmStep::doTestStepPostambleL()
	{
	return TestStepResult();
	}

void CTMultipleAlarmStep::StartAlertServerL(const TInt aMaxAlarms)
	{
	LaunchServerL(aMaxAlarms, EFalse, 0, 0, Time::NullTTime(), 0, EFalse, 0);
	}

void CTMultipleAlarmStep::StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse)
	{
	LaunchServerL(aMaxAlarms, ETrue, aId, aResponse, Time::NullTTime(), 0, EFalse, 0);
	}
	
void CTMultipleAlarmStep::StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse, const TTime& aTime)
	{
	LaunchServerL(aMaxAlarms, ETrue, aId, aResponse, aTime, 0, EFalse, 0);
	}

void CTMultipleAlarmStep::StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse, const TTime& aTime, TInt aSnoozeTime, TBool aUpdateSnooze,TInt aInitialState)
	{
	LaunchServerL(aMaxAlarms, ETrue, aId, aResponse, aTime, aSnoozeTime, aUpdateSnooze, aInitialState);
	}

void CTMultipleAlarmStep::StopAlertServer()
	{
	iMsgQ.Close();
	iServer.Terminate(KErrCancel);
	iServer.Close();
	}

void CTMultipleAlarmStep::LaunchServerL(const TInt aMaxAlarms, const TBool aReplies, const TAlarmId aId, const TInt aResponse, const TTime& aTime, TInt aSnoozeTime, TBool aUpdateSnooze, TInt aInitialState)
	{
	User::LeaveIfError(iMsgQ.CreateGlobal(KRemoteQName, KRemoteQSize, EOwnerThread));

	// UID of console alarm alert server
	const TUid KServerUid2={0x1000008D};
	const TUid KServerUid3={0x1020E043};
	const TUidType serverUid(KNullUid,KServerUid2,KServerUid3);
	_LIT(KTAlertServerImg, "TAlertServer");

	INFO_PRINTF2(_L("Starting Alert Server with max alarms: %i"), aMaxAlarms);
	SendInt(aMaxAlarms);
	SendInt(aInitialState);
	SendBool(aReplies);
	
	if(aReplies) 
		{
		TBuf<12> buf;
		aTime.FormatL(buf, _L("%H:%T:%S"));
		INFO_PRINTF4(_L("response id: %i op-code: %i time: %s"), aId, aResponse, buf.PtrZ());
		SendInt(aId);
		SendInt(aResponse);
		
		SendInt(aSnoozeTime);
		SendBool(aUpdateSnooze);
			
		SendInt(I64HIGH(aTime.Int64()));
		SendInt(I64LOW(aTime.Int64()));
		}
	
   	User::LeaveIfError(iServer.Create(KTAlertServerImg, KNullDesC, serverUid));
	iServer.Resume();	// logon OK - start the server
	
	// Wait for the Alert Server to start up	
	User::After(1000000);
	}

void CTMultipleAlarmStep::SendInt(const TInt aValue)
	{
	TRemoteMsg msg(aValue);
	iMsgQ.SendBlocking(msg);
	}

void CTMultipleAlarmStep::SendBool(const TBool aValue)
	{
	TRemoteMsg msg(aValue);
	iMsgQ.SendBlocking(msg);
	}
	
TInt CTMultipleAlarmStep::ReadInt()
	{
	TRemoteMsg msg;
	iMsgQ.ReceiveBlocking(msg);
	return msg.Int();
	}
	
TInt CTMultipleAlarmStep::ReadIntL()
	{
	TRemoteMsg msg;
	User::LeaveIfError(iMsgQ.Receive(msg));
	return msg.Int();
	}
	
void CTMultipleAlarmStep::ReadData(TDes8& aBuffer)
	{
	TRemoteMsg msg;
	iMsgQ.ReceiveBlocking(msg);
	
	aBuffer.Copy(msg.Data(), KRemoteQMaxDataSize);
	}

void CTMultipleAlarmStep::ResetConfigValues()
	{
	iMaxAlarms = 0;
	iAlarmCount = 0;
	iInitialState = 0;
	iId = 0;
	iState = 0;
	iQuietTime = 0;

	iDataArray.Reset();

	iResponse = 0;
	iSnoozeTime = 0;
	iQueueResponse = 0;
	iCancelNotify = EFalse;
	iNoResponse = EFalse;
	iWaitForUpdate = EFalse;
	iTime.HomeTime();
	
	iPauseTime = 0;
	iExpectedSnoozeTime = 0;
	iAction = 0;
	}

//
//


void CTMultipleAlarmStep::MaxAlarmTestL()
	{
	INFO_PRINTF2(_L("Testing MaxAlarm with MaxAlarm=%d"), iMaxAlarms);
	TEST(iMaxAlarms > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	TInt ret = 0;
	session.GetMaxNumberOfAlarms(ret);		
	TEST(ret == iMaxAlarms);
	
	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}


/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-351
 */

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-352

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Alarm Server in SAN and MAN mode. 
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Create Alert Server by invoking CEikServAlarmAlertServer::NewL(MEirkServAlarmFactory*) with aMaxAlarms 1 and 5;
				   Create RASAltClientSession, call GetMaxNumberOfAlarms().
   
   @SYMTestExpectedResults RASAltClientSession::GetMaxNumberOfAlarms() returns 1 and 5.    
 */
void CTMultipleAlarmStep::DoMaxAlarmTestL()
	{
	// Test with MaxAlarm = 1
	iMaxAlarms = 1;
	MaxAlarmTestL();
	
	// Test with MaxAlarm = 5
	iMaxAlarms = 5;
	MaxAlarmTestL();
	}

//
//


TInt CTMultipleAlarmStep::AddAlarmsL(RASAltClientSession& aSession)
	{
	for(TInt i = 0; i < iAlarmCount; ++i) 
		{
		TBufC8<1> data;
		TInt ret = AddAlarmL(aSession, TAlarmId(i + 1), data);
		if(ret == KErrNotFound && i >= iMaxAlarms) 
			{
			continue; // Expected result, since iAlarmCount is bigger than iMaxAlarms
			}
		else if(ret != KErrNone) 
			{
			return ret;
			}
		}
	return KErrNone;	
	}


TInt CTMultipleAlarmStep::AddAlarmL(RASAltClientSession& aSession, const TAlarmId aId, const TDesC8& aData)
	{
	TFullName name;

	TTAlarm alarm;
	alarm.Id() = aId;
	
	if(aData.Size() > 0)
		{
		alarm.SetHasAssociatedData(ETrue);
		}
		
	if(alarm.Id() % 2)
		{
		TTime now;
		now.UniversalTime();
		alarm.NextDueTime() = now;
		alarm.OriginalExpiryTime() = now;
		}
	else
		{
		alarm.NextDueTime() = Time::NullTTime();
		alarm.OriginalExpiryTime() = Time::NullTTime();
		}
		
	INFO_PRINTF2(_L("Adding alarm with id: %i"), alarm.Id());	
	
	TRequestStatus status;
	aSession.SetAlarm(status, alarm, name, aData);
	User::WaitForRequest(status);
	if (status.Int() == KErrNone) 
		{
		// Make sure the correct alarm was added	
		if(ReadIntL() != EASAltOpCodeSetAlarm || ReadIntL() != aId)
			{
			INFO_PRINTF1(_L("Mismatched SetAlarm return"));
			return KErrUnknown;
			}
		
		TInt dataSize = ReadIntL();
		while(dataSize > 0) // There is data associated with alarm
			{
			TBuf8<KRemoteQMaxDataSize> buf;
			ReadData(buf);
			
			TInt length = dataSize > KRemoteQMaxDataSize ? KRemoteQMaxDataSize : dataSize;
			if(!CompareAlarm(aData.Length() - dataSize, length, aData, buf))
				{
				INFO_PRINTF1(_L("Mismatched SetAlarm data"));
				return KErrUnknown;	
				}
			dataSize -= KRemoteQMaxDataSize;			
			}

		TInt opCode = ReadIntL();
		TInt state =  ReadIntL();
		TInt id =  ReadIntL();

		if(opCode != EASAltOpCodeSetState || state != iInitialState || id != aId)
	   		{
	   		INFO_PRINTF1(_L("Mismatched SetState return"));
	   		return KErrUnknown;	
	   		}
		}
	
	return status.Int();
	}


void CTMultipleAlarmStep::AddAlarmTestL()
	{
	INFO_PRINTF3(_L("Testing AddAlarm with MAxAlarms=%d, and AlarmCount=%d"), iMaxAlarms, iAlarmCount);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);

	if(iDataArray.Count() > 0)
		{
		for(TInt i = 0; i < iAlarmCount; ++i)
			{
			TAlarmData data(i + 1);
			TInt index = iDataArray.FindInOrder(data, TLinearOrder<TAlarmData>(TAlarmData::Compare));
			TBuf8<256> value;
			
			if(index != KErrNotFound) 
				{
				value.Copy(iDataArray[index].iData);
				}
			
			TEST(AddAlarmL(session, i + 1, value) == KErrNone);
			}
		}
	else 
		{
		TEST(AddAlarmsL(session) == KErrNone); 
		}

	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-354
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-AD-AltS-241
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-AD-AltS-242

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Alarm Server maxAlarms and Retrieve AD.
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Start Alert Server specifying aMaxAlarms equal to 3;
				       Call RASAltClientSession::SetAlarm() fifty (50) times;
				   (2) Register 1 alarm with expiry time and associated data;
				   (3) Register 3 alarms with expiry time and associated data;
   
   @SYMTestExpectedResults (1) Number of alarms objects: 3.
   						   (2 & 3) Is possible to retrieve the Associated Data for the alarm;
						           Data retrieved matches the data supplied at the time when the alarm was registered.   
 */
void CTMultipleAlarmStep::DoAddAlarmTestL()
	{
	// Add alarm with no data associated
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-354"));
	iMaxAlarms = 3;
	iAlarmCount = 50;
	AddAlarmTestL();
	RecordTestResultL();
	
	// Add alarm with data
	SetTestStepID(_L("UIF-UCT-PREQ1118-AD-AltS-241"));
	iMaxAlarms = 1;
	iAlarmCount = 1;
	iDataArray.AppendL(TAlarmData(1, _L("Data For Alarm 0")));
	AddAlarmTestL();
	RecordTestResultL();

	// Add alarm with data
	SetTestStepID(_L("UIF-UCT-PREQ1118-AD-AltS-242"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iDataArray.AppendL(TAlarmData(1, _L("Data For Alarm 0")));
	iDataArray.AppendL(TAlarmData(2, _L("")));
	iDataArray.AppendL(TAlarmData(3, _L("Data For Alarm 2 And some filler because to see what happens when I send larger pieces of data.")));
	AddAlarmTestL();
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}

//
//

void CTMultipleAlarmStep::DelAlarmTestL(const TInt aDeleteAll)
	{
	INFO_PRINTF2(_L("Testing DeleteAlarm with AlarmId=%d"), iId);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);
	
	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 
	
	// Delete alarm
	if (aDeleteAll)
		{
		session.DeleteAlarm();		
		}
	else
		{
		session.DeleteAlarm(iId);
		}
	
	// Void return by method, but KNullAlarmId is an invalid id we assume we pass 
	// (KErrNotFound is actually returned in the message but it doesn't propagate).
	if(iId != KNullAlarmId && iMaxAlarms > 1) 
		{
		if (aDeleteAll)
			{
			for (TInt i =0; i< iAlarmCount; i++)
				{
				User::After(10000);
				TInt id = ReadInt();
				TEST(id == i+1);
				INFO_PRINTF2(_L("Alarm %d deleted"), id);
				}
			}
		else
			{
			TEST(ReadInt() == iId);
			INFO_PRINTF2(_L("Alarm %d deleted"), iId);
			}
		}
		
	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-369
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-370
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-379

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Delete Alarm. 
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in SAN mode;
					   create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data; 
					   delete alarm #2
   				   (2) Alert Server in MAN mode;
					   create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
					   delete alarm #2
   				   (3) Alert Server in MAN mode;
					   create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
					   delete alarm with invalid id.
   
   @SYMTestExpectedResults (1 & 2) Alarm #2 is deleted.
   						   (3) No alarm is deleted.
 */
void CTMultipleAlarmStep::DoDelAlarmTestL()
	{
	// Delete alarm #2 in SAN mode
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-369"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 1;
	DelAlarmTestL();
	RecordTestResultL();
	
	// Delete alarm #2 in SAN mode
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-370"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	DelAlarmTestL();
	RecordTestResultL();

	// Delete an invalid alarm id
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-379"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 0;
	DelAlarmTestL();
	RecordTestResultL();
	
	// Delete all alarms
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	DelAlarmTestL(1);

	CloseTMSGraphicsStep();
	}

//
//

void CTMultipleAlarmStep::SoundTestL()
	{
	INFO_PRINTF2(_L("Testing Sound with AlarmId=%d"), iId);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	_LIT(KSoundFile, "Sound File\0"); // Zero terminate to simplify logging.

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 
	
	// Start playing sound
	session.StartPlayingSound(KSoundFile, iId);
	INFO_PRINTF1(_L("Testing that Alarm id and op-code match after StartPlayingSound"));
	TEST(ReadInt() == EASAltOpCodeStartPlayingSound && ReadInt() == iId);

	TBuf8<KRemoteQMaxDataSize> data;
	ReadData(data);
	
	TBuf<KRemoteQMaxDataSize> buf;
	buf.Copy(data);
	
	TBuf<KRemoteQMaxDataSize> cmp(KSoundFile);
	
	TEST(buf.Compare(cmp));
	INFO_PRINTF3(_L("Testing Alarm sound file name match, expected: '%s', got: '%s'"), KSoundFile().Ptr(), buf.Ptr());

	// Stop playing sound
	session.StopPlayingSound(iId);
	INFO_PRINTF1(_L("Testing that Alarm id and op-code match after StopPlayingSound"));
	TEST(ReadInt() == EASAltOpCodeStopPlayingSound && ReadInt() == iId);

	session.StopPlayingSound();	
	if(iMaxAlarms > 1)
		{
		for (TInt i = 0; i < iMaxAlarms; ++i)
			{
			TEST(ReadInt() == EASAltOpCodeStopPlayingSound && ReadInt() == (i + 1));
			}
		}
	else 
		{
		TEST(ReadInt() == EASAltOpCodeStopPlayingSound && ReadInt() == iId);
		}

	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-355
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-356

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc StartPlayingSound specified alarm MAN and SAN
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in MAN mode; 
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call StartPlayingSound() for the 2nd alarm;
					   Call StopPlayingSound() for the 2nd alarm;
				   (2) Start Alert Server in SAN mode;
					   create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call StartPlayingSound();
					   Call StartPlayingSound(.., aAlarmID) with aAlarmID = ID of the 2nd alarm;
					   Call StopPlayingSound();
   
   @SYMTestExpectedResults (1) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the 2nd alarm exactly, 
							   and the state of the other two alarms (1st and 3rd) is not affected.
						   (2) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the alarm 1, 
						   	   Regardless of the ID supplied. 
						   	   The calls for the 2nd and 3rd alarms should be dropped by the Alarm Server.
 */
void CTMultipleAlarmStep::DoSoundTestL()
	{
	// Sound test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-355"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	SoundTestL();
	RecordTestResultL();
	
	// Sound test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-356"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 3;
	SoundTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::VisibleTestL()
	{
	INFO_PRINTF2(_L("Testing Visibility with AlarmId=%d"), iId);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 
	
	// Set visibility true
	session.SetVisibility(ETrue, iId);
	INFO_PRINTF1(_L("Checking AlarmId, op-code and visiblity match after setting visibility ON"));
	TEST(ReadInt() == EASAltOpCodeVisible && ReadInt() == iId && TTrue(ReadInt()) == ETrue);

	// Set visibility false
	session.SetVisibility(EFalse, iId);
	INFO_PRINTF1(_L("Checking AlarmId, op-code and visiblity match after setting visibility OFF"));;
	TEST(ReadInt() == EASAltOpCodeVisible && ReadInt() == iId && TTrue(ReadInt()) != ETrue);
	

	session.SetVisibility(EFalse);
	if(iMaxAlarms > 1)
		{
		for (TInt i = 0; i < iMaxAlarms; ++i)
			{
			TEST(ReadInt() == EASAltOpCodeVisible && ReadInt() == (i + 1) && ReadInt() == EFalse);
			}
		}
	else 
		{
		TEST(ReadInt() == EASAltOpCodeVisible && ReadInt() == iId && ReadInt() == EFalse);
		}
			
	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-357
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-358

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc SetVisibility in mode MAN and SAN
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in MAN mode; 
    				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call SetVisibility(ETrue, aAlarmId) for the 2nd alarm;
					   Call SetVisibility(EFalse, aAlarmId) for the 2nd alarm;
				   (2) Start Alert Server in SAN mode;
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call SetVisibility(ETrue);
					   Call SetVisibility(EFalse, aAlarmID) with aAlarmID = ID of the 2nd alarm;
					   Call SetVisibility(EFalse);
   
   @SYMTestExpectedResults (1) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the 2nd alarm exactly, 
							   and the state of the other two alarms (1st and 3rd) is not affected.

						   (2) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the alarm 1,
							   regardless of the ID supplied. 
							   The calls for the 2nd and 3rd alarms should be dropped by the Alarm Server.
 */
void CTMultipleAlarmStep::DoVisibleTestL()
	{
	// Visibility test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-357"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	VisibleTestL();
	RecordTestResultL();
	
	// Visibility test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-358"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 3;
	VisibleTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::StateTestL()
	{
	INFO_PRINTF2(_L("Testing State with AlarmId=%d"), iId);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 
	
	// Set State
	session.SetAlertServerState(iState, iId);
	INFO_PRINTF1(_L("Checking that AlarmId, state and op-code match"));
	TEST(ReadInt() == EASAltOpCodeSetState && ReadInt() == iState && ReadInt() == iId);
		
	
	session.SetAlertServerState(iState);
	if(iMaxAlarms > 1)
		{
		for (TInt i = 0; i < iMaxAlarms; ++i)
			{
			TEST(ReadInt() == EASAltOpCodeSetState && ReadInt() == iState && ReadInt() == (i + 1));
			}	
		}
	else 
		{
		TEST(ReadInt() == EASAltOpCodeSetState && ReadInt() == iState && ReadInt() == iId);
		}
	
	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-359
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-360

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc SetAlertState MAN and SAN
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in MAN mode; 
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call SetAlertState(..., aAlarmId) for the 2nd alarm, check alarm flags
				   (2) Start Alert Server in SAN mode;
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
					   Call SetAlertState(..., aAlarmID) with aAlarmID = ID of the 2nd alarm;
					   Call SetAlertState(...).

   @SYMTestExpectedResults (1) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the 2nd alarm exactly, 
							   and the state of the other two alarms (1st and 3rd) is not affected
						   (2) Verify through MEikServAlarm and CEikAlmControlSupervisor that the action is taken for the alarm 1, 
							   regardless of the ID supplied. 
							   The calls for the 2nd and 3rd alarms should be dropped by the Alarm Server.
 */
void CTMultipleAlarmStep::DoStateTestL()
	{
	// State test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-359"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iState = 3;
	StateTestL();
	RecordTestResultL();
	
	// State test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-360"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 3;
	iState = 3;
	StateTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::QuietTestL()
	{
	INFO_PRINTF2(_L("Testing Quiet with QuietTime=%d"), iQuietTime);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 

	TTime now;
	now.UniversalTime();
	now += TTimeIntervalSeconds(iQuietTime);
	
	// Set Quiet period
	session.SetQuietPeriod(now);
	
	TRequestStatus status;
	TPckgBuf<TTime> pTime;
	
	session.TimeWhenQuietPeriodShouldEnd(status, pTime);
	User::WaitForRequest(status);
	if(status.Int() != KErrNone || pTime() != now)
		{
		TBuf<12> nowBuf;
		TBuf<12> timeBuf;
		pTime().FormatL(timeBuf, _L("%H:%T:%S"));
		now.FormatL(nowBuf, _L("%H:%T:%S"));
		
		INFO_PRINTF4(_L("Expected status: 'KErrNone', got '%i', expected time: '%s', got: '%s'"), status.Int(), nowBuf.PtrZ(), timeBuf.PtrZ());
		TEST(EFalse);
		}
	
	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-361

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc SetQuietPeriod
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Alert Server in MAN mode;
				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
				   Call SetQuietPeriod().

   @SYMTestExpectedResults Verify through MEikServAlarm and CEikAlmControlSupervisor that all alarm sounds have been silenced.
 */
void CTMultipleAlarmStep::DoQuietTestL()
	{
	// Quiet test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-361"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iQuietTime = 5;
	QuietTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::NotifyTestL()
	{
	INFO_PRINTF2(_L("Testing Notify with Response=%d"), iResponse);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	if(iCancelNotify)
		{
		StartAlertServerL(iMaxAlarms);
		}
	else if(iResponse == ETestActionSetQuietPeriod)
		{
		StartAlertServerL(iMaxAlarms, iId, iResponse, iTime);
		}
	else if(iResponse == EASAltAlertServerResponseSnooze || iResponse == EASAltAlertServerResponsePauseSound)
		{
		StartAlertServerL(iMaxAlarms, iId, iResponse, Time::NullTTime(), iSnoozeTime, iWaitForUpdate, 0);
		}
	else 
		{
		StartAlertServerL(iMaxAlarms, iId, iResponse);
		}
		
	RASAltClientSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);
	
	TRequestStatus status;
	TTime time;
	TAlarmId id;
	
	if(!iQueueResponse)
		{
		session.NotifyOnResponse(status, time, id);
		}

	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 
	
	if(iResponse == ETestActionTaskKey) // Alarm needs to be visible for response to be sent.
		{
		session.SetVisibility(ETrue, iId);
		INFO_PRINTF1(_L("Checking that AlarmId, op-code and visiblity match"));
		TEST(ReadInt() == EASAltOpCodeVisible && ReadInt() == iId && TTrue(ReadInt()) == ETrue);
		}
	
	if(iCancelNotify)
		{
		session.NotifyOnResponseCancel();
		if(status.Int() != iResponse)
			{
			INFO_PRINTF3(_L("Response doesn't match! response: '%i' != '%i'"), status.Int(), iResponse);	
			TEST(EFalse);
			}
		}
	else if(!iNoResponse) // Action in the alert server generates a response
		{
		if(iQueueResponse)
			{
			session.NotifyOnResponse(status, time, id);
			}
		
		// wait for notification.
		User::WaitForRequest(status);
		TAlarmId checkId = (iResponse == EASAltAlertServerResponseClearAll ||
							iResponse == KErrCancel ||
							iResponse == ETestActionSetQuietPeriod) ? KNullAlarmId : iId;
		
		if(iResponse == ETestActionTaskKey) // We should receive a snooze alarm
			{
			iResponse = EASAltAlertServerResponseSnooze;
			}
			
		else if(iResponse == ETestActionSetQuietPeriod)
			{
			iResponse = EASAltAlertServerResponseQuietPeriod;
			
			TRequestStatus quietStatus;
			TPckgBuf<TTime> pTime;
	
			session.TimeWhenQuietPeriodShouldEnd(quietStatus, pTime);
			User::WaitForRequest(quietStatus);
			
			if(pTime() != iTime)
				{
				TBuf<12> buf1;
				TBuf<12> buf2;
				
				iTime.FormatL(buf1, _L("%H:%S:%T"));
				time.FormatL(buf2, _L("%H:%S:%T"));
				INFO_PRINTF3(_L("Quiet period doesn't match, expected: %s got: %s"), buf1.PtrZ(), buf2.PtrZ());
				TEST(EFalse);
				}
			}
	
		if(status.Int() != iResponse ||
			id != checkId)
			{
			INFO_PRINTF5(_L("Response or id doesn't match! id: %i != %i || resonse: %i != %i"), id, checkId, status.Int(), iResponse);	
			TEST(EFalse);
			}
			
		if(iWaitForUpdate && ReadInt() != 0) // Paused update after the time-out
			{
			TEST(EFalse);
			}
		}
	
	//Clean-up
	session.NotifyOnResponseCancel();	
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();

	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-362
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-363
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-364
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-365
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-366
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-367
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-368

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Snooze, Clear, Pause, Silence specified alarms, and cancel notifications
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Alert Server in MAN mode;
				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
				   		(1) Snooze alarm #2 through MEikServAlarm
				   		(2) Clear alarm #2 (via MEikServAlarm).
				   		(3) Pause sound for alarm #2 (via MEikServAlarm) for 1 minute.
				   		(4) Clear all alarms.
				   		(5) Silence alarm #2 through MEikServAlarm.
				   		(6) Cancel alarm notification.
				   Alert Server in MAN mode;
				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
				   		(7) Cancel alarm notification.

   @SYMTestExpectedResults Vverify that RASAltClientSession::NotifyOnResponse() triggers, sending back 
   								(1) Snooze message and AlarmId of alarm #2.
   								(2) Clear message and AlarmId of alarm #2.
   								(3) Pause sound message and AlarmId of alarm #2.
   								(4) EASAlertServerResponseClearAll.
   								(5) proper message and specified AlarmId (alarm #2).
   								(6) KErrCancel.
   								(7) KErrCancel.
 */
void CTMultipleAlarmStep::DoNotifyTest1L()
	{
	// Notify test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-362"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iQueueResponse = ETrue;
	iWaitForUpdate = ETrue;
	iSnoozeTime = 1;
	iResponse = 4;			// EASAltAlertServerResponseSnooze
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-363"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iResponse = 2;			// EASAltAlertServerResponseClear
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 3
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-364"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iSnoozeTime = 1;
	iResponse = 5;			// EASAltAlertServerResponsePauseSound
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 4
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-365"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iResponse = 3;			// EASAltAlertServerResponseClearAll
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 5
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-366"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iQueueResponse = ETrue;
	iResponse = 0;			// EASAltAlertServerResponseSilence
	NotifyTestL();	
	RecordTestResultL();
	
	// Notify test 6
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-367"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 0;
	iCancelNotify = ETrue;
	iResponse = -3;			// KErrCancel
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 7
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-368"));
	iMaxAlarms = 1;
	iAlarmCount = 1;
	iId = 0;
	iCancelNotify = ETrue;
	iResponse = -3;			// KErrCancel
	NotifyTestL();
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}


/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-373
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-374
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-375
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-376

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc TaskKeyPressedL in Alert Server and Quiet period response chain
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in SAN mode;
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
					   Perform a TaskKeyPressedL in the Alert Server.
				   (2) Repeat (1) in MAN mode.
				   (3) Alert Server in SAN mode;
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
					   Perform a SetQuietPeriodL in the Alert Server.
				   (4) Repeat (3) in MAN mode.
				   
   @SYMTestExpectedResults Verify that RASAltClientSession::NotifyOnResponse() triggers,
   								(1) Snoozing the specified AlarmId (alarm #1).
   								(2) Snoozing the specified AlarmId (alarm #1).
   								(3) and TimeWhenQuietPeriodShouldEnd() returns the correct time.
   								(4) and TimeWhenQuietPeriodShouldEnd() returns the correct time.
 */
void CTMultipleAlarmStep::DoNotifyTest2L()
	{
	TDateTime dt;

	// Notify test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-373"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 3;
	iResponse = 1005;		// ETestActionTaskKey
	NotifyTestL();
	RecordTestResultL();

	// Notify test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-374"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	iResponse = 1005;		// ETestActionTaskKey
	NotifyTestL();
	RecordTestResultL();

	// Notify test 3
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-375"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iId = 3;
	dt.SetHour(07);
	dt.SetMinute(00);
	iTime = dt;
	iResponse = 1007;		// ETestActionSetQuietPeriod
	NotifyTestL();
	RecordTestResultL();

	// Notify test 4
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-376"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 2;
	dt.SetHour(07);
	dt.SetMinute(00);
	iTime = dt;
	iResponse = 1007;		// ETestActionSetQuietPeriod
	NotifyTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}


/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-380
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-381
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-382

   @SYMPREQ	PREQ1118

   @SYMTestCaseDesc Snooze specified alarm
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Alert Server in MAN mode;
				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data);
				   	(1) Snooze alarm #2 through MEikServAlarm with a snooze time out of 0 minutes.
				   	(2) Snooze alarm #2 through MEikServAlarm with a snooze time out of 61 minutes.
				   	(3) Snooze alarm #2 through MEikServAlarm with default snooze timeout.

   @SYMTestExpectedResults Verify that RASAltClientSession::NotifyOnResponse() triggers, 
   						   sending back Snooze message and AlarmId of alarm #2 
 */
void CTMultipleAlarmStep::DoNotifyTest3L()
	{
	// Notify test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-380"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iNoResponse = ETrue;
	iSnoozeTime = 0;
	iResponse = 4;			// EASAltAlertServerResponseSnooze
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-381"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iQueueResponse = ETrue;
	iSnoozeTime = 61;
	iResponse = 4;			// EASAltAlertServerResponseSnooze
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 3
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-382"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iQueueResponse = ETrue;
	iSnoozeTime = -1;
	iResponse = 4;			// EASAltAlertServerResponseSnooze
	NotifyTestL();
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}


/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-386
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-387
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-388
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-389

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Snooze and pause sound for specified alarm
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Alert Server in MAN mode;
				   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
				   	(1) Pause sound for alarm #2 (via MEikServAlarm) for 0 minutes..
				   	(2) Pause sound for alarm #2 (via MEikServAlarm) for 61 minutes.
				   	(3) Pause sound for alarm #2 (via MEikServAlarm) for 120 minutes.
				   	(4) Snooze alarm #2 through MEikServAlarm with a snooze time out of 120 minutes.

   @SYMTestExpectedResults Verify that RASAltClientSession::NotifyOnResponse() triggers, 
   							(1, 2, 3) Sending back PauseSound message and AlarmId of alarm #2.
   							(4) Sending back Snooze message and AlarmId of alarm #2

 */
void CTMultipleAlarmStep::DoNotifyTest4L()
	{
	// Notify test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-386"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iSnoozeTime = 0;
	iNoResponse = ETrue;
	iResponse = 5;			// EASAltAlertServerResponsePauseSound
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-387"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iSnoozeTime = 61;
	iResponse = 5;			// EASAltAlertServerResponsePauseSound
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 3
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-388"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iSnoozeTime = 120;
	iResponse = 5;			// EASAltAlertServerResponsePauseSound
	NotifyTestL();
	RecordTestResultL();
	
	// Notify test 4
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-389"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iId = 1;
	iSnoozeTime = 120;
	iResponse = 4;			// EASAltAlertServerResponseSnooze
	NotifyTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::ServerDeathTestL()
	{
	INFO_PRINTF2(_L("Testing Server Death with MaxAlarms=%d"), iMaxAlarms);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms, iMaxAlarms, ETestActionDie);

	RASAltClientSession session;
	User::LeaveIfError(session.Connect());		
	CleanupClosePushL(session);
	
	TRequestStatus status;
	session.NotifyAlertServerDeath(status);

	// Add alarms
	TInt ret = AddAlarmsL(session);
	TEST(ret == KErrServerTerminated || ret == KErrNone); // Server may die during AddAlarmsL()
	
	User::WaitForRequest(status);
	TEST(status == KErrServerTerminated);

	//Clean-up
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-371
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-372

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Alert Server death
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in SAN mode; 
					   Create RASClientSession, register for NotifyAlertServerDeath; stop alert server.
				   (2) Repeat (1) in MAN mode
   
   @SYMTestExpectedResults NotifyAlertServerDeath should complete.
 */
void CTMultipleAlarmStep::DoServerDeathTestL()
	{
	// Server Death test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-371"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	ServerDeathTestL();
	RecordTestResultL();
	
	// Sound test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-372"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	ServerDeathTestL();
	RecordTestResultL();
	CloseTMSGraphicsStep();
	}

//
//


void CTMultipleAlarmStep::SwitchEventTestL()
	{
	INFO_PRINTF2(_L("Testing SwitchEvent with Action=%d"), iAction);
	TEST(iMaxAlarms > 0);
	TEST(iAlarmCount > 0);

	// Start alert server
	StartAlertServerL(iMaxAlarms, iAlarmCount, iAction, Time::NullTTime(), iSnoozeTime, EFalse, iInitialState);	
		
	RASAltClientSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);

	// Add alarms
	TEST(AddAlarmsL(session) == KErrNone); 

	if(iAction == ETestActionHandleSwitchAndPause)  
		{
		TEST(ReadIntL() == iAction && ReadIntL() == iSnoozeTime);
		}	

	for(TInt i = 1; i <= iMaxAlarms; ++i)
		{
		if(iNoResponse)
			{
			TRAPD(r, ReadIntL());
			INFO_PRINTF1(_L("Checking that we don't receive pause time when we shouldn't"));
			TEST(r == KErrUnderflow);
			}
		else 
			{			
			// snooze time is only valid for alarm we operated on.
			TInt expectedSnooze = (i == iAlarmCount) ? iExpectedSnoozeTime : 0;
			TEST(ReadIntL() == iAction && ReadIntL() == expectedSnooze);
			}
		}
	
	//Clean-up
	session.NotifyOnResponseCancel();	
	CleanupStack::PopAndDestroy(&session);
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-377
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-378
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-390
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-391
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-392
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-393
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-394

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc HandleSwitchOnEvent
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions (1) Alert Server in SAN mode; 
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing corresponding supplementary data;
					   Perform a HandleSwitchOnEvent in the Alert Server.
				   (2, 3, 4, 5, 6, 7) Alert Server in MAN mode;
					   Create RASClientSession, notify Alarm Server on the 3 alarms in a row (call RASClientSession::SetAlarm() 3 times providing 
					   corresponding supplementary data. Each separate test case use different initial alarm state.
					   Perform a HandleSwitchOnEvent in the Alert Server.

   
   @SYMTestExpectedResults UpdateSoundPauseTimeInterval will be called in the Alert Server.
 */
void CTMultipleAlarmStep::DoSwitchEventTestL()
	{
	// Switch Event test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-377"));
	iMaxAlarms = 1;
	iAlarmCount = 3;
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();

	// Switch Event test 2
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-378"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();

	// Switch Event test 3
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-390"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();
	
	// Switch Event test 4
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-391"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iNoResponse = ETrue;
	iInitialState = 4; 		// EASAltStateFlagsInQuietPeriod (1 << 2)
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();

	// Switch Event test 5
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-392"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iNoResponse = ETrue;
	iInitialState = 2; 		// EASAltStateFlagsSilentRunning (1 << 1)
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();

	// Switch Event test 6
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-393"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iNoResponse = ETrue;
	iInitialState = 32;		// EASAltStateFlagsSilentRunning (1 << 5)
	iAction = 1006; 		// ETestActionHandleSwitch
	SwitchEventTestL();
	RecordTestResultL();

	// Switch Event test 7
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-394"));
	iMaxAlarms = 3;
	iAlarmCount = 3;
	iSnoozeTime = 1;
	iExpectedSnoozeTime = 2;
	iAction = 1009; 		// ETestActionHandleSwitchAndPause
	SwitchEventTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}


//
//


TInt CTMultipleAlarmStep::RTestSession::Connect(TInt aVersion)
	{
	const TVersion KVersion(aVersion, KASAltVersionMinor, KASAltVersionBuild);
	return CreateSession(KAlarmAlertServerName, KVersion);
	}
	
TInt CTMultipleAlarmStep::RTestSession::SendOpCode(TInt aOpCode)
	{
	return SendReceive(aOpCode);
	}


void CTMultipleAlarmStep::SessionTestL()
	{
	INFO_PRINTF2(_L("Testing session with SessionCount=%d"), iSessionCount);
	TEST(iMaxAlarms > 0);

	const TInt KBadOpcode = 0xffff;

	// Start Alert Server
	StartAlertServerL(iMaxAlarms);
	
	RTestSession session;
	TInt ret = session.Connect(iSessionVersion);
	if(ret == KErrNone)
		{
		for(TInt i = 1; i < iSessionCount; ++i)
			{
			RTestSession failedSession;
			
			if(failedSession.Connect(iSessionVersion) != KErrArgument)
				{
				failedSession.Close();
				TEST(EFalse);
				}
			}
		
		if(iInvalidOpCode)
			{
			// Should be the last entry in the enum
			TEST(session.SendOpCode(KBadOpcode) == KErrNotSupported);
			}
		}
	else
		{
		TEST(ret == KErrNotSupported && iSessionVersion != KASAltVersionMajor);
		}
		
	//Clean-up
	session.Close();
	StopAlertServer();
	ResetConfigValues();
	}

/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-383
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-384
 */
/**
   @SYMTestCaseID UIF-UCT-PREQ1118-MAN-AltS-385

   @SYMPREQ	PREQ1118
  
   @SYMTestCaseDesc Multiple sessions, wrong client, invalid op-code, 
   
   @SYMTestPriority High 
  
   @SYMTestStatus Implemented
   
   @SYMTestActions Alert Server in MAN mode;
					(1) Create multiple client sessions and attempt to connect to alert server.
				   	(2) Attempt to connect to alert server using wrong client major version.
				   	(3) Send an invalid op-code to Alert Server.
   
   @SYMTestExpectedResults (1) All sessions except the first one should fail to connect with KErrArgument.
   						   (2) Connect call should fail with KErrNotSupported.
   						   (3) Call completes with KErrNotSupported.
 */
void CTMultipleAlarmStep::DoSessionTestL()
	{
	// Session test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-383"));
	iMaxAlarms = 3;
	iSessionCount = 3;
	iSessionVersion = 3;
	SessionTestL();
	RecordTestResultL();

	// Session test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-384"));
	iMaxAlarms = 3;
	iSessionCount = 2;
	iSessionVersion = 2;
	SessionTestL();
	RecordTestResultL();

	// Session test 1
	SetTestStepID(_L("UIF-UCT-PREQ1118-MAN-AltS-385"));
	iMaxAlarms = 3;
	iSessionCount = 1;
	iSessionVersion = 3;
	iInvalidOpCode = ETrue;
	SessionTestL();
	RecordTestResultL();

	CloseTMSGraphicsStep();
	}

//
//


TVerdict CTMultipleAlarmStep::doTestStepL()
{
	__UHEAP_MARK;
	TRAPD(ret,DoMaxAlarmTestL());
	INFO_PRINTF2(_L("  DoMaxAlarmTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoAddAlarmTestL());
	INFO_PRINTF2(_L("  DoAddAlarmTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoDelAlarmTestL());
	INFO_PRINTF2(_L("  DoDelAlarmTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoSoundTestL());
	INFO_PRINTF2(_L("  DoSoundTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoVisibleTestL());
	INFO_PRINTF2(_L("  DoVisibleTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoStateTestL());
	INFO_PRINTF2(_L("  DoStateTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoQuietTestL());
	INFO_PRINTF2(_L("  DoQuietTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoNotifyTest1L());
	INFO_PRINTF2(_L("  DoNotifyTest1L completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoNotifyTest2L());
	INFO_PRINTF2(_L("  DoNotifyTest2L completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoNotifyTest3L());
	INFO_PRINTF2(_L("  DoNotifyTest3L completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoNotifyTest4L());
	INFO_PRINTF2(_L("  DoNotifyTest4L completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoServerDeathTestL());
	INFO_PRINTF2(_L("  DoServerDeathTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoSwitchEventTestL());
	INFO_PRINTF2(_L("  DoSwitchEventTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	__UHEAP_MARK;
	TRAP(ret,DoSessionTestL());
	INFO_PRINTF2(_L("  DoSessionTestL completes with %d\n"), ret);
	TEST(ret==KErrNone);
	__UHEAP_MARKEND;

	INFO_PRINTF1(_L("Test Completed!"));	
	return TestStepResult();
}

