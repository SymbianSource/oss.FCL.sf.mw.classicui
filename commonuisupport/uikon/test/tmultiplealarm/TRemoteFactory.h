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

#ifndef __TRemoteFactory_h
#define __TRemoteFactory_h

#include <uikon/eiksvfty.h>
#include <e32msgqueue.h>
#include <asshdalarm.h>
#include <uikon/eiknotifyalert.h>
#include "TRemoteControl.h"

class CEikServAlarmAlertServer;

class CTRemoteFactory : public MEikServAlarmFactory
{
public:
	static CTRemoteFactory* NewL(); 
	~CTRemoteFactory();
	
	// MEikServAlarmFactory
	MEikServAlarm* NewAlarmL(CEikAlmControlSupervisor& aSupervisor);

	// Message queue stuff
	TInt ReadInt();
	TBool ReadBool();
	void SendInt(const TInt aValue);
	void SendData(const TDesC8& aData);
	
	TInt MaxAlarms() const
		{
		return iMaxAlarms;
		}
		
	void SetServer(CEikServAlarmAlertServer* aServer) 
		{
		iServer = aServer;
		}
		
	CEikServAlarmAlertServer* Server() const
		{
		return iServer;
		}
		
	TBool Response() const
		{
		return iResponse;
		}
		
	TAlarmId ResponseId() const
		{
		return iId;
		}
		
	TInt ResponseCode() const
		{
		return iResponseCode;
		}
		
	const TTime& QuietPeriod() const
		{
		return iQuietPeriod;
		}
		
	TInt SnoozeTime() const
		{
		return iSnoozeTime;
		}
		
	TBool UpdateSnooze() const
		{
		return iUpdateSnooze;	
		}
	
private:
	CTRemoteFactory();
	void ConstructL();

private:
	TInt iMaxAlarms;
	TBool iResponse;
	TAlarmId iId;
	TInt iResponseCode;
	RMsgQueue<TRemoteMsg> iMsgQ;
	CEikServAlarmAlertServer* iServer;
	TInt iCount;
	TTime iQuietPeriod;
	TInt iSnoozeTime;
	TBool iUpdateSnooze;
	TInt iState;
	};
	
class CTRemoteAlarm : public MEikServAlarm
	{
public:
	static CTRemoteAlarm* NewL(CEikAlmControlSupervisor& aSupervisor, CTRemoteFactory* aFactory, TInt aState); 
	~CTRemoteAlarm();
	
	// MEikServAlarm
	void Release();
	void ShowAlarm();
	void HideAlarm();
	TInt CurrentServerState() const;
	void UpdateSoundPauseTimeInterval(TInt aMinutes);
	void UpdateForAlarmServerState(TInt aNewAlarmServerState);
	void UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName& aOwner);
	void StartPlayAlarmL(const TDesC& aAlarmName);
	void StopPlayAlarm();

private:
	CTRemoteAlarm(CEikAlmControlSupervisor& aSupervisor, CTRemoteFactory* aFactory, TInt aState);

private:
	CEikAlmControlSupervisor& iSupervisor;
	CTRemoteFactory* iFactory;
	TAlarmId iAlarmId;
	TInt iState;
	};


#endif // __TRemoteFactory_h

