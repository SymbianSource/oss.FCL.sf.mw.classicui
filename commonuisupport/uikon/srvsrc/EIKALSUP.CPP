// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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
// MultiAlrm version of supervisor
// 
//

/**
 @file
*/

// System includes
#include <eikenv.h>
#include <eiksrv.h>
#include <asshdalarm.h>

// User includes
#include "EIKSRV.PAN"
#include "EIKALSUP.H"
#include <uikon/eiknotifyalert.h>

// Constants
const TInt KAlarmMinuteInMicroSeconds = 60000000;
 
// See eiksrv.cpp for initialization of
// EXPORT_C extern const TInt KEikAlarmDefaultSnoozeInMinutes 

CEikAlmControlSupervisor* CEikAlmControlSupervisor::NewLC(MEikServAlarmFactory& aAlarmControl, CEikServAlarmAlertSession* aSession)
	{
	CEikAlmControlSupervisor* supervisor = new (ELeave) CEikAlmControlSupervisor();
	CleanupStack::PushL(supervisor);
	supervisor->ConstructL(aAlarmControl, aSession);	
	return supervisor;	
	}

void CEikAlmControlSupervisor::ConstructL(MEikServAlarmFactory& aAlarmControlFactory, CEikServAlarmAlertSession* aSession)
	{
	iMinuteCountDown = CPeriodic::NewL(ESnoozeCountDownPriority);
	iAlarmAlert = aAlarmControlFactory.NewAlarmL(*this);
	iSession = aSession;
	}

CEikAlmControlSupervisor::CEikAlmControlSupervisor()
	{
	}

CEikAlmControlSupervisor::~CEikAlmControlSupervisor()
	{
	delete iMinuteCountDown;
	delete iAlarmData;
	
	if (iAlarmAlert)
		iAlarmAlert->Release();
	}

/**
Services requests to the server
@param aMessage Message from client.
@internalTechnology
*/
void CEikAlmControlSupervisor::ServiceL(const RMessage2 &aMessage)
	{  
	__ASSERT_DEBUG(iAlarmAlert, Panic(EEsPanicAlarmAlert));
	__ASSERT_DEBUG(!aMessage.IsNull(), Panic(EEsPanicAlarmAlert));

	switch (aMessage.Function())
		{
	case EASAltOpCodeVisible:
	case EASAltOpCodeVisibleAll:
		SetVisibility(aMessage.Int0());
		break;
	case EASAltOpCodeSetState:
	case EASAltOpCodeSetStateAll:
		iAlarmAlert->UpdateForAlarmServerState(aMessage.Int0());
		break;
	case EASAltOpCodeSetAlarm:
		UpdateAlarmInfoL(aMessage);
		break;
	case EASAltOpCodeStartPlayingSound:
		StartPlayAlarmL(aMessage); 
		break;
	case EASAltOpCodeStopPlayingSound:
	case EASAltOpCodeStopPlayingSoundAll:
		StopPlayAlarm();
		break;
	default:
		break;
		}	
	}

/**
@internalTechnology
*/
void CEikAlmControlSupervisor::CancelTimeCountDown()
	{
	iMinuteCountDown->Cancel();
	}

void CEikAlmControlSupervisor::SetVisibility(TBool aVisible)
	{
	iVisible = aVisible;
	
	if (aVisible)
 		iAlarmAlert->ShowAlarm();
	else
		iAlarmAlert->HideAlarm();
	}

/**
Static callback function.  Decrements snooze minutes
@param aAlarmControl Pointer to this. Gets cast to CEikAlarmControlSupervisor*
@internalComponent
*/
TInt CEikAlmControlSupervisor::CallbackSnoozeDecrement(TAny *aAlarmControl)
	{
	__ASSERT_ALWAYS(aAlarmControl, Panic(EEsPanicAlarmAlert));
	static_cast<CEikAlmControlSupervisor*>(aAlarmControl)->DecrementSnoozeMinutes();
	return KErrNone;
	}

/**
@internalComponent
*/
void CEikAlmControlSupervisor::DecrementSnoozeMinutes()
	{
	iPauseSoundMinutes--;
	iAlarmAlert->UpdateSoundPauseTimeInterval(iPauseSoundMinutes);
	if (iPauseSoundMinutes <= 0)
		CancelTimeCountDown();
	}

/**
@internalComponent
*/
void CEikAlmControlSupervisor::StartTimeCountDown()
	{
	TCallBack callback(&CallbackSnoozeDecrement, this);
	CancelTimeCountDown();
	iMinuteCountDown->Start(KAlarmMinuteInMicroSeconds, KAlarmMinuteInMicroSeconds, callback);
	iAlarmAlert->UpdateSoundPauseTimeInterval(iPauseSoundMinutes); 
	}

