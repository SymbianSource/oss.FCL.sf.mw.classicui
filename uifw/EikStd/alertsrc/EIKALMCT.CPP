/*
* Copyright (c) 1997-1999 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:
*
*/

#include <uikon/eiksvfty.h>
#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <uikon/eiknotifyalert.h>
#endif

#include "AlarmObserver.h"
#include "Eikalmct.h"
//#include "eikalert.hrh"


_LIT(KAlertDllFile, "AlmAlert.dll");

//
// CEikAlarmControl class
//

EXPORT_C CEikAlarmControl::CEikAlarmControl(CEikAlmControlSupervisor* aSupervisor, CEikServAppUiBase* aAppUi)
    : iSupervisor(aSupervisor), iAppUi(aAppUi)
    //
    // default c'tor
    //
    {
    }

EXPORT_C CEikAlarmControl::~CEikAlarmControl()
    //
    // d'tor
    //
    {
    if (iAlarm)
        {
        iAlarm->Release();
        }
    iLibrary.Close();
    }

void CEikAlarmControl::Release()
    {
    delete this;
    }

void CEikAlarmControl::StartPlayAlarmL(const TDesC& aAlarmName)
    {
    if (iAlarm)
        {
        iAlarm->StartPlayAlarmL(aAlarmName);
        }
    /*if (iAlarmPlayer)
        iAlarmPlayer->StartPlay();
    else
        iAlarmPlayer=CEikAlarmPlayer::NewL(*iEikonEnv,aAlarmName);*/
    }

void CEikAlarmControl::StopPlayAlarm()
    {
    if (iAlarm)
        {
        iAlarm->StopPlayAlarm();
        }
    /*if (iAlarmPlayer)
        iAlarmPlayer->StopPlay();*/
    }

EXPORT_C void CEikAlarmControl::ConstructL()
    //
    // Create window and components
    //
    {
    User::LeaveIfError(iLibrary.Load(KAlertDllFile));
    TLibraryFunction constructor = iLibrary.Lookup(1);
    iAlarm = (MAlarmObserver*)((*constructor)());
    User::LeaveIfNull(iAlarm);
    iAlarm->ConstructL(iSupervisor, iAppUi);
    }

void CEikAlarmControl::ShowAlarm()
    {
    if (iAlarm)
        {
        iAlarm->ShowAlarm();
        }
    }

void CEikAlarmControl::HideAlarm()
    {
    if (iAlarm)
        {
        iAlarm->HideAlarm();
        }
    /*if (!IsVisible())
        return;
    delete iAlarmPlayer;
    iAlarmPlayer=NULL;
    RWindowGroup& groupWin=iAppUi->AlertGroupWin();
    for (TInt i=0; i<3; i++)
        {
        groupWin.CancelCaptureKey(iExternalKeys[i]);
        groupWin.CancelCaptureKeyUpAndDowns(iExternalKeyUpAndDowns[i]);
        }
    iAppUi->BringAlertGroupWinForwards(EFalse);
    MakeVisible(EFalse);

    iCba->MakeVisible(EFalse);
    // Make the CBA refuse keypresses
    CCoeControl* cba = iCba->ButtonGroup()->AsControl();
    iEikonEnv->EikAppUi()->UpdateStackedControlFlags(cba,
        ECoeStackFlagRefusesAllKeys | ECoeStackFlagRefusesFocus,
        ECoeStackFlagRefusesAllKeys | ECoeStackFlagRefusesFocus);

    iEikonEnv->RouseSleepingDialog(this,EFalse);*/
    }

TInt CEikAlarmControl::CurrentServerState() const
    {
    if (iAlarm)
        {
        return iAlarm->CurrentServerState();
        }
    return iCurrentAlarmServerState;
    }

void CEikAlarmControl::UpdateSoundPauseTimeInterval(TInt aMinutes)
    //
    // Update the visual pause time
    //
    {
    if (iAlarm)
        {
        iAlarm->UpdateSoundPauseTimeInterval(aMinutes);
        }
    }

void CEikAlarmControl::UpdateForAlarmServerState(TInt aNewAlarmServerState)
    {
    iCurrentAlarmServerState = aNewAlarmServerState;
    if (iAlarm)
        {
        iAlarm->UpdateForAlarmServerState(aNewAlarmServerState);
        }
    // The order of the following are important
    // Note that these are always updated because they can change independently
    // of their binary state.
    /*TInt timePaused=iSupervisor->PauseSoundMinutes();
    if (!timePaused && aNewAlarmServerState&EAlmSvrSoundOff)
        iAlarmInfoView->SetSoundOff();
    else if (!timePaused && aNewAlarmServerState&EAlmSvrQuietPeriod)
        iAlarmInfoView->SetQuietPeriodTimeEnd(iSupervisor->QuietPeriodEndTime());
    else
        iAlarmInfoView->SetPauseSoundTime(timePaused);
    if (aNewAlarmServerState==iCurrentAlarmServerState)
        return;
    if (!timePaused && (aNewAlarmServerState&EAlmSvrNoSoundToPlay) && (!(aNewAlarmServerState&EAlmSvrSoundOff)))
        {
        CEikAlarmControlInfo::TSilentType silent=CEikAlarmControlInfo::ESilentAlarm;
        //if (!(iButtons->ControlById(EEikBidOk)->IsDimmed())) // silence pressed
        if (!iSilence)
            silent=CEikAlarmControlInfo::EAlarmSilenced;
        //iAlarmInfoView->SetNoSoundToPlay(silent);
        }
    if (aNewAlarmServerState&EAlmSvrManyDueAlarms)
        iAlarmInfoView->SetManyDueAlarms();
    if (aNewAlarmServerState&EAlmSvrNoSnoozeMemory)
        iAlarmInfoView->SetNoMemoryToSnooze();
    iAlarmInfoView->DrawSnoozeLabelNow();*/
    //
    }

/*void CEikAlarmControl::CheckSilenceButtonDimmed()
    {*/
    /*CCoeControl* silenceButton=iButtons->ControlById(EEikBidOk);
    TBool wasDimmed=silenceButton->IsDimmed();
    TBool newDimmed=iCurrentAlarmServerState&(EAlmSvrQuietPeriod|EAlmSvrSoundOff|EAlmSvrNoSoundToPlay);
    if (wasDimmed!=newDimmed)
        {
        silenceButton->SetDimmed(newDimmed);
        silenceButton->DrawNow();
        }*/
/*    TBool wasDimmed(iSilence);
    TBool newDimmed(iCurrentAlarmServerState &
        (EAlmSvrQuietPeriod|EAlmSvrSoundOff|EAlmSvrNoSoundToPlay));
    if (wasDimmed != newDimmed)
        {
        iSilence = newDimmed;
        }
    }*/

void CEikAlarmControl::UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName &aOwner)
    {
    if (iAlarm)
        {
        iAlarm->UpdateAlarmInfo(aAlarm, aOwner);
        }
    //iTime->UpdateDate();
    //iTime->UpdateCityInfo();
    /*_LIT(KFormatBuf," (%S)");
    TBuf<KAlarmMaxCharInTitle> ownerBuf;
    if (aAlarm.iType!=EAlarmTypeClock)
        {
        TPtrC owner=BaflUtils::ExtractAppNameFromFullName(aOwner);
        if (owner.Length())
            ownerBuf.Format(KFormatBuf ,&owner);
        }
    iAlarmInfoView->SetAlarm(aAlarm, ownerBuf);
    iAlarmInfoView->DrawAllLabelsNow();*/
    }

