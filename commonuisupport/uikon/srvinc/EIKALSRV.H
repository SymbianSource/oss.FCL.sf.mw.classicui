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
 WARNING: For internal use ONLY. Compatibility is not guaranteed in future releases.
*/

#ifndef __EIKALSRV_H__
#define __EIKALSRV_H__

#include <e32base.h>
#include <asaltdefs.h>
#include <asshddefs.h>

class MEikServAlarmFactory;
class MEikServAlarm;
class CEikServAlarmAlertSession;

/** 
@publishedPartner
WARNING: Class for internal use ONLY. Compatibility is not guaranteed in future releases.
*/
NONSHARABLE_CLASS(CEikServAlarmAlertServer) : public CPolicyServer
	{
public:
	IMPORT_C static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControlFactory);
	IMPORT_C static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControlFactory, TInt aMaxAlarms);
	~CEikServAlarmAlertServer();
	IMPORT_C void HandleSwitchOnEvent();
	IMPORT_C void TaskKeyPressedL();
	inline TBool AlarmAlertIsVisible() const;
	inline void SessionDied();
	IMPORT_C void SetQuietPeriodL(TTime aQuietPeriodEndTime);
	IMPORT_C void ClearAllAlarmsL();	
public: // from CPolicyServer
	CSession2* NewSessionL(const TVersion& aVersion, const RMessage2& aMessage) const;
private:
	CEikServAlarmAlertServer(TInt aPriority, MEikServAlarmFactory& aAlarmControlFactory,  TInt aMaxAlarms);
private:
	CEikServAlarmAlertSession* iSession; // iSession does not *own* what it points to
	MEikServAlarmFactory& iAlarmControlFactory;
	TInt iMaxAlarms;
	};


class CEikAlmControlSupervisor;

/** 
Helper class for CEikServAlarmAlertSession. Holds response data for queuing
@publishedPartner
WARNING: Class for internal use ONLY. Compatibility is not guaranteed in future releases.
*/
NONSHARABLE_CLASS(TAlarmResponse)
	{
public:	
	TAlarmResponse (TASAltAlertServerResponse  aCode,  TAlarmId aId, TTime aTime);
	TASAltAlertServerResponse ResponseCode () const;
	TAlarmId AlarmId () const;
	TTime TimeToSnooze() const;
private:
	TASAltAlertServerResponse  iCode;
	TAlarmId iId;
	TTime iTime;
	};
	
// supposed to be maximum one response in a queue, because client should resubmit request 
// for response as soon	as it receive previous 
const TInt KAlertResponseQueueSize = 20;	

/**
Represents a session for a client thread on the server-side.
@publishedPartner
WARNING: Class for internal use ONLY. Compatibility is not guaranteed in future releases. 
*/
NONSHARABLE_CLASS(CEikServAlarmAlertSession) : public CSession2
	{
public:
	static CEikServAlarmAlertSession* NewL(MEikServAlarmFactory& aAlarmControlFactory, TInt aMaxAlarms);
	~CEikServAlarmAlertSession();
	void TaskKeyPressedL();
	void HandleSwitchOnEvent();
	inline TBool AlarmAlertIsVisible() const;

	void SetQuietPeriodL(TTime aQuietPeriodEndTime);
	inline TTime QuietPeriodEndTime() const; 
	void RespondEventL(TASAltAlertServerResponse aCode);
	void RespondEventL(TASAltAlertServerResponse aCode, TAlarmId aId, TTime aTimeToSnooze = 0);
	void ClearAllAlarmsL();
private:
	CEikServAlarmAlertServer* AlarmAlertServer() const;
	void ConstructL();
	virtual void ServiceL(const RMessage2 &aMessage);

	CEikServAlarmAlertSession(MEikServAlarmFactory& aAlarmControl, TInt aMaxAlarms);
	void QueueEventL (TASAltAlertServerResponse&  aCode,TAlarmId& aId, TTime& aTimeToSnooze);
	TInt FindAlarm(TAlarmId aAlarmId) const;
	void DeleteAlarmL(const RMessage2& aMessage);
	void UpdateVisibility();
private:
	TBool iVisible;
	MEikServAlarmFactory& iAlarmControlFactory;
	TTime iQuietPeriodEndTime;
	TInt iMaxAlarms;
	RPointerArray<CEikAlmControlSupervisor> iAlarmSupervisors;
	RArray <TAlarmResponse> iResponseQueue;
	RMessage2 iMessage;
	};

/** WARNING: Function for internal use ONLY. Compatibility is not guaranteed in future releases.*/
inline TBool CEikServAlarmAlertServer::AlarmAlertIsVisible() const 
	{ return iSession->AlarmAlertIsVisible(); }

/** WARNING: Function for internal use ONLY. Compatibility is not guaranteed in future releases.*/
inline TBool CEikServAlarmAlertSession::AlarmAlertIsVisible() const 
	{ return iVisible; }

/** WARNING: Function for internal use ONLY. Compatibility is not guaranteed in future releases.*/
inline void CEikServAlarmAlertServer::SessionDied() 
	{ iSession = NULL; }

/** WARNING: Function for internal use ONLY. Compatibility is not guaranteed in future releases.*/
inline TTime CEikServAlarmAlertSession::QuietPeriodEndTime() const 
	{ return iQuietPeriodEndTime; }

#endif //__EIKALSRV_H__
