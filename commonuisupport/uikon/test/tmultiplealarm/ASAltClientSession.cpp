// Copyright (c) 1999-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "ASAltClientSession.h"

// User includes
#include "asaltdefs.h"
#include "asshdalarm.h"
//nclude "assrvstaticutils.h"

//
// ----> RASAltClientSession (source)
//

//*************************************************************************************
RASAltClientSession::RASAltClientSession()
:	iTimePointer(NULL, 0, 0),
	iAlarmPckg(TASShdAlarm())
    ,iAlarmIdPointer(NULL, 0, 0)
	{
	}


//
//
//


//*************************************************************************************
TInt RASAltClientSession::Connect()
	{
	const TVersion KVersion(KASAltVersionMajor, KASAltVersionMinor, KASAltVersionBuild);
	return CreateSession(KAlarmAlertServerName, KVersion);
	}


//
//
//


//*************************************************************************************
/**
 * Be notified if the alarm alert server dies for any reason.
 */
void RASAltClientSession::NotifyAlertServerDeath(TRequestStatus& aStatus) const
	{
	SendReceive(EASAltOpCodeLogon, aStatus);
	}




//*************************************************************************************
/**
 * Cancel the previous server-death notification
 */
void RASAltClientSession::NotifyOnResponseCancel() const
	{
#ifdef _DEBUG
	const TInt error = 
#endif
	SendReceive(EASAltOpCodeNotifyCancel);
//_ASSERT_DEBUG(error == KErrNone || error == KErrServerTerminated || error == KErrBadHandle, ASSrvStaticUtils::Fault(ASSrvStaticUtils::EASSrvFaultAlarmAlertServerFault));
	}


//*************************************************************************************
void RASAltClientSession::SetQuietPeriod(const TTime& aTimeToRemainQuietUntil) const
	{
	TIpcArgs args(I64LOW(aTimeToRemainQuietUntil.Int64()),I64HIGH(aTimeToRemainQuietUntil.Int64()));
	Send(EASAltOpCodeSetDeferTime, args);
	}



//*************************************************************************************
void RASAltClientSession::SetAlarm(TRequestStatus& aStatus, const TASShdAlarm& aAlarm, const TFullName& aOwner, const TDesC8& aAlarmData)
	{
	TPckgC<TASShdAlarm> pAlarm(aAlarm);  
	iAlarmPckg.Set(pAlarm);
	iAlarmOwner.Copy(aOwner);
	iAlarmData.Set(aAlarmData);
	//
	TIpcArgs args(&iAlarmPckg, &iAlarmOwner, &iAlarmData);
	SendReceive(EASAltOpCodeSetAlarm, args, aStatus);
	}



//*****************************************
//*    Multialarm version of interface    *
//*****************************************

/**
Receive messages (asynchronously) from the Alarm Alert Server
@param aStatus Returns the result code after the asynchronous call completes. use RASAltClientSession::NotifyOnResponseCancel() to cancel
@param aTimeThatSnoozeShouldEnd On return has a time when  snooze period should end.
@param aAlarmId On return Id of alarm which initiate this response
*/
void RASAltClientSession::NotifyOnResponse(TRequestStatus& aStatus, TTime& aTimeThatSnoozeShouldEnd, TAlarmId& aAlarmId)
	{
	iAlarmIdPointer.Set(reinterpret_cast<TUint8*>(&aAlarmId), sizeof(TAlarmId), sizeof(TAlarmId));
	PrepareTimePointer(aTimeThatSnoozeShouldEnd);
	TIpcArgs args(&iAlarmIdPointer, &iTimePointer );
	SendReceive(EASAltOpCodeNotify, args, aStatus);
	}


/**
Ask the alarm alert server to start playing the specified alarm sound
@param aSoundFile Sound file name
@param aAlarmId Id of alarm which should paly the sound
 */
void RASAltClientSession::StartPlayingSound(const TDesC& aSoundFile, TAlarmId aAlarmId) const
	{
	TIpcArgs args(&aSoundFile, aAlarmId);
	Send(EASAltOpCodeStartPlayingSound, args);
	}

