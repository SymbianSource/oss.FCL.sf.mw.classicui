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

#include "TRemoteFactory.h"

#include <asaltdefs.h>
#include "eikalsup.h"
#include <uikon/eikalsrv.h>

CTRemoteFactory* CTRemoteFactory::NewL()
	{
	CTRemoteFactory *self = new (ELeave) CTRemoteFactory;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}
	
CTRemoteFactory::CTRemoteFactory() :
	iMaxAlarms(1),
	iResponse(EFalse),
	iId(-1),
	iResponseCode(-1),
	iCount(0),
	iSnoozeTime(0)
	{
	}
	
void CTRemoteFactory::ConstructL()
	{
	User::LeaveIfError(iMsgQ.OpenGlobal(KRemoteQName, EOwnerThread));
	iMaxAlarms = ReadInt();
	iState = ReadInt();
	iResponse = ReadBool();
	
	if(iResponse) 
		{
		iId = ReadInt();
		iResponseCode = ReadInt();
		
		iSnoozeTime = ReadInt();
		iUpdateSnooze = ReadBool();
			
		iQuietPeriod = TTime(MAKE_TUINT64(ReadInt(), ReadInt()));
		}
	}
	
CTRemoteFactory::~CTRemoteFactory()
	{
	}
	
MEikServAlarm* CTRemoteFactory::NewAlarmL(CEikAlmControlSupervisor& aSupervisor)
	{
	return CTRemoteAlarm::NewL(aSupervisor, this, iState);
	}

TInt CTRemoteFactory::ReadInt()
	{
	TRemoteMsg msg;
	iMsgQ.ReceiveBlocking(msg);
	return msg.Int();
	}

TBool CTRemoteFactory::ReadBool()
	{
	TRemoteMsg msg;
	iMsgQ.ReceiveBlocking(msg);
	
	return msg.Bool();
	}
	
void CTRemoteFactory::SendInt(const TInt aValue)
	{
	TRemoteMsg msg(aValue);
	iMsgQ.SendBlocking(msg);
	}
	
void CTRemoteFactory::SendData(const TDesC8& aData)
	{
	for(TInt i = 0; i < aData.Size(); i += KRemoteQMaxDataSize)
		{
		TPtrC8 mid = aData.Mid(i);
		
		TRemoteMsg msg(mid.Ptr(), KRemoteQMaxDataSize);		
		iMsgQ.SendBlocking(msg);
		}
	}

CTRemoteAlarm* CTRemoteAlarm::NewL(CEikAlmControlSupervisor& aSupervisor, CTRemoteFactory* aFactory, TInt aState)
	{
	return new (ELeave) CTRemoteAlarm(aSupervisor, aFactory, aState);
	}

CTRemoteAlarm::CTRemoteAlarm(CEikAlmControlSupervisor& aSupervisor, CTRemoteFactory* aFactory, TInt aState) :
	iSupervisor(aSupervisor), iFactory(aFactory), iAlarmId(KNullAlarmId), iState(aState)
	{
	}

CTRemoteAlarm::~CTRemoteAlarm()
	{
	iFactory->SendInt(iAlarmId);
	}
	
void CTRemoteAlarm::Release()
	{
	delete this;
	}
	
void CTRemoteAlarm::ShowAlarm()
	{
	iFactory->SendInt(EASAltOpCodeVisible);
	iFactory->SendInt(iAlarmId);

	if(iFactory->Server()->AlarmAlertIsVisible() == EFalse) // Already showing
		{
		iFactory->SendInt(ETrue);
		}

	else // Will be updated on completion.
		{
		iFactory->SendInt(!iFactory->Server()->AlarmAlertIsVisible());
		}
	
	// If we are testing TaskKeyPressedL do this here since we will only be notified for visible alarms.
	if (iFactory->Response() && 
		iFactory->ResponseId() == iAlarmId &&
		iFactory->ResponseCode() == ETestActionTaskKey) // We are in response mode
		{
		TRAP_IGNORE(iFactory->Server()->TaskKeyPressedL());
		}	
	}
	
void CTRemoteAlarm::HideAlarm()
	{
	iFactory->SendInt(EASAltOpCodeVisible);
	iFactory->SendInt(iAlarmId);

	if(iFactory->Server()->AlarmAlertIsVisible() == EFalse) // Already hidden
		{
		iFactory->SendInt(EFalse);
		}

	else // Will be updated on completion.
		{
		iFactory->SendInt(!iFactory->Server()->AlarmAlertIsVisible());
		}
	}
	
