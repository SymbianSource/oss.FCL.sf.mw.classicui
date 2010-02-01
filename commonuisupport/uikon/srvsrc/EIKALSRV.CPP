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
// Multialarm version of Alert Server
// 
//

/**
 @file
*/

#include "EIKALSRV.H"

// System includes

#include "EIKSRV.PAN"
#include <eiksrv.h>
#include <asaltdefs.h>
#include <asshdalarm.h>

// User includes
#include "EIKALSUP.H"
#include "EIKSVFTY.H"
#include "EIKPANIC.H"
#include "EIKSRV.PAN"


// Security constants

const TUint8 KPolicyElementSID = 0;

const TInt KAlarmServerSid = 0x101f5027;

const TUint KRangeCount = 6; 

const TInt KEikServAlarmAlertServerRanges[KRangeCount] = 
	{	
	EASAltOpCodeNotify,		
	EASAltOpCodeVisible,	
	EASAltOpCodeGetUserTime, 
	EASAltOpCodeStartPlayingSound,
	EASAltOpCodeGetEndQuietTime,
	EASAltOpCodeLast,
	};

const TUint8 KElementsIndex[KRangeCount] =
	{
	CPolicyServer::EAlwaysPass,		//Always passing no capability required (Notify, NotifyCancel)
	KPolicyElementSID,				//Requires SID to be of Alarmserver ie.0x101f5027 (Visible,SetState, SetAlarm, SetDeferTime)
	CPolicyServer::EAlwaysPass,		//Always passing no capability required (GetUserTime, Logon)
	KPolicyElementSID,				//Requires SID to be of Alarmserver ie.0x101f5027  (StartPlayingSound, StopPlayingSound, VisibleAll, SetStateAll, StopPlayingSoundAll, DeleteAlarm)
	CPolicyServer::EAlwaysPass,		//Always passing no capability required (GetEndQuietTime, GetMaxAlarms)
	CPolicyServer::ENotSupported,	//Not Supported		[EASAltOpCodeLast-End]
	};

const CPolicyServer::TPolicyElement KPolicyElements[] = 
	{ 
	{_INIT_SECURITY_POLICY_S0(KAlarmServerSid), CPolicyServer::EFailClient} 
	};

const CPolicyServer::TPolicy KEikServAlarmAlertServerPolicy =
	{
	CPolicyServer::EAlwaysPass, 
	KRangeCount,
	KEikServAlarmAlertServerRanges,
	KElementsIndex, 	 
	KPolicyElements 	
	};
 	

//
// class CEikServAlarmAlertServer
//

/**
Constructor.
*/
CEikServAlarmAlertServer::CEikServAlarmAlertServer(TInt aPriority, MEikServAlarmFactory& aAlarmControlFactory, TInt aMaxAlarms) :
	CPolicyServer(aPriority, KEikServAlarmAlertServerPolicy),
	iAlarmControlFactory(aAlarmControlFactory),
	iMaxAlarms(aMaxAlarms)
	{
	__ASSERT_ALWAYS(aMaxAlarms > 0, Panic(EEsPanicAlarmAlert));	
	}

/**
Creates a new Alert Server.  When an alarm expires, the Alert Server will request an Alarm Control from 
the Alarm Control factory.  The number of Alarm Controls at any instance in time will not exceed the specified 
maximum limit.

@param aAlarmControlFactory Pointer to the Alarm Control factory.  The Alert Server does not take ownership.
@param aMaxAlarms Maximum number of concurrent Alarm Controls that the Alarm Control factory will be requested to manufacture.
@return Pointer to the Alert Server.
*/
EXPORT_C CEikServAlarmAlertServer* CEikServAlarmAlertServer::NewL(MEikServAlarmFactory* aAlarmControlFactory,  TInt aMaxAlarms)
	{
	CEikServAlarmAlertServer* server = new (ELeave) CEikServAlarmAlertServer(EActivePriorityIpcEventsHigh, *aAlarmControlFactory, aMaxAlarms);

	CleanupStack::PushL(server);
	server->StartL(KAlarmAlertServerName);
	CleanupStack::Pop(server);
	
	return server;
	}
	
	
