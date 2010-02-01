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

#ifndef __ASALTCLIENTSESSION_H__
#define __ASALTCLIENTSESSION_H__

// System includes
#include <e32base.h>
#include <babitflags.h>

#include <asshddefs.h>

// Classes referenced
class TASShdAlarm;  

//
// ----> RASAltClientSession (header)
//
/**
 * The client-side interface to the Alarm Alert Server
 */
class RASAltClientSession : public RSessionBase
	{
//
public:										// CONSTRUCT
//
	RASAltClientSession();

//
public:										// FROM RSessionBase
//

	/**
	 * Connect to the Alarm Alert Server
	 */
    TInt									Connect();

//
public:										// ACCESS
//

	/**
	 * Be notified if the alarm alert server dies for any reason.
	 */
	void									NotifyAlertServerDeath(TRequestStatus& aStatus) const;


	/**
	 * Cancel the previous server-death notification
	 */
	void									NotifyOnResponseCancel() const;


	/**
	 * Ask the alarm alert server to stop playing sound.
	 */
	void									StopPlayingSound() const;

	/**
	 * Change the visibility of the screen furniture in the Alarm Alert Server thread
	 */
	void									SetVisibility(TBool aVisible) const;

	/**
	 * Inform the Alarm Alert Server that a quiet period has been set
	 */
	void									SetQuietPeriod(const TTime& aTimeToRemainQuietUntil) const;

	/**
	 * Update the Alarm Alert Server's flags
	 */
	TInt									SetAlertServerState(TBitFlags aAlarmAlertFlags) const;

	/**
	 * Tell the Alarm Alert Server that an alarm is due, pass the owner
	 * information, and any client-data associated with the alarm
	 */
	void									SetAlarm(TRequestStatus& aStatus,const TASShdAlarm& aAlarm, const TFullName& aOwner, const TDesC8& aAlarmData);

	/**
	 * Request the time at which the current alarm should be snoozed until.
	 */
	void 									TimeWhenQuietPeriodShouldEnd(TRequestStatus& aStatus,TPckgBuf<TTime>& aTimeBuf) const;


	void		NotifyOnResponse(TRequestStatus& aStatus, TTime& aTimeThatSnoozeShouldEnd, TAlarmId& aAlarmId);
	void		StartPlayingSound(const TDesC& aSoundFile, TAlarmId aAlarmId) const;
	void 		StopPlayingSound(TAlarmId aAlarmId) const;	
	TInt		SetAlertServerState(TBitFlags aAlarmAlertFlags, TAlarmId aAlarmId) const;	
	void 		SetVisibility(TBool aVisible, TAlarmId aAlarmId) const;
	void 		GetMaxNumberOfAlarms(TInt& aMaxNumberOfAlarms) const;
	void		DeleteAlarm(TAlarmId aAlarmId) const;
	void		DeleteAlarm() const;



//
private:									// MEMBER DATA
//

	/**
	 * Update the pointer to refer to the specified time
	 */
	void									PrepareTimePointer(TTime& aTime);

//
private:									// MEMBER DATA
//

	/**
	 * A pointer to a modifiable TTime object.
	 */
	TPtr8									iTimePointer;
	
	/**
	 * A package of a constant TASShdAlarm object. 
	 */
	TPckgC<TASShdAlarm>						iAlarmPckg;

	/**
	 * A pointer to a constant alarm data buffer
	 */
	TPtrC8									iAlarmData;

	/**
	 * A TFullName alarm owner object
	 */
	TFullName								iAlarmOwner;
	
	/**
	 * A pointer to a modifiable TAlarmId.
	 */
	 
	TPtr8									iAlarmIdPointer;

	//TTime time
	};

#endif