TInt CTRemoteAlarm::CurrentServerState() const
	{
	return iState;
	}
	
void CTRemoteAlarm::UpdateSoundPauseTimeInterval(TInt aMinutes)
	{
	if (iFactory->Response())
		{
		switch(iFactory->ResponseCode())
			{
		case ETestActionHandleSwitch: // If we are testing HandleSwitchOnEvent
		case ETestActionHandleSwitchAndPause: // or we are testing ETestActionHandleSwitchAndPause tell test step we got the update
			iFactory->SendInt(iFactory->ResponseCode());
			iFactory->SendInt(aMinutes);
			break;
		case EASAltAlertServerResponseSnooze: // Send update snooze interval in case someone is waiting
			if(aMinutes != iFactory->SnoozeTime() && iFactory->UpdateSnooze())  // Only send if it has been updated
				{
				iFactory->SendInt(aMinutes);
				}
			break;
		default:
			break;
			}
		}
	}
	
void CTRemoteAlarm::UpdateForAlarmServerState(TInt aNewAlarmServerState)
	{
	iState = aNewAlarmServerState;
	iFactory->SendInt(EASAltOpCodeSetState);
	iFactory->SendInt(aNewAlarmServerState);
	iFactory->SendInt(iAlarmId);
	
	if (iFactory->Response() && iFactory->ResponseId() == iAlarmId) // We are in response mode
		{
		switch(iFactory->ResponseCode())
			{
		case EASAltAlertServerResponseSnooze:
			if(iFactory->SnoozeTime() >= 0)
				{
				TRAP_IGNORE(iSupervisor.CmdTaskAwayFromAlarmL(iFactory->SnoozeTime()));
				}
			else 
				{
				TRAP_IGNORE(iSupervisor.CmdTaskAwayFromAlarmL());
				}
			
			break;
				
		case EASAltAlertServerResponseClear:
			iSupervisor.CmdAcknowledgeAlarm();
			break;
			
		case EASAltAlertServerResponsePauseSound:
			TRAP_IGNORE(iSupervisor.CmdPauseAlarmSoundL(iFactory->SnoozeTime()));
			break;
		case EASAltAlertServerResponseClearAll:
			TRAP_IGNORE(iFactory->Server()->ClearAllAlarmsL());
			break;
			
		case ETestActionSetQuietPeriod:
			TRAP_IGNORE(iFactory->Server()->SetQuietPeriodL(iFactory->QuietPeriod()));
			break;			
		case EASAltAlertServerResponseSilence:
			iSupervisor.CmdSilenceAlarmSound();
			break;
			
		case ETestActionHandleSwitch:
			iFactory->Server()->HandleSwitchOnEvent();
			break;
			

			
		case ETestActionDie:
			CActiveScheduler::Stop();
			break;
			
		case ETestActionHandleSwitchAndPause:
			TRAP_IGNORE(iSupervisor.CmdPauseAlarmSoundL(iFactory->SnoozeTime()));
			iFactory->Server()->HandleSwitchOnEvent();
			break;
		
		default:
			break;
			}
		}
	}
	
void CTRemoteAlarm::UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName& /*aOwner*/)
	{
	iAlarmId = aAlarm.Id();
	
	iFactory->SendInt(EASAltOpCodeSetAlarm);
	iFactory->SendInt(iAlarmId);

	const TDesC8& data = iSupervisor.AlarmData();
	
	iFactory->SendInt(data.Size());	
	iFactory->SendData(data);
	
	}
	
void CTRemoteAlarm::StartPlayAlarmL(const TDesC& aAlarmName)
	{
	iFactory->SendInt(EASAltOpCodeStartPlayingSound);
	iFactory->SendInt(iAlarmId);
	
	TBuf8<KMaxAlarmSoundNameLength> buf;
	buf.Copy(aAlarmName);
	iFactory->SendData(buf);
	}
	
void CTRemoteAlarm::StopPlayAlarm()
	{
	iFactory->SendInt(EASAltOpCodeStopPlayingSound);
	iFactory->SendInt(iAlarmId); 
	}