/**
Creates a new Alert Server.  When an alarm expires, the Alert Server will request an Alarm Control from 
the Alarm Control factory.  There is only one Alarm Control at any instance in time.

@param aAlarmControlFactory Pointer to the Alarm Control factory.  The Alert Server does not take ownership.
@return Pointer to the Alert Server.
*/	
EXPORT_C CEikServAlarmAlertServer* CEikServAlarmAlertServer::NewL(MEikServAlarmFactory* aAlarmControlFactory)
	{
	return NewL(aAlarmControlFactory, 1);
	}
			
CEikServAlarmAlertServer::~CEikServAlarmAlertServer()
	{
	iSession = NULL;
	}
														
CSession2* CEikServAlarmAlertServer::NewSessionL(const TVersion& aVersion, const RMessage2& /*aMessage*/) const
	{
	const TVersion KAlarmAlertServerVersion(KASAltVersionMajor, KASAltVersionMinor, KASAltVersionBuild);
	if (iSession)
		User::Leave(KErrArgument);	// There should only ever be one session with the alarm alert server.
	
	if (!User::QueryVersionSupported(KAlarmAlertServerVersion, aVersion) || aVersion.iMajor <=2)  //Current implementation doesn't support old clients 
		User::Leave(KErrNotSupported);

	CEikServAlarmAlertSession* const session = CEikServAlarmAlertSession::NewL(iAlarmControlFactory, iMaxAlarms);
	const_cast<CEikServAlarmAlertServer*>(this)->iSession = session; // iSession does not *own* what it points to
	return session;
	}


EXPORT_C void CEikServAlarmAlertServer::TaskKeyPressedL()
	{
	if (iSession)
		iSession->TaskKeyPressedL();
	}


EXPORT_C void CEikServAlarmAlertServer::HandleSwitchOnEvent()
	{
	if (iSession)
		iSession->HandleSwitchOnEvent();
	}


EXPORT_C void CEikServAlarmAlertServer::SetQuietPeriodL(TTime aQuietPeriodEndTime)
	{
	if (iSession)
		iSession->SetQuietPeriodL(aQuietPeriodEndTime);
	}


EXPORT_C void CEikServAlarmAlertServer::ClearAllAlarmsL()
	{
	if (iSession)
		iSession->ClearAllAlarmsL();
	}


//
// class CEikServAlarmAlertSession
//


CEikServAlarmAlertSession* CEikServAlarmAlertSession::NewL(MEikServAlarmFactory& aAlarmControlFactory, TInt aMaxAlarms)
	{
	CEikServAlarmAlertSession* const session = new(ELeave) CEikServAlarmAlertSession(aAlarmControlFactory, aMaxAlarms);
	CleanupStack::PushL(session);
	session->ConstructL();
	CleanupStack::Pop(session);
	return session;
	}


CEikServAlarmAlertSession::CEikServAlarmAlertSession(MEikServAlarmFactory& aAlarmControlFactory, TInt aMaxAlarms) :
	iVisible(EFalse), iAlarmControlFactory(aAlarmControlFactory), iMaxAlarms(aMaxAlarms)
	{
	}
	

CEikServAlarmAlertSession::~CEikServAlarmAlertSession()
	{
	CEikServAlarmAlertServer* const server = AlarmAlertServer();
	if (server)
		server->SessionDied();
	
	// Delete all the alarm supervisors
	const TInt count = iAlarmSupervisors.Count();	
	for(TInt i = 0; i < count; i++)
		delete iAlarmSupervisors[i];
	
	iAlarmSupervisors.Reset();
	iResponseQueue.Reset();	
	}


void CEikServAlarmAlertSession::ConstructL()
	{
	if (iMaxAlarms == 1)
		{
		CEikAlmControlSupervisor* alarmSupervisor = CEikAlmControlSupervisor::NewLC(iAlarmControlFactory, this);
		iAlarmSupervisors.AppendL(alarmSupervisor);
		CleanupStack::Pop(alarmSupervisor);
		}
	}


void CEikServAlarmAlertSession::TaskKeyPressedL()
	{
	const TInt count = iAlarmSupervisors.Count();
	for(TInt idx = 0; idx < count; idx++)
		{
		if (iAlarmSupervisors[idx]->IsVisible())
			iAlarmSupervisors[idx]->CmdTaskAwayFromAlarmL();
		}		
	}


