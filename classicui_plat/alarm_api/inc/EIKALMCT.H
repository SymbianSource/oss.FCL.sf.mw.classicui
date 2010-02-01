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


#if !defined (__EIKALMCT_H__)
#define __EIKALMCT_H__

#include <e32base.h>
#include <uikon/eiksvfty.h>

//
// CEikAlarmControl class
//

class MAlarmObserver;
class CEikAlmControlSupervisor;
class CEikServAppUiBase;
class TASShdAlarm;

class CEikAlarmControl : public CBase, public MEikServAlarm
    {
public: // specific
    IMPORT_C CEikAlarmControl(CEikAlmControlSupervisor* aSupervisor, CEikServAppUiBase* aAppUi);
    IMPORT_C ~CEikAlarmControl();
    IMPORT_C void ConstructL();
public: // from MEikServAlarm
    void Release();
    void ShowAlarm();
    void HideAlarm();
    TInt CurrentServerState() const;
    void UpdateSoundPauseTimeInterval(TInt aMinutes);
    void UpdateForAlarmServerState(TInt aNewAlarmServerState);
    void UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName& aOwner);
    void StartPlayAlarmL(const TDesC& aAlarmName);
    void StopPlayAlarm();
private: // specific
    void LayoutButtons(const TRect& aRect);
    // void CheckSilenceButtonDimmed();

private:
    //CEikControlGroup* iButtons;
    TInt iCurrentAlarmServerState;
    CEikAlmControlSupervisor* iSupervisor;
    CEikServAppUiBase* iAppUi;

    RLibrary iLibrary;
    MAlarmObserver* iAlarm;
	TInt iSpare;
    };

#endif