/**
@internalTechnology
*/
void CEikAlmControlSupervisor::SynchronizeCountDownTimer()
	{
	CancelTimeCountDown();
	
	TTime now;
	now.UniversalTime();
	if (iPauseSoundDueTime > now)
		{
		// sychronise timer (needed when machine has been turned off during snooze)
		TTimeIntervalSeconds seconds;
		iPauseSoundDueTime.SecondsFrom(now, seconds);
		iPauseSoundMinutes = (seconds.Int()/60)+1; // +1 because will be called back in less than a minute
		
		const TInt delay = ((seconds.Int())%60)*1000000; // pity there's no TTime::MicroSeconds32From :-(
		const TCallBack callback(&CallbackSnoozeDecrement, this);
		iMinuteCountDown->Start(delay, KAlarmMinuteInMicroSeconds, callback);
		}
	else 
		iPauseSoundMinutes = 0;
	
	TASAltClientServerStateFlags alarmState(iAlarmAlert->CurrentServerState());
	
	if (!((alarmState[EASAltStateFlagsInQuietPeriod] ||
	 	   alarmState[EASAltStateFlagsSilentRunning] ||
		   alarmState[EASAltStateFlagsAlarmHasNoSoundFileName]) &&
		   (iPauseSoundMinutes==0)))
		{
		iAlarmAlert->UpdateSoundPauseTimeInterval(iPauseSoundMinutes); 
		}
	}


/**
Update the alerts information on the current alarm.  Extracts owner and establishes whether alarm time is local
@param aMessage Message from client.  EASAltOpCodeSetAlarm
@internalComponent
*/
void CEikAlmControlSupervisor::UpdateAlarmInfoL(const RMessage2& aMessage)
	{
	const TInt KDataSlot = 2;
	iPauseSoundMinutes = 0;
	iMinuteCountDown->Cancel();
	iPauseSoundDueTime.UniversalTime();
	
	TASShdAlarm alarm;
	TPckg<TASShdAlarm> pAlarm(alarm);
	aMessage.ReadL(0, pAlarm);
	iAlarmId = alarm.Id();
	
	TFullName owner;
	aMessage.ReadL(1, owner);
	
	// Create new alarm data (use temporary newAlarmData and reassign iAlarmData on success)
	HBufC8* newAlarmData = NULL;	
	if(alarm.HasAssociatedData())
		{
		const TInt desLength = aMessage.GetDesLengthL(KDataSlot);
		newAlarmData = HBufC8::NewLC(desLength);	// Push in case ReadL() below leaves 
		TPtr8 readPtr(newAlarmData->Des());
		aMessage.ReadL(KDataSlot, readPtr);
		}
	else
		{
		newAlarmData = HBufC8::NewLC(0);
		}
		
	delete iAlarmData;
	iAlarmData = newAlarmData;
	CleanupStack::Pop(newAlarmData);
	newAlarmData = NULL;

	// These lines will make sure the alert server is given the alarm in local time, if the alarm is
	// set in local time (a floating alarm)
	//-------------------------------------------
	if (alarm.IsFloating())      
		{      
		TTimeIntervalSeconds offset = User::UTCOffset();
		if (alarm.NextDueTime() != Time::NullTTime())
			alarm.NextDueTime() += offset;
			
		if (alarm.OriginalExpiryTime() != Time::NullTTime())
			alarm.OriginalExpiryTime() += offset;
		}
	
	iAlarmAlert->UpdateAlarmInfo(alarm, owner);
	iAlarmAlert->UpdateForAlarmServerState(iAlarmAlert->CurrentServerState());
	}

/** 
This method will trigger a new alarm in aMinutesToSnooze minutes and start the 
alarm timer.

@internalTechnology */
TTime CEikAlmControlSupervisor::ReturnTimeToSnooze(TInt aMinutesToSnooze) 
	{
	if (iPauseSoundMinutes <= 0)
		iPauseSoundMinutes = aMinutesToSnooze;

	iPauseSoundDueTime.UniversalTime();
	iPauseSoundDueTime += TTimeIntervalMinutes(iPauseSoundMinutes);

	const TTime time = iPauseSoundDueTime;
	StartTimeCountDown();
	return time;
	}



void CEikAlmControlSupervisor::StartPlayAlarmL(const RMessage2& aMessage)
	{
	TBuf<KMaxAlarmSoundNameLength> alarmSoundName;
	aMessage.ReadL(0, alarmSoundName);
	iAlarmAlert->StartPlayAlarmL(alarmSoundName);
	}


void CEikAlmControlSupervisor::StopPlayAlarm()
	{
	iAlarmAlert->StopPlayAlarm();
	}