/**
Ask the alarm alert server to stop playing all sounds (if any)
*/
void RASAltClientSession::StopPlayingSound() const
	{
	Send(EASAltOpCodeStopPlayingSoundAll);
	}

/**
Ask the alarm alert server to stop playing the specified sound.
@param aAlarmId Id of alarm which should stop playing sound
 */
void RASAltClientSession::StopPlayingSound(TAlarmId aAlarmId) const
	{
	TIpcArgs arg(aAlarmId);
	Send(EASAltOpCodeStopPlayingSound, arg);
	}

/**
Change the visibility of all notifying alarms
@param aVisible Set to ETrue if alarms should be visible, EFalse otherwise
*/
void RASAltClientSession::SetVisibility(TBool aVisible) const
	{
	TIpcArgs args(aVisible);
	Send(EASAltOpCodeVisibleAll, args);
	}
/**
Change the visibility of the particular alarm.
@param aVisible Set to ETrue if alarm should be visible, EFalse otherwise
@param aAlarmId Id of alarm which visibility should be changed
*/
void RASAltClientSession::SetVisibility(TBool aVisible, TAlarmId aAlarmId) const
	{
	TIpcArgs args(aVisible, aAlarmId);
	Send(EASAltOpCodeVisible, args);
	}

/**
Update the Alarm Server's flags for all notifying alarms
@param aAlarmAlertFlags Alarm Server's flags
*/
TInt RASAltClientSession::SetAlertServerState(TBitFlags aAlarmAlertFlags) const
	{
	//
	TIpcArgs args(aAlarmAlertFlags.Value());
	
	Send(EASAltOpCodeSetStateAll, args);
	return KErrNone; // error code is no longer propagated
	}

/**
Update the Alarm Server's flags for particular alarm
@param aAlarmAlertFlags Alarm Server's flags
@param aAlarmId Id of alarm which should be updated
*/

TInt RASAltClientSession::SetAlertServerState(TBitFlags aAlarmAlertFlags, TAlarmId aAlarmId) const
	{
	//
	TIpcArgs args(aAlarmAlertFlags.Value(), aAlarmId);
	
	Send(EASAltOpCodeSetState, args);
	return KErrNone; // error code is no longer propagated
	}



/**
Return the the time at which the current alarm should be snoozed until.
@param aStatus Returns the result code after the asynchronous call completes.
@param aTimeBuf On return time at which the current alarm should be snoozed until.
 */
void RASAltClientSession::TimeWhenQuietPeriodShouldEnd(TRequestStatus& aStatus,TPckgBuf<TTime>& aTimeBuf) const
	{
	TIpcArgs args(&aTimeBuf);
	SendReceive(EASAltOpCodeGetEndQuietTime,args,aStatus);	
	}	
	

/**
Get the maximum number of simultaneously notifying alarms supported by GUI
@param aMaxNumberOfAlarms On return number of supported alarms
*/
void RASAltClientSession::GetMaxNumberOfAlarms(TInt& aMaxNumberOfAlarms) const
	{
	TPckg<TInt> package(aMaxNumberOfAlarms);
	TIpcArgs args( &package);
	SendReceive(EASAltOpCodeGetMaxAlarms, args);
	}

/**
Delete particular alarm form Alert Server 
Do nothing if alarm with provided ID doesn't exist or .MaxNumberOfAlarms == 1
@param aAlarmId ID of alarm which should be deleted
*/
	
void RASAltClientSession::DeleteAlarm(TAlarmId aAlarmId) const
	{
	TIpcArgs args(aAlarmId);
	Send(EASAltOpCodeDeleteAlarm, args);
	}

/**
Delete all alarms form Alert Server 
Do nothing if MaxNumberOfAlarms == 1
*/
	
void RASAltClientSession::DeleteAlarm() const
	{
	Send(EASAltOpCodeDeleteAlarmAll);
	}

	

//
//
//


//*************************************************************************************
/**
 * Update the pointer to refer to the specified time
 */
void RASAltClientSession::PrepareTimePointer(TTime& aTime)
	{
	iTimePointer.Set(reinterpret_cast<TUint8*>(&aTime), sizeof(TTime), sizeof(TTime));
	}