void CEikServAlarmAlertSession::HandleSwitchOnEvent()
	{
	const TInt count = iAlarmSupervisors.Count();
	for(TInt idx = 0; idx < count; idx++)
		iAlarmSupervisors[idx]->SynchronizeCountDownTimer();
	}
	

void CEikServAlarmAlertSession::ServiceL(const RMessage2 &aMessage)
	{
	TInt idSlot(0);
	TInt idx(0);
	
	const TInt opCode = aMessage.Function();
	switch (opCode)
		{
    case EASAltOpCodeLogon:  //Will be completed automatically when session dies.
		break;
				
	case EASAltOpCodeNotify:
		if (!iMessage.IsNull()) // don't accept second pending notification request
			{
			_LIT(KPanicCategory,"EikSrv-ASAlt");
			aMessage.Panic(KPanicCategory, EEsPanicAlarmAlert);
			}
		else	
			{
			if (iResponseQueue.Count() == 0)
				iMessage = aMessage;
			else
				{
				aMessage.WriteL(0, TPckgC<TAlarmId>(iResponseQueue[0].AlarmId())); 
				aMessage.WriteL(1, TPckgC<TTime>(iResponseQueue[0].TimeToSnooze()));
				aMessage.Complete(iResponseQueue[0].ResponseCode());
				iResponseQueue.Remove(0);
				}
			}
		break;
    
    case EASAltOpCodeNotifyCancel:
    	if (!iMessage.IsNull())
			{
			iMessage.Complete(KErrCancel);
			aMessage.Complete(KErrNone);
			}
		else 
			aMessage.Complete(KErrNone);
		break;		
		
	case EASAltOpCodeSetAlarm:
		{
		TASShdAlarm alarm;
		TPckg<TASShdAlarm> pAlarm(alarm);
		aMessage.ReadL(0,pAlarm);

		if( (idx = FindAlarm(alarm.Id())) >=0 )
			{
			iAlarmSupervisors[idx]->ServiceL(aMessage);
			aMessage.Complete(KErrNone);
			return;
			}
			
       	// alarm was not found
		if (iAlarmSupervisors.Count() >= iMaxAlarms)
			{
			// and no room to create new alarm, return KErrNotFound to client to indikate this
			aMessage.Complete(KErrNotFound);
			return;
			}
			
		CEikAlmControlSupervisor* alarmSupervisor = CEikAlmControlSupervisor::NewLC(iAlarmControlFactory, this);
		iAlarmSupervisors.AppendL(alarmSupervisor);
		CleanupStack::Pop(alarmSupervisor);
		alarmSupervisor->ServiceL(aMessage);
		aMessage.Complete(KErrNone);
		}
		break;		

	case EASAltOpCodeGetMaxAlarms:
		aMessage.WriteL(0,TPckgC<TInt>(iMaxAlarms)); 
		aMessage.Complete(KErrNone);
		break;
	
	case EASAltOpCodeSetState:
	case EASAltOpCodeStartPlayingSound:
	case EASAltOpCodeVisible:
		idSlot = 1;
		//fall through
	case EASAltOpCodeStopPlayingSound:	
		{
		const TAlarmId alarmId = (idSlot==0 ? aMessage.Int0() : aMessage.Int1());
		if ((idx = FindAlarm(alarmId)) >=0)
			{
			iAlarmSupervisors[idx]->ServiceL(aMessage);
			aMessage.Complete(KErrNone);
			}
		else  //alarm was not found
			aMessage.Complete(KErrNotFound);
		}
		break;

	case EASAltOpCodeVisibleAll:
	case EASAltOpCodeSetStateAll:
	case EASAltOpCodeStopPlayingSoundAll:
		for(idx = 0; idx < iAlarmSupervisors.Count(); idx++)
			iAlarmSupervisors[idx]->ServiceL(aMessage);

		aMessage.Complete(KErrNone);		
		break;

	case EASAltOpCodeSetDeferTime:
		{
		iQuietPeriodEndTime = TTime(MAKE_TUINT64(aMessage.Int1(), aMessage.Int0()));
		aMessage.Complete(KErrNone);
		}
		break;
	
	case EASAltOpCodeGetEndQuietTime:
		aMessage.WriteL(0,TPckgC<TTime>(iQuietPeriodEndTime)); 
		aMessage.Complete(KErrNone);
		break;
	
	case EASAltOpCodeDeleteAlarmAll:
	case EASAltOpCodeDeleteAlarm:
		DeleteAlarmL(aMessage);	
		break;
	
	default:
		aMessage.Complete(KErrNotSupported);
		break;
		}
	
	UpdateVisibility();
	}