/**
Acknowledges a notifying alarm
(i.e. an alarm that is going off or has expired).

When an alarm has expired, the alarm control is notified and can call 
this function to acknowledge the alarm.  
*/
EXPORT_C void CEikAlmControlSupervisor::CmdAcknowledgeAlarm()
	{
	if (iSession)
		{
		TRAP_IGNORE(iSession->RespondEventL(EASAltAlertServerResponseClear, AlarmId()));
		}
	}

/**
Acknowledges all notifying alarms 
(i.e. all alarms that are going off or have expired).

When an alarm has expired, the alarm control is notified and can call 
this function to acknowledge all alarms that are currently notifying.  
*/
EXPORT_C void CEikAlmControlSupervisor::CmdAcknowledgeAllAlarms()
	{
	if (iSession)
		{
		TRAP_IGNORE(iSession->ClearAllAlarmsL());
		}
	}



/** 
Increases the alarm's snooze period by the specified number of minutes.

If the alarm has expired, it is snoozed by aNumMinutes. 
MEikServAlarm::UpdateSoundPauseTimeInterval() is called, which might, for instance, 
update the view to display the new snooze period. 

@param aNumMinutes The number of minutes to add to the snooze period.
*/
EXPORT_C void CEikAlmControlSupervisor::CmdPauseAlarmSoundL(TInt aNumMinutes)
	{
	// If the argument is KUseDefaultAlarmSnoozeIncrement (minus one) then change it to KAlarmDefaultSnoozeInMinutes.
	// The use of KUseDefaultAlarmSnoozeIncrement as default argument (rather than KAlarmDefaultSnoozeInMinutes)
	// is needed to allow KAlarmDefaultSnoozeInMinutes being ROM patchable constant.
	if(aNumMinutes == KEikUseDefaultAlarmSnoozeIncrement)
		aNumMinutes = KEikAlarmDefaultSnoozeInMinutes;
	
	if(iPauseSoundMinutes + aNumMinutes <= 0)
		return;
	
	iPauseSoundMinutes += aNumMinutes;

	// Update the client's TTime so that they don't need to
	// call "ReturnTimeToSnoozeL" (synchronous) in response to
	// an asynch completion here...
	const TTime time = ReturnTimeToSnooze(KEikAlarmDefaultSnoozeInMinutes);
	if (iSession)
		iSession->RespondEventL(EASAltAlertServerResponsePauseSound, AlarmId(), time); 
	}

/**
Silences the alarm sound that is playing, without changing the alarm's state.
*/
EXPORT_C void CEikAlmControlSupervisor::CmdSilenceAlarmSound()
	{
	if (iSession)
		{
		TRAP_IGNORE(iSession->RespondEventL(EASAltAlertServerResponseSilence, AlarmId()));
		}
	}


/**
If an alarm has expired, this function snoozes it for the default 
period (e.g. 5 minutes). 

This function shall be called in response to the user switching away from the 
application when an alarm has expired. 

@return Always ETrue. 
*/
EXPORT_C TBool CEikAlmControlSupervisor::CmdTaskAwayFromAlarmL()
	{
	return CmdTaskAwayFromAlarmL(KEikAlarmDefaultSnoozeInMinutes);
	}

/** 
If an alarm has expired, this function snoozes it for specified snooze period. 

This function shall be called in response to the user switching away from the 
application when an alarm has expired. 

@param aMinutesToSnooze Minutes to be added to the snooze period.
@return Always ETrue. 
*/
EXPORT_C TBool CEikAlmControlSupervisor::CmdTaskAwayFromAlarmL(TInt aMinutesToSnooze)
	{
	// Update the client's TTime so that they don't need to
	// call "ReturnTimeToSnoozeL" (synchronous) in response to
	// an asynch completion here...
	aMinutesToSnooze = Max(1, aMinutesToSnooze); //minimum snooze time is one minute, to avoid live lock between alarm server & eik server
	const TTime time = ReturnTimeToSnooze(aMinutesToSnooze);
	if (iSession)
		{
		iSession->RespondEventL(EASAltAlertServerResponseSnooze, AlarmId(), time);         
		}
	return ETrue;
	}


TBool CEikAlmControlSupervisor::IsVisible() const
	{
	return iVisible;
	}
	

TAlarmId CEikAlmControlSupervisor::AlarmId() const
	{
	return iAlarmId;
	}
	
/**
Gets data associated with alarm.

@param aData Application specific 8-bit data that was queued with the Alarm.
@return KErrNotFound if no data is associated with current alarm, KErrNone otherwise.
*/	
EXPORT_C TDesC8&  CEikAlmControlSupervisor::AlarmData() const	
	{
	return *iAlarmData;
	}
	

EXPORT_C void CEikAlmControlSupervisor::CEikAlmControlSupervisor_Reserved1()
	{
	}

	
EXPORT_C void CEikAlmControlSupervisor::CEikAlmControlSupervisor_Reserved2()
	{
	}

