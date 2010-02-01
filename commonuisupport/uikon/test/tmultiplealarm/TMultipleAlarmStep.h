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

#ifndef __TMULTIPLEALARMSTEP_H
#define __TMULTIPLEALARMSTEP_H

/**
includes
*/
#include <e32msgqueue.h>
#include <asshddefs.h>

#include <test/testexecutestepbase.h>
#include "TRemoteControl.h"
#include "TAlarm.h"
#include "appfwk_tmsteststep.h"

/**
needed classes
*/
class RASAltClientSession;

/**
constants and definitions
*/
const TInt KInvalidAlarmId = -1;


/**
Test step utility class, contains test methods.
*/
class TAlarmData
	{
public:
	TAlarmData(TAlarmId aId, TPtrC aData) :	iAlarmId(aId), iData(aData)
			{	
			}
	TAlarmData(TAlarmId aId) : iAlarmId(aId)
			{	
			}
	static TInt Compare(const TAlarmData& aD1, const TAlarmData& aD2)
		{
		return (aD1.iAlarmId - aD2.iAlarmId);
		}
		
	TAlarmId iAlarmId;
	TBuf<256> iData;
	};

/**
Test step utility class, contains test methods.
*/


/**
Test step base class, contains test methods.
*/
class CTMultipleAlarmStep : public CTmsTestStep
	{
public:
	CTMultipleAlarmStep();
	~CTMultipleAlarmStep();
	
	virtual TVerdict doTestStepPreambleL();
	virtual TVerdict doTestStepPostambleL();
	virtual TVerdict doTestStepL();

private:
	void LaunchServerL(const TInt aMaxAlarms, const TBool aReplies, const TAlarmId aId, const TInt aResponse, const TTime& aTime, TInt aSnoozeTime, TBool aUpdateSnooze,TInt aInitialState);

	void StartAlertServerL(const TInt aMaxAlarms);
	void StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse);
	void StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse, const TTime& aTime);
	void StartAlertServerL(const TInt aMaxAlarms, const TAlarmId aId, const TInt aResponse, const TTime& aTime, TInt aSnoozeTime, TBool aUpdateSnooze, TInt aInitialState);
	void StopAlertServer();
	
	void SendInt(const TInt aValue);
	void SendBool(const TBool aValue);
	TInt ReadInt();
	TInt ReadIntL();
	void ReadData(TDes8& aBuffer);
	
	void ResetConfigValues();
	
private:
	void MaxAlarmTestL();
	void AddAlarmTestL();
	TInt AddAlarmsL(RASAltClientSession& aSession);
	TInt AddAlarmL(RASAltClientSession& aSession, const TAlarmId aId, const TDesC8& aData);
	void DelAlarmTestL(const TInt aDeleteAll = 0);
	void SoundTestL();
	void VisibleTestL();
	void StateTestL();
	void QuietTestL();
	void NotifyTestL();
	void ServerDeathTestL();
	void SwitchEventTestL();
	void SessionTestL();

private:
	void DoMaxAlarmTestL();
	void DoAddAlarmTestL();
	void DoDelAlarmTestL();
	void DoSoundTestL();
	void DoVisibleTestL();
	void DoStateTestL();
	void DoQuietTestL();
	void DoNotifyTest1L();
	void DoNotifyTest2L();
	void DoNotifyTest3L();
	void DoNotifyTest4L();
	void DoServerDeathTestL();
	void DoSwitchEventTestL();
	void DoSessionTestL();

private:
	RMsgQueue<TRemoteMsg> iMsgQ;
	RProcess iServer;

	TInt iMaxAlarms;
	TInt iAlarmCount;
	TInt iInitialState;
	TAlarmId iId;
	TInt iState;
	TInt iQuietTime;

	RArray<TAlarmData> iDataArray;

	// Notify tests	
	TInt iResponse;
	TInt iSnoozeTime;
	TBool iQueueResponse;
	TBool iCancelNotify;
	TBool iNoResponse;
	TBool iWaitForUpdate;
	TTime iTime;
	
	TInt iPauseTime;
	TInt iExpectedSnoozeTime;
	TInt iAction;

private:
	class RTestSession : public RSessionBase
		{
		public:
		TInt Connect(TInt aVersion);
		TInt SendOpCode(TInt aOpCode);
		};

	TInt iSessionCount;
	TInt iSessionVersion;
	TBool iInvalidOpCode;	
	};


_LIT(KTMultipleAlarm, "TMultipleAlarm");

#endif // __TMULTIPLEALARMSTEP_H