CEikServAlarmAlertServer* CEikServAlarmAlertSession::AlarmAlertServer() const
	{
	return static_cast<CEikServAlarmAlertServer*>( const_cast<CServer2*>(Server()) );
	}


void CEikServAlarmAlertSession::UpdateVisibility()
	{
	iVisible = EFalse;
	
	const TInt count = iAlarmSupervisors.Count();
	for(TInt i = 0; i < count; i++)
		iVisible |= iAlarmSupervisors[i]->IsVisible();
	}



void CEikServAlarmAlertSession::RespondEventL(TASAltAlertServerResponse aCode)
	{
	RespondEventL(aCode, KNullAlarmId);
	}


void CEikServAlarmAlertSession::RespondEventL(TASAltAlertServerResponse aCode, TAlarmId aId, TTime aTimeToSnooze)
	{
	if (iMessage.IsNull())  // if no request pending
		QueueEventL(aCode, aId, aTimeToSnooze); 
	else	
		{
		iMessage.WriteL(0,TPckgC<TAlarmId>(aId)); 
		iMessage.WriteL(1,TPckgC<TTime>(aTimeToSnooze));
		iMessage.Complete(aCode);
		}
	}
	

void CEikServAlarmAlertSession::QueueEventL(TASAltAlertServerResponse& aCode, TAlarmId& aId, TTime& aTimeToSnooze)
	{
	if (iResponseQueue.Count() < KAlertResponseQueueSize) //ignore new response if queue is full
		{
		TAlarmResponse response(aCode, aId, aTimeToSnooze);
		iResponseQueue.AppendL(response);
		}
	}


void CEikServAlarmAlertSession::ClearAllAlarmsL()
	{
	RespondEventL(EASAltAlertServerResponseClearAll);
	}
	

void CEikServAlarmAlertSession::SetQuietPeriodL(TTime aQuietPeriodEndTime)
	{
	iQuietPeriodEndTime = aQuietPeriodEndTime;

	RespondEventL(EASAltAlertServerResponseQuietPeriod);
	}	


TInt CEikServAlarmAlertSession::FindAlarm(TAlarmId aAlarmId) const
	{
	if (iMaxAlarms == 1)
		return 0;

	const TInt count = iAlarmSupervisors.Count();
	for(TInt i = 0; i < count; i++)
		{
		if (iAlarmSupervisors[i]->AlarmId() == aAlarmId)
			return i;
		}
		
	return KErrNotFound;	
	}


void CEikServAlarmAlertSession::DeleteAlarmL(const RMessage2& aMessage)
	{
	if (iMaxAlarms == 1)
		{
		aMessage.Complete(KErrNone);
		return;
		}
		
	TInt idx = 0;
	if (aMessage.Function()	== EASAltOpCodeDeleteAlarmAll)		// delete all alarms
		{ 
		const TInt cnt = iAlarmSupervisors.Count();
		for(idx = 0; idx < cnt; idx++)
			delete iAlarmSupervisors[idx];

		iAlarmSupervisors.Reset();	
		aMessage.Complete(KErrNone);
		return;	
		}
	else	//delete particular alarm
		{
		const TAlarmId alarmId(aMessage.Int0());
		if( (idx = FindAlarm(alarmId)) >=0 )	// found!
			{
			delete iAlarmSupervisors[idx];
			iAlarmSupervisors.Remove(idx); 
			aMessage.Complete(KErrNone);
			}
		else	// not found
			aMessage.Complete(KErrNotFound);
		}	
	}
	

TAlarmResponse::TAlarmResponse(TASAltAlertServerResponse aCode, TAlarmId aId, TTime aTime) :
	iCode(aCode),
	iId(aId),
	iTime(aTime)
	{
	}


TASAltAlertServerResponse TAlarmResponse::ResponseCode() const
	{
	return iCode;
	}


TAlarmId TAlarmResponse::AlarmId() const
	{
	return iId;
	}
	

TTime TAlarmResponse::TimeToSnooze() const
	{
	return iTime;
	}

