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
//
/** 	  	 
@file 	  	 
@publishedPartner 	  	 
@released 	  	 
*/

#ifndef __EIKALSUP_H__
#define __EIKALSUP_H__

// System includes
#include <e32base.h>
#include <uikon/eiksvfty.h>
#include <asaltdefs.h>
#include <uikon/eikalsrv.h>


/** Patchable ROM constant for the default number of minutes to snooze. See uikon.iby.
@publishedPartner 
@released */
IMPORT_C extern const TInt KEikAlarmDefaultSnoozeInMinutes;  // default snooze increment in minutes

/** WARNING: Constant for internal use ONLY.  Compatibility is not guaranteed in future releases. 
@publishedPartner 
@released */
const TInt KEikUseDefaultAlarmSnoozeIncrement = -1; // Use ROM constant KAlarmDefaultSnoozeInMinutes

/** Provides an interface between the alarm server and applications that need to 
handle expiring alarms. 

When an alarm has expired, this class handles silencing, acknowledging and snoozing it, 
and users switching to another application (which causes the alarm to be snoozed for a 
default period).

@publishedPartner 
@released */
NONSHARABLE_CLASS(CEikAlmControlSupervisor) : public CBase
	{
public:
	/** The priority of the periodic timer that is used to count down the snooze period. */
	enum TPriority 
		{ 
		/** The timer's priority. This value is between EPriorityStandard and EPriorityUserInput. */
		ESnoozeCountDownPriority = 0x00000001
		};
public:  //exported API
	inline TInt PauseSoundMinutes() const;
	inline TTime QuietPeriodEndTime() const;
	IMPORT_C void CmdAcknowledgeAlarm();
	IMPORT_C void CmdPauseAlarmSoundL(TInt aNumMinutes = KEikUseDefaultAlarmSnoozeIncrement);
	IMPORT_C void CmdSilenceAlarmSound();
	IMPORT_C TBool CmdTaskAwayFromAlarmL();	// use default snooze time
	IMPORT_C TBool CmdTaskAwayFromAlarmL(TInt aMinutesToSnooze);
	IMPORT_C TDesC8& AlarmData() const;
	IMPORT_C void CmdAcknowledgeAllAlarms();
public: // deprecated	
	inline TBool CmdTaskAwayFromAlarm();	// deprecated
	inline void CmdPauseAlarmSound(TInt aNumMinutes = KEikUseDefaultAlarmSnoozeIncrement);	// deprecated
public: // internal to Symbian
	static CEikAlmControlSupervisor* NewLC(MEikServAlarmFactory& aAlarmControlFactory, CEikServAlarmAlertSession* aSession);
	~CEikAlmControlSupervisor();
	void CancelTimeCountDown();
	void SynchronizeCountDownTimer();
	void ServiceL(const RMessage2& aMessage);
	TBool IsVisible() const;
	TAlarmId AlarmId() const;
protected:
	IMPORT_C virtual void CEikAlmControlSupervisor_Reserved1();
	IMPORT_C virtual void CEikAlmControlSupervisor_Reserved2();
private:
	CEikAlmControlSupervisor();
	void ConstructL(MEikServAlarmFactory& aAlarmControl, CEikServAlarmAlertSession* aSession);
	
	void StartTimeCountDown();
	static TInt CallbackSnoozeDecrement(TAny *aAlarmAlert);
	void DecrementSnoozeMinutes();
	void SetAlertState(TInt aAlarmServerStateFlags);
	void StartPlayAlarmL(const RMessage2& aMessage);
	void StopPlayAlarm();
	
	TTime ReturnTimeToSnooze(TInt aMinutesToSnooze);	
	void UpdateAlarmInfoL(const RMessage2& aMessage);
	void SetVisibility(TBool aVisible);
private:
	CPeriodic* iMinuteCountDown;
	TInt iPauseSoundMinutes;
	TTime iPauseSoundDueTime;
	
	HBufC8*	iAlarmData;
	TBool iVisible;
	CEikServAlarmAlertSession* iSession;
	TAlarmId iAlarmId;

	MEikServAlarm* iAlarmAlert;
	};

/** Gets the number of minutes remaining in the alarm's snooze period, before 
the alarm is due to expire again.

@return The number of minutes remaining in the alarm's snooze period. */
inline TInt CEikAlmControlSupervisor::PauseSoundMinutes() const
	{
	return(iPauseSoundMinutes);
	}

/** Gets the end time for the alarm server's quiet period. 

During a quiet period, any alarms that are due to expire are 
deferred until the quiet period is over. Not all UIs support 
this feature.

@return The end time for the quiet period (if any). */
inline TTime CEikAlmControlSupervisor::QuietPeriodEndTime() const
	{
	return(iSession->QuietPeriodEndTime());
	}

/** @deprecated

Deprecated in 7.0s. Use CEikAlmControlSupervisor::CmdPauseAlarmSoundL() instead 
because RMessage::WriteL() could leave. */
inline void CEikAlmControlSupervisor::CmdPauseAlarmSound(TInt aNumMinutes)
	{ CmdPauseAlarmSoundL(aNumMinutes); }

/** @deprecated

Deprecated in 7.0s. Use CEikAlmControlSupervisor::CmdTaskAwayFromAlarmL() instead 
because RMessage::WriteL() could leave. */
inline TBool CEikAlmControlSupervisor::CmdTaskAwayFromAlarm()
	{ return CmdTaskAwayFromAlarmL(); }

#endif	// __EIKALSUP_H__
